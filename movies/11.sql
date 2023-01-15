SELECT movies.title
FROM movies
INNER JOIN ratings
ON ratings.movie_id = movies.id
WHERE movie_id IN
(SELECT movie_id FROM stars WHERE person_id IN (SELECT people.id FROM people WHERE name = "Chadwick Boseman"))
ORDER BY rating DESC, title LIMIT 5;