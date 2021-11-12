SELECT T.name, COUNT(CP.id)
FROM Trainer AS T, CatchedPokemon AS CP
WHERE CP.owner_id = T.id 
GROUP BY T.name
ORDER BY T.name;
