#include <stdio.h>
#include<string.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#define ENCRYPT 1
#define DECRYPT 0
#define MAXSIZE 1024

// Let's see how to work with files... In this example we have...

// argv[1]--> input file
// argv[2]--> key (hexstring)
// argv[3]--> iv (hexstring)
// argv[4]--> file output
// save in a buffer in memory the result of the encryption

void handle_errors(){
    ERR_print_errors_fp(stderr);
    abort();
}

int main(int argc, char **argv) {

    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();

    if(argc != 4){
        fprintf(stderr, "Invalid parameters. Usage %s input:file key IV out_file\n", argv[1]);
        exit(1);
    }

    FILE *f_in;
    if( (f_in = fopen(argv[1], "r")) == NULL){
        fprintf(stderr, "Errors opening the input file: %s\n", argv[1]);
        exit(1);
    }

    FILE *f_out;
    if( (f_in = fopen(argv[4], "wb")) == NULL){
        fprintf(stderr, "Errors opening the input file: %s\n", argv[1]);
        exit(1);
    }

    //control the Key

    if(strlen(argv[2])/2 != 32){
        fprintf(stderr, "Wrong key length.\n");
        exit(1);
    }

    unsigned char key[strlen(argv[2])/2];
    for(int i=0; i<strlen(argv[2])/2; i++)
        sscanf(&argv[2][2*i], "%2hhx", &key[i]); //sscanf read from the first parameter and put the value in the format specified as second param in the third param

    //control the IV

    if(strlen(argv[3])/2 != 32){
            fprintf(stderr, "Wrong IV length.\n");
            exit(1);
        }

    unsigned char iv[strlen(argv[3])/2];
    for(int i=0; i<strlen(argv[3])/2; i++)
        sscanf(&argv[3][2*i], "%2hhx", &iv[i]);

    // Initial operations

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new(); //!!! check NULL 

    if(!EVP_CipherInit(ctx, EVP_aes_128_cbc(), key, iv, ENCRYPT))
        handle_errors();
    
    // now the data are taken from a file

    int n_read;
    unsigned char buffer[MAXSIZE];

    unsigned char ciphertext[MAXSIZE + 16]; //plus size of the block

    int len, ciphertext_len=0;

    while((n_read = fread(buffer, 1, MAXSIZE, f_in)) > 0) {

        /*
        //if you risk to overflow the ciphertext variable you exit before
        //nread + 1block > what's left in ciphertext variable (that is MAX -ciphertext_len)
        if( ciphertext_len > 100*MAXSIZE - n_read - EVP_CIPHER_CTX_block_size(ctx)){
            fprintf(stderr, "The file to cipher is to large.\n");
            exit(1);
        }
        */

       //new version with output file -> directly writing the ciphertext in the output

        if(!EVP_CipherUpdate(ctx, ciphertext, &len, buffer, n_read)) // here ciph+ciph_len is used because at each iteration the operation will start
            handle_errors();                                                        // from the point where it was remained in the step before
        ciphertext_len += len;

        if( fwrite(ciphertext, 1, len, f_out ) < len){
            fprintf(stderr, "Error writing into the output file\n");
            abort();
        }   
    }

    if(!EVP_CipherFinal(ctx, ciphertext, &len))
        handle_errors();

    ciphertext_len += len;

    if( fwrite(ciphertext, 1, len, f_out ) < len){
            fprintf(stderr, "Error writing into the output file\n");
            abort();
        } 

    EVP_CIPHER_CTX_free(ctx);

    printf("Cipherxtext length = %d\n", ciphertext_len);

    CRYPTO_cleanup_all_ex_data();
    ERR_free_strings();

    fclose(f_in);
    fclose(f_out);

    return 0;
}