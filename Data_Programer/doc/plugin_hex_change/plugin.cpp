#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdint.h"
int   cpp_process_hex_cpp(uint8_t *hex);//����������
#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
#include "plugin.h"
int __cdecl __declspec(dllexport) process_program(const uint8_t *hex)
{

    return 0;
}
unsigned int __cdecl __declspec(dllexport) get_plugin_type()
{
    return 1;
}
int __cdecl __declspec(dllexport) process_hex(uint8_t *hex)
{
    return cpp_process_hex_cpp(hex);
}
#ifdef __cplusplus
}
#endif // __cplusplus
#include "vector"
#ifdef WIN32
#include "windows.h"
#endif // WIN32

//hex����Ϣ�ṹ��
typedef
struct
{
size_t start_pos;
size_t end_pos;
} line_info;


//�ַ����鵽Hex�ַ���֮���ת����
/*
out��������������Է�ֹ���룻
�ɹ�����0��ʧ�ܷ��ط���
*/
static inline int  str2Hex(unsigned char in[],size_t in_size,unsigned char out[],size_t out_size)
{
if(in_size>((out_size)/2))
    return 1;//����ַ����ռ䲻��
for(size_t i=0;i<in_size;i++)
    {
        unsigned char H=0,L=0;
        H=(in[i]>>4);
        L=(in[i]& 0x0f);

        if(H<=9)
            {
                out[2*i]='0'+H;
            }
        else
            {
               out[2*i]='A'+H-10;
            }
        if(L<=9)
            {
                out[2*i+1]='0'+L;
            }
        else
            {
               out[2*i+1]='A'+L-10;
            }

    }
return 0;
}

//��Сд��֧��
/*
Hex�ַ���ת�ַ�����
*/
static inline int  hex2str(unsigned char in[],size_t in_size,unsigned char out[],size_t out_size)
{

if((in_size%2) != 0)
    return 1;//���ܲ���Hex�ַ���
for(size_t i=0;i<in_size/2;i++)
    {
        unsigned char H=0,L=0;
        if(in[2*i] <= '9' && in[2*i] >= '0')
        {
            H=in[2*i]-'0';
        }
        if(in[2*i] <= 'F' && in[2*i] >= 'A')
        {
            H=in[2*i]-'A'+10;
        }
        if(in[2*i] <= 'f' && in[2*i] >= 'a')
        {
            H=in[2*i]-'a'+10;
        }

        if(in[2*i+1] <= '9' && in[2*i+1] >= '0')
        {
            L=in[2*i+1]-'0';
        }
        if(in[2*i+1] <= 'F' && in[2*i+1] >= 'A')
        {
            L=in[2*i+1]-'A'+10;
        }
        if(in[2*i+1] <= 'f' && in[2*i+1] >= 'a')
        {
            L=in[2*i+1]-'a'+10;
        }
        out[i]=((H<<4)+L);

    }

return 0;
}


//���������е���Ϣ�ṹ��
typedef
struct
{
    size_t symbol_start;
    size_t symbol_length;
    size_t flash_success;
} env_info_t;

static env_info_t env_info={0,0,0};//Ĭ��ȫ��
static int load_env_var()//���ػ�������
{
char *data=NULL;
if((data=getenv("symbol_start"))!=NULL)//symbol_start�������
    {
       size_t i;
       sscanf(data,"%X",&i);
       env_info.symbol_start=i;
    }
else
    return -1;

if((data=getenv("symbol_length"))!=NULL)//symbol_length�������
    {
       size_t i;
       sscanf(data,"%u",&i);
       env_info.symbol_length=i;
    }
else
    return -1;

if((data=getenv("flash_success"))!=NULL)
    {
       size_t i;
       sscanf(data,"%u",&i);
       env_info.flash_success=i;
    }
else
   {
       env_info.flash_success=0;
   }

return 0; //�ɹ�����0
}

#include "thread"

static const char *thread_msg=NULL,*thread_title=NULL;
static void messagebox_thread()
{
  MessageBoxA(NULL,thread_msg,thread_title,MB_OK);
}
static void inline messagebox(const char * msg,const char * title="��ʾ",bool Is_noblock=true)//��Ϣ��
{
if(Is_noblock)
{
   thread_msg=msg;
   thread_title=title;
   std::thread *th=new std::thread(messagebox_thread);
   th->detach();
}
else
{
    MessageBoxA(NULL,msg,title,MB_OK);
}

}


static std::vector<line_info> hex_line_info;
static uint8_t*hex_data=NULL;
static inline void load_hex_line_info()
{
    hex_line_info.clear();
    {//ͳ����λ��
        line_info temp;
        for(size_t i=0;i<strlen((char *)hex_data);i++)
        {
           if(hex_data[i]==':') //����ʼ
                    temp.start_pos=i;
           if(hex_data[i]=='\n')
               {//�н���
                   temp.end_pos=i;
                   hex_line_info.push_back(temp);
               }
        }
    }

}


static int check_ECC()//������У����
{
    unsigned char buff_str[300],buff_hex[600];
    for(size_t i=0;i<hex_line_info.size();i++)
    {
        memset(buff_hex,0,sizeof(buff_hex));
        memset(buff_str,0,sizeof(buff_str));
        size_t length=hex_line_info[i].end_pos-hex_line_info[i].start_pos-2;
        uint8_t *data_start=&hex_data[hex_line_info[i].start_pos+1];

        if(((hex_line_info[i].end_pos-hex_line_info[i].start_pos)>300) ||(hex_line_info[i].start_pos+2>hex_line_info[i].end_pos))
         {
            messagebox("hex�����쳣��","����");
            return -1;
         }
         memcpy(buff_hex,data_start,length);
         if(hex2str(buff_hex,length,buff_str,length/2))
         {
             messagebox("hexת������","����");
             return -1;
         }
         {//����У��λ
             uint16_t sum=256;
             uint8_t  temp=0;
             for(size_t pos=0;pos<length/2;pos++)
             {
                 if((length/2)-1 != pos)
                 {
                     temp+=buff_str[pos];
                 }
                 else
                 {
                     buff_str[pos]=((sum-temp)&0xff);
                 }

             }

         }

         if(str2Hex(buff_str,length/2,buff_hex,length))
         {
             messagebox("hexת������","����");
             return -1;
         }
         memcpy(data_start,buff_hex,length);

    }
    return 0;
}






int   cpp_process_hex_cpp(uint8_t *hex)
{
    hex_data=hex;//����hex���ݱ���
    int file_size=strlen((char *)hex);
    if(load_env_var()<0)
    {
        messagebox("���ػ��������쳣,���������ļ��Ƿ�����!\n");
        return 0;
    }

    load_hex_line_info();//����hex����Ϣ



    if(check_ECC()<0)
        {
           return 0;
        }

//    {
//        //���Դ���
//        char buff[8192];
//        memset(buff,0,sizeof(8192));
//        sprintf(buff,"hex����:%u,symbol_start=%08X,symbol_length=%d,flash_success=%d,%d,%d",
//                                hex_line_info.size(),
//                                env_info.symbol_start,
//                                env_info.symbol_length,
//                                env_info.flash_success,
//                                hex_line_info[0].start_pos,
//                                hex_line_info[0].end_pos);
//        messagebox(buff,"����");
//    }

    return file_size;
}




