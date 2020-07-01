/* List the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.*/

/* List movies starring Johnny Depp*/
SELECT title
FROM movies
JOIN stars ON movies.id == stars.movie_id
JOIN people ON people.id == stars.person_id
WHERE name == "Johnny Depp"

INTERSECT

/* List of movies starring Helena Bonham Carter*/
SELECT title
FROM movies
JOIN people ON people.id = stars.person_id
JOIN stars ON stars.movie_id = movies.id
WHERE people.name = "Helena Bonham Carter"
ORDER BY title