#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "can.h"

void callbackFrame(CAN_FRAME *frame)
{	
	writeToStruct(*frame);
    saveFrame(*frame);
    printFrame(*frame);
}

#endif // INTERRUPT_H
