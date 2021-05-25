# ChaCha Command Line File Encryptor

Welcome to my first public project!

This is a Linux binary that

If you would like to make a contribution to this project please open up an issue and, instead of submitting code, please submit advice/resources to help me learn what I am doing incorrectly or what I could be doing better. That would help a lot!!!

# !WARNING!
Do not use this in production code! I am not a Cryptographer and only a novice at C, as such this code is probably really bad! This is just a learning project.

# Implemented
* ChaCha 8, 12, 20, with a 256 bit private key, 96 bit nonce and 32 bit counter.
* Encryption of variable length byte arrays in memory
* File encryption tested and confirmed working! (On my i9-9900K I can achieve a throughput of about 500 Mibibytes per second when encrypting files from my SSD.)
* Takes user input as a command line program

# TODO
* Clean up code and turn this into a proper command line executable
* Multi threading (maybe?)
* Create a second vectorized implementation of ChaCha using AVX2 SIMD
* Add Poly1305 for integrity verification

# Sources
Here are a list of references that I used to guide me along with their accompanying license. I try not to copy paste code.

https://tools.ietf.org/html/rfc8439 - Main reference

The three sources below are "GPL-2.0-or-later"
https://www.oryx-embedded.com/doc/chacha_8c_source.html

https://www.oryx-embedded.com/doc/chacha_8h_source.html

https://www.oryx-embedded.com/doc/cpu__endian_8h_source.html
