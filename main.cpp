#include <iostream>
#include <string>
#include <unordered_map>
#include "bst.cpp"

void printValues(const std::list<std::pair<int, std::string>> l) {
  std::cout << "values: " << std::endl;
  for(auto const &i : l) {
    std::cout << "(" << i.first << ": " << i.second << ") " << std::endl;
  }
}

int main() {
  BST bst;
  bst.Insert(30, "car");
  bst.Insert(10, "bird");
  bst.Insert(15, "coin");
  bst.Insert(60, "tree");
  bst.Insert(8, "bug");
  bst.Insert(18, "pen");
  bst.Insert(40, "fly");
  bst.Insert(20, "gun");

  std::list<std::pair<int, std::string>> l;
  l = bst.GetValues(INORDER);
  printValues(l);

  int search_key = 18;
  BSTNode *result = bst.Search(search_key);
  std::cout << "value for key " << search_key << " is '" << (result == nullptr ? "?" : result->value) << "'" << std::endl;

  int delete_key = 10;
  std::cout << "deleting key " << delete_key << std::endl;
  bst.Delete(delete_key);
  l = bst.GetValues(INORDER);
  printValues(l);

  return 0;
}
