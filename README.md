# ChaCha
This is an implementation of the ChaCha stream cipher in C that aims to be completely compliant with https://tools.ietf.org/html/rfc8439. This is just a learning project so I don't recomend using this in production.

With time, I plan on improving this project and turning it into a useable ChaCha & Poly1305 encryption libary.

If you would like to make a contribution to this project, please open up an issue and send me some advice/reasources to help me learn what I am doing incorrectly or what I could be doing better. That would help a lot!!!

# Implemented
* ChaCha 8, 12, 20, with a 256 bit private key, 96 bit nonce and 32 bit counter.
* Encryption of variable length byte arrays in memory 

# TODO
* Have it encrypt files
* Put the cipher state into a struct
* Clean up code and turn this into a proper lib
* Support ChaCha version with 64 bit counter and 64 bit nonce (maybe unneccessary?)

# Sources
Here are a list of refrences that I used to guide me along with their accompanying liscense. I try not to copy paste code.

GPL-2.0-or-later

https://www.oryx-embedded.com/doc/chacha_8c_source.html

https://www.oryx-embedded.com/doc/chacha_8h_source.html

https://www.oryx-embedded.com/doc/cpu__endian_8h_source.html - The defintion LE32 in chacha.c came from this file.
