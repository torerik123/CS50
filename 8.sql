/*List the names of all people who starred in Toy Story.
Your query should output a table with a single column for the name of each person.
You may assume that there is only one movie in the database with the title Toy Story.*/

/* Selects name from a joined table*/
SELECT name FROM

/* Joins people and stars table where people ID and person ID are the same, and then joins movies table with stars*/
people JOIN stars ON people.id == stars.person_id JOIN movies ON stars.movie_id == movies.id WHERE title == "Toy Story"