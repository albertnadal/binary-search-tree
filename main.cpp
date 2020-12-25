#include <iostream>
#include <string>
#include <unordered_map>
#include "bst.cpp"

void printValues(const std::unordered_map<int, std::string> l) {
    for (auto const &i : l) {
        std::cout << "(" << i.first << ": " << i.second << ") " << std::endl;
    }
}

int main() {
    BST bst;
    bst.Insert(10, "molt");
    bst.Insert(11, "bon");
    bst.Insert(4, "fa");
    bst.Insert(3, "Avui");
    bst.Insert(22, "dia!");

    std::unordered_map<int, std::string> l;
    std::cout << "inorder: " << std::endl;
    l = bst.GetValues(INORDER);
    printValues(l);

    std::cout << "preorder: " << std::endl;
    l = bst.GetValues(PREORDER);
    printValues(l);

    std::cout << "postorder: " << std::endl;
    l = bst.GetValues(POSTORDER);
    printValues(l);

    int search_key = 4;
    BSTNode *result = bst.Search(search_key);
    std::cout << "value for key " << search_key << " is '" << (result == nullptr ? "?" : result->value) << "'"
              << std::endl;

    int delete_key = 22;
    std::cout << "deleting key " << delete_key << std::endl;
    bst.Delete(delete_key);
    std::cout << "inorder: " << std::endl;
    l = bst.GetValues(INORDER);
    printValues(l);

    delete_key = 10;
    std::cout << "deleting key " << delete_key << std::endl;
    bst.Delete(delete_key);
    std::cout << "inorder: " << std::endl;
    l = bst.GetValues(INORDER);
    printValues(l);

    return 0;
}
