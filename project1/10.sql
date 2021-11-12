SELECT Pokemon.name
FROM Pokemon 
WHERE Pokemon.id NOT IN (
		SELECT CatchedPokemon.pid
  		FROM CatchedPokemon
	)
ORDER BY Pokemon.name;
