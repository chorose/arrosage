<head>
  <title>Domotic</title>
  <meta name="Roselyne">
</head>
<body>
<?php
   error_reporting(E_ALL);

   /* Autorise l'exécution infinie du script, en attente de connexion. */
   set_time_limit(0);

   /* Active le vidage implicite des buffers de sortie, pour que nous
    * puissions voir ce que nous lisons au fur et à mesure. */
   ob_implicit_flush();

   $address = '192.168.1.101';
   $port = 8000;

   /* Crée un socket TCP/IP. */
   $socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
   if ($socket === false) {
      echo "socket_create() a echoue : raison :  " . socket_strerror(socket_last_error()) . "\n";
   }

   //echo "Essai de connexion a '$address' sur le port '$port'...";
   $result = socket_connect($socket, $address, $port);
   if ($socket === false) {
       echo "socket_connect() a échoué : raison : ($result) " . socket_strerror(socket_last_error($socket)) . "\n";
   }
   //print_r($_POST);
   if(array_key_exists('arroser', $_POST)){
      socket_write($socket, "A", 1);
   }
   if(array_key_exists('humi', $_POST)){
      socket_write($socket, "H", 1);
   }
   if(array_key_exists('temp', $_POST)){
      socket_write($socket, "T", 1);
   }

   socket_close($socket);
      
?>
<a href=index.php>Retour a l'interface</a>
</body>
</html>
