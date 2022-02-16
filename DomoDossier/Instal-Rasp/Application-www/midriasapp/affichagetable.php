if ($_POSt['submit']=="Afficher"){

   $link = mysql_connect ($host,$user,$pass) or die ('Erreur : '.mysql_error() );

   mysql_select_db($bdd) or die ('Erreur :'.mysql_error());

   $select = 'SELECT IdPers,Nom,Prenom,Tel,Mail,Groupe FROM PERSONNE';

   $result = mysql_query($select,$link) or die ('Erreur : '.mysql_error() );

   $total = mysql_num_rows($result);

   if($total) {

    // debut du tableau

    echo '<table bgcolor="#FFFFFF">'."\n";

        // première ligne on affiche les titres prénom et surnom dans 2 colonnes

        echo '<tr>';

        echo '<td bgcolor="#669999"><b><u>IdPers</u></b></td>';

        echo '<td bgcolor="#669999"><b><u>Nom</u></b></td>';

      echo '<td bgcolor="#669999"><b><u>Prenom</u></b></td>';

        echo '<td bgcolor="#669999"><b><u>Tel</u></b></td>';

      echo '<td bgcolor="#669999"><b><u>Mail</u></b></td>' ;

      echo '<td bgcolor="#669999"><b><u>Groupe</u></b></td>' ;

      echo '</tr>'."\n";

    // lecture et affichage des résultats sur 2 colonnes, 1 résultat par ligne.

    while($row = mysql_fetch_array($result)) {

        echo '<tr>';

        echo '<td bgcolor="#CCCCCC">'.$row["IdPers"].'</td>';

        echo '<td bgcolor="#CCCCCC">'.$row["Nom"].'</td>';

      echo '<td bgcolor="#CCCCCC">'.$row["Prenom"].'</td>';

        echo '<td bgcolor="#CCCCCC">'.$row["Tel"].'</td>';

      echo '<td bgcolor="#CCCCCC">'.$row["Mail"].'</td>';

      echo '<td bgcolor="#CCCCCC">'.$row["Groupe"].'</td>';

      echo '</tr>'."\n";

    }

    echo '</table>'."\n";

   }

   else echo 'Pas d\'enregistrements dans cette table...';


   // on libère le résultat

   mysql_free_result($result);

}
