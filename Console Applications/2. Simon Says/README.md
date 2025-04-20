<!-- Created by Jonathan Carrero -->

**Simon Says** 🧠🌈
=================
----------

**🎮 Introduction**

Simon Says is a classic memory game where you must replicate a sequence of colors generated randomly by the machine. After the original sequence is shown, the user must repeat it by entering the corresponding colors (represented by characters). If the user correctly repeats the sequence, the machine generates a new, longer sequence (adding one more color). This process continues until the user makes a mistake or reaches the maximum sequence length.

**📝 Description**

1.  **Welcome:** Upon starting, a welcome screen appears, prompting the user to enter their name.

    ![Welcome Screen](https://github.com/Joncarre/CPlusPlus-language/blob/master/Aplicaciones%20sin%20interfaz%20gr%C3%A1fica/images/2_1.png)

2.  **Main Menu:** After entering a name, a menu with 5 options is displayed. The options are quite intuitive:
    *   **Easy Mode:** Sequences have a maximum length of four colors (colors can repeat randomly).
    *   **Hard Mode:** Sequences can have up to seven colors. The number of sequences to complete is also greater than in Easy Mode.
    *   Other options (likely viewing scores, instructions, exit).

    ![Main Menu](https://github.com/Joncarre/CPlusPlus-language/blob/master/Aplicaciones%20sin%20interfaz%20gr%C3%A1fica/images/2_2.png)

3.  **Gameplay:**
    *   Once the game starts, the generated sequence is displayed.
    *   The user has as much time as needed to memorize it.

    ![Sequence Display](https://github.com/Joncarre/CPlusPlus-language/blob/master/Aplicaciones%20sin%20interfaz%20gr%C3%A1fica/images/2_3.png)

4.  **Lifelines (Wildcards):**
    *   To help the user, 3 wildcards are available (entered using the character 'x').
    *   These can be used if the user forgets a color in the sequence.
    *   Wildcards are *not* replenished after each sequence.

    ![Using a Wildcard](https://github.com/Joncarre/CPlusPlus-language/blob/master/Aplicaciones%20sin%20interfaz%20gr%C3%A1fica/images/2_4.png)

Test your memory with this console implementation of Simon Says! 🤔✨
