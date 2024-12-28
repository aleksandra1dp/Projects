#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

// Add more test cases here

TEST(test_card_face_or_ace) {
    Card c1(JACK, SPADES);
    ASSERT_TRUE(c1.is_face_or_ace());

    Card c2(TWO, HEARTS);
    ASSERT_FALSE(c2.is_face_or_ace());

    Card c3(ACE, DIAMONDS);
    ASSERT_TRUE(c3.is_face_or_ace());
}


TEST(test_card_right_left_bower) {
    Card c1(JACK, SPADES);
    Card c2(JACK, CLUBS);
    
    ASSERT_TRUE(c1.is_right_bower(SPADES));
    ASSERT_FALSE(c1.is_right_bower(HEARTS));
    ASSERT_TRUE(c2.is_left_bower(SPADES));
    ASSERT_FALSE(c2.is_left_bower(CLUBS));
}

TEST(test_card_trump) {
    Card c2(JACK, CLUBS);
    Card c3(ACE, DIAMONDS);
    Card c1(ACE, CLUBS);

    ASSERT_FALSE(c3.is_trump(SPADES)); 
    ASSERT_TRUE(c2.is_trump(SPADES));
    ASSERT_TRUE(c1.is_trump(CLUBS));
    ASSERT_FALSE(c1.is_trump(HEARTS));
}

TEST(test_card_comparisons) {
    Card ace_spades(ACE, SPADES);
    Card king_hearts(KING, HEARTS);
    Card ace_hearts(ACE, HEARTS);

    ASSERT_TRUE(king_hearts < ace_hearts);   
    ASSERT_TRUE(ace_spades < ace_hearts);   

    Card nine_hearts(NINE, HEARTS);
    ASSERT_TRUE(king_hearts > nine_hearts);   
    ASSERT_TRUE(ace_hearts > ace_spades);   

    Card ace_hearts2(ACE, HEARTS);
    ASSERT_TRUE(ace_hearts == ace_hearts2);
    ASSERT_FALSE(ace_hearts == ace_spades);

    ASSERT_TRUE(ace_hearts != ace_spades);
    ASSERT_FALSE(ace_hearts != ace_hearts2);  
}

TEST(test_card_streams) {
    Card c(ACE, HEARTS);

    ostringstream os;
    os << c;
    ASSERT_EQUAL(os.str(), "Ace of Hearts");

    istringstream iss("King of Diamonds");
    Card king_diamonds;
    iss >> king_diamonds;
    ASSERT_EQUAL(king_diamonds.get_rank(), KING);
    ASSERT_EQUAL(king_diamonds.get_suit(), DIAMONDS);
}

TEST(test_card_output) {
    Card ace_hearts(NINE, HEARTS);
    ostringstream oss;
    oss << ace_hearts;
    ASSERT_EQUAL(oss.str(), "Nine of Hearts");
}

TEST(test_card_input) {
    istringstream iss("Nine of Hearts");
    Card card;
    iss >> card;
    ASSERT_EQUAL(card.get_rank(), NINE);
    ASSERT_EQUAL(card.get_suit(), HEARTS);
}

TEST(test_suit_next) {
    ASSERT_EQUAL(Suit_next(SPADES), CLUBS);
    ASSERT_EQUAL(Suit_next(HEARTS), DIAMONDS);
}


TEST(test_card_less_trump) {
    Card ace_spades(ACE, SPADES);
    Card ten_hearts(TEN, HEARTS);

    ASSERT_TRUE(Card_less(ten_hearts, ace_spades, SPADES));  // Spades is trump
    ASSERT_FALSE(Card_less(ace_spades, ten_hearts, SPADES));

    Card jack_hearts(JACK, HEARTS);
    Card nine_spades(NINE, SPADES);
    ASSERT_TRUE(Card_less(nine_spades, jack_hearts, HEARTS)); 
    ASSERT_FALSE(Card_less(jack_hearts, nine_spades, HEARTS));
}

TEST(test_card_less_trump_and_led) {
    Card ace_spades(ACE, SPADES);
    Card ten_hearts(TEN, HEARTS);
    Card queen_spades(QUEEN, SPADES);

    ASSERT_TRUE(Card_less(ten_hearts, ace_spades, ace_spades, SPADES));  // Spades led and trump
    ASSERT_FALSE(Card_less(ace_spades, ten_hearts, ace_spades, SPADES));  
}


TEST(test_Card_less_led_suit) {
    Card nine_spades(NINE, SPADES);
    Card queen_spades(QUEEN, SPADES);
    ASSERT_TRUE(Card_less(nine_spades, queen_spades, Card(QUEEN, SPADES), HEARTS)); //Compare based on led suit
}

TEST(test_Card_get_Suit){
    Card left_bower(JACK, CLUBS);
    Card right_bower(JACK, SPADES);
    ASSERT_EQUAL(left_bower.get_suit(SPADES), SPADES); // Should return trump suit
    ASSERT_EQUAL(right_bower.get_suit(SPADES), SPADES); 

    // Non-bower card: returns its own suit
    Card card(QUEEN, HEARTS); 
    ASSERT_EQUAL(card.get_suit(SPADES), HEARTS);
}

TEST(test_card_less_than){
    Suit trump = DIAMONDS;
    Card card1(ACE,SPADES);
    Card card2(ACE,HEARTS);
    ASSERT_TRUE(Card_less(card1, card2, trump));
}
TEST_MAIN()
