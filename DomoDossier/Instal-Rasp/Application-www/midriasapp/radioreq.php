<?php
  require_once('config.php');

  $mysqli = new mysqli($host, $user, $pass, $bdd);
  if ($mysqli->connect_errno) {
    die("&Eacute;chec lors de la connexion &agrave; la base de donn&eacute;es");
  }


//requête vers la table PERSONNE ajoute une nouvelle personne a la bdd
   if($_POST['submit']=="Nouveau"){
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
      }
      else
      {
         // si la requête a échoué
         echo "Erreur lors de la requête";
      }
      $resultat->close();

}


//requête vers la table OPERATEUR, créer un compte d'utilisateur dans la bdd

  if($_POST['submit']=="Creer"){
      $login=$_POST['login'];
      $mdpasse=$_POST['pass'];
      $idPers=$_POST['idpers'];
      $req = "INSERT INTO OPERATEUR VALUES ('NULL','".$login."','".$mdpasse."','".$idPers."')";

//validation de la requête
      $resultat = $mysqli->query($req);

      if ($resultat)
      {
        // si la requête a fonctionné
        echo "Requête validée";
      }
      else
      {
         // si la requête a échoué
        echo "Erreur lors de la requête";
      }
      $resultat->close();

   }


//affiche le contenu de la table PERSONNE et la table OPERATEUR dans un tableau
   if($_POST['submit']=="Afficher"){

      // Creer la connexion
      $conn = new mysqli($host, $user, $pass, $bdd);
       //Vérifie la connexion

       //table PERSONNE
      if ($conn->connect_errno) {
          die("Erreur de connexion: " . $conn->connect_errno);
      }

      $sql = "SELECT IdPers, Nom, Prenom, Tel, Mail, Groupe FROM PERSONNE";
      $result = $mysqli->query($sql);


      if ($result->num_rows > 0) {
         echo "<table><tr><th>IdPers</th><th>Nom</th><th>Prenom</th><th>Tel</th></tr>";
         //Donnée de la base de donnée de chaques colonnes
      while($row = $result->fetch_assoc()) {
         echo "<tr><td>".$row["IdPers"]."</td><td>".$row["Nom"]."</td><td>".$row["Prenom"]."</td><td>".$row["Tel"]."</td></tr>";
      }
      echo "</table>";
      }
      else {
          echo "Erreur lors de la requête";
      }


      //table OPERATEUR
      if ($conn->connect_errno) {
          die("Erreur de connexion: " . $conn->connect_errno);
      }

      $sql = "SELECT IdOp, login, mdpasse, IdPers FROM OPERATEUR";
      $result = $mysqli->query($sql);

      if ($result->num_rows > 0) {
         echo "<table><tr><th>IdOp</th><th>login</th><th>Mot de passe</th><th>IdPers</th>";
          //Donnée de la base de donnée de chaques colonnes
      while($row = $result->fetch_assoc()) {
         echo "<tr><td>".$row["IdOp"]."</td><td>".$row["login"]."</td><td>".$row["mdpasse"]."</td><td>".$row["IdPers"]."</td></tr>";
      }
      echo "</table>";
      }
      else {
          echo "Erreur lors de la requête";
      }

//fin de la requête
      $mysqli->close();
}


?>
