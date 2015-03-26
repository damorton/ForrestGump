<?php	

include 'connect.php';

function createUser($username)
{	
	$conn = connect();
	$sql = "INSERT INTO Player (player_username)
	VALUES ($username)";
	if ($conn->query($sql) === TRUE) {
		echo "New user created successfully";
	} else {
		echo "Error: " . $sql . "<br>" . $conn->error;
	}
	$conn->close();
}
?>