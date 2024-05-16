#!/bin/bash
set -euo pipefail

mkdir -p /opt/vfio-vm-rotation/
cp daemon /opt/vfio-vm-rotation/
chmod u+x /opt/vfio-vm-rotation/daemon

cp vfio-vm-rotation.service /etc/systemd/system
systemctl enable --now vfio-vm-rotation

echo "Install finished!"
