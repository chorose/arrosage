<?php

function connect(){
   #$link = mysql_connect("localhost","chorose","elouan");
   #mysql_select_db("chorose", $link) or die(mysql_error());
   $link = mysql_connect("localhost","roselyne");
   mysql_select_db("domotic", $link) or die(mysql_error());
   return $link;
}

function requete($query, $link){
   $result = mysql_query($query, $link) or die($query . " - " . mysql_error());
   return $result;
}

?>
