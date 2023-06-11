#include <iostream>
#include <string>

using namespace std;

class lexicon {
private:
    struct Node {
        string word;
        int frequency;
        Node* left;
        Node* right;

        Node(const string& w) : word(w), frequency(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

public:
    lexicon() : root(nullptr) {}
    ~lexicon() {
        clear(root);
    }

    void insert(const string& s) {
        if (root == nullptr) {
            root = new Node(s);
        } else {
            insertHelper(root, s);
        }
    }

    int lookup(const string& s) const {
        Node* node = findNode(root, s);
        if (node == nullptr) {
            return 0;
        } else {
            return node->frequency;
        }
    }

    int depth(const string& s) {
        return depthHelper(root, s, 0);
    }

    void replace(const string& s1, const string& s2) {
        replaceHelper(root, s1, s2);
    }

    friend ostream& operator<<(ostream& out, const lexicon& l) {
        l.printInOrder(out, l.root);
        return out;
    }

private:
    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    void insertHelper(Node* node, const string& s) {
        if (s < node->word) {
            if (node->left == nullptr) {
                node->left = new Node(s);
            } else {
                insertHelper(node->left, s);
            }
        } else if (s > node->word) {
            if (node->right == nullptr) {
                node->right = new Node(s);
            } else {
                insertHelper(node->right, s);
            }
        } else {
            node->frequency++;
        }
    }

    Node* findNode(Node* node, const string& s) const {
        if (node == nullptr || node->word == s) {
            return node;
        } else if (s < node->word) {
            return findNode(node->left, s);
        } else {
            return findNode(node->right, s);
        }
    }

    int depthHelper(Node* node, const string& s, int depth) {
        if (node == nullptr) {
            return -1;
        } else if (node->word == s) {
            return depth;
        } else if (s < node->word) {
            return depthHelper(node->left, s, depth + 1);
        } else {
            return depthHelper(node->right, s, depth + 1);
        }
    }

    Node* findMinNode(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void replaceHelper(Node*& node, const string& s1, const string& s2) {
        if (node == nullptr) {
            return;
        } else if (s1 < node->word) {
            replaceHelper(node->left, s1, s2);
        } else if (s1 > node->word) {
            replaceHelper(node->right, s1, s2);
        } else {
            // s1 found
            int frequency = node->frequency;
            deleteNode(node);
            if (frequency > 0) {
                insertHelper(root, s2);
                Node* newNode = findNode(root, s2);
                newNode->frequency = frequency;
            }
        }
    }

    void deleteNode(Node*& node) {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        } else if (node->left == nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        } else if (node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        } else {
            Node* successor = findMinNode(node->right);
            node->word = successor->word;
            node->frequency = successor->frequency;
            deleteNode(successor);
        }
    }

    void printInOrder(ostream& out, Node* node) const {
        if (node != nullptr) {
            printInOrder(out, node->left);
            out << node->word << node->frequency << endl;
            printInOrder(out, node->right);
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

    cout << "The word 'the' is found " << l.lookup("the") << " time(s)" << endl;
    cout << "The word 'and' is found at depth " << l.depth("and") << endl;
    cout << l;

    l.replace("boy", "wolf");

    cout << "After replacement:\n";
    cout << l;
    cout << "Now the word 'and' is found at depth " << l.depth("and") << endl;

    return 0;
}
