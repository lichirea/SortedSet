#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>
#include <cassert>

using namespace std;

bool r500(TComp e1, TComp e2) {
    if (e1 <= e2) {
        return true;
    }
    else {
        return false;
    }
}

void customTest() {
    SortedSet s(r500);
    assert(s.getRange() == -1);
    s.add(1);
    s.add(6);
    s.add(-3);
    assert(s.getRange() == 9);
    s.add(10);
    assert(s.getRange() == 13);
    s.add(-5);
    assert(s.getRange() == 15);
    std::cout << "Test custom" << endl;
}

int main() {
	testAll();
	testAllExtended();
	customTest();

	cout << "Test end" << endl;
	system("pause");
}


