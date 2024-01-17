<?php

		
	$dbhost = 'localhost';	
	$dbuser = 'root';
	$dbpass = 'vertrigo';
	$dbname = 'taxi';
	

	$link = mysql_connect($dbhost, $dbuser, $dbpass);
	if (!$link) 
	{
		die('<center><br>Nie mo¿na siê po³aczyæ: </center>' . mysql_error());
	}
	mysql_select_db($dbname) or die('<center><br>Nie udalo sie wybrac bazy danych.</center>');
	
?>
