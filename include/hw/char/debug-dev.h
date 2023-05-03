#ifndef HW_DEBUG_DEV_STATE_H
#define HW_DEBUG_DEV_STATE_H

#include "hw/sysbus.h"
#include "chardev/char-fe.h"
#include "qom/object.h"


#define TYPE_DEBUG_DEV "debug-dev"
OBJECT_DECLARE_SIMPLE_TYPE(DebugDevState, DEBUG_DEV)

struct DebugDevState {
    /* <private> */
    SysBusDevice parent_obj;

    /* <public> */
    MemoryRegion mmio;
    AddressSpace *as;
};

#endif