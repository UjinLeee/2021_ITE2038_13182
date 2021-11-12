SELECT CP.nickname
FROM Trainer AS T, CatchedPokemon AS CP
WHERE CP.owner_id = T.id
AND CP.level >= 40 AND CP.owner_id >= 5 
ORDER BY CP.nickname;
