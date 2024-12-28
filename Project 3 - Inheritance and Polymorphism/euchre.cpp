#include <iostream>
#include <cassert>
#include <array>
#include <algorithm> 
#include <fstream>
#include <vector>
#include "Card.hpp"
#include "Pack.hpp"
#include "Player.hpp"

using namespace std;

  void error_message(){
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
  }

class Game {
  private:
  std::vector<Player*> players;
  Pack pack;
  string shuffle_deck;
  int points_to_win;
  int hand_number=0;
  int dealer=0;
  int team_1_points = 0;
  int team_2_points = 0;
  Suit trump_suit;
  int ordering_player = -1;

 public:
  Game(ifstream& pack_filename, const string &shuffle_deck , int points_to_win,  
  const vector<string> &player_info)
  : pack(pack_filename), shuffle_deck(shuffle_deck), 
  points_to_win(points_to_win) {
    for (int i = 0; i < player_info.size(); i += 2) {
      string name = player_info.at(i);
      string type = player_info.at(i + 1);
      
      players.push_back(Player_factory(name, type));
      // Additional implimintation for constructor
    }
  }

  void play(){
    while (team_1_points < points_to_win 
    && team_2_points < points_to_win) {
      
      cout <<"Hand " << hand_number <<endl;
      shuffle();
      deal();
      play_hand();

      ++hand_number;
      dealer = (dealer + 1) % 4; //Move to the next dealer
    }

    if (team_1_points >= points_to_win) {
      cout << players.at(0)->get_name() << " and " 
      << players.at(2)->get_name() << " win!" << endl;
    } else if (team_2_points >= points_to_win) {
      cout << players.at(1)->get_name() << " and " 
      << players.at(3)->get_name() << " win!" << endl;
    }
  }

  void shuffle(){
    pack.reset();
    if (shuffle_deck == "shuffle") {
      pack.shuffle();
    }
  }


  void deal(){
    assert(players.size()== 4);
    int eldest_hand  = (dealer + 1) % players.size();
    cout << players.at(dealer)->get_name() 
    << " deals" << endl; //Access the name using player class function

    for (int i = 0; i < players.size(); ++i) {
    // Alternate between dealing 3&2 cards
    Player *player = players[(eldest_hand+i) % players.size()];
      if (i % 2 == 0) {
        for (int j = 0; j < 3; ++j) {
          player->add_card(pack.deal_one());// Player to the left receves it first
        }
      }else{
        for (int j = 0; j < 2; ++j) {
          player->add_card(pack.deal_one());// Alternating one person
        }
      }
    }
    for (int i = 0; i < players.size(); ++i) {
      Player *player = players[(eldest_hand+i) % players.size()];
      if (i % 2 == 0) {
        for (int j = 0; j < 2; ++j) {
          player->add_card(pack.deal_one());// then 2-3-2-3 cards
        }
      }else{
        for (int j = 0; j < 3; ++j) {
          player->add_card(pack.deal_one());
        }
      }
      
    }

    Card upcard = pack.deal_one(); 
    cout << upcard << " turned up" << endl; 
    make_trump(upcard);
  }

    
  void make_trump(Card upcard) {
    int eldest_hand = (dealer + 1) % players.size();
    bool all_pass = true;

    for(int i = 0; i < 4 && all_pass; ++i) {
      int player_i = (eldest_hand+i)%players.size();
      bool is_dealer = (player_i == dealer);

      if (players.at(player_i) -> make_trump(upcard, 
      is_dealer, 1, trump_suit)) {
        cout << players.at(player_i) -> get_name() 
        << " orders up " << trump_suit <<  endl; 

        ordering_player = player_i;
        players.at(dealer)->add_and_discard(upcard);
        cout << endl;
        all_pass=false;
        break;
      }
      else {
        cout << players.at(player_i) -> get_name() 
        << " passes" << endl;
    
      }
    }
    if(all_pass){
      Suit upcard_suit = upcard.get_suit();
      trump_suit = Suit_next(upcard_suit);
      for(int i = 0; i < 4 && all_pass; ++i) {
        int player_i = (eldest_hand+i) % players.size();
        bool is_dealer = (player_i == dealer);

        if (is_dealer && i == 3) {
          if (players.at(player_i) -> make_trump(upcard, 
          is_dealer, 2, trump_suit)) {
          //players.at(player_i) -> make_trump(upcard, is_dealer, 2, trump_suit);
          cout << players.at(dealer)->get_name() << " orders up " 
          << trump_suit<< endl;
          }
          cout << endl;
          ordering_player = player_i;
          all_pass = false;
          //cout << endl;
          break;
        } 
         if (players.at(player_i) -> make_trump(upcard, 
        is_dealer, 2, trump_suit)) {
          
          cout << players.at(player_i) -> get_name() 
          << " orders up " << trump_suit << endl; 
          cout << endl;
          ordering_player= player_i;
          all_pass=false;
          
          break;
        } 
        else{
          cout << players.at(player_i) -> get_name() 
          << " passes" << endl;
        }

        // if(is_dealer && all_pass){ //Screw the dealer
        //   players.at(player_i) -> make_trump(upcard, 
        //all_pass, 2, trump_suit);
        //   cout << players.at(dealer)->get_name() 
        //<< " orders up " 
        //<< trump_suit << endl;
        //   ordering_player = dealer;
        //   all_pass=false;
        //   break;
        // }
      }
    }
    //cout << endl;
    
  }


  void play_hand() {
    int winner = (dealer+1) % 4;
    Card led_card;
    int tricks_team_1 = 0; 
    int tricks_team_2 = 0; 

    for(int i = 0; i < 5; ++i) {

      led_card = players.at(winner)->lead_card(trump_suit);
      cout << led_card  << " led by " << players.at(winner)->get_name() << endl;
      Card highest_card =led_card;
      int highest_player = winner;
      
      for(int j = 1; j < players.size(); ++j) {
        int player_i = (winner +j)% players.size();
        Card card_played = players.at(player_i)->play_card(led_card, trump_suit);
        cout << card_played << " played by " <<  
        players.at(player_i) -> get_name()<<endl; 

        if (!Card_less(card_played, highest_card, led_card, trump_suit)) {
          highest_card = card_played;
          highest_player = player_i;
        }
      }
 
      cout << players.at((highest_player) % players.size())->get_name() 
      << " takes the trick\n" << endl;
      if (highest_player % 2 == 0) {
        ++tricks_team_1;
      } else {
        ++tricks_team_2;
      }
      winner =highest_player;
    }
    scoring(tricks_team_1,  tricks_team_2);
  }


  void scoring (int tricks_team_1, int tricks_team_2){
    bool team_1_ordered = (ordering_player == 0 || ordering_player == 2); 
    bool team_2_ordered = (ordering_player == 1 || ordering_player == 3);

    if (tricks_team_1 >= 3) {

      cout << players.at(0)->get_name() << " and " 
        << players.at(2)->get_name() << " win the hand" << endl;
      if(team_1_ordered){  
        if (tricks_team_1 == 5) {
          team_1_points += 2; // Team 1 gets 2 points for a march
          cout << "march!" << endl;
        } else{
          team_1_points += 1; 
          }
        } else{
          team_1_points += 2; // Team 1 gets 2 points for euchred
          cout << "euchred!" << endl;
        }
    } else if (tricks_team_2 >= 3) {
      cout << players.at(1)->get_name() << " and " 
        << players.at(3)->get_name() << " win the hand" << endl;

      if (team_2_ordered){
        if (tricks_team_2 == 5) {
          team_2_points += 2; // Team 2 gets 2 points for a march
          cout << "march!" << endl;
        }else{
        team_2_points += 1; 
      }
      } else {
        team_2_points += 2; // Team 2 gets 2 points for euchred
        cout << "euchred!" << endl;
      }
    }
    
    cout << players.at(0)->get_name() << " and " 
    << players.at(2)->get_name() << " have " 
    << team_1_points << " points" << endl;
    cout << players.at(1)->get_name() << " and " 
    << players.at(3)->get_name() << " have " 
    << team_2_points << " points\n" << endl;
  }


  void delete_players(){
    for (size_t i = 0; i < players.size(); ++i) {
      delete players[i];
    }
  }
};

int main(int argc, char **argv) {
  for (int i = 0; i < argc; ++i) {
    cout << argv[i] << " ";
  }
    cout << endl;
  // Read command line args and check for errors
  string pack_filename = argv[1];
  string shuffle_deck = argv[2];
  int points_to_win = stoi(argv[3]);
  vector<string> player_info = {argv[4], argv[5], argv[6], argv[7], 
  argv[8], argv[9], argv[10], argv[11]};

  //Errors
  if (argc != 12){
    error_message();
    return 1;
  }

  if (!(points_to_win>0 && points_to_win<=100)){
    error_message();
    return 1;
  }
  
  if (shuffle_deck != "shuffle" && shuffle_deck != "noshuffle"){
    error_message();
    return 1;
  }

  for (int i = 1; i < player_info.size(); i += 2) {
    if (player_info.at(i) != "Human" && player_info.at(i) != "Simple") {
        error_message();
        return 1;
    }
  }

  ifstream file(pack_filename);
  if(!file.is_open()){
    cout << "Error opening " << pack_filename << endl;
    return 1;
  }
  
  Game game(file, shuffle_deck, points_to_win, player_info);
  game.play();
  game.delete_players();
  return 0;
}