<?php


include "db_functions.php";

$db = db_connect();
if($db == FALSE)
{
  db_report_error("DB access");
  exit(1);
}

$rec['value'] = "100000.00";
$rec['owner'] = "John Doe";
$rec['plate'] = "IJD007";

if( db_insert($db, $rec) == FALSE)
{
  db_report_error("DB access");
  exit(2);
}


$rec['value'] = "50000.00";
$rec['owner'] = "Jane Doe";
$rec['plate'] = "00JJ77";

if( db_insert($db, $rec) == FALSE)
{
  db_report_error("DB access");
  exit(2);
}

$rec['value'] = "20000.00";
$rec['owner'] = "Fulano Cicrano";
$rec['plate'] = "11AA22";

if( db_insert($db, $rec) == FALSE)
{
  db_report_error("DB access");
  exit(2);
}

db_close($db);


//Confirmation
include("header.html");
echo "Records inserted\n";
include("footer.html");


?>
