
SELECT P3.name
FROM Pokemon AS P1, Evolution AS E1, Pokemon AS P2, Evolution AS E2, Pokemon AS P3
WHERE P1.name = 'Charmander' AND P1.id = E1.before_id 
	AND E1.after_id = P2.id AND P2.id = E2.before_id 
    AND E2.after_id = P3.id ;