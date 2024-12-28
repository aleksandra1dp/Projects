#include "Image.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


TEST(test_init1) {
  Image img;
  int width = 4;
  int height= 5;
  Image_init(&img, width, height); 

  ASSERT_EQUAL(Image_width(&img), width);
  ASSERT_EQUAL(Image_height(&img), height);

  for (int i = 0; i < Image_height(&img); ++i) {
    for (int j = 0; j < Image_width(&img); ++j) {
      ASSERT_EQUAL(Image_get_pixel(&img, i, j).r, 0);
      ASSERT_EQUAL(Image_get_pixel(&img, i, j).g, 0);
      ASSERT_EQUAL(Image_get_pixel(&img, i, j).b, 0);
    }
  }
}
TEST(test_init2) {
  Image img;
  int width = 1;
  int height= 1;
  Image_init(&img, width, height); 

  ASSERT_EQUAL(Image_width(&img), width);
  ASSERT_EQUAL(Image_height(&img), height);

  for (int i = 0; i < Image_height(&img); ++i) {
    for (int j = 0; j < Image_width(&img); ++j) {
      ASSERT_EQUAL(Image_get_pixel(&img, i, j).r, 0);
      ASSERT_EQUAL(Image_get_pixel(&img, i, j).g, 0);
      ASSERT_EQUAL(Image_get_pixel(&img, i, j).b, 0);
    }
  }
}

TEST(test_width) {
  Image img;
  int width = 100;
  int height= 1;
  Image_init(&img, width, height); 

  ASSERT_EQUAL(Image_width(&img), width);
} 

TEST(test_init_small) {
  Image img;
  int width = 1;
  int height= 1;
  Image_init(&img, width, height);
    
  ASSERT_EQUAL(Image_width(&img),width);
  ASSERT_EQUAL(Image_height(&img), height);

  ASSERT_EQUAL(Image_get_pixel(&img, 0, 0).r, 0);
  ASSERT_EQUAL(Image_get_pixel(&img, 0, 0).g, 0);
  ASSERT_EQUAL(Image_get_pixel(&img, 0, 0).b, 0);
}

TEST(test_init_large) {
  Image img;
  int width = 10;
  int height= 1;
  Image_init(&img, width, height);
    

  for (int i = 0; i < Image_height(&img); ++i) {
    for (int j = 0; j < Image_width(&img); ++j) {
      ASSERT_EQUAL(Image_get_pixel(&img, i, j).r, 0);
      ASSERT_EQUAL(Image_get_pixel(&img, i, j).g, 0);
      ASSERT_EQUAL(Image_get_pixel(&img, i, j).b, 0);
    }
  }
}

TEST(test_Image_init_from_ppm) {
  stringstream ppm_data("P3\n3 2\n255\n255 0 0 0 255 0 0 0 255");
  Image img;
  Image_init(&img, ppm_data);
    
  ASSERT_EQUAL(Image_get_pixel(&img, 0, 0).r, 255);
  ASSERT_EQUAL(Image_get_pixel(&img,  0, 0).g, 0);
  ASSERT_EQUAL(Image_get_pixel(&img, 0, 0).b, 0);

  ASSERT_EQUAL(Image_get_pixel(&img, 0, 1).r, 0);
  ASSERT_EQUAL(Image_get_pixel(&img, 0, 1).g, 255);
  ASSERT_EQUAL(Image_get_pixel(&img, 0, 1).b, 0);

  ASSERT_EQUAL(Image_get_pixel(&img, 0, 2).r, 0);
  ASSERT_EQUAL(Image_get_pixel(&img, 0, 2).g, 0);
  ASSERT_EQUAL(Image_get_pixel(&img, 0, 2).b, 255);
}


 TEST(test_width_height) {
  Image img;
  int width = 4;
  int height= 5;
  Image_init(&img, width, height); 

  ASSERT_EQUAL(Image_width(&img), 4);
  ASSERT_EQUAL(Image_height(&img), 5);
}

TEST(img_init_set_pixel){
  Image img;
  int width = 4;
  int height= 5;
  Image_init(&img, width, height);

  ASSERT_EQUAL(Image_width(&img), width);
  ASSERT_EQUAL(Image_height(&img), height);
  for (int i = 0; i < Image_height(&img); ++i) {
    for (int j = 0; j < Image_width(&img); ++j) {
      ASSERT_EQUAL(Image_get_pixel(&img, i, j).r, 0);
      ASSERT_EQUAL(Image_get_pixel(&img, i, j).g, 0);
      ASSERT_EQUAL(Image_get_pixel(&img, i, j).b, 0);
    }
  }
}



TEST(test_set_get_pixel_colored) {
  Image img;
  int width = 4;
  int height= 4;
  Image_init(&img, width, height); 
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel yellow = {255, 255, 0};

  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 1, 1, green);
  Image_set_pixel(&img, 2, 2, blue);
  Image_set_pixel(&img, 3, 3, yellow);

  ASSERT_EQUAL(Image_get_pixel(&img, 0, 0).r, red.r);
  ASSERT_EQUAL(Image_get_pixel(&img, 1, 1).g, green.g);
  ASSERT_EQUAL(Image_get_pixel(&img, 2, 2).b, blue.b);
  ASSERT_EQUAL(Image_get_pixel(&img, 3, 3).r, yellow.r);

}



// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image img;
  int width = 2;
  int height= 2;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img, width, height);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(&img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
}

TEST(test_print_same_color) {
  Image img;
  int width = 2;
  int height= 2;
  const Pixel white = {255, 255, 255};

  Image_init(&img, width, height);
    
  // Set all pixels to white
  Image_set_pixel(&img, 0, 0, white);
  Image_set_pixel(&img, 0, 1, white);
  Image_set_pixel(&img, 1, 0, white);
  Image_set_pixel(&img, 1, 1, white);

  ostringstream s;
  Image_print(&img, s);


  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 255 255 255 255 255 \n"; 
  correct << "255 255 255 255 255 255 \n"; 

  ASSERT_EQUAL(s.str(), correct.str());
}

TEST(test_fill) {
  Image img;
  int width = 2;
  int height= 3;
  Image_init(&img, width, height); 

  Pixel color = {100, 150, 200};
  Image_fill(&img, color);

  for (int i = 0; i < Image_height(&img); ++i) {
    for (int j = 0; j < Image_width(&img); ++j) {
      ASSERT_EQUAL(Image_get_pixel(&img, i, j).r, color.r);
      ASSERT_EQUAL(Image_get_pixel(&img, i, j).g, color.g);
      ASSERT_EQUAL(Image_get_pixel(&img, i, j).b, color.b);
    }
  }
}

TEST(test_fill_with_new_color) {
  Image img;
  int width = 4;
  int height= 4;
  Image_init(&img, width, height);
  Pixel initial_color = {255, 255, 255};
  Pixel new_color = {50, 50, 50};
    
  Image_fill(&img, initial_color);
  for (int i = 0; i < Image_height(&img); ++i) {
    for (int j = 0; j < Image_width(&img); ++j) {
      ASSERT_EQUAL(Image_get_pixel(&img, i, j).r, 255);
      ASSERT_EQUAL(Image_get_pixel(&img, i, j).g, 255);
      ASSERT_EQUAL(Image_get_pixel(&img, i, j).b, 255);
    }
  }

  Image_fill(&img, new_color);
  for (int i = 0; i < Image_height(&img); ++i) {
    for (int j = 0; j < Image_width(&img); ++j) {
      ASSERT_EQUAL(Image_get_pixel(&img, i, j).r, 50);
      ASSERT_EQUAL(Image_get_pixel(&img, i, j).g, 50);
      ASSERT_EQUAL(Image_get_pixel(&img, i, j).b, 50);
    }
  }
}



TEST_MAIN() // Do NOT put a semicolon here
