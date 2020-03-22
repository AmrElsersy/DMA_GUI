# Direct Memory Access Intel 8237 using Verilog HDL

# GUI 
## DMA Simulator using Qt C++ Framework
Assembler for the Assembly Instructions
Communication with Verilog 
Accessing DMA & Processor Registers

![1](https://user-images.githubusercontent.com/35613645/77266666-c72ad500-6ca8-11ea-8cf6-453438b3de75.png)

## Graphical Simulation
Visualization of the Execution Flow to allow the user to see what is going on underneath the hood @ the Hardware 

![2](https://user-images.githubusercontent.com/35613645/77266668-c8f49880-6ca8-11ea-99fa-b18bf75b85b9.png)
![3](https://user-images.githubusercontent.com/35613645/77266670-cabe5c00-6ca8-11ea-9c8d-53d134f2b001.png)
![4](https://user-images.githubusercontent.com/35613645/77266673-cc881f80-6ca8-11ea-9401-e9f40a778196.png)


## Verilog 
- **Github** : https://github.com/AmrElsersy/DMA.git
-	Supports reading internal registers, current mode and status registers in DMA 
-	Supports IO to Memory, Memory to IO, Memory to Memory modes
-	Supports transferring data up to 64k byte in one request 
-	Supports Memory mapped devices and memory up to 64k byte 
-	Supports 4 channels to connect up to 4 IO devices (Keyboard, Printer and Hard Disk, etc)
-	Supports resetting the DMA, address increment or decrement and DREQ and DACK signal to be read as active low or high
-	Supports status register to be read by processor to be aware the current status of channels in DMA 
-	Supports set request by software (Assembly instruction)
