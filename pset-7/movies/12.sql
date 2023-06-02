

SELECT title
FROM movies
WHERE id IN (
    SELECT movie_id
    FROM stars
    INNER JOIN people
            ON stars.person_id = people.id
    WHERE people.name
            IN ('Johnny Depp' , 'Helena Bonham Carter')
    GROUP BY movie_id
    HAVING COUNT(DISTINCT people.name) = 2
);


