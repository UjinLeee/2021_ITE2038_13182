SELECT  COUNT(type)
FROM Pokemon, CatchedPokemon
GROUP BY type
ORDER BY type;
