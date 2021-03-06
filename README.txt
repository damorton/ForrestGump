Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

http://www.grandtheftmuffins.esy.es

Third year games design and development project. Grand Theft Muffins endless runner game
written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

Database instructions
=====================

The database for the game is hosted remotely at http://grandtheftmuffins.esy.es/ on an Apache server. The Apache 
server was installed as a LAMP stack, Linux, Apache, MySQL and PHP. The Apache server deals with requests.
The PHP scripts then act as an interface between the game and the MySQL database. The MySQL database contains a Player
table that is updated based on the information received from the game.

The LAMP stack used for testing locally was https://www.apachefriends.org/index.html. XAMPP can be installed locally on a 
machine and the games data access object will communicate with a server locally as well as remotely. 

LOCAL SERVER SETUP
------------------

1. Install XAMPP making sure to switch off anti virus and UAC User Account Control
2. In the XAMPP control panel start the Apache server and the MySQL database
3. go to http://localhost/ and the XAMPP landing page should appear
4. Choose a language and then navigate to phpMyAdmin
5. Create a database and modify the connect.php file changing the database login details to the database you just created
6. Click Import from the menu options to import the table used by the game
7. Click Choose file and navigate to the player.SQL file in the projects ServerV1.3 folder
8. The character set of the file is utf-8
9. Format is SQL and click Go at the bottom of the screen

This will create the table needed for the game statistics.

Now copy the contents of the ServerV1.3 folder into C:\xampp\htdocs\

Goto http://localhost/ to see the website

Now when a game is played information will be sent to the local server and if you have an internet connection the remote 
database will also be updated. Refresh http://localhost/ to see changes made to the database, or http://grandtheftmuffins.esy.es/ for the 
remote changes.



