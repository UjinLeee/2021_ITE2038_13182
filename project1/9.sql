SELECT T1.name, CP1.nickname
FROM Trainer AS T1, CatchedPokemon AS CP1, (
		SELECT owner_id, MAX(CP2.level) AS 'Max'
  		FROM Trainer AS T2, CatchedPokemon AS CP2, Pokemon AS P2
  		WHERE T2.id = CP2.owner_id AND P2.id = CP2.pid
  		GROUP BY T2.id
  		HAVING COUNT(*) >= 4
	) AS A
WHERE T1.id = CP1.owner_id AND T1.id = A.owner_id AND CP1.level = A.Max
ORDER BY CP1.nickname;
