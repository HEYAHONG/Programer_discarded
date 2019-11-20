#include "stdio.h"
#include "plugin.h"
unsigned int __cdecl get_plugin_type()
{
return 1;
}

int __cdecl  process_hex(uint8_t *hex)
{
return 0;
}

int __cdecl process_program(const uint8_t *hex)
{
return 0;
}
