<?php
 session_start();

if(isset($_SESSION['user']) && isset($_SESSION['pass']))
{
	unset($_SESSION['user']);
	unset($_SESSION['pass']);
}

//initialise le système de connexion

if( isset($_SESSION['ERRMSG_ARR']) && is_array($_SESSION['ERRMSG_ARR']) && count($_SESSION['ERRMSG_ARR']) >0 ) {
	echo '<ul style="padding:0; color:red;">';
	foreach($_SESSION['ERRMSG_ARR'] as $msg) {
		echo '<li>',$msg,'</li>';
	}
	echo '</ul>';
	unset($_SESSION['ERRMSG_ARR']);
}
?>

<!DOCTYPE html>

  <html>
  <link rel="icon" href="images/tab-icon.png"/>
  <link rel="stylesheet" href="index.css">
  <meta charset="utf-8">
  <html lang="fr">

  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="Library/bootstrap.min.css">
  <script src="Library/jquery.min.js"></script>
  <script src="Library/bootstrap.min.js"></script>

    <head>
        <title>Connexion</title>
    </head>
    <style>
    .login
      {

      }
    </style>

    <script type="text/javascript">

    </script>


      <body>
        <form action="login.php" method="post">
          <div class="imgcontainer">
            <img src="images/Avatar" alt="Avatar" class="avatar">
          </div>

          <div class="container">
            <label><b>Username</b></label>
            <input type="text" placeholder="Entrez le nom d'utilisateur" name="uname" required>

            <label><b>Password</b></label>
            <input type="password" placeholder="Entrez le mot de passe" name="psw" required>

            <button class="login" type="submit" name="submit" value="login">Login</button>

          </div>

          <div class="container" style="background-color:#f1f1f1">
            <button type="button" class="cancelbtn">Cancel</button>
          </div>
        </form>



      </body>
  </html>
