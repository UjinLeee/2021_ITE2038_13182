SELECT Trainer.name
FROM Trainer, CatchedPokemon
WHERE CatchedPokemon.owner_id =Trainer.id
GROUP By Trainer.id
HAVING COUNT(Trainer.id) >= 3
ORDER BY COUNT(Trainer.id) 
;
