#include <stdio.h>
#include<string.h>
#include <openssl/evp.h>

#define ENCRYPT 1
#define DECRYPT 0

int main() {

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    unsigned char key[] = "1234567890abcdef"; //ascii characters
    unsigned char iv[] = "abcdef1234567890";

    EVP_CipherInit(ctx, EVP_aes_128_cbc(), key, iv, ENCRYPT); //this is the context of the encryption

    unsigned char plaintext[] = "This variable contains the data to encrypt"; //this text is 44 bytes
    unsigned char ciphertext[48]; // since P is 44 bytes the closer multiple of 16 is 48byte

    int length; //will contain the size of data processed
    int ciphertext_length = 0;

    EVP_CipherUpdate(ctx, ciphertext, &length, plaintext, strlen(plaintext));

    printf("After update: %d\n", length);
    ciphertext_length+=length;

    EVP_CipherFinal(ctx, ciphertext+ciphertext_length, &length);
    printf("After final: %d\n", length);

    ciphertext_length+=length;

    EVP_CIPHER_CTX_free(ctx); //we've finished to use this context so at the end we must free it

    printf("Size of the ciphertext = %d\n", ciphertext_length);

    for(int i=0 ; i<ciphertext_length; i++)
        printf("%02x", ciphertext[i]);
    printf("\n");   

    return 0;
}