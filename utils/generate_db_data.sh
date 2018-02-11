#!/bin/bash

for i in `seq 10 49`; do echo "insert into mac2ip (name, mac, ip, admin_act) values ('Client$i', '00:01:02:03:05:$i', '192.168.0.$i', '1');" ; done
