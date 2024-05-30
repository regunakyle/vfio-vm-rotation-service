## Description

Systemd service (written in C) that boots the VFIO gaming VM after the idle VM is shut off, and vice versa.

Note: This has been tested on a Fedora 40 system only, use at your own risk!

## Why is this needed?

The [VFIO Discord](https://discord.com/invite/f63cXwH) suggests always bind the GPU to any VM (because this might save power).

One approach to implement this is to boot the idle VM after the VFIO VM shuts down (and vice versa).

You cannot use QEMU hooks to do this, as calling `virsh` in a hook script will lead to race condition.

Systemd service is a viable alternative, so I wrote one myself.

Please refer to the `wiki-and-psa` channel in the [VFIO Discord](https://discord.com/invite/f63cXwH) for further power saving settings that should be implemented inside the idle VM.

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
