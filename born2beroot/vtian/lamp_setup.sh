#!/bin/sh
sudo dnf update
sudo dnf install epel-release
sudo dnf install lighttpd \
	mariadb mariadb-server \
	php php-mysqlnd php-pdo php-gd php-mbstring \
	lighttpd-fastcgi php-fpm # fastcgi stuff

sudo firewall-cmd --permanent --zone=public --add-service=http
sudo firewall-cmd --reload

sudo systemctl enable --now php-fpm
sudo systemctl enable --now lighttpd
lighttpd -v
sudo systemctl enable --now mariadb.service

sudo mysql_secure_installation
sudo mysql -u root -p

CREATE DATABASE wpdb;
CREATE USER 'vtian'@'localhost' IDENTIFIED BY 'Qwmnebrv10!!';
GRANT ALL ON wpdb.* TO 'vtian'@'localhost' IDENTIFIED BY 'Qwmnebrv10!!' WITH GRANT OPTION;
FLUSH PRIVILEGES;

EXIT;

# user = lighttpd
# group = lighttpd
# ;listen = /run/php-fpm/www.sock
# listen = 127.0.0.1:9000 
sudo nano /etc/php-fpm.d/www.conf

# server.port = 80
# server.username = "www-data"
# server.groupname = "www-data"
# server.document-root = "/var/www/html"
# server.pid-file = "/run/lighttpd.pid"
# server.errorlog = "/var/log/lighttpad.error.log"
# 	logroot + err.log
sudo nano /etc/lighttpd/lighttpd.conf

# systemctl enable --now php-fpm.serviceW
# cgi.fix_pathinfo=1l
sudo nano /etc/php.ini

# include "conf.d/fastcgi.conf"
sudo nano /etc/lighttpd/modules.conf

# fastcgi.server += ( ".php" =>
#         ((
                # "host" => "127.0.0.1",
                # "port" => "9000",
                # "broken-scriptfilename" =>enable"
#         ))
# )
sudo nano /etc/lighttpd/conf.d/fastcgi.conf

# SELINUX STUFF
# i just followed journalctl
# and this https://bugzilla.redhat.com/show_bug.cgi?id=1322650
sudo nano /etc/selinux/config
sudo setbool -P httpd_setrlimit on
# selinunx config
sudo semanage fcontext -a -t httpd_config_t /etc/lighttpd/lighttpd.conf
sudo restorecon -v /etc/lighttpd/lighttpd.conf

# web dir
# use sys httpd_sys_script_exec_t not httpd_sys_content_t https://unix.stackexchange.com/questions/778774/how-do-i-create-an-selinux-policy-to-allow-php-fpm-to-execute-optipng
# temporary (use semanage fcontext for permanance)
#  sudo chcon -R -t httpd_sys_script_exec_t "/var/www/html/"
sudo semanage fcontext -a -t  httpd_sys_script_exec_t "/var/www/*"
sudo restorecon -Rv /var/www/

# debug selinux logs
sudo grep AVC /var/log/audit/audit.lo

# it was denying port 9000
# type=AVC msg=audit(1750263915.380:265): avc:  denied  { name_connect } for  pid=1947 comm="lighttpd" dest=9000 scontext=system_u:system_r:httpd_t:s0 tcontext=system_u:object_r:http_port_t:s0 tclass=tcp_socket permissive=0
# tried didnt work: sudo semanage port -a -t http_port_t -p tcp 9000
setsebool -P httpd_can_network_connect 1
# by default it only can do inbound not outbound :)


sudo systemctl restart lighttpd

wget -c https://wordpress.org/latest.tar.gz
tar -xvzf latest.tar.gz
mv wordpress/ /var/www/html/
chmod 755 -R /var/www/html/wordpress/

#other stuffhere https://idroot.us/install-lighttpd-fedora-41/