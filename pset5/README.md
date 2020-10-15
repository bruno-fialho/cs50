<img alt="Header" src=../assets/header.png />

<h2 align="center">
  Problem Set 5
</h2>

<p align="center">
  <img src="https://img.shields.io/badge/c%20-%2300599C.svg?&style=for-the-badge&logo=c&logoColor=white"/>
</p>

## :rocket: Introduction

One problem in C:

- [Speller](#desktop_computer-speller)

## :desktop_computer: [Speller](https://cs50.harvard.edu/x/2020/psets/5/speller/)

A program that spell-checks a file, a la the below, using a hash table.

<p align="center">
  <img src=./assets/screen-ide.gif alt="Screen" />
</p>

The program should accept two command-line arguments, the dictionary and the text, the dictionary is optional, if this argument is omitted, speller will use dictionaries/large by default.

The program has five main functions:

- `load`:  is responsible for taking a dictionary and loading it into a hash table.

- `hash`: take a word and return which index into your hash table you should use in order to find that word or insert the word into your data structure.

- `size`: return the number of words that are in your dictionary.

- `check`: take a word and check to see if the word is in the dictionary or not.

- `unload`: is responsible for freeing up any memory that has been allocated in the process of running the spell check.

The polynomial hash function used is based on [Horner’s rule](https://en.wikipedia.org/wiki/Horner%27s_method).

