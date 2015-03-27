<?php	
/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. And back-end game 
	analytics and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted
	locally and remotely.

	create_user.php

	Description: This will handle checking the database for the new user and adding them if they do not already exist. 
	The secret key is generated when the game is first installed and paired with the username, this is then used to 
	stop users being hacked. It provides added security for the game statistics and user data
	
	TODO : implement secret key in both game and back-end system
*/
function createUserIfNotExists($connection, $playerUsername)
{		
	// Check that players are entering usernames in the correct format
	if($playerUsername == NULL || strlen($playerUsername) < 4 || strlen($playerUsername) > 12)
	{		
		printf("Error: player username not in the correct format, don't give up! try again :)");
	}	
	
	// Search for the player in the database
	// TODO : add secret key check for uniqueness
	$searchResult = $connection->query("SELECT player_username FROM Player WHERE player_username = '$playerUsername' LIMIT 1");
	if ($searchResult->num_rows) {
		// If the user exists do not add them again
		printf("Error: player already exists in the database");
	}
	else
	{		
		// Insert user into database if not NULL
		if($playerUsername != NULL)
		{
			$connection->query("INSERT INTO Player (player_username) VALUES ('$playerUsername')");	
		}
	}
	
	// Free the query result
	$searchResult->free();
}
?>