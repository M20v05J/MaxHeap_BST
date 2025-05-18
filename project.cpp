#include <iostream>
#include <string>
#include <vector>
using namespace std;
//BST class:
struct BST{
    int id;
    string name;
    BST*left;
    BST*right;

    //constructor:
    BST(int Id,string Name){
        id=Id;
        name=Name;
        left=NULL;
        right=NULL;
    }

    //functions: 

    //helping functions:
    bool isEmptyBST() const {
        if(left!=NULL || right!=NULL){
            return false;
        }
        else
        {
            return true;
        }   
    }

    int sizeBST(){
        int count=1;
        if(left!=NULL){
            count=left->sizeBST() + count;
        }
        if(right!=NULL){
            count = count + right->sizeBST();
        }
        return count;
    }

    // khode asl functions:
    void insertRequest(int Id,string Name){
        if(Id==id){
            return;
        } 
        if(Id<id){
            if(left==NULL){
                left=new BST(Id,Name);
            }
            else{
                left->insertRequest(Id,Name);
            }
        }
        else{
            if(right==NULL){
                right=new BST(Id,Name);
            }
            else{
                right->insertRequest(Id,Name);
            }
        }
    }

    void searchRequest(int Id){
        if(Id==id){
            cout<<"Id: "<<id<<" Name: "<<name<<endl;
        }
        else if(Id<id){
            if(left!=NULL){
                left->searchRequest(Id);
            }
        }
        else{
            if(right!=NULL){
                right->searchRequest(Id);
            }
        }
    }

    void deleteRequest(int Id){
        if (this->isEmptyBST())
            return;
        if(Id==id){
            if (left == NULL && right == NULL) {
                delete this;
                return;
            }
            else if(left==NULL){
                BST*bst=right;
                id=bst->id;
                name=bst->name;
                left=bst->left;
                right=bst->right;
                delete bst;
            }
            else if(right==NULL){
                BST*bst=left;
                id=bst->id;
                name=bst->name;
                left=bst->left;
                right=bst->right;
                delete bst;
            }
            else{
                BST*bst=right;
                while(bst->left!=NULL){
                    bst=bst->left;
                }
                id=bst->id;
                name=bst->name;
                delete bst;
            }
        }
        else if(Id<id){
            if(left!=NULL){
                left->deleteRequest(Id);
            }
        }
        else{
            if(right!=NULL){
                right->deleteRequest(Id);
            }
        }
    }

    void pre_order_print(){
        cout<<"Id: "<<id<<" Name: "<<name<<"    ";
        if(left!=NULL){
            left->pre_order_print();
        }
        if(right!=NULL){
            right->pre_order_print();
        }
        cout<<"================================================="<<endl;
    }

    //all of the functions:
    // bool isEmptyBST();
    // int sizeBST();
    // void insertRequest(int Id,string Name);
    // void searchRequest(int Id);
    // void deleteRequest(int Id);
    // void pre_order_print();

};
//node class for heap:
struct node{
    int id;
    int priority;

    node(int Id, int Priority){
        this->id=Id;
        this->priority=Priority;
    }
};
struct maxHeap{
    int id;
    int priority;
    vector<node>child;

    /*maxHeap(int Id,int Priority){
        id=Id;
        priority=Priority;
    }*/

    /* bool isEmptyHeap();
    int sizeMaxHeap();
    void insertHeap(int Id, int Priority);
    void deleteMaxHeap();
    void processHighestPriorityRequest();
    void levelOrder_printMaxHeap();
    void maxHeapify(int index);
    void increasePriority(int Id, int newPriority); */

    //helping :
    bool isEmptyHeap(){
        if (child.size()==0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int sizeMaxHeap(){
        return child.size();
    }

    void maxHeapify(int s){
        int left = s*2+1;
        int right = s*2+2;
        int big = s;
        if(left < child.size() && child[left].priority > child[big].priority){
            big = left;
        }
        if(right < child.size() && child[right].priority > child[big].priority){
            big = right;
        }
        if(big != s){
            node temp = child[s];
            child[s] = child[big];
            child[big] = temp;
            maxHeapify(big);
        }

    }
    //important:
    void increasePriority(int Id, int pri){
        for(int i=0; i<child.size();i++){
            if(child[i].id==Id){
                child[i].priority=pri;
                maxHeapify(i);
            }
        }
    }

    void insertHeap(int Id, int Priority){
        child.push_back(node(Id,Priority));
        int a=child.size()-1;
        while(a>0 && child[a].priority > child[(a-1)/2].priority){
            node temp=child[a];
            child[a]=child[(a-1)/2];
            child[(a-1)/2]=temp;
            a=(a-1)/2;
        }
    }

    void deleteMaxHeap(){
        if(child.size()==0){
            return;
        }
        else{
            child[0]=child[child.size()-1];
            child.pop_back();
            maxHeapify(0);
        }
    }

    void delete_with_Id(int Id) {
        if (child.size() == 0) {
            return;
        }
        
        int inno = -1;
        for (int i = 0; i<child.size(); ++i) {
            if (child[i].id == Id) {
                inno = i;
                break;
            }
        }
        
        if (inno == -1) {
            return;
        }
        
        child[inno] = child[child.size() - 1];
        child.pop_back();
        if (inno<child.size()) {
            maxHeapify(inno);
        }
    }

    void processHighestPriorityRequest(){
        if(child.size()==0){
            return;
        }
        else{
            cout<<"Id: "<<child[0].id<<" Priority: "<<child[0].priority<<endl;
            child[0]=child[child.size()-1];
            child.pop_back();
            maxHeapify(0);
        }
    }

    void levelOrder_printMaxHeap() {
        if (child.size() == 0) {
            return;
        }
        for( unsigned int i=0; i<child.size();i++){
            cout<<"Id: "<<child[i].id<<" Priority: "<<child[i].priority<<"    ";
        }
        cout<<"================================================="<<endl;
    }
    
};

//merge class for merging BST and maxHeap:
struct merge{
    int id;
    string name;
    int priority;
    BST* bstroot;
    maxHeap heap;

    merge(int Id, string Name, int Priority){
        this->id=Id;
        this->name=Name;
        this->priority=Priority;
        bstroot=NULL;
        heap = maxHeap();
    }
    void insert_both(int Id, string Name, int Priority){
        if(bstroot==NULL){
            bstroot=new BST(Id,Name);
        }
        else{
            bstroot->insertRequest(Id, Name);
        }
        bstroot->insertRequest(Id, Name);
        heap.insertHeap(Id, Priority);
    }
    void delete_both(int Id){
        bstroot->deleteRequest(Id);
        heap.delete_with_Id(Id);
    }
    void print_both(){
        bstroot->pre_order_print();
        cout<<"************************************************"<<endl;
        heap.levelOrder_printMaxHeap();
    }
    void ProcessHighestPriorityRequest(){
        if(heap.isEmptyHeap()){
            return;
        }
        else {
            int iid = heap.child[0].id;
            heap.processHighestPriorityRequest();
            heap.maxHeapify(0);
            iid = heap.child[0].id;
            bstroot->deleteRequest(iid);
        }
    }

        /*int iid = heap.child[0].id;
        heap.processHighestPriorityRequest();
        heap.maxHeapify(0);
        int iid = heap.child[0].id;
        bstroot->deleteRequest(iid);*/

};

int main(){
    //some examples for BST:
    BST*root = new BST(1,"A");
    root->insertRequest(2,"B");
    root->insertRequest(4,"D");
    root->insertRequest(9,"G");
    root->insertRequest(3,"C");
    root->insertRequest(6,"F");
    //1 2 4 9 3 6 ->                                                                       
    root->pre_order_print();
    cout<<"-----------------------------------------------------------------------"<<endl;
    root->searchRequest(4);
    cout<<"-----------------------------------------------------------------------"<<endl;
    root->deleteRequest(9);
    root->pre_order_print();

    //examples for maxHeap:
    maxHeap h = maxHeap();
    h.insertHeap(4,3);
    h.insertHeap(1,8);
    h.insertHeap(5,4);
    h.insertHeap(3,1);
    h.insertHeap(5,7);
    h.insertHeap(6,5);
    h.insertHeap(2,2);
    h.levelOrder_printMaxHeap();

    //cout<<"-----------------------------------------------------------------------"<<endl;
    //examples for both:
    merge m = merge(1,"A",1);
    m.insert_both(2,"B",2);
    m.insert_both(4,"D",4);
    m.insert_both(9,"G",5);
    m.insert_both(3,"C",3);
    m.insert_both(5,"F",6);
    m.print_both();
    //cout<<"-----------------------------------------------------------------------"<<endl;
    m.delete_both(5);
    cout<<"-----------------------------------------------------------------------"<<endl;
    m.ProcessHighestPriorityRequest();
    return 0;
}