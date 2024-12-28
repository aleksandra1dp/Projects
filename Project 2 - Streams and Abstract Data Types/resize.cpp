#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include "Image.hpp"
#include "Matrix.hpp"
#include "processing.hpp"
#include "jpeg.hpp"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 4 && argc != 5) {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    return 1;
  }

  string input_filename = argv[1];
  string output_filename = argv[2];
  int new_width = stoi(argv[3]);
  int new_height;
  if(argc == 5) {
    new_height = stoi(argv[4]);
  } else {
    new_height = -1;
  }

  Image img;
  ifstream input_file(input_filename);
  if (!input_file.is_open()) {
    cout << "Error opening file: " << input_filename << endl;
    return 1;  
  }
  Image_init(&img, input_file);
  input_file.close();

  seam_carve(&img, new_width, new_height);

  int og_width = Image_width(&img);
  int og_height = Image_height(&img);

  if (new_width <= 0 || new_width > og_width) {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    return 1;
  } 

  if (new_height != -1 && (new_height <= 0 || new_height > og_height)) {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
     return 1;
  }
  ofstream output_file(output_filename);
  if (!output_file.is_open()) {
    cout << "Error opening file: " << output_filename << endl;
    return 1;  
  }
  Image_print(&img, output_file);
  output_file.close();


  return 0;
}