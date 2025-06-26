#!/bin/bash
wall <<EOF
	$(echo "Architecture : $(uname -m) $(uname -r)")
	$(lscpu | grep 'Socket(s)' | awk '{print "CPU Physical : "$2}')
	$(nproc | awk '{print "vCPU : "$1}')
	$(free -m | awk '/Mem:/ {printf "Memory Usage: %d MB, Used: %.2f%%\n", $7, $3/$2 * 100}')
	$(df -h | grep -vE '^tmpfs|cdrom' | awk 'NR>1 {print "Mount: "$6", Usage: "$3"/"$2" ("$4" Free), Used: "$5}')
	$(top -bn1 | grep "Cpu(s)" | awk '{print "CPU Load: " 100 - $8 "%"}')
	$(who -b | awk '{print "Last Reboot: "$3, $4}')
	$(lsblk | grep lvm >/dev/null && echo "LVM: active" || echo "LVM: inactive")
	$(ss -tun | grep ESTAB | wc -l | awk '{print "Connections TCP : "$1}')
	$(who | wc -l | awk '{print "user log : "$1}')
	$(ip -4 addr show | grep inet | grep -v 127 | awk '{print "IP: "$2};')
	$(ip link show | awk '/ether/ {print "MAC: "$2}')
EOF
	# $(grep -c 'COMMAND=' /var/log/sudo.log 2>/dev/null || grep -c 'sudo' /var/log/secure)