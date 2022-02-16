<?php

  require_once('config.php');

  $mysqli = new mysqli($host, $user, $pass, $bdd);
  if ($mysqli->connect_errno)
  {
    die("&Eacute;chec lors de la connexion &agrave; la base de donn&eacute;es");
  }


//CREER UN CONTACT (PERSONNE)
   if(isset($_POST['submit']) && $_POST['submit']=="Valider")
   {
      $Nom=$_POST['nom'];
      $Groupe=$_POST['groupe'];
      $Tel=$_POST['num'];
      $Prenom=$_POST['prenom'];
      $Mail=$_POST['mail'];
      $req = "INSERT INTO PERSONNE VALUES ('NULL','".$Nom."','".$Prenom."','".$Tel."','".$Mail."','".$Groupe."')";

//validation de la requête
      $resultat = $mysqli->query($req);

      if ($resultat)
      {
         // si la requête a fonctionné
         echo "Requête validée";
         header('Location: compte.php');
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


//CREER UN COMPTE (OPERATEUR)

  if(isset($_POST['submit']) && $_POST['submit']=="creer")
  {
      $login=$_POST['login'];
      $mdpasse=$_POST['pass'];
      $idPers=$_POST['IdPers'];
      $req = "INSERT INTO OPERATEUR VALUES ('NULL','".$login."','".$mdpasse."','".$idPers."')";

//validation de la requête
      $resultat = $mysqli->query($req);

      if ($resultat)
      {
         // si la requête a fonctionné
         echo "Requête validée";
         header('Location: compte.php');
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


   //SUPRESSION D'UN COMTACT (DELETE PERSONNE)

   if(isset($_POST['submit']) && $_POST['submit']=="Supprimer")
   {
      $Nom=$_POST['Nom'];
      $req = "DELETE FROM OPERATEUR WHERE IdPers in ( SELECT IdPers FROM PERSONNE where Nom='".$Nom."');";
      $req2 = "DELETE FROM PERSONNE WHERE Nom='".$Nom."';";

      $resultat = $mysqli->query($req);
      $resultat2 = $mysqli->query($req2);
      
      if ($resultat && $resultat2)
      {
         // si la requête a fonctionné
         echo "Requête validée";
         header('Location: compte.php');
         $resultat->close();
         $resultat2->close();
         $mysqli->close();
         exit;
      }
      else
      {
         // si la requête a échoué
         echo "Erreur lors de la requête";
      }
   }

//FIN

?>
