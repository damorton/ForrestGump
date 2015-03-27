<?php
include 'connect.php';
$conn = connect();

// print whats in the database
$query = "SELECT * FROM Player ORDER BY player_score DESC";
$result = $conn->query($query);

echo '
<div id="game_stats" class="blurb">
	<div class="container">
		<div class="row">
';
		
echo '
			<div class="table-responsive">		  
				<h1>Player Statistics</h1>				
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

while($row = $result->fetch_array(MYSQLI_ASSOC))
{	
	$playerRank++;
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
	//$playerDeathsInDB = isset($row["player_deaths"]) ? $row['player_deaths'] : "0";	
		
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
	//$playerDeathsInDB = htmlspecialchars($playerDeathsInDB,ENT_QUOTES);

	echo "  
	<tr>
		<td>$playerPosition</td>
		<td>$playerNameInDB</td>
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

$playerRank = 0;

echo '		
			</table>		 
			</div>			
		</div>
	</div>
</div>
';		


?>