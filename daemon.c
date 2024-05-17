#include <libvirt/libvirt.h>
#include <syslog.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void)
{
    const char *VFIO_VM_NAME = getenv("VFIO_VM_NAME");
    const char *IDLE_VM_NAME = getenv("IDLE_VM_NAME");

    const char *CONNECTION_URI = getenv("IDLE_VM_NAME");

    if (!CONNECTION_URI)
    {
        CONNECTION_URI = "qemu:///system";
    }

    if (!VFIO_VM_NAME && !IDLE_VM_NAME)
    {
        syslog(LOG_ERR, "Exiting because the following variable(s) are not set:%s%s\n", VFIO_VM_NAME ? "" : " VFIO_VM_NAME", IDLE_VM_NAME ? "" : " IDLE_VM_NAME");
        return EXIT_FAILURE;
    }

    virConnectPtr conn = NULL;

    if (!(conn = virConnectOpen("qemu:///system")))
    {
        syslog(LOG_ERR, "Failed to connect to hypervisor.");
        return EXIT_FAILURE;
    }

    virDomainPtr vfio_vm = NULL;
    if (!(vfio_vm = virDomainLookupByName(conn, VFIO_VM_NAME)))
    {
        syslog(LOG_ERR, "Unable to find VM '%s'", VFIO_VM_NAME);
    }

    virDomainPtr idle_vm = NULL;
    if (!(idle_vm = virDomainLookupByName(conn, IDLE_VM_NAME)))
    {
        syslog(LOG_ERR, "Unable to find VM '%s'", IDLE_VM_NAME);
    }

    bool boot_vfio_next = false;

    syslog(LOG_INFO, "Service started.");

    int vfio_vm_state;
    int idle_vm_state;
    int dummy;

    for (;;)
    {
        /*
         *  See https://libvirt.org/html/libvirt-libvirt-domain.html#virDomainState
         *  for the meaning of state values
         */

        // virDomainGetState() produces `state` and `reason`, only the former is useful to us
        virDomainGetState(vfio_vm, &vfio_vm_state, &dummy, 0);
        virDomainGetState(idle_vm, &idle_vm_state, &dummy, 0);

        if (vfio_vm_state == 5 && idle_vm_state == 5)
        {
            // If both VMs are shut off, boot the next VM in the rotation
            sleep(1);

            if (boot_vfio_next)
            {
                syslog(LOG_INFO, "Booting VFIO VM!");
                if (virDomainCreate(vfio_vm) != 0)
                {
                    syslog(LOG_ERR, "Failed to boot the VFIO VM.");
                }
            }
            else
            {
                syslog(LOG_INFO, "Booting idle VM!");
                if (virDomainCreate(idle_vm) != 0)
                {
                    syslog(LOG_ERR, "Failed to boot the idle VM.");
                }
            }

            boot_vfio_next = !boot_vfio_next;
        }
        // Assume that both VMs cannot be up at the same time
        else if (vfio_vm_state == 1)
        {
            boot_vfio_next = false;
        }
        else if (idle_vm_state == 1)
        {
            boot_vfio_next = true;
        }

        sleep(1);
    }
}
