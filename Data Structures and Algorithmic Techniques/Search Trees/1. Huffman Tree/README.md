# Huffman Tree

**What is the goal?**

It's possible to significantly reduce the number of bits required to represent text if, instead of using a fixed-length code like ASCII, a variable-length code is used. In this case, the number of bits required can vary from character to character. The goal is to encode the most frequently appearing characters using shorter bit strings. However, when the code is of variable length, some method is needed to determine the start and end bits of a code.

The Huffman coding technique allows us to construct prefix-free codes that will also be optimal, in the sense that shorter code lengths will be chosen for characters that appear more frequently. The data compression/decompression method consists of the following:

- Calculate the frequencies of all characters in a given message (frequency table).
- Build the "Huffman tree" from the frequency table.
- Build a variable-length code table using the "Huffman tree".
- Once the codes for each character are obtained, encode the message.
- The encoded message is decoded directly using the Huffman tree.

**How is it implemented?**

A "Huffman tree" is a binary tree that is either a leaf node containing a character and its frequency, or is built from two other Huffman trees A1 and A2, left child and right child respectively, with the frequency of the new root being the sum of the frequencies of A1 and A2. The code for a character is given by the path from the root to the leaf containing the character, where for each bit of the code, a "0" means go to the left child and a "1" means go to the right child. The tree is constructed so that shorter codes correspond to more frequent characters. For this, a "priority queue" is used, which initially will contain the leaf trees from the frequency table. While there is more than one tree in the queue, the two smallest trees will be removed and a new one built from these two will be inserted. We will have defined an ordering relation with respect to the trees (they are ordered directly by comparing the frequencies of the root nodes).

A design is presented capable of performing the encoding of text files using the described technique, and capable of decoding files previously encoded with this technique, thus obtaining a file with the original text.


