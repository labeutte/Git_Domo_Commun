<?php
  //require_once('config.php');

  $host = "localhost";
  $user = "root";
  $pass = "root";
  $bdd = "Surveillance";


  $mysqli = new mysqli($host, $user, $pass, $bdd);
  if ($mysqli->connect_errno) {
    die("&Eacute;chec lors de la connexion &agrave; la base de donn&eacute;es");
  }







?>
