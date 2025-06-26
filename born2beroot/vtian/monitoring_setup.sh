sudo ln -s ~/bin/monitoring.sh /usr/local/bin/monitoring.sh
sudo chmod +x /usr/local/bin/monitoring.sh
sudo cp /home/vtian/.config/systemd/user/* /etc/systemd/system/
sudo systemctl daemon-reload
sudo systemctl enable --now monitoring.timer
sudo systemctl list-timers --all | grep monitoring