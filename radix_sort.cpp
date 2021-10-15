/*
 * Radix sort, time complexity is described below
 * Watched Pavel Mavrin S01E04
 * This sort can work without using the binary representation, but then the program has to find the max amount of digits(brute force?)
 * If the program uses the binary representation, there is more calls of functions to sort by a radix,
 * but the program doesn't have to count digits every time. In addition to get a single digit for a number is quite tedious
 * Time complexity is O(n + m), where m is constant and equal bits size, in this version of the program m = 32, since unsinged int is 32 bits
 * Though program uses templates, it can't handle with signed integers and floats, because it use the binary representation
 */


#include <iostream>
#include <vector>
#include <array>

template<class T>
void sortByCertainRadix(std::vector<T> &vec, size_t radix)
{
	std::vector<T> tempVector;
	tempVector.resize(vec.size());
	std::array<size_t, 2> counter = {0, 0};
	for(unsigned int item: vec)
		counter[item & radix]++;

	size_t lesserElementsIndex = 0, greaterElementsIndex  = counter[0];
	for(auto item: vec) {
		if(item & radix) 
			tempVector[greaterElementsIndex++] = item;
		else
			tempVector[lesserElementsIndex++] = item;
	}

	vec = tempVector;
}

template<class T>
void radixSort(std::vector<T> &vec)
{
	for(int i = 0; i < int(sizeof(T)); ++i) {
		sortByCertainRadix(vec, 1 << i);
	}
}

int main()
{
	std::vector<unsigned int> vec = {7, 1, 0, 8, 3, 9, 4, 2, 6, 5};
	radixSort(vec);

	return 0;
}
