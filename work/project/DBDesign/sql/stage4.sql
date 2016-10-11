-- MySQL dump 10.13  Distrib 5.6.33, for Linux (x86_64)
--
-- Host: localhost    Database: propertydata
-- ------------------------------------------------------
-- Server version	5.6.33-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `building`
--

DROP TABLE IF EXISTS `building`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `building` (
  `building_id` varchar(10) NOT NULL COMMENT '楼栋id',
  `floor_num` smallint(3) NOT NULL COMMENT '楼层数目',
  `built_date` date NOT NULL COMMENT '建成时间',
  PRIMARY KEY (`building_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `building`
--

LOCK TABLES `building` WRITE;
/*!40000 ALTER TABLE `building` DISABLE KEYS */;
INSERT INTO `building` VALUES ('1#',5,'2016-01-01'),('2#',5,'2016-02-01'),('3#',6,'2016-03-01'),('4#',6,'2016-04-01');
/*!40000 ALTER TABLE `building` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `func`
--

DROP TABLE IF EXISTS `func`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `func` (
  `function` varchar(40) NOT NULL COMMENT '功能',
  PRIMARY KEY (`function`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `func`
--

LOCK TABLES `func` WRITE;
/*!40000 ALTER TABLE `func` DISABLE KEYS */;
INSERT INTO `func` VALUES ('ADD_DEL_BUILDING'),('ADD_DEL_CHARGER'),('ADD_DEL_PROPRIETOR'),('ADD_DEL_ROOM'),('CHARGE_FEE'),('RECORD_METER'),('REPORT_FORMS'),('SET_STANDARD');
/*!40000 ALTER TABLE `func` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `meter`
--

DROP TABLE IF EXISTS `meter`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `meter` (
  `building_id` varchar(10) NOT NULL COMMENT '楼栋id',
  `room_id` varchar(10) NOT NULL COMMENT '房屋id',
  `date` date NOT NULL COMMENT '抄表时间',
  `water` decimal(6,1) NOT NULL COMMENT '水表读数',
  `watt` decimal(6,1) NOT NULL COMMENT '电表读数',
  `gas` decimal(6,1) NOT NULL COMMENT '煤气表读数',
  PRIMARY KEY (`room_id`,`building_id`,`date`),
  KEY `building_id` (`building_id`,`room_id`),
  CONSTRAINT `meter_ibfk_1` FOREIGN KEY (`building_id`, `room_id`) REFERENCES `room` (`building_id`, `room_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `meter`
--

LOCK TABLES `meter` WRITE;
/*!40000 ALTER TABLE `meter` DISABLE KEYS */;
INSERT INTO `meter` VALUES ('1#','101','2016-01-01',0.0,0.0,0.0),('1#','101','2016-07-01',2.0,3.0,0.0),('1#','101','2016-07-25',6.0,6.0,6.0),('1#','101','2017-07-01',100.0,100.0,100.0),('2#','101','2016-01-01',0.0,0.0,0.0),('2#','101','2016-07-25',10.0,10.0,10.0),('2#','101','2017-07-01',100.0,100.0,100.0),('3#','101','2016-01-01',0.0,0.0,0.0),('4#','101','2016-01-01',0.0,0.0,0.0),('1#','102','2016-01-01',0.0,0.0,0.0),('2#','102','2016-01-01',0.0,0.0,0.0),('3#','102','2016-01-01',0.0,0.0,0.0),('4#','102','2016-01-01',0.0,0.0,0.0),('1#','201','2016-01-01',0.0,0.0,0.0),('2#','201','2016-01-01',0.0,0.0,0.0),('3#','201','2016-01-01',0.0,0.0,0.0),('4#','201','2016-01-01',0.0,0.0,0.0),('1#','202','2016-01-01',0.0,0.0,0.0),('2#','202','2016-01-01',0.0,0.0,0.0),('3#','202','2016-01-01',0.0,0.0,0.0),('4#','202','2016-01-01',0.0,0.0,0.0),('1#','301','2016-01-01',0.0,0.0,0.0),('2#','301','2016-01-01',0.0,0.0,0.0),('3#','301','2016-01-01',0.0,0.0,0.0),('4#','301','2016-01-01',0.0,0.0,0.0),('1#','302','2016-01-01',0.0,0.0,0.0),('2#','302','2016-01-01',0.0,0.0,0.0),('3#','302','2016-01-01',0.0,0.0,0.0),('4#','302','2016-01-01',0.0,0.0,0.0),('1#','401','2016-01-01',0.0,0.0,0.0),('2#','401','2016-01-01',0.0,0.0,0.0),('3#','401','2016-01-01',0.0,0.0,0.0),('4#','401','2016-01-01',0.0,0.0,0.0),('1#','402','2016-01-01',0.0,0.0,0.0),('2#','402','2016-01-01',0.0,0.0,0.0),('3#','402','2016-01-01',0.0,0.0,0.0),('4#','402','2016-01-01',0.0,0.0,0.0),('1#','501','2016-01-01',0.0,0.0,0.0),('2#','501','2016-01-01',0.0,0.0,0.0),('3#','501','2016-01-01',0.0,0.0,0.0),('4#','501','2016-01-01',0.0,0.0,0.0),('1#','502','2016-01-01',0.0,0.0,0.0),('2#','502','2016-01-01',0.0,0.0,0.0),('3#','502','2016-01-01',0.0,0.0,0.0),('4#','502','2016-01-01',0.0,0.0,0.0),('3#','601','2016-01-01',0.0,0.0,0.0),('4#','601','2016-01-01',0.0,0.0,0.0),('3#','602','2016-01-01',0.0,0.0,0.0),('4#','602','2016-01-01',0.0,0.0,0.0);
/*!40000 ALTER TABLE `meter` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `month_bill`
--

DROP TABLE IF EXISTS `month_bill`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `month_bill` (
  `ID` varchar(18) NOT NULL COMMENT '业主身份证号',
  `date` date NOT NULL COMMENT '月账单产生日期',
  `water` decimal(5,2) NOT NULL COMMENT '月水费数额',
  `watt` decimal(5,2) NOT NULL COMMENT '月电费数额',
  `gas` decimal(5,2) NOT NULL COMMENT '月煤气费数额',
  `tv` decimal(5,2) NOT NULL,
  `property` decimal(5,2) NOT NULL COMMENT '月物业费数额',
  `mortage` decimal(8,2) NOT NULL COMMENT '月房贷数额',
  `payed` varchar(1) DEFAULT NULL,
  PRIMARY KEY (`ID`,`date`),
  CONSTRAINT `month_bill_ibfk_1` FOREIGN KEY (`ID`) REFERENCES `proprietor` (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `month_bill`
--

LOCK TABLES `month_bill` WRITE;
/*!40000 ALTER TABLE `month_bill` DISABLE KEYS */;
INSERT INTO `month_bill` VALUES ('371327199501018899','2016-07-25',20.00,20.00,25.00,18.00,100.00,6000.00,'0'),('371327199501018899','2017-07-01',200.00,250.00,300.00,18.00,50.00,6000.00,'0'),('371327199509115110','2016-07-01',4.00,6.00,0.00,18.00,100.00,6000.00,'0'),('371327199509115110','2016-07-25',12.00,12.00,15.00,18.00,100.00,6000.00,'1'),('371327199509115110','2017-07-01',200.00,250.00,300.00,18.00,50.00,6000.00,'0');
/*!40000 ALTER TABLE `month_bill` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `proprietor`
--

DROP TABLE IF EXISTS `proprietor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `proprietor` (
  `ID` varchar(18) NOT NULL COMMENT '业主身份证号',
  `name` varchar(30) NOT NULL COMMENT '业主姓名',
  `organization` varchar(50) NOT NULL DEFAULT 'none' COMMENT '业主工作单位',
  `building_id` varchar(10) NOT NULL COMMENT '楼栋id',
  `room_id` varchar(10) NOT NULL COMMENT '房屋id',
  `own_date` date NOT NULL COMMENT '入住时间',
  PRIMARY KEY (`ID`),
  KEY `building_id` (`building_id`,`room_id`),
  CONSTRAINT `proprietor_ibfk_1` FOREIGN KEY (`building_id`, `room_id`) REFERENCES `room` (`building_id`, `room_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `proprietor`
--

LOCK TABLES `proprietor` WRITE;
/*!40000 ALTER TABLE `proprietor` DISABLE KEYS */;
INSERT INTO `proprietor` VALUES ('371327199308071123','zhang','SDU','2#','102','2017-07-01'),('371327199501018899','Jack','SDU','2#','101','2016-07-01'),('371327199509115110','Tom','SDU','1#','101','2016-07-01');
/*!40000 ALTER TABLE `proprietor` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `proprietor_phone_num`
--

DROP TABLE IF EXISTS `proprietor_phone_num`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `proprietor_phone_num` (
  `phone_num` varchar(20) NOT NULL COMMENT '业主电话号码',
  `ID` varchar(18) NOT NULL COMMENT '业主身份证号',
  PRIMARY KEY (`phone_num`),
  KEY `ID` (`ID`),
  CONSTRAINT `proprietor_phone_num_ibfk_1` FOREIGN KEY (`ID`) REFERENCES `proprietor` (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `proprietor_phone_num`
--

LOCK TABLES `proprietor_phone_num` WRITE;
/*!40000 ALTER TABLE `proprietor_phone_num` DISABLE KEYS */;
INSERT INTO `proprietor_phone_num` VALUES ('123','371327199308071123'),('15788989009','371327199308071123'),('15866634456','371327199501018899'),('15866617807','371327199509115110'),('15866617809','371327199509115110');
/*!40000 ALTER TABLE `proprietor_phone_num` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `role`
--

DROP TABLE IF EXISTS `role`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `role` (
  `role_type` varchar(20) NOT NULL COMMENT '角色类型',
  PRIMARY KEY (`role_type`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `role`
--

LOCK TABLES `role` WRITE;
/*!40000 ALTER TABLE `role` DISABLE KEYS */;
INSERT INTO `role` VALUES ('CHARGER'),('MANAGER');
/*!40000 ALTER TABLE `role` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `role_func`
--

DROP TABLE IF EXISTS `role_func`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `role_func` (
  `role_type` varchar(20) NOT NULL COMMENT '角色类型',
  `function` varchar(20) NOT NULL COMMENT '功能',
  PRIMARY KEY (`role_type`,`function`),
  KEY `function` (`function`),
  CONSTRAINT `role_func_ibfk_1` FOREIGN KEY (`role_type`) REFERENCES `role` (`role_type`),
  CONSTRAINT `role_func_ibfk_2` FOREIGN KEY (`function`) REFERENCES `func` (`function`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `role_func`
--

LOCK TABLES `role_func` WRITE;
/*!40000 ALTER TABLE `role_func` DISABLE KEYS */;
INSERT INTO `role_func` VALUES ('MANAGER','ADD_DEL_BUILDING'),('MANAGER','ADD_DEL_CHARGER'),('MANAGER','ADD_DEL_PROPRIETOR'),('MANAGER','ADD_DEL_ROOM'),('CHARGER','CHARGE_FEE'),('MANAGER','CHARGE_FEE'),('CHARGER','RECORD_METER'),('MANAGER','RECORD_METER'),('MANAGER','REPORT_FORMS'),('MANAGER','SET_STANDARD');
/*!40000 ALTER TABLE `role_func` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `room`
--

DROP TABLE IF EXISTS `room`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `room` (
  `building_id` varchar(10) NOT NULL COMMENT '楼栋id',
  `room_id` varchar(10) NOT NULL COMMENT '每栋楼上房屋id',
  `area` decimal(5,2) NOT NULL COMMENT '房屋面积',
  `stayed` varchar(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`building_id`,`room_id`),
  CONSTRAINT `room_ibfk_1` FOREIGN KEY (`building_id`) REFERENCES `building` (`building_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `room`
--

LOCK TABLES `room` WRITE;
/*!40000 ALTER TABLE `room` DISABLE KEYS */;
INSERT INTO `room` VALUES ('1#','101',100.00,'1'),('1#','102',100.00,'0'),('1#','201',100.00,'0'),('1#','202',100.00,'0'),('1#','301',100.00,'0'),('1#','302',100.00,'0'),('1#','401',100.00,'0'),('1#','402',100.00,'0'),('1#','501',100.00,'0'),('1#','502',100.00,'0'),('2#','101',100.00,'1'),('2#','102',100.00,'1'),('2#','201',100.00,'0'),('2#','202',100.00,'0'),('2#','301',100.00,'0'),('2#','302',100.00,'0'),('2#','401',100.00,'0'),('2#','402',100.00,'0'),('2#','501',100.00,'0'),('2#','502',100.00,'0'),('3#','101',120.00,'0'),('3#','102',120.00,'0'),('3#','201',120.00,'0'),('3#','202',120.00,'0'),('3#','301',120.00,'0'),('3#','302',120.00,'0'),('3#','401',120.00,'0'),('3#','402',120.00,'0'),('3#','501',120.00,'0'),('3#','502',120.00,'0'),('3#','601',120.00,'0'),('3#','602',120.00,'0'),('4#','101',120.00,'0'),('4#','102',120.00,'0'),('4#','201',120.00,'0'),('4#','202',120.00,'0'),('4#','301',120.00,'0'),('4#','302',120.00,'0'),('4#','401',120.00,'0'),('4#','402',120.00,'0'),('4#','501',120.00,'0'),('4#','502',120.00,'0'),('4#','601',120.00,'0'),('4#','602',120.00,'0');
/*!40000 ALTER TABLE `room` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `standard`
--

DROP TABLE IF EXISTS `standard`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `standard` (
  `start_date` date NOT NULL COMMENT '标准启动时间',
  `water_per_stere` decimal(5,2) NOT NULL DEFAULT '0.00' COMMENT '每立方米水价(元)',
  `watt_per_degree` decimal(5,2) NOT NULL DEFAULT '0.00' COMMENT '每度电价格(元)',
  `gas_per_stere` decimal(5,2) NOT NULL DEFAULT '0.00' COMMENT '每立方米煤气价(元)',
  `tv_per_month` decimal(5,2) NOT NULL DEFAULT '0.00' COMMENT '每月有线电视价格',
  `prop_per_sqare_month` decimal(5,2) NOT NULL DEFAULT '0.00' COMMENT '每平米每月物业费',
  `mortage` decimal(8,2) NOT NULL DEFAULT '0.00',
  PRIMARY KEY (`start_date`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `standard`
--

LOCK TABLES `standard` WRITE;
/*!40000 ALTER TABLE `standard` DISABLE KEYS */;
INSERT INTO `standard` VALUES ('2016-01-20',2.00,2.00,2.50,18.00,1.00,6000.00),('2016-10-01',2.00,2.50,3.00,18.00,0.50,6000.00),('2017-01-01',4.00,4.00,4.00,4.00,4.00,8000.00);
/*!40000 ALTER TABLE `standard` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user` (
  `login_id` varchar(20) NOT NULL COMMENT '系统用户登录名',
  `password` varchar(100) NOT NULL COMMENT '登录密码哈希密文',
  `role_type` varchar(20) NOT NULL,
  PRIMARY KEY (`login_id`),
  KEY `role_type` (`role_type`),
  CONSTRAINT `user_ibfk_1` FOREIGN KEY (`role_type`) REFERENCES `role` (`role_type`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` VALUES ('elvis','37ed2c07cda30a82f8442c52944475ea','MANAGER'),('manager','96e79218965eb72c92a549dd5a330112','MANAGER'),('operator','96e79218965eb72c92a549dd5a330112','CHARGER');
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-10-06 21:39:37
