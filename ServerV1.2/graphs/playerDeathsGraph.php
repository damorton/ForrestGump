<?php

// Create a line graph displaying the users deaths compared to time spent playing the game
require_once '../phplot-6.1.0/phplot.php';



// Populate the graph with player statistics
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