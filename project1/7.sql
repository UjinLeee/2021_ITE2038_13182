SELECT CP1.nickname
FROM Trainer AS T1, CatchedPokemon AS CP1, 
(
  SELECT T2.hometown AS 'Thometown', MAX(level) AS 'MAXLev'
  FROM Trainer AS T2, CatchedPokemon AS CP2
  WHERE T2.id = CP2.owner_id
  GROUP BY T2.hometown
) as A
WHERE T1.id = CP1.owner_id AND CP1.level = A.MAXLev AND T1.hometown = A.Thometown
ORDER BY CP1.nickname;
  