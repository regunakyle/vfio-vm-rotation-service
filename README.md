## Description

Systemd service (written in C) that boots the VFIO gaming VM after the idle VM is shut off, and vice versa.

Note: This has been tested on a Fedora KDE install only, use at your own risk!

## Why is this needed?

The Linux gurus in the [VFIO Discord](https://discord.com/invite/f63cXwH) suggests always bind your gaming GPU to the proprietary driver (because they save more power than `vfio-pci`).

One approach to this is to create a low resource "idle VM", attach the GPU to it and install proprietary driver inside. Boot the idle VM after the VFIO VM shuts down (and vice versa).

You cannot use QEMU hooks to do this, as calling `virsh` in a hook script will lead to deadlock.

Systemd service is a viable alternative, so I wrote one myself.

Please refer to the `wiki-and-psa` channel in the [VFIO Discord](https://discord.com/invite/f63cXwH) for further power saving settings that should be implemented inside the idle VM.

## Prerequisites  

- systemd, libvirt (+QEMU/KVM), a VFIO gaming VM and a idle VM
- libvirt C library (e.g. `sudo dnf install libvirt-devel` in Fedora)
- `gcc`, `make`

## Usage

1. Clone this repo and install dependencies
2. **IMPORTANT:** Add these items under `[Service]` in [vfio-vm-rotation.service](./vfio-vm-rotation.service):

    ```
    # Change the values below accordingly
    Environment="VFIO_VM_NAME=vfio-linux"
    Environment="IDLE_VM_NAME=vfio-win10"
    # Optional: Default to "qemu:///system" if not set
    # Environment="CONNECTION_URI=qemu:///system"
    ```

3. Run `sudo make install`

You may use `make static` instead create a binary with statically linked libvirt. In such case, please handle service file installation by yourself.

## Uninstall

Run `sudo make uninstall`
