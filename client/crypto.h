#ifndef CRYPT_H
#define CRYPT_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<openssl/aes.h>
#include<openssl/evp.h>
#include<string.h>
#define INPUT_BUFFER 1080
#define BLOCK_SIZE 16
#define AES_KEY_LENGTH 128


bool encrypt(char *filename, const unsigned char *key);
bool decrypt(char *filename, const unsigned char *key);

char iv[AES_KEY_LENGTH]={"@ojhge84hn4hd89j"};

extern const char key[];
#endif