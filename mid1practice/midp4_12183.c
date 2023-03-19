#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct Node{
    bool value;         // This is the value of the subtree, not the ID number
    int type;
    struct Node *lnode;
    struct Node *rnode;
    struct Node *pnode;
}Node;
Node *variable[100001];

Node *create_node(int type){
    Node *tmp = (Node*)calloc(1, sizeof(Node));
    tmp->type = type;
    return tmp;
}

Node *parse(){
    Node *root;
    char input[2];
    int index;
    scanf("%1s", input);
    if(input[0] == '['){
        scanf("%d", &index);
        root = variable[index];
        scanf("%1s", input);
    } else {
        root = create_node(input[0] == '|' ? 2 : 1);
        root->lnode = parse();
        root->lnode->pnode = root;
        root->rnode = parse();
        root->rnode->pnode = root;
    }
    return root;
}

void update(Node *root){
    if(root == NULL) return;
    if(root->type == 1) root->value = root->lnode->value && root->rnode->value;
    if(root->type == 2) root->value = root->lnode->value || root->rnode->value;
    update(root->pnode);
}

void deleteTree(Node *root){
    if(root == NULL) return;
    deleteTree(root->lnode);
    deleteTree(root->rnode);
    free(root);
}

int main(){
    int T, N, M, X;
    Node *root;
    scanf("%d", &T);
    while(T--){
        scanf("%d %d", &N, &M);
        for(int i = 0; i <= N; i++) variable[i] = create_node(0);
        root = parse();
        while(M--){
            scanf("%d", &X);
            variable[X]->value = !variable[X]->value;
            update(variable[X]->pnode);
            printf("%d\n", root->value);
        }
        deleteTree(root);
    }
}