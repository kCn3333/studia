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
<h2>FIRMA 'PRZEW�Z OS�B'</h2>

</td></tr>
<tr><td valign="top">
<center>
<?php
$tab=$_POST['tab'];
$rek=$_POST["rek"];
$key=$_POST["key"];
$query="SHOW COLUMNS FROM $tab";

if(mysql_select_db($dbname))
{
	$result=mysql_query($query);
	if(!$result) return;

	$row=mysql_fetch_assoc($result);
	$query2="UPDATE $tab SET ";
	while($row)
	{
		$query2.=$row["Field"]."='".$_POST[$row["Field"]]."', ";
		$row=mysql_fetch_assoc($result);
	}
	$query2=substr($query2,0,-2);
	$query2.=" WHERE $key='$rek'";
	$result=mysql_query($query2);
	if(!$result) return;
	
	echo "Dane zosta�y zaktualizowane.<br>";
}

?>
<br><a href="index.php"><-- powr�t</a></td></tr></table>

</center>
</BODY>
</HTML>
