<?php 

function mostAwesomePlayer(){
	
	$conn = connect();

	// print whats in the database
	$query = "SELECT player_username FROM Player ORDER BY player_score DESC LIMIT 1";
	$result = $conn->query($query);

	$row = $result->fetch_array(MYSQLI_ASSOC);
	echo $row['player_username'];

}

function enemyKiller(){
	
	$conn = connect();

	// print whats in the database
	$query = "SELECT player_username FROM Player ORDER BY player_enemies_killed DESC LIMIT 1";
	$result = $conn->query($query);

	$row = $result->fetch_array(MYSQLI_ASSOC);
	echo $row['player_username'];
}

function mostDistanceTravelled()
{
	$conn = connect();
	
	// print whats in the database
	$query = "SELECT player_username FROM Player ORDER BY player_distance DESC LIMIT 1";
	$result = $conn->query($query);

	$row = $result->fetch_array(MYSQLI_ASSOC);
	echo $row['player_username'];	
}

function mostCoinsCollected()
{
	$conn = connect();
	
	// print whats in the database
	$query = "SELECT player_username FROM Player ORDER BY player_coins DESC LIMIT 1";
	$result = $conn->query($query);

	$row = $result->fetch_array(MYSQLI_ASSOC);
	echo $row['player_username'];
}

?>