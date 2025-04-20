<!-- Created by Jonathan Carrero -->

**The Chinese Game (Los Chinos)** 🪙
===================================
----------

**📜 Description**

According to one theory, the game known as "juego de los chinos" originated in 1787 in a small village in León, Spain. Felipe Valdeón Triguero, a local shepherd, is said to have invented the game to pass the long hours of herding.

The most traditional way to play involves each player having three coins. In each round, players secretly choose to hold 0, 1, 2, or 3 coins in their right hand. Then, each player takes turns guessing the *total* number of coins held by all players combined.

**🔑 Key Rules:**

1.  **Unique Guesses:** A player cannot guess a number already guessed by another player in the same round.
2.  **No Lying (Plausible Guesses):** This is crucial! A player's guess must be *possible* given the number of coins they are holding.
    *   Your guess must be at least the number of coins *you* are holding.
    *   Your guess cannot be more than the number of coins *you* are holding plus the maximum possible coins held by all *other* players (number of opponents * 3).

**🎮 Example (2 Players):**

*   Player A holds 1 coin (🪙).
*   Player B holds 2 coins (🪙🪙).
*   The total number of coins is 1 + 2 = 3.

*   **Player A's Turn:**
    *   Player A knows they have 1 coin.
    *   Player B can have 0, 1, 2, or 3 coins.
    *   The minimum possible total is 1 (A's coin) + 0 (B's minimum) = 1.
    *   The maximum possible total is 1 (A's coin) + 3 (B's maximum) = 4.
    *   So, Player A must guess a number between 1 and 4 (inclusive). Let's say Player A guesses **3**.

*   **Player B's Turn:**
    *   Player B knows they have 2 coins.
    *   Player A can have 0, 1, 2, or 3 coins.
    *   The minimum possible total is 2 (B's coins) + 0 (A's minimum) = 2.
    *   The maximum possible total is 2 (B's coins) + 3 (A's maximum) = 5.
    *   Player B must guess a number between 2 and 5 (inclusive).
    *   Crucially, Player B *cannot* guess 3, because Player A already guessed it.
    *   Let's say Player B guesses **4**.

*   **Outcome:** Player A guessed 3, which was the correct total. Player A wins the round! 🎉

This C++ implementation brings this classic guessing game to the console.

