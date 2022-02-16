<?php
	session_start();

	require_once("config.php");

		$mysqli = new mysqli($host, $user, $pass, $bdd);
		if ($mysqli->connect_errno)
		{
			echo $mysqli->connect_error;
		}
?>

<!DOCTYPE html>
<html lang="fr">
<head>
	<title>Cameras</title>
<link rel="icon" href="images\tab-icon.png"/>

    <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>

<h3>Parametrage des cameras</h3><a href="../board.php"><button type="button">Menu principal</button></a>



<fieldset>
  <legend> Modifier parametres </legend>
    <form action="camreq.php" method="post">
			<p>
				Sélectionnez une caméra à parametrer:
				<select type="text" name="Nom">
      		<optgroup label="Nom">
		        <?php
							$reponse = $mysqli->query('SELECT * FROM CAMERA');
		          while ($donnees = $reponse->fetch_assoc())
		          {
							//echo $donnees['Nom'];
		            echo'<option>'.$donnees['Nom'].'</option>';
		          }
		        ?>
    			</optgroup>
				</select>
			</p>
			<p>
				Intérieur ou extérieur:
				<select type="text" name="Int_Ext">
      		<optgroup label="Interieur/exterieur">
		        <option>INT</option>
						<option>EXT</option>
    			</optgroup>
				</select>
			</p>
			<p>
				Position géographique:
				<input type="text" name="PosGeo">
			</p>
			<p>
				Résolution (pixels) :
					<input name="HautPX" id="HautPX"/>
					x
					<input name="LargPX" id="LargPX"/>
			</p>
			<p>
				IP:
				<input type="text" name="IP">
			</p>
			<p>
				Type d'alerte:
				<select type="text" name="TypeAlert">
      		<optgroup>
		        <option>FTP</option>
						<option>RTSP</option>
    			</optgroup>
				</select>
			</p>
			<p>
				Nombre de pixels d'alerte:
				<input type="text" name="NbPixAlert">
			</p>
			<p>
				RepAlert:
				<input name="RepAlert">
			</p>
			<p>
				Adresse RTSP:
				<input name="AdRTSP">
			</p>
			<p>
				ID:
				<input name="ID">
			</p>
			<input type="submit" name="submit" value="Enregistrer">
    </form>
</fieldset>

<fieldset>
  <legend> Ajouter une caméra </legend>
    <form action="camreq.php" method="post">
			<p>
				Nom:
				<input name="Nom">
			</p>
			<p>
				Intérieur ou extérieur:
				<select type="text" name="Int_Ext">
      		<optgroup label="Interieur/exterieur">
		        <option>INT</option>
						<option>EXT</option>
    			</optgroup>
				</select>
			</p>
			<p>
				Position géographique:
				<input type="text" name="PosGeo">
			</p>
			<p>
				Résolution (pixels) :
					<input name="HautPX" id="HautPX"/>
					x
					<input name="LargPX" id="LargPX"/>
			</p>
			<p>
				IP:
				<input type="text" name="IP">
			</p>
			<p>
				Type d'alerte:
				<select type="text" name="TypeAlert">
      		<optgroup>
		        <option>FTP</option>
						<option>RTSP</option>
    			</optgroup>
				</select>
			</p>
			<p>
				Nombre de pixels d'alerte:
				<input type="text" name="NbPixAlert">
			</p>
			<p>
				RepAlert:
				<input name="RepAlert">
			</p>
			<p>
				Adresse RTSP:
				<input name="AdRTSP">
			</p>
			<p>
				ID:
				<input name="ID">
			</p>
			<input type="submit" name="submit" value="Ajouter">
    </form>

</fieldset>


<fieldset>
  <legend> Supprimer une caméra </legend>
    <form action="camreq.php" method="post">
			<p>
				Sélectionnez une caméra à supprimer:
				<select type="text" name="Nom">
      		<optgroup label="Nom">
		        <?php
						$reponse2 = $mysqli->query('SELECT * FROM CAMERA');
		          while ($donnees = $reponse2->fetch_assoc())
		          {
							//echo $donnees['Nom'];
		            echo'<option>'.$donnees['Nom'].'</option>';
		          }
		          $reponse2->free();
		        ?>
    			</optgroup>
				</select>
			</p>
			<input type="submit" name="submit" value="Supprimer">
    </form>
</fieldset>

</body>
</html>
