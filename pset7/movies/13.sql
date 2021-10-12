SELECT DISTINCT name
FROM people JOIN stars ON people.id = stars.person_id WHERE name != 'Kevin Bacon' AND movie_id IN
(SELECT movie_id FROM stars WHERE person_id =
(SELECT people.id
FROM people
WHERE name == 'Kevin Bacon' AND birth == 1958));