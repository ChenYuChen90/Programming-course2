//11339.c

#ifndef NODE
#define NODE
#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>

typedef struct node
{
	struct node *next;
	struct node *prev;
	unsigned short val;
} Node;

Node* create_node(int n){
    Node *node = (Node*)calloc(1, sizeof(Node));
    node->val = n;
    return node;
}

void do_I(Node **head,size_t pos,unsigned short val){
    Node *tmp = create_node(val), *curr = *head;
    if(*head == NULL || pos == 0){
        if(*head != NULL) tmp->next = *head, (*head)->prev = tmp;
        *head = tmp;
    } else {
        for(size_t i = 1; i < pos; i++){
            if(curr->next == NULL) break;   // 要注意
            else curr = curr->next;
        }
        tmp->next = curr->next;
        curr->next = tmp;
        tmp->prev = curr;
        if(tmp->next != NULL) tmp->next->prev = tmp;
    }
}
void do_E(Node **head,size_t begin_pos,size_t end_pos){
    if(*head == NULL) return;
    Node *curr = *head, *left = NULL, *tmp;
    if(begin_pos == end_pos) end_pos++;         // 注意
    for(size_t i = 0; i < end_pos; i++){
        if(i == begin_pos) left = curr;
        if(curr->next == NULL){
            if(left == NULL) return;
            else break;
        }
        if(i+1 < end_pos) curr = curr->next;
    }
    if(*head == left){
        *head = curr->next;
        if(*head != NULL) (*head)->prev = NULL;
    } else {
        left->prev->next = curr->next;
        if(curr->next != NULL) curr->next->prev = left->prev;
    }
    curr->next = NULL;  //把要remove的那段提出來
    while(left != NULL){
        tmp = left;
        left = left->next;
        free(tmp);
    }
}
void do_P(Node  *head,size_t pos){
    if(head == NULL) return;
    for(size_t i = 0; i < pos; i++){
        if(head->next == NULL) break;
        head = head->next;
    }
    printf("%d ", head->val);
}
void do_R(Node **head,unsigned short val){
    Node *curr = (*head), *tmp;
    while(curr != NULL){
        if(curr->val == val){
            if(curr == (*head)){    //要記的考慮
                *head = curr->next;
                if(*head != NULL) (*head)->prev = NULL;
            } else {
                curr->prev->next = curr->next;
                if(curr->next != NULL) curr->next->prev = curr->prev;
            }
            tmp = curr;
            curr = curr->next;
            free(tmp);
        } else {
            curr = curr->next;
        }
    }
}
void do_S(Node  *head){
    while(head != NULL){
        printf("%d ", head->val);
        head = head->next;
    }
}

#endif

int main(void)
{
	Node *head=NULL;
	size_t N;
	scanf("%zu",&N);
	while(N--)
	{
		char op;
		unsigned short val;
		size_t pos,begin_pos,end_pos;
		scanf(" %c",&op);
		switch(op)
		{
		case 'I':
			scanf("%zu %hu",&pos,&val);
			do_I(&head,pos,val);
			break;
		case 'E':
			scanf("%zu %zu",&begin_pos,&end_pos);
			do_E(&head,begin_pos,end_pos);
			break;
		case 'P':
			scanf("%zu",&pos);
			do_P(head,pos);
			break;
		case 'R':
			scanf("%hu",&val);
			do_R(&head,val);
			break;
		case 'S':
			do_S(head);
			break;
		}
	}
            return 0;
}