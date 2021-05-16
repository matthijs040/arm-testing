/* Define memory regions. */

/* On the box of the nucleo it says that there is 80KB of RAM. This does not mean you can assign 80K here */
/* Only 64KB are allocatable. The other 16KB are CCM RAM. */

MEMORY
{
	rom (rx) : ORIGIN = 0x08000000, LENGTH = 512k
	ram (rwx) : ORIGIN = 0x20000000, LENGTH = 64K 
}

/* Include the common ld script. */
INCLUDE cortex-m-generic.ld
