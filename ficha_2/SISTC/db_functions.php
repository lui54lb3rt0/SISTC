<?php

function db_connect()
{
  return fopen("/tmp/veic.txt", "a+");
  //return false;
}

function db_insert($db, $rec)
{
  return fwrite($db, trim($rec['plate']).",".trim($rec['owner']).",".trim($rec['value'])."\n");
}

function db_close($db)
{
  fclose($db);
}

function db_read($db)
{
  rewind($db);

  $res = array();
  
  while (($line = fgetcsv($db)) !== false) 
  {
    $res[] = $line;
  }
  
  if($line===NULL)
    return NULL;
  else
    return $res;
}

function db_read_v1($db)
{
  rewind($db);
  
  while (($line = fgets($db)) !== false) 
  {
    $res[] = $line;
  }
  
  return $res;
}

function db_report_error($msg)
{
  echo file_get_contents("header.html");
  //HTML5 supports custom tags. Tag name must contain a character "-".
  echo "<ws-error>Error: $msg</ws-error>\n";
  echo file_get_contents("footer.html");
}

?>
