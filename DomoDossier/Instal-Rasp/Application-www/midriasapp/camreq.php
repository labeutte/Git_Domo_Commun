<?php
  require_once('config.php');

  $mysqli = new mysqli($host, $user, $pass, $bdd);
  if ($mysqli->connect_errno) {
    die("&Eacute;chec lors de la connexion &agrave; la base de donn&eacute;es");
  }


//requête vers la table PERSONNE ajoute une nouvelle personne a la bdd
   if($_POST['submit']=="Enregistrer"){
      $Nom=$_POST['Nom'];
      $Int_Ext=$_POST['Int_Ext'];
      $PosGeo=$_POST['PosGeo'];
      $HautPX=$_POST['HautPX'];
      $LargPX=$_POST['LargPX'];
      $IP=$_POST['IP'];
      $TypeAlert=$_POST['TypeAlert'];
      $NbPixAlert=$_POST['NbPixAlert'];
      $RepAlert=$_POST['RepAlert'];
      $AdRTSP=$_POST['AdRTSP'];
      $ID=$_POST['ID'];
      $req = "UPDATE CAMERA SET Int_Ext='".$Int_Ext."', PosGeo='".$PosGeo."', HautPX='".$HautPX."', LargPX='".$LargPX."' WHERE Nom='".$Nom."';";
      echo $req;
    }

    if($_POST['submit']=="Ajouter"){
       $Nom=$_POST['Nom'];
       $Int_Ext=$_POST['Int_Ext'];
       $PosGeo=$_POST['PosGeo'];
       $HautPX=$_POST['HautPX'];
       $LargPX=$_POST['LargPX'];
       $IP=$_POST['IP'];
       $TypeAlert=$_POST['TypeAlert'];
       $NbPixAlert=$_POST['NbPixAlert'];
       $RepAlert=$_POST['RepAlert'];
       $AdRTSP=$_POST['AdRTSP'];
       $ID=$_POST['ID'];
       $req = "INSERT INTO CAMERA (`IdCam`, `Nom`, `Int_Ext`, `PosGeo`, `HautPX`, `LargPX`, `IP`, `TypeAlert`, `NbPixAlert`, `RepAlert`, `AdRTSP`, `ID`) VALUES ('', '".$Nom."', '".$Int_Ext."', '".$PosGeo."',".$HautPX.", ".$LargPX.",'".$IP."','".$TypeAlert."', ".$NbPixAlert.", '".$RepAlert."', '".$AdRTSP."', '".$ID."');";
       echo $req;
     }

     if($_POST['submit']=="Supprimer"){
        $Nom=$_POST['Nom'];

        $req = "DELETE FROM CAMERA WHERE Nom='".$Nom."';";
        echo $req;
      }



//validation de la requête
      $resultat = $mysqli->query($req);

      if ($resultat)
      {
         // si la requête a fonctionné
         header("location: cam.php");
         exit();
      }
      else
      {
         // si la requête a échoué
         echo "Erreur lors de la requête";
      }
?>
