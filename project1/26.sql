SELECT Trainer.name, SUM(CP.level)
FROM Trainer, CatchedPokemon AS CP
WHERE CP.owner_id = Trainer.id
GROUP BY Trainer.name
HAVING SUM(CP.level) >= ALL (
	SELECT SUM(CP2.level)
	FROM Trainer, CatchedPokemon AS CP2
	WHERE CP2.owner_id = Trainer.id
	GROUP BY Trainer.name ) 
;