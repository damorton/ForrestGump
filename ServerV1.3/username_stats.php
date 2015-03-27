<!--
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. And back-end game 
	analytics and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted
	locally and remotely.

	username_stats.php

	Description: The username_stats.php will be used to generate personalised data for a specific
	player. A new web page is generated with visual graphs and game statistics stored in the database.	
-->
<html>
<body>


<!-- Return the value sent to the script using the URL method transferring data.
e.g http://grandtheftmuffins.esy.es/username_stats.php?playerUsername=David
TODO : Get this working... :/
-->
Welcome <?php echo $_POST['playerUsername']; ?><br>

</body>
</html>