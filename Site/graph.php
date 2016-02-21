<?php

DEFINE("TTF_DIR", "./");

require_once("jpgraph/jpgraph.php");
require_once("jpgraph/jpgraph_line.php");
require_once( "jpgraph/jpgraph_date.php" );
require_once("fonction.php");

$link = connect();
$query = "SELECT * FROM `humidity` ORDER BY `index` ASC";
$res = requete($query, $link);
$i = 0;

while ($tab = mysql_fetch_array($res)){
   $data[] = $tab['val'];
   $xdata[] = strtotime($tab['date']);
}

#$data1 = array(12,23,9,58,23,26,57,48,12);

//// Initialisation du graphique
$graphe = new Graph(480,280);
$graphe->SetMargin(40,10,10,80);
$graphe->setScale("datlin",0,800);
$graphe->xaxis->SetFont(FF_VERA,FS_NORMAL,8);
$graphe->xaxis->SetLabelAngle(50);
$graphe->xaxis->scale->SetDateFormat('M:d');

// Creation de l'histogramme
$line1 = new LinePlot($data,$xdata);

// Ajout de l'histogramme au graphique
$graphe->add($line1);

// Ajout du titre du graphique
//$graphe->title->set("Courbe d'humidite");

// Affichage du graphique
$graphe->stroke();
?>
