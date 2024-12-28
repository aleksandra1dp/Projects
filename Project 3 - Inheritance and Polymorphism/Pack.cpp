#include <cassert>
#include <iostream>
#include <vector>
#include "Pack.hpp"

////////////////////// Implementation for Pack ///////////////////////

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on. 
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
// NOTE: The pack is initially full, with no cards dealt.
Pack::Pack() {
    int i = 0;
    next = 0;
    for(int suit = 0; suit <= 3; ++suit) { 
        for(int rank = 7; rank <= 12; ++rank) {      
            Card default_card(static_cast<Rank>(rank), static_cast<Suit>(suit));
            cards.at(i) = default_card;
            ++i; // debug this line of code
            //cout << cards << endl;
        }
    }
}
// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
// NOTE: The pack is initially full, with no cards dealt.
Pack::Pack(std::istream& pack_input) {
    //Rank rank;
   // Suit suit;
    Card storage_card;
    next = 0;
    for(int i = 0; i < PACK_SIZE; ++i) {
        pack_input>> storage_card;
        cards.at(i) = storage_card; 
    }
}


// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
    assert(next < PACK_SIZE);  
    return cards.at(next++);
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
    next = 0;
    // cards.at(next) = cards.at(0);
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() { // interweave stack so break into 2 sections?
    for(int j = 0; j < 7; ++j) { // repeats shuffle 7 times
        std::array<Card, PACK_SIZE> shuffled_cards; 
        for (int i = 0; i < PACK_SIZE/2; ++i) {
            shuffled_cards.at(2*i) = cards.at(PACK_SIZE/2+i); // second half of deck
            //cout << i << endl;
            shuffled_cards.at((2*i+1)) = cards.at(i); //offset 
            //std::cout << i + 1 << endl;
        }
    cards = shuffled_cards;
    }
    
}


// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const{
    if (next >= PACK_SIZE) {
        return true;
    }
    else {
        return false;
    }
}


