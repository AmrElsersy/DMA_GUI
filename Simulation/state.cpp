#include "state.h"


State::State()
{
    this->PC=0;
    this->Hold=INITIAL_COLOR;
    this->HoldAck = INITIAL_COLOR;
    this->DACK_IO_1 = INITIAL_COLOR;
    this->DACK_IO_2 = INITIAL_COLOR;
    this->DREQ_IO_1 = INITIAL_COLOR;
    this->DREQ_IO_2 = INITIAL_COLOR;
    this->Instruction = "xxxx";
    this->ControlBusColor = INITIAL_COLOR;
    this->DataBusColor = INITIAL_COLOR;
    this->AddressBusColor = INITIAL_COLOR;

    this->ControlValue = "0";
    this->DataBusValue = "0";
    this->AddressBusValue = "0";

    this->CPUColor = INITIAL_COLOR;
    this->DMAColor = INITIAL_COLOR;
    this->IO1Color = INITIAL_COLOR;
    this->IO2Color = INITIAL_COLOR;
    this->RAMColor = INITIAL_COLOR;
}
