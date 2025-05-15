#Huff Puff

A C++ terminal-based project that integrates user authentication with Huffman encoding and decoding. Users must register and log in to access functionalities for compressing or decompressing messages. This project demonstrates secure credential handling alongside efficient text compression using classic Huffman coding.

Features
1. User Authentication

Supports user registration and login

Passwords are hashed with a unique salt for each user

User credentials are stored securely in a local file (user_data.txt)

2. Huffman Encoding

Compresses user-inputted messages using Huffman coding

Saves the encoded message along with its frequency map to a file

Displays character-to-code mappings and packing density statistics

3. Huffman Decoding

Reads an encoded file and decodes it using the saved encoding table

Reconstructs the original text accurately

4. Command-Line Interface

Clear, interactive text-based UI for navigating login and compression options

Supports multiple encode/decode sessions under the same login

