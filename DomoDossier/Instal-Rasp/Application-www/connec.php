<?php
	session_start();
?>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
        <title>Verification...</title>
        <link rel="stylesheet" type="text/css" href="style.css">
	<body>
	</body>

<?php

	$nom=$_POST['nom'];
	$prenom=$_POST['prenom'];
	$classe=$_POST['classe'];

	$servername = "localhost";
	$username = "root";
	$dbname = "lampe";

	$link = mysqli_connect($servername, $username , "" , $dbname );

	if (mysqli_connect_errno())
	{
		printf("Échec de la connexion : %s\n", mysqli_connect_error());
		exit();
	}

	if( $_SESSION["fin"] == 1 )
	{
		$sql = 'UPDATE eleve SET vote=1 WHERE nom="' . $_SESSION["nom"] . '" AND prenom="' . $_SESSION["prenom"] . '"' ;
		mysqli_query($link, $sql);
		$sql = 'UPDATE eleve SET top1="' . $_SESSION["t1"] . '" , top2="' . $_SESSION["t2"] . '" , top3="' . $_SESSION["t3"] . '" , top4="' . $_SESSION["t4"] . '" , top5="' . $_SESSION["t5"] . '" WHERE nom="' . $_SESSION["nom"] . '" AND prenom="' . $_SESSION["prenom"] . '"';
		mysqli_query($link, $sql);
		session_unset();
		session_destroy();
		header('Location: merci.html');
		exit;
	}

	$sql = 'SELECT 1 FROM eleve WHERE nom="'. $nom . '" AND prenom="' . $prenom . '" AND classe="' . $classe . '"';
	$result = mysqli_query($link, $sql);

	if (mysqli_num_rows($result) <= 0)
    {
        $_SESSION["fail"]=1;
		header('Location: index.php');
		exit;
    }
	mysqli_free_result($result);

	$sql = 'SELECT vote FROM eleve WHERE nom="'. $nom . '" AND prenom="' . $prenom . '" AND classe="' . $classe . '"' ;
	$result = mysqli_query($link, $sql);
	$valeur	= mysqli_fetch_array($result,MYSQLI_ASSOC);

	mysqli_free_result($result);

	if( $valeur[vote] == 0 )
	{
		$_SESSION["nom"] = $nom;
		$_SESSION["prenom"] = $prenom;
		$_SESSION["classe"] = $classe;
		header('Location: lampe.php');
		exit;
	}
	if( $valeur[vote] == 1 )
	{
		$_SESSION["fail"]=2;
		header('Location: index.php');
		exit;
	}
?>

</html>
