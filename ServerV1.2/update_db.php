<?php	


// Read the values in the post
$playerUsername = isset($_POST['playerUsername']) ? $_POST['playerUsername'] : NULL;
$playerHighscore = isset($_POST['playerHighscore']) ? $_POST['playerHighscore'] : '0';	
$playerDistance = isset($_POST['playerDistance']) ? $_POST['playerDistance'] : '0';	
$playerCoins = isset($_POST['playerCoins']) ? $_POST['playerCoins'] : '0';	
$enemiesKilled = isset($_POST['enemiesKilled']) ? $_POST['enemiesKilled'] : '0';
$itemsCollected = isset($_POST['itemsCollected']) ? $_POST['itemsCollected'] : '0';
$timePlayed = isset($_POST['timePlayed']) ? $_POST['timePlayed'] : '0';
$numberOfGamesPlayed = isset($_POST['numberOfGamesPlayed']) ? $_POST['numberOfGamesPlayed'] : '0';
$deaths = isset($_POST['numberOfDeaths']) ? $_POST['numberOfDeaths'] : '0';

// Connect to the database
include 'connect.php';
$conn = connect();

// CHECK IF THE USER IS IN THE DATABASE
// IF NOT INSERT THEN
// UPDATE PLAYER

//include 'create_user.php';
// First, prevent sql injection with mysql_real_escape_string
//$string = mysql_real_escape_string($string);

//$playerUsername = mysql_real_escape_string($playerUsername);  // SECURITY!
$searchResult = $conn->query("SELECT player_username FROM Player WHERE player_username = '$playerUsername' LIMIT 1");
if ($searchResult->num_rows) {
	//echo 'User exists in database';
	// do nothing
}
else
{
	//echo 'User does not exist';
	// Insert user into database if not unknown
	if($playerUsername != NULL)
	{
		$conn->query("INSERT INTO Player (player_username) VALUES ('$playerUsername')");	
	}
}
$searchResult->free();

/// Grab data from the database for the player
$query = "SELECT * FROM Player WHERE player_username = '$playerUsername' ";
$result = $conn->query($query);					

//echo $playerHighscoreDB;

while($row = $result->fetch_array(MYSQLI_ASSOC))
{
	// get stored data
	$playerHighscoreDB = $row['player_score'];
	$playerDistanceDB = $row['player_distance'];  
	$playerCoinsDB = $row['player_coins'];  
	$playerEnemiesKilledDB = $row['player_enemies_killed'];  
	$playerItemsCollectedDB = $row['player_items_collected'];  
	$playerTimePlayedDB = $row['player_time_played'];  
	$playerGamesPlayedDB = $row['player_games_played'];  
	$playerDeathsDB = $row['player_deaths'];  
	
	// increment each of the player stats
	$playerDistanceDB += $playerDistance;
	$playerCoinsDB += $playerCoins;
	$playerEnemiesKilledDB += $enemiesKilled;  
	$playerItemsCollectedDB += $itemsCollected;  
	$playerTimePlayedDB += $timePlayed;  
	$playerGamesPlayedDB += $numberOfGamesPlayed;  
	$playerDeathsDB += $deaths;  
	
}

// Update the players highscore
if($playerHighscore > $playerHighscoreDB)
{
	$playerHighscoreDB = isset($playerHighscore) ? $playerHighscore : '0';	
}
else
{
	$playerHighscoreDB = isset($playerHighscoreDB) ? $playerHighscoreDB : '0';
}

// reset highscore
//$playerHighscoreDB = isset($playerHighscore) ? $playerHighscore : '0';	

$playerDistanceDB = isset($playerDistanceDB) ? $playerDistanceDB : '0'; 
$playerCoinsDB = isset($playerCoinsDB) ? $playerCoinsDB : '0'; 
$playerEnemiesKilledDB = isset($playerEnemiesKilledDB) ? $playerEnemiesKilledDB : '0'; 
$playerItemsCollectedDB = isset($playerItemsCollectedDB) ? $playerItemsCollectedDB : '0'; 
$playerTimePlayedDB = isset($playerTimePlayedDB) ? $playerTimePlayedDB : '0'; 
$playerGamesPlayedDB = isset($playerGamesPlayedDB) ? $playerGamesPlayedDB : '0'; 
$playerDeathsDB = isset($playerDeathsDB) ? $playerDeathsDB : '0'; 

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

$result->free();
$conn->close();
?>