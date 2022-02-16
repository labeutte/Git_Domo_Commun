<?php
session_start();
$errmsg_arr = array();
$errflag = false;

require_once('conflog.php');

$dsn="mysql:dbname=$dbname;host=$dbhost";
// connexion a la base de donnée
$conn = new PDO($dsn,$dbuser,$dbpass);

// new data

$user = $_POST['uname'];
$password = $_POST['psw'];




// requête vers la table OPERATEUR
$result = "SELECT * FROM OPERATEUR WHERE login=? AND mdpasse=?";

$stmt = $conn->prepare($result);

$stmt->execute(array($password,$user));

$rows = $stmt->rowCount();
echo $rows;



if($rows > 0)
{
   $_SESSION['user']=$user;
   $_SESSION['pass']=$password;
   header("location: board.php");
   exit();
}
else
{
	$errmsg_arr[] = 'Utilisateur ou mot de passe inexistant';
   $_SESSION['ERRMSG_ARR'] = $errmsg_arr;
	session_write_close();
	header("location: index.php");
	exit();
}
?>
