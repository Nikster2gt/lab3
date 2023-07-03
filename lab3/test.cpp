#include "histogram.h"
#include <cassert>
void test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({ 1, 2, 3 }, min, max);
    assert(min == 1);
    assert(max == 3);
}

void test_negative() {
	double min = 0;
	double max = 0;
	vector <double> numbers{ -1,-2,-3 };
	find_minmax(numbers, min, max);
	assert(min == 0);
	assert(max == 0);
}

void test_odinak() {
	double min = 0;
	double max = 0;
	vector <double> numbers{ 10, 10, 10 };
	find_minmax(numbers, min, max);
	assert(min == 10);
	assert(max == 10);
}

void test_odno() {
	double min = 0;
	double max = 0;
	vector <double> numbers{ 5 };
	find_minmax(numbers, min, max);
	assert(min == max);
}

void test_pustoi() {
	double min = 0;
	double max = 0;
	vector <double> numbers{};
	find_minmax(numbers, min, max);
	assert(min == max);
}
//int main() {
//    test_positive();
//	test_negative();
//	test_odinak();
//	test_odno();
//	test_pustoi();
//}