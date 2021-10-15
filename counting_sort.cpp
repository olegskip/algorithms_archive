/*
 * Watched Pavel Mavrtin S01E03
 * The main idea is to count elements, using a vector and elements as its index)
 * and then just insert these elements in the correct correct a[number] times
 * Time complexity is O(n + m), where m is the max element
 * Works quick only for a relatively low numbers
 */


#include <iostream>
#include <vector>

void countingSort(std::vector<unsigned int> &vec)
{
	if(vec.empty())
		return;

	std::vector<size_t> counter;
    // We should to know tha max elemen in order to know the last element in vec
	unsigned int maxElement = vec[0];
	counter.resize(vec.size());
	for(int item: vec) {
		if(item > maxElement)
			maxElement = item;

		counter[item]++;
	}

	for(size_t i = 0, j = 0; i <= maxElement; ++i) {
		while(counter[i]-- > 0)
			vec[j++] = i;
	}

}

int main()
{
	std::ios::sync_with_stdio(0);

	std::vector<unsigned int> vec = {1, 1, 0, 2, 1, 2, 1, 2, 0};
	countingSort(vec);

	return 0;
}
