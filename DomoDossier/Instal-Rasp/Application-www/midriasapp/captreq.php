<?php

   require_once('config.php');

   $mysqli = new mysqli($host, $user, $pass, $bdd);
   if ($mysqli->connect_errno)
   {
      die("&Eacute;chec lors de la connexion &agrave; la base de donn&eacute;es");
   }


//requête vers la table CAPTEUR ajoute un nouveau capteur a la bdd
   if(isset($_POST['submit']) && $_POST['submit']=="Valider")
   {
      $Type=$_POST['Type'];
      $Nom=$_POST['Nom'];
      $Code=$_POST['Code'];
      $Valeur=$_POST['Valeur'];
      $alert=$_POST['alert'];
      $req = "INSERT INTO CAPTEUR VALUES ('NULL','".$Type."','".$Nom."','NULL','".$Code."','".$Valeur."','".$alert."')";

//validation de la requête
      $resultat = $mysqli->query($req);

      if ($resultat)
      {
         // si la requête a fonctionné
         echo "Requête validée";
         header('Location: capt.php');
         $resultat->close();
         $mysqli->close();
         exit;
      }
      else
      {
         // si la requête a échoué
         echo "Erreur lors de la requête";
      }
   }

//Modifier un capteur
   if(isset($_POST['submit']) && $_POST['submit']=="Modifier")
   {
      $IdCapt=$_POST['IdCapt'];
      $Type=$_POST['Type'];
      $Nom=$_POST['Nom'];
      $Code=$_POST['Code'];
      $Valeur=$_POST['Valeur'];
      $alert=$_POST['alert'];
      $req = "UPDATE CAPTEUR VALUES ('".$IdCapt."','".$Type."','".$Nom."','NULL','".$Code."','".$Valeur."','".$alert."')";

   //validation de la requête
      $resultat = $mysqli->query($req);

      if ($resultat)
      {
         // si la requête a fonctionné
         echo "Requête validée";
         $resultat->close();
         $mysqli->close();
         header('Location: capt.php');
         exit;
      }
      else
      {
         // si la requête a échoué
         echo "Erreur lors de la requête";
      }
   }


//Suprime un capteur

   if(isset($_POST['submit']) && $_POST['submit']=="Supprimer")
   {
      $Nom=$_POST['Nom'];
      $req = "DELETE FROM CAPTEUR WHERE Nom='".$Nom."';";

      $resultat = $mysqli->query($req);

      if ($resultat)
      {
         // si la requête a fonctionné
         echo "Requête validée";
         header('Location: capt.php');
         $resultat->close();
         $mysqli->close();
         exit;
      }
      else
      {
         // si la requête a échoué
         echo "Erreur lors de la requête";
      }
   }

//fin de la requête

?>
