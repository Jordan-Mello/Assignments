#define _CRT_SECURE_NO_WARNINGS //this just prevents scanf from throwing errors (as it is "unsafe" on certain compilers)
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct avlN { //redo syntax
    char key[1000];
    struct avlN* L;
    struct avlN* R;
    int height;
    int count;
} avlN;

int getBalance(avlN* root);

int getHeight(avlN* root);
int maxInt(int a, int b);
int verifyCommand(char* command);
avlN* insert(avlN* root, char key[1000]);
avlN* deleteNode(avlN* root, char key[1000]);
avlN* del(avlN* root, char key[1000]);
avlN* Rrotation(avlN* root);
avlN* Lrotation(avlN* root);
avlN* smallestNode(avlN* root);
avlN* createNode(char key[1000]);

void findAll(avlN* root, int count);
void findSize(avlN* root, int* size);
void findTotalCount(avlN* root, int* totalCount);

void searchNode(avlN* root, char key[1000]);
void searchDeleted(avlN* tree, char key[1000]);

avlN* inputOne(char** argv, avlN* tree);
void inputTwo(avlN* tree);
avlN* inputThree(avlN* tree);
avlN* inputFour(avlN* tree);
void inputFive(avlN* tree, int size, int totalCount);
void inputSix(avlN* tree, int count);
void inputSeven();