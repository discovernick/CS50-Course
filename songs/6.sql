-- Firstly getting the subset of Post Malone from artist table
-- SELECT id FROM artisits WHERE name LIKE "Post Malone"
-- Inputting this into the main database
SELECT name FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name LIKE "Post Malone");