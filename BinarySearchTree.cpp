#include "BinarySearchTree.hpp"
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

BinarySearchTree::Node::Node(BinarySearchTree::DataType newval){
    val = newval;
    left = NULL;
    right = NULL;
}

BinarySearchTree::BinarySearchTree(){
    size_ = 0;
    root_ = NULL;
}

BinarySearchTree::~BinarySearchTree(){
    if(root_!=NULL){
        queue<Node*> Q;
        Q.push(root_);

        while(!Q.empty()){
            if(Q.front()->left != NULL)
                Q.push(Q.front()->left);
            if(Q.front()->right != NULL)
                Q.push(Q.front()->right);
            delete Q.front();
            Q.pop();
        }
    }
}

int BinarySearchTree::getNodeDepth(Node* n) const{
    if(n == NULL)
        return -1;

    return 1 + std::max(getNodeDepth(n->left), getNodeDepth(n->right));
}

unsigned int BinarySearchTree::size() const{
    return size_;
}

unsigned int BinarySearchTree::depth() const{
    return getNodeDepth(root_);
}

BinarySearchTree::DataType BinarySearchTree::min() const{
    Node* curNode = root_;
    while(curNode->left != NULL)
        curNode = curNode->left;
    return curNode->val;
}

BinarySearchTree::DataType BinarySearchTree::max() const{
    Node* curNode = root_;
    while(curNode->right != NULL)
        curNode = curNode->right;
    return curNode->val;
}

bool BinarySearchTree::exists(DataType val) const
{
    Node* curNode = root_;

    while(curNode != NULL)
    {
        if(curNode->val == val)
            return true;
        else if (val > curNode->val)
            curNode = curNode->right;
        else
            curNode = curNode->left;
    }

    return false;
}

bool BinarySearchTree::insert(DataType val)
{
    if(root_ == NULL){
        root_ = new Node(val);
        size_++;
        return true;
    }

    Node* curNode = root_;

    while(true){
        if(curNode->val == val)
            return false;

        else if (val > curNode->val){
            if(curNode->right == NULL){
                curNode->right = new Node(val);
                break;
            }
            curNode = curNode->right;
        }
        else{
            if(curNode->left == NULL){
                curNode->left = new Node(val);
                break;
            }
            curNode = curNode->left;
        }
    }

    size_++;
    return true;
}

bool BinarySearchTree::remove(DataType val)
{
    if(!exists(val))
        return false;

    Node* child = root_;
    Node* parent = NULL;

    while(child->val != val){
        parent = child;
        if (val > child->val)
            child = child->right;
        else
            child = child->left;
    }

    if(child->right == NULL){
        if(parent != NULL){
            if(child->val > parent->val)
                parent->right = child->left;
            else
                parent->left = child->left;
        }

        else
            root_ = child->left;

        delete child;
        child = NULL;
    }

    else if(child->left == NULL){
        if(parent != NULL){
            if(child->val > parent->val)
                parent->right = child->right;

            else
                parent->left = child->right;
        }

        else
            root_ = child->right;

        delete child;
        child = NULL;
    }

    else{
        Node* successor_child = child->right;
        Node* successor_parent = child;

        if(successor_child->left == NULL){
            child->val = successor_child->val;
            child->right = successor_child->right;
        }

        else{
            while(successor_child->left != NULL){
                successor_parent = successor_child;
                successor_child = successor_child->left;
            }
            child->val = successor_child->val;
            successor_parent->left = successor_child->right;
        }

        delete successor_child;
        successor_parent = NULL;
        successor_child = NULL;
    }

    size_--;
    return true;
}

void BinarySearchTree::print() const
{
	stack<Node*> s;
	Node *cur = root_;

	while(cur != NULL || s.empty() == false){
		while(cur!=NULL){
			s.push(cur);
			cur = cur->left;
		}
		cur = s.top();
		s.pop();
		cout << cur->val << " ";
		cur = cur->right;
	}
}
