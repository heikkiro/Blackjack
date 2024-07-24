Blackjack - card game with text based IO.
Date: July 2024

Programmed by Heikki Rousu for Centria University of Applied Sciences C++ -programming course.
---------------------------------------------------------------------------------------------


This was my first attempt to write a actual program from scratch in C++. 
It is also the first program I have made apart from smaller programming exercises that I have completed with C# in my first year of ICT engineering studies.


Self-assessment of the programming task:

At first, I had no idea how to tackle this task so I went and searched for guidelines what to include in a program such as a game of blackjack.
I also knew quite little about the rules of blackjack.
I had to search for rules of blackjack and examples of what parts of the game would be good to create in separate classes.
Thinking this wouldn't be too difficult I quickly started to create different classes and create functions in them that I thought would be needed.
This was a mistake as I ended up with too much code that I hadn't compiled after each added part. The first attempt didn't really proceed into working program 
and I found out from forums that you should try to compile the code after each addition (something that was also taught in school and I forgot completely).
So, I ended up starting from scratch again and to advance in considerably smaller steps.

I'm starting to get the basic programming with loops, if-statements classes and what-not but at this point I'm not too familiar with C++ pointers and variable addresses.
It had some challenges in getting variables and functions to work outside their classes as I have very limited coding experience at this point. 
The result is not nearly as clear a code as I would like it to be and I think my if statement conditions for winning and losing are a bit too complex.
The gameplay of the game worked out all right for a first program I ever made. I ended up using way more time than was the approximated time for the task to take.
If I would do it again, I would try to refractor the code to look more cleaner in the "game" source file and use more private and protected variables. 



The information about gameplay and rules can also be read in the game in the beginning of each round,
but it requires user to scroll with mouse and full screen window to show properly.

+ - - - - - - - - - - - - - - - - + " 
| Gameplay and rules of blackjack | " 
+ - - - - - - - - - - - - - - - - + " 

Gameplay :
----------
The game asks you to choose different numerical inputs during gameplay. 
Entering wrong input results in asking for the user to input correct number.
To advance in the game you need to input a number given as an option and press enter.
You have the option to quit the game at the start of each round.

You begin a round by placing a bet of 5, 10 or 15 chips.
After placing your bet you enter *first stage* where you and the dealer are dealt two cards each.
Dealers hand value and second card are not revealed at this point.

You choose from two to three options:
1) Stay, which means you don't take anymore cards and see if the cards dealt to you are enough to win."

2) Hit, which means you ask for another card and it's value is added to your hands total value.

If your hand value with the two initial cards is 9, 10 or 11, you get the third option. (Double down).
3) Double Down, in which case you double your bet and must take one additional card and stay that hand.

If you have a pair (two hands of the same rank) your third option is Split pairs.
3) Split Pair, in which case you split your cards into two separate hands and must add equal amount of bet to the second hand.
   Each hand is played separately starting from the second hand. Once you have stayed with the second hand, you play the first hand.
   After you have stayed your both hands or bust them, it's the dealers turn. 

After the *first stage* you enter *second stage* and can hit for more cards until you stay or bust.
When you choose to stay, Double down or you bust the dealer gets his turn.

When it's the dealers turn then dealers card number two is revealed and the hands value shown.
If the dealers hand value is less than 17, the dealers takes a new card until value is 17 or more.
After dealer finishes hitting cards the game checks who won and player loses or wins chips.
Winnings or losses are added or taken from the players chips.
If player still has chips left at the end of the round, the game begins another round.
"After certain amount of rounds the deck is shuffled few times before next round.

Other game play related information:
- If player has an ace and handvalue is less than 12 the ace is counted as 11 and if higher than 12 the ace is counted as 1.



Rules of Blackjack: 
-------------------

Player's goal in the game is to get larger hand value than the dealer without going over 21.

Card values:
Ace can be worth 11 or 1. Face cards are 10 and any other cards values match their number.


Blackjack:
If a player's first two card are and ace and a 'ten-card' (hand value of 21 in two cards). This is a 'blackjack'.
The players turn then ends and it's the dealers turn.
If a player has a blackjack and the dealer has not, the dealer pays the player 1.5 times the amount of their bet.
If the dealer also has a blackjack with the two first cards, then it's a tie and the player gets his/hers chips back.


Splitting pairs: 
If the first two cards of the player's hand are a pair, the player can choose to treat them as two separate hands. 
The amount of the original bet is placed on one hand and an equal amount of bet must be placed on the other hand.
Getting a face card and ace with split pair hands is not counted as blackjack.
However, if dealer gets blackjack he wins players both hands.


Dealers play:
Once the player has played his/her hand/split hand it's the dealers turn.
When dealer begins his turn, the second card is shown. If the value of the hand is less than 17 the dealer takes another card.
The dealer continues to take more cards until total hand value is 17 or more, at which point the dealer must stand. 
If dealer has an ace, and counting it as 11 would bring the total to 17 or more (but not over 21),
the dealer must count the ace as 11 and stand.



Blackjack rules have been referenced from https://bicyclecards.com/how-to-play/blackjack


----------------------------------------
