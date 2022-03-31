-- phpMyAdmin SQL Dump
-- version 5.1.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jan 27, 2022 at 02:26 PM
-- Server version: 10.4.18-MariaDB
-- PHP Version: 7.3.27

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `ernita`
--
CREATE DATABASE IF NOT EXISTS `ernita` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
USE `ernita`;

-- --------------------------------------------------------

--
-- Table structure for table `status`
--

DROP TABLE IF EXISTS `status`;
CREATE TABLE IF NOT EXISTS `status` (
  `mode` int(11) NOT NULL,
  PRIMARY KEY (`mode`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `status`
--

INSERT INTO `status` (`mode`) VALUES
(4);

-- --------------------------------------------------------

--
-- Table structure for table `tmprfid`
--

DROP TABLE IF EXISTS `tmprfid`;
CREATE TABLE IF NOT EXISTS `tmprfid` (
  `nokartu` varchar(20) NOT NULL,
  `pass` varchar(20) NOT NULL,
  PRIMARY KEY (`nokartu`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `tmprfid`
--

INSERT INTO `tmprfid` (`nokartu`, `pass`) VALUES
('2', '');

-- --------------------------------------------------------

--
-- Table structure for table `t_rfid`
--

DROP TABLE IF EXISTS `t_rfid`;
CREATE TABLE IF NOT EXISTS `t_rfid` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `tag_rfid` varchar(100) NOT NULL,
  `pass` varchar(100) NOT NULL,
  `lemari_no` int(11) NOT NULL,
  `stat` enum('A','N') NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `t_rfid`
--

INSERT INTO `t_rfid` (`id`, `tag_rfid`, `pass`, `lemari_no`, `stat`) VALUES
(1, '14721017024', '1234', 1, 'A'),
(2, '281905174', '4', 2, 'A');

-- --------------------------------------------------------

--
-- Table structure for table `t_transaksi`
--

DROP TABLE IF EXISTS `t_transaksi`;
CREATE TABLE IF NOT EXISTS `t_transaksi` (
  `id_transaksi` int(11) NOT NULL AUTO_INCREMENT,
  `tagRfid` varchar(100) NOT NULL,
  `jumlah` int(11) NOT NULL,
  `lemari` int(11) NOT NULL,
  `tanggal` date NOT NULL,
  PRIMARY KEY (`id_transaksi`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `t_transaksi`
--

INSERT INTO `t_transaksi` (`id_transaksi`, `tagRfid`, `jumlah`, `lemari`, `tanggal`) VALUES
(7, '281905174', 20, 1, '2022-01-23');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
