<?php
include 'connect.php';
$conn = connect();

// print whats in the database
$query = "SELECT * FROM Player";
$result = $conn->query($query);

echo '
<div id="game_stats" class="blurb">
	<div class="container">
		<div class="row">
';
		
echo '
			<div class="col-md-18">		  
				<h1>Player Statistics</h1>				
				<table class="reference" style="width:100%">
				<tr>
					<th>Player ID</th>					
					<th>Username</th>					
					<th>Highscore</th>
					<th>Total<br/>Distance</th>
					<th>Coins<br/>Collected</th>					
					<th>Enemies<br/>Killed</th>					
					<th>Items<br/>Collected</th>
					<th>Time<br/>Played</th>
					<th>Games<br/>Played</th>
					<th>Deaths</th>
				</tr>						
';
				
while($row = $result->fetch_array(MYSQLI_ASSOC))
{	
	$playerIDInDB = isset($row["player_id"]) ? $row["player_id"] : "0";
	$playerNameInDB = isset($row["player_username"]) ? $row["player_username"] : "unknown";
	$playerScoreInDB = isset($row["player_score"]) ? $row['player_score'] : "0";	
	$playerDistanceInDB = isset($row["player_distance"]) ? $row['player_distance'] : "0";	
	$playerCoinsInDB = isset($row["player_coins"]) ? $row['player_coins'] : "0";	
	$playerEnemiesKilledInDB = isset($row["player_enemies_killed"]) ? $row['player_enemies_killed'] : "0";	
	$playerItemsCollectedInDB = isset($row["player_items_collected"]) ? $row['player_items_collected'] : "0";	
	$playerTimePlayedInDB = isset($row["player_time_played"]) ? $row['player_time_played'] : "0";	
	$playerGamesPlayedInDB = isset($row["player_games_played"]) ? $row['player_games_played'] : "0";	
	$playerDeathsInDB = isset($row["player_deaths"]) ? $row['player_deaths'] : "0";	
		
	$playerIDInDB = htmlspecialchars($playerIDInDB,ENT_QUOTES);
	$playerNameInDB = htmlspecialchars($playerNameInDB,ENT_QUOTES);
	$playerScoreInDB = htmlspecialchars($playerScoreInDB,ENT_QUOTES);	
	$playerDistanceInDB = htmlspecialchars($playerDistanceInDB,ENT_QUOTES);
	$playerCoinsInDB = htmlspecialchars($playerCoinsInDB,ENT_QUOTES);	
	$playerEnemiesKilledInDB = htmlspecialchars($playerEnemiesKilledInDB,ENT_QUOTES);	
	$playerItemsCollectedInDB = htmlspecialchars($playerItemsCollectedInDB,ENT_QUOTES);	
	$playerTimePlayedInDB = htmlspecialchars($playerTimePlayedInDB,ENT_QUOTES);
	$playerGamesPlayedInDB = htmlspecialchars($playerGamesPlayedInDB,ENT_QUOTES);
	$playerDeathsInDB = htmlspecialchars($playerDeathsInDB,ENT_QUOTES);

	echo "  
	<tr>
		<td>$playerIDInDB</td>
		<td>$playerNameInDB</td>
		<td>$playerScoreInDB</td>		
		<td>$playerDistanceInDB m</td>		
		<td>$playerCoinsInDB</td>		
		<td>$playerEnemiesKilledInDB</td>		
		<td>$playerItemsCollectedInDB</td>		
		<td>$playerTimePlayedInDB Secs</td>
		<td>$playerGamesPlayedInDB</td>
		<td>$playerDeathsInDB</td>
	</tr>			 
	";
}


echo '		
			</table>		 
			</div>			
		</div>
	</div>
</div>
';		

$result->free();
$conn->close();
?>