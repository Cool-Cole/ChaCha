# ChaCha Command Line File Encryptor

Welcome to my first public project!

This is a Linux command line executable that can encrypt/decrypt files using the ChaCha encryption algorithm.

If you would like to make a contribution to this project please open up an issue and, instead of submitting code, please submit advice/resources to help me learn what I am doing incorrectly or what I could be doing better. That would help a lot!!!

# !WARNING!
Do not use this in production code! I am not a Cryptographer and only a novice at C, as such this code is probably really bad! This is just a learning project.

# Installing
Compile with your compiler of choice.

`gcc -O3 main.c chacha.c chacha.h hex.c hex.h -o chacha`

If you want to keep the `chacha` command local to your user move the binary to `$HOME/.local/bin/`.

`cp chacha ~/.local/bin/`

If you insist on making everyone suffer through my terrible command line program feel free to install it for all users by moving the binary to `/usr/local/bin/`.

`sudo cp chacha /usr/local/bin/`

# Sources
Here are a list of references that I used to guide me along with their accompanying license. I try not to copy paste code.

https://tools.ietf.org/html/rfc8439 - Main reference

The three sources below are "GPL-2.0-or-later"
https://www.oryx-embedded.com/doc/chacha_8c_source.html

https://www.oryx-embedded.com/doc/chacha_8h_source.html

https://www.oryx-embedded.com/doc/cpu__endian_8h_source.html
