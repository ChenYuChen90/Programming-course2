// function有更短的寫法
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXEXPR 256
typedef struct Node{
    char c;
    struct Node *left, *right;
}Node;

char expr[MAXEXPR] = {};
int pos;

Node *EXPR();
Node *FACTOR();
Node *createNode(char c){
    Node *tmp = (Node*) calloc(1, sizeof(Node));
    tmp->c = c;
    return tmp;
}
void output(Node *root){
    if(root == NULL) return;
    output(root->left);
    putchar(root->c);
    if(root->right != NULL && (root->right->c == '|' || root->right->c == '&')){
        putchar('(');
        output(root->right);
        putchar(')');
    } 
    else output(root->right);
}
void freeTree(Node *root){
    if(root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
Node* EXPR(){
    char c;
    Node *node = NULL, *right = NULL;
    if(pos >= 0){
        right = FACTOR();
        if(pos > 0){
            c = expr[pos];
            if(c == '&' || c == '|'){
                node = createNode(c);
                node->right = right;
                pos--;
                node->left = EXPR(); 
            } else node = right;
        } else node = right;
    }
    return node;
}
Node* FACTOR(){
    char c;
    Node *node = NULL;
    if(pos >= 0){
        c = expr[pos--];
        if(c >= 'A' && c <= 'D'){
            node = createNode(c);
        } else if(c == ')'){
            node = EXPR();
            if(expr[pos--] != '('){
                printf("error\n");
                freeTree(node);
            }
        }
    }
    return node;
}


int main(void){
    while (scanf("%s", expr)!=EOF)
    {
        pos = strlen(expr) - 1;
        Node *root = EXPR();
        output(root);
        freeTree(root);
    }
    return 0;
}



