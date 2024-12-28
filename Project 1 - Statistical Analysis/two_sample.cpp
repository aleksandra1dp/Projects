/* two_sample.cpp
 * 
 * Performs a two sample analysis of data read from a .tsv file.
 * Usage:
 *   ./two_sample.exe filename filter_column filter_val_a filter_val_b data_column
 *
 * Data is read from filename, and filtered into two groups where the values
 * in filter_column are equal to filter_val_a and filter_val_b. Statistics are
 * printed for the corresponding data_column, including descriptive statistics
 * for groups A and B as well as a 95% confidence interval for the
 * difference in means between the two groups.
 */

#include "stats.hpp"
#include "p1_library.hpp"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

//REQUIRES: data contains at least 2 elements
//EFFECTS: Prints descriptive statistics for the given data
void print_descriptive_stats(vector<double> data) {
  int data_count = count(data);
  double data_sum = sum(data);
  double data_mean = mean(data);
  double data_median = median(data);
  double data_min= min(data);
  double data_max = max(data);
  double data_stedv = stdev(data);

  cout << "count = " << data_count <<endl;
  cout << "sum = " << data_sum <<endl;
  cout << "mean = " << data_mean <<endl;
  cout << "stdev = " << data_stedv <<endl;
  cout << "median = " << data_median <<endl;
  cout << "min = " << data_min <<endl;
  cout << "max = " << data_max <<endl;

  cout << "  0th percentile = " << percentile(data, 0.0) << endl;
  cout << " 25th percentile = " << percentile(data, 0.25) << endl;
  cout << " 50th percentile = " << percentile(data, 0.5) << endl;
  cout << " 75th percentile = " << percentile(data, 0.75) << endl;
  cout << "100th percentile = " << percentile(data, 1.0) << endl;
}

//REQUIRES: Nothing
//EFFECTS:  Returns an approximation of the sampling distribution of the
//          difference in means between groups A and B, represented as a
//          vector of the computed difference in means for 1000 bootstrap
//          resamples of original samples data_A and data_B.
vector<double> mean_diff_sampling_distribution(
  vector<double> data_A, vector<double> data_B) {
  // Create the mean difference vector and declare the iteration value.
  vector<double> mean_diff;
  double iterations = 1000.0;

  //Loop through the vector and perform the bootstrep resample function
  for (double i=0; i<iterations;++i){
    vector<double> resample_A = bootstrap_resample(data_A, i); 
    vector<double> resample_B = bootstrap_resample(data_B, i); 

    //Calculate the two mean and find their differnece
    double mean_A = mean(resample_A);
    double mean_B = mean(resample_B);

    mean_diff.push_back(mean_A - mean_B);

  }

  return mean_diff;
  
}

//REQUIRES: v is not empty
//          width is between 0 and 1, inclusive
//EFFECTS:  Returns a confidence interval for the data in v of the given
//          width, centered on the 50th percentile. The interval is represented
//          as a pair of upper and lower bounds. For example, the bounds on a
//          confidence interval with width 0.8 are the 10th and 90th percentiles.
pair<double, double> confidence_interval(vector<double> v, double width) {
  // Sort from lowest to highest for the values
  sort(v.begin(), v.end());

  // Upper and lower bounds calculation
  double lower_bound = (1.0-width)/2.0;
  double upper_bound = width+(1.0-width)/2.0;
  // Use the pecentile function to generate the lower and upper intervals
  double lower = percentile(v, lower_bound);
  double upper = percentile(v, upper_bound);
  // Return the interval
  return {lower, upper};
  

}

void two_sample_analysis(string file_name, string filter_column_name,
                         double filter_val_A, double filter_val_B,
                         string data_column_name) {

  // Extract data from the input file, removing rows with missing data.
  // filter_data and data have type vector<double>
  auto [filter_data, data] = extract_columns(
    file_name, filter_column_name, data_column_name);
  
  // Filter data into groups A and B based on given criteria
  vector<double> data_A = filter(data, filter_data, filter_val_A);
  vector<double> data_B = filter(data, filter_data, filter_val_B);

  // Print descriptive statistics for group A
  cout << "Group A: " << data_column_name << " | " << filter_column_name
       << " = " << filter_val_A << endl;
  print_descriptive_stats(data_A);
  cout << endl;

  // Print descriptive statistics for group B
  cout << "Group B: " << data_column_name << " | " << filter_column_name
       << " = " << filter_val_B << endl;
  print_descriptive_stats(data_B);
  cout << endl;

  // Use bootstrap resampling to approximate the sampling distribution of the
  // difference in means between groups A and B and compute a confidence interval.
  vector<double> mean_diffs = mean_diff_sampling_distribution(data_A, data_B);
  pair<double, double> ci_95 = confidence_interval(mean_diffs, 0.95);

  // Print confidence interval for the difference in means
  cout << "Confidence interval for mean(" << data_column_name
       << " | A) - mean(" << data_column_name << " | B):" << endl;
  cout << "  95% [" << ci_95.first << ", " << ci_95.second  << "]" << endl;
}

int main(int argc, char **argv) {
  if (argc == 1) {
    // No command-line arguments, use default values for cats.csv sample data
    two_sample_analysis("cats.csv", "food", 1, 2, "weight");
  }
  else if (argc == 6) {
    // Use custom values from command-line arguments
    two_sample_analysis(argv[1], argv[2], stod(argv[3]), stod(argv[4]), argv[5]);
  }
  else {
    cout << "Error: requires exactly zero or five command-line arguments." << endl
         << "Usage:" << endl
         << "  ./two_sample.exe" << endl
         << "  ./two_sample.exe file_name filter_column_name "
         << "filter_val_a filter_val_b data_column_name" << endl;
    return 1;
  }
}