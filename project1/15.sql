SELECT T.name
FROM Trainer as T, Pokemon as P, CatchedPokemon as CP
WHERE T.id = CP.owner_id 
	AND CP.pid = P.id 
	AND T.hometown = 'Sangnok city'
    AND P.name LIKE 'P%'
ORDER BY T.name
     ;
