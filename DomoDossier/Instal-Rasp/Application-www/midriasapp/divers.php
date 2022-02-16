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
	<title>Divers</title>
<link rel="icon" href="images\tab-icon.png"/>
    <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>

<h3>Paramétrages divers</h3><a href="../board.php"><button type="button">Menu principal</button></a>

<fieldset>
  <legend> Etat du systeme </legend>
    <form action="diversreq.php" method="post">
			<?php
				$reponse = $mysqli->query('SELECT * FROM INFO');
				while ($donnees = $reponse->fetch_assoc())
				{
					if ($donnees['state']=="1") {
						echo "Systeme en marche</br>";
					}
					else {
						echo "Systeme à l'arret</br>";
					}
				}

			?>
			<input type="submit" name="submit" value="Allumer">
			<input type="submit" name="submit" value="Eteindre">
		</br>
			<?php
				$reponse = $mysqli->query('SELECT * FROM CAPTEUR WHERE Type="Temperature"');
				while ($donnees = $reponse->fetch_assoc())
				{
					echo $donnees['Nom']." : ".$donnees['Valeur']."°C</br>";
				}

			?>
    </form>
</fieldset>

<fieldset>
  <legend> Numéro de téléphone </legend>
    <form action="diversreq.php" method="post">
			<input name="NoTel3G"/>
			<input type="submit" name="submit" value="Enregistrer le numéro" id="NoTel3G">
    </form>
</fieldset>

<fieldset>
  <legend> Code PIN </legend>
    <form action="diversreq.php" method="post">
			<input name="Pin"/>
			<input type="submit" name="submit" value="Enregistrer le Pin" id="Pin">
    </form>
</fieldset>

<fieldset>
  <legend> SSID Wifi </legend>
	<form action="diversreq.php" method="post">
		<input name="WiFiSSID"/>
		<input type="submit" name="submit" value="Enregistrer le SSID" id="WiFiSSID">
	</form>
</fieldset>

<fieldset>
	<legend> Mot de passe Wifi </legend>
	<form action="diversreq.php" method="post">
		<input name="WiFiMdP"/>
		<input type="submit" name="submit" value="Enregistrer le mdp wifi" id="WiFiMdP">
	</form>
</fieldset>

<fieldset>
  <legend> Mot de passe SMS </legend>
	<form action="diversreq.php" method="post">
		<input name="pwd"/>
		<input type="submit" name="submit" value="Enregistrer le mdp SMS" id="pwd">
	</form>
</fieldset>

</body>
</html>
