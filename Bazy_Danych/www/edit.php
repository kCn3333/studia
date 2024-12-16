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
$rek=$_POST['rek'];
$key=$_POST['key'];
$query = "SELECT * FROM $tab WHERE $key = '$rek'";
echo "<h2>Zawartosc tabeli ",$tab,"</h2><br>";

if(mysql_select_db($dbname))
   {
   $result = mysql_query($query);
   mysql_close();
   if($result)
      {
      echo '<form name="form" method="POST" action="save.php">';
      echo "<table border='2'>";
      $row=mysql_fetch_assoc($result);
      foreach($row as $field=>$value)
      {
      	echo "<tr><th>$field</th><td>";
      	echo '<input type="text" name="'.$field.'" value="'.$value.'">';
      	echo "</td>";
      }
      echo "</table>";
      echo '<input type="hidden" name="tab" value="'.$tab.'">';
      echo '<input type="hidden" name="key" value="'.$key.'">';
      echo '<input type="hidden" name="rek" value="'.$rek.'">';
      echo '<br><input type="submit" value="Zapisz">';
      echo "</form>";
      } else echo "Tabela jest pusta.";
      if($rek)
         {
         echo '<form name="form" method="POST" action="del.php">';
         echo '<input type="hidden" name="tab" value="',$tab,'">';
      	 echo '<input type="hidden" name="key" value="'.$key.'">';
      	 echo '<input type="hidden" name="rek" value="'.$rek.'">';
         echo '<br><br><input type="submit" value="Usun dane"></form>';
         }
  } else echo "Blad odczytu.";

?>
<br><a href="index.php"><-- powrót</a></td></tr></table>

</td></tr></table>
</body>

<hr>
<br>

</center>
</BODY>
</HTML>

