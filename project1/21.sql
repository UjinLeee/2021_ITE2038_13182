
SELECT T1.name
FROM Trainer AS T1, CatchedPokemon AS CP, 
(SELECT owner_id, COUNT(*)
FROM CatchedPokemon
GROUP BY owner_id, pid
HAVING COUNT(*) >= 2) AS A
WHERE T1.id = A.owner_id
GROUP BY T1.name;