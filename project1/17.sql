SELECT AVG(CP.level)
FROM Pokemon as P, Trainer as T, CatchedPokemon as CP
WHERE T.id = CP.owner_id 
	AND P.id = CP.pid 
	AND P.type = 'Water';
