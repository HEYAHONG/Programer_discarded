#include "stdio.h"
#include "plugin.h"
#include "windows.h"
#include "string.h"
#include "unistd.h"
int  cpp_plug_process_program_cpp(const uint8_t *hex);

unsigned int __cdecl __declspec(dllexport)  get_plugin_type()
{
return 2;
}

int __cdecl __declspec(dllexport)  process_hex(uint8_t *hex)//插件类型为2,不处理此函数。
{

return 0;
}

int __cdecl __declspec(dllexport) process_program(const uint8_t *hex)
{
  return   cpp_plug_process_program_cpp(hex);
}
