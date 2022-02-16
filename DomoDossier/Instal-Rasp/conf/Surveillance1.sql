-- phpMyAdmin SQL Dump
-- version 4.6.6deb4
-- https://www.phpmyadmin.net/
--
-- Client :  localhost:3306
-- Généré le :  Mar 06 Mars 2018 à 22:05
-- Version du serveur :  10.1.23-MariaDB-9+deb9u1
-- Version de PHP :  7.0.19-1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données :  `Surveillance`
--

-- --------------------------------------------------------

--
-- Structure de la table `ALERTE`
--

CREATE TABLE `ALERTE` (
  `IdAlert` int(11) NOT NULL,
  `DateH` char(150) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `IdCapt` int(11) DEFAULT NULL,
  `IdCam` int(11) DEFAULT NULL,
  `description` text CHARACTER SET utf8 COLLATE utf8_bin,
  `DateAlerte` date DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `ALERTE`
--

INSERT INTO `ALERTE` (`IdAlert`, `DateH`, `IdCapt`, `IdCam`, `description`, `DateAlerte`) VALUES
(1, 'Mon Mar  5 15:56:55 2018\n', 7, NULL, NULL, '2018-03-05');

-- --------------------------------------------------------

--
-- Structure de la table `CAMERA`
--

CREATE TABLE `CAMERA` (
  `IdCam` int(11) NOT NULL,
  `Nom` char(20) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `NomRep` char(20) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `Int_Ext` enum('EXT','INT') CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `PosGeo` char(30) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `HautPX` int(11) NOT NULL,
  `LargPX` int(11) NOT NULL,
  `IP` char(15) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `TypeAlert` enum('FTP','RTSP') CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `NbPixAlert` int(11) DEFAULT NULL,
  `RepAlert` char(50) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `AdRTSP` char(50) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `ID` char(100) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `CAMERA`
--

INSERT INTO `CAMERA` (`IdCam`, `Nom`, `NomRep`, `Int_Ext`, `PosGeo`, `HautPX`, `LargPX`, `IP`, `TypeAlert`, `NbPixAlert`, `RepAlert`, `AdRTSP`, `ID`) VALUES
(1, 'SZSino5', 'SzSino_5', 'EXT', 'pos5', 720, 1280, '192.168.2.5', 'FTP', NULL, NULL, 'rtsp://192.168.2.5/11', 'WXH-121433-DFEAA'),
(2, 'SZSino50N', 'SzSino_50', 'EXT', 'pos50', 720, 1280, '192.168.2.50', 'FTP', NULL, NULL, NULL, ''),
(3, 'SZSino7', 'SzSino_7', 'EXT', 'pos7', 1280, 768, '192.168.2.7', 'RTSP', NULL, NULL, NULL, ''),
(4, 'CAM10', 'Gad_10', 'EXT', 'pos10', 720, 1280, '192.168.2.10', 'RTSP', NULL, NULL, NULL, ''),
(5, 'SzSino_8', 'SzSino_8', 'EXT', 'Labo', 1024, 768, '192.16.2.8', 'FTP', NULL, NULL, NULL, '');

-- --------------------------------------------------------

--
-- Structure de la table `CAPTEUR`
--

CREATE TABLE `CAPTEUR` (
  `IdCapt` int(11) NOT NULL,
  `Type` char(20) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT 'Température',
  `Nom` char(30) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `PosGeo` char(60) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `Code` int(11) NOT NULL,
  `Valeur` float DEFAULT NULL,
  `alert` float DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `CAPTEUR`
--

INSERT INTO `CAPTEUR` (`IdCapt`, `Type`, `Nom`, `PosGeo`, `Code`, `Valeur`, `alert`) VALUES
(0, 'Inconnu', 'Element inconnu', NULL, 0, NULL, NULL),
(1, 'Temperature', 'Capt temperature 1', NULL, 21, 18.4, 5),
(2, 'Ouverture', 'Ouverture PF Salle', NULL, 4674901, NULL, NULL),
(3, 'ouverture', 'capteur ouverture 2', NULL, 5526869, NULL, NULL),
(4, 'Mouvement', 'capteur mouvement 1', NULL, 7689557, NULL, NULL),
(5, 'ouverture', 'capteur ouverture 1', NULL, 5330261, NULL, NULL),
(6, 'Mouvement', 'Capteur de mouvement 2', NULL, 4541765, NULL, NULL),
(7, 'Mouvement', 'Capteur de mouvement 3', NULL, 5592437, NULL, NULL),
(8, 'Mouvement', 'Capteur  ouverture porte 2', NULL, 13631487, NULL, NULL),
(9, 'Mouvement', 'Capteur  mouvement 4', NULL, 12770345, NULL, NULL),
(10, 'Temperature', 'Capt temperature 2', NULL, 22, 22.3, 5);

-- --------------------------------------------------------

--
-- Structure de la table `IMAGE`
--

CREATE TABLE `IMAGE` (
  `idImage` int(11) NOT NULL,
  `nomImage` char(254) COLLATE utf8_bin DEFAULT NULL,
  `dateIm` datetime DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- Contenu de la table `IMAGE`
--

INSERT INTO `IMAGE` (`idImage`, `nomImage`, `dateIm`) VALUES
(0, NULL, NULL),
(1, 'A18030222224910.jpg', '2018-03-02 22:22:51'),
(2, 'A18030222281210.jpg', '2018-03-02 22:28:16'),
(3, 'A18030222341510.jpg', '2018-03-02 22:34:18'),
(4, 'A18030222433510.jpg', '2018-03-02 22:43:37'),
(5, 'A18030222501410.jpg', '2018-03-02 22:50:16'),
(6, 'toto.jpg', '2018-03-02 22:54:38'),
(7, 'A18030222595510.jpg', '2018-03-02 22:59:58'),
(8, 'A18030223031210.jpg', '2018-03-02 23:03:16'),
(9, 'A18030214530010.jpg', '2018-03-02 14:53:02'),
(10, 'A18030222042310.jpg', '2018-03-02 22:04:25'),
(11, 'A18030222161410.jpg', '2018-03-02 22:16:16'),
(12, '8', NULL),
(13, NULL, NULL),
(14, NULL, NULL),
(15, NULL, NULL),
(16, NULL, NULL),
(17, NULL, NULL),
(18, NULL, NULL),
(19, NULL, NULL),
(20, NULL, NULL);

-- --------------------------------------------------------

--
-- Structure de la table `INFO`
--

CREATE TABLE `INFO` (
  `IdInfo` int(11) NOT NULL,
  `NoTel3G` char(13) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `Pin` char(6) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `WiFiSSID` char(30) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `WiFiMdP` char(10) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `pwd` text CHARACTER SET utf8 COLLATE utf8_bin,
  `state` int(11) DEFAULT NULL,
  `pwdSMS` char(10) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `ftpAdr` varchar(50) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `ftpLogin` varchar(30) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `ftpMdp` varchar(30) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `INFO`
--

INSERT INTO `INFO` (`IdInfo`, `NoTel3G`, `Pin`, `WiFiSSID`, `WiFiMdP`, `pwd`, `state`, `pwdSMS`, `ftpAdr`, `ftpLogin`, `ftpMdp`) VALUES
(1, '0769101655', NULL, 'LaBeutte', 'labeutte71', 'test', 1, '3456', 'ftp://perso-ftp.orange.fr/images/', 'gillesaucaigne@orange.fr', 'gilles21');

-- --------------------------------------------------------

--
-- Structure de la table `OPERATEUR`
--

CREATE TABLE `OPERATEUR` (
  `IdOp` int(11) NOT NULL,
  `login` char(20) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `mdpasse` char(30) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `IdPers` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `OPERATEUR`
--

INSERT INTO `OPERATEUR` (`IdOp`, `login`, `mdpasse`, `IdPers`) VALUES
(1, 'admin', 'admin', 3);

-- --------------------------------------------------------

--
-- Structure de la table `PERSONNE`
--

CREATE TABLE `PERSONNE` (
  `IdPers` int(11) NOT NULL,
  `Nom` char(30) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `Prenom` char(30) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `Tel` char(13) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `Mail` char(60) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `Groupe` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `PERSONNE`
--

INSERT INTO `PERSONNE` (`IdPers`, `Nom`, `Prenom`, `Tel`, `Mail`, `Groupe`) VALUES
(1, 'Aucaigne', 'Gilles', '+33651980787', 'gillesaucaigne@orange.fr', 1),
(3, 'Desvalois', 'Nicolas', '+33615173377', 'gillesaucaigne@orange.fr', 2);

--
-- Index pour les tables exportées
--

--
-- Index pour la table `ALERTE`
--
ALTER TABLE `ALERTE`
  ADD PRIMARY KEY (`IdAlert`),
  ADD UNIQUE KEY `ID_Alerte_IND` (`IdAlert`),
  ADD KEY `FKCap_Declenche` (`IdCapt`),
  ADD KEY `FKCam_Declenche` (`IdCam`);

--
-- Index pour la table `CAMERA`
--
ALTER TABLE `CAMERA`
  ADD PRIMARY KEY (`IdCam`);

--
-- Index pour la table `CAPTEUR`
--
ALTER TABLE `CAPTEUR`
  ADD PRIMARY KEY (`IdCapt`);

--
-- Index pour la table `IMAGE`
--
ALTER TABLE `IMAGE`
  ADD PRIMARY KEY (`idImage`);

--
-- Index pour la table `INFO`
--
ALTER TABLE `INFO`
  ADD PRIMARY KEY (`IdInfo`);

--
-- Index pour la table `OPERATEUR`
--
ALTER TABLE `OPERATEUR`
  ADD PRIMARY KEY (`IdOp`),
  ADD KEY `FKInclue` (`IdPers`);

--
-- Index pour la table `PERSONNE`
--
ALTER TABLE `PERSONNE`
  ADD PRIMARY KEY (`IdPers`);

--
-- AUTO_INCREMENT pour les tables exportées
--

--
-- AUTO_INCREMENT pour la table `ALERTE`
--
ALTER TABLE `ALERTE`
  MODIFY `IdAlert` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=322;
--
-- AUTO_INCREMENT pour la table `CAMERA`
--
ALTER TABLE `CAMERA`
  MODIFY `IdCam` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;
--
-- AUTO_INCREMENT pour la table `CAPTEUR`
--
ALTER TABLE `CAPTEUR`
  MODIFY `IdCapt` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;
--
-- AUTO_INCREMENT pour la table `INFO`
--
ALTER TABLE `INFO`
  MODIFY `IdInfo` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT pour la table `OPERATEUR`
--
ALTER TABLE `OPERATEUR`
  MODIFY `IdOp` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT pour la table `PERSONNE`
--
ALTER TABLE `PERSONNE`
  MODIFY `IdPers` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
--
-- Contraintes pour les tables exportées
--

--
-- Contraintes pour la table `ALERTE`
--
ALTER TABLE `ALERTE`
  ADD CONSTRAINT `FKCam_Declenche` FOREIGN KEY (`IdCam`) REFERENCES `CAMERA` (`IdCam`),
  ADD CONSTRAINT `FKCap_Declenche` FOREIGN KEY (`IdCapt`) REFERENCES `CAPTEUR` (`IdCapt`);

--
-- Contraintes pour la table `OPERATEUR`
--
ALTER TABLE `OPERATEUR`
  ADD CONSTRAINT `FKInclue` FOREIGN KEY (`IdPers`) REFERENCES `PERSONNE` (`IdPers`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
