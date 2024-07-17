#include <stdio.h>
#include <openssl/rand.h>

#define MAX 64

int main(){
    unsigned char random_string[MAX];

    RAND_load_file("/dev/random", 64); // Load 64 bytes from /dev/random
    RAND_bytes(random_string,MAX); // Generate 64 random bytes

    printf("Sequence generated: ");
    for(int i = 0; i < MAX; i++)
        printf("%02x-", random_string[i]);
    printf("\n");

    return 0;

}