SELECT Pokemon.name
FROM Evolution, Pokemon
WHERE before_id > after_id
AND Evolution.before_id = Pokemon.id; 
