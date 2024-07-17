#include <stdio.h>
#include <openssl/rand.h>
#include <openssl/err.h> // framkework to print error messages

#define MAX 128


void handle_errors(){
    ERR_print_errors_fp(stderr);
    abort();
}

int main() {
    unsigned char random_string[MAX];
    //initialization of the sudo random generator
    if(RAND_load_file("/dev/random", 64) != 64)
        handle_errors();
        //fprintf(stderr, "Error with the intialization of the PRNG\n"); !!! with err_print_errors from openssl I can remove tehfprintf
        // explicit seeding of the prng. This function returns the number of bytes that have been actually loaded... but it may fail! and so we add the if statement

    if(RAND_bytes(random_string, MAX) != 1) //this function returns 1 when all is working and -1 or 0 with errors
        handle_errors();
        //fprintf(stderr, "Error with the intialization of the generation\n");
    

    printf("sequence generator:\n");
    for(int i=0; i<MAX; i++){
        printf("%02x-", random_string[i]);
    }
    printf("\n");

    return 0;
}