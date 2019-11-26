#ifndef PLUGIN_H_INCLUDED
#define PLUGIN_H_INCLUDED
#include "stdint.h"


//获取插件类型
/*
返回值:
0=失败
大于0表示插件类型
*/
typedef unsigned int __cdecl (*get_plugin_type_t)();
unsigned int __declspec(dllexport)  __cdecl get_plugin_type();

//处理hex函数
/*
返回值：
小于等于0表示失败，大于零表示成功修改的内容字节数
*/
typedef int __cdecl  (*process_hex_t)(uint8_t *hex);
int __cdecl __declspec(dllexport)  process_hex(uint8_t *hex);

//烧录插件
/*
小于等于0表示失败，大于零表示成功写入的字节数
*/
typedef int __cdecl (*process_program_t)(const uint8_t *hex);
int __cdecl __declspec(dllexport) process_program(const uint8_t *hex);



#endif // PLUGIN_H_INCLUDED
