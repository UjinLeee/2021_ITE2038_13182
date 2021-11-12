SELECT T1.name, AVG(CP.level)
FROM Trainer as T1, CatchedPokemon as CP
WHERE T1.name IN (
  SELECT T2.name
  FROM Trainer as T2, Gym
  WHERE T2.id = leader_id)
  AND CP.owner_id = T1.id
 GROUP BY T1.name;
