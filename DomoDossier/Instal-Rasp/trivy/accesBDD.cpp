#include <sstream>
#include "accesBDD.h"

using namespace std;

/**
 * Constructeur/Destructeur
 */
accesBDD::accesBDD() {
    ifstream fichier("/home/pi/trivy/confBDD.txt");
    string donnees[5];
    string ligne;
    int i = 0;

    if (fichier) {
        getline(fichier, ligne);
    }

    istringstream iss(ligne);
    string token;
    while (getline(iss, token, '@')) {
        donnees[i] = token;
        i++;
    }
    //mysql=new MYSQL();
    host = donnees[0];
    dbname = donnees[1];
    login = donnees[2];
    pwd = donnees[3];
    cout<< "BDD="<<host<<" "<<login<<"  "<<pwd<<endl;
}

accesBDD::~accesBDD() {
}

/**
 *
 */
string accesBDD::dateL() {
    const char* nomJourSem[] = {"Dim", "Lun", "Mar", "Mer", "Jeu", "Ven", "Sam"};
    const char* nomMois[] = {"janv", "fev", "mar", "avr", "mai", "juin", "juil", "aout", "sept", "oct", "nov", "dec"};

    char locTime[30];
    time_t TH;
    struct tm* t;
    TH = time(NULL);
    t = localtime(&TH);
    sprintf(locTime, "%3s %02u %s %04u %02u:%02u:%02u", nomJourSem[t->tm_wday], t->tm_mday, nomMois[t->tm_mon], 1900 + t->tm_year, t->tm_hour, t->tm_min, t->tm_sec);
    return (string(locTime));
}

void accesBDD::sortErr(int nb) {
    dt = dateL();
    fprintf(stderr, "%s- Erreur BdD -%d\n", dt.c_str(), nb);
}

/**
 * 
 * @param grp
 * @return 
 */
string accesBDD::getnum(string grp) {
    MYSQL *mysql;
    string req;
    string num;
    if (grp == "1") {
        req = "SELECT Tel FROM PERSONNE WHERE Groupe=1";
    } else if (grp == "2") {
        req = "SELECT Tel FROM PERSONNE WHERE Groupe=1 OR Groupe=2";
    }

    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) //Si la connexion réussie...
        //if(mysql_real_connect(mysql,"localhost","root","root","Surveillance",0,NULL,0))
    {
        mysql_query(mysql, req.c_str());
        result = mysql_store_result(mysql);
        int numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                num += row[i];
                num += "-";
            }
        }
        mysql_free_result(result);
        mysql_close(mysql);
        return num;
    } else {
        sortErr(1);
        return ("");
    }
}

/**
 * 
 * @param id
 * @param temp
 * @return 
 */
void accesBDD::updatetemp(unsigned long id, float temp) {
    MYSQL *mysql;
    string Resultid; // string which will contain the result
    ostringstream conver; // stream used for the conversion
    conver << id; // insert the textual representation of 'Number' in the characters in the stream
    Resultid = conver.str(); // set 'Result' to the contents of the stream

    string Resulttemp; // string which will contain the result
    ostringstream convert; // stream used for the conversion
    convert << temp; // insert the textual representation of 'Number' in the characters in the stream
    Resulttemp = convert.str(); // set 'Result' to the contents of the stream

    string req = "UPDATE `CAPTEUR` SET `Valeur` =";
    req += Resulttemp;
    req += " WHERE `CAPTEUR`.`Code` = ";
    req += Resultid;

    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) //Si la connexion réussie...
    {
        mysql_query(mysql, req.c_str());
    } else {
        sortErr(2);
    }
    mysql_close(mysql);
}

/**
 * 
 * @param idcapt
 * @return 
 */
void accesBDD::alertcapt(string idcapt) {
    //INSERT INTO `ALERTE` (`IdAlert`, `DateH`, `IdType`, `IdCapt`, `IdCam`) VALUES (NULL, '2017-03-16 00:00:00', '2', '2', NULL);
    MYSQL *mysql;
    time_t now;
    char *date;
    time(&now);
    date = ctime(&now);

    string Resultdate; // string which will contain the result
    ostringstream converc; // stream used for the conversion
    converc << date; // insert the textual representation of 'Number' in the characters in the stream
    Resultdate = converc.str(); // set 'Result' to the contents of the stream

    /*string Resultid;          // string which will contain the result
    ostringstream conver;   // stream used for the conversion
    conver << idtype;      // insert the textual representation of 'Number' in the characters in the stream
    Resultid = conver.str(); // set 'Result' to the contents of the stream*/

    string Resultcode; // string which will contain the result
    ostringstream convert; // stream used for the conversion
    //convert << code;      // insert the textual representation of 'Number' in the characters in the stream
    Resultcode = convert.str(); // set 'Result' to the contents of the stream

    string req = "INSERT INTO `ALERTE` VALUES (NULL, '";
    req += Resultdate;
    req += "', '";
    req += idcapt;
    req += "', NULL, NULL, CURRENT_DATE())";
    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) //Si la connexion réussie...
    {
        mysql_query(mysql, req.c_str());
    } else {
        sortErr(3);
    }
}

string accesBDD::getidcapt(int code) {
    MYSQL *mysql;
    string Resultcode; // string which will contain the result
    ostringstream convert; // stream used for the conversion
    convert << code; // insert the textual representation of 'Number' in the characters in the stream
    Resultcode = convert.str(); // set 'Result' to the contents of the stream
    string req, num;
    string idcapt;
    req = "SELECT IdCapt FROM `CAPTEUR` WHERE Code=";
    req += Resultcode;

    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) //Si la connexion réussie...
        //if(mysql_real_connect(mysql,"localhost","root","root","Surveillance",0,NULL,0))
    {
        mysql_query(mysql, req.c_str());
        result = mysql_store_result(mysql);
        int numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                num += row[i];
            }
        }
        int nbr = result->row_count;
        mysql_free_result(result);
        mysql_close(mysql);
        if (nbr > 0)
            return num;
        else
            return ("0");
    } else {
        sortErr(4);
        return ("0");
    }
}

/**
 * 
 * @param code
 * @return 
 */
float accesBDD::gettemp(int code) {
    MYSQL *mysql;
    float temp;
    string Resultcode; // string which will contain the result
    ostringstream convert; // stream used for the conversion
    convert << code; // insert the textual representation of 'Number' in the characters in the stream
    Resultcode = convert.str(); // set 'Result' to the contents of the stream

    string req, num;
    string idcapt;
    req = "SELECT Valeur FROM `CAPTEUR` WHERE Code=";
    req += Resultcode;

    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) //Si la connexion réussie...
        //if(mysql_real_connect(mysql,"localhost","root","root","Surveillance",0,NULL,0))
    {
        mysql_query(mysql, req.c_str());
        result = mysql_store_result(mysql);
        //int totalrows = mysql_num_rows(result);
        int numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                num += row[i];
            }
        }
        mysql_free_result(result);
        mysql_close(mysql);
        temp = atof(num.c_str());
        return temp;
    } else {
        sortErr(5);
        return 0;
    }
}

/**
 * 
 * @param mdp
 * @return 
 */
bool accesBDD::testpwd(string mdp) {
    MYSQL *mysql;
    //SELECT CASE WHEN pwd="123" then 'true' ELSE 'false' END FROM INFO
    string req, pass;
    req = "SELECT CASE WHEN pwd='";
    req += mdp;
    req += "' then 'true' ELSE 'false' END FROM INFO";

    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) //Si la connexion réussie...
    {
        mysql_query(mysql, req.c_str());
        result = mysql_store_result(mysql);
        int numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                pass += row[i];
            }
        }
        mysql_free_result(result);
        mysql_close(mysql);
        if (pass == "true") {
            return 1;
        } else {
            return 0;
        }
    } else {
        sortErr(6);
        return 0;
    }
}

/**
 * 
 * @param mdp
 * @return 
 */
bool accesBDD::testpwdSMS(string mdp) {
    MYSQL *mysql;
    //SELECT CASE WHEN pwd="123" then 'true' ELSE 'false' END FROM INFO
    string req, pass;
    req = "SELECT CASE WHEN pwdSMS='";
    req += mdp;
    req += "' then 'true' ELSE 'false' END FROM INFO";

    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) //Si la connexion réussie...
    {
        mysql_query(mysql, req.c_str());
        result = mysql_store_result(mysql);
        int numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                pass += row[i];
            }
        }
        mysql_free_result(result);
        mysql_close(mysql);
        if (pass == "true") {
            return 1;
        } else {
            return 0;
        }
    } else {
        sortErr(7);
        return 0;
    }
}

/**
 * 
 * @return 
 */
int accesBDD::getstate() {
    MYSQL *mysql;
    int i;
    string req, state;
    req = "SELECT state FROM `INFO` WHERE IdInfo=1";
    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) {
        //if(mysql_real_connect(mysql,"localhost","gilles","gilles","Surveillance",0,NULL,0)) {
        mysql_query(mysql, req.c_str());
        result = mysql_store_result(mysql);
        int numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                state += row[i];
            }
        }
        mysql_free_result(result);
        mysql_close(mysql);
        i = atoi(state.c_str());
        return i;
    } else {
        dt = dateL();
        sortErr(8);
        return 0;
    }
}

/**
 * 
 * @return 
 */
int accesBDD::getcle3G() {
    MYSQL *mysql;
    int i;
    string req, state;
    req = "SELECT cle3G FROM `INFO` WHERE IdInfo=1";
    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) {
        mysql_query(mysql, req.c_str());
        result = mysql_store_result(mysql);
        int numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                state += row[i];
            }
        }
        mysql_free_result(result);
        mysql_close(mysql);
        i = atoi(state.c_str());
        return i;
    } else {
        dt = dateL();
        sortErr(80);
        return 0;
    }
}

/**
 * 
 * @param code
 * @return 
 */
float accesBDD::gettempalert(int code) {
    MYSQL *mysql;
    float temp;
    string Resultcode; // string which will contain the result
    ostringstream convert; // stream used for the conversion
    convert << code; // insert the textual representation of 'Number' in the characters in the stream
    Resultcode = convert.str(); // set 'Result' to the contents of the stream

    string req, num;
    string idcapt;
    req = "SELECT alert FROM `CAPTEUR` WHERE Code=";
    req += Resultcode;

    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) //Si la connexion réussie...
        //if(mysql_real_connect(mysql,"localhost","root","root","Surveillance",0,NULL,0))
    {
        mysql_query(mysql, req.c_str());
        result = mysql_store_result(mysql);
        int numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                num += row[i];
            }
        }
        mysql_free_result(result);
        mysql_close(mysql);
        temp = atof(num.c_str());
        return temp;
    } else {
        sortErr(9);
        return 0;
    }
}

/**
 * 
 * @param IdCam
 * @return 
 */
void accesBDD::alertcam(string IdCam) {
    MYSQL *mysql;
    time_t now;
    char *date;
    time(&now);
    date = ctime(&now);

    string Resultdate; // string which will contain the result
    ostringstream converc; // stream used for the conversion
    converc << date; // insert the textual representation of 'Number' in the characters in the stream
    Resultdate = converc.str(); // set 'Result' to the contents of the stream

    string req = "INSERT INTO `ALERTE` VALUES (NULL, '";
    req += Resultdate;
    req += "', NULL, '";
    req += IdCam;
    req += "', NULL, CURRENT_DATE())";
    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) //Si la connexion réussie...
    {
        mysql_query(mysql, req.c_str());
    } else {
        sortErr(10);
    }
}

/**
 * 
 * @param nom
 * @return 
 */
string accesBDD::getidcam(string nom) {
    MYSQL *mysql;
    string req, num;
    string idcapt;

    req = "SELECT IdCam FROM `CAMERA` WHERE NOM='";
    req += nom;
    req += "'";

    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) //Si la connexion réussie...
        //if(mysql_real_connect(mysql,"localhost","root","root","Surveillance",0,NULL,0))
    {
        mysql_query(mysql, req.c_str());
        result = mysql_store_result(mysql);
        int numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                num += row[i];
            }
        }
        int nbr = result->row_count;
        mysql_free_result(result);
        mysql_close(mysql);
        if (nbr > 0)
            return num;
        else
            return ("0");
    } else {
        sortErr(11);
    }
}

/**
 * 
 * @param newstate
 * @return 
 */
bool accesBDD::updatestate(int newstate) {
    MYSQL *mysql;
    string Resultstate; // string which will contain the result
    ostringstream convert; // stream used for the conversion
    convert << newstate; // insert the textual representation of 'Number' in the characters in the stream
    Resultstate = convert.str(); // set 'Result' to the contents of the stream

    string req = "UPDATE `INFO` SET state =";
    req += Resultstate;

    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) //Si la connexion réussie...
    {
        mysql_query(mysql, req.c_str());
    } else {
        sortErr(12);
    }
    mysql_close(mysql);
}

/**
 * 
 * @param code
 * @return 
 */
string accesBDD::getcaptname(int code) {
    MYSQL *mysql;
    string Resultcode; // string which will contain the result
    ostringstream convert; // stream used for the conversion
    convert << code; // insert the textual representation of 'Number' in the characters in the stream
    Resultcode = convert.str(); // set 'Result' to the contents of the stream

    string req, num;
    string idcapt;
    req = "SELECT Nom FROM `CAPTEUR` WHERE Code=";
    req += Resultcode;
    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) //Si la connexion réussie...
        //if(mysql_real_connect(mysql,"localhost","root","root","Surveillance",0,NULL,0))
    {
        mysql_query(mysql, req.c_str());
        result = mysql_store_result(mysql);
        int numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                num += row[i];
            }
        }
        int nbr = result->row_count;
        mysql_free_result(result);
        mysql_close(mysql);
        if (nbr > 0)
            return num;
        else
            return ("Capteur inconnu");
    } else {
        sortErr(13);
    }
}

/**
 * 
 * @return 
 */
bool accesBDD::coupure() {
    MYSQL *mysql;
    //INSERT INTO `ALERTE` (`IdAlert`, `DateH`, `IdCapt`, `IdCam`, `description`) VALUES (NULL, 'test', NULL, NULL, 'coupure');
    time_t now;
    char *date;
    time(&now);
    date = ctime(&now);

    string Resultdate; // string which will contain the result
    ostringstream converc; // stream used for the conversion
    converc << date; // insert the textual representation of 'Number' in the characters in the stream
    Resultdate = converc.str(); // set 'Result' to the contents of the stream

    string req = "INSERT INTO `ALERTE` VALUES (NULL, '";
    req += Resultdate;
    req += "', NULL, NULL, 'Coupure de courant', CURRENT_DATE());";
    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) //Si la connexion réussie...
    {
        mysql_query(mysql, req.c_str());
    } else {
        sortErr(14);
    }
}

/**
 * 
 * @return 
 */
bool accesBDD::retour() {
    MYSQL *mysql;
    //INSERT INTO `ALERTE` (`IdAlert`, `DateH`, `IdCapt`, `IdCam`, `description`) VALUES (NULL, 'test', NULL, NULL, 'coupure');
    time_t now;
    char *date;
    time(&now);
    date = ctime(&now);

    string Resultdate; // string which will contain the result
    ostringstream converc; // stream used for the conversion
    converc << date; // insert the textual representation of 'Number' in the characters in the stream
    Resultdate = converc.str(); // set 'Result' to the contents of the stream

    string req = "INSERT INTO `ALERTE` VALUES (NULL, '";
    req += Resultdate;
    req += "', NULL, NULL, 'Retour du courant', CURRENT_DATE());";

    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) //Si la connexion réussie...
    {
        mysql_query(mysql, req.c_str());
    } else {
        sortErr(15);
    }
}

string accesBDD::getNomSite() {
    MYSQL *mysql;
    string req, resultat;
    req = "SELECT nomSite FROM `INFO` WHERE IdInfo=1";

    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) //Si la connexion réussie...
        //if(mysql_real_connect(mysql,"localhost","root","root","Surveillance",0,NULL,0))
    {
        mysql_query(mysql, req.c_str());
        result = mysql_store_result(mysql);
        int numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                resultat += row[i];
            }
        }
        mysql_free_result(result);
        mysql_close(mysql);
        return resultat;
    } else {
        sortErr(30);
        return "";
    }
}

/**
 * 
 * @return 
 */
int accesBDD::getNbCam() {
    MYSQL *mysql;
    string req, resultat;
    req = "SELECT count(*) FROM `CAMERA`";

    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) //Si la connexion réussie...
        //if(mysql_real_connect(mysql,"localhost","root","root","Surveillance",0,NULL,0))
    {
        mysql_query(mysql, req.c_str());
        result = mysql_store_result(mysql);
        int numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                resultat += row[i];
            }
        }
        mysql_free_result(result);
        mysql_close(mysql);
        return atoi(resultat.c_str());
    } else {
        sortErr(16);
        return 0;
    }
}

/**
 * 
 * @param id
 * @return 
 */
string accesBDD::getcamRep(string id) {
    MYSQL *mysql;
    string Resultcode; // string which will contain the result
    ostringstream convert; // stream used for the conversion
    convert << id; // insert the textual representation of 'Number' in the characters in the stream
    Resultcode = convert.str(); // set 'Result' to the contents of the stream

    string req, num;
    string idcapt;
    req = "SELECT NomRep FROM `CAMERA` WHERE ID='";
    req += id;
    req += "'";

    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) //Si la connexion réussie...
        //if(mysql_real_connect(mysql,"localhost","root","root","Surveillance",0,NULL,0))
    {
        mysql_query(mysql, req.c_str());
        result = mysql_store_result(mysql);
        int totalrows = mysql_num_rows(result);
        int numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                num += row[i];
            }
        }
        int nbr = result->row_count;
        mysql_free_result(result);
        mysql_close(mysql);
        if (nbr > 0)
            return num;
        else
            return ("Camera inconnue");
    } else {
        sortErr(170);
    }
}

/**
 * 
 * @param id
 * @return 
 */
string accesBDD::getcamname(string id) {
    MYSQL *mysql;
    string Resultcode; // string which will contain the result
    ostringstream convert; // stream used for the conversion
    convert << id; // insert the textual representation of 'Number' in the characters in the stream
    Resultcode = convert.str(); // set 'Result' to the contents of the stream

    string req, num;
    string idcapt;
    req = "SELECT Nom FROM `CAMERA` WHERE ID='";
    req += id;
    req += "'";

    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) //Si la connexion réussie...
        //if(mysql_real_connect(mysql,"localhost","root","root","Surveillance",0,NULL,0))
    {
        mysql_query(mysql, req.c_str());
        result = mysql_store_result(mysql);
        int totalrows = mysql_num_rows(result);
        int numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                num += row[i];
            }
        }
        int nbr = result->row_count;
        mysql_free_result(result);
        mysql_close(mysql);
        if (nbr > 0)
            return num;
        else
            return ("Camera inconnue");
    } else {
        sortErr(171);
    }
}

/**
 * 
 * @param id
 * @return 
 */
string accesBDD::getcamGeo(string nomR) {
    MYSQL *mysql;

    string req, num;
    string nomRcapt;
    req = "SELECT PosGeo FROM `CAMERA` WHERE NomRep='";
    req += nomR;
    req += "'";

    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) //Si la connexion réussie...
        //if(mysql_real_connect(mysql,"localhost","root","root","Surveillance",0,NULL,0))
    {
        mysql_query(mysql, req.c_str());
        result = mysql_store_result(mysql);
        int totalrows = mysql_num_rows(result);
        int numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                num += row[i];
            }
        }
        int nbr = result->row_count;
        mysql_free_result(result);
        mysql_close(mysql);
        if (nbr > 0)
            return num;
        else
            return ("inconnue");
    } else {
        sortErr(173);
    }
}

/**
 * 
 * @return 
 */
string accesBDD::getftpadr() {
    MYSQL *mysql;
    string req, resultat;
    req = "SELECT ftpAdr FROM `INFO`";

    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) //Si la connexion réussie...
        //if(mysql_real_connect(mysql,"localhost","root","root","Surveillance",0,NULL,0))
    {
        mysql_query(mysql, req.c_str());
        result = mysql_store_result(mysql);
        int numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                resultat += row[i];
            }
        }
        mysql_free_result(result);
        mysql_close(mysql);
        return resultat;
    } else {
        sortErr(174);
        return "";
    }
}

/**
 * 
 * @return 
 */
string accesBDD::getftplogin() {
    MYSQL *mysql;
    string req, resultat;
    req = "SELECT ftpLogin FROM `INFO`";

    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) //Si la connexion réussie...
        //if(mysql_real_connect(mysql,"localhost","root","root","Surveillance",0,NULL,0))
    {
        mysql_query(mysql, req.c_str());
        result = mysql_store_result(mysql);
        int numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                resultat += row[i];
            }
        }
        mysql_free_result(result);
        mysql_close(mysql);
        return resultat;
    } else {
        sortErr(18);
        return "";
    }
}

/**
 * 
 * @return 
 */
string accesBDD::getftpmdp() {
    MYSQL *mysql;
    string req, resultat;
    req = "SELECT ftpMdp FROM `INFO`";

    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) //Si la connexion réussie...
        //if(mysql_real_connect(mysql,"localhost","root","root","Surveillance",0,NULL,0))
    {
        mysql_query(mysql, req.c_str());
        result = mysql_store_result(mysql);
        int numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                resultat += row[i];
            }
        }
        mysql_free_result(result);
        mysql_close(mysql);
        return resultat;
    } else {
        sortErr(19);
        return "";
    }
}

string accesBDD::getIndexImage() {
    MYSQL *mysql;
    string req, resultat;
    req = "SELECT nomImage FROM IMAGE WHERE idImage = '12'";

    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "appli");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) {
        mysql_query(mysql, req.c_str());
        result = mysql_store_result(mysql);
        int numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                resultat += row[i];
            }
        }
        mysql_free_result(result);
        mysql_close(mysql);
        return resultat;
    } else {
        sortErr(20);
        return "";
    }
}

string accesBDD::getLastImg(string numImg) {
    MYSQL *mysql;
    string req, resultat, ind;
    if (numImg == "0")
        ind = getIndexImage();
    else {
        ind = numImg;
    }
    req = "SELECT nomImage FROM IMAGE WHERE idImage = ";
    req += ind;

    //fprintf(stderr,"req= %s\n",req.c_str());
    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "appli");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) {
        mysql_query(mysql, req.c_str());
        result = mysql_store_result(mysql);
        int numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                resultat += row[i];
            }
        }
        int nbr = result->row_count;
        mysql_free_result(result);
        mysql_close(mysql);
        if (nbr > 0)
            return resultat;
        else
            return " ";
    } else {
        sortErr(21);
        return "";
    }
}

void accesBDD::incIx() {
    MYSQL *mysql;
    //On recupère et on incremente l'index de la derniere image
    // en case 12 de la table IMAGE
    string ind, req;
    ind = getIndexImage();
    int ix = atoi(ind.c_str());
    ix++;
    if (ix == 12)
        ix = 1;
    req = "UPDATE IMAGE SET nomImage = '";
    req += std::to_string(ix);
    req += "' WHERE idImage = 12";
    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "appli");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) {
        if (mysql_query(mysql, req.c_str()))
            fprintf(stderr, "Erreur bdd1: %s\n", mysql_error(mysql));
    } else {
        sortErr(22);
    }
    mysql_close(mysql);
}

void accesBDD::putLastImg(string chImg) {
    MYSQL *mysql;
    string ind, req2;
    //On incremente l'index de la derniere image
    incIx();

    usleep(100000);
    ind = getIndexImage();
    usleep(100000);
    req2 = "UPDATE IMAGE SET nomImage = '";
    req2 += chImg;
    req2 += "', dateIm = NOW() WHERE idImage = ";
    req2 += ind;
    //fprintf(stderr,"%s\nLG=%d\n", req2.c_str(), strlen(req2.c_str()));
    mysql = mysql_init(NULL);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "appli");

    if (mysql_real_connect(mysql, host.c_str(), login.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0)) {
        if (mysql_query(mysql, req2.c_str()))
            fprintf(stderr, "Erreur bdd2: %s\n", mysql_error(mysql));
    } else {
        sortErr(23);
    }
    mysql_close(mysql);
}
