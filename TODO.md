# TODO
* Clean up and comment code.
* Better handle edge cases in user input.
* Multi threading. (maybe?)
* Create a second vectorized implementation of ChaCha using AVX2 SIMD.
* Add Poly1305 for integrity verification.

# Implemented
* The ChaCha encryption algorithm with a 256 bit private key, 96 bit nonce and 32 bit counter.
* Encryption of variable length byte arrays in memory.
* File encryption/decryption tested and confirmed working!
* Takes user input as a command line program.
