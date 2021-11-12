
SELECT DISTINCT P2.name
FROM Pokemon AS P1, Evolution AS E1, Evolution AS E2, Pokemon AS P2, Evolution AS E0
WHERE P1.id = E1.after_id AND P1.id = E2.before_id AND E2.after_id = P2.id AND E1.before_id <> E0.after_id ;