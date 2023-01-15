/*CREATE TABLE KB AS
SELECT movie_id, person_id
FROM stars
WHERE person_id NOT LIKE
(SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = 1958)

SELECT name FROM people WHERE id in
(SELECT person_id FROM KB WHERE movie_id IN
(SELECT movie_id FROM stars WHERE person_id IN
(SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = 1958))); */

SELECT name FROM people WHERE id IN
(SELECT person_id FROM stars WHERE movie_id IN
(SELECT movie_id FROM stars WHERE person_id IN
(SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = 1958))) AND id NOT IN
(SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = 1958);

