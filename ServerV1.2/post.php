<?php	

// Read the values in the post
$playerUsername = isset($_POST['playerUsername']) ? $_POST['playerUsername'] : 'David';
$playerScore = isset($_POST['playerScore']) ? $_POST['playerScore'] : '567';	
$playerDistance = isset($_POST['playerDistance']) ? $_POST['playerDistance'] : '123';	
$playerCoins = isset($_POST['playerCoins']) ? $_POST['playerCoins'] : '999';	
$enemiesKilled = isset($_POST['enemiesKilled']) ? $_POST['enemiesKilled'] : '5';
$itemsCollected = isset($_POST['itemsCollected']) ? $_POST['itemsCollected'] : '26';
$timePlayed = isset($_POST['timePlayed']) ? $_POST['timePlayed'] : '789';
$numberOfGamesPlayed = isset($_POST['numberOfGamesPlayed']) ? $_POST['numberOfGamesPlayed'] : '1';
		
include 'connect.php';
$conn = connect();




// query db for users score and increment
$userScoreQuery = "	SELECT player_score 
					FROM Player 
					WHERE player_username = '$playerUsername' ";	

$dbScore = $conn->query($userScoreQuery);

while($row = $result->fetch_array(MYSQLI_ASSOC))
{  
  $pScore = $row['player_score'];  
  $pScore += $playerScore;  
}
$pScore = isset($pScore) ? $pScore : '0';

// update the players score in the database
$query = "	UPDATE users 
			SET playerScore = $pScore
			WHERE playerUsername = '$playerUsername'";
			
$result->free();
$conn->close();
?>