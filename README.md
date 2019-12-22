# DMA_GUI
Direct Memory Access 

•	Modularity
o	All modules that in data sheet is implemented 
o	Support reusability and readable comments
o	Easy to test and debug 
•	Supports program condition mode from processor to DMA by addresses in 8237 datasheet or by using software (Assembly instructions) 
•	Supports reading internal registers, current mode and status registers in DMA 
•	Supports IO to Memory, Memory to IO, Memory to Memory modes
•	Supports transferring data up to 64k byte in one request 
•	Supports Memory mapped devices and memory up to 64k byte 
•	Supports 4 channels to connect up to 4 IO devices (Keyboard, Printer and Hard Disk, etc)
•	Supports handling more than 4 IO devices by cascade mode 
•	Supports single transfer mode to transfer one time till number of words changes to zero, block transfer mode to transfer unknown number of transfers till the IO sends external EOP (end of operation) to DMA.
•	Handling priority to the devices which connected to channels in priority module
•	Supports disable or enable any of channels in DMA by mask register
•	Supports Auto initialization to set the operation to the default mode to restart the transfer if channel in verify transfer mode
•	Supports resetting the DMA, address increment or decrement and DREQ and DACK signal to be read as active low or high
•	Supports status register to be read by processor to be aware the current status of channels in DMA 
•	Supports set request by software (Assembly instruction)
•	Supports mode register programing to define every channel parameter as read or write transfer 

Processor
•	Supports arithmetic operations (xor, or, add, addi, etc).
•	Communicates with RAM and IO Devices through the Bus through an assembly instructions “LW” $register $address and “SW “  $register $address “ 
•	Supports assembly instructions to access with DMA internal registers
•	Executes arithmetic instructions during DMA Transfers
•	Support Holding the Execution of the Bus’s Instructions if the DMA uses the Bus.

BUS 
•	Consist of DataBus, AddressBus, control, IReady and TReady
•	Supports acknowledgement for both master and slaves through IReady and TReady Control lines
•	Read and Write Operations take one clock cycle
