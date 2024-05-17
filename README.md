## Description

A Python service that boots the VFIO gaming VM after the idle VM is shut off, and vice versa.

Note: This has been tested on a Fedora 40 system only, use at your own risk!

## Prerequisites  

- systemd, libvirt (+QEMU/KVM), a VFIO gaming VM and a idle VM
- Python 3.11 or up
- `libvirt-python` (e.g. `dnf install libvirt-python` in Fedora)

## Usage

1. Clone this repo
2. **IMPORTANT:** Add these items under `[Service]` in [vfio-vm-rotation.service](./vfio-vm-rotation.service):

    ```
    # Change the values below accordingly
    Environment="VFIO_VM_NAME=<Name of your VFIO VM>"
    Environment="IDLE_VM_NAME=<Name of your idle VM>"
    # Optional: Default to "qemu:///system" if not set
    # Environment="CONNECTION_URI=<Name of your idle VM>"
    ```

3. Run (with root) [install.sh](./install.sh)

You can edit the service file directly after installation (in `/etc/systemd/system/vfio-vm-rotation.service`).

## Uninstall

Run the following with root:

1. `systemctl disable --now vfio-vm-rotation`
2. `rm -rf /opt/vfio-vm-rotation`
3. `rm /etc/systemd/system/vfio-vm-rotation.service`
