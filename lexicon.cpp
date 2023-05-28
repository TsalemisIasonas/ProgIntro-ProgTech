#include <iostream>
#include <string>

using namespace std;

class lexicon {
private:
    // Node structure for the lexicon tree
    class Node {
    public:
        string key;
        Node* left;
        Node* right;
        int freq;

        Node(const string& k) {
            key = k;
            left = nullptr;
            right = nullptr;
            freq = 1;
        }
    };

    Node* root;

public:
    // Constructor
    lexicon() {
        root = nullptr;
    }

    // Destructor
    ~lexicon() {
        clear(root);
    }

    // Insert a word into the lexicon tree
    void insert(const string& s) {
        if (root == nullptr) {
            root = new Node(s);
        } else {
            insertRecursive(root, s);
        }
    }

    // Lookup the occurrence frequency of a word in the lexicon tree
    int lookup(const string& s) const {
        Node* node = findNode(root, s);
        return (node != nullptr) ? node->freq : 0;
    }

    // Get the depth of a word in the lexicon tree
    int depth(const string& s) {
        return getDepth(root, s, 1);
    }

    // Replace occurrences of a word with another word in the lexicon tree
    void replace(const string& s1, const string& s2) {
        int frequency = lookup(s1);

        if (frequency == 0) {
            return; // Word s1 does not exist in the tree
        }

        removeNode(root, s1);
        insertOccurrences(s2, frequency);
    }

    // Overloading the << operator to print the lexicon tree in alphabetical order
    friend ostream& operator<<(ostream& out, const lexicon& l) {
        l.printLexicon(out, l.root);
        return out;
    }

private:
    // Recursive helper function to insert a word into the lexicon tree
    void insertRecursive(Node* currentNode, const string& s) {
        if (s < currentNode->key) {
            if (currentNode->left == nullptr) {
                currentNode->left = new Node(s);
            } else {
                insertRecursive(currentNode->left, s);
            }
        } else if (s > currentNode->key) {
            if (currentNode->right == nullptr) {
                currentNode->right = new Node(s);
            } else {
                insertRecursive(currentNode->right, s);
            }
        } else {
            currentNode->freq++;
        }
    }

    // Recursive helper function to find a node with a given word in the lexicon tree
    Node* findNode(Node* currentNode, const string& s) const {
        if (currentNode == nullptr || currentNode->key == s) {
            return currentNode;
        }

        if (s < currentNode->key) {
            return findNode(currentNode->left, s);
        } else {
            return findNode(currentNode->right, s);
        }
    }

    // Recursive helper function to calculate the depth of a word in the lexicon tree
    int getDepth(Node* currentNode, const string& s, int depth) {
        if (currentNode == nullptr || currentNode->key == s) {
            return (currentNode != nullptr) ? depth : 0;
        }

        if (s < currentNode->key) {
            return getDepth(currentNode->left, s, depth + 1);
        } else {
            return getDepth(currentNode->right, s, depth + 1);
        }
    }

    // Recursive helper function to remove a node with a given word from the lexicon tree
    Node* removeNode(Node* currentNode, const string& s) {
        if (currentNode == nullptr) {
            return currentNode;
        }

        if (s < currentNode->key) {
            currentNode->left = removeNode(currentNode->left, s);
        } else if (s > currentNode->key) {
            currentNode->right = removeNode(currentNode->right, s);
        } else {
            if (currentNode->freq > 1) {
                currentNode->freq--;
            } else {
                if (currentNode->left == nullptr) {
                    Node* temp = currentNode->right;
                    delete currentNode;
                    return temp;
                } else if (currentNode->right == nullptr) {
                    Node* temp = currentNode->left;
                    delete currentNode;
                    return temp;
                }

                Node* smallestNode = findSmallestNode(currentNode->right);
                currentNode->key = smallestNode->key;
                currentNode->freq = smallestNode->freq;
                currentNode->right = removeNode(currentNode->right, smallestNode->key);
            }
        }

        return currentNode;
    }

    // Helper function to find the smallest node in a subtree (used for deletion)
    Node* findSmallestNode(Node* currentNode) const {
        while (currentNode->left != nullptr) {
            currentNode = currentNode->left;
        }
        return currentNode;
    }

    // Helper function to insert multiple occurrences of a word into the lexicon tree
    void insertOccurrences(const string& s, int frequency) {
        for (int i = 0; i < frequency; i++) {
            insert(s);
        }
    }

    // Helper function to clear the lexicon tree (used in the destructor)
    void clear(Node* currentNode) {
        if (currentNode != nullptr) {
            clear(currentNode->left);
            clear(currentNode->right);
            delete currentNode;
        }
    }

    // Recursive helper function to print the lexicon tree in alphabetical order
    void printLexicon(ostream& out, const Node* currentNode) const {
        if (currentNode != nullptr) {
            printLexicon(out, currentNode->left);
            out << currentNode->key << " " << currentNode->freq << endl;
            printLexicon(out, currentNode->right);
        }
    }
};

