#include <stdio.h>
#include <string.h>

#include <openssl/evp.h>


#define ENCRYPT 1
#define DECRYPT 0

int main()
{
    

    unsigned char key[] = "012340123401234012340123401234012340123401234012";
    unsigned char iv[]  = "ABCDEFABCDEFABCDEFABCDEFABCDEFAB";

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_CipherInit(ctx,EVP_camellia_192_cbc(), key, iv, ENCRYPT);


    unsigned char plaintext[] = "2024-04-05 CLASS"; 
    unsigned char ciphertext[48];

    int update_len, final_len;
    int ciphertext_len=0;

    EVP_CipherUpdate(ctx,ciphertext,&update_len,plaintext,strlen(plaintext));
    ciphertext_len+=update_len;
    printf("update size: %d\n",ciphertext_len);

    EVP_CipherFinal_ex(ctx,ciphertext+ciphertext_len,&final_len);
    ciphertext_len+=final_len;

    EVP_CIPHER_CTX_free(ctx);

    printf("Ciphertext lenght = %d\n", ciphertext_len);
    for(int i = 0; i < ciphertext_len; i++)
        printf("%02x", ciphertext[i]);
    printf("\n");

    return 0;
}

