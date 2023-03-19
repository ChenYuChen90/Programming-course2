#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *prev;
    struct node *next;
}node;

node* create_node(int num){
    node* cur = (node*)malloc(sizeof(node));
    if(num == 1) {
        cur->data = num;
        cur->next = cur->prev = cur;
    } else {
        cur->data = num;
        cur->next = NULL;
        cur->prev = NULL;
    }
    return cur;
}

node *start, *curr, *end, *temp;
int main(){
    int n, m; scanf("%d%d", &n, &m);
    
    curr = start = create_node(1);
    for(int i = 2; i <= n; i++){
        curr->next = create_node(i);
        curr->next->prev = curr;
        curr = curr->next;
    }
    curr->next = start;
    curr->next->prev = curr;
    curr = curr->next;

    for(int j = 0; j < m; j++){
        int k; scanf("%d", &k);
        if(j != 0){
            if(k % 2 == 1){
                curr = temp->next;
                free(temp);
            } else if(k % 2 == 0){
                curr = temp->prev;
                free(temp);
            }
        }
        if(k % 2 == 1){
            for(int i = 0; i < k; i++) curr = curr->next;
            temp = curr->prev;
            printf("%d\n", temp->data);
            curr->prev = temp->prev;
            temp->prev->next = curr;
        } else if(k % 2 == 0){
            for(int i = 0; i < k; i++) curr = curr->prev;
            temp = curr->next;
            printf("%d\n", temp->data);
            curr->next = temp->next;
            temp->next->prev = curr;
        }
        
    }
    return 0;
}