                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
<?php
	session_start();

	require_once("config.php");

		$mysqli = new mysqli($host, $user, $pass, $bdd);
		if ($mysqli->connect_errno)
		{
			echo $mysqli->connect_error;
		}
?>                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 

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


  <style>
    table, th, tr {
			margin-left: 10%;
      border: 1px solid black;
      text-align: center;
			width:60%;
    }
		th{
			width:20%;
		}
    h1 {
      text-align: center;
    }
    p {
      text-align: center;
    }
	 a {
		 position: absolute;
		 right:0%;
	 }
  </style>
</head>


<body>                                                                                                                                                                                                                                                  

<a href="../board.php"><button type="button">Menu principal</button></a>
<br>
<h3>Capteurs r??pertori??s</h3>

	<button type=button id="showcapt">Montrer / Cacher Liste Capteurs</button>
	<br><br>
  <table id="capteurs">
    <tr>
      <th>Type</th>
      <th>Nom</th>
      <th>PosGeo</th>
    </tr>
                   <?php
                      $reponse = $mysqli->query('SELECT * FROM CAPTEUR');
                      while ($donnees = $reponse->fetch_assoc())
                      {
                         echo'<tr>';
                         echo'<th>'.$donnees['Type'].'</th>';
                         echo'<th>'.$donnees['Nom'].'</th>';
												 if($donnees['PosGeo']==NULL)
														echo'<th>NULL</th>';
												 else
														echo'<th>'.$donnees['PosGeo'].'</th>';
                         echo'</tr>';
                      }
                      $reponse->free();
                    ?>
    </table>

		<br><br>

		<h3>Cam??ras r??pertori??es</h3>
		<button type=button id="showcam">Montrer / Cacher Liste Cam??ras</button>
		<br><br>
		<table id="camera">
			<tr>
				<th>Nom</th>
				<th>Int_Ext</th>
				<th>PosGeo</th>
				<th>R??solution</th>
				<th>IP</th>
			</tr>
										 <?php
												$reponse = $mysqli->query('SELECT * FROM CAMERA');
												while ($donnees = $reponse->fetch_assoc())
												{
													 echo'<tr>';
													 echo'<th>'.$donnees['Nom'].'</th>';
													 echo'<th>'.$donnees['Int_Ext'].'</th>';
													 if($donnees['PosGeo']==NULL)
													 		echo'<th>NULL</th>';
													 else
													 		echo'<th>'.$donnees['PosGeo'].'</th>';
													 echo'<th>'.$donnees['HautPX']." x ".$donnees['LargPX'].'</th>';
													 echo'<th>'.$donnees['IP'].'</th>';
													 echo'</tr>';
												}
												$reponse->free();
											?>
			</table>

		<br><br>

		<h3>Log des Alertes</h3>
		<button type=button id="showal">Montrer / Cacher Liste Alertes</button>
		<br><br>
		<table id="alerte">
			<tr>
				<th>IdAlert</th>
				<th>Date</th>
				<th>Nom Capteur</th>
				<th>Nom Cam??ra</th>
				<th>Description</th>
			</tr>
										 <?php
												$reponse = $mysqli->query('SELECT * FROM ALERTE');
												while ($donnees = $reponse->fetch_assoc())
												{
													 echo'<tr>';
													 echo'<th>'.$donnees['IdAlert'].'</th>';
													 echo'<th>'.$donnees['DateH'].'</th>';
													 if($donnees['IdCapt']!=NULL)
													 {
														 $req = "SELECT Nom FROM CAPTEUR where IdCapt='".$donnees['IdCapt']."'";
														 $reponse2 = $mysqli->query($req);
														 $donnees2 = $reponse2->fetch_assoc();
														 echo'<th>'.$donnees2['Nom'].'</th>';
													 }
													 else
													 	echo'<th>NULL</th>';
													 if($donnees['IdCam']!=NULL)
													 {
														 $req = "SELECT Nom FROM CAPTEUR where IdCapt='".$donnees['IdCam']."'";
														 $reponse2 = $mysqli->query($req);
														 $donnees2 = $reponse2->fetch_assoc();
														 echo'<th>'.$donnees2['Nom'].'</th>';
													 }
													 else
													 	echo'<th>NULL</th>';
													 if($donnees['description']==NULL)
													 		echo'<th>NULL</th>';
													 else
													    echo'<th>'.$donnees['description'].'</th>';
													 echo'</tr>';
												}
												$reponse->free();
											?>
			</table>

		<script>
		var i=0,j=0,k=0,l=0;
		if(l==0)
		{
			$("#camera").hide();
			$("#capteurs").hide();
			$("#alerte").hide();
			l++;
		}


			$("#showcam").on("click",function(){
				if (i==1)
				{
					$("#camera").hide();
					i=0;
				}
				else
				{
					$("#camera").show();
					i=1;
				}
			});

			$("#showcapt").on("click",function(){
				if (j==1)
				{
					$("#capteurs").hide();
					j=0;
				}
				else
				{
					$("#capteurs").show();
					j=1;
				}
			});

			$("#showal").on("click",function(){
				if (k==1)
				{
					$("#alerte").hide();
					k=0;
				}
				else
				{
					$("#alerte").show();
					k=1;
				}
			});

		</script>
  </body>
  </html>
