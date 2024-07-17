#include <stdio.h>
#include <openssl/evp.h>
#include <string.h>
#include <openssl/err.h>

#define MAXBUF 1024

// THIS IS A WELL WRITTEN CODE IN WHICH WE COVER ALSO THE POTENTIAL ERRORS!!! IT IS GOOD FOR THE EXAM!!!    

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

    //first of all the context that is an MD one
    EVP_MD_CTX * md;

    ERR_load_crypto_strings(); // these two suggested as a best practice (also needed in the exam)
    OpenSSL_add_all_algorithms();

    //pedantic mode: also check if md == NULL
    md = EVP_MD_CTX_new();

    if(!EVP_DigestInit(md, EVP_sha1()))
        handle_errors();

    unsigned char buffer[MAXBUF];
    int n_read;
    while((n_read = fread(buffer, 1, MAXBUF, f_in) > 0)){
        if(!EVP_DigestUpdate(md, buffer, n_read))
            handle_errors();
    }

    // the computation of the digest is done in the final! now create a variable to store the digest
    unsigned char md_value[EVP_MD_size(EVP_sha1())]; // use the openssl library to get the size of the digest function used
    int md_len;

    if(!EVP_DigestFinal(md, md_value, &md_len))
        handle_errors();

    EVP_MD_CTX_free(md);

    CRYPTO_cleanup_all_ex_data(); // important to cleanup all the data and free al the strings
    ERR_free_strings();

    printf("The digest is:\n");
    for(int i=0; i<md_len; i++)
        printf("%02x", md_value[i]);
    printf("\n");

    return 0;
}