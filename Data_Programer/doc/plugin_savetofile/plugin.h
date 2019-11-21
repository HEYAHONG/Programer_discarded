#ifndef PLUGIN_H_INCLUDED
#define PLUGIN_H_INCLUDED
#include "stdint.h"


//��ȡ�������
/*
����ֵ:
0=ʧ��
����0��ʾ�������
*/
typedef unsigned int __cdecl (*get_plugin_type_t)();
unsigned int __declspec(dllexport)  __cdecl get_plugin_type();

//����hex����
/*
����ֵ��
С�ڵ���0��ʾʧ�ܣ��������ʾ�ɹ��޸ĵ������ֽ���
*/
typedef int __cdecl  (*process_hex_t)(uint8_t *hex);
int __cdecl __declspec(dllexport)  process_hex(uint8_t *hex);

//��¼���
/*
С�ڵ���0��ʾʧ�ܣ��������ʾ�ɹ�д����ֽ���
*/
typedef int __cdecl (*process_program_t)(const uint8_t *hex);
int __cdecl __declspec(dllexport) process_program(const uint8_t *hex);



#endif // PLUGIN_H_INCLUDED
