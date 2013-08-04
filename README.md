pasgen
======

A non-random unique password generator using master password utilizing SHA3. As it is written in Qt 5, it is very portable. Tested platforms are Linux and Android.
Currently it is at proof-of-concept stage.

Usage Notes
-----------
It saves resulting password also to clipboard.

Command-line equivalent
-----------------------
echo -n "<master password><site name>" | sha3sum -c 448 -r 1152 -o 224  | tr '[A-Z]' '[a-z]'

