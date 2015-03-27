<?php
/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. And back-end game 
	analytics and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted
	locally and remotely.

	connect.php

	Description: Connect will handle the connection to the MySQL database. The hostname is localhost because
	the PHP scripts run on a machine with the same IP address as the MySQL database. Only the login details and database
	name will be modified for locally hosted servers and databases.
*/
function connect()
{
	// Remote database login details
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