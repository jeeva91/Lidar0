#pragma once

// for the delay
#include "HRMTimeAPI.h"
#include "QuickUSB.h"
#include "ni4882.h"
#include "MTIDevice.h"
#include "MTIDefinitions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <string>

#define DLY_BOARDID 0
#define DLY_PRIMARYADD 5
#define DLY_SECONDARYADD 0
#define DLY_TIMEOUT 10
#define DLY_EOS 1
#define DLY_EOT 0

//int change_delay(int dly);
//int change_offs

//for the TDC
typedef unsigned char Ubyte; /* Unsigned byte */
typedef char Sbyte; /* Signed byte */
typedef unsigned short Uword; /* Unsigned 16 bits */
typedef short Sword; /* Signed 16 bits */
typedef unsigned int Ulong; /* Unsigned 32 bits */
typedef int Slong; /* Signed 32 bits */
typedef double Sdoub; /* Double */
#define CH0_ADDR 0
#define CH1_ADDR CH0_ADDR+0x80000
#define CH2_ADDR CH1_ADDR+0x80000
#define CH3_ADDR CH2_ADDR+0x80000

#define  MEMORY_SZ      (Ulong)0x200000



//for the Mirror
#define OUTCHAR 255