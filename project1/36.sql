
SELECT DISTINCT P.name
FROM Pokemon AS P
WHERE P.id NOT IN 
	(
    	SELECT E2.before_id
      	FROM Evolution AS E2
    ) AND P.type = 'Water'
    ORDER BY P.name;