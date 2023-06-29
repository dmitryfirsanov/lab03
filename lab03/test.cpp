#include <cassert>
#include "lab03.h"
using namespace std;

void test_minmax() {
	vector<double> numbers{ 1,2,3 };
	auto [min, max] = find_minmax(numbers);

	assert(min == 1);
	assert(max == 3);
}

void test_allnegative() {
	bool all_negative = true;
	vector <int> numbers{ -1,-2,-3 };

	for (auto i = 0; i < numbers.size(); i++) {
		if (numbers[i] >= 0) {
			all_negative = false;
			break;
		}
	}

	assert(all_negative == true);
}

void test_allsame() {
	bool all_same = true;
	vector <int> numbers{ 1,1,1 };
	int temp = numbers[0];
	for (auto i = 0; i < numbers.size(); i++) {
		if (numbers[i] != temp) {
			all_same = false;
			break;
		}
	}
	assert(all_same == true);
}

void test_onenum() {
	vector <int> numbers;
	numbers.push_back(1);
	if (numbers.size() > 0) assert(numbers.size() == 1);
}

void test_emptyarr() {
	bool empty = true;
	vector <int> numbers;

	if (numbers.size() > 0) {
		bool empty = false;
	}
	else assert(empty == true);
}

//int main() {
//	test_minmax();
//	test_allnegative();
//	test_allsame();
//	test_onenum();
//	test_emptyarr();
//}