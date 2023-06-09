#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node{
    int val;
    struct Node *left;
    struct Node *right;
}Node;
Node *create_node(int n){
    Node *tmp = (Node*)calloc(1, sizeof(Node));
    tmp->val = n;
    return tmp;
}
void pushNode(Node **root, int val){
    Node *curr = *root, *tmp = create_node(val);
    if(curr == NULL) *root = tmp;
    else while(1){
        if(val >= curr->val){
            if(curr->right == NULL){
                curr->right = tmp;
                break;
            }
            else curr = curr->right;
        }
        else if(val < curr->val){
            if(curr->left == NULL){
                curr->left = tmp;
                break;
            }
            else curr = curr->left;
        }
    }
}
int searchVal(Node *root, int val){
    while(root != NULL){
        if(val == root->val) return 1;
        else if(val > root->val) root = root->right;
        else if(val < root->val) root = root->left;
    }
    return 0;
}
void printInorder(Node *root){
    if(root == NULL) return;
    printInorder(root->left);
    printf("%d ", root->val);
    printInorder(root->right);
}
int getMaxlevel(Node *root){
    if(root == NULL) return 0;
    int lsum, rsum;
    lsum = getMaxlevel(root->left);
    rsum = getMaxlevel(root->right);
    return 1 + (lsum > rsum ? lsum : rsum);
}
int countSum(Node *root, int level, int target){
    if(root == NULL || target == 0) return 0;
    if(level < target){
        int l = countSum(root->left, level+1, target);
        int r = countSum(root->right, level+1, target);
        return l + r;
    }
    else return root->val;
}
int countAmount(Node *root, int level, int target){
    if(root == NULL || target == 0) return 0;
    if(level < target){
        int l = countAmount(root->left, level+1, target);
        int r = countAmount(root->right, level+1, target);
        return l + r;
    }
    else return 1;
}
int main(){
    int N, M, X;
    char command[10];
    int maxLevel;
    Node *root = NULL;
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d", &X);
        if(searchVal(root, X)) continue;
        else pushNode(&root, X);
    }
    maxLevel = getMaxlevel(root);
    scanf("%d", &M);
    while(M--){
        scanf("%s", command);
        if(strcmp(command, "P") == 0){
            static int done = 0;        //??
            if(done){
                if(M == 0) puts("");
                continue;
            }
            done = 1;

            if(root == NULL) printf("NULL");
            else printInorder(root);
            puts("");
        }
        else if(strcmp(command, "GetMax") == 0){
            static int done = 0;
            if(done){
                if(M == 0) puts("");
                continue;
            }
            done = 1;

            printf("%d\n", maxLevel);
        }
        else if(strcmp(command, "SumLevel") == 0){
            static Node *quer = NULL;
            scanf("%d", &X);
            if(searchVal(quer, X)){
                if(M == 0) puts("");
                continue;
            }
            pushNode(&quer, X);

            printf("%d\n", countSum(root, 1, X));
        }
        else if(strcmp(command, "AverLevel") == 0){
            static Node *quer = NULL;
            scanf("%d", &X);
            if(searchVal(quer, X)){
                if(M == 0) puts("");
                continue;
            }
            pushNode(&quer, X);

            float sum = countSum(root, 1, X), amount = countAmount(root, 1, X);
            if(sum == 0 || amount == 0) printf("0\n");
            else printf("%.3f\n", amount == 0 ? 0 : sum/ amount);
        }
    }
}