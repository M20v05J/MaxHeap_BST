#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct BST{
    int id;
    string name;
    BST*left;
    BST*right;

    BST(int Id,string Name){
        id=Id;
        name=Name;
        left=NULL;
        right=NULL;
    }

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
            count+=left->sizeBST();
        }
        if(right!=NULL){
            count+=right->sizeBST();
        }
        return count;
    }

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
                BST*temp=right;
                id=temp->id;
                name=temp->name;
                left=temp->left;
                right=temp->right;
                delete temp;
            }
            else if(right==NULL){
                BST*temp=left;
                id=temp->id;
                name=temp->name;
                left=temp->left;
                right=temp->right;
                delete temp;
            }
            else{
                BST*temp=right;
                while(temp->left!=NULL){
                    temp=temp->left;
                }
                id=temp->id;
                name=temp->name;
                delete temp;
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
        cout<<"Id: "<<id<<" Name: "<<name<<endl;
        if(left!=NULL){
            left->pre_order_print();
        }
        if(right!=NULL){
            right->pre_order_print();
        }
    }

    // bool isEmptyBST();
    // int sizeBST();
    // void insertRequest(int Id,string Name);
    // void searchRequest(int Id);
    // void deleteRequest(int Id);
    // void pre_order_print();

};

//BST*root=NULL;

struct heapNode{
    int id;
    int priority;

    heapNode(int Id, int Priority){
        this->id=Id;
        this->priority=Priority;
    }
};
struct maxHeap{
    int id;
    int priority;
    vector<heapNode>child;

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

    void maxHeapify(int index){
        int left = index*2+1;
        int right = index*2+2;
        int largest = index;
        if(left < child.size() && child[left].priority > child[largest].priority){
            largest = left;
        }
        if(right < child.size() && child[right].priority > child[largest].priority){
            largest = right;
        }
        if(largest != index){
            heapNode temp = child[index];
            child[index] = child[largest];
            child[largest] = temp;
            maxHeapify(largest);
        }

    }
    void increasePriority(int Id, int newPriority){
        for(int i=0;i<child.size();i++){
            if(child[i].id==Id){
                child[i].priority=newPriority;
                maxHeapify(i);
            }
        }
    }

    void insertHeap(int Id, int Priority){
        child.push_back(heapNode(Id,Priority));
        int index=child.size()-1;
        while(index>0 && child[index].priority>child[(index-1)/2].priority){
            heapNode temp=child[index];
            child[index]=child[(index-1)/2];
            child[(index-1)/2]=temp;
            index=(index-1)/2;
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
        
        int indexToDelete = -1;
        for (int i = 0; i < child.size(); ++i) {
            if (child[i].id == Id) {
                indexToDelete = i;
                break;
            }
        }
        
        if (indexToDelete == -1) {
            return;
        }
        
        child[indexToDelete] = child[child.size() - 1];
        child.pop_back();
        if (indexToDelete < child.size()) {
            maxHeapify(indexToDelete);
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

    void levelOrder_printMaxHeap(){
        for(int i=0;i<child.size();i++){
            cout<<"Id: "<<child[i].id<<" Priority: "<<child[i].priority<<endl;
        }
    }

    
};

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

    cout<<"-----------------------------------------------------------------------"<<endl;
    merge m = merge(1,"A",1);
    m.insert_both(2,"B",2);
    m.insert_both(4,"D",4);
    m.insert_both(9,"G",5);
    m.insert_both(3,"C",3);
    m.insert_both(5,"F",6);
    m.print_both();
    cout<<"-----------------------------------------------------------------------"<<endl;
    m.delete_both(5);
    cout<<"-----------------------------------------------------------------------"<<endl;
    m.ProcessHighestPriorityRequest();
    return 0;
}
