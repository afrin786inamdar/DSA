#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Node structure for Expression Tree
struct Node {
    string data;
    Node* left;
    Node* right;
    
    Node(string value) {
        data = value;
        left = right = nullptr;
    }
};

// Custom Stack class to store nodes
struct Stack {
    Node** arr;
    int top;
    int capacity;
    
    Stack(int size) {
        capacity = size;
        arr = new Node*[capacity];
        top = -1;
    }
    
    bool isEmpty() {
        return top == -1;
    }
    
    void push(Node* node) {
        if (top < capacity - 1) {
            arr[++top] = node;
        }
    }
    
    Node* pop() {
        if (!isEmpty()) {
            return arr[top--];
        }
        return nullptr;
    }
    
    Node* peek() {
        if (!isEmpty()) {
            return arr[top];
        }
        return nullptr;
    }
    
    ~Stack() {
        delete[] arr;
    }
};

// Function to check if a character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to construct the expression tree from a prefix expression
Node* constructTree(const string& prefix) {
    Stack stack(prefix.length());
    
    // Process the prefix expression from right to left
    for (int i = prefix.length() - 1; i >= 0; i--) {
        char c = prefix[i];
        
        // If the character is an operand (a letter or number), create a node and push it to the stack
        if (isalnum(c)) {
            Node* node = new Node(string(1, c)); // Create node with operand
            stack.push(node);
        }
        // If the character is an operator, pop two nodes from the stack, create a new node and push it back
        else if (isOperator(c)) {
            Node* node = new Node(string(1, c)); // Create node with operator
            
            // Pop two nodes for left and right subtrees
            node->left = stack.pop();
            node->right = stack.pop();
            
            // Push the newly created node back to the stack
            stack.push(node);
        }
    }
    
    // The last element in the stack is the root of the expression tree
    return stack.pop();
}

// Non-recursive post-order traversal using custom stacks
void postOrderTraversal(Node* root) {
    if (root == nullptr) return;
    
    Stack s1(100), s2(100);
    
    // Push the root to the first stack
    s1.push(root);
    
    // Run the loop until the first stack is empty
    while (!s1.isEmpty()) {
        Node* curr = s1.pop();
        
        // Push the node to the second stack (reverse of preorder)
        s2.push(curr);
        
        // Push left and right children to the first stack
        if (curr->left != nullptr) {
            s1.push(curr->left);
        }
        if (curr->right != nullptr) {
            s1.push(curr->right);
        }
    }
    
    // Now print the nodes from the second stack (postorder)
    while (!s2.isEmpty()) {
        cout << s2.pop()->data << " ";
    }
}

// Function to delete the entire tree (post-order deletion)
void deleteTree(Node* root) {
    if (root == nullptr) return;
    
    // First delete left and right subtrees
    deleteTree(root->left);
    deleteTree(root->right);
    
    // Then delete the current node
    delete root;
}

int main() {
    string prefix = "+--a*bc/def";
    
    // Construct the expression tree
    Node* root = constructTree(prefix);
    
    // Perform post-order traversal (non-recursive)
    cout << "Post-order Traversal (non-recursive): ";
    postOrderTraversal(root);
    cout << endl;
    
    // Delete the entire tree
    deleteTree(root);
    
    return 0;
}
