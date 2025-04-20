<!-- Created by Jonathan Carrero -->

**Online Game Manager** 🎮🌐
=========================
----------

**📜 Introduction**

This project implements a manager for 2-player online games (specifically Connect 4 in this version). It allows:

*   **New User Registration:** Players can create new accounts.
*   **Login:** Registered users can log in.
*   **Matchmaking:** Users can find opponents to start a new game.
*   **Ongoing Games:** Users can play games they currently have in progress.

**✨ Key Features:**

*   **Asynchronous Play:** Users connect whenever they want to play. They can have multiple games running simultaneously (up to a set limit).
*   **Categorization:** Users are classified into categories (skill levels).
*   **Matchmaking by Category:** Games are initiated between opponents of the same category.
*   **Promotion/Demotion:**
    *   Winning enough consecutive games promotes a user to a higher category.
    *   Losing too many consecutive games demotes a user to a lower category.
*   **Game End Conditions:**
    *   The game concludes naturally (e.g., Connect 4 win/draw).
    *   A player chooses to abandon the game. In this case, the opponent is declared the winner.
*   **Notifications:** When a player finishes a game (win, loss, or abandonment), the manager notifies the opponent, who will see the message upon their next login.

**💻 System Description**

1.  **Main Menu:**
    *   The initial menu offers options to log in (for registered users) or register (for new users).
    *   Both options require a username and password.
    *   The "Exit" option terminates the application.

    ![Main Menu](https://github.com/Joncarre/CPlusPlus-language/blob/master/Aplicaciones%20sin%20interfaz%20gr%C3%A1fica/images/4_1.png)

    *   **Login:** Checks if the username exists and the password is correct. If not, an error is shown, and the main menu reappears.
    *   **Register:** Checks if the desired username already exists. If it does, an error is shown, and the user returns to the main menu.

2.  **User Session Menu:**
    *   After logging in, the menu displays the user's ongoing games, sorted by the last update date.
    *   Games are numbered, and a marker indicates if it's the user's turn.

    ![User Session Menu](https://github.com/Joncarre/CPlusPlus-language/blob/master/Aplicaciones%20sin%20interfaz%20gr%C3%A1fica/images/4_2.png)

    *   **View Game:** Prompts the user for the number of the game to display (input is validated).
    *   **New Game:** Allows the user to request a new game.
        *   The manager checks if the user is already waiting for a match and hasn't reached the maximum game limit.
        *   It then searches for an opponent of the same level.
        *   If found, a new game is created and added to both players' lists.
        *   If not found, the user is placed in a waiting state.
    *   **Sort Games:** Options to sort the game list by update time, whose turn it is, or date.
    *   **Logout:** Returns to the main menu.

3.  **Connect 4 Gameplay:**
    *   The Connect 4 game board is displayed.
    *   Options include making a move, viewing the board, or abandoning the game.
    *   Crucially, a user can only make a move (`Jugar`) when it is their turn.
    *   If a user abandons the game, a message is sent to the opponent informing them they won due to abandonment.

    ![Connect 4 Game](https://github.com/Joncarre/CPlusPlus-language/blob/master/Aplicaciones%20sin%20interfaz%20gr%C3%A1fica/images/4_3.png)

This system provides a basic framework for managing turn-based online games. 🏆



