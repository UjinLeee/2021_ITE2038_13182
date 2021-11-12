SELECT T.name
FROM Trainer AS T, Pokemon AS P, CatchedPokemon AS CP
WHERE T.id = CP.owner_id AND CP.pid = P.id AND P.name = 'Pikachu'
ORDER BY T.name;

