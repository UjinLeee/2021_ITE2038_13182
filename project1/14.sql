SELECT City.name
FROM City, Trainer
WHERE City.name = Trainer.hometown
GROUP BY City.name
HAVING COUNT(Trainer.id) >= ALL(
		SELECT COUNT(Trainer.id)
  		FROM City, Trainer
  		WHERE City.name = Trainer.hometown
  		GROUP BY City.name
	);
