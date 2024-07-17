#include <stdio.h>
#include<string.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#define ENCRYPT 1
#define DECRYPT 0

// NOW WE'RE GOING TO SEE ALL THE CONTROLS THAT A GOOD PROGRAM SHOULD IMPLEMENT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// for our purposes is enough to control that if there are some errors at the context creation then the other operations will return null
// so to check that each function call is checked if(!...) then we call handle_errors that prints on ERR_print_errors_fp the stderr and abort the exectution 

void handle_errors(){
    ERR_print_errors_fp(stderr);
    abort();
}

int main() {

    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new(); //!!! check NULL 

    unsigned char key[] = "1234567890abcdef"; //ascii characters
    unsigned char iv[] = "abcdef1234567890";

    if(!EVP_CipherInit(ctx, EVP_aes_128_cbc(), key, iv, ENCRYPT))
        handle_errors(); 

    unsigned char plaintext[] = "This variable contains the data to encrypt"; //this text is 44 bytes
    unsigned char ciphertext[48]; // since P is 44 bytes the closer multiple of 16 is 48byte

    int length; //will contain the size of data processed
    int ciphertext_length = 0;

    if(!EVP_CipherUpdate(ctx, ciphertext, &length, plaintext, strlen(plaintext)))
        handle_errors();

    printf("After update: %d\n", length);
    ciphertext_length+=length;

    if(!EVP_CipherFinal(ctx, ciphertext+ciphertext_length, &length))
        handle_errors();

    printf("After final: %d\n", length);

    ciphertext_length+=length;

    EVP_CIPHER_CTX_free(ctx); 

    printf("Size of the ciphertext = %d\n", ciphertext_length);

    for(int i=0 ; i<ciphertext_length; i++)
        printf("%02x", ciphertext[i]);
    printf("\n");   

    CRYPTO_cleanup_all_ex_data();
    ERR_free_strings();

    return 0;
}