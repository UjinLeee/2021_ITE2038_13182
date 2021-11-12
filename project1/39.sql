SELECT P.name
FROM Pokemon AS P, Trainer AS T1, CatchedPokemon AS CP
WHERE T1.id = 
	(
    	SELECT T2.id
      	FROM Gym, Trainer AS T2
      	WHERE T2.id = Gym.leader_id AND Gym.city = 'Rainbow City'
    ) AND CP.owner_id = T1.id AND CP.pid = P.id
ORDER BY P.name;
