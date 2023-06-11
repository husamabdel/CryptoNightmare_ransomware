#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#ifndef FileNode
#define FileNode

#define MAX_FILE_BUFFER 1080

//Defining the Linked List for files added.

typedef struct FileNodes{

    FILE *fPointer;
    struct FileNodes* next;
    int size;

}FileNodes;

//Init the Head node.
FileNodes *head = NULL;
//Adding the files to the List.
void add_file_array(FILE *file);
//Adding all files from the current directory to the list.
void add_all_dir(char *dir_name);
//Pop the file out of the stack.
FILE* pop_file_out();
//Print a debug log to see if the files are there
void print_debug_log();

/*

Separator from function declarations.
Below are implimintations of these functions.

*/


void add_file_array(FILE *file){
    
    FileNodes *temp = (FileNodes*)malloc(sizeof(FileNodes));
    temp ->fPointer=file;
    temp->next=head;
    head=temp;

}

void add_all_dir(char *dir_name){

    struct dirent *myDir;

    DIR *dir = opendir(dir_name);

    if(dir == NULL){

        fprintf(stderr, "FileNode: Error opening current directory, aborting !!\n");
        exit(EXIT_FAILURE);

    }

    while((myDir=readdir(dir)) != NULL){

        FILE *current = fopen(myDir->d_name, "r+");

        if(current == NULL){
            perror("FileNode: Error opening current File, aborting !!");
        }

        add_file_array(current);
        printf("FileNode: Current File being added: %s ....\n", myDir->d_name);

    }

    closedir(dir);

}

FILE* pop_file_out(){

    FILE *popped = head->fPointer;
    head=head->next;
    return popped;

}

// this is @deprecated, its been addressed inside add_all_dir();
void print_debug_log(){
/*
    FileNodes *temp = head;

    int count=1;
    while(temp != NULL){

        char *nameOfFile=temp->fPointer->_wide_data;



        printf("FileNode: File no %d is: %s \n", count, nameOfFile);
        count++;
        temp=temp->next;
    }
    */
}



#endif