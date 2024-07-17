#include <stdio.h>
#include <string.h>

#include <openssl/evp.h>
#include <openssl/err.h>

#define ENCRYPT 1
#define DECRYPT 0
#define MAX_BUFFER 1024

void handle_errors(){
    ERR_print_errors_fp(stderr);
    abort();
}

int main(int argc, char **argv) {

   // if(argc != 5){
   //     fprintf(stderr,"Invalid parameters. Usage: %s ciphername_file key iv file_out\n",argv[0]);
   //     exit(1);
   // }

    FILE *cipherAlgoNames;
    if((cipherAlgoNames = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr,"Couldn't open the ciphername file, try again\n");
        abort();
    }

    
    FILE *f_in;
    if((f_in = fopen(argv[4], "rb")) == NULL) {
        fprintf(stderr,"Couldn't open the input file, try again\n");
        abort();
    }
 
    FILE *f_out;
    if((f_out = fopen(argv[5], "wb")) == NULL) {
        fprintf(stderr,"Couldn't open the output file, try again\n");
        abort();
    }

    unsigned char key [] = "0123456789ABCDEF";
    unsigned char iv [] = "0123456789ABCDEF";

    /* Load the human readable error strings for libcrypto */
    ERR_load_crypto_strings();
    /* Load all digest and cipher algorithms */
    OpenSSL_add_all_algorithms(); // deprecated since version 1.1.1

    char cipher_name[256];
    while (fgets(cipher_name, sizeof(cipher_name), cipherAlgoNames)) {
        cipher_name[strcspn(cipher_name, "\n")] = 0;
        const EVP_CIPHER *cipher = EVP_get_cipherbyname(cipher_name);
        if(!cipher) {
            fprintf(stderr, "Cipher %s not found\n", cipher_name);
            break;
        }

        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

        //if(!EVP_CipherInit(ctx, cipher, key, iv, DECRYPT))
        //    handle_errors();

        EVP_CipherInit(ctx, EVP_aria_128_cbc, key, iv, DECRYPT);
        
        int length;
        unsigned char plaintext[MAX_BUFFER];

        int n_read;
        unsigned char buffer[MAX_BUFFER];

        while((n_read = fread(buffer, 1, MAX_BUFFER, f_in)) > 0) {
            if(!EVP_CipherUpdate(ctx, plaintext, &length, buffer, n_read))
                handle_errors();
            if(fwrite(plaintext, 1, length, f_out) < length) {
                fprintf(stderr, "Error writing the output file\n");
                abort();
            }
        }
                
        if(!EVP_CipherFinal_ex(ctx, plaintext, &length))
            handle_errors();

        if(fwrite(plaintext, 1, length, f_out) < length) {
            fprintf(stderr, "Error writing in the output file\n");
            abort();
        }

        EVP_CIPHER_CTX_free(ctx);
        rewind(f_in); // Reset file pointer for next round of decryption
        printf("File decrypted with %s!\n", cipher_name);
    }

    fclose(cipherAlgoNames);
    fclose(f_in);
    fclose(f_out);

    // completely free all the cipher data
    CRYPTO_cleanup_all_ex_data();
    /* Remove error strings */
    ERR_free_strings();

    return 0;
}
