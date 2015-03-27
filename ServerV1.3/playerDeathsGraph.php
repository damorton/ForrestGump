
<?php
/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. And back-end game 
	analytics and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted
	locally and remotely.

	playerDeathsGraph.php

	Description: The playerDeathsGraph.php file generates game statistics graph for being displayed on the 
	website. All information will be taken from the database and used to generate up to date graphs and
	visual diagrams. 
	
*/

// Include the PHPlot library
require_once 'phplot-6.1.0/phplot.php';

// Create a line graph displaying the users deaths compared to time spent playing the game.

// Populate the graph with player statistics
// TODO : read database and use info to populate the graph values
$data = array(
	// (time, deaths)
	array('a',3),
     array('b',5),
     array('c',7),
     array('d',8),
     array('e',2),
     array('f',6),
     array('g',7)
);

// Create a new graph
$plot = new PHPlot(500, 300);

// Customize the graph
$plot->SetXTickLabelPos('none');
$plot->SetXTickPos('none');
$plot->SetXTitle('Deaths');
$plot->SetYTitle('Time (Seconds)');

// Add values to the graph 
$plot->SetDataValues($data);

// Give it a title
$plot->SetTitle('Player Deaths Statistics');

// Set time to start at 0 seconds
$plot->SetPlotAreaWorld(NULL, 0, NULL, NULL);

// Draw the graph 
$plot->DrawGraph();

// Clean up
$result->free();
$conn->close();

?>