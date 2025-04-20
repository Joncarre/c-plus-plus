<!-- Created by Jonathan Carrero -->

**Online Game Manager 2.0** 🚀🎮🌐
===============================
----------

This version builds upon the original Online Game Manager, introducing several new features and design changes.

**✨ New Functionality**

Three main new features have been added in this second version:

1.  **Automatic Game Closure (Inactivity):** ⏳
    *   Games that have been inactive for more than 30 days will be automatically closed when the application shuts down.
    *   The player whose turn it *wasn't* will be declared the winner (as the other player was inactive).

2.  **Game History:** 📜
    *   Finished games (wins, losses, abandonments, inactivity closures) will now be saved to a file named `historico.txt`.

3.  **Opponent Statistics:** 📊
    *   Users can now view statistics against specific opponents they have played.
    *   This will show the number of games won, lost, and drawn against each opponent.

**🔧 Design Changes**

Several modifications and new implementations have been made in this version. The most important ones are described below:

*   **Game Access List Decoupling:** The list providing access to ongoing games (`ListaAccesoPartidas`) is no longer part of the `Usuario` (User) module. It's now managed separately.

*   **Manager Holds Session Access List:** The main `Gestor` (Manager) class now contains a field of type `tListaAccesoPartidas` to maintain the access list for the *current user's session* games.

*   **Dynamic User List:** The list of users (`listaUsuarios`) is now implemented as a dynamically sized array. When the array becomes full, it will be replaced by a larger one to accommodate more users.

*   **Dynamic Game List:** Similarly, the list of games (`listaPartidas`) is also a dynamic array. When inserting a new game, if the list is full, it will be resized.

*   **Game Access via Pointers:** The access list for ongoing games (`ListaAccesoPartidas`) now stores memory addresses (pointers) to the actual game objects instead of storing their index/position within the manager's main game list. This likely improves efficiency for accessing game data.


