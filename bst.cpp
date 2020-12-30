#include <iostream>
#include <string>
#include <list>
#include <utility>

enum BSTTraverseMode {
    PREORDER, INORDER, POSTORDER
};

struct BSTNode {
    int key;
    std::string value;
    BSTNode *left;
    BSTNode *right;
};

class BST {

private:
    BSTNode *root = nullptr;
    unsigned int size = 0;
    void GetValuesInOrder(std::list<std::pair<int, std::string>> &l, BSTNode *node);
    void GetValuesPreOrder(std::list<std::pair<int, std::string>> &l, BSTNode *node);
    void GetValuesPostOrder(std::list<std::pair<int, std::string>> &l, BSTNode *node);
    void DeleteTree(BSTNode *);

public:
    BST();
    ~BST();
    void Insert(int, const std::string &);
    BSTNode *Search(int);
    void Delete(int);
    bool IsEmpty();
    unsigned int Size();
    std::list<std::pair<int, std::string>> GetValues(BSTTraverseMode mode);
};

BST::BST() = default;

BST::~BST() {
    this->DeleteTree(this->root);
}

bool BST::IsEmpty() {
    return this->size == 0;
}

unsigned int BST::Size() {
    return this->size;
}

void BST::DeleteTree(BSTNode *node) {
    if (node == nullptr) return;
    this->DeleteTree(node->left);
    this->DeleteTree(node->right);
    delete node;
    this->size--;
}

std::list<std::pair<int, std::string>> BST::GetValues(BSTTraverseMode mode) {
    std::list<std::pair<int, std::string>> l;
    switch (mode) {
        case INORDER:
            this->GetValuesInOrder(l, this->root);
            break;
        case PREORDER:
            this->GetValuesPreOrder(l, this->root);
            break;
        case POSTORDER:
            this->GetValuesPostOrder(l, this->root);
            break;
        default:
            this->GetValuesInOrder(l, this->root);
    }

    return l;
}

void BST::GetValuesInOrder(std::list<std::pair<int, std::string>> &m, BSTNode *node) {
    if (node == nullptr) return;
    this->GetValuesInOrder(m, node->left);
    m.push_back({node->key, node->value});
    this->GetValuesInOrder(m, node->right);
}

void BST::GetValuesPreOrder(std::list<std::pair<int, std::string>> &m, BSTNode *node) {
    if (node == nullptr) return;
    m.push_back({node->key, node->value});
    this->GetValuesPreOrder(m, node->left);
    this->GetValuesPreOrder(m, node->right);
}

void BST::GetValuesPostOrder(std::list<std::pair<int, std::string>> &m, BSTNode *node) {
    if (node == nullptr) return;
    this->GetValuesPostOrder(m, node->left);
    this->GetValuesPostOrder(m, node->right);
    m.push_back({node->key, node->value});
}

void BST::Delete(int key) {
    BSTNode *parentNode, *currentNode;
    parentNode = currentNode = this->root;

    // first search the node to delete
    while (currentNode != nullptr) {
        if (key == currentNode->key) {
            break;
        }
        parentNode = currentNode;
        currentNode = key < currentNode->key ? currentNode->left : currentNode->right;
    }

    // return if no node is found
    if (currentNode == nullptr) {
        // Not found
        return;
    }

    bool currentNodeIsRootNode = currentNode == this->root;
    if (currentNodeIsRootNode) parentNode = new BSTNode(); // This is a sentinel node. Must be delete once this method finishes
    bool currentNodeIsLeftBranch = parentNode->left == currentNode;

    // If current node has no branch nodes then delete current node and update proper parent branch link
    if (currentNode->left == nullptr && currentNode->right == nullptr) {
        if (currentNodeIsLeftBranch) parentNode->left = nullptr;
        else parentNode->right = nullptr;
        delete currentNode;
        this->size--;
        if (currentNodeIsRootNode) delete parentNode;
        return;
    }

    // If current node has left branch then replace it by the the node with highest key on the left branch
    if (currentNode->left != nullptr) {
        BSTNode *auxParentNode, *auxCurrentNode;
        auxParentNode = auxCurrentNode = currentNode->left;

        // Case 1: Left branch has no right subbranch
        if (auxCurrentNode->right == nullptr) {
            auxCurrentNode->right = currentNode->right;
            if (currentNodeIsLeftBranch) parentNode->left = auxCurrentNode;
            else parentNode->right = auxCurrentNode;
            delete currentNode;
            this->size--;
            if (currentNodeIsRootNode) {
                this->root = auxCurrentNode;
                delete parentNode;
            }
            return;
        }

        // Case 2: Left branch has right subbranch
        while (auxCurrentNode->right != nullptr) {
            auxParentNode = auxCurrentNode;
            auxCurrentNode = auxCurrentNode->right;
        }

        auxParentNode->right = nullptr;
        auxCurrentNode->right = currentNode->right;
        if (currentNodeIsLeftBranch) parentNode->left = auxCurrentNode;
        else parentNode->right = auxCurrentNode;
        delete currentNode;
        this->size--;
        if (currentNodeIsRootNode) {
            this->root = auxCurrentNode;
            delete parentNode;
        }
        return;
    }

    // If current node has no left branch and has right branch then replace it by the root node in the right branch
    if (currentNode->right != nullptr) {
        if (currentNodeIsLeftBranch) parentNode->left = currentNode->right;
        else parentNode->right = currentNode->right;
        if (currentNodeIsRootNode) {
            this->root = currentNode->right;
            delete parentNode;
        }
        delete currentNode;
        this->size--;
        return;
    }

}

BSTNode *BST::Search(int key) {
    BSTNode *currentNode = this->root;
    while (currentNode != nullptr) {
        if (key == currentNode->key) {
            return currentNode;
        }
        currentNode = key < currentNode->key ? currentNode->left : currentNode->right;
    }
    return nullptr;
}

void BST::Insert(int key, const std::string &value) {
    BSTNode *node = new BSTNode();
    node->key = key;
    node->value = value;
    node->right = node->left = nullptr;

    if (this->root == nullptr) {
        this->root = node;
        this->size++;
        return;
    }

    BSTNode *currentNode = this->root;
    while (1) {
        if (node->key < currentNode->key) {
            if (currentNode->left == nullptr) {
                currentNode->left = node;
                this->size++;
                break;
            } else {
                currentNode = currentNode->left;
            }
        } else {
            if (currentNode->right == nullptr) {
                currentNode->right = node;
                this->size++;
                break;
            } else {
                currentNode = currentNode->right;
            }
        }
    }
}
