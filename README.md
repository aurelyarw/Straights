# STRAIGHTS
A 4-players card game built using C++.

## Rules
- Players could be human or computer.
- If a player withdraw from the game, a computer will take over.

## Game Play
- The player with 7 spades will start the game.
- This player must play the 7 of spades in the centre of the table. 
- After the 7 of spades, the players take turns to play cards on the table. 
- At this point, the players must play cards that constitute legal plays. The following cards are legal:  
  • A 7 of any suit. This card starts a new pile on the table.  
  • A card with the same suit and adjacent rank as another card that has already been played. It must be played on the pile of the appropriate suit.   
  (Note that the “pile” is spread across the table, so that play can proceed at either end.)
- When a player has no legal plays, they must then choose a card in their hand, and place it face down in front of them. This is a discard.  
  Note that if a player has at least one legal play in their hand, then they must make a legal play; they may not discard in this case
- A player's score is based on the total number of ranks in the cards he/she discards. The player who has the least score wins the game.
