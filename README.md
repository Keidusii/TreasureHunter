# TreasureHunter
A strategy-based console game made with C++.
Uses profile system to save number of games played and total score
Open the .exe file to play.

**Instructions**:

The goal is to get to position 35. You start at position 1. You get 10 Points every move.

1.	Easy: 60 moves (final score * 0.50)
2. 	Medium: 50 Moves (final score * 1.00)
3.	Hard: 40 moves (final score * 1.50)

You start out with 0 money, 5 energy, and 6 gas. The max amount of energy you can have is 5. The max gas is 6.
At every move, you can harvest work, rest, or move forward. Working gives you $15 but spends 1 energy.
Resting recharges energy by 3 spots. Moving forward moves you up one position but spends 1 gas.
If you try to move forward but you are out of gas, you cannot move forward, and you will be charged
$75 and your tank will be full.
If you do not have $35 you cannot move forward. If you run out of energy, you cannot work.
Every 10 moves, you can visit a shop.

Shop items -
1.      Juice($60): increases energy capacity by 2
2.      Bigger Tank($60): increases gas capacity by 2
3.      Extra moves($50/move): gives an extra move
4.      Traveler perk($75): each time you move forward, you move forward one extra position

Every 5 moves, you can visit a gas station. Gas cost $30 to fill the tank

You get 500 points for reaching position 10, 2500 for reaching position 20, and 10000 for reaching position 30.
You get 50000 for winning the game.
If win, Final score = score + money + moves * 1000
If lose, Final score = score