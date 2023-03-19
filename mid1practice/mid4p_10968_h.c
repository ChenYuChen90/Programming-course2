#include <stdio.h>
#include <stdlib.h>
#ifndef FUNCTION_H
#define FUNCTION_H

typedef struct treeNode {
    char data;
    struct treeNode *left;
    struct treeNode *right;
} Node;

void constructTree(Node** head);
void printInfix(Node *root);
void freeTree(Node *root);

void printInfix(Node *root){
    if(root != NULL){
        printInfix(root->left);
        printf("%c", root->data);
        if(root->right != NULL && (root->right->data == '&' || root->right->data == '|')) printf("(");
        printInfix(root->right);
        if(root->right != NULL && (root->right->data == '&' || root->right->data == '|')) printf(")");
    }
}


#endif