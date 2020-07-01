/* Select name where people.id is IN*/
SELECT COUNT(name) FROM people WHERE people.id
IN

/* List of person_id where person_id is IN*/
( SELECT person_id FROM stars JOIN movies ON movies.id = stars.movie_id
WHERE movie_id IN

/* List of movie_id where movie_id is IN*/
( SELECT movie_id FROM movies JOIN stars ON stars.movie_id = movies.id JOIN people ON
 people.id = stars.person_id WHERE people.id IN (

/* List of Kevin Bacon movies*/
SELECT id FROM people WHERE people.name = "Kevin Bacon" AND people.birth = 1958 )))

/* Remove Kevin Bacon himself from the results*/
EXCEPT
SELECT name FROM people WHERE people.name = "Kevin Bacon" AND people.birth = 1958