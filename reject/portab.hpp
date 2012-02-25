#ifndef __PORTAB_HPP__                
#define __PORTAB_HPP__                

#ifdef __x86_64
typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned int  DWORD;

typedef char  SBYTE;
typedef short SWORD;
typedef int  SDWORD;

#else

typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;

typedef char  SBYTE;
typedef short SWORD;
typedef long  SDWORD;
                                  
#endif                            
#endif                            
