#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
    int number;
    struct _Node* next;
    struct _Node* prev;
}Node;

Node *head;

Node* create_node(int num){
    Node* cur = (Node*)calloc(1, sizeof(Node));
    cur->number = num;
    return cur;
}
Node* createList(int n){
    Node *start, *curr, *temp;
    start = curr = create_node(1);
    for(int i = 2; i <= n; i++){
        temp = create_node(i);
        curr->next = temp;
        temp->prev = curr;
        curr = temp;
    }
    curr->next = start;
    start->prev = curr;
    return start;
}
void solveJosephus(int n, int m){
    int k;
    Node *curr = head, *tmp;
    scanf("%d", &k);
    for(int i = 0; i < m; i++){
        if(k % 2){
            k = k % (n-i) == 0? n-i : k % (n-i);
            while(--k > 0) curr = curr->next;
        } else {
            k = k % (n-i) == 0 ? n-i : k % (n-i);
            while(--k > 0) curr = curr->prev;
        }
        // 記得在這邊設 tmp = curr
        tmp = curr;
        if(i < m-1){
            scanf("%d", &k);
            if(k % 2) curr = curr->next;
            else curr = curr->prev;
        }
        printf("%d\n", tmp->number);
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        free(tmp);
    }
}
#endif