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

    bool isEmptyBST(){
        return left==NULL && right==NULL;
    }

    int sizeBST(){
        int count=0;
        if(left!=NULL){
            count+=left->sizeBST();
        }
        if(right!=NULL){
            count+=right->sizeBST();
        }
        return count;
    }

    void insertRequest(int Id,string Name){
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
        if(Id<id){
            if(left!=NULL){
                left->deleteRequest(Id);
            }
        }
        else if(Id>id){
            if(right!=NULL){
                right->deleteRequest(Id);
            }
        }
        else{
            if(left==NULL && right==NULL){
                delete this;
            }
            else if(left==NULL){
                right->id=id;
                right->name=name;
                delete this;
            }

            else if(right==NULL){
                left->id=id;
                left->name=name;
                delete this;
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


    bool isEmptyBST();
    int sizeBST();
    void insertRequest(int Id,string Name);
    void searchRequest(int Id);
    void deleteRequest(int Id);
    void pre_order_print();

};

BST*root=NULL;

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

    maxHeap(int Id,int Priority){
        id=Id;
        priority=Priority;
    }

    bool isEmptyHeap();
    int sizeMaxHeap();
    void insertHeap(int Id, int Priority);
    void deleteMaxHeap();
    void processHighestPriorityRequest();
    void levelOrder_printMaxHeap();
    void maxHeapify(int index);
    void increasePriority(int Id, int newPriority);

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
int main(){

}
