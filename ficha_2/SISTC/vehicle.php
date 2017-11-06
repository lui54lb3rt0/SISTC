<?php

include "db_functions.php";

$db = db_connect();
if($db == FALSE)
{
  db_report_error("DB access");
  exit(1);
}

/*
$rec['value'] = $_POST['value'];
$rec['owner'] = $_POST['owner'];
$rec['plate'] = $_POST['plate'];
*/


if( db_insert($db, $_POST) == FALSE)
{
  db_report_error("DB access");
  exit(2);
}

db_close($db);


//Confirmation
include("header.html");
echo "Record inserted\n";
include("footer.html");


?>
