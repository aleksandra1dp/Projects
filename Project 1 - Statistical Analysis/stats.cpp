// stats.cpp
#include "stats.hpp"
#include <cassert>
#include <vector>
#include <algorithm> // sort
#include <cmath> // sqrt, modf
#include <iostream>

using namespace std;

int count(vector<double> v) {
  //Check if the vector is emppty before preceding
  if (v.empty()){
    return 0;
  }
  //Find the size of the vector, aka how many values the vector contains
  int data_size = v.size();
  //Return the generated value
  return data_size;
}

double sum(vector<double> v) {
  if (v.empty()){
    return 0;
  }
  //Initialize the variable to 0
  double data_sum = 0;
  //Loop through the whole vector adding each value to the pre-initialized double variable
  for (size_t i = 0;i < v.size(); ++i){
    data_sum += v.at(i);
  }
  return data_sum;
}

double mean(vector<double> v) {
  if (v.empty()){
    return 0;
  }
  //Use the functions created beforehand to find the mean value by following the mean equation
  double data_mean = sum(v) / v.size();
  return data_mean;
}

double median(vector<double> v) {
  if (v.empty()){
    return 0;
  }
  //Sort the vector in descending order
  sort(v.begin(), v.end());
  //Use the count function to create a size variable. Initialize a median variable.
  int data_size = count(v);
  double data_median=0.0;

  //Produce the middle value for the median if the number of values in the vector is odd and find
  //the average of the two middle values if it is even
  if (data_size % 2 != 0) {
    data_median = v.at(data_size / 2);
  } else {
    data_median = (v.at((data_size - 1) / 2) + v.at(data_size / 2)) / 2.0;
  }
  return data_median;
}

double min(vector<double> v) {
  if (v.empty()){
    return 0;
  }
  //Initialize the min at the first index
  double data_min = v.at(0);
  //Loop through the whole vector 
  for (size_t i=0; i < v.size(); ++i){
    //If the value at the following index is smaller than the current one, replace the current min
    //with that new value
    if(v.at(i) < data_min) {
      data_min = v.at(i);
    }
  }
  return data_min;
}

double max(vector<double> v) {
  if (v.empty()){
    return 0;
  }
  double data_max = v.at(0);
  for (size_t i=0; i < v.size(); ++i){
    //If the value at the following index is larger than the current one, replace the current max
    //with that new value
    if(v.at(i) > data_max) {
      data_max= v.at(i);
    }
  }
  return data_max;
}

double stdev(vector<double> v) {
  if (v.empty()){
    return 0;
  }
  // Initialize the stdev at 0 and calculate the mean for the vector 
  double stdev_index  = 0;
  double data_mean = mean(v);

  for(size_t i = 0; i < v.size(); ++i){
    //Find each value in the value and incorporate it into the equation
    stdev_index +=  pow(v.at(i)-data_mean, 2.0);
  }
  //Finish the remainder of the stdev equation
  double data_stdv = sqrt(stdev_index / (v.size()-1));
  return data_stdv;
}

double percentile(vector<double> v, double p) {
  sort(v.begin(), v.end());
  double n = v.size();
  if (v.size() < 2) {
    return 0.0;
  }
  
  //Check for edge cases
  if (p==1.0){
    return v.at(n-1);
  }
  if (p==0.0){
    return v.at(0);
  }
  //Check if the percentile is within bounds
  if (p>1.0){
    return 0.0;
  }
  //Write out the percentile equation accounting for indexing
  double data_rank = p * (n - 1);
  double intpart = 0.0;
  double fractpart = modf(data_rank, &intpart);
  //Check if the the fractional and the integer parts are within bounds
  if (fractpart >= 1.0){
    return 0.0;
  }
  if (intpart > n){
    return 0.0;
  }
  //Input the values found previously into the percentile equation
  double data_percent = v.at(intpart) + fractpart*(v.at(intpart+1)-v.at(intpart));

  return data_percent;
}

vector<double> filter(vector<double> v,
                      vector<double> criteria,
                      double target) {
  //Ensure that both of the vectors are the same size so that the function won't crush                   
  assert(v.size() == criteria.size());

  vector<double> result_data;

  for (size_t i = 0; i < criteria.size(); ++i) {
    //Check where the criteria has the target value and add that to the vector
    if (criteria.at(i) == target) {
      result_data.push_back(v.at(i));
    }
  }

  return result_data;
}
