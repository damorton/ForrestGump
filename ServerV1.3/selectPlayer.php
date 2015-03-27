<?php 
/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. And back-end game 
	analytics and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted
	locally and remotely.

	selectPlayer.php

	Description: selectPlayer.php contains implementations of functions used to query the database for 
	player information. It is mainly used for the awards section of the website. 
	
*/

/* Query the database for the player scores and return the player username with the highest score*/
function mostAwesomePlayer(){
	
	$conn = connect();

	// Query the database for player high scores
	$query = "SELECT player_username FROM Player ORDER BY player_score DESC LIMIT 1";
	$result = $conn->query($query);

	$row = $result->fetch_array(MYSQLI_ASSOC);
	echo $row['player_username'];

}

/* Query the database for the enemies killed by the player specified by player_username and 
return the player username with the highest enemy kills*/
function enemyKiller(){
	
	$conn = connect();

	// Query the database for enemies killed
	$query = "SELECT player_username FROM Player ORDER BY player_enemies_killed DESC LIMIT 1";
	$result = $conn->query($query);

	$row = $result->fetch_array(MYSQLI_ASSOC);
	echo $row['player_username'];
}

/* Query the database for the players total distance travelled and return the player username with the highest value*/
function mostDistanceTravelled()
{
	$conn = connect();
	
	// Query the database for player distance travelled
	$query = "SELECT player_username FROM Player ORDER BY player_distance DESC LIMIT 1";
	$result = $conn->query($query);

	$row = $result->fetch_array(MYSQLI_ASSOC);
	echo $row['player_username'];	
}

/* Query the database for the players with the most coins collected and return the result */
function mostCoinsCollected()
{
	$conn = connect();
	
	// Query the database for coins collected
	$query = "SELECT player_username FROM Player ORDER BY player_coins DESC LIMIT 1";
	$result = $conn->query($query);

	$row = $result->fetch_array(MYSQLI_ASSOC);
	echo $row['player_username'];
}

?>