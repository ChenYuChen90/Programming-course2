#include<iostream>
#include<algorithm>
using namespace std;

class MAX_HEAP{
public:
    MAX_HEAP():Count(0){}
    virtual ~MAX_HEAP() {}
    virtual void PUSH(const int &) = 0;
    virtual int MAX() const = 0;
    virtual int POP() = 0;
    int count() const { return Count; }// An empty tree has height of 0. A tree with only root node has height of 1.

protected:
    int Count;
};

class Array_MAX_HEAP : public MAX_HEAP{
public:
    Array_MAX_HEAP();
    virtual ~Array_MAX_HEAP() {}
    virtual void PUSH(const int &) override; //root node is stored at index 1.
    virtual int MAX() const override;
    virtual int POP() override;

private:
    int array[1025];
};

class ListNode{
    friend class List_MAX_HEAP; //make List_BST a friend

public:
    ListNode(const int &info):value( info ),left( NULL ),right( NULL ), parent(NULL) //constructor
    {
    }//end ListNode constructor

private:
    int value;
    ListNode *left;
    ListNode *right;
    ListNode *parent;
};//end class ListNode

class List_MAX_HEAP : public MAX_HEAP{
public:
    List_MAX_HEAP();
    virtual ~List_MAX_HEAP()
    {
        deleteTree(root);
    }
    virtual void PUSH(const int &) override;
    virtual int MAX() const override;
    virtual int POP() override;

private:
    ListNode *root;
    /* clean a tree.*/
    void deleteTree(ListNode *root);
    ListNode* findparent(int cnt, ListNode* root){//find the parent of node cnt
        if(cnt <= 1) return root;
        string s = "";
        while(cnt !=0){
            s += cnt%2 +'0';
            cnt/=2;
        }ListNode *now = root;
        for(int i = 1; i < s.size()-1; i++){
            if(s[i] == '0'){
                now = now->left;
            }else{
                now = now->right;
            }
        }return now;
    }
};

Array_MAX_HEAP::Array_MAX_HEAP(){
    Count = 0;
}
void Array_MAX_HEAP::PUSH(const int & a) {
    this->Count += 1;
    this->array[this->Count] = a;

    for(int i = this->Count; i/2 >= 1 && array[i] > array[i/2]; i /= 2){
        swap(array[i], array[i/2]);
    }
}
int Array_MAX_HEAP::MAX() const {
    if(Count == 0) return -1;
    else return array[1];
}
int Array_MAX_HEAP::POP() {
    if(Count == 0) return -1;
    
    int max = array[1];
    int n = 1;
    array[n] = array[Count--];
    while((2*n <= Count && array[n] < array[2*n]) || (2*n+1 <= Count && array[n] < array[2*n+1])){
        if(array[2*n+1] < array[2*n] || 2*n+1 > Count){
            swap(array[n], array[2*n]);
            n = n*2;
        } else {
            swap(array[n], array[2*n+1]);
            n = n*2 + 1;
        }
    }
    return max;
}

List_MAX_HEAP::List_MAX_HEAP(){
    root = NULL;
}
void List_MAX_HEAP::PUSH(const int &a){
    Count++;
    ListNode *curr = new ListNode(a);
    if(Count == 1) {
        root = curr;
        root->parent = root;
    } else {
        ListNode *par = findparent(Count, root);
        if(par->left == NULL) par->left = curr;
        else if(par->right == NULL) par->right = curr;
        curr->parent = par;
    }

    while(curr->value > curr->parent->value) {
        swap(curr->value, curr->parent->value);
        curr = curr->parent;
    }
}
int List_MAX_HEAP::MAX() const{
    if(Count >= 1) return root->value;
    else return -1;
}
int List_MAX_HEAP::POP(){
    int max = -1;
    if(Count > 1) {
        max = root->value;

        ListNode *lastpar = findparent(Count, root);
        if(lastpar->right != NULL) {
            root->value = lastpar->right->value;  
            lastpar->right = NULL;
        } else {
            root->value = lastpar->left->value;
            lastpar->left = NULL;
        }
        Count--;

        ListNode *curr = root;
        // 注意要先檢查右邊再看左邊
        while((curr->left != NULL && curr->value < curr->left->value) || (curr->right != NULL && curr->value < curr->right->value)) {
            if(curr->right != NULL && curr->right->value >= curr->left->value){
                swap(curr->value, curr->right->value);
                curr = curr->right;
            } else {
                swap(curr->value, curr->left->value);
                curr = curr->left;
            }
        }
    } else if (Count == 1) {
        max = root->value;
        root = NULL;
        Count--;
    }
    return max;
} 
void List_MAX_HEAP::deleteTree(ListNode *root){
    if(root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main(){
    int n, a;
    Array_MAX_HEAP A_heap;
    List_MAX_HEAP B_heap;
    string s;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> s;
        if(s == "A_push"){
            cin >> a;
            A_heap.PUSH(a);
        }else if(s == "L_push"){
            cin >> a;
            B_heap.PUSH(a);
        }
        else if(s == "max"){
            cout << A_heap.MAX() << "\n";
            cout << B_heap.MAX() << "\n";
        }
        else if(s == "A_pop"){
            cout << A_heap.POP() << "\n";
        }
        else if(s == "L_pop"){
            cout << B_heap.POP() << "\n";
        }
        else if(s == "size"){
            cout << A_heap.count() << "\n";
            cout << B_heap.count() << "\n";
        }
    }
}
