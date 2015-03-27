<?php	
function createUserIfNotExists($connection, $playerUsername)
{		
	// Check that players are entering usernames in the correct format
	if($playerUsername == NULL || strlen($playerUsername) < 4 || strlen($playerUsername) > 12)
	{		
		printf("Error: player username not in the correct format");
	}	
	
	// Search for the player in the database
	$searchResult = $connection->query("SELECT player_username FROM Player WHERE player_username = '$playerUsername' LIMIT 1");
	if ($searchResult->num_rows) {
		// If the user exists do not add them again
		printf("Error: player already exists in the database");
	}
	else
	{		
		// Insert user into database if not NULL
		if($playerUsername != NULL)
		{
			$connection->query("INSERT INTO Player (player_username) VALUES ('$playerUsername')");	
		}
	}
	
	// Free the query result
	$searchResult->free();
}
?>