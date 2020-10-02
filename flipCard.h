//
// Created by cohen on 5/19/2020.
//

#ifndef FLIPCARDGAME_FLIPCARD_H
#define FLIPCARDGAME_FLIPCARD_H
/**********************************************************************************************************************/
#include <io.h>
#include <iostream>
#include <fcntl.h>
#include <string>
#include <list>
#include <ctime>
using namespace std;
#define SPADE L"\u2660"
#define CLUB L"\u2663"
#define HEART L"\u2665"
#define DIAMOND L"\u2666"
/**********************************************************************************************************************/

/**********************************************************************************************************************/
//                         __
//    _________ __________/ /
//   / ___/ __ `/ ___/ __  /
//  / /__/ /_/ / /  / /_/ /
//  \___/\__,_/_/   \__,_/
//
class card {
public:
    card();// default constructor for the card class
    card(int, int);// overloaded assignment operator for card class
    void cardPrint();// function that prints a text image of the playing card based on the stored values
public:
    int value;// stores the value of the card as an int
    int suit;// stores the suit of the card as an int
};
/**********************************************************************************************************************/

/**********************************************************************************************************************/
//         __          __
//    ____/ /__  _____/ /__
//   / __  / _ \/ ___/ //_/
//  / /_/ /  __/ /__/ ,<
//  \__,_/\___/\___/_/|_|
//
class deck {
public:
    list <card> deckList;
    deck();// default constructor for the deck class
    deck(bool);// overloaded assignment operator for deck class
    card deal();// returns the top card in the deck by value and removes the card from the deck
    void replace(card);// passed a card as a parameter by value and stores it at the bottom of the deck
    void shuffle();// shuffles the deck of cards using the fisher-yates shuffle algorithm
    void deckPrint();// debugging function that will print the deckList from start to bottom
    double deckScan();// function for determining the score of a game
};
/**********************************************************************************************************************/

/**********************************************************************************************************************/

//            __      __          __
//     ____ _/ /___  / /_  ____ _/ /
//    / __ `/ / __ \/ __ \/ __ `/ /
//   / /_/ / / /_/ / /_/ / /_/ / /
//   \__, /_/\____/_.___/\__,_/_/
//  /____/
void flipCardPlay();// global function that controls the game and handles user interaction
/**********************************************************************************************************************/

#endif //FLIPCARDGAME_FLIPCARD_H
