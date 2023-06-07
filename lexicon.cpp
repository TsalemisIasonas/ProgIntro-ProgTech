#include <iostream>
#include <string>

using namespace std;

class lexicon {
private:
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
    lexicon() {
        root = nullptr;
    }

    ~lexicon() {
        clear(root);
    }

    void insert(const string& s) {
        if (root == nullptr) {
            root = new Node(s);
        } else {
            insertRecursive(root, s);
        }
    }

    int lookup(const string& s) const {
        Node* node = findNode(root, s);
        return (node != nullptr) ? node->freq : 0;
    }

    int depth(const string& s) {
        return getDepth(root, s, 1);
    }

    void replace(const string& s1, const string& s2) {
        int frequency = lookup(s1);

        if (frequency == 0) {
            return; 
        }

        removeNode(root, s1);
        insertOccurrences(s2, frequency);
    }

    friend ostream& operator<<(ostream& out, const lexicon& l) {
        l.printLexicon(out, l.root);
        return out;
    }

private:
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

    int getDepth(Node* currentNode, const string& s, int depth) {
        if (currentNode == nullptr) {
            return 0;
        }

        if (s < currentNode->key) {
            return getDepth(currentNode->left, s, depth + 1);
        } else if (s > currentNode->key) {
            return getDepth(currentNode->right, s, depth + 1);
        } else {
            // Key found, return the current depth
            return depth;
        }
    }

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

    Node* findSmallestNode(Node* currentNode) const {
        while (currentNode->left != nullptr) {
            currentNode = currentNode->left;
        }
        return currentNode;
    }

    void insertOccurrences(const string& s, int frequency) {
        for (int i = 0; i < frequency; i++) {
            insert(s);
        }
    }

    void clear(Node* currentNode) {
        if (currentNode != nullptr) {
            clear(currentNode->left);
            clear(currentNode->right);
            delete currentNode;
        }
    }
    
    void printLexicon(ostream& out, const Node* currentNode) const {
        if (currentNode != nullptr) {
            printLexicon(out, currentNode->left);
            out << currentNode->key << " " << currentNode->freq << endl;
            printLexicon(out, currentNode->right);
        }
    }
};

int main() {
    lexicon l;
    l.insert("the");
    l.insert("boy");
    l.insert("and");
    l.insert("the");
    l.insert("wolf");

    int the_freq = l.lookup("the");
    cout << "The word 'the' is found " << the_freq << " time";
    if (the_freq > 1) {
        cout << "s";
    }
    cout << endl;

    cout << "The word 'and' is found at depth " << l.depth("and") - 1 << endl;
    cout << "and " << l.lookup("and") << endl;
    cout << "boy " << l.lookup("boy") << endl;
    cout << "the " << l.lookup("the") << endl;
    cout << "wolf " << l.lookup("wolf") << endl;

    l.replace("boy", "wolf");
    cout << "After replacement:\n";
    cout << l;
    cout << "Now the word 'and' is found at depth " << l.depth("and") - 1 << endl;
}
