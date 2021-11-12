
SELECT AVG(CatchedPokemon.level)
FROM Trainer, CatchedPokemon
WHERE Trainer.id = CatchedPokemon.owner_id 
AND Trainer.name = 'Red';