pasgen
======

Deterministic unique password generator using master password.

As it is written in Qt 5, it is very portable. It has been tested on Linux and Android.

Usage Notes
-----------
Generated password is also saved to clipboard.

Command-line equivalent
-----------------------
echo -n "&lt;master password&gt;&lt;site name&gt;" | sha3-224sum -b | base64 | tr -d '/+=' | head -c 30
