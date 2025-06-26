# Born2BeRoot Instructions (Rocky Linux)

## Configuration Requirements 
- No need KDump
- SELinux
  - for rocky minimal install, `getenforce` is `enforcing`
  - `semanage` is missing, must install from `policycoreutils-python-utils`
  - `semanage` must be used to set custom SSH port
- LVM Partitioning (at least 2 encrypted) BONUS if all
  	- vg-root /
  	- vg-home /home
  	- swap [SWAP]
  	- var /var
  	- srv /srv
  	- tmp /tmp
  	- var--log /var/log
  - sshd on tcp/4242
	- no root
	- must be enable on startup
- hostname is {username}42
- [strong passwd policy](https://www.server-world.info/en/note?os=Rocky_Linux_8&p=pam&f=1)
  - `login.defs`
	- expire * * * */30 *
	- password modification only for day > 2
	- password change reminder after day > 23
  - `pwquality.conf`
    - minlen 10
	- must have [a-z][A-Z][0-9] and no 3 consecutive identical char
	- must not have username
	- (NOT APPLICABLE FOR ROOT) min 7 char must not overlap with previous passwd
    	- You don't need to mess with any PAM files like `system-auth`. [PAM does not even compare the previous password](https://stackoverflow.com/questions/72362666/pam-cracklib-not-enforcing-difok-for-root-even-with-enforce-for-root-option)
    	- I lost 1h cause I bricked my VM editing `system-auth` :)
    	- However there are more useful resources at least:
  		- https://docs.redhat.com/en/documentation/red_hat_enterprise_linux/7/html/system-level_authentication_guide/pam_configuration_files
		- https://linux.die.net/man/8/pam_succeed_if

- strong sudo policy `visudo` (don't scp / rsync this because of bricking)
  - max 3 login attempts
	`Defaults    passwd_tries=3`
  - custom sudo wrong password message
	`Defaults    badpass_message="Access denied. Contact your system administrator."`
  - all sudo actions must be archived to a `/var/log/sudo/sudo.log`
	`Defaults    logfile="/var/log/sudo/sudo.log"`
	`Defaults    log_input,log_output`
	```
	...
	sudo chown root:root /var/log/sudo/sudo.log
	sudo chmod 600 $_
	```
  - TTY mode enabled for security
	`Defaults    requiretty`
  - only allow $PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin
	`Defaults    secure_path="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin"`
- users
	- root
	- {username}
		- must belong to sudo and user42
- after setting configurations
  - immediately change passwords of all accounts
  
## `monitoring.sh`
At server startup, the script will display some information (listed below) on all termi- nals and every 10 minutes (take a look at `wall`). The banner is optional. No error must be visible. You will also have to interrupt it without modifying it. Take a look at `cron`.

`wall <<EOF`
- The architecture of your operating system and its kernel version.
	`uname -m && uname -r`
- The number of physical processors.
	`lscpu | grep 'Socket(s)' | awk '{print $2}'`
- The number of virtual processors.
	`nproc`
- The current available RAM on your server and its utilization rate as a percentage.
	`free -m | awk '/Mem:/ {printf "Available: %d MB, Used: %.2f%%\n", $7, $3/$2 * 100}'`
- The current available storage on your server and its utilization rate as a percentage.
	`df -h / | awk 'NR==2 {print "Disk Usage: "$3"/"$2" ("$4" Free), Used: "$5}'`
- The current utilization rate of your processors as a percentage.
	`top -bn1 | grep "Cpu(s)" | awk '{print "CPU Usage: " 100 - $8 "%"}'`
- The date and time of the last reboot.
	`who -b | awk '{print "Last Reboot: "$3, $4}'`
- Whether LVM is active or not.
	`lsblk | grep lvm >/dev/null && echo "LVM: active" || echo "LVM: inactive"`
- The number of active connections.
	`ss -tun | grep ESTAB | wc -l`
- The number of users using the server.
	`who | wc -l`
- The IPv4 address of your server and its MAC (Media Access Control) address.
	`ip -4 addr show | grep inet | grep -v 127 | awk '{print "IP: "$2};'`
	`ip link show | awk '/ether/ {print "MAC: "$2}'`
- The number of commands executed with the sudo program.
	`grep -c 'COMMAND=' /var/log/sudo.log 2>/dev/null || grep -c 'sudo' /var/log/secure`

`EOF`

Example output:
```
#Architecture: Linux wil 4.19.0-16-amd64 #1 SMP Debian 4.19.181-1 (2021-03-19) x86_64 GNU/Linux
#CPU physical : 1
#vCPU : 1
#Memory Usage: 74/987MB (7.50%)
#Disk Usage: 1009/2Gb (49%)
#CPU load: 6.7%
#Last boot: 2021-04-25 14:45
#LVM use: yes
#Connections TCP : 1 ESTABLISHED
#User log: 1
#Network: IP 10.0.2.15 (08:00:27:51:9b:a5)
#Sudo : 42 cmd
```

### Using Systemd instead of Crontabs
`cron` is older than systemd timers, is much less centralized and feature rich.
Nowadays, it is less often used in production, and more for hotfixes and tests.

### Hints
- `head -n 2 /etc/os-release`
- `firewall-cmd [--state | --list-service | --list-port]`

## Bonus
- functional WordPress site
  - lighttpd
  - MariaDB
  - PHP
- Additional Service (Can update **Firewalld** freely)
  - (My Choice) File Server: NFS
  - Monitoring: Prometheus
  - LDAP: OpenLDAP
  - DNS Server: Bind9
  - VCS: Gitlab
  - Caching Proxy: Squid

## Banned Stuff
- Snapshots

# Submission
- sha1sum rocky_serv.sdi > signature.txt

# Defense
- Explain all the major tools used
	- KDump vs no KDump
	- Rocky vs Debian
	- SELinux vs Apparmor
	- UFW vs **Firewalld** 
- Setup a new user and assign to group over SSH