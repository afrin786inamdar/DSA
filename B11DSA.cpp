#include<iostream>
#include<string>
using namespace std;

// Node structure for the BST
struct Node {
    string keyword;
    string meaning;
    Node* left;
    Node* right;
    
    Node(string key, string val) {
        keyword = key;
        meaning = val;
        left = right = nullptr;
    }
};

// Class for Dictionary
class Dictionary {
private:
    Node* root;

    // Utility function for inserting a keyword into BST
    Node* insert(Node* root, string keyword, string meaning) {
        if (root == nullptr) {
            return new Node(keyword, meaning);
        }
        
        if (keyword < root->keyword) {
            root->left = insert(root->left, keyword, meaning);
        } else if (keyword > root->keyword) {
            root->right = insert(root->right, keyword, meaning);
        }
        
        return root;
    }

    // Utility function for deleting a keyword from BST
    Node* deleteNode(Node* root, string keyword) {
        if (root == nullptr) return root;
        
        // Find the node to delete
        if (keyword < root->keyword) {
            root->left = deleteNode(root->left, keyword);
        } else if (keyword > root->keyword) {
            root->right = deleteNode(root->right, keyword);
        } else {
            // Node to be deleted found
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            
            // Node has two children, find the inorder successor
            Node* temp = minValueNode(root->right);
            root->keyword = temp->keyword;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->keyword);
        }
        
        return root;
    }

    // Find the node with the minimum keyword value
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Utility function to search a keyword in BST
    Node* search(Node* root, string keyword) {
        if (root == nullptr || root->keyword == keyword) {
            return root;
        }
        
        if (keyword < root->keyword) {
            return search(root->left, keyword);
        }
        
        return search(root->right, keyword);
    }

    // Utility function to update meaning of a keyword
    Node* updateMeaning(Node* root, string keyword, string newMeaning) {
        if (root == nullptr) return root;
        
        if (keyword < root->keyword) {
            root->left = updateMeaning(root->left, keyword, newMeaning);
        } else if (keyword > root->keyword) {
            root->right = updateMeaning(root->right, keyword, newMeaning);
        } else {
            root->meaning = newMeaning;
        }
        
        return root;
    }

    // Function to perform inorder traversal for displaying dictionary in ascending order
    void inorder(Node* root) {
        if (root != nullptr) {
            inorder(root->left);
            cout << "Keyword: " << root->keyword << " -> Meaning: " << root->meaning << endl;
            inorder(root->right);
        }
    }

    // Function to perform reverse inorder traversal for displaying dictionary in descending order
    void reverseInorder(Node* root) {
        if (root != nullptr) {
            reverseInorder(root->right);
            cout << "Keyword: " << root->keyword << " -> Meaning: " << root->meaning << endl;
            reverseInorder(root->left);
        }
    }

    // Function to calculate maximum comparisons for finding a keyword
    int maxComparisons(Node* root) {
        if (root == nullptr) {
            return 0;
        }
        int leftComparisons = maxComparisons(root->left);
        int rightComparisons = maxComparisons(root->right);
        
        return max(leftComparisons, rightComparisons) + 1;
    }

public:
    Dictionary() {
        root = nullptr;
    }

    // Public function to add a new keyword
    void addKeyword(string keyword, string meaning) {
        root = insert(root, keyword, meaning);
    }

    // Public function to delete a keyword
    void deleteKeyword(string keyword) {
        root = deleteNode(root, keyword);
    }

    // Public function to update the meaning of a keyword
    void updateKeywordMeaning(string keyword, string newMeaning) {
        root = updateMeaning(root, keyword, newMeaning);
    }

    // Public function to display dictionary in ascending order
    void displayAscending() {
        inorder(root);
    }

    // Public function to display dictionary in descending order
    void displayDescending() {
        reverseInorder(root);
    }

    // Public function to search a keyword
    bool searchKeyword(string keyword) {
        Node* result = search(root, keyword);
        if (result != nullptr) {
            cout << "Found: " << result->keyword << " -> " << result->meaning << endl;
            return true;
        } else {
            cout << "Keyword not found!" << endl;
            return false;
        }
    }

    // Public function to calculate maximum comparisons
    void showMaxComparisons() {
        int comparisons = maxComparisons(root);
        cout << "Maximum comparisons required for search: " << comparisons << endl;
    }
};

int main() {
    Dictionary dict;
    
    dict.addKeyword("apple", "A fruit");
    dict.addKeyword("banana", "A yellow fruit");
    dict.addKeyword("cherry", "A small red fruit");
    
    cout << "Dictionary in Ascending Order:" << endl;
    dict.displayAscending();
    
    cout << "\nDictionary in Descending Order:" << endl;
    dict.displayDescending();
    
    cout << "\nSearching for 'banana':" << endl;
    dict.searchKeyword("banana");
    
    cout << "\nUpdating 'apple' meaning:" << endl;
    dict.updateKeywordMeaning("apple", "A sweet red or green fruit");
    dict.displayAscending();
    
    cout << "\nDeleting 'cherry':" << endl;
    dict.deleteKeyword("cherry");
    dict.displayAscending();
    
    dict.showMaxComparisons();
    
    return 0;
}

