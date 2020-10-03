<img alt="Header" src=../assets/header.png />

<h2 align="center">
  Problem Set 2
</h2>

<p align="center">
  <img src="https://img.shields.io/badge/c%20-%2300599C.svg?&style=for-the-badge&logo=c&logoColor=white"/>
</p>

## :rocket: Introduction

Two problems in C:

- [Readability](#desktop_computer-readability)
- [Substitution](#desktop_computer-substitution)

## :desktop_computer: [Readability](https://cs50.harvard.edu/x/2020/psets/2/readability/)

A program that computes the approximate grade level needed to comprehend some text, per the below.

```
$ ./readability
Text: Congratulations! Today is your day. You're off to Great Places! You're off and away!
Grade 3
```
The program prompt user for text, and then outputs Coleman-Liau index. The Coleman-Liau index of a text is designed to output what (U.S.) grade level is needed to understand the text. The formula is:

```
index = 0.0588 * L - 0.296 * S - 15.8
```
Where `L` is the average number of letters per 100 words in the text, and `S` is the average number of sentences per 100 words in the text.

## :desktop_computer: [Substitution](https://cs50.harvard.edu/x/2020/psets/2/substitution/)

A program that implements a substitution cipher, per the below.

```
$ ./substitution JTREKYAVOGDXPSNCUIZLFBMWHQ
plaintext:  HELLO
ciphertext: VKXXN
```

The program prompt user for a 26-character key, with all letters of the alphabet and each letter exactly once, and then prompt the user for a string of plaintext.

The program outputs a ciphertext, with each alphabetical character in the plaintext substituted for the corresponding character in the ciphertext (non-alphabetical characters should be outputted unchanged).
