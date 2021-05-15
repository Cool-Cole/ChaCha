# ChaCha
Welcome to my first evey public project!

This is an implementation of the ChaCha stream cipher in C that aims to be completely compliant with https://tools.ietf.org/html/rfc8439.

With time, I plan on improving this project and turning it into a useable ChaCha & Poly1305 encryption libary.

If you would like to make a contribution to this project please open up an issue and, instead of submitting code, please submit advice/reasources to help me learn what I am doing incorrectly or what I could be doing better. That would help a lot!!!

# !WARNING!
Do not use this in production code! I am not a Cryptographer and only a novice at C, as such this code is probably really bad! This is just a learning project.

# Implemented
* ChaCha 8, 12, 20, with a 256 bit private key, 96 bit nonce and 32 bit counter.
* Encryption of variable length byte arrays in memory
* File encryption tested and confirmed working! (On my i9-9900K I can achive a throughput of about 500 Mibibytes per second when encrypting files from my SSD.)

# TODO
* Have it take user input
* Clean up code and turn this into a proper lib
* Have functions return errors (if counter reaches max, if function params incorrect, ect)
* Multithreading (maybe?)

# Sources
Here are a list of refrences that I used to guide me along with their accompanying liscense. I try not to copy paste code.

https://tools.ietf.org/html/rfc8439 - Main refrence

The three sources below are "GPL-2.0-or-later"
https://www.oryx-embedded.com/doc/chacha_8c_source.html

https://www.oryx-embedded.com/doc/chacha_8h_source.html

https://www.oryx-embedded.com/doc/cpu__endian_8h_source.html
