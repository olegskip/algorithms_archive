/*
 * Quicksort
 * Θ(n^2) - the worst case, O(n lg) - the average case
 * Watched Pavel Mavrin E03 S01 and read clrs the 7th chapter
 * The main idea is to choose a pivot and we should make all x in A[0 ... p - 1] be x <= A[p] and all x in A[p + 1 ... n] be x >= A[p],
 * where p is the index of the pivot, n is the size of the array A,
 * then recursively use the same method to A[0 ... p - 1] and A[p + 1 ... n], until there is only one element left.
 * This implementation uses a random number as an index for the pivot, but there are another ways to choose it,
 * e.g. we can use the first or the last element or use some special techniques like dividing the array into the small ones(recommended 4-5, more is useless)
 * then find the medians of the small arrays and find the median of the medians and use it as a pivot.
*/

#include <iostream>
#include <random>
#include <ctime>

// Returns a random number lies at [minNumber, maxNumber]
int getRandomNumber(int minNumber, int maxNumber)
{
	static std::random_device rd;
	static std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(minNumber, maxNumber);
	return uni(rng);
}

std::string printVector(const std::vector<int> &vec)
{
	std::string str = "";
	for(int item: vec) {
		str += std::to_string(item) + " ";
	}
	str += "\n";
	return str;
}

void quickSort(std::vector<int> &vec, int left, int right)
{
	if(right <= left)
		return;

	const int randomNumber = getRandomNumber(left, right);
	const int pivotNumber = vec[randomNumber];

	// Indicating the index where to put an element that <= pivotNumber
	int lesserGreaterBorder = left;

	// It's convenient to put the pivotNumber at the end, in order to put it in the correct position in the end
	std::swap(vec[randomNumber], vec[right]);
	for(int i = left; i < right; ++i) {
		if(vec[i] < pivotNumber)
			std::swap(vec[lesserGreaterBorder++], vec[i]);
	}

	std::swap(vec[right], vec[lesserGreaterBorder]);
	quickSort(vec, 0, lesserGreaterBorder - 1);
	quickSort(vec, lesserGreaterBorder + 1, right);
}

int main()
{
	std::ios::sync_with_stdio(0);
	std::srand(std::time(NULL));

	std::vector<int> vec = {1, 2, 1, 1, 1, 1, 4 , 4, 0, 3};
	quickSort(vec, 0, vec.size() - 1);

	std::cout << "Result = " << printVector(vec);

	return 0;
}
