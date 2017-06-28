## Multiplayer Blackjack Game

Blackjack is a card game for making the score 21.
This program plays the game with at least two or more players and house.

## Blackjack Rules

* Draw two cards for all players and house at the start of the game
	* House draws one card to him/herself first, to player1 second, to player2 third, to player3 fourth, and so on..
	* After all players have received a card, house draws the second cards (same order)
* The score of each player or house is calculated by the card number
* Priority rules between house and players
	* House always wins on draw
	* If there is a tie between players, the player who has the highest card number wins (Ace = 1, King = 13, Queen = 12, Jack = 11)
	* If the highest card numbers are the same, shapes decide the priority (Spades > Diamonds > Hearts > Clovers)
	* If the shapes are the same, the second highest card number decides the winner
* If a player makes 21, the game is finished
* If a player has a higher score than 21, the player cannot play anymore
* If a players stands, the player cannot play anymore

## Game Rules

* Player1 plays in interactive mode
* House and other players play with the following decisions
	* Always decide **'HIT'** if current sum is below 13 (sum < 13)
	* Decide **'HIT'** or **'STAND'** with a 1/2 probability if sum is between 13 and 16
	* Always decide **'STAND'** if current sum is above 16 (sum >= 17)
* The number of decks is fixed at 4

## Data Structures & Functions

* `std::vector<string> cards` a global variable to store the cards used in the game
* `void swap (int i, int j)` a function which swaps two elements in global variable 'cards' by **index** *i* and *j*
* `void shuffle_cards (int num_decks)`
	* a function which shuffles cards of 'num_decks' of decks at **1000 times**
	* **shuffling algorithm**
		* initialize the cards by **LOW** score to **HIGH** score (e.g., 1c 1c ... 1h 1h ... 1d 1d ... 1s 1s ... 2c 2c ... 2h 2h ... 13s)
		* **swap two elements** of random indices at **1000 times**
* `string draw_card()` return a **BACKMOST** card in the 'cards' vector with pop_back()
* `int is_hit = rand() % 2` calculate probability of house rule #3 (1/2 probability)

## Command Line Arguments

```
./blackjack R N
```
* R: random seed number
* N: number of players
* *(stdin)* **h** (HIT) or **s** (STAND) for player1's decisions
