<img alt="Header" src=../assets/header.png />

<h2 align="center">
  Problem Set 1
</h2>

<p align="center">
  <img src="https://img.shields.io/badge/c%20-%2300599C.svg?&style=for-the-badge&logo=c&logoColor=white"/>
</p>

## :rocket: Introduction

Three problems in C:

- [Hello](#desktop_computer-hello)
- [Mario](#desktop_computer-mario)
- [Credit](#desktop_computer-credit)

## :desktop_computer: [Hello](https://cs50.harvard.edu/x/2020/psets/1/hello/)

A simple program that prompt user for name and say hello to user.

```
$ make hello
$ ./hello
What is your name?
Brian
hello, Brian
```

## :desktop_computer: [Mario](https://cs50.harvard.edu/x/2020/psets/1/mario/more/)

A program to recreate Nintendo’s Super Mario Brothers pyramids in C, albeit in text, using hashes (#) for bricks, a la the below. Each hash is a bit taller than it is wide, so the pyramids themselves are also be taller than they are wide.

```
$ ./mario
Height: 4
   #  #
  ##  ##
 ###  ###
####  ####
```

The program prompt user for height (1-8), and prints the pyramid.

## :desktop_computer: [Credit](https://cs50.harvard.edu/x/2020/psets/1/credit/)

The program prompts user for a number and uses [Luhn’s Algorithm](https://en.wikipedia.org/wiki/Luhn_algorithm) to calculate the checksum. Then it checks, with the length and starting digits, if it's a valid number.

The only output of the program is the result: `AMEX`, `MASTERCARD`, `VISA` or `INVALID`.

```
$ ./credit
Number: 4003600000000014
VISA
```
