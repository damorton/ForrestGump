<?php

// Create a line graph displaying the users deaths compared to time spent playing the game
require_once 'phplot-6.1.0/phplot.php';

// Populate the graph with player statistics
$data = array(
	// (time, deaths)
  array('', 1800,   5), array('', 1810,   7), array('', 1820,  10), array('', 1830,  13), array('', 1840,  17), array('', 1850,  23), array('', 1860,  31), array('', 1870,  39), array('', 1880,  50),
  array('', 1890,  63), array('', 1900,  76), array('', 1910,  92),
  array('', 1920, 106), array('', 1930, 123), array('', 1940, 132),
  array('', 1950, 151), array('', 1960, 179), array('', 1970, 203),
  array('', 1980, 227), array('', 1990, 249), array('', 2000, 281),
);

// Create a new graph
$plot = new PHPlot(800, 600);

// Customize the graph
$plot->SetImageBorderType('plain');
$plot->SetPlotType('lines');
$plot->SetDataType('data-data');

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