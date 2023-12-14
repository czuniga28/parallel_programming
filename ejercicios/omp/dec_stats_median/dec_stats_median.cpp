// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
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
  double median = 0;  // median of the given numbers

  std::sort(numbers.begin(), numbers.end());

#pragma omp parallel for num_threads(thread_count)default(none) shared(numbers)\
reduction(min:minimum) reduction(max:maximum) reduction(+:average)\
reduction(+:stdDev) 
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
  std::cout << "Median: " << numbers[(numbers.size()/2) - 1] << std::endl;
  std::cout << "Standard Deviation: " << std << std::endl;

  return 0;
}


int main() {
  std::vector<double> numbers;
  int thread_count = omp_get_max_threads();
  std::cout << "Enter the numbers, ended Ctrl+D:" << std::endl;
  double number;
  while (std::cin >> number) {
    numbers.push_back(number);
  }
  if (numbers.size() == 0) {
    std::cout << "No numbers entered." << std::endl;
    return 0;
  }
  double minimum = numbers[0];
  double maximum = numbers[0];
  double average = 0;
  double stdDev = 0;
  double median = 0;
  std::sort(numbers.begin(), numbers.end());
#pragma omp parallel for num_threads(thread_count)default(none) shared(numbers)\
reduction(min:minimum) reduction(max:maximum) reduction(+:average)\
reduction(+:stdDev) 
  for (auto i = 0; i < numbers.size(); i++) {
    if (numbers[i] < minimum) {
        minimum = numbers[i];
    }
    if (numbers[i] > maximum) {
        maximum = numbers[i];
    }
    average += numbers[i]/numbers.size();
    stdDev += (numbers[i] - average) * (numbers[i] - average);
  }

  stdDev = std::sqrt(stdDev/(numbers.size()-1));
  std::cout << "Minimum: " << minimum << std::endl;
  std::cout << "Maximum: " << maximum << std::endl;
  std::cout << "Median: " << numbers[(numbers.size()/2) - 1] << std::endl;
  std::cout << "Average: " << average << std::endl;
  std::cout << "Standard Deviation: " << stdDev << std::endl;
  return 0;
}