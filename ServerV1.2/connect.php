<?php
function connect()
{
	// Database login details
	$username = "u583858232_david";
	$password = "davidGTMDB88";
	$hostname = "localhost";
	$database = "u583858232_gtmdb";

	// Connect to the database
	$conn = new mysqli($hostname,$username,$password,$database);

	// Return a message if the connection failed
	if($conn->connect_errno)
	{
		printf("Connection failed, and that's all the information your allowed to have :)");
	}
	return $conn;
}
?>