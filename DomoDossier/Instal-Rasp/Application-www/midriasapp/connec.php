<?php
	session_start();
?>
<!DOCTYPE html>
<html>
	<head>
		<html lang="fr">
		<meta charset="UTF-8">
        <title>Verification...</title>
        <link rel="stylesheet" type="text/css" href="style.css">
	<body>
	</body>

<?php

	$usr=$_POST['uname'];
	$pass=$_POST['psw'];

   $host = "172.20.140.40";
   $user = "root";
   $pass = "root";
   $bdd = "Surveillance";

	$link = mysqli_connect($host, $user,$pass, "" , $bdd);

	if (mysqli_connect_errno())
	{
		printf("Échec de la connexion : %s\n", mysqli_connect_error());
		exit();
	}

	if( $_SESSION["fin"] == 1 )
	{
		mysqli_query($link, $sql);
		session_unset();
		session_destroy();
		header('Location: index.php');
		exit;
	}

	$result = mysqli_query($link, $sql);
	$valeur	= mysqli_fetch_array($result,MYSQLI_ASSOC);

	mysqli_free_result($result);

?>

</html>
