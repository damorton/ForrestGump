<?php
function connect()
{
	$username = "u583858232_david";
	$password = "davidGTMDB88";
	$hostname = "localhost";
	$database = "u583858232_gtmdb";

	$conn = new mysqli($hostname,$username,$password,$database);

	if($conn->connect_errno)
	{
		die("Connection failed: " . $conn->connect_error);
	}
	return $conn;
}


?>