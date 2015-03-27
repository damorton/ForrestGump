<?php
/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. And back-end game 
	analytics and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted
	locally and remotely.

	display_stats.php

	Description: The game statistics table is generated dynamically when this script is called. The information
	stored in the database is used to populate the table. Each time the website is accessed or refreshed the contents
	of the database and the website will be generated. The database is queried and the results are displayed in descending
	order by highscore to create a ranking system for players.
	
*/

// Connect to the MySQL database
include 'connect.php';
$conn = connect();

// Query the database for all information stored in the database in descending order of player scores
//$query = "SELECT * FROM Player ORDER BY player_score DESC LIMIT 10";
$query = "SELECT * FROM Player ORDER BY player_score DESC";
$result = $conn->query($query);


// Generate the html code for the website
echo '
<div id="leaderboards" class="blurb">
	<div class="container">
		<div class="row">
';
		
// Create the table to display all the players information
echo '
			<div class="table-responsive">		  
				<h1>Top 10</h1>				
				<table class="table">
				<tr>
					<th>Rank</th>										
					<th>Username</th>					
					<th>Highscore</th>
					<th>Distance Travelled (M)</th>
					<th>Coins Collected</th>					
					<th>Enemies Killed</th>					
					<th>Items Collected</th>
					<th>Seconds In Game</th>
					<th>Games Played</th>
					
				</tr>						
';

// Keep a count for the players ranking in the leaderboard
$playerRank = 0;


// While there are still rows in the query results, grab the players statistics info
while($row = $result->fetch_array(MYSQLI_ASSOC))
{	
	// Increment the player rank
	$playerRank++;
	
	// 
	//$playerIDInDB = isset($row["player_id"]) ? $row["player_id"] : "0";
	$playerPosition = $playerRank;
	$playerNameInDB = isset($row["player_username"]) ? $row["player_username"] : "unknown";
	$playerScoreInDB = isset($row["player_score"]) ? $row['player_score'] : "0";	
	$playerDistanceInDB = isset($row["player_distance"]) ? $row['player_distance'] : "0";	
	$playerCoinsInDB = isset($row["player_coins"]) ? $row['player_coins'] : "0";	
	$playerEnemiesKilledInDB = isset($row["player_enemies_killed"]) ? $row['player_enemies_killed'] : "0";	
	$playerItemsCollectedInDB = isset($row["player_items_collected"]) ? $row['player_items_collected'] : "0";	
	$playerTimePlayedInDB = isset($row["player_time_played"]) ? $row['player_time_played'] : "0";	
	$playerGamesPlayedInDB = isset($row["player_games_played"]) ? $row['player_games_played'] : "0";	
	$playerDeathsInDB = isset($row["player_deaths"]) ? $row['player_deaths'] : "0";	
		
	//$playerIDInDB = htmlspecialchars($playerIDInDB,ENT_QUOTES);
	$playerPosition = htmlspecialchars($playerPosition,ENT_QUOTES);
	$playerNameInDB = htmlspecialchars($playerNameInDB,ENT_QUOTES);
	$playerScoreInDB = htmlspecialchars($playerScoreInDB,ENT_QUOTES);	
	$playerDistanceInDB = htmlspecialchars($playerDistanceInDB,ENT_QUOTES);
	$playerCoinsInDB = htmlspecialchars($playerCoinsInDB,ENT_QUOTES);	
	$playerEnemiesKilledInDB = htmlspecialchars($playerEnemiesKilledInDB,ENT_QUOTES);	
	$playerItemsCollectedInDB = htmlspecialchars($playerItemsCollectedInDB,ENT_QUOTES);	
	$playerTimePlayedInDB = htmlspecialchars($playerTimePlayedInDB,ENT_QUOTES);
	$playerGamesPlayedInDB = htmlspecialchars($playerGamesPlayedInDB,ENT_QUOTES);
	$playerDeathsInDB = htmlspecialchars($playerDeathsInDB,ENT_QUOTES);

	// Display the players statistics in a table
	// TODO : 	use the player name and statistics to generate localised data for the player
	// 			by sending each players username to the uername_stats.php script. 
	echo "  
	<tr>
		<td>$playerPosition</td>		
		<td><a href='username_stats.php?playerUsername=$playerNameInDB'>$playerNameInDB</a></td>
		<td class='info'>$playerScoreInDB</td>		
		<td>$playerDistanceInDB</td>		
		<td>$playerCoinsInDB</td>		
		<td>$playerEnemiesKilledInDB</td>		
		<td>$playerItemsCollectedInDB</td>		
		<td>$playerTimePlayedInDB</td>
		<td>$playerGamesPlayedInDB</td>
		
	</tr>			 
	";
}

// Reset the player rank after the table has been generated
$playerRank = 0;

echo '		
			</table>		 
			</div>			
		</div>
	</div>
</div>
';		


?>