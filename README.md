## Description

C program that boots the VFIO gaming VM after the idle VM is shut off, and vice versa.

Note: This has been tested on a Fedora 40 system only, use at your own risk!

## Prerequisites  

- systemd, libvirt (+QEMU/KVM), a VFIO gaming VM and a idle VM
- libvirt C library (e.g. `dnf install libvirt-devel` in Fedora)
- `gcc`

## Usage

1. Clone this repo and install dependencies
2. **IMPORTANT:** Add these items under `[Service]` in [vfio-vm-rotation.service](./vfio-vm-rotation.service):

    ```
    # Change the values below accordingly
    Environment="VFIO_VM_NAME=<Name of your VFIO VM>"
    Environment="IDLE_VM_NAME=<Name of your idle VM>"
    # Optional: Default to "qemu:///system" if not set
    # Environment="CONNECTION_URI=<Name of your idle VM>"
    ```

3. Run (with root) `make install`

## Uninstall

Run (with root) `make uninstall`

## Note

You can find the Python version of this program in the `python_version` branch. (It eats up about 2x amount of RAM though)
