#ifndef CARD_H
#define CARD_H


class Card
{
public:
	Card();
	Card(int num, char suit, int value);
	int getNum() const;
	char getSuit() const;
	int getValue() const;

private:
	int num;	//Cards number can be 1-13
	char suit;	//Cards suit can be S = Spade , H = Heart , C = Club , D = Diamond 
	int value;	//Cards value ranges from 1 to 10 and ace can be 1 or 11

};

#endif  //CARD_H

