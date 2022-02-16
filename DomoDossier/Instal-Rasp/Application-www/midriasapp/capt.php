<?php

session_start();
error_reporting(E_ALL);
ini_set('display_errors', 1);
require_once('captreq.php');

?>


<!DOCTYPE html>
<html lang="fr">
   <meta charset="utf-8">
   <meta name="viewport" content="width=device-width, initial-scale=1">
   <link rel="stylesheet" href="Library/bootstrap.min.css">
   <script src="Library/jquery.min.js"></script>
   <script src="Library/bootstrap.min.js"></script>

<head>
   <title>Capteurs</title>
	<link rel="icon" href="images\tab-icon.png"/>
</head>


<body>


<h3>Ajouter un capteur a la base de donnée</h3><a href="../board.php"><button type="button">Menu principal</button></a>








<div>
<fieldset>
   <legend> Nouveau capteur </legend>
      <form action="captreq.php" method="POST">
         <p>
            Type :
            <SELECT name="Type" id="Type" size="1">
               <OPTION>Température</option>
               <OPTION>Ouverture</option>
               <OPTION>Mouvement</option>
            </SELECT>
         </p>
         <p>
           Nom :
          <input type="text" name="Nom" id="Nom" size="25" value=""/>
         </p>
         <p>
            Code :
            <input type="number" name="Code" id="Code" size="10" value=""/>
         </p>
         <p>
           Valeur :
            <input type="text" name="Valeur" id="Valeur" size="25" value=""/>
         </p>
            Alerte :
            <input type="text" name="alert" id="alert" size="25" value=""/>
         </p>
       <input type="submit" name="submit" value="Valider"><br><br>
    </form>
</fieldset>
</div>




<div>
   <fieldset>
         <legend>Modifier un Capteur</legend>
         <form action="captreq.php" method="POST">
            <p>
               IdCapt :
              <SELECT name="IdCapt" id="IdCapt">
                 <optgroup>
                    <?php

                       echo $mysqli->host_info . "\n";
                       $reponse = $mysqli->query('SELECT IdCapt FROM CAPTEUR');
                       while ($donnees = $reponse->fetch_assoc())
                       {
                          //echo $donnees
                          echo'<option>'.$donnees['IdCapt'].'</option>';
                       }
                       $reponse->free();
                     ?>
                 </optgroup>
              </SELECT>
            </p>
            <p>
               Type :
               <SELECT name="Type" id="Type" size="1">
                  <OPTION>Température</option>
                  <OPTION>Ouverture</option>
                  <OPTION>Mouvement</option>
               </SELECT>
            </p>
            <p>
              Nom :
              <SELECT name="Nom" id="Nom">
                 <optgroup>
                    <?php

                       echo $mysqli->host_info . "\n";
                       $reponse = $mysqli->query('SELECT Nom FROM CAPTEUR');
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
            <p>
               Code :
               <input type="number" name="Code" id="Code" size="10" value=""/>
            </p>
            <p>
              Valeur :
               <input type="text" name="Valeur" id="Valeur" size="25" value=""/>
            </p>
            <p>
               Alerte :
               <input type="text" name="alert" id="alert" size="25" value=""/>
            </p>
          <input type="submit" name="submit" value="Modifier"><br><br>
       </form>
   </fieldset>
</div>



<div>
   <fieldset>
      <legend>Supprimer un Capteur</legend>
      <form action="captreq.php" method="POST">
         <p>
           Nom :
           <SELECT name="Nom" id="Nom">
              <optgroup>
                 <?php

                    echo $mysqli->host_info . "\n";
                    $reponse = $mysqli->query('SELECT Nom FROM CAPTEUR');
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
