//////////////////////////////////////////////////////////////////////
// MTIDevice
//////////////////////////////////////////////////////////////////////

#ifndef MTI_DEVICE_H
#define MTI_DEVICE_H
#define MTI_RESETSAMPLES 10000

///////////////////////////////////////////////////////////////////////////////////

#include "MTIDataGenerator.h"
#include "MTISerial.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DLLEXPORT MTIDeviceParams
{
public:
		bool Success;						//read only
		char DeviceName[32];
		char FirmwareName[16];				//read only
		char CommType[16];					//read only
		char BluetoothMAC[16];				//read only
		unsigned int HardwareFilterOn;		//read only
		float VmaxMEMSDriver;				//read only
		unsigned int DeviceState;			//read only
		unsigned int DeviceErrorRegister;	//read only
		unsigned int USARTBaudRate;
		unsigned int SampleRate;
		unsigned int HardwareFilterBw;
		float VdifferenceMax;
		float Vbias;
		float XOffset;
		float YOffset;
		float DataScale;
		float DataRotation;
		unsigned int MEMSDriverEnable;
		unsigned int DigitalOutputEnable;
		unsigned int LaserModulationEnable;
		unsigned int BufferOffset;
		MTIAxes DeviceAxes;
		MTIBoot BootSetting;
		MTIDataMode DataMode;
		MTISync SyncMode;
		struct 
		{
			unsigned int SampleRate_Min;					// read only
			unsigned int SampleRate_Max;					// read only
			unsigned int SamplesPerFrame_Min;				// read only
			unsigned int SamplesPerFrame_Max;				// read only
			unsigned int HardwareFilterBw_Min;				// read only
			unsigned int HardwareFilterBw_Max;				// read only
			unsigned int FramesPerSecond_Min;				// read only
			unsigned int FramesPerSecond_Max;				// read only
			unsigned int VdifferenceMax_Min;				// read only
			unsigned int VdifferenceMax_Max;				// read only
			unsigned int Vbias_Min;							// read only
			unsigned int Vbias_Max;							// read only
		} DeviceLimits;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DLLEXPORT MTIAvailableDevices
{
public:
		char DeviceName[MTI_MAXDEVICES][32];				//read only
		char FirmwareName[MTI_MAXDEVICES][16];				//read only
		char CommType[MTI_MAXDEVICES][16];					//read only
		unsigned int USARTBaudRate[MTI_MAXDEVICES];				//read only
		unsigned int CommPortNumber[MTI_MAXDEVICES];		//read only
		char CommPortName[MTI_MAXDEVICES][10];				//read only
		float VmaxMEMSDriver[MTI_MAXDEVICES];				//read only
		unsigned int NumDevices;							//read only
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DLLEXPORT MTITrackParams
{
public:
	bool Success;
	float Threshold;
	int NormalGain;
	int TangentialGain;
	unsigned int BufferDelay;
	float HitRatio;
	unsigned int EnableSearch;
	unsigned int EnableOffsetStreaming;
	unsigned int EnableTrack;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DLLEXPORT MTITrackStatus
{
public:
	bool Success;
	bool TrackLocked;
	float XOffset;
	float YOffset;
	unsigned int HitCount;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
class DLLEXPORT MTIDevice
{

protected:
	MTIError			m_LastError;
	MTIDeviceParams		*m_pParams;
	MTITrackParams		*m_pTrackParams;

	MTISerialIO*			mConnectedSocket;	
	unsigned int			m_iIStop;
	float					m_fXStop, m_fYStop;
	unsigned int			m_iMStop;
	unsigned int			mBytesPerSample;


private:

	void SetDeviceName( char* text );

	void SetDigitalOutputEnable( unsigned int digitalOutputEnable );

	void SetLaserModulationEnable( unsigned int laserModulationEnable );

	void SetHardwareFilterBw( unsigned int bw );

	void SetSampleRate( unsigned int sps );

	void SetDataScale( float amplitude );

	void SetDataRotation( float rotation );

	void SetDeviceAxes( MTIAxes deviceAxesSetting );

	void SetOutputOffsets( float xOffset, float yOffset );
	
	void SetBufferOffset( unsigned int offset );

	void SetMEMSDriverEnable( unsigned int status );

	void SetVdifferenceMax( float vMax );

	void SetVbias( float vBias );

	unsigned int CalcHardwareFilterDelay( unsigned int numSamples );

	void SetBootParams( MTIBoot bootmode );
	
	void SetDataMode( MTIDataMode datamode );
	
	void SetSyncMode( MTISync datamode );

	void SetAnalogInputBufferLength(unsigned int BufferLength );

	void SetUSARTBaudRate( unsigned int baudrate );

	void PurgeSerialBuffers();

	void SendSerialCommand( bool requestConfirmation = true );

	void SendSerialCommandWithRequest();

	void GetDeviceState();

	//Verifies if a device is responding to serial commands
	bool IsDeviceResponding();

	void GetOutputOffsets();

	float LoadDeviceParam( const char* fileName, const char* paramName, float paramValue = 1e9f );

	unsigned int InterpolateDataTriangle( float* xKey, float* yKey, unsigned char* mKey, float* xSample, float* ySample, unsigned char* mSample, unsigned int numSamplePoints );

	std::string EnumToString( std::string enumName, int enumValue );

	int EnumToInt( std::string myEnum );

	void SetTrackThreshold( float Track_Threshold );
	void SetTrackNormalGain( int Track_NormalGain );
	void SetTrackTangentialGain( int Track_TangentialGain );
	void SetTrackBufferDelay( unsigned int Track_BufferDelay );
	void SetTrackHitRatio ( float Track_HitRatio );
	void SetTrackState ( unsigned int Track_State );

public:

	/////// MTI Device ///////
	
	//************ CREATING AND DELETING APPLICATION *************//
	//Create device instance in memory
	MTIDevice();

	~MTIDevice();

	//Deletes the device object from the memory
	void DeleteDevice();

	//************ OPENING THE PORT AND CONNECTING TO DEVICE, DISCONNECTIG AND CLOSING *************//
	//Opens the COM port and connects to the addressed device.
	void ConnectDevice( char* portName );

	//Stops communication and closes the COM port.
	void DisconnectDevice();

	//************ SEARCHING FOR AVAILBLE DEVICES AND THEIR INFO **************//
	//Searches for available devices to connect to at the host and returns
	//the devices with port settings. It tests for the maximum possible connection speed. 
	MTIAvailableDevices* GetAvailableDevices();

	// Lists all available devices on COM Ports at the computer.
	void ListAvailableDevices( MTIAvailableDevices* table );

	//************ RESETTING CONNECTION AND DEVICE *************//
	//Clears the input buffer of the device. 
	void ClearInputBuffer();

	//Clears the SerialIO buffers and resets the communication. 
	void SendSerialReset();

	//Resets the device parameters to its default settings. Keeps all data in the device memory.
	void ResetDevice();

	//************ GETTING PARAMETERS AND FIRMWARE SETTINGS AND SAVING THEM *************//
	//Get all device parametes from the device (Writable settings and read only firmware values).
	MTIDeviceParams* GetDeviceParams();

	//Sends the complete device parameter structure to the device (including all settings).
	void SetDeviceParams( MTIDeviceParams *params );

	//Gets a single parameter from the device.
	float GetDeviceParam( MTIParam param, int paramID = 0 );

	//Sets a single parameter in the device. 
	void SetDeviceParam( MTIParam param, float paramValue1, float paramValue2=0.f );

	//Loads a single or multiple device parameters in the parameter structure from a file (by default "mtidevice.ini"). 
	MTIDeviceParams* LoadDeviceParams( const char* fileName );
	
	//Saves the complete parameter structure into a file.
	void SaveDeviceParams( 	char* fileName );
	
	//************ GETTING PARAMETERS AND FIRMWARE SETTINGS AND SAVING THEM *************//
	//Get all device parametes from the device (Writable settings and read only firmware values).
	MTITrackParams* GetTrackParams();

	//Sends the complete device parameter structure to the device (including all settings).
	void SetTrackParams( MTITrackParams *params );

	// get back the integration values for tuning parameters
	void GetTrackIntegrals( int &TrackIntegralX, int &TrackIntegralY );

	MTITrackStatus* GetTrackStatus();

	//Loads a single or multiple device parameters in the parameter structure from a file (by default "mtidevice.ini"). 
	//MTIDeviceParams* LoadDeviceParams( char* fileName );
	
	//Saves the complete parameter structure into a file.
	//void SaveDeviceParams( 	char* fileName );

	//************ OPERATING THE DEVICE **************//
	//Stops the data output operation of the device. Sampling stops and object obtains info about the last sample output.
	void StopDataStream( );						

	//After MTIStopDataStream, returns the last outputted X point where the device stopped.
	float GetXStop();

	//After MTIStopDataStream, returns the last outputted Y point where the device stopped.
	float GetYStop();

	//After MTIStopDataStream, returns the last outputted digital output where the device stopped.
	unsigned char GetMStop();

	//After MTIStopDataStream, returns the last outputted sample index, where the device stopped.
	unsigned int GetIStop();

	//Sends (x, y) coordinates, modulation data and additional settings for the output operation to the device.
	//By default, the device will start outputting the data after everything is received.  
	void SendDataStream( float* x, float* y, unsigned char* m, unsigned int numSamples, unsigned int delaySamples = 0, bool minimizeJump = true );

	//Starts the output operation of the device. If repeatCount = 0, it repeats infinitely from 1 to 32.
	void StartDataStream( int repeatCount = -1 );

	//Resets the MEMS device position back to its origin. 
	//Creates sample data from the current position to the origin to move the mirror back.
	void ResetDevicePosition( );
	
	//MEMS device position will be changed from present position to new (x, y) in the time(mSec).
	// If running, stops operation and creates points for the mirror to move to the new (x, y) 
	// in the time requested (Recommend time >5ms). If time of mSec is not entered, the function will default 
	// to 1ms although the resulting device response may be slower based on the hardware filter parameters.
	void GoToDevicePosition( float x, float y, unsigned char m, unsigned int mSec);

	//Verifies if a device is connected and ready. 
	bool IsDeviceConnected();

	//Verifies if the output operation is presently running and generating samples.
	bool IsDeviceRunning();

	//Verifies if the output operation is presently running and generating samples.
	bool IsTrackingSupported();

	//Returns the last error. Called after each communication with the device to verify correct transfer.
	MTIError GetLastError();

	//Samples immediately one value from Analog Input Channel 0 or 1.
	float GetAnalogInputValue( unsigned int ChannelNumber );

	//Samples immediately one value from Analog Input Channel 0, demodulated over one sample.
	//For proper function SyncMode should be OutputSampleClock, so laser will modulate on/off in each sample
	float GetPhotoDetectorValue();

	//Gets the sampled values from channel 1 or 2. (Obtained before via MTIDataMode parameter).
	void GetAnalogInputBuffer( float* AI0, float* AI1, unsigned int DataLength );

	//Gets the sampled values from channel 1 or 2 as they stream.  Get as many as are available, return how many were obtained.
	unsigned int GetAnalogInputStream( float* AI0, float* AI1, unsigned int DataLength = 0 );

	//Gets the  samples remaining in data buffer
	unsigned int GetSamplesRemaining();

	//Sends settings to the target to save params, data, or both to flash memory.
	void SaveToFlash( MTIFlash flashsave );

	void SetDefaultDeviceName( char* text, long pass = 0 );

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////////////////

#endif