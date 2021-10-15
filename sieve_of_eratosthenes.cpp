/*
 * The sieve of Eratosthenes
 * Time complexity is O(n(logn)(loglogn))
 * Finds all primes number up to the given number
 * The idea is to build an array of [1, number], then go step by step, erasing elements that is a multiple of the current number
 */

#include <iostream>
#include <vector>


std::vector<int> getPrimes(int number)
{
	std::vector<bool> sieve = std::vector<bool>(number, true);
	std::vector<int> primes;

	for(int i = 2; i < number; ++i) {
		if(sieve[i]) {
			primes.push_back(i);
			for(int j = i; j < number; j += i) {
				sieve[j] = false;
			}
		}
	}

	return primes;
}


int main()
{
	std::ios::sync_with_stdio(0);
	const auto test = getPrimes(30);

	return 0;
}
