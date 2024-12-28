#include <cassert>
#include <vector>
#include "processing.hpp"

using namespace std;

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_left is provided for you.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image aux;
  Image_init(&aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_right is provided for you.
// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img){

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image aux;
  Image_init(&aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// v DO NOT CHANGE v ------------------------------------------------
// The implementation of diff2 is provided for you.
static int squared_difference(Pixel p1, Pixel p2) {
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows
  // later on in the algorithm.
  return (dr*dr + dg*dg + db*db) / 100;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// ------------------------------------------------------------------
// You may change code below this line!



// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
void compute_energy_matrix(const Image* img, Matrix* energy) {
  int width = Image_width(img);
  int height = Image_height(img);
  Matrix_init(energy, width, height);
  Matrix_fill(energy, 0);

  for(int i = 1;  i< height-1; ++i) { 
    for(int j = 1; j < width-1; ++j) {
      Pixel NorthPixel, SouthPixel, EastPixel, WestPixel;
      NorthPixel = Image_get_pixel(img, i - 1, j);
      SouthPixel = Image_get_pixel(img, i + 1, j);
      EastPixel = Image_get_pixel(img, i, j + 1);
      WestPixel = Image_get_pixel(img, i, j - 1);

      int energy_total = squared_difference(NorthPixel, SouthPixel) 
      + squared_difference(WestPixel, EastPixel);
      *Matrix_at(energy, i, j) = energy_total;

    }
  }
   int max_energy = Matrix_max(energy);
   Matrix_fill_border(energy, max_energy);
}


// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
void compute_vertical_cost_matrix(const Matrix* energy, Matrix *cost) {
  assert(energy);
  assert(cost);
  assert(energy != cost);
  
  int width = Matrix_width(energy);
  int height = Matrix_height(energy);
  assert(width > 0 && height > 0);
  Matrix_init(cost, width, height);
  Matrix_fill(cost,0);

  for(int j = 0; j < width; ++j) {
    *Matrix_at(cost, 0, j) = *Matrix_at(energy, 0, j);
  }
  

  for (int i = 1; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      int left_col, right_col;

            
    if (j == 0) {
      left_col = j;  //leftmost column
    } else {
      left_col = j - 1;  // not leftmost, is able to move left
    }

            
    if (j == width - 1) {
      right_col = j;  //rightmost column
    } else {
      right_col = j + 1;  //  not rightmost, is able to move right
    }
      
    int min_cost= Matrix_min_value_in_row(cost, i - 1, left_col, right_col+1);
    *Matrix_at(cost, i, j) = *Matrix_at(energy, i, j) + min_cost;
    }
  }

}


// REQUIRES: cost points to a valid Matrix
// EFFECTS:  Returns the vertical seam with the minimal cost according to the given
//           cost matrix, represented as a vector filled with the column numbers for
//           each pixel along the seam, starting with the lowest numbered row (top
//           of image) and progressing to the highest (bottom of image). The length
//           of the returned vector is equal to Matrix_height(cost).
//           While determining the seam, if any pixels tie for lowest cost, the
//           leftmost one (i.e. with the lowest column number) is used.
//           See the project spec for details on computing the minimal seam.
vector<int> find_minimal_vertical_seam(const Matrix* cost) {
  assert(cost);
  int height = Matrix_height(cost);
  int width = Matrix_width(cost);
  assert(width > 0 && height > 0);

  //Vector filled with column numbers, so need to be of height size
  vector<int> seam(height);
  //Subtract 1 from height and weight to account for the difference between index 
  //value and actual row/column number
  int min_bottom = Matrix_column_of_min_value_in_row(cost, height-1, 0 ,width-1);
  seam[height - 1] = min_bottom;

    for (int i = height - 2; i >= 0; --i) {
      int left_col;
      int right_col;
        if (min_bottom - 1 < 0) {
            left_col = 0; // out of bound
        } else {
            left_col = min_bottom - 1;
        }

        if (min_bottom + 1 >= width) {
            right_col = width - 1; // out of bound
        } else {
            right_col = min_bottom + 1;
        }
        min_bottom = Matrix_column_of_min_value_in_row(cost, i, left_col, right_col + 1);
        seam[i] = min_bottom;
    }

    return seam;
}



// REQUIRES: img points to a valid Image with width >= 2
//           seam.size() == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Declare a new variable to hold the smaller Image, and
//           then do an assignment at the end to copy it back into the
//           original image.
void remove_vertical_seam(Image *img, const vector<int> &seam) {
  assert(img);
  assert(Image_width(img)>=2);
  assert(static_cast<int>(seam.size())==Image_height(img));

  for(int i = 0; i < Image_height(img); ++i){
    assert(0 <= seam.at(i)&& seam.at(i)< Image_width(img));
  }

  Image smaller_img;
  Image_init(&smaller_img, Image_width(img)-1, Image_height(img));

  for(int i = 0; i < Image_height(img); ++i){
    for(int j = 0; j < Image_width(img); ++j) {
      Pixel color= Image_get_pixel(img, i, j);
      if(j<seam.at(i)){
        Image_set_pixel(&smaller_img, i, j, color);
      }else if(j>seam.at(i)){
          Image_set_pixel(&smaller_img, i, j-1, color);
        }
      }
    }
  *img = smaller_img;
}


// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
// NOTE:     Use a vector to hold the seam, and make sure that it has
//           the right size. You can use .data() on a vector to get
//           the underlying array.
void seam_carve_width(Image *img, int newWidth) {
  assert(img);
  assert(0 < newWidth && newWidth <= Image_width(img));

  while(Image_width(img)>newWidth){
    Matrix energy;
    compute_energy_matrix(img, &energy);

    Matrix cost;
    compute_vertical_cost_matrix(&energy, &cost);

    vector<int> seam=find_minimal_vertical_seam(&cost);
    remove_vertical_seam(img, seam);
  }
}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image *img, int newHeight) {
  assert(img);
  assert(0 < newHeight && newHeight <= Image_height(img));

  rotate_left(img);
  seam_carve_width(img, newHeight);
  rotate_right(img);
}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image *img, int newWidth, int newHeight) {
  assert(img);
  assert(0 < newWidth && newWidth <= Image_width(img));
  assert(0 < newHeight && newHeight <= Image_height(img));

  seam_carve_width(img, newWidth);
  seam_carve_height(img, newHeight);
}
