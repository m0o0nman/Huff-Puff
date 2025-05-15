# Huff-Puff

**Huff-Puff** is a C++ terminal-based application that combines user authentication with Huffman encoding and decoding. This project is designed to securely manage user credentials and provide efficient text compression and decompression using the Huffman coding algorithm.

Features

User Authentication
- Register and log in securely
- Passwords are hashed with a unique salt per user
- Credentials are stored in a local file (`user_data.txt`)

Huffman Encoding
- Compress any input message using Huffman coding
- Saves the encoded message and code table to a file
- Displays character-code mappings and packing density

Huffman Decoding
- Decodes files previously encoded using this program
- Restores the original message using the saved encoding table

Command-Line Interface
- Simple, interactive text-based UI
- Allows multiple encode/decode sessions per login



