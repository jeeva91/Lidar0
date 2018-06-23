////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef MTI_DEFINITIONS_H
#define MTI_DEFINITIONS_H

///////////////////////////////////////////////////////////////////////////////////
// OS & DLL Export / Import Specifiers
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	#define MTI_WINDOWS
#endif
#if defined(__linux__) || defined( __unix__)
	#define MTI_UNIX
#endif

#ifdef MTI_UNIX
	#define DLLEXPORT
#elif MTI_ANDROID
	#define DLLEXPORT
#elif _MTIDLLEXPORT
	#define DLLEXPORT	__declspec(dllexport)
#else
	#define DLLEXPORT	__declspec(dllimport)
#endif
///////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Macros
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=0; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=0; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=0; } }
#define SIGN(x)				 ((x) > 0 ? 1 : -1)
#define SWAP_2(x)			 ((((x) & 0xff) << 8) | ((unsigned short)(x) >> 8))
#define LE_SHORT(x)			 (*(unsigned short *)&(x) = SWAP_2(*(unsigned short *)&(x)))
#define BOUND_COORD(x)		 (((x) > 1.0) ? 1.0 : (((x) < -1.0) ? -1.0 : (x)));
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MTI_MAXDEVICES	12

typedef void* MTIHandle;		// for the C API

// MTIDEVICE SECTION
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum MTIError
{
	// all of the items must be in the specific order
	MTI_SUCCESS,
	MTI_ERR_INVALID_HANDLE,
	MTI_ERR_INVALID_DEVICEID,
	MTI_ERR_GENERAL,
	MTI_ERR_SERIALCOMM,
	MTI_ERR_SERIALCOMM_READ_TIMEOUT,
	MTI_ERR_SERIALCOMM_SERIAL_RESET_FAIL,
	MTI_ERR_INCORRECT_TARGET_RESPONSE,
	MTI_ERR_PARAMETER_OUT_OF_RANGE,
	MTI_ERR_SOME_PARAMETERS_CANNOT_BE_SET,
	MTI_ERR_INVALID_PARAMETER_NAME,
	MTI_ERR_CONNECTDEVICE_INVALID_PORTNAME,
	MTI_ERR_CONNECTDEVICE_PORT_NOT_AVAILABLE,
	MTI_ERR_LOADDEVICEPARAMS_FILE_NOT_FOUND,
} 
MTIError;

typedef enum MTIBlockingMode
{
	MTI_BLOCKING_MODE_ERR = -1,
	MTI_BLOCKING_MODE_OFF =  0,
	MTI_BLOCKING_MODE_ON  =  1,
}
MTIBlockingMode;

typedef enum MTIParam
{
	HardwareFilterOn,			// read only
	VmaxMEMSDriver,				// read only
	DeviceState,				// read only
	DeviceErrorRegister,		// read only
	USARTBaudRate,
	SampleRate,
	HardwareFilterBw,
	VdifferenceMax,
	Vbias,
	OutputOffsets,
	DataScale,
	DataRotation,
	MEMSDriverEnable,
	DigitalOutputEnable,
	LaserModulationEnable,
	BufferOffset,
	DeviceAxes,
	BootSetting,
	DataMode,
	SyncMode,
	FramesPerSecond,
	InterpolationType,
	WaveformType,
}
MTIParam;

typedef enum MTIAxes
{
	// all of the items must be in the specific order
	Normal													= 0,
	FlipXY													= 1,
	MirrorY													= 2,
	MirrorY_FlipXY											= 3,
	MirrorX													= 4,
	MirrorX_FlipXY											= 5,
	MirrorX_MirrorY											= 6,
	MirrorX_MirrorY_FlipXY									= 7,
}
MTIAxes;

typedef enum MTIDataMode
{
	// all of the items must be in the specific order
	Sample_Output											= 0,
	Sample_And_Analog_Input_Buffer							= 1,
	Keypoint												= 2,
	Text													= 3,
	Waveform												= 4,
	Analog_Input_To_Output									= 5,
	Sample_And_Analog_Input_Stream							= 6,
	Sample_And_Analog_Input_Track							= 7,
	Auto_Track												= 8,
}
MTIDataMode;

typedef enum MTISync
{
	// all of the items must be in the specific order
	Output_DOut0											= 0,
	Output_Inverted_DOut0									= 1,
	Output_Sample_Clock										= 2,
	Output_Start_Trigger									= 3,
	External_Sample_Clock									= 4,
	External_Start_Trigger									= 5,
	External_Frame_Trigger									= 6,

}
MTISync;

typedef enum MTIBoot
{
	// all of the items must be in the specific order
	Boot_With_Factory_Defaults								= 0,
	Boot_With_Flash_Device_Params							= 1,
	Boot_With_Flash_Data_And_Autorun						= 2,
	Boot_With_Flash_Data_No_Autorun							= 3,
}
MTIBoot;

typedef enum MTIFlash
{
	// all of the items must be in the specific order
	Device_Params,
	Data_In_Buffer,
} MTIFlash;

typedef enum MTIDeviceLimits
{
	SampleRate_Min,						// read only
	SampleRate_Max,						// read only
	SamplesPerFrame_Min,				// read only
	SamplesPerFrame_Max,				// read only
	HardwareFilterBw_Min,				// read only
	HardwareFilterBw_Max,				// read only
	FramesPerSecond_Min,				// read only
	FramesPerSecond_Max,				// read only
	VdifferenceMax_Min,					// read only
	VdifferenceMax_Max,					// read only
	Vbias_Min,							// read only
	Vbias_Max,							// read only
} MTIDeviceLimits;

typedef enum MTITrack
{
	Threshold,
	NormalGain,
	TangentialGain,
	BufferDelay,
	HitRatio,
	EnableSearch,
	EnableOffsetStreaming,
	EnableTrack,
} MTITrack;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MTIDATAGENERATOR SECTION
// Enums for DataGenerator
typedef enum FilterType
{
	FilterNone			= 0,
	FilterBessel		= 1,
	FilterButterworth	= 2,
	FilterChebyshevI	= 3,
	FilterChebyshevII	= 4,
	FilterElliptic		= 5,
	FilterLegendre		= 6,
	FilterIIRGeneric	= 7,
}
FilterType;

typedef enum SpirographType
{
	CurveRose			= 0,
	CurveEpicycloid		= 1,
	CurveEpitrochoid	= 2,
	CurveHypocycloid	= 3,
	CurveHypotrochoid	= 4,
}
SpirographType;

typedef enum ModulationType
{
	ModulationNone	= 0,
	ModulationAmpl	= 1,
	ModulationFreq	= 2,
}
ModulationType;

typedef enum WaveType
{
	WaveSine	 = 0,
	WaveTriangle = 1,
	WaveSquare   = 2,
}
WaveType;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif