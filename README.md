# DMA_GUI
## Direct Memory Access Intel 8237 using Verilog HDL
•	Supports reading internal registers, current mode and status registers in DMA 
•	Supports IO to Memory, Memory to IO, Memory to Memory modes
•	Supports transferring data up to 64k byte in one request 
•	Supports Memory mapped devices and memory up to 64k byte 
•	Supports 4 channels to connect up to 4 IO devices (Keyboard, Printer and Hard Disk, etc)
•	Supports resetting the DMA, address increment or decrement and DREQ and DACK signal to be read as active low or high
•	Supports status register to be read by processor to be aware the current status of channels in DMA 
•	Supports set request by software (Assembly instruction)

# GUI 
## DMA Simulator using Qt C++ Framework
Assembler for the Assembly Instructions
Communication with Verilog 
Accessing DMA & Processor Registers

![GUI](https://ibb.co/ZxXRSNV)

## Graphical Simulation
Visualization of the Execution Flow to allow the user to see what is going on underneath the hood @ the Hardware 

![Design](https://ibb.co/LQ92tvc)

![DMA](https://ibb.co/1sZH3YF)

![Processor](https://ibb.co/W2rrhfH)
