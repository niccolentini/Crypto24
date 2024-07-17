#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *generate_random_string() {
    char *rand_string = (char *)malloc(65 * sizeof(char));
    if (rand_string == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < 64; i++) {
        rand_string[i * 3] = rand() % 256; // Generate a random byte
        sprintf(&rand_string[i * 3], "%02x-", rand_string[i * 3]); // Convert byte to hex
    }
    rand_string[64 * 3] = '\0'; // Null terminate the string
    return rand_string;
}

char *perform_bytewise_or(char *rand1, char *rand2) {
    char *result = (char *)malloc(65 * sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < 64; i++) {
        result[i * 3] = rand1[i * 3] | rand2[i * 3]; // Perform bytewise OR
        sprintf(&result[i * 3], "%02x-", result[i * 3]); // Convert byte to hex
    }
    result[64 * 3] = '\0'; // Null terminate the string
    return result;
}

char *perform_bytewise_and(char *rand1, char *rand2) {
    char *result = (char *)malloc(65 * sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < 64; i++) {
        result[i * 3] = rand1[i * 3] & rand2[i * 3]; // Perform bytewise AND
        sprintf(&result[i * 3], "%02x-", result[i * 3]); // Convert byte to hex
    }
    result[64 * 3] = '\0'; // Null terminate the string
    return result;
}

char *perform_bytewise_xor(char *rand1, char *rand2) {
    char *result = (char *)malloc(65 * sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < 64; i++) {
        result[i * 3] = rand1[i * 3] ^ rand2[i * 3]; // Perform bytewise XOR
        sprintf(&result[i * 3], "%02x-", result[i * 3]); // Convert byte to hex
    }
    result[64 * 3] = '\0'; // Null terminate the string
    return result;
}

int main() {
    char *rand1 = "63-3b-6d-07-65-1a-09-31-7a-4f-b4-aa-ef-3f-7a-55-d0-33-93-52-1e-81-fb-63-11-26-ed-9e-8e-a7-10-f6-63-9d-eb-92-90-eb-76-0b-90-5a-eb-b4-75-d3-a1-cf-d2-91-39-c1-89-32-84-22-12-4e-77-57-4d-25-85-98";
    char *rand2 = "92-05-d8-b5-fa-85-97-b6-22-f4-bd-26-11-cf-79-8c-db-4a-28-27-bb-d3-31-56-74-16-df-cb-f5-61-a7-9d-18-c2-63-92-f1-cb-c3-6d-2b-77-19-aa-21-07-8e-fe-8b-1a-4f-7d-70-6e-a4-7b-c8-68-30-43-12-50-30-1e";

    char *k1 = perform_bytewise_or(rand1, rand2);
    char *k2 = perform_bytewise_and(rand1, rand2);
    char *key = perform_bytewise_xor(k1, k2);

    printf("CRYPTO24{%s}\n", key);

    free(k1);
    free(k2);
    free(key);

    return 0;
}

