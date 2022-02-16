<?php

session_start();
error_reporting(E_ALL);
ini_set('display_errors', 1);
require_once('comptereq.php');

?>

<!DOCTYPE html>

<html lang="fr">
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="stylesheet" href="Library/bootstrap.min.css">
	<script src="Library/jquery.min.js"></script>
	<script src="Library/bootstrap.min.js"></script>



<head>
	<title>Comptes</title>
	<link rel="icon" href="images\tab-icon.png"/>
</head>


<body>


<h3>Creation de compte et ajout de contacts</h3><a href="../board.php"><button type="button">Menu principal</button></a>


<div>
<fieldset>
   <legend> Ajouter contact </legend>
      <form action="comptereq.php" method="POST">
         <p>
           Nom :
          <input type="text" name="nom" id="nom" value=""/>
         </p>
         <p>
            Prénom :
            <input type="text" name="prenom" id="prenom" size="20" value=""/>
         </p>
         <p>
           Groupe :
          <input type="number" name="groupe" id="groupe" size="1" value=""/>
         </p>
         <p>
            Numéro Tel :
            <input type="text" name="num" id="num" size="10" value=""/>
         </p>
         <p>
           E-mail :
          <input type="text" name="mail" id="mail" size="25" value=""/>
         </p>
       <input type="submit" name="submit" value="Valider"><br><br>
    </form>
</fieldset>
</div>



<div>
<fieldset>
    <legend> Ajouter un compte</legend>
    <form action="comptereq.php" method="POST">
      <p>
          Login :
          <input type="text" name="login" id="login" value=""/>
      </p>
      <p>
          mot de passe :
          <input type="text" name="pass" id="pass" value=""/>
      </p>
		<p>
			<p title="Après création d'un contact choisir l'Id le plus grand"/>IdPers* :
			<SELECT name="IdPers" id="IdPers">
				<optgroup>
					<?php
					echo $mysqli->host_info . "\n";
					$reponse = $mysqli->query('SELECT IdPers FROM PERSONNE');
					while ($donnees = $reponse->fetch_assoc())
					{
						//echo $donnees
						echo'<option>'.$donnees['IdPers'].'</option>';
					}
					$reponse->free();
					?>
				</optgroup>
			</SELECT>
		</p>
       <input type="submit" name="submit" value="creer"><br><br>
    </form>
</fieldset>
</div>


<div>
<fieldset>
   <legend>Supprimer un compte & contact</legend>
   	<form action="comptereq.php" method="POST">
         <p>
           Nom :
           <SELECT name="Nom" id="Nom">
              <optgroup>
                 <?php

                    echo $mysqli->host_info . "\n";
                    $reponse = $mysqli->query('SELECT Nom FROM PERSONNE');
                    while ($donnees = $reponse->fetch_assoc())
                    {
                       //echo $donnees
                       echo'<option>'.$donnees['Nom'].'</option>';
                    }
                    $reponse->free();
                  ?>
              </optgroup>
           </SELECT>
         </p>
      <input type="submit" name="submit" value="Supprimer"><br><br>
   </form>
</fieldset>
</div>


</body>
</html>
