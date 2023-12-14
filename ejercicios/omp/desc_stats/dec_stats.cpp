// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

int main() {
  std::vector<double> numbers;  // given array of numbers
  std::cout << "Enter the numbers, ended Ctrl+D:" << std::endl;
  int thread_count = omp_get_max_threads();  // max num of threads of the user
  double number;

  while (std::cin >> number) {
    numbers.push_back(number);  // allocates the numbers on the vector
  }

  if (numbers.size() == 0) {
    std::cout << "No numbers entered." << std::endl;
    return 0;
  }

  double min = numbers[0];  // minimun of the given numbers
  double max = numbers[0];  // maximun of the given numbers
  double avg = 0;  // average of the given numbers
  double std = 0;  // standard deviation of the given numbers

#pragma omp parallel for num_threads(thread_count)default(none) shared(numbers)\
 reduction(min:minimum) reduction(max:maximum) reduction(+:average) \
 reduction(+:standardDeviation) 
//  parallel region
  for (auto i = 0; i < numbers.size(); i++) {
    if (numbers[i] < min) {
      min = numbers[i];  // iterates the vector refreshing the min found
    }
    if (numbers[i] > max) {
      max = numbers[i];  // iterates the vector refreshing the mmax found
    }
    avg += numbers[i]/numbers.size();  // calculares the average
    std += (numbers[i] - avg) * (numbers[i] - avg);
  }
// end parallel region
std = std::sqrt(std/(numbers.size()-1));

std::cout << "Minimum: " << min << std::endl;
std::cout << "Maximum: " << max << std::endl;
std::cout << "Average: " << avg << std::endl;
std::cout << "Standard Deviation: " << std << std::endl;

return 0;
}
