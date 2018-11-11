#ifndef TreeNode_H
#define TreeNode_H

template<typename T>
class TreeNode
{
public:
  TreeNode();
  TreeNode(int k);
  ~TreeNode();

  int key;
  TreeNode<T> *left;
  TreeNode<T> *right;
};

template<typename T>
TreeNode<T>::TreeNode()
{
  left = nullptr;
  right = nullptr;
}

template<typename T>
TreeNode<T>::TreeNode(int k)
{
  key = k;
  left = nullptr;
  right = nullptr;
}

template<typename T>
TreeNode<T>::~TreeNode()
{

}
#endif
