# Python script for rotating between two VMs (for VFIO)

## Description

A Python service boot the VFIO gaming VM after the idle VM is shut off, and vice versa.

## Prerequisites  

- Systemd, Libvirt (+QEMU/KVM), a VFIO gaming VM and a idle VM
- Python 3.11 or up
- `libvirt-python`

## Usage

1. Clone this repo
2. Edit `VFIO_VM_NAME` and `IDLE_VM_NAME` in [vm_rotation](./vm_rotation)
3. Run (with root) [install.sh](./install.sh),
4. Run (with root) `systemctl enable vm-rotation-daemon`.

## Uninstall

Run the following with root:

1. `systemctl disable --now vm-rotation-daemon`
2. `rm -rf /usr/vfio-vm-rotation-service`
3. ``

## TODO

Rewrite this in C
