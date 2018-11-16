#include <iostream>
#include "BST.h"
#include "Student.h"
#include "Faculty.h"
using namespace std;

int main(int argc, char* argv[])
{

  BST<Student> studentTree;

  Student ryan(200, "ryan2", "senior", "cs", 4.0, 69);
  studentTree.insert(ryan);
  Student lol(100, "ryan1", "senior", "cs", 1.0, 420);
  studentTree.insert(lol);
  Student matt(500, "matt", "sophmore", "cs", 3.0, 12);
  studentTree.insert(matt);
  Student rene(1, "rene", "prof", "cs", 4.0, 1);
  studentTree.insert(rene);
  studentTree.deleteNode(100);
  studentTree.printTree();
/*  if(!myTree.contains(7))
  {
    cout << "nice" << endl;
  }
  if(myTree.contains(17))
  {
    cout << "very nice" << endl;
  }
  myTree.deleteNode(10);
  myTree.printTree();

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

  Faculty rene(1000, "rene", "Prof", "cs");
  rene.addAdvisee(ryan.getID());
  //print advisees method is gonna have to for each node in list, search them in the Student BST and print all their info.
  rene.printAdvisees();*/

  return 0;
}
