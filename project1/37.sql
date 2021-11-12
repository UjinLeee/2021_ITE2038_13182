SELECT SUM(CP.level)
FROM Pokemon AS P, CatchedPokemon AS CP
WHERE CP.pid = P.id AND P.type = 'Fire';
