create table mac2ip ( id int(4) unsigned not null auto_increment primary key,
  `name` varchar(200) not null unique default 'INACTIVE',
  `mac` varchar(17) not null unique default 'INACTIVE',
  `ip` varchar(15) not null,
  `cir` int(5) not null default '0',
  `mir` int(5) not null default '0',
  `active` enum('0','1') default '1',
  `admin_act` enum('0','1') default '0'
);
