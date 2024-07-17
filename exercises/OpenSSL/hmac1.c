#include <stdio.h>
#include <openssl/evp.h>
#include <string.h>
#include <openssl/err.h>
#include <openssl/hmac.h>

#define MAXBUF 1024

// iNSTEAD OF USING HMAC_ APPROACH THAT IS DEPRECATED WE'LL USE ANOTHER METHOD    

// first parameter is the name of the file to hash

void handle_errors(){
    ERR_print_errors_fp(stderr);
    abort();
}

int main(int argc, char **argv){

    if(argc != 2){
        fprintf(stderr, "Invalid parameters number. Usage: %s string_to_hash\n", argv[0]);
        exit(-1);
    }

    FILE *f_in;
    if((f_in = fopen(argv[1], "r"))== NULL){
        fprintf(stderr, "Couldn't open the input file, try again\n");
        exit(-1);
    }

    
    //load the human readable error strings for libcrypto
    ERR_load_crypto_strings(); // these two suggested as a best practice (also needed in the exam)
    //load all digesst annd cipher algorithms
    OpenSSL_add_all_algorithms();

    unsigned char key[] = "1234567887654321"; // 16 ASCII characters
    EVP_PKEY *hmac_key = EVP_PKEY_new_mac_key(EVP_PKEY_HMAC, NULL, key, strlen(key));

    // check null
    EVP_MD_CTX *hmac_ctx = EVP_MD_CTX_new();

    if(!EVP_DigestSignInit(hmac_ctx, NULL, EVP_sha1(), NULL, hmac_key)) //context, ctx for public key material(for digital signature), algo, engine (don't have one), key
        handle_errors();

    int n_read;
    unsigned char buffer[MAXBUF];
    while( (n_read=fread(buffer, 1, MAXBUF, f_in)) > 0){
            if(!EVP_DigestSignUpdate(hmac_ctx, buffer, n_read))
                handle_errors();
    }

    unsigned char hmac_value[EVP_MD_size(EVP_sha1())]; //HMAC_size differently from the EVP_MD_size retrieve data directly from the context and not from the passed algorithm
    int hmac_len;
    
    if(!EVP_DigestSignFinal(hmac_ctx, hmac_value, &hmac_len))
        handle_errors();

    EVP_MD_CTX_free(hmac_ctx);

    printf("The HMAC is: ");
    for(int i=0; i<hmac_len; i++){
        printf("%02x", hmac_value[i]);
    }
    printf("\n");

    //VERIFICATION
    unsigned char hmac[] = "e0c81e906477ba344664fb5170743dc672c8c6d6";
    unsigned char hmac_binary[strlen(hmac)/2];

    //tranform hex string in binary string
    for(int i=0; i < strlen(hmac)/2; i++){
        sscanf(&hmac[2*i], "%2hhx", &hmac_binary[i]); //must use 2 characters, hh = double half the size since size is 32bit -> 16bits -> 8bits we want exactly 1byte, x=hex
    }
    //check1: length of the HMAC... check2: actual comparison of the buffers
    if((hmac_len == strlen(hmac)/2) && (CRYPTO_memcmp(hmac_binary, hmac_value, hmac_len) == 0))
        printf("Verification successful!");
    else
        printf("Verification failed.");

    // completely free all the cipher data
    CRYPTO_cleanup_all_ex_data(); 
    //remove error strings
    ERR_free_strings();

    return 0;
}