
SELECT T.name
FROM Trainer AS T, Gym
WHERE leader_id = id AND T.hometown = 'Brown City';