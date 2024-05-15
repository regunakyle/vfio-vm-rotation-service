# Python script for rotating between two VMs (for VFIO)

## Description

A Python service boot the VFIO gaming VM after the idle VM is shut off, and vice versa.

## Prerequisites  

- Systemd, Libvirt (+QEMU/KVM), a VFIO gaming VM and a idle VM
- Python 3.11 or up
- `libvirt-python` ()
- `systemd-python` ()

## Usage

Clone this repo, edit `VFIO_VM_NAME` and `IDLE_VM_NAME` in [vm_rotation](./vm_rotation), then run (with root) [install.sh](./install.sh),

Then run (with root) `systemctl enable vm-rotation-daemon`.

## Uninstall

Run the following with root:

1. `systemctl stop vm-rotation-daemon`
2. `systemctl disable vm-rotation-daemon`
3. ``
