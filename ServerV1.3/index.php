<!--
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. And back-end game 
	analytics and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted
	locally and remotely.

	index.php

	Description: The Grand Theft Muffins website was created using bootstrap template but modified to suit
	the design created by the team. The website itself was heavily modified to display user statistics and
	relevant features. Added : indicates the extra code added to the original template. index.php is the default 
	file served by the apache server when the URL http://www.grandtheftmuffins.esy.es is used.
-->

<!-- Added : include the selectPlayer.php functions and implementation-->
<?php include 'selectPlayer.php'; ?>



<!DOCTYPE html>
<html lang="en">
	<head>
	<meta http-equiv="content-type" content="text/html; charset=UTF-8">
	<meta charset="utf-8">
	<title>Grand Theft Muffins</title>
	<meta name="generator" content="Bootply" />
	<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
	<link href="css/bootstrap.min.css" rel="stylesheet">
	<link href="//netdna.bootstrapcdn.com/font-awesome/3.2.1/css/font-awesome.min.css" rel="stylesheet">
	<!--[if lt IE 9]>
		<script src="//html5shim.googlecode.com/svn/trunk/html5.js"></script>
	<![endif]-->
	<link href="css/styles.css" rel="stylesheet">
	</head>
	<body>

	
	
	
<div class="navbar navbar-fixed-top alt" data-spy="affix" data-offset-top="1000">
  <div class="container">
    <div class="navbar-header">
      <a href="#" class="navbar-brand">Home</a>
      <a class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
      </a>
    </div>
	
	
	
	
	<!-- Added : Navigation bar was modified to link to sections of the website relevant to the
	game and user statistics information.-->
    <div class="navbar-collapse collapse" id="navbar">
      <ul class="nav navbar-nav">
        <li><a href="#leaderboards">Leaderboards</a></li>        
		<li><a href="#awards">Awards</a></li>        
		<li><a href="#game_stats">Game Stats</a></li>        
		<li><a href="#more">More Info</a></li>        
      </ul>
    </div>
   </div>
</div>




<!-- Added : Header modified to display game information and a game download button
that will link to the Windows App Store
TODO : Link to the game in the Windows App Store-->
<div class="header alt vert">
  <div class="container">
    <br/>
    <h1>Grand Theft Muffins</h1>
      <p class="lead">Cocos2dx endless runner game</p>   
	  <a href="" class="btn btn-default btn-lg">Download</a>
  </div>
</div>



<!-- Added : Include the functions and implementation contained in the display_stats.php script-->
<?php include 'display_stats.php'; ?>
		
		
		
		
<!-- Added : Display the game awards using functions in the selectPlayer.php script for 
querying the database and returning specific results.-->
<div class="featurette" id="awards"> 
  <div class="container">
    <div class="row">
		<h1>Awards</h1>
		<ul class="lead">
			<li>Most Awesome Player is <?php mostAwesomePlayer(); ?></li>        
			<li>Enemy Killer is <?php enemyKiller(); ?></li> 
			<li>Forrest Gump is <?php mostDistanceTravelled(); ?></li> 
			<li>Treasure Hunter is <?php mostCoinsCollected(); ?></li>
      	</ul>				
	</div>
  </div>
</div>
		
		
		
		
<!-- Added : Game stats section for displaying the statistics graphs-->
<div class="blurb" id="game_stats">
	<div class="container">
		<div class="row">
			<h1>Game Statistics</h1>
			<br/>
			
			
			
			<!-- Added : Create the graphs using the playerDeathsGraph.php scripts
			TODO : create new scripts for generating specific graphs e.g time in game VS highscores-->
			<!--<img src="graphs/playerDeathsGraph.php"><img src="graphs/playerDeathsGraph.php">-->
			<img src="graph.php"><img src="graph.php">
		</div>
	</div>
</div>
		
		
		
		
<!-- Added : More information section for future use.-->
<div class="featurette" id="more">
  <div class="container">
    <div class="row">
		<h1>More information</h1>		
			<p>
				Loads more information about the game to come :) 
			</p>      	
	</div>
  </div>
</div>




<!-- Added : Social media links for user interactions and notifications-->
<footer>
  <div class="container">
    <div class="row">
      <div class="col-md-6 col-md-offset-3 text-center">
        <ul class="list-inline">
          <li><i class="icon-facebook icon-2x"></i></li>
          <li><i class="icon-twitter icon-2x"></i></li>
          <li><i class="icon-google-plus icon-2x"></i></li>          
        </ul>
        <hr>
		
		
		
		<!-- Added : Team copyright notice-->
        <p>Copyright David Morton, Donnchadh Murphy, Tiago Oliveira, Georgina Sheehan ©2015</p>
      </div>
    </div>
  </div>
</footer>	




<ul class="nav pull-right scroll-down">
  <li><a href="#" title="Scroll down"><i class="icon-chevron-down icon-3x"></i></a></li>
</ul>
<ul class="nav pull-right scroll-top">
  <li><a href="#" title="Scroll to top"><i class="icon-chevron-up icon-3x"></i></a></li>
</ul>



	<!-- script references -->
		<script src="//ajax.googleapis.com/ajax/libs/jquery/2.0.2/jquery.min.js"></script>
		<script src="js/bootstrap.min.js"></script>
		<script src="js/scripts.js"></script>
		
		
	</body>
</html>