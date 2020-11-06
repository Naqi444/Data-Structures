#include "wordTree.h"

WordTree::~WordTree(){
    clearTree(_root);
}

void WordTree::updateHeight(Node *aNode) {
    if (aNode->_right == nullptr && aNode->_left == nullptr && aNode != _root)
    {
        aNode->_height = 0;
    }
    else if (aNode->_right == nullptr && aNode->_left == nullptr && aNode == _root)
    {
        aNode->_height =1;
    }
    else
    { 
            int leftHeight=0, rightHeight = 0;

            if (aNode->_left!=nullptr)
            {
                leftHeight = aNode->_left->_height;
            }
            if (aNode->_right!=nullptr)
            {
                rightHeight = aNode->_right->_height;
            }
            aNode->_height = (leftHeight >= rightHeight) ? leftHeight +1 : rightHeight +1;
    }
}

void WordTree::updateTreeHt(Node *aNode){
    if (aNode!=nullptr)
    {
        updateTreeHt(aNode->_left);
        updateTreeHt(aNode->_right);
        updateHeight(aNode);
    }
}

void WordTree::clearTree(Node* aNode){
    if(aNode != nullptr)
    {
        if (aNode->_left!=nullptr)
        {
            clearTree(aNode->_left);
        }
        if(aNode->_right!=nullptr)
        {
            clearTree(aNode->_right);
        }
        delete aNode;
    }
    else
    {
        return;
    }
}

void WordTree::inOrder(Node* aNode, std::ostream& ostr){
    if (aNode != nullptr){
        ostr << "[";
        inOrder(aNode->_left, ostr);
        ostr << aNode->_value << ":" << aNode->_count << ":" << aNode->_height;
        inOrder(aNode->_right, ostr);
        ostr << "]";
    }
}

Node* WordTree::find(Node* aNode, const string& element){
    if(aNode != nullptr)
    {
        if(aNode->getValue() == element)
        {
            return aNode;
        }
        else
        {
            if(element < aNode->getValue())
            {
                if(aNode->_left!=nullptr){
                    return  find(aNode->_left,element);
                }
                return nullptr;
            }
            else if(element > aNode->getValue())
            {
                if(aNode->_right!=nullptr)
                {
                    return find(aNode->_right,element);
                }
                return nullptr;
            }
        }   
    }
    return nullptr;
}
Node* WordTree::find(const string& element){
    if(_root == nullptr)
    {
        return nullptr;
    }
    else
    {
        return find(_root,element);
    }
}

Node* WordTree::leftRotation(Node* aNode){
    if (aNode != nullptr)
    {
        if (aNode->_right != nullptr)
        {
            Node* newRoot = aNode->_right;
            Node* newChildTree = newRoot->_left;
            if (aNode->_parent == nullptr)
            {
                newRoot->_parent = nullptr;
                _root = newRoot;
            }
            else
            {
                newRoot->_parent = aNode->_parent;
                if (aNode->_parent->_right != nullptr)
                {
                    if (aNode->_parent->_right == aNode)
                    {
                        aNode->_parent->_right = newRoot;
                    }
                }
                if (aNode->_parent->_left != nullptr)
                {
                    if (aNode->_parent->_left == aNode)
                    {
                        aNode->_parent->_left = newRoot;
                    }
                }
            }
            aNode->_parent = newRoot;
            aNode->_right = newChildTree;
            newRoot->_left = aNode;
            if (newChildTree != nullptr)
            {
                newChildTree->_parent = aNode;
            }
            updateTreeHt(_root);
            return newRoot;
        }
    }
    return nullptr;
}

Node* WordTree::rightRotation(Node* aNode){
     if (aNode != nullptr)
    {
        if (aNode->_left != nullptr)
        {
            Node* newRoot = aNode->_left;
            Node* newChildTree = newRoot->_right;
            if (aNode->_parent == nullptr)
            {
                newRoot->_parent = nullptr;
                _root = newRoot;
            }
            else
            {
                newRoot->_parent = aNode->_parent;
                if (aNode->_parent->_right != nullptr)
                {
                    if (aNode->_parent->_right == aNode)
                    {
                        aNode->_parent->_right = newRoot;
                    }
                }
                if (aNode->_parent->_left != nullptr)
                {
                    if (aNode->_parent->_left == aNode)
                    {
                        aNode->_parent->_left = newRoot;
                    }
                }
            }
            aNode->_parent = newRoot;
            aNode->_left = newChildTree;
            newRoot->_right = aNode;
            if (newChildTree != nullptr)
            {
                newChildTree->_parent = aNode;
            }
            updateTreeHt(_root);
            return newRoot;
        }
    }
    return nullptr;
}

int WordTree::checkBalance(Node* aNode){
    if (aNode != nullptr)
    {
        int difference = getChildHtDiff(aNode);

        if (difference > 1)
        {
            return 1;
        }
        else if (difference < -1)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

int WordTree::getChildHtDiff(Node* aNode)
{
    if (aNode != nullptr)
    {
        int leftChildHeight = -1, rightChildHeight = -1;
        if (aNode->_left != nullptr)
        {
            leftChildHeight = aNode->_left->_height;
        }
        if (aNode->_right != nullptr)
        {
            rightChildHeight = aNode->_right->_height;
        }
        int difference = leftChildHeight - rightChildHeight;
        return difference;
    }
    return -1;
}

Node* WordTree::reBalance(Node* aNode){
    if(aNode != nullptr)
    {
        int nodeBalance = checkBalance(aNode);
        string val = aNode->getValue();
        if(nodeBalance ==1)
        {
            if(aNode->_left!=nullptr)
            {
                if(getChildHtDiff(aNode->_left) < 0)
                {
                    leftRotation(aNode->_left);
                }
                return rightRotation(aNode);
            }
        }

        if (nodeBalance ==-1)
        {
            if (aNode->_right !=nullptr)
            {
                if(getChildHtDiff(aNode->_right)>0)
                {
                    rightRotation(aNode->_right);
                }
                return leftRotation(aNode);
            }
        }
    }
    return aNode;
}

void WordTree::insert(const string& element){
    if(_root==nullptr)
    {
        _root = new Node(element);
        _root->_count++;
    }
    else
    {
        insert(element,_root);
    }
}
Node* WordTree::insert(const string& element, Node*& aNode){
    if(aNode!=nullptr)
    {
        string value = aNode->getValue();
        if(element == value)
        {
            aNode -> _count++;
        }
        else if(element < value)
        {
            if (aNode->_left != nullptr)
            {
                insert(element, aNode->_left);
            }
            else
            {
                Node* newNode = new Node(element);
                aNode->_left = newNode;
                newNode->_parent = aNode;
                newNode->_count++;
                updateTreeHt(_root);
            }
        }
        else if(element >value)
        {
            if(aNode->_right != nullptr)
            {
                insert(element,aNode->_right);
            }
            else
            {
                Node* newNode = new Node(element);
                aNode->_right = newNode;
                newNode->_parent = aNode;
                newNode->_count++;
                updateTreeHt(_root);
            }
        }
        return reBalance(aNode);
    }
    return nullptr;
}

void WordTree::dump(std::ostream& ostr){
    inOrder(_root, ostr);
}

int WordTree::searchCount(string word){
    int result = searchCountHelp(_root,word,0);
    return ((result >=0) ? result:-1);
}

int WordTree::searchCountHelp(Node* aNode, string word, int counter){
    if(aNode!=nullptr)
    {
        if(aNode->_value == word){
            return counter;
        }
        else
        {
            if (word < aNode -> getValue())
            {
                if(aNode->_left!=nullptr){
                    return searchCountHelp(aNode->_left,word,counter+1);
                }
                return -1;
            }
            else if(word > aNode->getValue())
            {
                if(aNode ->_right!=nullptr)
                {
                    return searchCountHelp(aNode->_right,word,counter+1);
                }
                return -1;
            }
        }
    }
    return -1;
}

int WordTree::getRootHeight(){
    if(_root!=nullptr)
    {
        if(_root->_left == nullptr && _root->_right == nullptr)
        {
            return 1;
        }
        else
        {
            return _root->_height;
        }
    }
    return -1;
}

int WordTree::getNodeHeight(string word){
    int result = getNodeHeightHelp(_root,word);
    return (result>=0 ? result:-1);
}

int WordTree::getNodeHeightHelp(Node* aNode, string word){
    if (aNode!=nullptr)
    {
        if(aNode->_value == word)
        {
            return aNode->_height;
        }
        else
        {
            if(word < aNode->getValue())
            {
                if(aNode->_left!=nullptr)
                {
                    return getNodeHeightHelp(aNode->_left,word);
                }
                return -1;
            }
            else if(word > aNode->getValue())
            {
                if (aNode->_right != nullptr)
                {
                    return getNodeHeightHelp(aNode->_right,word);
                }
                return -1;
            }
        }
    }
    return -1;
}