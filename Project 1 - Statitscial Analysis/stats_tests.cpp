/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.hpp"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
using namespace std;

//Declare the test cases
void test_sum_small_data_set();
void test_sum_empty();
void test_sum_single_element();
void test_sum_fractional_elements();
void test_sum_large_data_set();
void test_sum_negative_elements();

void test_mean_simple();
void test_mean_empty();
void test_mean_large_data_set();
void test_mean_mixed_values();
void test_mean_negative();

void test_median_odd();
void test_median_even();
void test_median_empty(); 
void test_median_unsorted_data();
void test_median_large_data_set();

void test_min_max();
void test_min_empty();
void test_max_empty(); 
void test_min_max_large_values();

void test_stdev();
void test_stdev_empty();
void test_stdev_negative();

void test_percentile();
void test_percentile_large_data_set();
void test_percentile_fractional_data();

void test_filter_simple();
void test_filter_no_match();
void test_filter_no_target();

int main() {
  //Run the test cases
  test_sum_small_data_set();
  test_sum_empty();
  test_sum_single_element();
  test_sum_fractional_elements();
  test_sum_large_data_set();
  test_sum_negative_elements();

  test_mean_simple();
  test_mean_empty();
  test_mean_large_data_set();
  test_mean_mixed_values();
  test_mean_negative();

  test_median_odd();
  test_median_even();
  test_median_empty() ;
  test_median_unsorted_data();
  test_median_large_data_set();

  test_min_max();
  test_min_empty();
  test_max_empty(); 
  test_min_max_large_values();

  test_stdev();
  test_stdev_empty();
  test_stdev_negative();

  test_percentile();
  test_percentile_large_data_set();
  test_percentile_fractional_data();

  test_filter_simple();
  test_filter_no_match();
  test_filter_no_target();

  return 0;
}

//Set the tolerance
double tolerance = 0.00001; 

void test_sum_small_data_set() {
  cout << "test_sum_small_data_set" << endl;
// add the numbers to the vector to get a sum and check if the "sum" function yields the same value
  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(sum(data) == 6);

  cout << "PASS!" << endl;
}

void test_sum_empty() {
  cout << "test_sum_empty" << endl;
  //Check if the sum of an empty vector is 0;
  vector<double> v;
  assert(sum(v) == 0);
  cout << "PASS!" << endl;
}

void test_sum_single_element() {
  cout << "test_sum_single_element" << endl;
  vector<double> v = {5};  
  cout << "PASS!" << endl;
}

void test_sum_fractional_elements() {
  cout << "test_sum_fractional_elements" << endl;
  //Compare the difference in expected and produced sum to the tolerance
  vector<double> v = {1.5, 2.8, 3.4, 4.1, 5.05};
  double expected_sum = 16.85;
  assert(abs(sum(v) - expected_sum) < tolerance); 
  cout << "PASS!" << endl;
}

void test_sum_large_data_set() {
  cout << "test_sum_large_data_set" << endl;
  
  vector<double> v(1000, 1); 
  assert(sum(v) == 1000);

  cout << "PASS!" << endl;
}

void test_sum_negative_elements() {
  cout << "test_sum_negative_elements" << endl;

  vector<double> data = {-10, -20, -30, 10};
  assert(sum(data) == -50);

  cout << "PASS!" << endl;
}

void test_mean_simple() {
  cout << "test_mean_simple" << endl;
  vector<double> data = {1, 2, 3, 4, 5};
  double expected_mean = 3.0;
  assert(abs(mean(data) - expected_mean) < tolerance); 
  cout << "PASS!" << endl;
}
void test_mean_empty() {
  cout << "test_mean_empty" << endl;

  vector<double> v;
  assert(mean(v) == 0);
  cout << "PASS!" << endl;
}

void test_mean_large_data_set() {
  cout << "test_mean_large_data_set" << endl;

  vector<double> data(10000, 5.0);  
  double expected_mean = 5.0;
  assert(abs(mean(data) - expected_mean) < tolerance);

  cout << "PASS!" << endl;
}

void test_mean_mixed_values() {
  cout << "test_mean_mixed_values" << endl;

  vector<double> data = {100, -100, 50, -50, 25, -25, 0};
  double expected_mean = 0.0;
  assert(abs(mean(data) - expected_mean) < tolerance);

  cout << "PASS!" << endl;
}

void test_mean_negative() {
  cout << "test_mean_negative" << endl;

  vector<double> data = {-100, -75, -50, -10, -25, -75};
  double expected_mean = -55.8333333;
  assert(abs(mean(data) - expected_mean) < tolerance);

  cout << "PASS!" << endl;
}

void test_median_odd() {
  cout << "test_median_odd" << endl;
  vector<double> data = {1, 2, 3, 4, 5};
  double expected_median = 3.0;
  assert(abs(median(data) - expected_median) < tolerance);
  cout << "PASS!" << endl;
}

void test_median_even() {
  cout << "test_median_even" << endl;
  vector<double> data = {1, 2, 3, 4};
  double expected_median = 2.5;
  assert(abs(median(data) - expected_median) < tolerance);
  cout << "PASS!" << endl;
}

void test_median_empty() {
  cout << "test_median_empty" << endl;
  vector<double> v;
  assert(median(v) == 0);
  cout << "PASS!" << endl;
}

void test_median_unsorted_data() {
  cout << "test_median_unsorted_data" << endl;

  vector<double> data = {5, 1, 3, 4, 2};
  double expected_median = 3.0;  
  assert(abs(median(data) - expected_median) < tolerance);

  cout << "PASS!" << endl;
}

void test_median_large_data_set() {
  cout << "test_median_large_data_set" << endl;

  vector<double> data(10001, 5.0);  
  data[5000] = 10.0;  
  double expected_median = 5.0;
  assert(abs(median(data) - expected_median) < tolerance);

  cout << "PASS!" << endl;
}

void test_min_max() {
  cout << "test_min_max" << endl;
  vector<double> data = {-1, 100, 5, 10};
  assert(min(data) == -1);
  assert(max(data) == 100);
  cout << "PASS!" << endl;
}

void test_min_max_large_values() {
  cout << "test_min_max_large_values" << endl;

  vector<double> data = {numeric_limits<double>::max(), numeric_limits<double>::lowest(), 0};
  assert(min(data) == numeric_limits<double>::lowest());
  assert(max(data) == numeric_limits<double>::max());

  cout << "PASS!" << endl;
}

void test_min_empty() {
  cout << "test_min_empty" << endl;
  vector<double> v;
  assert(min(v) == 0);
  cout << "PASS!" << endl;
}

void test_max_empty() {
  cout << "test_max_empty" << endl;
  vector<double> v;
  assert(max(v) == 0);
  cout << "PASS!" << endl;
}

void test_stdev() {
  cout << "test_stdev" << endl;
  vector<double> data = {1, 2, 3, 4, 5};
  double expected_stdv = 1.58114;
  assert(abs(stdev(data) - expected_stdv) < tolerance);  
  cout << "PASS!" << endl;
}

void test_stdev_empty() {
  cout << "test_stdev_empty" << endl;

  vector<double> v;
  assert(stdev(v) == 0);
  cout << "PASS!" << endl;
}

void test_stdev_negative() {
  cout << "test_stdev_negative" << endl;
  vector<double> data = {100, -100, 50, -50, 25};
  double expected_stdv =  79.843597113357;
  assert(abs(stdev(data) - expected_stdv) < tolerance);  
  cout << "PASS!" << endl;
}

void test_percentile() {
  cout << "test_percentile" << endl;
  vector<double> data = {1, 2, 3, 4, 5};
    
  double expected_perc_0 = 1.0;
  double expected_perc_25 = 2.0;
  double expected_perc_50 = 3.0;
  double expected_perc_75 = 4.0;
  double expected_perc_100 = 5.0;
  assert(abs(percentile(data, 0) - expected_perc_0) < tolerance);
  assert(abs(percentile(data, 0.25) - expected_perc_25) < tolerance); 
  assert(abs(percentile(data, 0.5) - expected_perc_50) < tolerance);  
  assert(abs(percentile(data, 0.75) - expected_perc_75) < tolerance); 
  assert(abs(percentile(data, 1) - expected_perc_100) < tolerance);
  cout << "PASS!" << endl;
}

void test_percentile_large_data_set() {
  cout << "test_percentile_large_data_set" << endl;

  vector<double> data(10000);
  for (int i = 0; i < 10000; ++i) {
    data[i] = i; 
  }
  double expected_perc_50 = 4999.5; 
  assert(abs(percentile(data, 0.5) - expected_perc_50) < 1);

  cout << "PASS!" << endl;
}

void test_percentile_fractional_data() {
  cout << "test_percentile_fractional_data" << endl;

  vector<double> data = {1.5, 2.3, 3.7, 4.2, 5.9};
    
  double expected_perc_0 = 1.5;
  double expected_perc_25 = 2.3;
  double expected_perc_50 = 3.7;
  double expected_perc_75 = 4.2;
  double expected_perc_100 = 5.9;
    
  assert(abs(percentile(data, 0) - expected_perc_0) < tolerance);
  assert(abs(percentile(data, 0.25) - expected_perc_25) < tolerance);
  assert(abs(percentile(data, 0.5) - expected_perc_50) < tolerance);
  assert(abs(percentile(data, 0.75) - expected_perc_75) < tolerance);
  assert(abs(percentile(data, 1) - expected_perc_100) < tolerance);
    
  cout << "PASS!" << endl;
}

void test_filter_simple(){
  cout << "test_filter_simple_case" << endl;
  
  //Create a test vector and criteria vector  and match the target value in the criteria to the test vector value
  vector<double> v = {1, 2, 3, 4, 5};
  vector<double> criteria = {0, 1, 0, 1, 0};
  double target = 1;
  vector<double> expected = {2, 4};
    
  vector<double> result = filter(v, criteria, target);
  assert(result == expected);
    
  cout << "PASS!" << endl;
}

void test_filter_no_match() {
  cout << "test_filter_no_match" << endl;
  
  vector<double> v = {4, 2, 3};
  vector<double> criteria = {1, 1, 1};
  double target = 0;
  vector<double> expected = {};
    
  vector<double> result = filter(v, criteria, target);
  assert(result == expected);
    
  cout << "PASS!" << endl;
}

void test_filter_empty_vectors() {
  cout << "test_filter_empty_vectors" << endl;
    
  vector<double> v = {};
  vector<double> criteria = {};
  double target = 1;
  vector<double> expected = {};
    
  vector<double> result = filter(v, criteria, target);
  assert(result == expected);
    
  cout << "PASS!" << endl;
}

void test_filter_no_target() {
  cout << "test_filter_no_target" << endl;
    
  vector<double> v = {11, 12, 13};
  vector<double> criteria = {2, 2, 2};
  double target = 1;
  vector<double> expected = {};
    
  vector<double> result = filter(v, criteria, target);
  assert(result == expected);
    
  cout << "PASS!" << endl;
}
