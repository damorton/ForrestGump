<?php	
/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. And back-end game 
	analytics and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted
	locally and remotely.

	update_db.php

	Description: The update_db.php script reads the data it receives from the game in a HTTP Request message.
	The data is then checked and the database is updated accordingly. Users are created if they do not already
	exist in the database.
	
*/

// Read the values in the POST message received from the game
// The isset() function is used to validate the values coming from the post message
$playerUsername = isset($_POST['playerUsername']) ? $_POST['playerUsername'] : NULL;
$playerHighscore = isset($_POST['playerHighscore']) ? $_POST['playerHighscore'] : NULL;	
$playerDistance = isset($_POST['playerDistance']) ? $_POST['playerDistance'] : NULL;	
$playerCoins = isset($_POST['playerCoins']) ? $_POST['playerCoins'] : NULL;	
$enemiesKilled = isset($_POST['enemiesKilled']) ? $_POST['enemiesKilled'] : NULL;
$itemsCollected = isset($_POST['itemsCollected']) ? $_POST['itemsCollected'] : NULL;
$timePlayed = isset($_POST['timePlayed']) ? $_POST['timePlayed'] : NULL;
$numberOfGamesPlayed = isset($_POST['numberOfGamesPlayed']) ? $_POST['numberOfGamesPlayed'] : NULL;
$deaths = isset($_POST['numberOfDeaths']) ? $_POST['numberOfDeaths'] : NULL;

// Connect to the database
require_once 'connect.php';
$conn = connect();

// Create new user if they do not already exist in the database
require_once 'create_user.php';
createUserIfNotExists($conn, $playerUsername);

// Grab data from the database for the player
$query = "SELECT * FROM Player WHERE player_username = '$playerUsername' ";
$result = $conn->query($query);					

//echo $playerHighscoreDB;

// Loop through each row of the results. Should only be one row
while($row = $result->fetch_array(MYSQLI_ASSOC))
{
	// Get stored data
	$playerHighscoreDB = $row['player_score'];
	$playerDistanceDB = $row['player_distance'];  
	$playerCoinsDB = $row['player_coins'];  
	$playerEnemiesKilledDB = $row['player_enemies_killed'];  
	$playerItemsCollectedDB = $row['player_items_collected'];  
	$playerTimePlayedDB = $row['player_time_played'];  
	$playerGamesPlayedDB = $row['player_games_played'];  
	$playerDeathsDB = $row['player_deaths'];  
	
	// Increment each of the player stats
	$playerDistanceDB += $playerDistance;
	$playerCoinsDB += $playerCoins;
	$playerEnemiesKilledDB += $enemiesKilled;  
	$playerItemsCollectedDB += $itemsCollected;  
	$playerTimePlayedDB += $timePlayed;  
	$playerGamesPlayedDB += $numberOfGamesPlayed;  
	$playerDeathsDB += $deaths;  
	
}

// Update the players highscore if better than previously saved score
if($playerHighscore > $playerHighscoreDB)
{
	$playerHighscoreDB = isset($playerHighscore) ? $playerHighscore : '0';	
}
else
{
	// Store the value already stored in the database 
	$playerHighscoreDB = isset($playerHighscoreDB) ? $playerHighscoreDB : '0';
}

// Reset highscore
//$playerHighscoreDB = isset($playerHighscore) ? $playerHighscore : '0';	

// Check each variable before storing it in the database
$playerDistanceDB = isset($playerDistanceDB) ? $playerDistanceDB : NULL; 
$playerCoinsDB = isset($playerCoinsDB) ? $playerCoinsDB : NULL; 
$playerEnemiesKilledDB = isset($playerEnemiesKilledDB) ? $playerEnemiesKilledDB : NULL; 
$playerItemsCollectedDB = isset($playerItemsCollectedDB) ? $playerItemsCollectedDB : NULL; 
$playerTimePlayedDB = isset($playerTimePlayedDB) ? $playerTimePlayedDB : NULL; 
$playerGamesPlayedDB = isset($playerGamesPlayedDB) ? $playerGamesPlayedDB : NULL; 
$playerDeathsDB = isset($playerDeathsDB) ? $playerDeathsDB : NULL; 

// update the players score in the database
$updateDBQuery = "	UPDATE Player 
			SET player_score = 	$playerHighscoreDB, 
				player_distance = $playerDistanceDB,
				player_coins =	$playerCoinsDB, 
				player_enemies_killed =	$playerEnemiesKilledDB, 
				player_items_collected = $playerItemsCollectedDB,
				player_time_played = $playerTimePlayedDB,
				player_games_played = $playerGamesPlayedDB,
				player_deaths =	$playerDeathsDB
			WHERE player_username = '$playerUsername'";			
$conn->query($updateDBQuery);

// Release resources created by the script
$result->free();
$conn->close();
?>