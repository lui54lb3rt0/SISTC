<?php
include("db_functions.php");

if(($db = db_connect()) == FALSE) {
  db_report_error("DB access");
  exit(1);
}

if( ($res = db_read($db)) === FALSE) {
  db_report_error("DB access");
  exit(2);
}

db_close($db);


// Output section
switch($_GET['o']) {

//HTML format, table
case 'html_table':
  include("header.html");

  //CSS
  echo "<style type=\"text/css\">\n
  table, th, td { border: 1px solid black;}\n
  th, td { padding: 15px;}\n
  </style>\n";
  
  echo "<table>\n";  
  //table headers
  echo "<tr><th>Registration plate</th>
        <th>Owner</th><th>Comercial value</th></tr>\n";
  //table rows
  foreach($res as $line) {
    echo "<tr>";    
    foreach($line as $col)
      echo "<td>".$col."</td>";      
    echo "</tr>\n";
  }  
  echo "</table>\n";
  echo "<p>".count($res)." records.</p>\n";

  include("footer.html");  
  break;
  
//HTML format, multiple CSV lines  
default:
  include("header.html");

  foreach($res as $line)
    echo "$line[0], $line[1], $line[2] <br>\n";
    
  include("footer.html");
}

?>
