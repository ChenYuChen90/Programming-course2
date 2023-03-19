#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int num;
    struct node *next;
}node;

node* create_node(int num){
    node* cur = (node*)malloc(sizeof(node));
    cur->num = num;
    cur->next = NULL;
    return cur;
}

node *start, *curr, *end, *temp, *temp_1;
int main(){
    char type[3];
    int n, m, tmp;
    int idx, add_num, a, b;
    scanf("%d%d", &n, &m);
    
    curr = start = create_node(0);
    for(int i = 0; i < n; i++){
        scanf("%d", &tmp);
        curr = curr->next = create_node(tmp);
    }
    
    while(m--){
        curr = start;
        scanf("%s", &type);
        if(type[0] == 'A'){
            scanf("%d%d", &idx, &add_num);
            for(int i = 0; i < idx; i++){
                curr = curr->next;
            }
            temp = create_node(add_num);
            temp->next = curr->next;
            curr->next = temp;

        } else if(type[0] == 'C') {
            scanf("%d%d", &a, &b);
            for(int i = 0; i < a; i++){
                curr = curr->next;
            }
            temp = curr->next;
            temp_1 = curr;
            curr = temp;
            for(;b-1 > 0; b--) curr = curr->next;
            temp_1->next = curr->next;
            curr->next = start->next;
            start->next = temp;
        }
    }
    curr = start->next;
    while(curr != NULL){
        printf("%d\n", curr->num);
        curr = curr->next;
    }
    return 0;
}