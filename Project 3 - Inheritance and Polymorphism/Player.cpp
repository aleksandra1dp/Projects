#include <cassert>
#include <iostream>
#include <array>
#include <algorithm> 
#include <vector>
#include "Player.hpp"
#include "Card.hpp"

using namespace std;


// class Player {
//     public:
//     virtual const string & get_name() const = 0;
//     virtual void add_card(const Card &c) = 0;
//     virtual bool make_trump(const Card &upcard, bool is_dealer, int round, 
//     Suit &order_up_suit) const = 0;
//     virtual void add_and_discard(const Card &upcard) = 0;
//     virtual Card lead_card(Suit trump) = 0;
//     virtual Card play_card(const Card &led_card, Suit trump) = 0;
//     static const int MAX_HAND_SIZE = 5;
//     virtual ~Player() {}
// }; 

class Simple : public Player {
    private:
    string name; 
    vector<Card> hand;

    public:
    //EFFECTS returns player's name
    Simple(const string& player_name) : name(player_name) {}

    const string & get_name() const override {
        return name;
    }

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override{
        assert(hand.size() < MAX_HAND_SIZE);
        hand.push_back(c);
    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
        int round, Suit &order_up_suit) const override {
     

        
        assert(round == 1 || round == 2);

        if (round == 1){
            int face_ace_trump = 0;
            Suit upcard_suit = upcard.get_suit();
            for (int i=0; i < hand.size(); ++i){
                if ((hand.at(i).is_trump(upcard_suit) 
                && hand.at(i).is_face_or_ace()) ) {
                    ++face_ace_trump;
                }
            }
            if (face_ace_trump >= 2) {
                order_up_suit = upcard_suit;
                return true;
            }
            return false;
        }
        else if(round ==2){
            Suit round_2_suit = Suit_next(upcard.get_suit());
            for (int i=0; i < hand.size(); ++i){
                if ((hand.at(i).is_trump(round_2_suit) && 
                    hand.at(i).is_face_or_ace()) )  {
                    // ++face_ace_trump;
                    order_up_suit = round_2_suit;
                    return true;
                    }
            }
            if (is_dealer) {
                order_up_suit = round_2_suit;
                return true;
            }
        }
        //int face_ace_trump = 0;
        //Suit round_2_suit = Suit_next(upcard.get_suit());
        // for (int i=0; i < hand.size(); ++i){
        //     if ((hand.at(i).is_trump(round_2_suit) && 
        //         hand.at(i).is_face_or_ace()) )  {
        //         ++face_ace_trump;
        //     }
        // }
        // if (face_ace_trump >= 1) {
        //     order_up_suit = round_2_suit; //Order up if we have at 1+ face ace of suit
        //     return true;
        // } 
        // if (is_dealer) {
        //     // bool has_suit = false;
        //     // for (int i = 0; i < hand.size(); ++i) {
        //     //     if (((hand.at(i).is_trump(round_2_suit) && 
        //     //     hand.at(i).is_face_or_ace())) ) {
        //     //         has_suit = true;
        //     //         break;
        //     //     }
        //     // }
        //     // if (has_suit) {
        //         order_up_suit = round_2_suit;
        //         return true;
        //     //}
                
        // }
        return false;
    
    }

    

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override {
        assert(!hand.empty());
        hand.push_back(upcard);

        Card lowest_card = hand.at(0);
        int index =0 ;
        for (int i=0; i<hand.size(); ++i) {
            if (Card_less(hand.at(i), lowest_card, upcard.get_suit())){
                lowest_card = hand.at(i);
                index = i;
            }
        }
        
        hand.erase(hand.begin() + index); 
    }


    //REQUIRES Player has at least one card
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(Suit trump) override {
        assert(!hand.empty());

        Card highest_non_trump_card = hand.at(0);
        Card highest_trump_card = hand.at(0);

        int highest_non_trump_index = -1; // Invalid index
        int highest_trump_index = -1;

        for (int i = 0; i < hand.size(); ++i) {
            if (!hand.at(i).is_trump(trump)) {
                if (highest_non_trump_index == -1 || 
                Card_less(hand.at(highest_non_trump_index), hand.at(i), trump)) {
                    highest_non_trump_index = i;
                }
            } else {
                if (highest_trump_index == -1 || 
                Card_less(hand.at(highest_trump_index), hand.at(i), trump)) {
                    highest_trump_index = i;
                }
            }
        }

        if (highest_non_trump_index != -1) {
            highest_non_trump_card = hand.at(highest_non_trump_index);
            hand.erase(hand.begin() + highest_non_trump_index);
            return highest_non_trump_card;
        } else {
            highest_trump_card = hand.at(highest_trump_index);
            hand.erase(hand.begin() + highest_trump_index);
            return highest_trump_card;
        }
    }

     //REQUIRES Player has at least one card
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, Suit trump) override {
    assert(!hand.empty());

    Suit led_suit = led_card.get_suit(trump);
    Card highest_led_card; 
    bool follow_suit = false;
    int best_card_index = -1;


        for (int i=0; i < hand.size(); ++i){
           if (hand.at(i).get_suit(trump) == led_suit) { // If player can follow suit
                if (best_card_index== -1|| 
                Card_less(hand.at(best_card_index), hand.at(i), trump)) {
                best_card_index = i;
                follow_suit  = true;
                }
            }
        }
        
        if (follow_suit) {
            highest_led_card = hand.at(best_card_index);
            hand.erase(hand.begin()+best_card_index);
            return highest_led_card; //Returned the card that was played
        }

        Card lowest_card;
        best_card_index = 0;
        for (int i = 0; i < hand.size(); ++i) {
            if (Card_less(hand.at(i), hand.at(best_card_index), trump)) {
                best_card_index = i;
            }
        }
        lowest_card = hand.at(best_card_index);
        hand.erase(hand.begin()+best_card_index);
        return lowest_card; 
    }

};



class Human : public Player {
    private:
    string name; 
    vector<Card> hand;

    void print_hand() const {
        for (size_t i=0; i < hand.size(); ++i)
        cout << "Human player " << name << "'s hand: "
            << "[" << i << "] " << hand[i] << "\n";
    }
    
    public:

    Human(const string& player_name) : name(player_name) {}

    //EFFECTS returns player's name
    const string & get_name() const override {
        return name;
    }


    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override{
        if (hand.size() < MAX_HAND_SIZE){
            hand.push_back(c);
            sort(hand.begin(), hand.end());
        }
    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                            int round, Suit &order_up_suit) const override{
        print_hand();
        assert(round == 1 || round == 2);
        cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
        string decision;
        cin >> decision;

        if (decision != "pass") {
            Suit ordered_up = string_to_suit(decision);
            order_up_suit = ordered_up;
            return true;
        } else {
            return false;
        }
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override {
        assert(!hand.empty());
        sort(hand.begin(), hand.end());
        print_hand();

        cout << "Discard upcard: [-1]\n";
        cout << "Human player " << name << ", please select a card to discard:"<<endl;

        int choice;
        cin >> choice;
        if (choice == -1) {
            hand.push_back(upcard);
            //cout << endl;
        } else {
            hand.erase(hand.begin() + choice);
            hand.push_back(upcard);
            //cout << endl;
        }
        //cout << endl;

    }


    //REQUIRES Player has at least one card
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(Suit trump) override{
        assert(!hand.empty());
        sort(hand.begin(), hand.end());
        print_hand();
        cout << "Human player " << name << ", please select a card:\n";


        int choice;
        cin >> choice;
        Card lead_card = hand.at(choice);
        hand.erase(hand.begin() + choice);
        return lead_card;
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, Suit trump) override {
        assert(!hand.empty());
        sort(hand.begin(), hand.end());
        print_hand();
        cout << "Human player " << name << ", please select a card:\n";
        
        int choice;
        cin >> choice;
        Card play_card = hand.at(choice);
        hand.erase(hand.begin() + choice);
        return play_card;
    }
};

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name,  const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new Simple(name);
  } else if (strategy == "Human") {
    // The "new" keyword dynamically allocates an object.
    return new Human(name);
  }
  // Invalid strategy if we get here
    assert(false);

    return nullptr;
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}