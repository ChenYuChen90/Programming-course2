#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
typedef struct _Node{
    int number;
    struct _Node* next;
    struct _Node* prev;
}Node;

Node *head, *start, *curr, *end, *temp;;
Node* create_node(int num){
    Node* cur = (Node*)malloc(sizeof(Node));
    if(num == 1) {
        cur->number = num;
        cur->next = cur->prev = cur;
    } else {
        cur->number = num;
        cur->next = NULL;
        cur->prev = NULL;
    }
    return cur;
}
Node* createList(int n){
    curr = start = create_node(1);
    for(int i = 2; i <= n; i++){
        curr->next = create_node(i);
        curr->next->prev = curr;
        curr = curr->next;
    }
    curr->next = start;
    curr->next->prev = curr;
    curr = curr->next;
}
void solveJosephus(int n, int m){
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
            k = k % (n-j) == 0? n-j : k % (n-j);
            for(int i = 0; i < k; i++) curr = curr->next;
            temp = curr->prev;
            printf("%d\n", temp->number);
            curr->prev = temp->prev;
            temp->prev->next = curr;
        } else if(k % 2 == 0){
            k = k % (n-j) == 0? n-j : k % (n-j);
            for(int i = 0; i < k; i++) curr = curr->prev;
            temp = curr->next;
            printf("%d\n", temp->number);
            curr->next = temp->next;
            temp->next->prev = curr;
        }
        
    }
}
#endif