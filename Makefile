all:
	@echo "Compiling the program..."
	gcc daemon.c -lvirt -o daemon

install: all
	@echo ""

	@grep -Fq 'Environment="VFIO_VM_NAME=' vfio-vm-rotation.service || \
	(echo 'ERROR: Please set `VFIO_VM_NAME` environment variable in vfio-vm-rotation.service, then try again.' && exit 1)

	@grep -Fq 'Environment="IDLE_VM_NAME=' vfio-vm-rotation.service || \
	(echo 'ERROR: Please set `IDLE_VM_NAME` environment variable in vfio-vm-rotation.service, then try again.' && exit 1)

	@echo "Installing the binary..."
	mkdir -p /opt/vfio-vm-rotation/
	cp daemon /opt/vfio-vm-rotation/
	chmod u+x /opt/vfio-vm-rotation/daemon

	@echo "" ; echo "Installing the systemd service..."
	cp vfio-vm-rotation.service /etc/systemd/system
	systemctl enable --now vfio-vm-rotation

	@echo "" ; echo "Installation finished!"

uninstall:
	@echo "Disabling and deleting the service..."
	systemctl disable --now vfio-vm-rotation
	rm -f /etc/systemd/system/vfio-vm-rotation.service
	
	@echo "" ; echo "Deleting the binary..."
	rm -rf /opt/vfio-vm-rotation

	@echo "" ; echo "Uninstallation finished!"
