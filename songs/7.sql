-- Firstly getting the subset of Drake from artist table
-- SELECT id FROM artisits WHERE name LIKE "Drake"
-- Inputting this into the main database
SELECT AVG(energy) FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name LIKE "Drake");