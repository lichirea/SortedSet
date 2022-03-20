#include "SortedSet.h"
#include "SortedSetIterator.h"

//worst,best,total: O(m); this is always the same no matter how it is called
SortedSet::SortedSet(Relation r) {
	TFunction = r;
	m = 5;
	length = 0;
	T = new Node*[m];
	for(int i = 0 ; i < m; i++)
	    T[i] = nullptr;
}

//worst: O(m), best: ϴ(1), total: O(m)
//worst: when there are collisions(that will give us length/m complexity)/we need to resize(the bigger complexity)
//best: when there are no collisions
bool SortedSet::add(TComp elem) {
	int pos = hash(elem);
	if(T[pos] != nullptr){
	    Node* prevNode = nullptr;
	    Node* currentNode = T[pos];
        if(currentNode->info == elem) return false;
	    while(!TFunction(elem, currentNode->info)){
            prevNode = currentNode;
            currentNode = currentNode->next;
            if(currentNode == nullptr) break;
            if(currentNode->info == elem) return false;
        }
	    Node* newNode = new Node;
	    newNode->next = currentNode;
	    if(prevNode == nullptr) T[pos] = newNode;
	    else prevNode->next = newNode;
        newNode->info = elem;
	}
	else{
        Node* newNode = new Node;
        T[pos] = newNode;
        newNode->info = elem;
        newNode->next = nullptr;
	}
	length++;
	if(m-m/4 == length) resize(); // collision threshold is 0.75
    return true;
}

//worst: O(length/m), best: ϴ(1), total: O(length/m)
//worst: when there are collisions
//best: when there are no collisions
bool SortedSet::remove(TComp elem) {
    int pos = hash(elem);
    if(T[pos] != nullptr){
        Node* prevNode = nullptr;
        Node* currentNode = T[pos];
        while(currentNode != nullptr && currentNode->info != elem){
            prevNode = currentNode;
            currentNode = currentNode->next;
        }
        if(currentNode == nullptr) return false;
        if(prevNode != nullptr) prevNode->next = currentNode->next;
        else T[pos] = currentNode->next;
        delete currentNode;
        length--;
        return true;
    }
    return false;
}

//worst: O(length/m), best: ϴ(1), total: O(length/m)
//worst: when there are collisions
//best: when there are no collisions
bool SortedSet::search(TComp elem) const {
	int position = hash(elem);
	Node* currentNode = T[position];
	while(currentNode != nullptr){
        if(currentNode->info == elem) return true;
	    currentNode = currentNode->next;
	}
	return false;
}

//worst,best,total: ϴ(1); this is always the same no matter how it is called
int SortedSet::size() const {
	return length;
}

//worst,best,total: ϴ(1); this is always the same no matter how it is called
bool SortedSet::isEmpty() const {
	if(length == 0 ) return true;
	return false;
}

//worst,best,total: O(m); this is always the same no matter how it is called
SortedSetIterator SortedSet::iterator(){
	return SortedSetIterator(*this);
}

//worst,best,total: O(length); this is always the same no matter how it is called
SortedSet::~SortedSet() {
	for(int i = 0; i < m; i++){
	    if(T[i] != nullptr){
            Node* prevNode = nullptr;
            Node* currentNode = T[i];
            while(currentNode != nullptr){
                prevNode = currentNode;
                currentNode = currentNode->next;
                delete prevNode;
            }
	    }
	}
	delete[] T;
}

//worst,best,total: ϴ(1); this is always the same no matter how it is called
int SortedSet::hash(int k) const {
    if(k < 0) k = -k;
    double d = 42; double* dPointer = &d;
    double x = floor(m * modf(k * 0.6180339887, dPointer));
    int y  = int (x);
    return y;
}

//worst,best,total: O(m); this is always the same no matter how it is called
void SortedSet::resize() {
    m = m * 2;
    Node** copy = new Node*[m];
    for(int i = 0 ; i < m; i++)
        copy[i] = nullptr;
    Node** placeholder = T;
    T = copy;

    for(int i = 0; i < m/2; i++) {
        Node *currentNode = placeholder[i];
        while (currentNode != nullptr) {
            add(currentNode->info);
            length--;
            currentNode = currentNode->next;
        }
    }

    for(int i = 0; i < m/2; i++){
        if(placeholder[i] != nullptr){
            Node* prevNode = nullptr;
            Node* currentNode = placeholder[i];
            while(currentNode != nullptr){
                prevNode = currentNode;
                currentNode = currentNode->next;
                delete prevNode;
                prevNode = nullptr;
            }
        }
    }
    delete[] placeholder;
}

//worst,best,total: O(length); this is always the same no matter how it is called
//so for each key (a total of m) we check for the average number of times(length/m)
//and that means the complexity of length/m * m = length
//I imagine it as a matrix with m rows and length/m columns
int SortedSet::getRange() const {
    if(isEmpty()) return -1;
    int maximum = -9999999;
    int minimum = 9999999;

    for(int i = 0; i < m; i++){
        if(T[i] != nullptr){
            Node* currentNode = T[i];
            while(currentNode != nullptr){
                if(maximum < currentNode->info) maximum = currentNode->info;
                if(minimum > currentNode->info) minimum = currentNode->info;
                currentNode = currentNode->next;
            }
        }
    }
    return maximum-minimum;
}


