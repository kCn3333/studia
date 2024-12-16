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
<h2>FIRMA 'PRZEWÓZ OSÓB'</h2></td></tr>
<tr><td valign="top">
<center>
<?php
$tab=$_POST['tab'];
$query="SHOW COLUMNS FROM $tab";

if(mysql_select_db($dbname))
{
	$result=mysql_query($query);
	if(!$result)
	{
		return;
	}
	$row=mysql_fetch_array($result);
	echo '<form action="saveadd.php" method="POST">';
	echo "<table>";
	while($row)
	{
		echo "<tr><th>".$row["Field"]."</th>";
		echo '<td><input type="text" name="'.$row["Field"].'"></td></tr>';
		$row=mysql_fetch_array($result);
	}
	echo "</table>";
	echo '<input type="hidden" name="tab" value="'.$tab.'">';
	echo '<input type="submit" value="Dodaj">';
	echo "</form>";
}

?>
<br><br><a href="index.php"><-- powrót</a></td></tr></table>

</td></tr></table>
</body>

<hr>
<br>

</center>
</BODY>
</HTML>
