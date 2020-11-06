#include "bNode.h"
BNode::BNode(){}
BNode::BNode(string key, string author, string text){
            _key = key;
            _author = author;
            _left = nullptr;
            _right = nullptr;
            _flag = false;
            _parent = nullptr;
            createTextTree(text);
        }
BNode::~BNode(){

}

void BNode::createTextTree(string text){
    istringstream iss(text);
    vector<string> tokens;
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));
    for (std::vector<string>::iterator it = tokens.begin() ; it != tokens.end(); ++it){
        _tree.insert(*it);
    }
}

int BNode::findFrequency(string word){
    if(_tree.find(word)!=nullptr)
    {
        return _tree.find(word) -> getFrequency();
    }
    return 0;
}

int BNode::searchCount(string word){
    return _tree.searchCount(word);
}

int BNode::getTextTreeHeight(){
    return _tree.getRootHeight();;
}

int BNode::getNodeHeight(string word){
    return _tree.getNodeHeight(word);
}