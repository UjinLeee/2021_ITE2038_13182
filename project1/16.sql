SELECT Trainer.name
FROM City, Trainer
WHERE Trainer.id IN (
		SELECT Trainer.id
  		FROM Trainer, Gym
  		WHERE Trainer.id = Gym.leader_id) AND City.name = Trainer.hometown
	AND City.description = 'Amazon';
