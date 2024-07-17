#include <stdio.h>
#include<string.h>
#include <openssl/evp.h>

#define ENCRYPT 1
#define DECRYPT 0

int main() {

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    unsigned char key[] = "1234567890abcdef"; //ascii characters
    unsigned char iv[] = "abcdef1234567890";
    unsigned char ciphertext[] = "13713c9b8081468892c518592730b3496d2c58ed3a9735d90788e7c24e8d324d75f6c9f5c6e43ee7dccad4a3221d697e";

    EVP_CipherInit(ctx, EVP_aes_128_cbc(), key, iv, DECRYPT); //this is the context of the encryption

    unsigned char plaintext[strlen(ciphertext)/2]; //In the worst case P will be as long as the ciphertext. Since it is in hex, we must divide by 2 the length
    unsigned char ciphertext_bin[strlen(ciphertext)/2];

    for(int i=0; i<strlen(ciphertext)/2; i++)
        sscanf(&ciphertext[2*i], "%2hhx", &ciphertext_bin[i]); //this is to convert hexstring into binary

    int length; 
    int plaintext_len = 0;

    EVP_CipherUpdate(ctx, plaintext, &length, ciphertext_bin, strlen(ciphertext)/2);

    printf("After update: %d\n", length);
    plaintext_len+=length;

    EVP_CipherFinal(ctx, plaintext+plaintext_len, &length);
    printf("After final: %d\n", length);

    plaintext_len+=length;

    EVP_CIPHER_CTX_free(ctx); //we've finished to use this context so at the end we must free it

    plaintext[plaintext_len]='\0'; // we do that just because we know that the plaintext is shorter than the ciphertext

    printf("Plaintext = %s", plaintext);  

    return 0;
}