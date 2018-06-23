/****************************************************************************
 Copyright (c) 2008,       SensL Technologies LTD.      All Rights Reserved.
*****************************************************************************

   File          : HRMTimeAPI.h

   Author        : Paul Rosinger

   Date          : 01-06-2008

   Function      : HRMTime HRMTimeAPI main header file.

   Update        : 05-07-2008 
   By            : Steve Buckley
   Reason        : 1. Add HRM_GetTimeTagGap, HRM_GetTimeTagGap
                      and HRM_GetLastError functions
                   2. Add module resolutions constants
   				   All changes indicated by (2.00)

   Update        : 18-08-2008 
   By            : Steve Buckley
   Reason        : Add functions:
                      HRM_RunFifoTimeTagging
					  HRM_GetTimeTagGap
                      HRM_FixTimeTags
					  HRM_GetMemorySize
   				   All changes indicated by (2.01)

   Update        : 14-11-2008 
   By            : Steve Buckley
   Reason        : Change code to allow RESYNC FIFO TimeTagging mode.
                   Global variable ResyncTTAG is set for new mode if
				   the FSR is set to 0xFFFF.
                   All changes indicated by (2.02)
				   
   Update        : 14-02-2009 
   By            : Steve Buckley
   Reason        : Add MODE for FIFO functions.
                   All changes indicated by (2.03)

****************************************************************************/
// #define COMPILE_FOR_LABVIEW

#pragma once

#include "windows.h"
#include "quickusb.h"
#include "HRMTimeErrs.h"

#ifdef HRMTIMEAPI_EXPORTS
#define HRM_API __declspec(dllexport)
#else
#define HRM_API __declspec(dllimport)
#endif

/*(2.02)*/
extern USHORT ResyncTTAG;

/*
 CONSTANTS FOR THE MODE REGISTER
*/
#define FILL_MEM_MODE		0
#define TTAG_TCSPC_MODE		1
#define	TTAG_CONT_MODE		2
#define	TBIN_TCSPC_MODE		3
#define TBIN_CONT_MODE		4

#define BINSIZE16			(1<<3)
#define BINSIZE32			0

#define FPGA_RESET			(1<<4)

#define BYTE_CMD			0
#define BLOCK_CMD			(1<<5)

#define RMODE				0

#define FIFO_READ_MODE		0
#define BLOCK_READ_MODE		0

#define START_MEM_TRANSFER	(1<<14)

#define MODE_PROCESSOR_START (1<<15)
#define MODE_PROCESSOR_RESET 0 


#define HRM_STATUS int

/****************************************/
/*   Resolutions of the module  (2.00)  */
/****************************************/
#define MICRO_RESOLUTION    26.9851
#define MACRO_RESOLUTION    5.0

#define MAX_MODULES         (USHORT)40  /*(2.01)*/

/*
 Definitions for FIFO mode (2.3)
*/
#define FIFO_TCSPC          (USHORT)0
#define FIFO_FREE_RUNNING   (USHORT)1
#define FIFO_RESYNC         (USHORT)2

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////
//		Low level functionality
//////////////////////////////////////////////////////////////////////////

HRM_API const char* WINAPI HRM_GetDLLVersion();

HRM_API void WINAPI  HRM_SetConfigurationPath(char* path);

HRM_API HRM_STATUS WINAPI HRM_RefreshConnectedModuleList();

HRM_API UINT WINAPI  HRM_GetConnectedModuleCount();

HRM_API HRM_STATUS WINAPI  HRM_GetConnectedModuleList(HANDLE* handleList);

HRM_STATUS WINAPI HRM_GetProductCodeRegister(HANDLE handle, USHORT *pcrData);

HRM_API HRM_STATUS WINAPI HRM_CloseModule(HANDLE handle);

HRM_API HRM_STATUS WINAPI HRM_SetAddressRouteRegister(HANDLE handle, BYTE* arrData);

HRM_API HRM_STATUS WINAPI HRM_SetDataRouteRegister(HANDLE handle, BYTE* drrData);

HRM_API HRM_STATUS WINAPI HRM_SetAddressRegister(HANDLE handle, ULONG arData);

HRM_API HRM_STATUS WINAPI HRM_SetFillValueRegister(HANDLE handle, ULONG fvrData);

HRM_API HRM_STATUS WINAPI HRM_SetUSBAddressRegister(HANDLE handle, ULONG uarData);

HRM_API HRM_STATUS WINAPI HRM_SetModeBitsRegister(HANDLE handle, USHORT mbrData);

HRM_API HRM_STATUS WINAPI HRM_SetEdgeSensitivityRegister(HANDLE handle, USHORT esrData);

HRM_API HRM_STATUS WINAPI HRM_SetRoutingResetRegister(HANDLE handle, USHORT rrrData);

HRM_API HRM_STATUS WINAPI HRM_SetMemoryCountRegister(HANDLE handle, ULONG mcrData);

HRM_API HRM_STATUS WINAPI HRM_SetUSBCountRegister(HANDLE handle, ULONG ucrData);

HRM_API HRM_STATUS WINAPI HRM_SetFrequencySelectionRegister(HANDLE handle, USHORT fsrData);

HRM_API HRM_STATUS WINAPI HRM_SetIODirectionRegister(HANDLE handle, USHORT iodrData);

HRM_API HRM_STATUS WINAPI HRM_SetIOValueRegister(HANDLE handle, USHORT iovrData);

HRM_API HRM_STATUS WINAPI HRM_SetBinCountRegister(HANDLE handle, ULONG mcrData);

HRM_API HRM_STATUS WINAPI HRM_GetStatusRegister(HANDLE handle, USHORT& srData);

HRM_API HRM_STATUS WINAPI HRM_GetSoftwareRevisionRegister(HANDLE handle, USHORT& srrData);

HRM_API HRM_STATUS WINAPI HRM_GetWriteCountRegister(HANDLE handle, ULONG& wrrData);

HRM_API HRM_STATUS WINAPI HRM_GetModuleIDRegister(HANDLE handle, BYTE *midData);

HRM_API HRM_STATUS WINAPI HRM_InitMemory(HANDLE handle, ULONG addr, ULONG len, ULONG fillData);

HRM_API HRM_STATUS WINAPI HRM_ReadMemory(HANDLE handle, USHORT modeMask, ULONG addr, ULONG len, BYTE *buf);

HRM_API HRM_STATUS WINAPI HRM_ReadFIFOMemory(HANDLE handle, USHORT modeMask, ULONG addr, ULONG len, BYTE *buf);

HRM_API HRM_STATUS WINAPI HRM_SetFPGAConfigRegister(HANDLE handle, USHORT fcrData);

HRM_API HRM_STATUS WINAPI HRM_WriteBlockFPGAConfigRegister(HANDLE handle, BYTE *ptr, USHORT addr, USHORT len);

HRM_API bool WINAPI HRM_HasFeature(HANDLE handle, const char *featureName);

HRM_API bool WINAPI HRM_HasChannel(HANDLE handle, unsigned ch);

HRM_API int WINAPI HRM_GetMinimumMicrotimeLSB(HANDLE handle);
/*(2.01)*/
HRM_API HRM_STATUS WINAPI HRM_GetMemorySize(HANDLE handle, ULONG *size);

//////////////////////////////////////////////////////////////////////////
//		Higher level functionality
//////////////////////////////////////////////////////////////////////////

HRM_API HRM_STATUS WINAPI HRM_StreamTCSPC2File(HANDLE handle, char* outfname, long recordinglength, long esr, int microbits, int microlsb, int macrobits, int macrolsb);

HRM_API HRM_STATUS WINAPI HRM_StreamTCSPC2Mem(HANDLE handle, BYTE* buf, ULONG bufsize, long recordinglength, long esr, int microbits, int microlsb, int macrobits, int macrolsb, ULONG &recordedbytes);

HRM_API HRM_STATUS WINAPI HRM_StreamTimeTags2File(HANDLE handle, char* outfname, long recordinglength, long esr, USHORT microlsb);

HRM_API HRM_STATUS WINAPI HRM_StreamTimeTags2Mem(HANDLE handle, BYTE* buf, ULONG bufsize, long recordinglength, long esr, USHORT microlsb, ULONG& recordedbytes);

HRM_API HRM_STATUS WINAPI HRM_RequestStop(HANDLE handle);

HRM_API HRM_STATUS WINAPI HRM_ConvertRawTCSPCFile2CSV(char* infname, char*  outfname, int microbits, int microlsb, int macrobits, int macrolsb);

HRM_API HRM_STATUS WINAPI HRM_ConvertRawContTTagsFile2CSV(char* infname, char*  outfname, USHORT microlsb);

HRM_API HRM_STATUS WINAPI HRM_CorrelateTimeBins(HANDLE handle, ULONG *x, ULONG lx, ULONG* y, ULONG ly, ULONG maxlag, double* corr);

HRM_API HRM_STATUS WINAPI HRM_StartHistogramFSM(HANDLE handle, USHORT tcspc, USHORT microlsb);

/*(2.00)(2.02)*/
HRM_API HRM_STATUS WINAPI HRM_GetTimeTagGap(ULONG pMacro, ULONG pMicro, ULONG cMacro, ULONG cMicro, BYTE *channel, double *gap);
/*(2.00)*/
HRM_API HRM_STATUS WINAPI HRM_GetFifoTCSPCinfo(ULONG tag, ULONG microBits, ULONG microLSB, ULONG macroLSB, BYTE *channel, double *micro, double *macro);
/*(2.00)*/
HRM_API HRM_STATUS WINAPI HRM_GetLastError(HRM_STATUS newVal);
/*(2.01)*/
HRM_API HRM_STATUS WINAPI  HRM_RunFifoTimeTagging(HANDLE handle, USHORT ESRreg, USHORT microlsb, USHORT mode);
/*(2.01)*/
HRM_API HRM_STATUS WINAPI  HRM_RunFifoTCSPC(HANDLE handle, USHORT ESRreg, USHORT microbits, USHORT microlsb, USHORT macrolsb);
/*(2.01)(2.03)*/
HRM_API HRM_STATUS WINAPI  HRM_GetFifoData(HANDLE handle, USHORT mode, ULONG max, ULONG *size, ULONG *buffer);
/*(2.01)(2.03)*/
HRM_API void WINAPI HRM_FixTimeTags(USHORT mode, ULONG size, ULONG *buffer);
/*(2.03)*/
HRM_API HRM_STATUS HRM_ConvertRAWtoCSV(USHORT mode, USHORT microBits, char *rawFile, char *csvFile);

#ifdef __cplusplus
}
#endif
