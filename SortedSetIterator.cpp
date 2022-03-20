#include "SortedSetIterator.h"
#include <exception>
using namespace std;

//worst,best,total: O(length); this is always the same no matter how it is called
SortedSetIterator::SortedSetIterator(SortedSet& m) : s(m)
{
    this->values = new int[s.length];
	position = 0;
	for(int i = 0; i < s.m; i++){
	    if(s.T[i] != nullptr){
	        Node* currentNode = s.T[i];
	        while(currentNode != nullptr){
	            values[position] = currentNode->info;
	            position++;
	            currentNode = currentNode->next;
	        }
	    }
	}
    std::sort(values, values+s.length, s.TFunction);

	position = 0;
}

//worst,best,total: ϴ(1); this is always the same no matter how it is called
void SortedSetIterator::first() {
	position = 0;
}

//worst,best,total: ϴ(1); this is always the same no matter how it is called
void SortedSetIterator::next() {
    if(!this->valid()) throw std::exception("Iterator over");
    position++;
}

//worst,best,total: ϴ(1); this is always the same no matter how it is called
TElem SortedSetIterator::getCurrent()
{
    if(this->valid()) 	return values[position];
    throw std::exception("Iterator over");
}
//worst,best,total: ϴ(1); this is always the same no matter how it is called
bool SortedSetIterator::valid() const {
    if(position == s.length) return false;
    return true;
}

//worst,best,total: O(length); this is always the same no matter how it is called
SortedSetIterator::~SortedSetIterator() {
    delete[] this->values;
}

