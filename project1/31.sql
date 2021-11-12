SELECT Pokemon.name, A.Bluecity, B.Scity
FROM Pokemon, CatchedPokemon AS CP1,
	(
      SELECT T1.id AS 'Blueid', T1.hometown AS 'Bluecity'
      FROM Trainer AS T1
      WHERE T1.hometown = 'Blue City'  
    ) AS A, 
    (
      SELECT T2.id AS 'Sid', T2.hometown AS 'Scity'
      FROM Trainer AS T2
      WHERE T2.hometown = 'Sangnok City'  
    ) AS B
WHERE CP1.id = A.Blueid
	AND CP1.id = B.Sid
ORDER BY Pokemon.name;