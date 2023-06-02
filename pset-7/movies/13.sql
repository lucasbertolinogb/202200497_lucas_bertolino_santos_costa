

    SELECT name
    FROM people
    WHERE id IN (
        SELECT movie_id
        FROM stars
        INNER JOIN people
                ON stars.person_id = people.id
        WHERE people.name = 'Kevin Bacon'
        GROUP BY movie_id
        HAVING MAX(people.name) = 'Kevin Bacon'
    );