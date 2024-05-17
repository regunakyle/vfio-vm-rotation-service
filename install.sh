#!/bin/bash
set -euo pipefail

if ! grep -Fq 'Environment="VFIO_VM_NAME=' vfio-vm-rotation.service; then
    echo "ERROR: Please set \`VFIO_VM_NAME\` environment variable in vfio-vm-rotation.service, then try again."
    exit 1
fi

if ! grep -Fq 'Environment="IDLE_VM_NAME=' vfio-vm-rotation.service; then
    echo "ERROR: Please set \`IDLE_VM_NAME\` environment variable in vfio-vm-rotation.service, then try again."
    exit 1
fi

mkdir -p /opt/vfio-vm-rotation/
cp daemon /opt/vfio-vm-rotation/
chmod u+x /opt/vfio-vm-rotation/daemon

cp vfio-vm-rotation.service /etc/systemd/system
systemctl enable --now vfio-vm-rotation

echo "Install finished!"
