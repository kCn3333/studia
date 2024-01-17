-- phpMyAdmin SQL Dump
-- version 3.4.9
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Czas wygenerowania: 15 Lut 2012, 23:33
-- Wersja serwera: 5.5.20
-- Wersja PHP: 5.3.10


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Baza danych: `taxi`
--

-- --------------------------------------------------------

--
-- Struktura tabeli dla  `dyspozytor`
--

CREATE TABLE IF NOT EXISTS `dyspozytor` (
  `idDYSPOZYTOR` int(3) NOT NULL AUTO_INCREMENT,
  `Imie` char(45) NOT NULL DEFAULT '',
  `Nazwisko` char(45) NOT NULL DEFAULT '',
  `PESEL` int(11) NOT NULL DEFAULT '0',
  `OdKiedyZatrudniony` date NOT NULL,
  `Status` enum('Aktywny','brak') NOT NULL DEFAULT 'brak',
  PRIMARY KEY (`idDYSPOZYTOR`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=5 ;

--
-- Zrzut danych tabeli `dyspozytor`
--

INSERT INTO `dyspozytor` (`idDYSPOZYTOR`, `Imie`, `Nazwisko`, `PESEL`, `OdKiedyZatrudniony`, `Status`) VALUES
(1, 'Stefan', 'Byk', 2147483647, '2010-05-20', 'Aktywny'),
(2, 'Roman', 'Krowicki', 2147483647, '2010-01-20', 'brak'),
(4, 'Mieczys³aw', 'Bolec', 2147483647, '2011-04-20', 'brak');

-- --------------------------------------------------------

--
-- Struktura tabeli dla  `firma`
--

CREATE TABLE IF NOT EXISTS `firma` (
  `idFIRMA` int(10) NOT NULL AUTO_INCREMENT,
  `Telefon` int(10) NOT NULL DEFAULT '0',
  `NazwaFirmy` char(50) COLLATE utf8_polish_ci NOT NULL DEFAULT '',
  `Adres` char(50) COLLATE utf8_polish_ci DEFAULT '',
  `NIP` int(10) NOT NULL DEFAULT '0',
  `REGON` int(9) NOT NULL DEFAULT '0',
  PRIMARY KEY (`idFIRMA`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=7 ;

--
-- Zrzut danych tabeli `firma`
--

INSERT INTO `firma` (`idFIRMA`, `Telefon`, `NazwaFirmy`, `Adres`, `NIP`, `REGON`) VALUES
(1, 500123459, 'Biedronka', 'Witosa 15, 30-611 Kraków', 1234567890, 123456789),
(2, 510223756, 'Max', 'Bojki 19, 30-611 Kraków', 2147483647, 123456789),
(3, 503133455, 'StefBud', 'Budowlana 10, 30-621 Kraków', 2147483647, 123456789),
(4, 600124426, 'Nike', 'Sportowa 13, 30-612 Kraków', 1634867891, 123456789),
(5, 888625436, 'PKO', 'Topolowa 55, 30-610 Kraków', 2147483647, 123456789),
(6, 509826436, 'Orlen', 'Wiertinicza 11, 30-615 Kraków', 2147483647, 123456789);

-- --------------------------------------------------------

--
-- Struktura tabeli dla  `gps`
--

CREATE TABLE IF NOT EXISTS `gps` (
  `idGPS` int(3) NOT NULL AUTO_INCREMENT,
  `Producent` char(45) NOT NULL DEFAULT '',
  `Model` char(45) NOT NULL DEFAULT '',
  `NrSeryjny` int(12) NOT NULL DEFAULT '0',
  `DataOstatniejAktualizacjiMap` date DEFAULT NULL,
  PRIMARY KEY (`idGPS`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=7 ;

--
-- Zrzut danych tabeli `gps`
--

INSERT INTO `gps` (`idGPS`, `Producent`, `Model`, `NrSeryjny`, `DataOstatniejAktualizacjiMap`) VALUES
(1, 'Garmin', 'GR200', 5654345, '2009-12-20'),
(2, 'Garmin', 'GR200', 4654345, '2009-12-20'),
(3, 'Garmin', 'GR200', 3654345, '2009-12-20'),
(4, 'Garmin', 'GR200', 7654345, '2009-12-20'),
(5, 'Garmin', 'GR200', 6654345, '2009-12-20'),
(6, 'Garmin', 'GR200', 6754345, '2009-12-20');

-- --------------------------------------------------------

--
-- Struktura tabeli dla  `kasa_fiskalna`
--

CREATE TABLE IF NOT EXISTS `kasa_fiskalna` (
  `idKASA_FISKALNA` int(3) NOT NULL AUTO_INCREMENT,
  `Producent` char(45) NOT NULL DEFAULT '',
  `Model` char(45) NOT NULL DEFAULT '',
  `NrSeryjny` int(12) NOT NULL DEFAULT '0',
  `NumerHomologacji` int(12) NOT NULL DEFAULT '0',
  `DataOstatniejLegalizacji` date DEFAULT NULL,
  PRIMARY KEY (`idKASA_FISKALNA`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=7 ;

--
-- Zrzut danych tabeli `kasa_fiskalna`
--

INSERT INTO `kasa_fiskalna` (`idKASA_FISKALNA`, `Producent`, `Model`, `NrSeryjny`, `NumerHomologacji`, `DataOstatniejLegalizacji`) VALUES
(1, 'Kaspol', 'K555', 9654345, 145345, '2012-01-20'),
(2, 'Kaspol', 'K555', 8654345, 245345, '2005-01-20'),
(3, 'Kaspol', 'K555', 7654345, 345345, '2005-01-20'),
(4, 'Kaspol', 'K555', 6654345, 445345, '2005-01-20'),
(5, 'Kaspol', 'K555', 5654345, 545345, '2005-01-20'),
(6, 'Kaspol', 'K555', 4654345, 645345, '2005-01-20');

-- --------------------------------------------------------

--
-- Struktura tabeli dla  `kierowca`
--

CREATE TABLE IF NOT EXISTS `kierowca` (
  `idKIEROWCA` int(3) NOT NULL AUTO_INCREMENT,
  `Imie` char(45) NOT NULL DEFAULT '',
  `Nazwisko` char(45) NOT NULL DEFAULT '',
  `PESEL` int(11) NOT NULL DEFAULT '0',
  `NrPrawaJazdy` char(12) NOT NULL DEFAULT '',
  `NrLicencji` int(12) NOT NULL DEFAULT '0',
  `OdKiedyZatrudniony` date DEFAULT NULL,
  `Status` enum('Aktywny','Wolny','brak') NOT NULL DEFAULT 'brak',
  `Samochod` int(3) NOT NULL DEFAULT '0',
  `Strefa` int(3) NOT NULL DEFAULT '0',
  PRIMARY KEY (`idKIEROWCA`),
  KEY `Samochod` (`Samochod`),
  KEY `Strefa` (`Strefa`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=7 ;

--
-- Zrzut danych tabeli `kierowca`
--

INSERT INTO `kierowca` (`idKIEROWCA`, `Imie`, `Nazwisko`, `PESEL`, `NrPrawaJazdy`, `NrLicencji`, `OdKiedyZatrudniony`, `Status`, `Samochod`, `Strefa`) VALUES
(1, 'Stefan', 'Kowal', 2147483647, 'AG123456', 5345445, '2012-05-20', 'brak', 1, 1),
(2, 'Roman', 'Nowakowski', 2147483647, 'AG323456', 2343245, '2012-01-20', 'brak', 2, 3),
(3, 'Kazimierz', 'Buczek', 2147483647, 'AG231486', 1341845, '2011-05-20', 'brak', 3, 5),
(4, 'Barbara', 'Piekarz', 2147483647, 'AG123756', 2340845, '2012-04-20', 'brak', 4, 8),
(5, 'Tomasz', 'Bobrek', 2147483647, 'AG923456', 7313745, '2002-11-20', 'brak', 5, 3),
(6, 'Marian', 'Wypych', 2147483647, 'AG223426', 1383845, '2018-02-20', 'brak', 6, 2);

-- --------------------------------------------------------

--
-- Struktura tabeli dla  `klient`
--

CREATE TABLE IF NOT EXISTS `klient` (
  `idKLIENT` int(10) NOT NULL AUTO_INCREMENT,
  `Telefon` int(10) NOT NULL DEFAULT '0',
  `Imie` char(45) COLLATE utf8_polish_ci DEFAULT '',
  `Nazwisko` char(45) COLLATE utf8_polish_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`idKLIENT`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=7 ;

--
-- Zrzut danych tabeli `klient`
--

INSERT INTO `klient` (`idKLIENT`, `Telefon`, `Imie`, `Nazwisko`) VALUES
(1, 500123458, 'Stefan', 'Kowalski'),
(2, 500223756, 'Roman', 'Nowak'),
(3, 500133455, 'Kazimierz', 'Buk'),
(4, 500124426, 'Barbara', 'Piekarska'),
(5, 500625436, 'Ewa', 'Marzec'),
(6, 500826436, 'Marian', 'Hojda');

-- --------------------------------------------------------

--
-- Struktura tabeli dla  `kurs`
--

CREATE TABLE IF NOT EXISTS `kurs` (
  `idKURS` int(3) NOT NULL AUTO_INCREMENT,
  `Status` enum('Aktywny','Zakonczony') NOT NULL DEFAULT 'Aktywny',
  `GodzinaPrzyjeciaZgloszenia` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `GodzinaStartuKursu` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `GodzinaZakonczeniaKursu` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `Dystans` int(4) NOT NULL DEFAULT '0',
  `Start` char(45) NOT NULL DEFAULT '',
  `Meta` char(45) NOT NULL DEFAULT '',
  `CzasPostoju` time DEFAULT NULL,
  `Cena` float(4,2) DEFAULT NULL,
  `Klient` int(10) NOT NULL DEFAULT '0',
  `Firma` int(10) NOT NULL DEFAULT '0',
  `Stawka` int(1) NOT NULL DEFAULT '0',
  `Kierowca` int(3) NOT NULL DEFAULT '0',
  `Dyspozytor` int(3) NOT NULL DEFAULT '0',
  PRIMARY KEY (`idKURS`),
  KEY `Klient` (`Klient`),
  KEY `Firma` (`Firma`),
  KEY `Stawka` (`Stawka`),
  KEY `Kierowca` (`Kierowca`),
  KEY `Dyspozytor` (`Dyspozytor`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=128 ;

--
-- Zrzut danych tabeli `kurs`
--

INSERT INTO `kurs` (`idKURS`, `Status`, `GodzinaPrzyjeciaZgloszenia`, `GodzinaStartuKursu`, `GodzinaZakonczeniaKursu`, `Dystans`, `Start`, `Meta`, `CzasPostoju`, `Cena`, `Klient`, `Firma`, `Stawka`, `Kierowca`, `Dyspozytor`) VALUES
(123, 'Zakonczony', '2011-12-05 10:05:00', '2011-12-05 10:10:00', '2011-12-05 11:07:00', 18, 'Bojki 15', 'Gronostajowa 50', '00:00:00', 30.00, 5, 0, 1, 2, 1),
(124, 'Zakonczony', '2011-12-05 11:44:00', '2011-12-05 11:55:00', '2011-12-05 12:46:00', 15, 'Studencka 20', 'Piaskowa', '00:00:00', 25.00, 0, 2, 1, 2, 2),
(125, 'Zakonczony', '2011-12-05 12:18:00', '2011-12-05 12:30:00', '2011-12-05 12:51:00', 11, 'Rynek 10', 'Zamkowa', '00:00:00', 20.00, 15, 0, 1, 2, 1),
(126, 'Zakonczony', '2011-12-05 14:26:00', '2011-12-05 14:35:00', '2011-12-05 15:29:00', 22, 'Kobierzynska', 'Podgórki 222', '00:00:35', 20.00, 5, 0, 1, 2, 3),
(127, 'Zakonczony', '2011-12-05 18:15:00', '2011-12-05 18:30:00', '2011-12-05 19:07:00', 28, 'Bojki 1', 'Bydgoska', '00:00:00', 20.00, 42, 0, 1, 2, 2);

-- --------------------------------------------------------

--
-- Struktura tabeli dla  `radiostacja`
--

CREATE TABLE IF NOT EXISTS `radiostacja` (
  `idRADIOSTACJA` int(3) NOT NULL AUTO_INCREMENT,
  `Producent` char(45) NOT NULL DEFAULT '',
  `Model` char(45) NOT NULL DEFAULT '',
  `NrSeryjny` int(12) DEFAULT '0',
  PRIMARY KEY (`idRADIOSTACJA`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=7 ;

--
-- Zrzut danych tabeli `radiostacja`
--

INSERT INTO `radiostacja` (`idRADIOSTACJA`, `Producent`, `Model`, `NrSeryjny`) VALUES
(1, 'Radiokom', 'P3300', 1654345),
(2, 'Radiokom', 'P3300', 2654345),
(3, 'Radiokom', 'P3300', 3654345),
(4, 'Radiokom', 'P3300', 4654345),
(5, 'Radiokom', 'P3300', 5654345),
(6, 'Radiokom', 'P3300', 6654343);

-- --------------------------------------------------------

--
-- Struktura tabeli dla  `samochod`
--

CREATE TABLE IF NOT EXISTS `samochod` (
  `idSAMOCHOD` int(3) NOT NULL AUTO_INCREMENT,
  `Marka` char(45) NOT NULL DEFAULT '',
  `Model` char(45) NOT NULL DEFAULT '',
  `Rocznik` year(4) NOT NULL DEFAULT '2000',
  `NrRejestracyjny` char(8) NOT NULL DEFAULT '',
  `Kolor` char(12) NOT NULL DEFAULT '',
  `IloscMiejsc` int(1) NOT NULL DEFAULT '4',
  `NrPolisyOC` char(20) NOT NULL DEFAULT '',
  `DataWaznosciPolisy` date DEFAULT '0000-00-00',
  `DataOstatniegoPrzegladu` date NOT NULL DEFAULT '0000-00-00',
  `Gps` int(3) NOT NULL,
  `Radio` int(3) NOT NULL,
  `Kasa` int(3) NOT NULL,
  PRIMARY KEY (`idSAMOCHOD`),
  KEY `Gps` (`Gps`),
  KEY `Radio` (`Radio`),
  KEY `Kasa` (`Kasa`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=7 ;

--
-- Zrzut danych tabeli `samochod`
--

INSERT INTO `samochod` (`idSAMOCHOD`, `Marka`, `Model`, `Rocznik`, `NrRejestracyjny`, `Kolor`, `IloscMiejsc`, `NrPolisyOC`, `DataWaznosciPolisy`, `DataOstatniegoPrzegladu`, `Gps`, `Radio`, `Kasa`) VALUES
(1, 'Ford', 'Mondeo 1.8TD', 2002, 'KR 12457', 'zielony', 4, '23423423423', '2005-06-20', '2002-01-20', 1, 1, 1),
(2, 'Ford', 'Galaxy', 2005, 'KR 92657', 'czerwony', 4, '23423423423', '2004-11-20', '2001-01-20', 2, 2, 2),
(3, 'Mercedes', 'S220', 2006, 'KR 22457', 'czarny', 4, '23423423423', '2001-08-20', '2002-02-20', 3, 3, 3),
(4, 'Fiat', '125', 1980, 'KR 72457', 'niebieski', 4, '23423423423', '2015-06-20', '2012-11-20', 4, 4, 4),
(5, 'Renault', 'Espace', 2009, 'KR 12257', 'granatowy', 6, '23423423423', '2019-02-20', '2020-09-20', 5, 6, 6),
(6, 'Mercedes', 'R129', 2008, 'KR 12477', 'czarny', 4, '23423423423', '2020-03-20', '2002-01-20', 6, 5, 5);

-- --------------------------------------------------------

--
-- Struktura tabeli dla  `stawka`
--

CREATE TABLE IF NOT EXISTS `stawka` (
  `idSTAWKA` int(1) NOT NULL AUTO_INCREMENT,
  `Opis` char(45) NOT NULL DEFAULT '',
  `StawkaZaKm` float(2,2) NOT NULL DEFAULT '0.00',
  `StawkaZa15minPostoju` float(2,2) NOT NULL DEFAULT '0.00',
  `StawkaZaWezwanie` float(2,2) NOT NULL DEFAULT '0.00',
  PRIMARY KEY (`idSTAWKA`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=5 ;

--
-- Zrzut danych tabeli `stawka`
--

INSERT INTO `stawka` (`idSTAWKA`, `Opis`, `StawkaZaKm`, `StawkaZa15minPostoju`, `StawkaZaWezwanie`) VALUES
(1, 'dzienna w miescie', 0.99, 0.50, 0.99),
(2, 'nocna w miescie', 0.99, 0.99, 0.99),
(3, 'dzienna poza miasto', 0.99, 0.00, 0.99),
(4, 'nocna poza miasto', 0.99, 0.99, 0.99);

-- --------------------------------------------------------

--
-- Struktura tabeli dla  `strefa`
--

CREATE TABLE IF NOT EXISTS `strefa` (
  `idSTREFA` int(3) NOT NULL AUTO_INCREMENT,
  `Opis` char(45) NOT NULL DEFAULT '',
  PRIMARY KEY (`idSTREFA`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=14 ;

--
-- Zrzut danych tabeli `strefa`
--

INSERT INTO `strefa` (`idSTREFA`, `Opis`) VALUES
(1, 'Ruczaj'),
(2, 'Wola Duchacka'),
(3, 'Bie¿anów'),
(4, 'Prokocim'),
(5, 'Kurdwanów'),
(6, 'Koz³ówek'),
(7, 'Piaski Nowe'),
(8, '¦ródmie¶cie'),
(9, 'Borek Fa³êcki'),
(10, '£agiewniki'),
(11, 'Pradnik Bia³y'),
(12, 'Azory');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
