#include "qemu/osdep.h"
#include "hw/char/debug-dev.h"
#include "hw/qdev-properties.h"
#include "hw/qdev-properties-system.h"
#include "target/arm/cpu-qom.h"
#include "qemu/log.h"
#include "qemu/module.h"


#include "exec/address-spaces.h"



static void debug_dev_reset(DeviceState *dev)
{
}

#define DATASIZE 10
static uint64_t debug_dev_read(void *opaque, hwaddr addr,
                                       unsigned int size)
{
    // DebugDevState *s = DEBUG_DEV(opaque);
    // const int baseaddr = 0;

    // uint8_t data[DATASIZE] = { 0 };

    if (addr == 0x0) {
        printf("debug_dev enter\n");


        MemoryRegionSection sub_region_a = memory_region_find(get_system_memory(), 0x60000000, 0x1000);
        MemoryRegionSection sub_region_b = memory_region_find(get_system_memory(), 0x60001000, 0x1000);

        if (sub_region_a.mr != NULL) {
            memory_region_set_address(sub_region_a.mr, 0x60001000);
        }
        if (sub_region_b.mr != NULL) {
            memory_region_set_address(sub_region_b.mr, 0x60000000);
        }

        printf("debug_dev exit\n");
        return 0;
    }
    return 0;
}

static void debug_dev_write(void *opaque, hwaddr addr,
                                  uint64_t val64, unsigned int size)
{
}

static const MemoryRegionOps debug_dev_ops = {
    .read = debug_dev_read,
    .write = debug_dev_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static Property debug_dev_properties[] = {
    DEFINE_PROP_END_OF_LIST(),
};

static void debug_dev_init(Object *obj)
{
    DebugDevState *s = DEBUG_DEV(obj);

    ARMCPU *cpu = ARM_CPU(first_cpu);
    CPUState *cs = CPU(cpu);
    // address_space_write_rom(rom->as, rom->addr, MEMTXATTRS_UNSPECIFIED, rom->data, rom->DATASIZE);
    // AddressSpace *as = cpu_get_address_space(cs, asidx);
    s->as = cpu_get_address_space(cs, 0);
    memory_region_init_io(&s->mmio, obj, &debug_dev_ops, s, TYPE_DEBUG_DEV, 0x400);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void debug_dev_realize(DeviceState *dev, Error **errp)
{
}

static void debug_dev_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->reset = debug_dev_reset;
    device_class_set_props(dc, debug_dev_properties);
    dc->realize = debug_dev_realize;
}

static const TypeInfo debug_dev_info = {
    .name          = TYPE_DEBUG_DEV,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(DebugDevState),
    .instance_init = debug_dev_init,
    .class_init    = debug_dev_class_init,
};

static void debug_dev_register_types(void)
{
    type_register_static(&debug_dev_info);
}

type_init(debug_dev_register_types)
