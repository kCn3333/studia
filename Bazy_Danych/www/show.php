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
<center><hr>
<?php
$tab=$_POST['tab'];
$query = "SELECT * FROM $tab";
echo "<h2>Zawartosc tabeli ",$tab,"</h2><br>";

if(mysql_select_db($dbname))
   {
   $result = mysql_query($query);
   mysql_close();
   if($result)
      {
      	for($i=0; $i<mysql_num_fields($result); $i++)
      	{
      		$field=mysql_fetch_field($result,$i);
      		if($field->primary_key)
      		{
      			$key=$field->name;
      		}
      	}
      	
		echo '<form name="form" method="POST" action="edit.php">';
      	echo "<table border='2'>";
		echo "<tr><th></th>";
      	
		$row=mysql_fetch_assoc($result);
      	
      	foreach($row as $field=>$value)
      	{
      		echo "<th>$field</th>";
      	}
      	echo "</tr>";
		
      	while($row)
      	{
      		echo "<tr>";
      		echo "<td><input type='radio' name='rek' value='".$row[$key]."'></td>";
			
      		foreach($row as $field=>$value)
      		{
      			echo "<td>$value</td>";
      		}
      		echo "</tr>";
      		$row=mysql_fetch_assoc($result);
      	}
      	echo '<input type="hidden" name="tab" value="'.$tab.'">';
      	echo '<input type="hidden" name="key" value="'.$key.'">';
      	echo "</table>";
      	echo '<br><br><input type="submit" value="Edytuj"></form>';
      	echo "</form>";
      } 
	  else echo "Tabela jest pusta.";
      echo '<form name="form" method="POST" action="add.php">';
      echo '<input type="hidden" name="tab" value="',$tab,'">';
      echo '<br><br><input type="submit" value="Dodaj"></form>';
         

  } else echo "Bład odczytu.";

?>

<br><a href="index.php"><-- powrót</a></td></tr></table>

</td></tr></table>
</body>

<br>

</center>
</BODY>
</HTML>
