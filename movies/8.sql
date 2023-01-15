-- People in Toy Story
SELECT name FROM people WHERE people.id IN
(SELECT person_id FROM stars WHERE movie_id IN
(SELECT movies.id FROM movies WHERE title = "Toy Story"));
