<?php
include_once "mysql.connection.php";
?>
<HTML>
<HEAD>
<META  http-equiv="Content-Type" content="text/html; charset=iso-8859-2">
</HEAD>
<BODY>

<style>
BODY {background-color: #FFFFCE}
A:visited {font-weight: bold; text-decoration: none}
A:hover {font-weight: bold; text-decoration: underline}
A:link {font-weight: bold; text-decoration: none}
TD {text-align: justify; font-family: Verdana; font-size: 10pt}
.head {font-family: Tahoma; font-weight: bold; font-size: 12pt; color: black}
</style>

<table border="0" cellspacing="15" bgcolor="#FFFFDF" align="center" width="700" style="text-align: justify; font-family: Verdana; font-size: 10pt">
<tr><td><center>
<h2>FIRMA 'PRZEWÓZ OSÓB'</h2>
<br><img src="taxi.gif">

</td></tr>
<tr><td valign="top">
<center><hr>
<?php

$query = "SHOW TABLES";

if(mysql_select_db($dbname))
   {
   $result = mysql_query($query);
   $n = mysql_num_rows($result);
   mysql_close();
   if($n>0)
      {
      echo"<table border='2'><tr>";
      echo"<th>&nbsp;</th>";
	  echo"<th>&nbsp;lp.&nbsp;</th>";
	  echo"<th>&nbsp;Nazwa Tabeli&nbsp;&nbsp;</th></tr>";
	  
      echo '<form name="form" method="POST" action="show.php">';
      for($i=0; $i<$n; $i++)
	  {
         $row= mysql_fetch_array($result);
         echo "<tr><td><input type='radio' name='tab' value='",$row[0],"'>";
		 echo "<td>&nbsp;",$i+1,"</td>";
		 echo "<td>&nbsp;",$row[0],"</td></tr>";
	  }
      echo "</table>";
      echo '<br><br><input type="submit" value="Pokaż zawartosć"></form>';
      } 
	  else echo "Baza jest pusta.";
  } 
  else echo "Bład odczytu.";

?>

<br>

</td></tr></table>
</body>

<br>

</center>
</BODY>
</HTML>
