SELECT T.name
FROM Trainer AS T, Pokemon AS P, CatchedPokemon AS CP
WHERE CP.pid = P.id AND CP.owner_id = T.id AND P.type = 'Psychic'
ORDER BY T.name;
