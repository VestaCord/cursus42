#!/bin/bash
sudo sed -i 's/^PASS_MAX_DAYS.*/PASS_MAX_DAYS	30/' /etc/login.defs
sudo sed -i 's/^PASS_MIN_DAYS.*/PASS_MIN_DAYS	2/' /etc/login.defs
sudo sed -i 's/^PASS_MIN_LEN.*/PASS_MIN_LEN	10/' /etc/login.defs
sudo sed -i 's/^PASS_WARN_AGE.*/PASS_WARN_AGE	7/' /etc/login.defs

sudo cat /etc/security/pwquality.conf > /home/vtian/.config/pwquality.conf.backup
sudo cat /home/vtian/.config/pwquality.conf > /etc/security/pwquality.conf

# dangerous as fuck
# cat /etc/authselect/system-auth > /etc/authselect/system-auth.backup
# cat /home/vtian/.config/system-auth > /etc/authselect/system-auth