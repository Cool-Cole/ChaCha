#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/random.h>

#include "chacha.h"
#include "hex.h"

#define NUMROUNDS 20

void printHelp(){

    printf( "Usage: chacha [OPTIONS]...\n"\
            "Encrypts/Decrypts files using ChaCha20\n"
            "\n"\
            " -h                        Prints this screen\n"\
            " -e [filename]             Encrypts a specified file (must be passed with -r or -k and -n)\n"\
            " -d [filename]             Decrypts a specified file (must be passed with -k and -n)\n"\
            " -k [256 bit Key in hex]   Specifies the key used for encryption/decryption\n"\
            " -n [96 bit nonce in hex]  Specifies the nonce used for encryption/decryption\n"\
            " -r                        Generates a random key and nonce pair\n"\
            "\n"\
            "Examples - \n"\
            "chacha -r -e testfile.txt\n"\
            "chacha -d testfile.txt.enc -k EFA3B9D80AF046A4ECA49F3DF2AEBE65E076ECDB48821D7881969429D7997601 -n 5D91B78D027B67C57CC0B7AF\n"\
            "\n"\
            "WARNING: This is a learning project! Do not trust this program without proper code review!\n"\
            "This executable does not delete the file that it encrypts/decrypts.\nSo don't worry about losing any data.\n"\
            "\n"\
            "ChaCha file Encryptor created by Cole 2021\n"\
            "Public Domain Software - Free Forever\n");

    exit(0);
}

void fileEncrypt(char filename[], uint8_t key[], uint8_t nonce[]){

    uint32_t counter = 1;
    uint32_t plainBufferLen = 1;
    chachastate chaInfo;

    size_t readSize = 65536;
    uint8_t buffer[readSize];

    char *fixedName = malloc(strlen(filename) * sizeof(char) + 5);
    fixedName[0] = '.';
    fixedName[1] = '/';
    fixedName[2] = '\0';
    strcat(fixedName, filename);

    FILE *rfp;
    rfp = fopen(fixedName,"rb");

    if(rfp == NULL){
        printf("Could not open %s\nQuitting...\n", filename);
        exit(1);
    }

    FILE *wfp;
    wfp = fopen(strcat(fixedName, ".enc"),"wb");

    if(wfp == NULL){
        printf("Could not create encrypted file %s\nQuitting...\n", strcat(fixedName, ".enc"));
        exit(1);
    }

    ChaChaInitialize(&chaInfo, key, nonce, &counter, NUMROUNDS);

    // While there is data still to be read from the file encrypt it
    while(plainBufferLen != 0){
        plainBufferLen = fread(buffer, 1, readSize, rfp);

        ChaChaEncrypt(&chaInfo, plainBufferLen, buffer);

        fwrite(buffer, 1, plainBufferLen, wfp);
    }

    fclose(rfp);
    fclose(wfp);
    free(fixedName);

    printf("The file has been encrypted and written to %s\n", strcat(filename, ".enc"));
}

void fileDecrypt(char filename[], uint8_t key[], uint8_t nonce[]){
    uint32_t counter = 1;
    uint32_t plainBufferLen = 1;
    chachastate chaInfo;

    size_t readSize = 65536;
    uint8_t buffer[readSize];

    char *fixedName = malloc(strlen(filename) * sizeof(char) + 5);
    fixedName[0] = '.';
    fixedName[1] = '/';
    fixedName[2] = '\0';
    strcat(fixedName, filename);

    FILE *rfp;
    rfp = fopen(fixedName,"rb");

    if(rfp == NULL){
        printf("Could not open %s\nQuitting...\n", filename);
        exit(1);
    }

    fixedName[strlen(fixedName) - 4] = '\0';

    FILE *wfp;
    wfp = fopen(fixedName,"wb");

    if(wfp == NULL){
        printf("Could not create encrypted file %s\nQuitting...\n", strcat(fixedName, ".enc"));
        exit(1);
    }

    ChaChaInitialize(&chaInfo, key, nonce, &counter, NUMROUNDS);

    // While there is data still to be read from the file encrypt it
    while(plainBufferLen != 0){
        plainBufferLen = fread(buffer, 1, readSize, rfp);

        ChaChaEncrypt(&chaInfo, plainBufferLen, buffer);

        fwrite(buffer, 1, plainBufferLen, wfp);
    }

    fclose(rfp);
    fclose(wfp);
    free(fixedName);

    filename[strlen(filename) - 4] = '\0';
    printf("The file has been decrypted and written to %s\n", filename);
}

int main(int argc, char *argv[]) {

    int opt;
    char nonceStr[25] = {'\0'};
    char keyStr[65] = {'\0'};
    char fileStr[256] = {'\0'};
    uint8_t encFlag = 0;
    uint8_t decFlag = 0;
    uint8_t randomFlag = 0;

    uint8_t keyFlag = 0;
    uint8_t nonceFlag = 0;

    uint8_t byteKey[32];
    uint8_t byteNonce[12];

    // put ':' in the starting of the
    // string so that program can
    //distinguish between '?' and ':'
    while((opt = getopt(argc, argv, ":d:e:rn:k:h")) != -1)
    {
        switch(opt)
        {
            case 'd':
                decFlag = 1;
                strcpy(fileStr, optarg);
                break;
            case 'e':
                encFlag = 1;
                strncpy(fileStr, optarg, 255);
                break;
            case 'r':
                randomFlag = 1;
                break;
            case 'k':
                keyFlag = 1;
                strncpy(keyStr, optarg, 64);
                break;
            case 'n':
                nonceFlag = 1;
                strncpy(nonceStr, optarg, 24);
                break;
            case 'h':
                printHelp();
                //break;
            case ':':
                printf("option needs a value\n");
                break;
            case '?':
                printf("unknown option: %c\n", optopt);
                break;
        }
    }

    // optind is for the extra arguments
    // which are not parsed
    //for(; optind < argc; optind++){
    //    printf("extra arguments: %s\n", argv[optind]);
    //}

    // Check to see if -r and -k/-n are passed together or not at all
    if((randomFlag != 1 && (keyFlag != 1 || nonceFlag != 1)) || (randomFlag == 1 && (keyFlag == 1 || nonceFlag == 1))){
        printHelp();
    }

    // Check to see if -d and -e are passed together or not at all
    if((encFlag == 1 && decFlag == 1) || (encFlag != 1 && decFlag != 1)){
        printHelp();
    }

    if(encFlag == 1){
        if(randomFlag == 1){
            
            // Check to make sure that getentropy executed succsessfully
            if(getentropy(byteKey, 32) == -1 || getentropy(byteNonce, 12) == -1){
                printf("Error generating random bits for the key and nonce.\nQuiting...\n");
                exit(0);
            }
            

            printf("Random key: %s\n", binToHex(byteKey, 32));
            printf("Random nonce: %s\n", binToHex(byteNonce, 12));
            printf("Keep these values safe. They are needed to decrypt the file.\n");

            fileEncrypt(fileStr, byteKey, byteNonce);
        } else if (keyFlag == 1 && nonceFlag == 1) {
            
            // Check to see if the hex strings are of correct length
            if(strlen(nonceStr) != 24 || strlen(keyStr) != 64){
                printf("Improper hex encoded nonce or key given!\nPrinting help....\n");
                printHelp();
            }
            
            // The user provided nonce and key are phrased and shown back to the user
            // if there is a discrepancy between what the user entered and what is outputted
            // then an error has obviously occurred
            printf("Key: %s\n", binToHex(hexToBin(keyStr, 64), 32));
            printf("Nonce: %s\n", binToHex(hexToBin(nonceStr, 24), 12));

            fileEncrypt(fileStr, hexToBin(keyStr, 64), hexToBin(nonceStr, 24));
        }
    }


    if(decFlag == 1){
        
        // Same trick I used in the encryption key display is used here as well
        printf("Key: %s\n", binToHex(hexToBin(keyStr, 64), 32));
        printf("Nonce: %s\n", binToHex(hexToBin(nonceStr, 24), 12));

        fileDecrypt(fileStr, hexToBin(keyStr, 64), hexToBin(nonceStr, 24));
    }
}
