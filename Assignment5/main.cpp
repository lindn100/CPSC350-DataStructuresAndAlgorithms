#include <iostream>
#include "BST.h"
#include "TreeNode.h"
using namespace std;

int main(int argc, char* argv[])
{
  BST<int> myTree;
  TreeNode<int> *mine =  new TreeNode<int>(10);
  myTree.insert(mine);
  myTree.printTree();
  mine = new TreeNode<int>(5);
  myTree.insert(mine);
  mine = new TreeNode<int>(15);
  myTree.insert(mine);
  mine = new TreeNode<int>(12);
  myTree.insert(mine);
  mine = new TreeNode<int>(17);
  myTree.insert(mine);
  myTree.printTree();
  if(!myTree.contains(7))
  {
    cout << "nice" << endl;
  }
  if(myTree.contains(17))
  {
    cout << "very nice" << endl;
  }
  myTree.deleteNode(10);
  myTree.printTree();
  return 0;
}
