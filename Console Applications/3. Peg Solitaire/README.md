<!-- Created by Jonathan Carrero -->

**Peg Solitaire (Uno Solo)** 🧩
=============================
----------

**📜 Introduction**

In this solitaire game, you start with a grid-like board with pegs placed in holes. The player must move one peg per turn. Pegs can only move by "jumping" over an adjacent peg into an empty hole. The jumped peg is then removed from the board, similar to checkers.

**🔑 Key Rules:**

1.  **Jumping:** Only one peg can be jumped at a time.
2.  **Movement:** Jumps must be horizontal or vertical, never diagonal.
3.  **Objective:** The goal is to eliminate all pegs, leaving only *one* peg remaining on the board.
4.  **Specific Goal (This Version):** In this particular version, the final remaining peg must end up in a specific target hole.

**💻 Description of this Implementation**

The program implements the game dynamics. It uses characters with different background colors to draw the board:

*   **Black Cells:** Null cells (not part of the playable board).
*   **Dark Green Cells:** Empty holes.
*   **Bright Green Cells:** Holes containing a peg.
*   **Cell with White Symbol:** Represents the target hole where the last peg must end.

![Board Example](https://github.com/Joncarre/CPlusPlus-language/blob/master/Aplicaciones%20sin%20interfaz%20gr%C3%A1fica/images/3_1.png)

As shown, the program displays the possible moves available for all pegs currently on the board.

**💾 Loading and Saving Games**

The program also supports loading and saving the state of a game. This is done using a `.txt` file with a specific structure, likely defining the board dimensions, peg positions, empty holes, and the target hole.

![Save File Structure Example](https://github.com/Joncarre/CPlusPlus-language/blob/master/Aplicaciones%20sin%20interfaz%20gr%C3%A1fica/images/3_2.png)

Challenge yourself with this classic brain teaser! 🤔

