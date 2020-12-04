// CMSC 341 - Fall 2020 - Project 3
// PQueue: an ER triage queue using a skew heap and function pointers

#include "pqueue.h"
using namespace std;
using std::cout;
using std::endl;
using std::domain_error;

PQueue::PQueue(prifn_t priFn) {
    priority = priFn;
    _heap = nullptr;
    _size = 0;
  
}

PQueue::~PQueue() {
  clear();
}

PQueue::PQueue(const PQueue& rhs) {
  //Copy Constructor
  _size = rhs._size;
  priority = rhs.priority;

  Node *newHeap = rhs._heap;
  _heap = rhsHelper(newHeap);
}


PQueue& PQueue::operator=(const PQueue& rhs) {
    if(this!= &rhs){
        clear();
        if(_heap == nullptr){
            _size = rhs._size;
            priority = rhs.priority;

            Node *currRhs = rhs._heap;
            _heap = rhsHelper(currRhs);
        }
    }
    return *this;
}

void PQueue::insertPatient(const Patient& input) {
    if(_heap==nullptr){
        _heap = new Node(input);
        _size++;
        return;
    }
  Node  *patient = new Node (input);
  _heap = mergeHelper(_heap,patient);
  _size++;
}


Patient PQueue::getNextPatient() {

    Node *heapHolder = _heap;
    if(_heap == nullptr){
        throw domain_error("No patient in the queue_");
    }

    Patient patient = _heap -> getPatient();

    _heap = mergeHelper(_heap->_left, _heap->_right); 
    delete heapHolder;
    _size--;
    return patient;  
}


void PQueue::mergeWithQueue(PQueue& rhs) {

    if(this!=&rhs){
        if(getPriorityFn()!=rhs.getPriorityFn()){
            throw domain_error("The two queue have different priorities, cannot merge.");
        }

        _heap = mergeHelper(_heap,rhs._heap);
        _size = _size + rhs._size;

        rhs._heap = nullptr;
        rhs._size = 0;
    }
    return;  
}

void PQueue::clear() {
  if (_heap == nullptr){
      return;
  }
  clearHelper(_heap);

  delete _heap;
  _heap = nullptr;
  _size = 0;
}

int PQueue::numPatients() const {
  return _size;
}

void PQueue::printPatientQueue() const {
    if (_heap == nullptr){
        cout << "No patients in the queue"<<endl;
    }
//   cout << "Following patients are in the queue:" << endl;
    preOrder(_heap);
}

prifn_t PQueue::getPriorityFn() const {
    return priority;
  
}

void PQueue::setPriorityFn(prifn_t priFn) {
    priority = priFn;
    PQueue tempQueue(priority);

    while(_size!=0){
        Patient newPatient = getNextPatient();
        tempQueue.insertPatient(newPatient);       
    }

    _heap = tempQueue._heap;
    _size = tempQueue._size;
    tempQueue._heap = nullptr;
}

void PQueue::dump() const
{
  inOrder(_heap);
}

void PQueue::clearHelper(Node *aNode){
    if(aNode -> _left!=nullptr){
        clearHelper(aNode->_left);
        delete aNode->_left;
    }

    if(aNode->_right!=nullptr){
        clearHelper(aNode->_right);
        delete aNode->_right;
    }
}

void PQueue::inOrder(Node *aNode) const {
    if(aNode !=nullptr){
        cout << "(";
        inOrder(aNode->_left);
        cout << priority(aNode->getPatient()) << ":" << aNode-> _patient.getPatient();
        inOrder(aNode ->_right);
        cout <<")";
    }
}
Node * PQueue::mergeHelper(Node *firstNode, Node *secNode){
    if(firstNode == nullptr){
        return secNode;
    }

    if(secNode == nullptr){
        return firstNode;
    }

    if(priority(firstNode -> getPatient())<= priority(secNode ->getPatient())){
        Node *temp = firstNode->_right;
        firstNode -> _right = firstNode->_left;
        firstNode-> _left = mergeHelper(secNode,temp);
        return firstNode;
    } else{
        return mergeHelper(secNode,firstNode);
    }
}

void PQueue::preOrder(Node *aNode) const{
    if(aNode!=nullptr){
        cout<< "[" << priority(aNode ->getPatient()) << "]" << aNode ->getPatient() << endl;
        preOrder(aNode->_left);
        preOrder(aNode->_right);
    }
}

Node* PQueue::rhsHelper(Node *aNode){
    Node* temp;

    if(aNode!=nullptr){
        temp = new Node(aNode->getPatient());
        temp -> _left = rhsHelper(aNode->_left);
        temp -> _right = rhsHelper(aNode->_right);
        return temp;
    }
    return aNode;
}

ostream& operator<<(ostream& sout, const Patient& patient) {
  sout << "Patient: " << patient.getPatient() << ", triage: " << patient.getTriage()
       << ", temperature: " << patient.getTemperature() << ", oxygen: " << patient.getOxygen() << ", RR: "
       << patient.getRR() << ", HR: " << patient.getHR() << ", BP: " << patient.getBP();
  return sout;
}

ostream& operator<<(ostream& sout, const Node& node) {
  sout << node.getPatient();
  return sout;
}

