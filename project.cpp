#include <iostream>
#include <string>
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

struct maxHeap{
    int id;
    int priority;

    maxHeap(int Id,int Priority){
        id=Id;
        priority=Priority;
    }
    
};
int main(){

}
