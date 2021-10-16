/*
 * Heapsort, time complexity is O(n * log n)
 * Can be used to quickly get the max/min elements or sort the array
 * However the program sorts the array in the reversed order, but it can be easily reversed
 * Each parent node is strictly greater or less than its children
 * Although sieveUp and sieveDown are both O(log n), sieveDown is faster
 * To sort the binary heap, we gradually remove the root and build the heap until there is no elements left
 */


#include <iostream>
#include <vector>
#include <cmath>

template<class T, class Compare>
class BinaryHeap
{
public:
	BinaryHeap(std::initializer_list<T> elements)
	{
		container = elements;
		heapSize = elements.size();
		buildHeap();
	}

	void addElement(T element) // 
	{
		container.push_back(element);
		sieveUp(++heapSize - 1);
	}

	int getRootElement() // O(1)
	{
		if(container.empty())
			throw std::length_error("The heap is empty");

		return container[0];
	}

	void popRoot() // O(log n)
	{
		if(container.empty() || heapSize == 0)
			throw std::length_error("The heap is empty");

		std::swap(container[0], container[heapSize - 1]);
		container.pop_back();
		heapSize--;
		sieveDown(0);
	}

	void print()
	{
		std::string delim = "";
		for(T item: container) {
			std::cout << delim << item;
			delim = " ";
		}
		std::cout << "\n";
	}

	// sorts the array, but in the reversed order
	void sort() // O(n * log n)
	{
		const size_t initialHeapSize = heapSize;
		while(heapSize > 0) {
			std::swap(container[0], container[heapSize-- - 1]);
			sieveDown(0);
		}
		heapSize = initialHeapSize;
	}

private:
	void sieveDown(size_t index) // O(log n)
	{
		if(index > heapSize - 1)
			return;

		const size_t leftChildIndex = getLeftChildIndex(index), rightChildIndex = getRightChildIndex(index);

		if(leftChildIndex < heapSize && compare(container[leftChildIndex], container[index])
		   && (rightChildIndex >= heapSize || compare(container[leftChildIndex], container[rightChildIndex]))) {
			std::swap(container[index], container[leftChildIndex]);
			sieveDown(leftChildIndex);
		}
		else if(rightChildIndex < heapSize && compare(container[rightChildIndex], container[index])
			    && (leftChildIndex >= heapSize || compare(container[rightChildIndex], container[leftChildIndex]))) {
			std::swap(container[index], container[rightChildIndex]);
			sieveDown(rightChildIndex);
		}
	}

	void sieveUp(size_t index) // O(log n)
	{
		if(index > heapSize - 1)
			return;

		const size_t parentIndex = getParentIndex(index), leftChildIndex = getLeftChildIndex(parentIndex), rightChildIndex = getRightChildIndex(parentIndex);

		if(leftChildIndex < heapSize && compare(container[leftChildIndex], container[parentIndex])
		   && (rightChildIndex >= heapSize || compare(container[leftChildIndex], container[rightChildIndex]))) {
			std::swap(container[parentIndex], container[leftChildIndex]);
			sieveUp(parentIndex);
		}
		else if(rightChildIndex < heapSize && compare(container[rightChildIndex], container[parentIndex])
			    && (leftChildIndex >= heapSize || compare(container[rightChildIndex], container[leftChildIndex]))) {
			std::swap(container[parentIndex], container[rightChildIndex]);
			sieveUp(parentIndex);
		}
	}

	void buildHeap() // O(n)
	{
		const size_t lastNotLeaf = getLastNotLeaf();
		for(int i = lastNotLeaf; i >= 0; --i) {
			sieveDown(i);
		}
	}
	
	inline size_t getParentIndex(size_t index)
	{
		return std::floor((index - 1) / 2);
	}

	inline size_t getLeftChildIndex(size_t index)
	{
		return 2 * index + 1;
	}

	inline size_t getRightChildIndex(size_t index)
	{
		return 2 * index + 2;
	}

	inline size_t getLastNotLeaf()
	{
		return std::floor(heapSize / 2) - 1;
	}

public:
	std::vector<T> container;
	size_t heapSize = 0; // it can be different then the container size, because we can use it to sort elements from the heap
	Compare compare;
};


int main()
{
	BinaryHeap<int, std::greater<int>> binaryHeap({4, 1, 3, 2, 16, 9, 10, 14, 8, 7});
	binaryHeap.print();

	binaryHeap.addElement(17);
	binaryHeap.print();
	binaryHeap.addElement(0);
	binaryHeap.print();
	binaryHeap.addElement(17);
	binaryHeap.print();
	binaryHeap.sort();
	binaryHeap.print();

	return 0;
}