<img alt="Header" src=../assets/header.png />

<h2 align="center">
  Problem Set 7
</h2>

<p align="center">
  <img src="https://img.shields.io/badge/python%20-%2314354C.svg?&style=for-the-badge&logo=python&logoColor=white"/>

  <img src ="https://img.shields.io/badge/sqlite-%2307405e.svg?&style=for-the-badge&logo=sqlite&logoColor=white"/>
</p>

## :rocket: Introduction

Two problems in Python and SQL:

- [Movies](#desktop_computer-movies)
- [Houses](#desktop_computer-houses)

## :desktop_computer: [Movies](https://cs50.harvard.edu/x/2020/psets/7/movies/)

These are SQL queries to answer questions about a database of movies.

The database [movies.db](https://cdn.cs50.net/2019/fall/psets/7/movies/movies.zip) stores data from IMDB about movies, the people who directed and starred in them, and their ratings.

Follow the 13 queries:

1 - In 1.sql, a SQL query to list the titles of all movies released in 2008

```
SELECT title FROM movies WHERE year = 2008;
```

2 - In 2.sql, a SQL query to determine the birth year of Emma Stone

```
SELECT birth FROM people WHERE name = "Emma Stone";
```

3 - In 3.sql, a SQL query to list the titles of all movies with a release date on or after 2018, in alphabetical order.

```
SELECT title FROM movies WHERE year >= 2018 ORDER BY title ASC;
```

4 - In 4.sql, a SQL query to determine the number of movies with an IMDb rating of 10.0.

```
SELECT COUNT(rating) FROM ratings WHERE rating = 10;
```

5 - In 5.sql, a SQL query to list the titles and release years of all Harry Potter movies, in chronological order.

```
SELECT title, year from movies WHERE title LIKE "Harry Potter%" ORDER BY year ASC;
```

6 - In 6.sql, a SQL query to determine the average rating of all movies released in 2012.

```
SELECT AVG(rating) FROM ratings WHERE movie_id IN
(SELECT id FROM movies WHERE year = 2012);
```

7 - In 7.sql, a SQL query to list all movies released in 2010 and their ratings, in descending order by rating. For movies with the same rating, order them alphabetically by title.

```
SELECT title, rating FROM
ratings JOIN movies ON ratings.movie_id = movies.id
WHERE year = 2010
ORDER BY rating DESC, title ASC;
```

8 - In 8.sql, a SQL query to list the names of all people who starred in Toy Story.

```
SELECT DISTINCT name FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON  stars.movie_id = movies.id
WHERE title = "Toy Story";
```

9 - In 9.sql, a SQL query to list the names of all people who starred in a movie released in 2004, ordered by birth year.

```
SELECT name FROM people WHERE id IN
(SELECT DISTINCT person_id FROM stars WHERE movie_id IN
(SELECT id FROM movies WHERE year = 2004))
ORDER BY birth;
```

10 - In 10.sql, a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.

```
SELECT DISTINCT name FROM people
JOIN directors ON people.id = directors.person_id
JOIN ratings ON  directors.movie_id = ratings.movie_id
WHERE rating >= 9.0;
```

11 - In 11.sql, a SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.

```
SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
JOIN ratings ON movies.id = ratings.movie_id
WHERE people.name = "Chadwick Boseman"
ORDER BY ratings.rating DESC
LIMIT 5;
```

12 - In 12.sql, a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.

```
SELECT title FROM movies WHERE id IN
(SELECT movie_id FROM stars WHERE person_id IN
(SELECT id FROM people WHERE name = "Johnny Depp"))
INTERSECT
SELECT title FROM movies WHERE id IN
(SELECT movie_id FROM stars WHERE person_id IN
(SELECT id FROM people WHERE name="Helena Bonham Carter"));
```

13 - In 13.sql, a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.

```
SELECT name FROM people WHERE NOT name="Kevin Bacon" AND id IN
(SELECT person_id FROM stars WHERE movie_id IN
(SELECT movie_id FROM stars WHERE person_id IN
(SELECT id FROM people WHERE name="Kevin Bacon" AND birth="1958")))
```

## :desktop_computer: [Houses](https://cs50.harvard.edu/x/2020/psets/7/houses/)

A program to import student data into a database, and then produce class rosters.

```
$ python import.py characters.csv
$ python roster.py Gryffindor

Lavender Brown, born 1979
Colin Creevey, born 1981
Seamus Finnigan, born 1979
Hermione Jean Granger, born 1979
Neville Longbottom, born 1980
Parvati Patil, born 1979
Harry James Potter, born 1980
Dean Thomas, born 1980
Romilda Vane, born 1981
Ginevra Molly Weasley, born 1981
Ronald Bilius Weasley, born 1980
```

In import.py, the program accepts one command-line argument, the name of a CSV spreadsheet, and it can import data from the spreadsheet. For each student in the CSV file, it inserts the student into the students table in the students.db database.

In roster.py, the program accepts one command-line argument, the name of a house. The program query the students table in the students.db database for all of the students in the specified house. Then it print out each student’s full name and birth year (formatted as, e.g., Harry James Potter, born 1980 or Luna Lovegood, born 1981). The rosters are ordered by last name. For students with the same last name, they are ordered by first name.
