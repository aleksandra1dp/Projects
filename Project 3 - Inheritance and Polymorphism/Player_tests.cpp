#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) { 
    // test simple player getname
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    delete alice;
}

TEST(test_player_get_name_stream) {
    // test simple player name from stream
    Player * anna = Player_factory("Anna", "Simple");
    ostringstream os;
    os<< *anna;
    ASSERT_EQUAL("Anna",os.str());
    delete anna;
}

// TEST(test_human_player_constructor) {
//     // test human player constructor
//     Player* anna = Player_factory("Anna", "human");
//     ASSERT_EQUAL(anna->get_name(), "Anna");
//     delete anna;
// }

TEST(test_simple_player_make_trump) {
    // test simple player will make trump
    // Round 1 both true
    // Anna's hand, no trump
    Player * Anna = Player_factory("Anna", "Simple");
    Anna->add_card(Card(NINE, DIAMONDS));
    Anna->add_card(Card(QUEEN, HEARTS)); //Face
    Anna->add_card(Card(QUEEN, SPADES));
    Anna->add_card(Card(KING, DIAMONDS));
    Anna->add_card(Card(ACE, HEARTS)); //Ace
    // Anna makes tump
    Card queen_hearts(JACK, HEARTS);
    Suit trump;
    bool orderup = Anna->make_trump(
        queen_hearts,    // Upcard
        false,           // Anna is also the dealer
        1,              // First round
        trump           // Suit ordered up (if any)
    );
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, HEARTS);
    delete Anna;
}

TEST(test_simple_player_make_trump_round_1_right_bower) {
    // test make trump with right bower
    Player* bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(JACK, SPADES));   // Right bower
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(NINE, DIAMONDS));
    bob->add_card(Card(ACE, CLUBS));
    bob->add_card(Card(QUEEN, SPADES));
    Card upcard(JACK, SPADES);  
    Suit trump;
    bool orderup = bob->make_trump(upcard, false, 1, trump);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, SPADES);
    delete bob;
}

TEST(test_simple_player_make_trump_round_1_face_ace_trump_greater_than_two) {
    // test make trump with more than 1 trump
    Player* bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(QUEEN, SPADES));  // Face 
    bob->add_card(Card(KING, SPADES));   // Face 
    bob->add_card(Card(ACE, SPADES));    // Ace 
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(NINE, DIAMONDS));
    Card upcard(JACK, SPADES); 
    Suit trump;
    bool orderup = bob->make_trump(upcard, false, 1, trump);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, SPADES);
    delete bob;
}



TEST(test_simple_player_make_trump_round_1_pass) {
    // test pass on make trump in round 1
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, SPADES));
    anna->add_card(Card(TEN, DIAMONDS));
    anna->add_card(Card(QUEEN, CLUBS));
    anna->add_card(Card(KING, DIAMONDS));
    anna->add_card(Card(ACE, SPADES));
    Card upcard(JACK, HEARTS);
    Suit trump;
    bool orderup = anna->make_trump(
        upcard,
        false,
        1,
        trump
    );
    ASSERT_FALSE(orderup);
    delete anna;
}

TEST(test_simple_player_lead_card) {
    // Anna's hand
    Player *anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, HEARTS));
    anna->add_card(Card(QUEEN, HEARTS));
    anna->add_card(Card(QUEEN, SPADES));
    anna->add_card(Card(ACE, DIAMONDS));
    anna->add_card(Card(ACE, HEARTS));
    // Anna adds a card to her hand and discards one card
    anna->add_and_discard(
        Card(TEN, CLUBS) // upcard
    );
    // Anna leads
    Card card_led = anna->lead_card(HEARTS);
    // Verify the card Anna selected to lead
    Card ace_diamonds(ACE, DIAMONDS);
    ASSERT_EQUAL(card_led, ace_diamonds); // Check the led card
    delete anna;
}

TEST(test_player_lead_all_trump) {
    // test lead all with trump
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, HEARTS));
    anna->add_card(Card(TEN, HEARTS));
    anna->add_card(Card(JACK, HEARTS)); // Right bower
    anna->add_card(Card(QUEEN, HEARTS));
    anna->add_card(Card(KING, HEARTS));
    Card led_card = anna->lead_card(SPADES);
    ASSERT_EQUAL(led_card, Card(KING, HEARTS));
    // Card led_card1 = anna->lead_card(HEARTS);
    // ASSERT_EQUAL(led_card1, Card(JACK, HEARTS));
    Card led_card2 = anna->lead_card(CLUBS);
    ASSERT_EQUAL(led_card2, Card(QUEEN, HEARTS));
    Card led_card3 = anna->lead_card(DIAMONDS);
    ASSERT_EQUAL(led_card3, Card(TEN, HEARTS));
    delete anna;
}

TEST(test_player_lead_no_trump) {
    // test no trump
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, HEARTS));
    anna->add_card(Card(TEN, SPADES));
    anna->add_card(Card(JACK, DIAMONDS));
    anna->add_card(Card(QUEEN, CLUBS));
    anna->add_card(Card(ACE, SPADES));
    Card led_card = anna->lead_card(HEARTS);
    ASSERT_EQUAL(led_card, Card(ACE, SPADES));
    delete anna;
}


TEST(test_simple_player_make_trump_round_1) {
    // Anna's hand
    Player * anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, SPADES));
    anna->add_card(Card(TEN, SPADES));
    anna->add_card(Card(QUEEN, SPADES));
    anna->add_card(Card(KING, SPADES));
    anna->add_card(Card(ACE, SPADES));

    // Anna decides trump based on the upcard
    Card nine_spades(NINE, SPADES);
    Suit trump;
    bool orderup = anna->make_trump(
        nine_spades,    // Upcard
        true,           // Anna is also the dealer
        1,              // First round
        trump           // Suit ordered up (if any)
    );

    // Verify Anna orders up Spades as trump
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, SPADES);

    Card jack_spades(JACK, SPADES); //Left-bower
    Suit trump1;
    bool orderup1 = anna->make_trump(
        jack_spades,  // Upcard
        true,         // Anna is the dealer
        1,            // First round
        trump1        // Suit ordered up (if any)
    );

    // Verify Anna orders up Spades as trump
    ASSERT_TRUE(orderup1);
    ASSERT_EQUAL(trump1, SPADES); 

    Card jack_clubs(JACK, CLUBS);
    Suit trump2;
    bool orderup2 = anna->make_trump(
        jack_clubs,     // Upcard
        true,           // Anna is the dealer
        1,              // First round
        trump2          // Suit ordered up (if any)
    );

    ASSERT_FALSE(orderup2);

    delete anna;
}

TEST(test_simple_player_make_trump_round_2) {
    // Anna's hand, all trump
    Player * anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, SPADES));
    anna->add_card(Card(TEN, SPADES));
    anna->add_card(Card(QUEEN, SPADES));
    anna->add_card(Card(KING, SPADES));
    anna->add_card(Card(ACE, SPADES));

    // Anna decides trump based on the upcard
    Card nine_spades(NINE, CLUBS);
    Suit trump;
    bool orderup = anna->make_trump(
        nine_spades,    // Upcard
        true,           // Anna is also the dealer
        2,              // First round
        trump           // Suit ordered up (if any)
    );

    // Verify Anna orders up Spades as trump
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, SPADES);

    delete anna;
}


TEST(test_make_trump_two_face__round_2_trump) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(QUEEN, HEARTS));//Face
    anna->add_card(Card(KING, HEARTS)); //Face
    anna->add_card(Card(NINE, SPADES));
    anna->add_card(Card(TEN, DIAMONDS));
    anna->add_card(Card(JACK, CLUBS));

    Card upcard(JACK, DIAMONDS);
    Suit trump;
    bool orderup = anna->make_trump(
        upcard, 
        false, 
        2, 
        trump
    );

    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, HEARTS);

    delete anna;
}


TEST(test_simple_player_make_trump_round_2_with_left_bower) {
    Player* anna = Player_factory("Anna", "Simple");
    
    anna->add_card(Card(JACK, CLUBS));// Left bower 
    anna->add_card(Card(NINE, HEARTS));
    anna->add_card(Card(KING, SPADES)); // Face in trump suit
    anna->add_card(Card(TEN, DIAMONDS));  
    anna->add_card(Card(QUEEN, DIAMONDS)); 

    Card upcard(JACK, SPADES);
    Suit trump;
    bool orderup = anna->make_trump(upcard, false, 2, trump); 

    ASSERT_TRUE(orderup);      
    ASSERT_EQUAL(trump, CLUBS);// Trump suit should be clubs; same color as spades

    delete anna;
}



TEST(test_make_trump_one_face_trump) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(QUEEN, DIAMONDS));
    anna->add_card(Card(NINE, HEARTS));
    anna->add_card(Card(TEN, SPADES));
    anna->add_card(Card(JACK, DIAMONDS));
    anna->add_card(Card(KING, CLUBS));

    Card upcard(JACK, HEARTS);
    Suit trump;
    bool orderup = anna->make_trump(
        upcard, 
        true, 
        1, 
        trump
    );

    ASSERT_FALSE(orderup);
    delete anna;
}


TEST(test_make_trump_right_and_left_bower) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(JACK, HEARTS));
    anna->add_card(Card(JACK, DIAMONDS));
    anna->add_card(Card(NINE, SPADES));
    anna->add_card(Card(TEN, HEARTS));
    anna->add_card(Card(KING, HEARTS));

    Card upcard(QUEEN, HEARTS);
    Suit trump;
    bool orderup = anna->make_trump(
        upcard,
        false,
        1,
        trump
    );
    
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(HEARTS, trump);

    delete anna;
}

TEST(test_make_trump_no_face_same_color) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, DIAMONDS));
    anna->add_card(Card(TEN, DIAMONDS));
    anna->add_card(Card(QUEEN, SPADES));
    anna->add_card(Card(KING, CLUBS));
    anna->add_card(Card(ACE, CLUBS));

    Card upcard(JACK, HEARTS);
    Suit trump;
    bool orderup = anna->make_trump(
        upcard,
        false,
        2,
        trump
    );

    ASSERT_FALSE(orderup);

    delete anna;
}

TEST(test_make_trump_face_same_color) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(QUEEN, DIAMONDS));
    anna->add_card(Card(NINE, SPADES));
    anna->add_card(Card(TEN, SPADES));
    anna->add_card(Card(JACK, CLUBS));
    anna->add_card(Card(KING, CLUBS));

    Card upcard(JACK, HEARTS);
    Suit trump;
    bool orderup = anna->make_trump(
        upcard, 
        false, 
        2, 
        trump
    );

    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(DIAMONDS, trump);

    delete anna;
}

TEST(test_make_trump_left_bower) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(JACK, DIAMONDS));// LEft bower
    anna->add_card(Card(NINE, SPADES));
    anna->add_card(Card(TEN, SPADES));
    anna->add_card(Card(QUEEN, CLUBS));
    anna->add_card(Card(KING, CLUBS));

    Card upcard(NINE, HEARTS);
    Suit trump;
    bool orderup = anna->make_trump(
        upcard, 
        false, 
        2, 
        trump
    );

    if (DIAMONDS == trump){
        orderup = true;
    }
    ASSERT_TRUE(orderup);

    delete anna;
}

TEST(test_make_trump_screw_the_dealer) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, SPADES));
    anna->add_card(Card(TEN, SPADES));
    anna->add_card(Card(QUEEN, CLUBS));
    anna->add_card(Card(KING, CLUBS));
    anna->add_card(Card(ACE, CLUBS));

    Card upcard(JACK, SPADES);
    Suit trump;
    bool orderup = anna->make_trump(
        upcard, 
        true, 
        2, 
        trump
    );

    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, CLUBS);

    delete anna;
}

TEST(test_add_and_discard_upcard_higher) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, HEARTS));
    anna->add_card(Card(TEN, HEARTS));
    anna->add_card(Card(JACK, SPADES));
    anna->add_card(Card(QUEEN, DIAMONDS));
    anna->add_card(Card(KING, CLUBS));

    Card upcard(ACE, HEARTS);
    anna->add_and_discard(upcard);

    Card led_card = anna->lead_card(SPADES);
    ASSERT_NOT_EQUAL(led_card, Card(NINE, HEARTS));

    delete anna;
}
TEST(test_add_and_discard_all_trump){
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, HEARTS));
    anna->add_card(Card(TEN, HEARTS));
    anna->add_card(Card(QUEEN, HEARTS));
    anna->add_card(Card(KING, HEARTS));
    anna->add_card(Card(ACE, HEARTS));

    Card upcard(QUEEN, DIAMONDS);
    anna->add_and_discard(upcard);

    Card led_card = anna->lead_card(HEARTS);
    ASSERT_EQUAL(led_card, Card(QUEEN, DIAMONDS));

      ASSERT_EQUAL(led_card, Card(QUEEN, DIAMONDS));
    delete anna;
}

TEST(test_add_and_discard_smallest_card){
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, HEARTS));
    anna->add_card(Card(TEN, SPADES));
    anna->add_card(Card(JACK, DIAMONDS));
    anna->add_card(Card(QUEEN, CLUBS));
    anna->add_card(Card(ACE, SPADES));

    Card upcard(QUEEN, DIAMONDS);
    anna->add_and_discard(upcard);
    ASSERT_NOT_EQUAL(anna->play_card(upcard, HEARTS), Card(NINE, HEARTS));

    Card led_card = anna->lead_card(HEARTS);
    ASSERT_EQUAL(led_card, Card(ACE, SPADES));  

    ASSERT_EQUAL(anna->play_card(led_card, HEARTS), Card(TEN, SPADES));
    ASSERT_EQUAL(anna->play_card(led_card, HEARTS), Card(QUEEN,CLUBS));
    ASSERT_EQUAL(anna->play_card(led_card, HEARTS), Card(JACK, DIAMONDS));
    //ASSERT_EQUAL(anna->play_card(led_card, HEARTS), Card(QUEEN, DIAMONDS));
     delete anna;
}


TEST(test_add_and_discard_hand_bowers) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(JACK, HEARTS));// Right
    anna->add_card(Card(JACK, DIAMONDS)); // Left
    anna->add_card(Card(QUEEN, HEARTS));
    anna->add_card(Card(NINE, HEARTS));
    anna->add_card(Card(KING, DIAMONDS));

    Card upcard(NINE, HEARTS);
    anna->add_and_discard(upcard);

    Card led_card = anna->lead_card(HEARTS);
    ASSERT_EQUAL(led_card, Card(JACK, HEARTS));
    delete anna;
}

TEST(test_lead_card_no_trump) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, HEARTS));
    anna->add_card(Card(TEN, SPADES));
    anna->add_card(Card(JACK, DIAMONDS));
    anna->add_card(Card(QUEEN, CLUBS));
    anna->add_card(Card(ACE, SPADES));

    Card led_card = anna->lead_card(HEARTS);
    ASSERT_EQUAL(led_card, Card(ACE, SPADES));

    delete anna;
}

TEST(test_lead_card_all_trump) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, HEARTS));
    anna->add_card(Card(TEN, HEARTS));
    anna->add_card(Card(QUEEN, HEARTS));
    anna->add_card(Card(KING, HEARTS));
    anna->add_card(Card(ACE, HEARTS));

    Card led_card = anna->lead_card(HEARTS);
    ASSERT_EQUAL(led_card, Card(ACE, HEARTS));

    delete anna;
}

TEST(test_lead_card_all_trump_with_bowers) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(JACK, HEARTS)); //Right Bower
    anna->add_card(Card(JACK, DIAMONDS));// Left Bower
    anna->add_card(Card(QUEEN, DIAMONDS));
    anna->add_card(Card(KING, HEARTS));
    anna->add_card(Card(ACE, SPADES));

    Card led_card = anna->lead_card(HEARTS);
    ASSERT_EQUAL(led_card, Card(ACE, SPADES));

    delete anna;
}

TEST(test_lead_card_no_trump_with_bowers) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(JACK, HEARTS));
    anna->add_card(Card(JACK, DIAMONDS));
    anna->add_card(Card(QUEEN, SPADES));
    anna->add_card(Card(KING, CLUBS));
    anna->add_card(Card(ACE, SPADES));

    Card led_card = anna->lead_card(CLUBS);
    ASSERT_EQUAL(led_card, Card(ACE, SPADES));

    delete anna;
}


TEST(test_play_card_follow_suit_not_trump) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, HEARTS));
    anna->add_card(Card(JACK, HEARTS));
    anna->add_card(Card(QUEEN, SPADES));
    anna->add_card(Card(KING, DIAMONDS));
    anna->add_card(Card(ACE, CLUBS));

    Card led_card(TEN, HEARTS);
    Card played_card = anna->play_card(led_card, SPADES);
    ASSERT_EQUAL(played_card, Card(JACK, HEARTS));
  
    delete anna;
}


TEST(test_simple_player_play_card) {
    // Anna's hand
    Player * anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, SPADES));
    anna->add_card(Card(TEN, SPADES));
    anna->add_card(Card(QUEEN, SPADES));
    anna->add_card(Card(KING, SPADES));
    anna->add_card(Card(ACE, SPADES));

    // Anna plays a card
    Card led_card(NINE, DIAMONDS);
    Card card_played = anna->play_card(
        led_card,  // Nine of Diamonds is led
        DIAMONDS    // Trump suit
    ); 

    // Verify the card Anna played
    ASSERT_EQUAL(card_played, Card(NINE, SPADES));
    delete anna;
}


TEST(test_simple_player_play_card_follow_suit) {
    // Anna's hand
    Player * anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, HEARTS));
    anna->add_card(Card(QUEEN, HEARTS));
    anna->add_card(Card(JACK, SPADES));
    anna->add_card(Card(TEN, CLUBS));
    anna->add_card(Card(ACE, HEARTS));

    // Led card is queen of hearts, trump is diamonds
    Card led_card(QUEEN, HEARTS);
    Card card_played = anna->play_card(
        led_card, 
        DIAMONDS
    );

    //Chooses highest card
    Card ace_hearts(ACE, HEARTS);
    ASSERT_EQUAL(card_played, ace_hearts);

    delete anna;
}

TEST(test_simple_player_play_card_no_follow_suit) {
    // Anna's hand
    Player * anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, DIAMONDS));
    anna->add_card(Card(QUEEN, SPADES));
    anna->add_card(Card(JACK, CLUBS));
    anna->add_card(Card(TEN, HEARTS));
    anna->add_card(Card(ACE, SPADES));

    Card led_card(KING, HEARTS);
    Card card_played = anna->play_card(
        led_card, 
        DIAMONDS
    );

    // Chooses the lowest card
    Card ten_hearts(TEN, HEARTS);
    ASSERT_EQUAL(card_played, ten_hearts);

    delete anna;
}

TEST(test_play_card_no_follow_suit_play_trump) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, CLUBS));
    anna->add_card(Card(JACK, SPADES));//Right bower 
    anna->add_card(Card(KING, SPADES));   
    anna->add_card(Card(QUEEN, SPADES));  
    anna->add_card(Card(TEN, CLUBS));

    Card led_card(ACE, DIAMONDS);
    Card card_played = anna->play_card(
        led_card,
        SPADES
    );

    // Plays the lowest card 
    ASSERT_EQUAL(card_played, Card(NINE,CLUBS));

    delete anna;
}

TEST(test_play_card_no_follow_suit_no_trump) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, DIAMONDS));
    anna->add_card(Card(TEN, CLUBS));
    anna->add_card(Card(JACK, CLUBS));
    anna->add_card(Card(KING, DIAMONDS));
    anna->add_card(Card(ACE, CLUBS));

    Card led_card(ACE, HEARTS);
    Card card_played = anna->play_card(
        led_card,
        SPADES
    );

    // Plays the lowest card 
    ASSERT_EQUAL(card_played, Card(NINE, DIAMONDS));

    delete anna;
}


TEST(test_hand_of_similar_cards_choose_worst_1) {
    Player * anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, SPADES));
    anna->add_card(Card(NINE, HEARTS));
    anna->add_card(Card(NINE, DIAMONDS));
    anna->add_card(Card(TEN, CLUBS));
    anna->add_card(Card(TEN, SPADES));
    Card led_card(NINE,DIAMONDS);
    Card card_played = anna->play_card(
        led_card, 
        DIAMONDS
    );

    // Chooses the lowest card
    Card nine_diamonds(NINE, DIAMONDS);
    ASSERT_EQUAL(card_played, nine_diamonds);

    delete anna;
}

// TEST(test_make_trump_of_lowest_suite) {
//     Player * anna = Player_factory("Anna", "Simple");
//     anna->add_card(Card(NINE, SPADES));
//     anna->add_card(Card(HAER, HEARTS));
//     anna->add_card(Card(NINE, DIAMONDS));
//     anna->add_card(Card(TEN, HEARTS));
//     anna->add_card(Card(TEN, HEARTS));
//     Card nine_diamonds(NINE, DIAMONDS);
//     Suit trump;
//     bool orderup = anna->make_trump(
//         nine_diamonds,    // Upcard
//         true,           // Anna is also the dealer
//         2,              // First round
//         trump           // Suit ordered up (if any)
//     );

//     // Verify Anna orders up Spades as trump
//     ASSERT_TRUE(orderup);
//     ASSERT_EQUAL(trump, HEARTS);

//     delete anna;
// }

TEST(test_simple_player_add_and_discard) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, HEARTS));
    anna->add_card(Card(TEN, HEARTS));
    anna->add_card(Card(JACK, SPADES));
    anna->add_card(Card(QUEEN, DIAMONDS));
    anna->add_card(Card(KING, CLUBS));

    Card upcard(ACE, HEARTS);
    anna->add_and_discard(upcard);

    // Discard lowest card
    Card led_card = anna->lead_card(DIAMONDS);
    ASSERT_NOT_EQUAL(led_card, Card(NINE, HEARTS));

    delete anna;
}

TEST(test_human_player_name) {
    Player* annita = Player_factory("Annita", "Human");
    ASSERT_EQUAL("Annita", annita->get_name());

    delete annita;
}

TEST(test_add_trump_less_than_5_cards) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, HEARTS));
    anna->add_card(Card(TEN, HEARTS));
    anna->add_card(Card(JACK, SPADES));
    Card nine_diamonds(NINE, DIAMONDS);
    Suit trump = SPADES;
    bool orderup = anna->make_trump(
        nine_diamonds,    // Upcard
        true,           // Anna is also the dealer
        1,              // First round
        trump           // Suit ordered up (if any)
    );
    ASSERT_FALSE(orderup);
    ASSERT_EQUAL(trump, SPADES);
    //assert less than 5 cards
    delete anna;
}

TEST(test_passing_trump) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, HEARTS));
    anna->add_card(Card(TEN, HEARTS));
    anna->add_card(Card(JACK, SPADES));
    anna->add_card(Card(QUEEN, DIAMONDS));
    anna->add_card(Card(KING, CLUBS));
    Card nine_diamonds(NINE, DIAMONDS);
    Suit trump = SPADES;
    bool orderup = anna->make_trump(
        nine_diamonds,    // Upcard
        false,           // Anna is also the dealer
        2,              // First round
        trump           // Suit ordered up (if any)
    );
    ASSERT_FALSE(orderup);
    ASSERT_EQUAL(trump, SPADES);
    delete anna;
}

TEST(test_make_trump_left_bower_1) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(JACK, HEARTS));
    anna->add_card(Card(QUEEN, DIAMONDS));
    anna->add_card(Card(KING, DIAMONDS));
    Card jack_diamonds(JACK, DIAMONDS);
    Suit trump = DIAMONDS;
    bool orderup = anna->make_trump(
        jack_diamonds,
        false,
        1,
        trump
    );
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump,DIAMONDS);
    delete anna;
}

TEST(test_simple_player_play_last_card) {
  Player * anna = Player_factory("Anna", "Simple");
  anna->add_card(Card(KING, CLUBS));  // Only one card left

  Card led_card(TEN, DIAMONDS);
  Card card_played = anna->play_card(led_card, HEARTS);

  // Must play her only card
  ASSERT_EQUAL(card_played, Card(KING, CLUBS));

  delete anna;
}

TEST(test_simple_player_make_trump_ace) {
    // One trump card (Ace)
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(ACE, DIAMONDS)); //Trump
    anna->add_card(Card(KING, HEARTS));
    anna->add_card(Card(ACE, CLUBS));
    anna->add_card(Card(ACE, HEARTS));
    anna->add_card(Card(QUEEN, HEARTS));
   
    Card upcard(NINE, DIAMONDS);
    Suit trump;
    bool orderup = anna->make_trump(
        upcard,
        false,
        1,
        trump
    );
    ASSERT_FALSE(orderup);

    bool orderup_deal= anna->make_trump(
        upcard, 
        true, 
        1, 
        trump
    );
    ASSERT_FALSE(orderup_deal);

    // One face card of next suit
    bool orderup_round2 = anna->make_trump(
        upcard,
        false,
        2,
        trump
    );
    ASSERT_TRUE(orderup_round2);
    ASSERT_EQUAL(trump, HEARTS);

    bool orderup_deal2= anna->make_trump(
        upcard, 
        true, 
        2, 
        trump
    );
    ASSERT_TRUE(orderup_deal2);
    ASSERT_EQUAL(trump, HEARTS);

    delete anna;
}

TEST(test_simple_player_make_trump_no_trump_faces) {
    // No face cards trump 
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, DIAMONDS));
    anna->add_card(Card(ACE, HEARTS));
    anna->add_card(Card(KING, HEARTS));
    anna->add_card(Card(TEN, CLUBS));
    anna->add_card(Card(QUEEN, HEARTS));
   
    Card upcard(KING, DIAMONDS);
    Suit trump;
    bool orderup = anna->make_trump(
        upcard,
        false,
        1,
        trump
    );
    ASSERT_FALSE(orderup);
    // Forced to order up in second round
    bool orderup_round2 = anna->make_trump(
        upcard,
        true,
        2,
        trump
    );
    ASSERT_TRUE(orderup_round2);
    ASSERT_EQUAL(trump, HEARTS);

    delete anna;
}

TEST(test_simple_player_discard_upcard_and_lead) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(JACK, HEARTS));// Right
    anna->add_card(Card(JACK, DIAMONDS)); // Left
    anna->add_card(Card(QUEEN, HEARTS));
    anna->add_card(Card(NINE, HEARTS));
    anna->add_card(Card(KING, HEARTS));

    Card upcard(NINE, HEARTS);
    Suit trump;
    bool orderup= anna->make_trump(
        upcard, 
        true, 
        1, 
        trump
    );

    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, HEARTS);

    anna->add_and_discard(upcard);

    ASSERT_EQUAL(anna->lead_card(trump), Card(JACK, HEARTS));
    ASSERT_EQUAL(anna->lead_card(trump), Card(JACK, DIAMONDS));
    ASSERT_EQUAL(anna->lead_card(trump), Card(KING, HEARTS));
    ASSERT_EQUAL(anna->lead_card(trump), Card(QUEEN, HEARTS));
    ASSERT_EQUAL(anna->lead_card(trump), Card(NINE, HEARTS));

    delete anna;
}

TEST(test_simple_player_play_card_multiple_follow_suit) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(NINE, DIAMONDS));
    anna->add_card(Card(ACE, DIAMONDS));
    anna->add_card(Card(QUEEN, DIAMONDS));
    anna->add_card(Card(JACK, DIAMONDS));
    anna->add_card(Card(JACK, DIAMONDS));
   
    Card led_card(QUEEN, DIAMONDS);
    Card played_card = anna->play_card(led_card, DIAMONDS);
    ASSERT_EQUAL(played_card, Card(JACK, DIAMONDS));

    delete anna;
}

TEST(test_simple_player_order_up_gameplay) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(TEN, SPADES));
    anna->add_card(Card(NINE, SPADES));
    anna->add_card(Card(QUEEN, DIAMONDS));
    anna->add_card(Card(TEN, DIAMONDS));
    anna->add_card(Card(ACE, CLUBS));

    Card upcard(TEN, SPADES);
    Suit trump;
    bool orderup1 = anna->make_trump(
        upcard,
        true,
        1,
        trump
    );
    ASSERT_FALSE(orderup1);
    
    bool orderup2 = anna->make_trump(
        upcard,
        true,
        2,
        trump
    );
    ASSERT_TRUE(orderup2);
    ASSERT_EQUAL(trump, CLUBS);

    ASSERT_EQUAL(anna->lead_card(trump), Card(QUEEN, DIAMONDS));

    Card card= Card(QUEEN, CLUBS);
    ASSERT_EQUAL(anna->play_card(card, trump), Card(ACE,CLUBS));

    Card card_2 = Card(JACK, DIAMONDS);
    ASSERT_EQUAL(anna->play_card(card_2, trump), Card(TEN, DIAMONDS));
    ASSERT_EQUAL(anna->lead_card(trump), Card(TEN, SPADES));

    delete anna;
}

TEST(test_trump_with_multiple_cards) {
    Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(JACK, SPADES));
    anna->add_card(Card(NINE, SPADES));
    anna->add_card(Card(KING, SPADES));
    anna->add_card(Card(TEN, CLUBS));
    anna->add_card(Card(ACE, DIAMONDS));
    Card trump_card(NINE,SPADES);
    Suit trump;
    bool orderup1 = anna->make_trump(
        trump_card,
        true,
        1,
        trump
    );
    ASSERT_TRUE(orderup1);
    delete anna;
}

TEST(test_only_left_bower) {
Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(JACK, SPADES));
    anna->add_card(Card(NINE, SPADES));
    anna->add_card(Card(KING, SPADES));
    anna->add_card(Card(JACK, CLUBS));
    anna->add_card(Card(ACE, DIAMONDS));
    Card trump_card(NINE,SPADES);
    Suit trump;
    bool orderup1 = anna->make_trump(
        trump_card,
        true,
        1,
        trump
    );
    ASSERT_TRUE(orderup1);
    delete anna;
}

TEST(test_pass_no_left_bower) {
Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(TEN, SPADES));
    anna->add_card(Card(NINE, SPADES));
    anna->add_card(Card(KING, SPADES));
    Card trump_card(NINE,SPADES);
    Suit trump;
    bool orderup1 = anna->make_trump(
        trump_card,
        true,
        1,
        trump
    );
    ASSERT_FALSE(orderup1);
    delete anna;
}

TEST(test_right_bower_notrump) {
Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(JACK, SPADES));
    anna->add_card(Card(NINE, CLUBS));
    anna->add_card(Card(KING, DIAMONDS));
    Card trump_card(TEN,SPADES);
    Suit trump;
    bool orderup1 = anna->make_trump(
        trump_card,
        true,
        1,
        trump
    );
    ASSERT_FALSE(orderup1); // will not trump
    delete anna;
}

TEST(test_only_bowers_play_left_bower) {
Player* anna = Player_factory("Anna", "Simple");
    anna->add_card(Card(JACK, SPADES));
    anna->add_card(Card(JACK, CLUBS));
    Card trump_card(TEN,SPADES);
    Suit trump;
    bool orderup1 = anna->make_trump(
        trump_card,
        true,
        1,
        trump
    );
      ASSERT_EQUAL(trump, SPADES)
    ASSERT_TRUE(orderup1); // will not trump
    delete anna;
}

TEST_MAIN()
