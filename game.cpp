#include "game.h"
#include "card.h"
#include "deck.h"
#include "player.h"
#include "dealer.h"

#include <chrono>	// time measurements
#include <thread>	// sleep_for
#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std::this_thread;
using namespace std::chrono_literals;
using namespace std;

//Constructor
Game::Game()
{
}


int cardsDealt = 0;	//Global value of tracking dealt cards, needed for deck-objects function

// Header for the start of the game
void Game::begin()
{
	std::cout << "+ - - - - - - - + " << std::endl;
	std::cout << "|   BLACKJACK   | " << std::endl;
	std::cout << "+ - - - - - - - + " << std::endl;
	std::cout << std::endl;
}


void Game::playGame()
{

	// Create deck, assign cards to it and shuffle it
	// Create player and dealer
	Deck deck;
	Player player;
	Player splitHand;
	Dealer dealer;
	deck.assignCardsToDeck();	// create and add cards to the deck in order
	deck.deckShuffle();			// shuffle deck to a random order


	int roundNumber = 1;		// variable to keep track of played rounds
	bool gameLoop = true;		// assisting boolean variable for main loop	
	bool doubleDown = false;	// boolean variable for certain option and skipping another loop
	double currentBet = 0;		// variable for initiating current bet

	player.addToChips(100);		// Initial amount of chips for player
	dealer.addToChips(10000);	// Initial amount of chips for dealer
	splitHand.addToChips(100);	// Initial amount of chips for split hand, splitHand winnings or losses affect players chips


	double playersChips = player.getChipAmount();
	double* PtrChAm = &playersChips;
	double startingChips = *PtrChAm;

	cout << "Cards have been shuffled and the game is about to begin." << endl;

	std::cout << "(."; sleep_for(500ms);
	std::cout << "."; sleep_for(500ms);
	std::cout << "."; sleep_for(500ms);
	std::cout << ")"; sleep_for(500ms);

	system("cls");	// Clear screen for cleaner gameplay


	// MAIN GAME LOOP
	// Continue until chips run out or user decides to quit 
	do
	{
		// For each round initiate variables to a certain state/value
		double* betPtr = &currentBet;
		*betPtr = 0;
		bool splitPairs = false;
		bool betLoop = true;
		bool firstStageLoop = true;
		bool secondStageLoop = true;
		doubleDown = false;
		system("cls");	// "double check" Clear screen for cleaner gameplay

		do
		{
			//Show round number at the top of the window
			cout << "\n" << "- Round " << roundNumber << ". -" << "\n" << endl;
			cout << "-----------------------------------------------" << std::endl;

			// PLACING THE BET OR OPTION TO QUIT THE GAME OR VIEW RULES AND GAMEPLAY
			cout << "\n" << "Your account balance is: " << player.getChipAmount() << " C" << "\n" << endl;

			std::cout << "Minimum bet is 5C." << "\n" << endl;
			std::cout << "How much would you like to bet?" << endl;
			std::cout << "1) Place bet [5C]." << endl;
			std::cout << "2) Place bet [10C]." << endl;
			std::cout << "3) Place bet [15C]." << endl;
			std::cout << "8) Show the rules." << endl;
			std::cout << "0) Exit the game." << "\n" << endl;

			std::cout << "Choose an option: ( 1 / 2 / 3 / 8 / 0 ) " << endl;

			// Make sure that if input has multiple correct numbers 
			// it only counts the first and doesn't use rest of the numbers in later options
			string input;
			std::cin >> input;
			char choice = input[0];

			if (choice == '0' && roundNumber == 1) return;

			if (choice == '0' && roundNumber != 1)
			{
				betLoop = false;
				firstStageLoop = false;
				secondStageLoop = false;
				gameLoop = false;
				break;
			}

			else if (choice == '1')
			{
				*betPtr = 5;
				betLoop = false;
			}

			else if (choice == '2')
			{
				*betPtr = 10;
				betLoop = false;
			}

			else if (choice == '3')
			{
				*betPtr = 15;
				betLoop = false;
			}

			else if (choice == '8')
			{
				viewRulesAndGameplay();
				betLoop = true;
				system("pause");	// Pause screen and require any input before looping back to betting options
				system("cls");
			}

			else
			{
				system("cls");
				cout << "\n" << "... Please choose correct option." << "\n" << endl;
				betLoop = true;
			}

		} while (betLoop == true);

		cin.clear();
		system("cls");


		// After bet has been set 
		// deal two cards for dealer and two cards for player
		player.hit(deck.deal());
		dealer.hit(deck.deal());
		player.hit(deck.deal());
		dealer.hit(deck.deal());


		// SHOW STATUS
		// Dealers first card is shown but hands value and second card are not
		// Players hands value and cards are shown
		dealer.showDealersCards(false);
		std::cout << "\n" << " - Current bet = " << *betPtr << " C -" << endl;
		player.showPlayersCards();
		std::cout << endl;


		// FIRST STAGE MEETS DOUBLE DOWN OR SPLIT PAIRS REQUIREMENTS 
		// player has an option to double the bet and take another card, or continue with current bet or decide to stay 
		// if player has natural blackjack (ace and jack/queen/king) this stage is skipped.
		do
		{
			// If double down requirements are met 
			// if player has natural blackjack (ace and jack/queen/king) this stage is skipped.
			if (player.isBlackjack() == false && gameLoop == true && (player.valueOfHand() == 9 || player.valueOfHand() == 10 || player.valueOfHand() == 11) && (player.hand[0].getNum() != 5 && player.hand[1].getNum() != 5))
			{
				std::cout << "List of commands:" << endl;
				std::cout << "1) Stay (settle for your cards and end your round." << endl;
				std::cout << "2) Hit (Get additional card)." << endl;
				std::cout << "3) Double Down (double your bet and get one additional card)." << endl;
				std::cout << "\n" << "What would you like to do? ( 1 / 2 / 3 ) " << endl;


				string input_1;
				std::cin >> input_1;
				char choice_1 = input_1[0];

				if (choice_1 == '1')
				{
					cout << "\n" << "You chose to end your turn. " << endl << "Now it's the dealers turn." << "\n" << endl;
					sleep_for(3s);
					firstStageLoop = false;
					secondStageLoop = false;	// Skip the second stage and give the dealer it's turn
					break;
				}

				// HIT
				else if (choice_1 == '2')
				{
					player.hit(deck.deal());
					firstStageLoop = false;
					break;
				}

				// enough chips to double down
				else if (choice_1 == '3' && player.enoughToBet((*betPtr)) == true)
				{
					*betPtr = *betPtr * 2;
					player.hit(deck.deal());
					doubleDown = true;
					firstStageLoop = false;
					break;
				}

				// not enough chips to double down
				else if (choice_1 == '3' && player.enoughToBet((*betPtr)) == false)
				{
					cout << "\n" << "You don't have enough chips to bet that much." << "\n";
					cout << "Please choose another option." << endl;
					cout << endl;
				}

				else
				{
					cout << "\n" << "... Please choose correct option." << "\n" << endl;

				}
			}

			// FIRST STAGE MEETS SPLIT PAIRS REQUIREMENTS
			// firs two cards are a pair
			else if (gameLoop == true && (player.hand[0].getNum() == 5 && player.hand[1].getNum() == 5 || player.equalNumCards() == true))
			{

				std::cout << "List of commands:" << endl;
				std::cout << "1) Stay (settle for your cards and end your round." << endl;
				std::cout << "2) Hit (Get additional card)." << endl;
				std::cout << "3) Split pairs (split cards and play two separate hands, bet is doubled)." << endl;

				std::cout << "\n" << "What would you like to do? ( 1 / 2 / 3 ) " << endl;

				string input_1;
				std::cin >> input_1;
				char choice_1 = input_1[0];

				if (choice_1 == '1')
				{
					cout << "\n" << "You chose to end your turn. " << endl << "Now it's the dealers turn." << "\n" << endl;
					sleep_for(3s);
					firstStageLoop = false;
					secondStageLoop = false;	// Skip the second stage and give the dealer it's turn
					break;
				}

				else if (choice_1 == '2')
				{
					player.hit(deck.deal());
					firstStageLoop = false;
					break;
				}

				else if (choice_1 == '3' && player.enoughToBet((*betPtr)) == true)
				{
					*betPtr = *betPtr * 2;
					Card tempCard = player.takeCard();
					splitHand.putCard(tempCard);
					player.hit(deck.deal());
					splitHand.hit(deck.deal());
					splitPairs = true;
					firstStageLoop = false;
					break;
				}

				else if (choice_1 == '3' && player.enoughToBet((*betPtr)) == false)
				{
					system("cls");
					cout << "\n" << "You don't have enough money to bet that much." << "\n";
					cout << "Please choose another option." << endl;
					cout << endl;
				}

				else
				{
					system("cls");
					cout << "\n" << "... Please choose correct option." << endl;
					cout << endl;
				}
			}

			// If player has blackjack, skip stages to dealers turn
			else if (player.isBlackjack() == true)
			{
				firstStageLoop = false;
				secondStageLoop = false;
				cout << "\n" << "You got a blackjack, Congratulations." << "\n" << endl;
				sleep_for(350ms);
				break;
			}

			else
			{
				firstStageLoop = false;
				secondStageLoop = true;
			}

		} while (firstStageLoop == true && player.isBlackjack() == false);

		system("cls");


		//SECOND STAGE
		//Player has taken another card without possibilty of doubling down 
		//or player chose to hit or split pairs
		while (secondStageLoop == true && player.isBust() == false && doubleDown == false && gameLoop == true)
		{
			system("cls");
			dealer.showDealersCards(false);

			std::cout << "\n" << " - Current bet = " << *betPtr << "C -" << endl;
			if (splitPairs == false)
			{
				cout << "(current hand)" << endl;	// Clarifies which hand is currently being played
			}
			player.showPlayersCards();

			if (splitHand.valueOfHand() > 0)
			{
				cout << "Players second hand:" << "  (half of the bet is on this hand)" << endl;
				if (splitPairs == true)
				{
					cout << "(current hand)" << endl; // Clarifies which hand is currently being played
				}
				splitHand.showPlayersCards();
			}


			cout << endl;

			std::cout << "List of commands:" << endl;
			std::cout << "1) Stay, and end your round." << endl;
			std::cout << "2) Take another card." << endl;
			std::cout << "\n" << "What would you like to do? ( 1 / 2 ) " << endl;

			string input_2;
			std::cin >> input_2;
			char choice_2 = input_2[0];

			// in case of second hand, play second hand first
			if (choice_2 == '1' && splitPairs == true)
			{
				secondStageLoop = true;
				splitPairs = false;
			}

			else if (choice_2 == '1' && splitPairs == false)
			{
				secondStageLoop = false;
			}

			else if (choice_2 == '2' && splitPairs == true)
			{
				splitHand.hit(deck.deal());
				secondStageLoop = true;
			}

			else if (choice_2 == '2')
			{
				player.hit(deck.deal());
				secondStageLoop = true;
			}

			else
			{
				std::cout << "\n" << "... Please choose correct option." << "\n" << endl;
				system("pause");
				secondStageLoop = true;
			}
		}


		if (gameLoop == true && splitPairs == false)
		{
			system("cls");
			double halfOfBet = *betPtr / 2;
			dealer.showDealersCards(true);
			std::cout << "\n" << " - Current bet = " << *betPtr << "C -" << endl;
			player.showPlayersCards();

			// If split hand has been played the second hand is shown
			if (splitHand.valueOfHand() > 0)
			{
				cout << "Players second hand:" << endl;
				splitHand.showPlayersCards();
			}
			sleep_for(2s);
			cout << "\n" << endl;
		}


		// THIRD STAGE //
		// DEALERS TURN
		// If dealers hand value is less than 17 the dealer takes another card
		while (dealer.valueOfHand() < 17 && player.isBlackjack() == false && player.isBust() == false && gameLoop == true)
		{
			dealer.hit(deck.deal());

			system("cls");
			dealer.showDealersCards(true);
			std::cout << "\n" << " - Current bet = " << *betPtr << "C -" << endl;
			player.showPlayersCards();
			if (splitHand.valueOfHand() > 0)
			{
				cout << "Players second hand:" << endl;
				splitHand.showPlayersCards();
			}
			cout << endl;

			sleep_for(2s);	// Add delay for bit of suspense
		}


		// FOURTH STAGE //
		// ------------ //
		// DIFFERENT OUTCOMES
		// print who won and pay chips accordingly

		// Outcomes When pairs were not split
		if (gameLoop == true && splitHand.valueOfHand() == 0)
		{

			//Player bust, loses instantly
			if (player.isBust() == true && splitHand.valueOfHand() == 0)
			{
				cout << "You're bust. The dealer wins." << endl;
				dealer.addToChips(*betPtr);
				player.takeFromChips(*betPtr);
			}

			// When player wins
			else if (player.isBlackjack() == false && player.isBust() == false && player.valueOfHand() > dealer.valueOfHand())
			{
				cout << "Player wins." << endl;
				dealer.takeFromChips(*betPtr);
				player.addToChips(*betPtr);
			}

			// When player wins (house got over 21)
			else if ((dealer.isBust() == true) && player.valueOfHand() < 22)
			{
				cout << "\n" << "The house bust. Player wins." << endl;
				dealer.takeFromChips(*betPtr);
				player.addToChips(*betPtr);
			}

			// Incase of tie with regular hand values
			else if ((dealer.valueOfHand() < 22 && (dealer.valueOfHand() == player.valueOfHand())) && player.isBlackjack() == false)
			{
				cout << "\n" << "It's a draw. You get your bet back." << endl;
			}

			// Incase of tie with natural Blackjacks
			else if (player.isBlackjack() == true && dealer.isBlackjack() == true)
			{
				cout << "\n" << "The dealer also has natural blackjack. It's a draw. You get your bet back." << endl;
				cout << "You get your bet back." << endl;
			}

			// Incase of player has natural Blackjack and the dealer does not
			// Player wins 1,5x the bet and the money put in
			else if (player.isBlackjack() == true && dealer.isBlackjack() == false)
			{
				cout << "\n" << "You won with blackjack. You winnings are multiplied by 1.5" << endl;
				double wins = (*betPtr * 1.5);
				dealer.takeFromChips(wins);
				player.addToChips(wins);
			}

			// Dealer has blackjack and the player doesn't
			else if (player.isBlackjack() == false && dealer.isBlackjack() == true)
			{
				cout << "\n" << "Dealer wins with blackjack." << endl;
				cout << "You lose." << endl;
				dealer.addToChips(*betPtr);	//player loses money to the dealer
				player.takeFromChips(*betPtr);
			}

			// Dealer wins
			else
			{
				cout << "\n" << "Dealer wins the hand." << endl;
				dealer.addToChips(*betPtr);	//player loses money to the dealer
				player.takeFromChips(*betPtr);
			}

			//cout << "\n" << "\n" << "... New round begins shortly." << endl;
			cout << endl;
			system("pause");
		}

		// Different outcomes if player split pairs
		else if (gameLoop == true && splitHand.valueOfHand() != 0)
		{

			if (splitHand.valueOfHand() > dealer.valueOfHand()
				&& player.valueOfHand() < dealer.valueOfHand()
				&& dealer.isBlackjack() == false
				&& splitHand.isBust() == false && dealer.isBust() == false)
			{
				cout << "\n" << "Second hand won the dealer and the first hand lost." << endl;
				double halfBet = *betPtr / 2;
				dealer.takeFromChips(halfBet);
				player.takeFromChips(halfBet);	// first hand lost
				player.addToChips(halfBet);		// second hand won
			}

			else if (splitHand.valueOfHand() < dealer.valueOfHand() && player.valueOfHand() > dealer.valueOfHand() && dealer.isBlackjack() == false
				&& player.isBust() == false && dealer.isBust() == false
				|| (splitHand.isBust() == true && player.isBust() == false && player.valueOfHand() > dealer.valueOfHand()))
			{
				cout << "\n" << "First hand won the dealer and the second hand lost." << endl;
				double halfBet = *betPtr / 2;
				dealer.takeFromChips(halfBet);
				player.takeFromChips(halfBet);	// first hand won
				player.addToChips(halfBet);		// second hand lost
			}

			else if (splitHand.valueOfHand() > dealer.valueOfHand()
				&& player.valueOfHand() > dealer.valueOfHand()
				&& dealer.isBlackjack() == false && player.isBust() == false && splitHand.isBust() == false
				|| dealer.isBust() == true && player.isBust() == false && splitHand.isBust() == false)
			{
				cout << "\n" << "Players both hands won the dealer." << endl;
				dealer.takeFromChips(*betPtr);
				double halfBet = *betPtr / 2;
				player.addToChips(halfBet);		// first hand won
				player.addToChips(halfBet);		// second hand won
			}

			else if (dealer.isBlackjack() == false && splitHand.valueOfHand() < dealer.valueOfHand() && player.valueOfHand() < dealer.valueOfHand() && dealer.isBust() == false
				|| (dealer.isBust() == false && player.isBust() == true && splitHand.isBust() == true))
			{
				cout << "\n" << "Players both hands lost to the dealer." << endl;
				dealer.addToChips(*betPtr);
				double halfBet = *betPtr / 2;
				player.takeFromChips(halfBet);		// first hand lost
				player.takeFromChips(halfBet);		// second hand lost
			}

			else if (dealer.isBlackjack() == true)
			{
				cout << "\n" << "Players both hands lost, because the dealer has blackjack." << endl;
				dealer.addToChips(*betPtr);
				double halfBet = *betPtr / 2;
				player.takeFromChips(halfBet);		// first hand lost
				player.takeFromChips(halfBet);		// second hand lost
			}

			else if (splitHand.valueOfHand() == dealer.valueOfHand() && dealer.valueOfHand() < 22
				&& player.valueOfHand() < dealer.valueOfHand() && dealer.isBlackjack() == false)
			{
				cout << "\n" << "Second hand is tie with the dealers hand." << endl;
				cout << "\n" << "First hand lost to the dealers hand." << endl;

				double halfBet = *betPtr / 2;
				dealer.addToChips(halfBet);
				player.takeFromChips(halfBet);		// first hand lost
			}

			else if (player.valueOfHand() == dealer.valueOfHand() && dealer.valueOfHand() < 22
				&& splitHand.valueOfHand() < dealer.valueOfHand() && dealer.isBlackjack() == false)
			{
				cout << "\n" << "First hand is tie with the dealers hand." << endl;
				cout << "\n" << "Second hand lost to the dealers hand." << endl;

				double halfBet = *betPtr / 2;
				dealer.addToChips(halfBet);
				player.takeFromChips(halfBet);		// second hand lost
			}

			// Incase of 'double tie' no chips are moved
			else if (dealer.valueOfHand() < 22
				&& splitHand.valueOfHand() == dealer.valueOfHand() && player.valueOfHand() == dealer.valueOfHand()
				&& dealer.isBlackjack() == false)
			{
				cout << "\n" << "Both hands are equal to the dealers hands value." << endl;
				cout << "\n" << "It's a tie." << endl;

			}

			else
			{
				cout << "Something wen't wrong and outcome is not clear." << endl;
			}

			cout << endl;
			system("pause");

		}
		// END OF FOURTH STAGE


		// Empty hands before next round
		dealer.clearHand();
		player.clearHand();
		splitHand.clearHand();

		std::cout << endl;
		roundNumber += 1;	// keep count of rounds for resuffle

		if (player.getChipAmount() <= 0)
		{
			system("cls");

			cout << "\n" << "I'm sorry to say but..." << endl;
			cout << "You don't have any chips left. It's time to quit." << endl;
			sleep_for(3s);
			gameLoop = false;
		}

		// Resuffle deck so that it doesn't run out or just start again with same cards
		if (roundNumber % 5 == 0 && gameLoop == true)
		{
			cout << "\n" << "Suffling deck. Please wait." << "\n" << endl;
			deck.deckShuffle();
			deck.deckShuffle();
			sleep_for(250ms);
		}


	} while (gameLoop == true);


	// END OF GAME
	// If rounds have been played and player ends the game
	system("cls");
	cout << "End statistics: " << "\n" << "-------------------" << endl;
	cout << "\n" << "You started with: " << startingChips << " chips. " << endl;
	cout << "You quit while having: " << player.getChipAmount() << " chips." << endl;

	if (startingChips > player.getChipAmount())
	{
		double chipsLost = player.getChipAmount() - startingChips;
		cout << "You lost :" << chipsLost << " chips" << endl;
		
		cout << "\n" << "Better luck next time." << endl;

	}

	else if (startingChips < player.getChipAmount())
	{
		double chipsWon = player.getChipAmount() - startingChips;
		cout << "You won :" << chipsWon << " chips" << endl;
		cout << "\n" << "Good for you!" << endl;
	}


	else
	{
		double chipsWon = player.getChipAmount() - startingChips;
		cout << "You won :" << chipsWon << " chips" << endl;
		cout << "\n" << "At least you didn't lose." << endl;
	}

	cout << "\n" << "Thank you for playing BlackJack." << "\n" << "\n" << endl;

	cout << "To exit the game ";
	system("pause");	// Pause screen before exiting and require any input
	return;

}


// Rules and gameplay
void Game::viewRulesAndGameplay()
{
	system("cls");
	cout << "+ - - - - - - - - - - - - - - - - + " << std::endl;
	cout << "| Gameplay and rules of blackjack | " << std::endl;
	cout << "+ - - - - - - - - - - - - - - - - + " << std::endl;
	cout << "\n" << endl;

	cout << "Gameplay : " << endl;
	cout << "----------------" << "\n" << endl;
	cout << "The game asks you to choose different numerical inputs during gameplay." << endl;
	cout << "Entering a wrong input results in asking for the user to input correct number." << endl;
	cout << "To advance in the game you need to input a number given as an option and press enter." << endl;
	cout << "You have the option to quit the game at the start of each round." << endl;
	cout << endl;
	cout << "You begin a round by placing a bet of 5, 10 or 15 chips." << endl;
	cout << "After placing your bet, you enter *first stage* where you and the dealer are dealt two cards each." << endl;
	cout << "Dealers hand value and second card are not revealed at this point." << endl;
	cout << endl;
	cout << "You choose from two to three options:" << endl;
	cout << "1) Stay, which means you don't take anymore cards and see if the cards dealt to you are enough to win." << "\n" << endl;
	cout << "2) Hit, which means you ask for another card and it's value is added to your hands total value." << endl;
	cout << endl;
	cout << "If your hand value with the two initial cards is 9, 10 or 11, you get the third option. (Double down). " << endl;
	cout << "3) Double Down, in which case you double your bet and must take one additional card and stay that hand." << endl;
	cout << endl;
	cout << "If you have a pair (two hands of the same rank) your third option is Split pairs. " << endl;
	cout << "3) Split Pair, in which case you split your cards into two separate hands and must add equal amount of bet to the second hand." << endl;
	cout << "   Each hand is played separately starting from the second hand. Once you have stayed with the second hand, you play the first hand." << endl;
	cout << "   After you have stayed your both hands or bust them, it's the dealers turn. " << endl;
	cout << "\n" << endl;

	cout << "After the *first stage* you enter *second stage* and can hit for more cards until you stay or bust." << endl;
	cout << "When you choose to stay, Double down or you bust the dealer gets his turn." << endl;
	cout << endl;
	cout << "When it's the dealers turn then dealers card number two is revealed and the hands value shown." << endl;
	cout << "If the dealers hand value is less than 17, the dealers takes a new card until value is 17 or more." << "\n" << endl;
	cout << "After dealer finishes hitting cards the game checks who won and player loses or wins chips." << endl;
	cout << "Winnings or losses are added or taken from the players chips." << endl;
	cout << "If player still has chips left at the end of the round, the game begins another round." << endl;
	cout << "After certain amount of rounds the deck is shuffled few times before next round." << endl;
	cout << endl;
	cout << "Other game play related information:" << endl;
	cout << "- If player has an ace and handvalue is less than 12 the ace is counted as 11 and if higher than 12 the ace is counted as 1." << endl;
	cout << "\n" << "\n" << endl;
	cout << "Rules of Blackjack: " << endl;
	cout << "-------------------" << "\n" << endl;
	cout << "Player's goal in the game is to get larger hand value than the dealer without going over 21." << endl;
	cout << "\n" << "Card values:" << endl;
	cout << "Ace can be worth 11 or 1. Face cards are 10 and any other cards values match their number." << endl;
	cout << "\n" << endl;
	cout << "Blackjack:" << endl;
	cout << "If a player's first two card are and ace and a 'ten-card' (hand value of 21 in two cards). This is a 'blackjack'. " << endl;
	cout << "The players turn then ends and it's the dealers turn." << endl;
	cout << "If a player has a blackjack and the dealer has not, the dealer pays the player 1.5 times the amount of their bet." << endl;
	cout << "If the dealer also has a blackjack with the two first cards, then it's a tie and the player gets his/hers chips back." << endl;
	cout << "\n" << endl;
	cout << "Splitting pairs: " << endl;
	cout << "If the first two cards of the player's hand are a pair, the player can choose to treat them as two separate hands. " << endl;
	cout << "The amount of the original bet is placed on one hand and an equal amount of bet must be placed on the other hand." << endl;
	cout << "Getting a face card and ace with split pair hands is not counted as blackjack. " << endl;
	cout << "However, if dealer gets blackjack, he wins players both hands." << endl;
	cout << "\n" << endl;
	cout << "Dealers play:" << endl;
	cout << "Once the player has played his/her hand/split hand it's the dealers turn." << endl;
	cout << "When dealer begins his turn, the second card is shown. If the value of the hand is less than 17 the dealer takes another card." << endl;
	cout << "The dealer continues to take more cards until total hand value is 17 or more, at which point the dealer must stand. " << endl;
	cout << "If dealer has an ace, and counting it as 11 would bring the total to 17 or more (but not over 21), " << endl;
	cout << "the dealer must count the ace as 11 and stand." << endl;
	cout << "\n" << "\n" << "\n" << endl;
	cout << "Blackjack rules have been referenced from https://bicyclecards.com/how-to-play/blackjack" << endl;
}
