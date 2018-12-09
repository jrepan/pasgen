pasgen
======

Deterministic unique password generator using master password.

As it is written in Qt 5, it is very portable. It has been tested on Linux and Android.

Simple web version: https://jrepan.github.io/pasgen/pasgen.html

Usage Notes
-----------
Generated password is also saved to clipboard.

If the page name is prefixed with lenNN or pinNN, then the length of resulting password is NN instead of default 30 characters. If the page name is prefixed with pin, then the resulting password will only contain numbers.

It allows optionally to specify an internal secret in the config file using setting name "secret", which if set, must be same each time for the generated password to be the same. This protects against cases when somebody might see you typing the master password, as the internal secret can't be seen anywhere in the user interface.

Command-line equivalent
-----------------------
echo -n "&lt;master password&gt;&lt;site name&gt;&lt;internal secret&gt;" | sha3-224sum -b | base64 | tr -d '/+=' | head -c 30
