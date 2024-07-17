#include <openssl/bn.h>
#include <openssl/err.h>

#define MAXBUF 1024 

int main()
{
    char hex_string1[] = "009eee82dc2cd4a00c4f5a7b8663b0c1ed0677fcebde1a235df4c3ff876a7dadc607faa835f6ae0503573e223676d50d574f99f958ad637ae745a6aafa023423b69d34157b1141b6b1cab91acd2955bd42f504abdf454a9d4eca4e01f9f8745967eeb6a9fb96b7c09400178a530eb6d831c968e66438d3633a04d7886bf0e1ad607f41bd857bd904e1975b1f9b05ceac2cc4553fb48b894d0a509a094e5e8f5b5f5569725f049b3a8a09b47f8db2ca520e5ebff4b0eec9badc934f6dd31f821ad9fc2ca73f18230dd744c728546784ee739265f01ce81e6d4d9565b4c84fb80462582bee3264a0a7dc99250e505376bc30db715e93d69f1f881c765d82c8593951";
    char hex_string2[] = "00d2c601326b4c4b855f527bb78ed68ae4c8767e6bc9249a3ecacd2fc9b875d4f97111e1cfbe62d32c5ff9fd9bfaed62f3df44c757fbee9bb232cb5449296c692e301d8c1ffab18ee44966c1fb927c82ca60c940a40ab2db50ecf6ff98a71623388d06d27ca9858ac22b4dd4e6f189e5b04254a05f3cddc764330511fbee8b2607";

    BIGNUM *big_number1 = BN_new();
    BN_hex2bn(&big_number1, hex_string1);
    BIGNUM *big_number2 = BN_new();
    BN_hex2bn(&big_number2, hex_string2);  
    
    

    
    printf("\n\n");

    // integer division
    BIGNUM *div=BN_new();
    BIGNUM *rem=BN_new();

    // a context is needed to optimize some operations
    BN_CTX *ctx=BN_CTX_new();
    BN_div(div,rem,big_number1, big_number2, ctx);
    
    BN_print_fp(stdout, div);

    printf("\ndrem=\n\n");

    BN_print_fp(stdout, rem);

    unsigned char flag[] = "c108c95709e073727db45e4b4b20bf3c5741bf5cbc144da66abd4d8669069f739d402c600f297b0b4cc77bf65ee5a61002713e74a5acb97ff3c57842cafe506f5b1bdfc7ee3620bb5673ab11fae2bfa8697de6f45c27c121693c0e1d2ddd702511579f8a5a605809905c54e0552a551ce1369d1470abb4e2cec4926bfa148fe7";

    for(int i=0; i<strlen(flag); i++){

    }


    printf("\n\n");

    /*
    For all functions, 1 is returned for success, 0 on error.
    */

    /*
    int BN_mod_exp(BIGNUM *r, BIGNUM *a, const BIGNUM *p,
            const BIGNUM *m, BN_CTX *ctx);
    */

   /*
    BIGNUM *m=BN_new();
    BN_set_word(m,35);
    // a^b mod m
    if (!BN_mod_exp(res, ,b,m,ctx)) {
        ERR_print_errors_fp(stdout);
        exit(1);
    }

    */

    /*
    int BN_cmp(BIGNUM *a, BIGNUM *b);
    int BN_ucmp(BIGNUM *a, BIGNUM *b);
    */
    

    return 0;
}
//CRYPTO24{00:c1:08:c9:57:09:e0:73:72:7d:b4:5e:4b:4b:20:bf:3c:57:41:bf:5c:bc:14:4d:a6:6a:bd:4d:86:69:06:9f:73:9d:40:2c:60:0f:29:7b:0b:4c:c7:7b:f6:5e:e5:a6:10:02:71:3e:74:a5:ac:b9:7f:f3:c5:78:42:ca:fe:50:6f:5b:1b:df:c7:ee:36:20:bb:56:73:ab:11:fa:e2:bf:a8:69:7d:e6:f4:5c:27:c1:21:69:3c:0e:1d:2d:dd:70:25:11:57:9f:8a:5a:60:58:09:90:5c:54:e0:55:2a:55:1c:e1:36:9d:14:70:ab:b4:e2:ce:c4:92:6b:fa:14:8f:e7}


//0c:10:8c:95:70:9e:07:37:27:db:45:e4:b4:b2:0b:f3:c5:74:1b:f5:cb:c1:44:da:66:ab:d4:d8:66:90:69:f7:39:d4:02:c6:00:f2:97:b0:b4:cc:77:bf:65:ee:5a:61:00:27:13:e7:4a:5a:cb:97:ff:3c:57:84:2c:af:e5:06:f5:b1:bd:fc:7e:e3:62:0b:b5:67:3a:b1:1f:ae:2b:fa:86:97:de:6f:45:c2:7c:12:16:93:c0:e1:d2:dd:d7:02:51:15:79:f8:a5:a6:05:80:99:05:c5:4e:05:52:a5:51:ce:13:69:d1:47:0a:bb:4e:2c:ec:49:26:bf:a1:48:fe:7