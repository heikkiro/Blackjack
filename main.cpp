#include "card.h"
#include "deck.h"
#include "game.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

// Blackjack by Heikki Rousu

int main()
{
	Game N;

	N.begin();
	N.playGame();

	return 0;
	
}