#include <iostream>
#include "BST.h"
#include "TreeNode.h"
#include "Student.h"
using namespace std;

int main(int argc, char* argv[])
{
  /*
  BST<int> myTree;
  TreeNode<int> *mine =  new TreeNode<int>(10);
  myTree.insert(mine);
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
  */

  Student ryan(100, "ryan", "senior", "cs", 4.0, 69);
  Student tiff(200, "tiff", "senior", "bio", 4.0, 69);
  if(ryan < tiff)
  {
    cout << ":)" << endl;
  }
  else
  {
    cout << "AWLKEJADSF" << endl;
  }

  return 0;
}
