<img alt="Header" src=../assets/header.png />

<h2 align="center">
  Problem Set 4
</h2>

<p align="center">
  <img src="https://img.shields.io/badge/c%20-%2300599C.svg?&style=for-the-badge&logo=c&logoColor=white"/>
</p>

## :rocket: Introduction

Two problems in C:

- [Recover](#desktop_computer-recover)
- [Filter](#desktop_computer-filter)

## :desktop_computer: [Recover](https://cs50.harvard.edu/x/2020/psets/4/recover/)

A program that recovers JPEGs from a forensic image, per the below.

```
$ ./recover card.raw
```

The program should accept exactly one command-line argument, the name of a forensic image from which to recover JPEGs, and returns all the JPEGs found.

## :desktop_computer: [Filter](https://cs50.harvard.edu/x/2020/psets/4/filter/)

A program that applies filters to BMPs, per the below.

```
$ ./filter -r image.bmp reflected.bmp
```

Example of a image and the 5 filters applied:

<p align="center">
  <img src=./assets/yard.png alt="Yard" />

  <img src=./assets/filters.png alt="Filters" />
</p>


The program can apply `5` filters to bitmap images: 

- `Grayscale`:  take an image and turn it into a black-and-white version of the same image.

- `Sepia`: take an image and turn it into a sepia version of the same image.

- `Reflection`: take an image and reflect it horizontally.

- `Blur`: take an image and turn it into a box-blurred version of the same image.

- `Edges`: take an image and highlight the edges between objects, according to the Sobel operator.

The program should accept exactly three command-line arguments:

1) The filter option: `b`, `e`, `g`, `r` or `s`, each of them specifies a different filter - blur, edges, grayscale, reflection, and sepia.
2) The name of the image to be filtered.
3) The name that will have the new image already filtered.
