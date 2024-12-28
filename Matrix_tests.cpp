#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

TEST(test_init){
  Matrix mat;
  const int width = 9;
  const int height = 3;
  Matrix_init(&mat, width, height);

  ASSERT_EQUAL(Matrix_width(&mat), width);
  ASSERT_EQUAL(Matrix_height(&mat), height);


  for(int i = 0; i < height; ++i){
    for(int j = 0; j < width; ++j){
      ASSERT_EQUAL(*Matrix_at(&mat, i, j), 0);
    }
  }
}

TEST(test_init_small) {
  Matrix mat;
  const int width = 1;
  const int height = 1;
  Matrix_init(&mat, width, height);
  
  ASSERT_EQUAL(Matrix_width(&mat), 1);
  ASSERT_EQUAL(Matrix_height(&mat), 1);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 0);
}

TEST(test_init_large) {
  Matrix mat;
  const int width = 10;
  const int height = 10;
  Matrix_init(&mat, width, height);
  
  ASSERT_EQUAL(Matrix_width(&mat), 10);
  ASSERT_EQUAL(Matrix_height(&mat), 10);

  for (int i = 0; i < Matrix_height(&mat); ++i) {
    for (int j = 0; j < Matrix_width(&mat); ++j) {
      ASSERT_EQUAL(*Matrix_at(&mat, i, j), 0);
    }
  }
}


TEST(test_print){
  Matrix mat;
  const int width = 2;
  const int height = 2;
  Matrix_init(&mat, width, height);

  *Matrix_at(&mat, 0, 0)=2;
  *Matrix_at(&mat, 0, 1)=5;
  *Matrix_at(&mat, 1, 0)=3;
  *Matrix_at(&mat, 1, 1)=6;

  string values = "2 2\n2 5 \n3 6 \n";

  ostringstream stream;
  Matrix_print(&mat, stream);
  // str converts stringstream to string
  ASSERT_EQUAL(stream.str(), values);
}


TEST(test_widtht) {
  Matrix mat;
  const int width = 7;
  const int height = 5;
  Matrix_init(&mat, width, height);
  ASSERT_EQUAL(Matrix_width(&mat), 7);
}

TEST(test_height) {
  Matrix mat;
  const int width = 7;
  const int height = 5;
  Matrix_init(&mat, width, height);
  ASSERT_EQUAL(Matrix_height(&mat), 5);
}

TEST(test_at){
  Matrix mat;
  const int width = 2;
  const int height = 2;
  Matrix_init(&mat, width, height); 
  
  *Matrix_at(&mat, 0 ,0) = 1;
  *Matrix_at(&mat, 0, 1) = 2;
  *Matrix_at(&mat, 1, 0) = 5;
  *Matrix_at(&mat, 1, 1) = 6;
  ASSERT_TRUE(*Matrix_at(&mat,1,1) == 6) ;
}

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}

TEST(test_fill_large_value) {
  Matrix mat;
  const int width = 3;
  const int height = 3;
  Matrix_init(&mat, width, height);
  Matrix_fill(&mat, 1000);
  
  for (int i = 0; i < Matrix_height(&mat); ++i) {
    for (int j = 0; j < Matrix_width(&mat); ++j) {
      ASSERT_EQUAL(*Matrix_at(&mat, i, j), 1000);
    }
  }
}

TEST(test_fill_zero) {
  Matrix mat;
  const int width = 5;
  const int height = 5;
  Matrix_init(&mat, width, height);
  Matrix_fill(&mat, 0);
  
  for (int i = 0; i < Matrix_height(&mat); ++i) {
    for (int j = 0; j < Matrix_width(&mat); ++j) {
      ASSERT_EQUAL(*Matrix_at(&mat, i, j), 0);
    }
  }
}

TEST(test_fill_border) {
  Matrix mat1;
  const int width = 5;
  const int height = 5;
  const int value = 16;
  Matrix_init(&mat1, width, height);
  Matrix_fill(&mat1, value);
  Matrix_fill_border(&mat1, 12);

  for (int i=0; i< height; ++i){
    ASSERT_EQUAL(*Matrix_at(&mat1,i,0), 12);
    ASSERT_EQUAL(*Matrix_at(&mat1,i,height-1), 12);
  }
  for (int j=0; j< width; ++j){
    ASSERT_EQUAL(*Matrix_at(&mat1,0,j), 12);
    ASSERT_EQUAL(*Matrix_at(&mat1,width-1, j), 12);
  }
  for(int i = 1; i < height-1; ++i){
    for(int j= 1; j < width-1; ++j){
      ASSERT_EQUAL(*Matrix_at(&mat1,i,j), 16);
    }
  }
}


TEST(test_fill_border_1_row) {
  Matrix mat;
  const int width = 1;
  const int height = 1;
  Matrix_init(&mat, width, height);
  Matrix_fill_border(&mat, 3);
  
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 3);
}


TEST(test_max){
  Matrix mat;
  const int width = 3;
  const int height = 4;
  const int value = 10;
  Matrix_init(&mat, width, height);
  Matrix_fill(&mat, value);
  *Matrix_at(&mat, 2, 2) = 67;

  ASSERT_TRUE(Matrix_max(&mat) == 67);

}

TEST(test_max_negative) {
  Matrix mat;
  const int width = 2;
  const int height = 2;
  Matrix_init(&mat, width, height);
  
  *Matrix_at(&mat, 0, 0) = -10;
  *Matrix_at(&mat, 0, 1) = -20;
  *Matrix_at(&mat, 1, 0) = -30;
  *Matrix_at(&mat, 1, 1) = -40;
  
  ASSERT_EQUAL(Matrix_max(&mat), -10);
}

TEST(test_max_mixed_values) {
  Matrix mat;
  const int width = 3;
  const int height = 3;
  
  Matrix_init(&mat, width, height);
  
  *Matrix_at(&mat, 0, 0) = 10;
  *Matrix_at(&mat, 0, 1) = -5;
  *Matrix_at(&mat, 1, 1) = 7;
  *Matrix_at(&mat, 2, 2) = 0;
  
  ASSERT_EQUAL(Matrix_max(&mat), 10);
}



TEST(test_column_of_min_value_in_row){
  Matrix mat;
  const int width = 6;
  const int height = 5;
  const int value = 11;
  Matrix_init(&mat, width, height);
  Matrix_fill(&mat, value);

  *Matrix_at(&mat, 1, 0) = 10;
  *Matrix_at(&mat, 1, 1) = 5;  
  *Matrix_at(&mat, 1, 2) = 15;
  *Matrix_at(&mat, 1, 3) = 20;
  *Matrix_at(&mat, 1, 4) = 30;

  ASSERT_TRUE(Matrix_column_of_min_value_in_row(&mat, 1,0, width) == 1);
}


TEST(test_column_of_min_value_in_row_1_column) {
  Matrix mat;
  const int width = 1;
  const int height = 3;
  Matrix_init(&mat, width, height);
    
  *Matrix_at(&mat, 2, 0) = 4; 
  *Matrix_at(&mat, 1, 0) = 2; 
  *Matrix_at(&mat, 0, 0) = 3;

  ASSERT_TRUE(Matrix_column_of_min_value_in_row(&mat, 1, 0, 1) == 0); 
}

TEST(test_column_of_min_value_in_row_all_equal) {
  Matrix mat;
  const int width = 4;
  const int height = 2;
  Matrix_init(&mat, width, height);
    
  for (int j = 0; j < width; ++j) {
    *Matrix_at(&mat, 0, j) = 7; 
  }

  ASSERT_TRUE(Matrix_column_of_min_value_in_row(&mat, 0, 0, width) == 0); 
}

TEST(test_column_of_min_value_in_row_negative_values) {
  Matrix mat;
  const int width = 4;
  const int height = 2;
  Matrix_init(&mat, width, height);
    
  *Matrix_at(&mat, 0, 0) = -1;
  *Matrix_at(&mat, 0, 1) = -5; 
  *Matrix_at(&mat, 0, 2) = 0;
  *Matrix_at(&mat, 0, 3) = 3;

  ASSERT_TRUE(Matrix_column_of_min_value_in_row(&mat, 0, 0, width) == 1); 
}

TEST(test_column_of_min_value_in_row_edge_case) {
 Matrix mat;
 const int width = 5;
 const int height = 1;
 Matrix_init(&mat, width, height);
 
 *Matrix_at(&mat, 0, 0) = 3;
 *Matrix_at(&mat, 0, 1) = 2; 
 *Matrix_at(&mat, 0, 2) = 1; 
 *Matrix_at(&mat, 0, 3) = 4;
 *Matrix_at(&mat, 0, 4) = 5;

 ASSERT_TRUE(Matrix_column_of_min_value_in_row(&mat, 0, 0, width) == 2);
 ASSERT_TRUE(Matrix_column_of_min_value_in_row(&mat, 0, 0, 3) == 2); 
}


TEST(test_min_value_in_row) {
 Matrix mat;
 const int width = 6;
 const int height = 5;
 Matrix_init(&mat, width, height);
 Matrix_fill(&mat, 11);

 *Matrix_at(&mat, 1, 0) = 10;
 *Matrix_at(&mat, 1, 1) = 5;  
 *Matrix_at(&mat, 1, 2) = 15;
 *Matrix_at(&mat, 1, 3) = 20;
 *Matrix_at(&mat, 1, 4) = 30;

 ASSERT_TRUE(Matrix_min_value_in_row(&mat, 1, 0, width) == 5);
}

TEST(test_min_value_in_row_1_column) {
 Matrix mat;
 const int width = 1;
 const int height = 3;
 Matrix_init(&mat, width, height);
 
 *Matrix_at(&mat, 2, 0) = 4; 
 *Matrix_at(&mat, 1, 0) = 2; 
 *Matrix_at(&mat, 0, 0) = 3;

 ASSERT_TRUE(Matrix_min_value_in_row(&mat, 1, 0, 1) == 2); 
}


TEST(test_min_value_in_row_negative_values) {
 Matrix mat;
 const int width = 4;
 const int height = 2;
 Matrix_init(&mat, width, height);
 
 *Matrix_at(&mat, 0, 0) = -1;
 *Matrix_at(&mat, 0, 1) = -5; 
 *Matrix_at(&mat, 0, 2) = 0;
 *Matrix_at(&mat, 0, 3) = 3;

 ASSERT_TRUE(Matrix_min_value_in_row(&mat, 0, 0, width) == -5); 
}

TEST(test_min_value_in_row_all_equal) {
 Matrix mat;
 const int width = 5;
 const int height = 1;
 Matrix_init(&mat, width, height);

 for (int i = 0; i < width; ++i) {
  *Matrix_at(&mat, 0, i) = 1; 
 }

 ASSERT_TRUE(Matrix_min_value_in_row(&mat, 0, 0, width) == 1); 
}

TEST(test_min_value_in_row_min_at_end) {
 Matrix mat;
 const int width = 4;
 const int height = 1;
 Matrix_init(&mat, width, height);

 *Matrix_at(&mat, 0, 0) = 10;
 *Matrix_at(&mat, 0, 1) = 20; 
 *Matrix_at(&mat, 0, 2) = 30;
 *Matrix_at(&mat, 0, 3) = 5; 

 ASSERT_TRUE(Matrix_min_value_in_row(&mat, 0, 0, width) == 5); 
}

TEST(test_min_value_in_row_edge_case) {
 Matrix mat;
 const int width = 5;
 const int height = 1;
 Matrix_init(&mat, width, height);
 
 *Matrix_at(&mat, 0, 0) = 3;
 *Matrix_at(&mat, 0, 1) = 2; 
 *Matrix_at(&mat, 0, 2) = 1; 
 *Matrix_at(&mat, 0, 3) = 4;
 *Matrix_at(&mat, 0, 4) = 5;

 ASSERT_TRUE(Matrix_min_value_in_row(&mat, 0, 0, width) == 1);
 ASSERT_TRUE(Matrix_min_value_in_row(&mat, 0, 0, 2) == 2); 
}

//TEST(test_small_matrix) {
//   Matrix mat3;
//   const int width = 1;
//   const int height = 1;
//   const int value = 1;
//   Matrix_init(&mat3, 1, 1);
//   Matrix_fill(&mat3, value);
//   *Matrix_at(&mat3, 0, 0) = 3;
//   ASSERT_TRUE(Matrix_small_matrix(&mat3, 0, 0, 3) == 0);
// }
// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.

TEST_MAIN() // Do NOT put a semicolon here
