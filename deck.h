#include "card.h"
#include "defaultplayer.h"

#include <vector>

using namespace std;

class Deck
{
public:
	Deck();
	~Deck();	//Destructor  

	void assignCardsToDeck();
	Card deal();

	vector<Card> deckShuffle();
	
	int dealtCards = 0;

	//static variables
public:
	static int cardsDealt;

private:
	
	vector<Card> deck;	//(vector type) array of cards
};

