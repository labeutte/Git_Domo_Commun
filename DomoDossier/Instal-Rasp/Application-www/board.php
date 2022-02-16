<?php
	session_start();
	if(!isset($_SESSION['user']) && !isset($_SESSION['pass']))
	{
		header("location: index.php");
		exit();
	}
?>

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


<style>
  table, th, td {
    border: 1px solid black;
  }
  h1 {
    text-align: center;
  }
  p {
    text-align: center;
  }
</style>

</head>
<body>

<div class="jumbotron text-center">
  <h1>Application midrias</h1>
  <h5>Système de paramètrage du système de surveillance</h5>
</div>


</form>

<div>
  <table style="width:15%" align="center">
    <tr>
      <th ><a href="midriasapp/gsm.php"><img src="midriasapp/Gallerie/Liste.png"</a></th>
      <th ><a href="midriasapp/cam.php"><img src="midriasapp/Gallerie/cameras.png"</a></th>
    </tr>
    <tr>
      <th ><a href="midriasapp/compte.php"><img src="midriasapp/Gallerie/user.png"</a></th>
      <th ><a href="midriasapp/capt.php"><img src="midriasapp/Gallerie/radio.png"</a></th>
    </tr>
    <tr>
      <th ><a href="midriasapp/divers.php"><img src="midriasapp/Gallerie/default.png"</a></th>
      <th ><a href="index.php"><img src="midriasapp/Gallerie/exit.png"/></a></th>
    </tr>
</div>

</body>
</html>
