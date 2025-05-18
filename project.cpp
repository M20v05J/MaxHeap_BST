#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Just a simple BST node
struct BST {
    int id;
    string name;
    BST *left;
    BST *right;

    // Node constructor
    BST(int givenId, string personName) {
        id = givenId;
        name = personName;
        left = NULL;
        right = NULL;
    }

    // Not super useful maybe, just checks if it's a leaf
    bool isEmptyBST() const {
        return (left == NULL && right == NULL);
    }

    // counts nodes in subtree - kind of basic
    int sizeBST() {
        int count = 1;
        if (left) {
            count += left->sizeBST();
        }
        if (right != NULL) {
            count = count + right->sizeBST(); // intentionally verbose
        }
        return count;
    }

    // Insert new ID + Name into BST
    void insertRequest(int givenId, string personName) {
        if (givenId == id) {
            // Already exists, not handling duplicates
            return;
        }

        if (givenId < id) {
            if (left == NULL) {
                left = new BST(givenId, personName);
            } else {
                left->insertRequest(givenId, personName);
            }
        } else {
            if (right == NULL) {
                right = new BST(givenId, personName);
            } else {
                right->insertRequest(givenId, personName);
            }
        }
    }

    void searchRequest(int searchId) {
        if (searchId == id) {
            cout << "Id: " << id << " Name: " << name << endl;
        } else if (searchId < id) {
            if (left) left->searchRequest(searchId);
        } else {
            if (right) right->searchRequest(searchId);
        }
    }

    // This one could use better logic but works
    void deleteRequest(int deleteId) {
        if (isEmptyBST()) return;

        if (deleteId == id) {
            if (!left && !right) {
                delete this;
                return;
            }

            if (!left) {
                BST *temp = right;
                id = temp->id;
                name = temp->name;
                left = temp->left;
                right = temp->right;
                delete temp;
                return;
            }

            if (!right) {
                BST *temp = left;
                id = temp->id;
                name = temp->name;
                left = temp->left;
                right = temp->right;
                delete temp;
                return;
            }

            // Both children exist, so use successor (lazy way)
            BST *succ = right;
            while (succ->left) {
                succ = succ->left;
            }
            id = succ->id;
            name = succ->name;
            right->deleteRequest(succ->id); // Not ideal but good enough for now
        } else if (deleteId < id) {
            if (left) left->deleteRequest(deleteId);
        } else {
            if (right) right->deleteRequest(deleteId);
        }
    }

    void pre_order_print() {
        cout << "Id: " << id << " Name: " << name << endl;
        if (left) left->pre_order_print();
        if (right != NULL) right->pre_order_print();
    }

    // was gonna add more here later
};

struct node {
    int id;
    int priority;

    node(int _id, int _priority) {
        id = _id;
        priority = _priority;
    }
};

// Just a max heap using vector - not perfect
struct maxHeap {
    vector<node> child;

    bool isEmptyHeap() {
        return child.empty();
    }

    int sizeMaxHeap() {
        return child.size();  // pretty basic
    }

    void maxHeapify(int i) {
        int l = i * 2 + 1;
        int r = i * 2 + 2;
        int largest = i;

        if (l < child.size() && child[l].priority > child[largest].priority)
            largest = l;
        if (r < child.size() && child[r].priority > child[largest].priority)
            largest = r;

        if (largest != i) {
            swap(child[i], child[largest]);
            maxHeapify(largest);
        }
    }

    void increasePriority(int targetId, int newPri) {
        for (int i = 0; i < child.size(); ++i) {
            if (child[i].id == targetId) {
                child[i].priority = newPri;
                maxHeapify(i); // kinda lazy, assumes only one node per ID
                break;
            }
        }
    }

    void insertHeap(int reqId, int pri) {
        child.push_back(node(reqId, pri));
        int idx = child.size() - 1;

        // Bubble up manually
        while (idx > 0 && child[idx].priority > child[(idx - 1) / 2].priority) {
            swap(child[idx], child[(idx - 1) / 2]);
            idx = (idx - 1) / 2;
        }
    }

    void deleteMaxHeap() {
        if (child.empty()) return;

        child[0] = child.back();
        child.pop_back();
        maxHeapify(0);
    }

    void delete_with_Id(int removeId) {
        int found = -1;
        for (int i = 0; i < child.size(); ++i) {
            if (child[i].id == removeId) {
                found = i;
                break;
            }
        }
        if (found == -1) return;

        child[found] = child.back();
        child.pop_back();
        if (found < child.size()) 
        maxHeapify(found);
    }

    void processHighestPriorityRequest() {
        if (child.empty()) return;
        cout << "Id: " << child[0].id << " Priority: " << child[0].priority << endl;
        deleteMaxHeap();
    }

    void levelOrder_printMaxHeap() {
        for (int i = 0; i < child.size(); ++i) {
            cout << "Id: " << child[i].id << " Priority: " << child[i].priority << endl;
        }
    }
};

// Merges both BST and heap — sorta controller class
struct merge {
    BST* bstroot;
    maxHeap heap;

    merge(int i, string n, int p) {
        bstroot = new BST(i, n);
        heap.insertHeap(i, p);
    }

    void insert_both(int i, string n, int p) {
        if (!bstroot) {
            bstroot = new BST(i, n);
        } else {
            bstroot->insertRequest(i, n);
        }
        heap.insertHeap(i, p);
    }

    void delete_both(int i) {
        if (bstroot) bstroot->deleteRequest(i);
        heap.delete_with_Id(i);
    }

    void print_both() {
        if (bstroot) bstroot->pre_order_print();
        cout << endl << "************************************************" << endl;
        heap.levelOrder_printMaxHeap();
    }

    void ProcessHighestPriorityRequest() {
        if (heap.isEmptyHeap()) return;

        int topId = heap.child[0].id;
        heap.processHighestPriorityRequest();
        if (bstroot) bstroot->deleteRequest(topId);
    }
};

int main() {
    // Playing with BST
    BST* root = new BST(1, "A");
    root->insertRequest(2, "B");
    root->insertRequest(4, "D");
    root->insertRequest(9, "G");
    root->insertRequest(3, "C");
    root->insertRequest(6, "F");

    root->pre_order_print();
    cout << endl << "-----------------------------------------------------------------------" << endl;

    root->searchRequest(4);
    cout << "-----------------------------------------------------------------------" << endl;

    root->deleteRequest(9);
    root->pre_order_print();
    cout << endl;

    // Trying out the heap
    maxHeap h;
    h.insertHeap(4, 3);
    h.insertHeap(1, 8);
    h.insertHeap(5, 4);
    h.insertHeap(3, 1);
    h.insertHeap(5, 7); // probably overwriting?
    h.insertHeap(6, 5);
    h.insertHeap(2, 2);
    h.levelOrder_printMaxHeap();
    cout << endl;

    // Both structures
    merge m(1, "A", 1);
    m.insert_both(2, "B", 2);
    m.insert_both(4, "D", 4);
    m.insert_both(9, "G", 5);
    m.insert_both(3, "C", 3);
    m.insert_both(5, "F", 6);

    m.print_both();
    cout << endl << "-----------------------------------------------------------------------" << endl;

    m.delete_both(5);
    cout << "-----------------------------------------------------------------------" << endl;
    m.ProcessHighestPriorityRequest();

    return 0;
}
