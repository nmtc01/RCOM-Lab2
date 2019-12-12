#!/bin/bash
ifconfig eth0 up
ifconfig eth0 172.16.41.1/24
route add default gw 172.16.41.254
echo 1 > /proc/sys/net/ipv4/conf/eth0/accept_redirects
echo 1 > /proc/sys/net/ipv4/conf/all/accept_redirects
vi /etc/resolv.conf search netlab.fe.up.pt nameserver 172.16.1.1