SELECT CP.nickname
FROM Pokemon AS P, CatchedPokemon AS CP, Trainer AS T
WHERE P.id = CP.pid AND CP.owner_id = T.id
	AND T.id IN (
      SELECT T2.id
	  FROM Trainer AS T2
	   JOIN Gym ON T2.id = leader_id 
	 )
     AND T.hometown = 'Sangnok City'
     AND P.type = 'Water'
ORDER BY CP.nickname;
