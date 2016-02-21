<?php
  require_once("fonction.php");
  $val = $_GET['val'];
  //$val = 450;
  //$fichier = fopen("log.txt", "a");
  //fwrite($fichier,date("d/m/y H:i ") . $val . "\n");
  // connexion a la BD mysql
  $link = connect();
  //fwrite($fichier,"link " . $link . "\n");
  $query = "INSERT INTO `humidity`(`val`) VALUES ($val)";
  $result = requete($query, $link);
  //fwrite($fichier,$link . " res " . $result . "\n");
  //fclose($fichier);
?>
