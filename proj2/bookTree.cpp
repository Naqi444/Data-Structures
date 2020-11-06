#include "bookTree.h"
BookTree::BookTree(){_root=nullptr;}

BookTree::~BookTree(){
    clear(_root);
}

BNode* BookTree::makeSplay(BNode* root, string key){
    if(root!=nullptr)
    {
         if (root->_parent != nullptr)
         {
              if(root->_parent->_parent!=nullptr)
              {
                   if(root->_key >root->_parent->_key && root->_parent->_key > root->_parent->_parent->_key)
                   {
                        leftRotate(root->_parent->_parent);
                        leftRotate(root->_parent);
                        return makeSplay(root,key);
                   }
                   else if (root->_key > root->_parent->_key && root->_parent->_key < root->_parent->_parent->_key)
                   {
                        leftRotate(root->_parent);
                        rightRotate(root->_parent);
                        return makeSplay(root,key);
                   }
                   else if(root->_key < root->_parent->_key && root->_parent->_key < root->_parent->_parent->_key)
                   {
                        rightRotate(root->_parent->_parent);
                        rightRotate(root->_parent);
                        return makeSplay(root,key);
                   } else if (root->_key < root->_parent->_key && root->_parent->_key > root->_parent->_parent->_key)
                {
                    rightRotate(root->_parent);
                    leftRotate(root->_parent);
                    return makeSplay(root, key);
                }
              }
          else
            {
                if (root->_key < root->_parent->_key)
                {
                    rightRotate(root->_parent);
                    return makeSplay(root, key);
                }
                else if (root->_key > root->_parent->_key)
                {
                    leftRotate(root->_parent);
                    return makeSplay(root, key);
                }
            }
         }
         _root = root;
         return _root;
    }
    return nullptr;
}
BNode* BookTree::rightRotate(BNode* x){
    if(x!= nullptr)
    {
         if(x->_left !=nullptr)
         {
              BNode* newRoot = x->_left;
              BNode* newChildTree = newRoot->_right;

              if(x->_parent == nullptr)
              {
                   newRoot->_parent = nullptr;
                   _root = newRoot;
              }
              else
              {
                   newRoot ->_parent = x->_parent;
                   if(x->_parent->_right!=nullptr)
                   {
                        if(x->_parent->_right==x)
                             {
                                  x->_parent->_right = newRoot;
                             }
                   }
                    if(x->_parent->_left != nullptr)
                        {
                             if (x->_parent->_left ==x)
                             {
                                  x->_parent->_left = newRoot;
                             }
                        }
                   }
                   x->_parent = newRoot;
                   x->_left = newChildTree;
                   newRoot->_right = x;

                   if(newChildTree != nullptr)
                   {
                        newChildTree->_parent = x;
                   }
                   return newRoot;
              }
         }
    return nullptr;
}
BNode* BookTree::leftRotate(BNode* x){
     if (x != nullptr)
    {
        if (x->_right != nullptr)
        {
            BNode* newRoot = x->_right;
            BNode* newChildTree = newRoot->_left;
            if (x->_parent == nullptr) 
            {
                newRoot->_parent = nullptr;
                _root = newRoot;
            }
            else
            {
                newRoot->_parent = x->_parent;
                if (x->_parent->_right != nullptr)
                {
                    if (x->_parent->_right == x)
                    {
                        x->_parent->_right = newRoot;
                    }
                    }
                if (x->_parent->_left != nullptr)
                {
                    if (x->_parent->_left == x)
                    {
                        x->_parent->_left = newRoot;
                    }
                }
            }
            x->_parent = newRoot;
            x->_right = newChildTree;
            newRoot->_left = x;
            if (newChildTree != nullptr)
            {
                newChildTree->_parent = x;
            }
            return newRoot;
        }
    }
    return nullptr;
}

bool BookTree::insert(string key, string author, string text){
    if (_root == nullptr)
    {
        _root = new BNode(key, author, text);
        return true;
    }
    else
    {
        bool inserted = false;
        BNode* curr = _root;
        while (!inserted)
        {
            if (key == curr->_key)
            {
                return false;
            }
            else if (key < curr->_key)
            {
                if (curr->_left == nullptr)
                {
                    BNode* newNode = new BNode(key, author, text);
                    curr->_left = newNode;
                    newNode->_parent = curr;
                    makeSplay(newNode, key);
                    return true;
                }
                else
                {
                    curr = curr->_left;
               }
            }
            else
            {
                if (curr->_right == nullptr)
                {
                    BNode* newNode = new BNode(key, author, text);
                    curr->_right = newNode;
                    newNode->_parent = curr;
                    makeSplay(newNode, key);
                    return true;
                }
                else
                {
                    curr = curr->_right;
                }
            }
        }
    }
     return false;
}
void BookTree::clear(BNode* root){
    if (root != nullptr)
    {
        clear(root->_left);
        clear(root->_right);
        delete root;
    }
    return;

}

void BookTree::inorderHelp(BNode* root, bool verbose) const{
    if (root != nullptr){
        if (verbose){
            cout << "(";
            inorderHelp( root->_left, verbose );
            cout << root->_key << ":" << root->_author;
			root->_tree.dump();
            inorderHelp( root->_right, verbose );
            cout << ")";
        }
        else{
            inorderHelp( root->_left, verbose );
            cout << root->_key;
            inorderHelp( root->_right, verbose );
        }
    }
}

void BookTree::dump(bool verbose) const{
    inorderHelp(_root, verbose);
}

int BookTree::findFrequency(string title, string word){
     bool found = false;
     BNode* curr = _root;
    while (!found)
    {
        if (_root == nullptr)
        {
            cout << "Tree Empty" << endl;
            return -1;
        }
        if (title == curr->_key)
        {
            makeSplay(curr, title);
            found = true;
            return curr->findFrequency(word);
        }
        else
        {
            if (title < curr->_key)
            {
                if (curr->_left != nullptr)
                {
                    curr = curr->_left;
                }
                else
                {
                    makeSplay(curr, title);
                    return -1;
                }
            }
             if (title > curr->_key)
            {
                if (curr->_right != nullptr)
                {
                    curr = curr->_right;
                }
                else
                {
                    makeSplay(curr, title);
                    return -1;
                }
            }
        }
    }
    return -1;
}
void BookTree::dumpTitle(string title){
    bool found = false;
    BNode* curr = _root;
    while (!found)
    {
        if (_root == nullptr)
        {
            cout << "Cannot find something from empty tree" << endl;
            return;
        }
        if (title == curr->_key)
        {

            makeSplay(curr, title);
            curr->_tree.dump();
            return;
        }
        else
        {

            if (title < curr->_key)
            {
                if (curr->_left != nullptr)
                {
                    curr = curr->_left;
                }
                else
                {
                    makeSplay(curr, title);
                    cout << "That title is not in the Tree." << endl;
                    return;
                }
            }
             if (title > curr->_key)
            {
                if (curr->_right != nullptr)
                {
                    curr = curr->_right;
                }
                else
                {
                    makeSplay(curr, title);
                    cout << "That title is not in the Tree." << endl;
                    return;
                }
            }
        }
    }
    return;
}
int BookTree::searchCount(string title, string word){
     bool found = false;
    BNode* curr = _root;
    while (!found)
    {
        if (_root == nullptr)
        {
            cout << "Cannot find something from empty tree" << endl;
            return -1;
        }
        if (title == curr->_key)
        {
            makeSplay(curr, word);
            return curr->searchCount(word);
        }
        else
        {
            if (title < curr->_key)
            {
                if (curr->_left != nullptr)
                {
                    curr = curr->_left;
                }
                else
                {
                    makeSplay(curr, word);
                    return -1;
                }
            }
            if (title > curr->_key)
            {
                if (curr->_right != nullptr)
                {
                    curr = curr->_right;
                }
                else
                {
                    makeSplay(curr, word);
                    return -1;
                }
            }
        }
    }
    return -1;
}


int BookTree::getTextTreeHeight(string title){
      bool found = false;
    BNode* curr = _root;
    while (!found)
    {
        if (_root == nullptr)
        {
            cout << "Cannot find something from empty tree" << endl;
            return -1;
        }
        if (title == curr->_key)
        {
            makeSplay(curr, title);
            return curr->getTextTreeHeight();
        }
        else
        {
            if (title < curr->_key)
            {
                if (curr->_left != nullptr)
                {
                    curr = curr->_left;
                }
                else
                {
                    makeSplay(curr, title);
                    return -1;
                }
            }
            if (title > curr->_key)
            {
                  if (curr->_right != nullptr)
                {
                    curr = curr->_right;
                }
                else
                {
                    makeSplay(curr, title);
                    return -1;
                }
            }
        }
    }
    return -1;
}
int BookTree::getWordHeight(string title, string word){
    bool found = false;
    BNode* curr = _root;
    while (!found)
    {
        if (_root == nullptr)
        {
            cout << "Tree empty" << endl;
            return -1;
        }
        if (title == curr->_key)
        {
            makeSplay(curr, title);
            return curr->getNodeHeight(word);
        }
        else
        {
            if (title < curr->_key)
            {
                if (curr->_left != nullptr)
                {
                    curr = curr->_left;
                }
                else
                {
                    makeSplay(curr, title);
                    return -1;
                }
            }
            if (title > curr->_key)
            {
                 if (curr->_right != nullptr)
                {
                    curr = curr->_right;
                }
                else
                {
                    makeSplay(curr, title);
                    return -1;
                }
            }
        }
    }
    return -1;
}

string BookTree::getRootKey(){
	return _root->_key;
}

void BookTree::loadData(string dataFile){
	std::ifstream t(dataFile);
	std::stringstream buffer;
	buffer << t.rdbuf();

	string titleDelimiter = "<==>";
	string itemsDeleimiter = "<=>";
	string s = buffer.str();
	size_t pos = 0;
	string token;
	while ((pos = s.find(titleDelimiter)) != string::npos) {
		token = s.substr(0, pos);
		int tempPos = token.find(itemsDeleimiter);
		string title = token.substr(0,tempPos);
		std::transform (title.begin(), title.end(), title.begin(), ::tolower);
		token.erase(0, tempPos + itemsDeleimiter.length()+1);
		tempPos = token.find(itemsDeleimiter);
		string author = token.substr(0,tempPos);
		std::transform (author.begin(), author.end(), author.begin(), ::tolower);
		token.erase(0, tempPos + itemsDeleimiter.length()+1);
		string text = token.substr(0,token.length() - 1);
          for( std::string::iterator iter = text.begin() ; iter != text.end() ; ){
               if( !std::isalnum(*iter) && *iter != ' ') 
                    iter = text.erase(iter) ;
               else 
                    ++iter ;
          }
		std::transform (text.begin(), text.end(), text.begin(), ::tolower);
		
		insert(title,author,text);
		s.erase(0, pos + titleDelimiter.length()+1);
	}
}