<?php
  require_once('config.php');

  $mysqli = new mysqli($host, $user, $pass, $bdd);
  if ($mysqli->connect_errno) {
    die("&Eacute;chec lors de la connexion &agrave; la base de donn&eacute;es");
  }


   if($_POST['submit']=="Enregistrer le mdp SMS"){
     $req= "UPDATE INFO Set pwd='".$_POST['pwd']."' WHERE IdInfo=1;";
    }

    if($_POST['submit']=="Enregistrer le mdp wifi"){
      $req= "UPDATE INFO Set WiFiMdP='".$_POST['WiFiMdP']."' WHERE IdInfo=1;";
     }

     if($_POST['submit']=="Enregistrer le SSID"){
       $req= "UPDATE INFO Set WiFiSSID='".$_POST['WiFiSSID']."' WHERE IdInfo=1;";
      }

      if($_POST['submit']=="Enregistrer le numéro"){
        $req= "UPDATE INFO Set Pin='".$_POST['Pin']."' WHERE IdInfo=1;";
       }


       if($_POST['submit']=="Enregistrer le numéro"){
         $req= "UPDATE INFO Set NoTel3G='".$_POST['NoTel3G']."' WHERE IdInfo=1;";
        }

        if($_POST['submit']=="Allumer"){
          $req= "UPDATE INFO Set state=1 WHERE IdInfo=1;";
        }

        if($_POST['submit']=="Eteindre"){
          $req= "UPDATE INFO Set state=0 WHERE IdInfo=1;";
        }


//validation de la requête
      $resultat = $mysqli->query($req);

      if ($resultat)
      {
         // si la requête a fonctionné
         header("location: divers.php");
         exit();
      }
      else
      {
         // si la requête a échoué
         echo "Erreur lors de la requête";
      }
?>
