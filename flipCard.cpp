//
// Created by cohen on 5/19/2020.
//
/**********************************************************************************************************************/
#include "flipCard.h"
/**********************************************************************************************************************/

/**********************************************************************************************************************/
//                         __
//    _________ __________/ /
//   / ___/ __ `/ ___/ __  /
//  / /__/ /_/ / /  / /_/ /
//  \___/\__,_/_/   \__,_/
//
card::card() {}// default constructor for the card class
card::card(int in1, int in2) {// overloaded assignment operator for card class
    value = in1;// store the first input in value
    suit = in2;// store the second input in suit
}
void card::cardPrint() {// function that prints a text image of the playing card based on the stored values
    _setmode(_fileno(stdout), _O_U16TEXT);
    char valueChar;
    switch (value + 1) {
        case 11:
            valueChar = 'J';
            break;
        case 12:
            valueChar = 'Q';
            break;
        case 13:
            valueChar = 'K';
            break;
        case 14:
            valueChar = 'A';
            break;
    }

    wprintf(L"\u250c\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2510\n");
    if (value + 1 < 10) {
        wprintf(L"\u2502 %d       \u2502\n", value + 1);
    } else if (value + 1 == 10) {
        wprintf(L"\u2502 %d      \u2502\n", value + 1);
    } else {
        wprintf(L"\u2502 %c       \u2502\n", valueChar);
    }
    wprintf(L"\u2502         \u2502\n");

    switch (suit) {
        case 1:
            wprintf(L"\u2502    %s    \u2502\n", CLUB);
            break;
        case 2:
            wprintf(L"\u2502    %s    \u2502\n", DIAMOND);
            break;
        case 3:
            wprintf(L"\u2502    %s    \u2502\n", HEART);
            break;
        case 4:
            wprintf(L"\u2502    %s    \u2502\n", SPADE);
            break;
    }

    wprintf(L"\u2502         \u2502\n");
    if (value + 1 < 10) {
        wprintf(L"\u2502       %d \u2502\n", value + 1);
    } else if (value + 1 == 10) {
        wprintf(L"\u2502      %d \u2502\n", value + 1);
    } else {
        wprintf(L"\u2502       %c \u2502\n", valueChar);
    }
    wprintf(L"\u2514\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2518\n\n");
}
/**********************************************************************************************************************/

/**********************************************************************************************************************/
//         __          __
//    ____/ /__  _____/ /__
//   / __  / _ \/ ___/ //_/
//  / /_/ /  __/ /__/ ,<
//  \__,_/\___/\___/_/|_|
//
deck::deck() {}// default constructor for the card class
deck::deck(bool){// overloaded assignment operator for deck class
    int value = 1;// declare value as an int and set equal to 1
    int suit = 1;// declare suit as an int and set equal to 1
    for (int i = 1; i <= 52; i++) {// loop 52 times
        deckList.emplace_back(card(value,suit));// create a new card with current suit/value and store it at top of list
        if (value == 13) {// when the value reaches 13...
            value = 1;// set it back to 1
            suit++;// and increase the suit by one
        } else {
            value++;// otherwise just increase the value
        }
    }
}
card deck::deal() {// returns the top card in the deck by value and removes the card from the deck
    card temp = deckList.front();// store the top card in a temporary container
    deckList.pop_front();// delete the front card from the deck
    return temp;// return the top card that was stored in the temporary container
}
void deck::replace(card in1) {// passed a card as a parameter by value and stores it at the bottpm of the deck
    deckList.push_back(in1);//  stores the input card at the top(achieves desired affect) of the deck
}
void deck::shuffle() {// shuffles the deck of cards using the fisher-yates shuffle algorithm
    card array[52]; //declare a temporary card array
    copy(deckList.begin(), deckList.end(), array);// use the list copy function to store the deck in the temp array
    srand(time(nullptr));// seed the random function with the current time
    for (int j = 0; j < 3; j++) {// do three shuffles
        for (int i = deckList.size()-1; i >= 0; i--) {// iterate for the size of the array from the right to left
            card temp = array[i];// store the current array position in temp container
            int randIndex = rand() % (i+1);// create a random int from the remaining iterations
            array[i] = array[randIndex];// store the value at the random index at the current iteration position
            array[randIndex] = temp;// store the original value at the random index position
        }
    }
    deckList.clear();// deconstruct the deckList
    for (int i = 0; i < 52; i++) {// loop 52 times
        deckList.emplace_back(array[i]);// copy the array back into the deckList
    }
}
void deck::deckPrint() {// debugging function that will print the deckList from start to bottom
    list <card> :: iterator it;// from list creat an iterator value
    for (it = deckList.begin(); it != deckList.end(); ++it){// loop through deskList from beginning to end
        wcout << it->value << "\t" << it->suit << endl;// print the cards value and suit @ it
        it->cardPrint();// call the cards print function @ it
    }
}
double deck::deckScan() {// function for determining the score of a game
    list<card>::iterator it;// from list creat an iterator value
    double score = 0.0;// declare score as 0
    for (it = deckList.begin(); it != deckList.end(); ++it) {// loop through (players)deskList from beginning to end
        if (it->value == 13){score = score + 10.0;}
        else if (it->value >= 10 && it->value <= 12){score = score + 5.0;}
        else if (it->value == 6){score = (score / 2.0);}
        else if (it->value >= 1 && it->value <= 5){score = 0.0;}
        if (it->suit == 3){score = score + 1.0;}
    }
    return score;
}
/**********************************************************************************************************************/

/**********************************************************************************************************************/

//            __      __          __
//     ____ _/ /___  / /_  ____ _/ /
//    / __ `/ / __ \/ __ \/ __ `/ /
//   / /_/ / / /_/ / /_/ / /_/ / /
//   \__, /_/\____/_.___/\__,_/_/
//  /____/
void flipCardPlay(){// global function that controls the game and handles user interaction
    deck deckDealer(true);// initiate the dealers deck by creating a deck obj with a full deck
    deckDealer.shuffle();// shuffle the dealers deck
    deck deckPlayer;// initiate the players deck by creating a deck obj with an empty deck
    int playerChoice;// declare an int to store the players input
    bool exit = false;// set the initial exit value for do-while loops exit status to false
    do {
        wcout << "*******Menu*******\n1. Hit\n2. Quit\nSelect an option:";// create a simple menu for the user
        wcin >> playerChoice;// store players response into playerChoice
        switch (playerChoice) {// use players choice to control a switch
            case 1:// 1. Hit
                deckPlayer.replace(deckDealer.deal());// move the top card from deckDealer and store in deckPlayer
                deckPlayer.deckList.back().cardPrint();// print the card that was just added to deckPlayer
                wcout << "current score: " <<deckPlayer.deckScan() << endl;// find than print the score of players deck
                break;
            case 2:// 2. Quit
                exit = true;// exit the do-while loop
                break;
            case 3:// debugging tool to print the entire dealer's deck
                deckDealer.deckPrint();//
                break;
            case 4:// debugging tool to print the entire player's deck
                deckPlayer.deckPrint();
                break;
            default:// the player selected a choice not on the user menu
                wcout << "That is an invalid choice, pick from one of the options" << endl;
                break;
        }
    }while (!exit && !deckDealer.deckList.empty());// while exit is still false and while the dealer still has cards
    wcout << "Final Score: " <<deckPlayer.deckScan() << endl;// find than print the final score of players deck
    deckDealer.deckList.clear();// deconstruct the dealer's deck
    deckPlayer.deckList.clear();// deconstruct the player's deck
}
/**********************************************************************************************************************/