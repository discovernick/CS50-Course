SELECT title FROM movies WHERE id IN
(SELECT movie_id FROM stars WHERE movie_id IN
(SELECT movie_id from stars WHERE person_id IN
(SELECT people.id FROM people WHERE name = "Johnny Depp" OR "Helena Bonham Carter")) GROUP BY movie_id HAVING COUNT(*) > 1);