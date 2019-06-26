drop database Silas;

create database Silas;

use Silas;

DROP TABLE  IF EXISTS `admin`;
DROP TABLE  IF EXISTS `flight`;
DROP TABLE  IF EXISTS `seat`;
DROP TABLE  IF EXISTS `passenger`;
DROP TABLE  IF EXISTS `order`;


DROP TABLE  IF EXISTS `notify`;
DROP TABLE  IF EXISTS `bill`;



CREATE TABLE `admin` (
  `aid` char(10) NOT NULL,
  `pass` char(10) NOT NULL,
  PRIMARY KEY  (`aid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


INSERT INTO `Silas`.`admin`(`aid`, `pass`) VALUES ('000001','123');
INSERT INTO `Silas`.`admin`(`aid`, `pass`) VALUES ('000002','123');
INSERT INTO `Silas`.`admin`(`aid`, `pass`) VALUES ('000003','123');
INSERT INTO `Silas`.`admin`(`aid`, `pass`) VALUES ('000004','123');

/*航班号和时间共同组成唯一键*/

CREATE TABLE `flight` (
  `fid` char(10) NOT NULL,
  `splace` char(10) NOT NULL,
  `eplace` char(10) NOT NULL,
  `stime` timestamp NOT NULL,
  PRIMARY KEY  (`fid`,`stime`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000001','北京','广州','2019-06-18 05:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000002','上海','深圳','2019-06-18 10:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000003','杭州','成都','2019-06-18 14:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000004','重庆','南京','2019-06-18 21:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000005','广州','北京','2019-06-18 23:21:00');

INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000001','北京','广州','2019-06-19 05:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000002','上海','深圳','2019-06-19 10:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000003','杭州','成都','2019-06-19 14:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000004','重庆','南京','2019-06-19 21:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000005','广州','北京','2019-06-19 23:21:00');

INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000001','北京','广州','2019-06-20 05:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000002','上海','深圳','2019-06-20 10:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000003','杭州','成都','2019-06-20 14:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000004','重庆','南京','2019-06-20 21:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000005','广州','北京','2019-06-20 23:21:00');

INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000001','北京','广州','2019-06-21 05:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000002','上海','深圳','2019-06-21 10:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000003','杭州','成都','2019-06-21 14:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000004','重庆','南京','2019-06-21 21:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000005','广州','北京','2019-06-21 23:21:00');

INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000001','北京','广州','2019-06-22 05:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000002','上海','深圳','2019-06-22 10:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000003','杭州','成都','2019-06-22 14:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000004','重庆','南京','2019-06-22 21:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000005','广州','北京','2019-06-22 23:21:00');

INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000001','北京','广州','2019-06-23 05:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000002','上海','深圳','2019-06-23 10:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000003','杭州','成都','2019-06-23 14:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000004','重庆','南京','2019-06-23 21:21:00');
INSERT INTO `Silas`.`flight`(`fid`, `splace`,`eplace`,`stime`) VALUES ('000005','广州','北京','2019-06-23 23:21:00');


/*座位*/
CREATE TABLE `seat` (
  `sid` char(10) NOT NULL,
  `fid` char(10) NOT NULL,
  `price` decimal(10,2) NOT NULL,
  PRIMARY KEY  (`sid`,`fid`),
  FOREIGN KEY  (`fid`) REFERENCES `flight`(`fid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000001','000001',1401.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000002','000001',1402.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000003','000001',1403.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000004','000001',1404.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000005','000001',1405.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000006','000001',1406.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000007','000001',1407.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000008','000001',1408.5);

INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000001','000002',1301.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000002','000002',1302.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000003','000002',1303.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000004','000002',1304.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000005','000002',1305.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000006','000002',1306.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000007','000002',1307.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000008','000002',1308.5);

INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000001','000003',1201);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000002','000003',1202);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000003','000003',1203);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000004','000003',1204);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000005','000003',1205);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000006','000003',1206);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000007','000003',1207);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000008','000003',1208);

INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000001','000004',1101.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000002','000004',1102.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000003','000004',1103.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000004','000004',1104.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000005','000004',1105.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000006','000004',1106.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000007','000004',1107.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000008','000004',1108.5);

INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000001','000005',1401.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000002','000005',1402.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000003','000005',1403.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000004','000005',1404.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000005','000005',1405.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000006','000005',1406.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000007','000005',1407.5);
INSERT INTO `Silas`.`seat`(`sid`, `fid`,`price`) VALUES ('000008','000005',1408.5);




CREATE TABLE `passenger` (
  `pid` char(10) NOT NULL,
  `pass` char(10) NOT NULL,
  `name` char(10) NOT NULL,
  `idcard` char(18) NOT NULL,
  `phone` char(11) NOT NULL,
  PRIMARY KEY  (`pid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `Silas`.`passenger`(`pid`, `pass`,`name`,`idcard`,`phone`) VALUES ('1','1','小樱','7894501','63700184');
INSERT INTO `Silas`.`passenger`(`pid`, `pass`,`name`,`idcard`,`phone`) VALUES ('000001','123','朱雀院椿','7894501','63700184');
INSERT INTO `Silas`.`passenger`(`pid`, `pass`,`name`,`idcard`,`phone`) VALUES ('000002','123','朝雾海斗','7894502','63700284');
INSERT INTO `Silas`.`passenger`(`pid`, `pass`,`name`,`idcard`,`phone`) VALUES ('000003','123','法月将臣','7894503','63700384');
INSERT INTO `Silas`.`passenger`(`pid`, `pass`,`name`,`idcard`,`phone`) VALUES ('000004','123','綾地宁宁','7894504','63700484');

/* 添加票价预防票价变动 --ctime是飞机起飞时间 保证订票唯一性*/

DROP TABLE  IF EXISTS `order`;

CREATE TABLE `order` (
  `oid` char(10) UNIQUE NOT NULL,
  
  `fid` char(10) NOT NULL,
  `sid` char(10) NOT NULL,
  `pid` char(10) NOT NULL,
  `price` decimal(10,2) NOT NULL,
  `ctime` timestamp NOT NULL,
  PRIMARY KEY  (`fid`,`sid`,`ctime`),
  FOREIGN KEY (`fid`) REFERENCES `flight`(`fid`),
  FOREIGN KEY (`sid`) REFERENCES `seat`(`sid`),
  FOREIGN KEY (`pid`) REFERENCES `passenger`(`pid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*
INSERT INTO `Silas`.`order`(`oid`, `fid`,`sid`,`pid`, `price`,`ctime`) VALUES('000001','000001','000001','000003',1400.5,'2019-04-18 14:21:00');
INSERT INTO `Silas`.`order`(`oid`, `fid`,`sid`,`pid`, `price`,`ctime`) VALUES('000002','000001','000002','000003',1400.5,'2019-04-18 14:21:00');
INSERT INTO `Silas`.`order`(`oid`, `fid`,`sid`,`pid`, `price`,`ctime`) VALUES('000003','000001','000003','000003',1400.5,'2019-04-18 14:21:00');

*/

/*一张票一张单*/
CREATE TABLE `notify` (
  `nid` char(10) NOT NULL,
  `oid` char(10) NOT NULL,
  PRIMARY KEY  (`nid`),
  FOREIGN KEY (`oid`) REFERENCES `order`(`oid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


/*一个订单一个账单这样bid和oid主键就行了,但是pid用户信息不能省略*/
CREATE TABLE `bill` (
  `bid` char(10) NOT NULL,
  `oid` char(10) NOT NULL,
  `pid` char(10) NOT NULL,
  `price` decimal(10,2) NOT NULL,
  `pay` boolean NOT NULL,
  `ptime` timestamp,
  PRIMARY KEY  (`bid`),
  FOREIGN KEY (`oid`) REFERENCES `order`(`oid`),
  FOREIGN KEY (`pid`) REFERENCES `passenger`(`pid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


use Silas;
select * from admin;
select * from flight;
select * from seat;
select * from passenger;
select * from `order`;
select * from notify;
select * from bill;


