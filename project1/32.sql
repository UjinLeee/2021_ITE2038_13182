 SELECT T1.name, P1.name, COUNT(*)
 FROM Trainer AS T1, CatchedPokemon AS CP1, Pokemon AS P1
 WHERE CP1.owner_id = T1.id AND CP1.pid = P1.id AND 
 T1.name IN (
 SELECT T2.name
 FROM Trainer AS T2, Pokemon AS P2, CatchedPokemon AS CP2
 WHERE T2.id = CP2.owner_id AND CP2.pid = P2.id 
 GROUP BY T2.name
 HAVING COUNT(DISTINCT T2.name, P2.type) = 1
 )
 GROUP BY T1.name, P1.name
 ORDER BY T1.name;
 
