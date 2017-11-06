<?php
include "db_functions.php";

if(($db = db_connect()) == FALSE) {
  db_report_error("DB access");
  exit(1);
}

if( ($res = db_read($db)) === NULL) {
  db_report_error("DB access");
  exit(2);
}

db_close($db);


// Output section
include("header.html");

//var_dump($res);
foreach($res as $line)
    echo "$line[0], $line[1], $line[2] <br>\n";

include("footer.html");

?>
