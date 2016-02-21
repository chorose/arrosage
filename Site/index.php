<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<head>
<meta content="yes" name="apple-mobile-web-app-capable" />
<meta content="text/html; charset=utf-8" http-equiv="Content-Type" />
<meta content="minimum-scale=1.0, width=device-width, maximum-scale=0.6667, user-scalable=no" name="viewport" />
<link href="css/style.css" rel="stylesheet" media="screen" type="text/css" />
<link rel="apple-touch-icon-precomposed" href="./images/arrosoir.jpg"/>
<script type="text/javascript" src="javascript/function.js"></script>
<title>Arrosage</title>
</head>

<body>


<div id="topbar">
   <div id="title">Arrosage</div>
</div>

<div id="content">
   <ul class="pageitem">
      <li class="textbox">
         <span class="header">Dernier relevé</span>
<?php
require_once("fonction.php");
$link = connect();
$query = "SELECT date, val FROM `humidity` ORDER BY `index` DESC LIMIT 1;";
$res = requete($query, $link);
$date=mysql_result($res,0); 
$val=mysql_result($res,0,1); 
echo "<p>" . $date . " - " . $val . "</p>";
?>

      </li>
      <li class="menu">
         <a href="./pgraph.html">
         <img src="thumbs/stocks.png" />
         <span class="name">Courbe d'humidité</span>
         <span class="comment">Voir</span>
         <span class="arrow"></span>
         </a>
      </li>
   </ul>
   <ul class="pageitem">
      <form method="get" action="http://avot.no-ip.org:8000/">
      <!form method="get" action="http://192.168.1.101:8000/">
      <li class="checkbox"><span class="name">Faire un relevé</span><input name="rel" type="checkbox" onclick="this.form.submit();" /> </li>
      <li class="checkbox"><span class="name">Arroser</span><input name="arr" type="checkbox" onclick="this.form.submit();"/> </li>
      </form>
   </ul>
   <ul class="pageitem">
      <li class="menu">
         <a href="./reglages.html">
         <img src="thumbs/settings.png" />
         <span class="name">Réglages</span>
         <span class="comment">Voir</span>
         <span class="arrow"></span>
         </a>
      </li>
   </ul>
</div>

<div id="footer">
	<!-- Support iWebKit by sending us traffic; please keep this footer on your page, consider it a thank you for my work :-) -->
	<a class="noeffect" href="http://snippetspace.com">iPhone site powered by iWebKit</a></div>

</body>

</html>
