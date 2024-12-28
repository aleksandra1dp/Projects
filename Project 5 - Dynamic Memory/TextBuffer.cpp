#include "TextBuffer.hpp"
#include <assert.h>

TextBuffer::TextBuffer() : row(1), column(0), index(0){
  cursor = data.end();

}

bool TextBuffer::forward(){
  if (cursor == data.end())
    return false;

  if (*cursor == '\n'){
    //move_to_row_start();
    row++;
    column = 0;
  } else{
    column++;
  }
  cursor++;
  index++;
  return true;
}

bool TextBuffer::backward(){
  if(cursor == data.begin())
    return false;

  cursor--;
  index--;
  if (*cursor == '\n'){
    // move_to_row_end();
    row--;
    column = compute_column();
  } else{
    column--;
  }
  return true;
}

void TextBuffer::insert(char c){
  data.insert(cursor, c);
  if (c == '\n') {
    row++;
    column = 0;
  } else {
    column++;
  }
  index++;
}

bool TextBuffer::remove(){
  if (cursor == data.end())
    return false;
  
  // char deleteChar = *cursor;
  Iterator temp = cursor;
  cursor++;
  data.erase(temp);

  // if(deleteChar == '\n'){
  //   row--;
  //   column= compute_column();
  // }
  return true;
}

void TextBuffer::move_to_row_start(){
  while (cursor != data.begin()) {
    Iterator prev = cursor;
    prev--;
    if (*prev == '\n'){
      break;
    }
    backward();
  }
  column = 0;
  //row--;
}

void TextBuffer::move_to_row_end(){
  //int TEST_VAL = 100;
  
  //temp--;
  //int count = 0;
  if (cursor == data.end()){
    return;
  }
  Iterator temp = cursor;
  if (*temp == '\n'){
    return;
  }
  while (temp  != data.end() && *temp != '\n'){
    //count++;
    temp++;
    index++;
    column++;
   // assert(TEST_VAL-- > 0);
  }
  // if (temp != data.end()){
  //   column = 0;
  //   row++;
  // }
  cursor = temp;
}

void TextBuffer::move_to_column(int new_column){
  assert(new_column >= 0);
  move_to_row_start();
  for (int i = 0; i < new_column; i++){
    if (cursor == data.end()) {
      break;
    }
    if (*cursor == '\n'){
      break;
    }
    forward();
  }
  //column = new_column;

}

bool TextBuffer::up(){
  if (row == 1)
    return false;

  int temp = column;
  move_to_row_start();
  backward();
  move_to_column(temp);
  return true;
  
}


bool TextBuffer::down(){
  if (cursor == data.end()){
    return false;
  }
  Iterator tempIterator = cursor;
  int temp = column;
  int itemp = index;
  move_to_row_end();

  if (cursor == data.end()||!forward()){
    column = temp;
    index = itemp;
    cursor =  tempIterator;
    return false;
  }
  //forward();
  move_to_column(temp);
  return true;
  
}

bool TextBuffer::is_at_end() const {
  if (cursor == data.end())
    return true;
  return false;
}

char TextBuffer::data_at_cursor() const {
  return *cursor;
}

int TextBuffer::get_row() const {
  return row;
}

int TextBuffer::get_column() const {
  return column;
}

int TextBuffer::get_index() const {
  return index;
}

int TextBuffer::size() const{
  return data.size();
}

std::string TextBuffer::stringify() const{
  auto temp = data.begin();
  std::string ret = "";
  while (temp != data.end()){
    ret += *temp;  
    temp++;
  }
  return ret;
   
}

//TODO
int TextBuffer::compute_column() const {
  if(cursor == data.begin()){
    return 0;
  }

  Iterator temp = cursor;
  int c = 0;

  while(temp!=data.begin()){
    temp--;
    if(*temp == '\n'){
      break;
    }
    c++;
  }
  return c;
  
  //return 0;
}