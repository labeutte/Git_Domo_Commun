<!DOCTYPE html>
<html lang="fr">
<meta charset="utf-8">
<head>

<title>Midrias</title>
  <link rel="icon" href="images\tab-icon.png"/>

  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="Library/bootstrap.min.css">
  <script src="Library/jquery.min.js"></script>
  <script src="Library/bootstrap.min.js"></script>
<body>


   <h3>Client capteurs</h3><a href="../board.php"><button type="button">Menu principal</button></a>
   <div>
   <fieldset>
      <legend>  </legend>
         <form action="comptereq.php" method="POST">
            <p>
              Type :
             <input type="value" name="nom" id="value" value=""/>
            </p>
            <p>
               Nom :
               <input type="text" name="prenom" id="nom" size="20" value=""/>
            </p>
            <p>
              Code :
             <input type="number" name="groupe" id="code" size="1" value=""/>
            </p>
            <p>
               Valeur :
               <input type="text" name="num" id="valeur" size="10" value=""/>
            </p>
            <p>
              Alerte :
             <input type="text" name="mail" id="alerte" size="25" value=""/>
            </p>
          <input type="submit" name="submit" value="Ajouter"><br><br>
       </form>
   </fieldset>


</body>
</html>
