<img alt="Header" src=../assets/header.png />

<h2 align="center">
  Problem Set 3
</h2>

<p align="center">
  <img src="https://img.shields.io/badge/c%20-%2300599C.svg?&style=for-the-badge&logo=c&logoColor=white"/>
</p>

## :rocket: Introduction

Two problems in C:

- [Plurality](#desktop_computer-plurality)
- [Tideman](#desktop_computer-tideman)

## :desktop_computer: [Plurality](https://cs50.harvard.edu/x/2020/psets/3/plurality/)

A program that runs a plurality election, per the below.

```
$ ./plurality Alice Bob Charlie
Number of voters: 4
Vote: Alice
Vote: Bob
Vote: Charlie
Vote: Alice
Alice
```
Perhaps the simplest way to hold an election, though, is via a method commonly known as the “plurality vote” (also known as “first-past-the-post” or “winner take all”). In the plurality vote, every voter gets to vote for one candidate. At the end of the election, whichever candidate has the greatest number of votes is declared the winner of the election.

The program prompt user for votes, for all votes it adds a vote to the candidate, if the candidate exists, and finally prints the winner.

## :desktop_computer: [Tideman](https://cs50.harvard.edu/x/2020/psets/3/tideman/)

A program that runs a Tideman election, per the below.

```
$ ./tideman Alice Bob Charlie
Number of voters: 5
Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Charlie
```

In a ranked-choice system, voters can vote for more than one candidate. Instead of just voting for their top choice, they can rank the candidates in order of preference.

The Tideman voting method consists of three parts:

- `Tally`: Once all of the voters have indicated all of their preferences, determine, for each pair of candidates, who the preferred candidate is and by what margin they are preferred.

- `Sort`: Sort the pairs of candidates in decreasing order of strength of victory, where strength of victory is defined to be the number of voters who prefer the preferred candidate.

- `Lock`: Starting with the strongest pair, go through the pairs of candidates in order and “lock in” each pair to the candidate graph, so long as locking in that pair does not create a cycle in the graph.

Once the graph is complete, the source of the graph (the one with no edges pointing towards it) is the winner!

<img alt="Tideman" src=./assets/tideman.png />

The user must add the candidates as command-line arguments.

The program prompt user for number of votes, and then the votes by rank. After tally, sort and lock, the program outputs the winner.
