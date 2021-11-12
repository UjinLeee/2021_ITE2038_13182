
SELECT Trainer.name
FROM Trainer, Gym
WHERE Gym.leader_id = Trainer.id
ORDER BY Trainer.name;