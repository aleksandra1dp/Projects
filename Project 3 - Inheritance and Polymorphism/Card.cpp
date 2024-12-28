#include <cassert>
#include <iostream>
#include <array>
#include "Card.hpp"

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const RANK_NAMES[] = {
  "Two",   // TWO
  "Three", // THREE
  "Four",  // FOUR
  "Five",  // FIVE
  "Six",   // SIX
  "Seven", // SEVEN
  "Eight", // EIGHT
  "Nine",  // NINE
  "Ten",   // TEN
  "Jack",  // JACK
  "Queen", // QUEEN
  "King",  // KING
  "Ace"    // ACE
};

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
//EFFECTS returns the Rank corresponding to str, for example "Two" -> TWO
Rank string_to_rank(const std::string &str) {
  for(int r = TWO; r <= ACE; ++r) {
    if (str == RANK_NAMES[r]) {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
  return {};
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank) {
  os << RANK_NAMES[rank];
  return os;
}

//REQUIRES If any input is read, it must be a valid rank
//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank) {
  string str;
  if(is >> str) {
    rank = string_to_rank(str);
  }
  return is;
}



/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
//EFFECTS returns the Suit corresponding to str, for example "Clubs" -> CLUBS
Suit string_to_suit(const std::string &str) {
  for(int s = SPADES; s <= DIAMONDS; ++s) {
    if (str == SUIT_NAMES[s]) {
      return static_cast<Suit>(s);
    }
  }
  assert(false); // Input string didn't match any suit
  return {};
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit) {
  os << SUIT_NAMES[suit];
  return os;
}

//REQUIRES If any input is read, it must be a valid suit
//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit) {
  string str;
  if (is >> str) {
    suit = string_to_suit(str);
  }
  return is;
}


/////////////// Write your implementation for Card below ///////////////


// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
//EFFECTS returns the Suit corresponding to str, for example "Clubs" -> CLUBS

  //EFFECTS Initializes Card to the Two of Spades
  Card::Card() : rank(TWO), suit(SPADES){}

  //EFFECTS Initializes Card to specified rank and suit
  Card::Card(Rank rank_in, Suit suit_in): rank(rank_in), suit(suit_in){}

  //EFFECTS Returns the rank
  Rank Card::get_rank() const{
    return rank;
  }

  //EFFECTS Returns the suit.  Does not consider trump.
  Suit Card::get_suit() const{
    return suit;
  }

  //EFFECTS Returns the suit
  //HINT: the left bower is the trump suit!
  Suit Card::get_suit(Suit trump) const{
  if(is_left_bower(trump) == true){
    return trump;
  }
    return suit;
  }

  //EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
  bool Card::is_face_or_ace() const{
    if(rank==JACK ||rank==QUEEN||rank==KING||rank==ACE){
      return true;
    }
    return false;

  }

  //EFFECTS Returns true if card is the Jack of the trump suit
  bool Card::is_right_bower(Suit trump) const{
    if (rank==JACK && suit ==trump){
      return true;
    }
    return false;
  }

  //EFFECTS Returns true if card is the Jack of the next suit
  bool Card::is_left_bower(Suit trump) const{
  if(rank==JACK){
    if (trump == SPADES) { //Spades and clubs are black; hearts and diamonds are red
      return suit == CLUBS; 
    } else if (trump == HEARTS) {
      return suit == DIAMONDS; 
    } else if (trump == CLUBS) {
      return suit == SPADES; 
    } else if (trump == DIAMONDS) {
      return suit == HEARTS;
    }
  }
  return false;
}

  //EFFECTS Returns true if the card is a trump card.  All cards of the trump
  // suit are trump cards.  The left bower is also a trump card.
  bool Card::is_trump(Suit trump) const{
    if (is_right_bower(trump)) {
        return true; 
    }
    if(suit==trump|| is_left_bower(trump)==true){
      return true;
    }
    return false;
  }
//   operator<<
ostream& operator<<(ostream& os,const Card& card) {
  os << card.get_rank()<< " of " << card.get_suit(); //send output to "os"
  return os; //don't forget to return "os"

}
//   operator>>
istream& operator>>(istream& is, Card& card) {
  string card_rank;
  string card_suit;
  string of;
  if (is >> card_rank>>of >> card_suit) { 
    if (of != "of") {
      return is;
    }
    card.rank = string_to_rank(card_rank);
    card.suit = string_to_suit(card_suit);
    }
  return is; 
}

//   operator<
bool operator<(const Card& card1,const Card& card2) {
  if (card1.get_rank() == card2.get_rank()) {
    return card1.get_suit() < card2.get_suit();  // Break ties with suit
  }
  return card1.get_rank() < card2.get_rank();
}
//   operator<=
bool operator<=(const Card& card1,const Card& card2) {
  return card1 < card2 || card1 == card2;

}
//   operator>
bool operator>(const Card& card1,const Card& card2){
  return !(card1 <= card2);

}
//   operator>=
bool operator>=(const Card& card1,const Card& card2) {
  return !(card1 < card2);
}
//   operator==
bool operator==(const Card& card1,const Card& card2){
  return card1.get_rank() == card2.get_rank() && card1.get_suit() == card2.get_suit();

}
//   operator!=
bool operator!=(const Card& card1,const Card& card2){
  return !(card1 == card2);

}

//EFFECTS returns the next suit, which is the suit of the same color
Suit Suit_next(Suit suit){
  if (suit == SPADES) {
   return  CLUBS; 
  } else if (suit == CLUBS) {
    return SPADES; 
  } else if (suit == DIAMONDS) {
    return HEARTS;
  }else if (suit == HEARTS) {
    return  DIAMONDS; 
  }
  return HEARTS;
}

//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, Suit trump){
  if (a == b) {
    return false;//Cards are equal
  }
  if (a.is_right_bower(trump)) {
    return false;
  }
  if (b.is_right_bower(trump)) {
    return true; 
  }
  if (a.is_left_bower(trump)){
    return false;
  }
  if (b.is_left_bower(trump)){
    return true;
  }
  // if (!a.is_trump(trump) && !b.is_trump(trump)) {
  //   return a.get_rank() < b.get_rank(); // Compare ranks if both are non-trump
  // }
  if (a.is_trump(trump) && !b.is_trump(trump)) {
    return false; // Trump card is higher
  }
  if (!a.is_trump(trump) && b.is_trump(trump)) {
   return true; 
  }
  if(a.get_rank() == b.get_rank()) {
    return a.get_suit() < b.get_suit();
  }
  return a.get_rank()<b.get_rank();

}

//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump){
  if (trump == led_card.get_suit(trump)) {
    return Card_less(a, b, trump); 
  }
  if (a.is_right_bower(trump)){
    return false;
  }
  if (a.is_left_bower(trump)){
    return false;
  }
  if (b.is_right_bower(trump)){
    return true;
  }
  if (b.is_left_bower(trump)){
    return true;
  }
  if (a.is_trump(trump) && !b.is_trump(trump)) {
    return false; // Trump card is higher
  }
  if (!a.is_trump(trump) && b.is_trump(trump)) {
   return true; 
  }

  if (a.get_suit(trump)!=led_card.get_suit(trump)
   && b.get_suit(trump)==led_card.get_suit(trump)) {
    return true; // b is higher
  }
  if (a.get_suit(trump)==led_card.get_suit(trump) 
  && b.get_suit(trump)!=led_card.get_suit(trump)) {
   return false; 
  }
  
  if(a.get_rank() == b.get_rank()) {
    return a.get_suit() < b.get_suit();
  }
  return a.get_rank()<b.get_rank(); //Compare ranks if same ranks/ not following led

}