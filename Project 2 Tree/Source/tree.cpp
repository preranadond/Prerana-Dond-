//Original code
#include <iostream>

using namespace std;
struct Node {
    int data;
    Node *left, *right;
    bool lthread; // true if left points to inorder predecessor, false if it's a child pointer
    bool rthread; // true if right points to inorder successor, false if it's a child pointer
};

Node* insert(Node* root, int key) {
    // 1. Create the new node
    Node* tmp = new Node();
    tmp->data = key;
    tmp->left = nullptr;
    tmp->right = nullptr;
    tmp->lthread = true; // Initially, pointers act as threads
    tmp->rthread = true;

    if (root == nullptr) {
        root = tmp;
        return root;
    }

    Node* ptr = root;
    Node* parent = nullptr;

    while (ptr != nullptr) {
        if (key == ptr->data) {
            cout << "Duplicate key " << key << " ignored.\n";
            delete tmp; // Clean up allocated memory
            return root;
        }

        parent = ptr; // Track parent node

        if (key < ptr->data) {
            if (!ptr->lthread) {
                ptr = ptr->left;
            } else {
                break;
            }
        } else {
            if (!ptr->rthread) {
                ptr = ptr->right;
            } else {
                break;
            }
        }
    }
    if (key < parent->data) {
        // Insert as left child
        tmp->left = parent->left;   // Predecessor of tmp is parent's old predecessor
        tmp->right = parent;        // Successor of tmp is parent itself
        parent->lthread = false;    // Parent's left link is no longer a thread
        parent->left = tmp;         // Point parent's left child to new node
    } else {
        // Insert as right child
        tmp->left = parent;         // Predecessor of tmp is parent itself
        tmp->right = parent->right; // Successor of tmp is parent's old successor
        parent->rthread = false;    // Parent's right link is no longer a thread
        parent->right = tmp;        // Point parent's right child to new node
    }

    return root;
}

Node* inorderSuccessor(Node* ptr) {
    // If rthread is true, the right pointer directly tracks the successor
    if (ptr->rthread) {
        return ptr->right;
    }
    ptr = ptr->right;
    while (!ptr->lthread) {
        ptr = ptr->left;
    }
    return ptr;
}

void printInorder(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty.\n";
        return;
    }

    Node* ptr = root;
    while (!ptr->lthread) {
        ptr = ptr->left;
    }

    while (ptr != nullptr) {
        cout << ptr->data << " ";
        ptr = inorderSuccessor(ptr);
    }
    cout << "\n";
}

int main() {
    Node* root = nullptr;

    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 25);
    root = insert(root, 35);

    cout << "Inorder Traversal of the Threaded BST: ";
    printInorder(root);

    return 0;
}

//Modified code:
#include <iostream>
#include <string>

using namespace std;

struct Node {
    int data;
    Node *left, *right;
    bool lthread; // true if left points to inorder predecessor, false if child
    bool rthread; // true if right points to inorder successor, false if child
};

string nodeVal(Node* n) {
    if (n == nullptr) return "NULL";
    return to_string(n->data);
}

Node* getMinNode(Node* root) {
    if (root == nullptr) return nullptr;
    Node* ptr = root;
    while (!ptr->lthread) {
        ptr = ptr->left;
    }
    return ptr;
}

Node* getMaxNode(Node* root) {
    if (root == nullptr) return nullptr;
    Node* ptr = root;
    while (!ptr->rthread) {
        ptr = ptr->right;
    }
    return ptr;
}
Node* inorderSuccessor(Node* ptr) {
    if (ptr == nullptr) return nullptr;
    if (ptr->rthread) {
        return ptr->right;
    }
    ptr = ptr->right;
    while (!ptr->lthread) {
        ptr = ptr->left;
    }
    return ptr;
}

Node* inorderPredecessor(Node* ptr) {
    if (ptr == nullptr) return nullptr;
    if (ptr->lthread) {
        return ptr->left;
    }
    ptr = ptr->left;
    while (!ptr->rthread) {
        ptr = ptr->right;
    }
    return ptr;
}

void verifyThreads(Node* target, string contextMessage) {
    if (target == nullptr) return;
    
    cout << "   [Verification - " << contextMessage << "]:\n";
   
    Node* pred = inorderPredecessor(target);
    Node* succ = inorderSuccessor(target);
    
    cout << "     * Node (" << target->data << ") Predecessor -> " << nodeVal(pred) << "\n";
    cout << "     * Node (" << target->data << ") Successor   -> " << nodeVal(succ) << "\n";
  
    if (target->lthread) {
        cout << "     * Verified: Left link is a thread pointing to Predecessor (" << nodeVal(target->left) << ")\n";
    }
    if (target->rthread) {
        cout << "     * Verified: Right link is a thread pointing to Successor (" << nodeVal(target->right) << ")\n";
    }
}
Node* insertAndTrack(Node* root, int key) {
    cout << "\n=========================================\n";
    cout << "INSERTING KEY: " << key << "\n";
    cout << "=========================================\n";

    Node* tmp = new Node();
    tmp->data = key;
    tmp->left = nullptr;
    tmp->right = nullptr;
    tmp->lthread = true;
    tmp->rthread = true;

    if (root == nullptr) {
        root = tmp;
        cout << "Tree was empty. Node " << key << " set as Root.\n";
        verifyThreads(tmp, "Root Creation");
        return root;
    }

    Node* ptr = root;
    Node* parent = nullptr;

    while (ptr != nullptr) {
        if (key == ptr->data) {
            cout << "Warning: Duplicate key " << key << " ignored.\n";
            delete tmp;
            return root;
        }

        parent = ptr;

        if (key < ptr->data) {
            if (!ptr->lthread) {
                ptr = ptr->left;
            } else {
                break;
            }
        } else {
            if (!ptr->rthread) {
                ptr = ptr->right;
            } else {
                break;
            }
        }
    }

    if (key < parent->data) {
        tmp->left = parent->left;   
        tmp->right = parent;        
        parent->lthread = false;    
        parent->left = tmp;         

        cout << "Attached " << key << " as LEFT child of " << parent->data << "\n";
        cout << "Thread Updates:\n";
        cout << " -> " << key << "->left  thread now points to Predecessor: " << nodeVal(tmp->left) << "\n";
        cout << " -> " << key << "->right thread now points to Successor:   " << nodeVal(tmp->right) << "\n";
        cout << " -> Parent " << parent->data << "->lthread set to FALSE (now structural link)\n";
    } else {
        tmp->left = parent;         
        tmp->right = parent->right; 
        parent->rthread = false;    
        parent->right = tmp;        

        cout << "Attached " << key << " as RIGHT child of " << parent->data << "\n";
        cout << "Thread Updates:\n";
        cout << " -> " << key << "->left  thread now points to Predecessor: " << nodeVal(tmp->left) << "\n";
        cout << " -> " << key << "->right thread now points to Successor:   " << nodeVal(tmp->right) << "\n";
        cout << " -> Parent " << parent->data << "->rthread set to FALSE (now structural link)\n";
    }

    verifyThreads(tmp, "Newly Inserted Node Validation");
    verifyThreads(parent, "Parent Node Link Validation");

    return root;
}
void printInorder(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty.\n";
        return;
    }
    Node* ptr = getMinNode(root);
    cout << "Current Inorder Sequence: ";
    while (ptr != nullptr) {
        cout << ptr->data << " ";
        ptr = inorderSuccessor(ptr);
    }
    cout << "\n";
}

int main() {
    Node* root = nullptr;

    root = insertAndTrack(root, 20);
    root = insertAndTrack(root, 10);
    root = insertAndTrack(root, 30);
    
    cout << "\n--- Base Tree Status ---\n";
    printInorder(root);

    // 2. Insert values violating bounds (Extreme Minimalist and Maximalist tests)
    root = insertAndTrack(root, 2); 
    
    root = insertAndTrack(root, 45); 

    cout << "\n--- Final Tree Status ---\n";
    printInorder(root);

    return 0;
}
