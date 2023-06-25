#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<openssl/aes.h>
#include <openssl/evp.h>
#include<string.h>
#include "crypt.h"

#define INPUT_BUFFER 1080
#define BLOCK_SIZE 16
#define AES_KEY_LENGTH 128

extern const char key[];

int main(int argc, char const *argv[])
{


    return 0;
}

bool encrypt(char *filename, const unsigned char *key)
{

    static long filesEncrypted = 1;

    printf("***Starting File Encryption for file: %s***\n", filename);

    char ext[]={".fred"};
    char *outputFileName;
    outputFileName = malloc(strlen(filename) + strlen(ext) + 1);
    strcpy(outputFileName, filename);
    strcat(outputFileName, ext);

    printf("Output file name: %s\n", outputFileName);

    FILE *inputFile, *outputFile;

    long fileSize;

    inputFile=fopen(filename, "rb+");

    if(inputFile == NULL){

        perror("ERROR, could not open file, returning with false.");
        return false;

    }

    fseek(inputFile, 0, SEEK_END);
    fileSize = ftell(inputFile);
    rewind(inputFile);

    outputFile=fopen(outputFileName, "wb+");

    if(outputFile == NULL){

        perror("ERROR, could not open output file, returning with false.");
        return false;

    }

    printf("Encrypting %ld bytes from %s\n", fileSize, filename);

    char *inputFileBuffer = (char *)malloc(fileSize+1);
    char *outputFileBuffer = (char *)malloc(fileSize+1);

    AES_KEY myKey;
    AES_set_encrypt_key(key, AES_KEY_LENGTH, &myKey);

    while(fread(inputFileBuffer, sizeof(unsigned char), AES_BLOCK_SIZE, inputFile) == AES_BLOCK_SIZE){

        AES_encrypt(inputFileBuffer, outputFileBuffer, &myKey);
        fwrite(outputFileBuffer, sizeof(unsigned char), AES_BLOCK_SIZE, outputFile);

    }

    size_t remainingBytes = fread(inputFileBuffer, sizeof(unsigned char), AES_BLOCK_SIZE, inputFile);
    AES_encrypt(inputFileBuffer, outputFileBuffer, &myKey);
    fwrite(outputFileBuffer, sizeof(unsigned char), remainingBytes, outputFile);

    free(inputFileBuffer);
    free(outputFileBuffer);
    fclose(outputFile);
    fclose(inputFile);
    
    filesEncrypted++;

    printf("Encrypted %s into %s successfully\nFile size: %ld, Files Encrypted so far:%ld\n", filename, outputFileName, fileSize, filesEncrypted);

    return true;


}

bool decrypt(char *filename, const unsigned char *key)
{

    static long filesEncrypted = 1;

    printf("***Starting File Encryption for file: %s***\n", filename);

    char ext[]={".fred"};
    char *outputFileName;
    outputFileName = malloc(strlen(filename) + strlen(ext) + 1);
    strcpy(outputFileName, filename);
    strcat(outputFileName, ext);

    printf("Output file name: %s\n", outputFileName);

    FILE *inputFile, *outputFile;

    long fileSize;

    inputFile=fopen(filename, "rb+");

    if(inputFile == NULL){

        perror("ERROR, could not open file, returning with false.");
        return false;

    }

    fseek(inputFile, 0, SEEK_END);
    fileSize = ftell(inputFile);
    rewind(inputFile);

    outputFile=fopen(outputFileName, "wb+");

    if(outputFile == NULL){

        perror("ERROR, could not open output file, returning with false.");
        return false;

    }

    printf("Encrypting %ld bytes from %s\n", fileSize, filename);

    char *inputFileBuffer = (char *)malloc(fileSize+1);
    char *outputFileBuffer = (char *)malloc(fileSize+1);

    AES_KEY myKey;
    AES_set_decrypt_key(key, AES_KEY_LENGTH, &myKey);

    while(fread(inputFileBuffer, sizeof(unsigned char), AES_BLOCK_SIZE, inputFile) == AES_BLOCK_SIZE){

        AES_decrypt(inputFileBuffer, outputFileBuffer, &myKey);
        fwrite(outputFileBuffer, sizeof(unsigned char), AES_BLOCK_SIZE, outputFile);

    }

    size_t remainingBytes = fread(inputFileBuffer, sizeof(unsigned char), AES_BLOCK_SIZE, inputFile);
    AES_decrypt(inputFileBuffer, outputFileBuffer, &myKey);
    fwrite(outputFileBuffer, sizeof(unsigned char), remainingBytes, outputFile);

    free(inputFileBuffer);
    free(outputFileBuffer);
    fclose(outputFile);
    fclose(inputFile);
    
    filesEncrypted++;

    printf("Encrypted %s into %s successfully\nFile size: %ld, Files Encrypted so far:%ld\n", filename, outputFileName, fileSize, filesEncrypted);

    return true;
}