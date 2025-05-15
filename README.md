#Huff Puff

A C++ terminal-based project that integrates user authentication with Huffman encoding and decoding. Users must register and log in to access functionalities for compressing or decompressing messages. This project demonstrates secure credential handling alongside efficient text compression using classic Huffman coding.

Features: 
User Authentication
    1.Supports user registration and login
    2.Passwords are hashed with a unique salt for each user
    3.User credentials are stored securely in a local file (user_data.txt)

Huffman Encoding
    1.Compresses user-inputted messages using Huffman coding
    2.Saves the encoded message along with its frequency map to a file
    3.Displays character-to-code mappings and packing density statistics

Huffman Decoding
    1.Reads an encoded file and decodes it using the saved encoding table
    2.Reconstructs the original text accurately

Command-Line Interface
    1.Clear, interactive text-based UI for navigating login and compression options
    2.Supports multiple encode/decode sessions under the same login

