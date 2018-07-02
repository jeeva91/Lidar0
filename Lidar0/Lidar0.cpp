
// program for the lidar to control the mirror, dely, and data acquistation.

// parameters needed for the program
//1. xy min default = -1
//2. xy max default = 1
//3. xy steps default = 0.1
//4. dly min default =0
//5. dly max default = 100
//6. dly steps 10
//7. integration time for the tdc default = 100
//8. filename to save
//9. Port to connect
//
//the program outputs a csv file 


#include "stdafx.h"
#include "lidar.h"

Ulong buffer[0x200000];

int main(int argc, char* argv[])
{
	float xy_min = -1;
	float xy_max = 1;
	float xy_steps = (float)0.1;
	float dly_min = 0;
	float dly_max = 100;
	float dly_steps = 10;
	int tdc_time = 100;		// in millisecond
	char filename[256] = "lidar.csv";
	char portno[5] = "COM5";

	if ((argc != 10) && (argc!=1)) {
		printf("Please give the correct number of inputs \n");
		printf("The number of inputs is %d\n", argc);
		exit(-1);
	}
	
	if (argc == 10) {
		xy_min = (float) atof(argv[1]);
		xy_max = (float) atof(argv[2]);
		xy_steps = (float) atof(argv[3]);
		dly_min = (float)atof(argv[4]);
		dly_max = (float)atof(argv[5]);
		dly_steps = (float)atof(argv[6]);
		tdc_time = atoi(argv[7]);	// in milli-sec
		strcpy_s(filename, argv[8]);
		strcpy_s(portno, argv[9]);

	}

	printf("The xy ranges from %f to %f and will be incremented in %f steps\n", xy_min, xy_max, xy_steps);
	printf("The delay ranges from %f to %f and will be incremented in %f steps\n", dly_min, dly_max, dly_steps);
	printf("The integration time of the tdc is %d\n", tdc_time);
	
	// Initialize the optical delay
	unsigned int dly_ud;
	int dly_status;
	
	printf("Connecting to the delay at address 5\n");

	dly_ud = ibdev(DLY_BOARDID, DLY_PRIMARYADD, DLY_SECONDARYADD, DLY_TIMEOUT, DLY_EOS, DLY_EOT);
	if (dly_ud == -1) {
		printf("Unable to connect to the delay device\n");
		exit(-1);
	}
	else
		printf("connected to the delay device\n");
	
	// Initialize the MEMS mirror
	printf("creating a new mti\n");
	MTIDevice *mti = new MTIDevice();
	MTIError LastError;

	printf("connecing to the %s\n", portno);
	mti->ConnectDevice(portno);
	MTIDeviceParams *params = mti->GetDeviceParams();
	LastError = mti->GetLastError();
	if (LastError != MTIError::MTI_SUCCESS) {
		printf("Error in connecting to the device in the %s\n", portno);
		exit(-1);
	}
	else printf("Connected to the mirror\n");
	
	//change the device specific parameters
	params->VdifferenceMax = 125;
	params->HardwareFilterBw = 140;
	params->Vbias = 80;
	//change the user related parameters
	params->DataMode = MTIDataMode::Sample_Output;			// this is default mode, shown here for demo
	params->DataScale = 1;								// example of scaling data/content to 80%
	params->SampleRate = 20000;
	params->DeviceAxes = MTIAxes::Normal;					// this is default mode, shown here for demo
	params->SyncMode = MTISync::Output_DOut0;
	params->DataRotation = 0;

	//set the above changed parameters
	mti->SetDeviceParams(params);
	mti->SetDeviceParam(MTIParam::MEMSDriverEnable, true);
	LastError = mti->GetLastError();
	if (LastError != MTIError::MTI_SUCCESS) {
		printf("Error in changing the device parameters\n");
		exit(-1);
	}

	mti->ResetDevicePosition(); 				// send analog outputs (and device) back to origin in 25ms
	LastError = mti->GetLastError();
	if (LastError != MTIError::MTI_SUCCESS) {
		printf("Error in reseting the device\n");
		exit(-1);
	}

	//TDC initialization
	HRM_STATUS error;
	Uword tcspc, delay, chann;
	Uword period, clock;
	Ulong moduleCount, offset, range, i, j, k;
	HANDLE hdl[10];
	FILE *fl, *fl2;
	USHORT srData;
	/*
	Initialise variables and clear error report
	*/
	error = HRM_OK;
	tcspc = 1;
	//delay = 0;
	chann = 0x9999;
	period = 2000;
	HRM_GetLastError(HRM_OK);
	/*
	Detect the number of HRM-TDC modules
	*/
	if (error == HRM_OK)
	{
		HRM_RefreshConnectedModuleList();
		moduleCount = (Ulong)HRM_GetConnectedModuleCount();
	}
	/*
	If a module is present connect to the first module.
	If no module, set error and reason in last error report.
	*/
	if (error == HRM_OK)
	{
		if (moduleCount)
			HRM_GetConnectedModuleList(hdl);
		else
		{
			HRM_GetLastError(HRM_OPEN_USB);
			error = HRM_ERROR;
		}
	}
	/*

	Set the clock frequency.

	if (error == HRM_OK)
	error = HRM_SetFrequencySelectionRegister(hdl[0], clock);
	/*
	Set the channel edge enables.
	*/
	if (error == HRM_OK)
		error = HRM_SetEdgeSensitivityRegister(hdl[0], chann);
	
	fopen_s(&fl, filename, "w+t");
	fprintf(fl, "delay, y, x, counts\n ");
	
	for (float yitr = xy_min; yitr <= xy_max; yitr = yitr + xy_steps) 
	{
		for (float xitr = xy_min; xitr <= xy_max; xitr = xitr + xy_steps) 
		{
			mti->SendDataStream(&xitr, &yitr, &out, 1);

			LastError = mti->GetLastError();
			if (LastError != MTIError::MTI_SUCCESS) 
			{
				printf("Error settinglocation");
			}
	
			for (float dly_itr = dly_min; dly_itr <= dly_max; dly_itr = dly_itr + dly_steps) 
			{
				auto comm = std::to_string(dly_itr);
				comm = "DLY " + comm;
				unsigned char out = OUTCHAR;
				ibwrt(dly_ud, comm.c_str(), comm.length());
				/*
				Clear the memory.
				*/
				if (error == HRM_OK)
					error = HRM_InitMemory(hdl[0], 0, 0x200000, 0);
				/*
				Start the histogram running.
				*/
				
				if (error == HRM_OK)
					error = HRM_StartHistogramFSM(hdl[0], tcspc, 0);
				/*
				Run the histogram for the programmed time in ms.
				*/
				
				// use QueryPerformanceCounter later
				LARGE_INTEGER start;
				LARGE_INTEGER stop;
				LARGE_INTEGER freq;
				QueryPerformanceFrequency(&freq);
				double frequency = (double)freq.QuadPart;
				if (error == HRM_OK)
					for (i = QueryPerformanceCounter(&start); ((double)(QueryPerformanceCounter(&stop) - i))/frequency < tdc_time;);
				/*
				Stop the histogram process.
				*/
				if (error == HRM_OK)
					error = HRM_SetModeBitsRegister(hdl[0], 0x0030);

				/*
				Read all the memory into the buffer.
				*/
				if (error == HRM_OK)
					error = HRM_ReadMemory(hdl[0], 0x0030, 0, 0x200000, (BYTE*)buffer);
				/*
				Open the file and set the headings.
				*/
				if (error == HRM_OK) 
				{
					for (i = 0, j = 0, k = 0; i != MEMORY_SZ; i++)
					{
						j = (j == 0 && buffer[i]) ? i : j;
						k = (Ulong)(k + buffer[i]);
					}
					fprintf(fl, "%f,%f,%f,%d\n", dly_itr, yitr, xitr, k);

				}
			}
		}
	}
	if (fl)
		fclose(fl);
	printf("closing the mirror connection\n");

	// End the program by returning the device to origin
	mti->ResetDevicePosition(); // send analog outputs (and device) back to origin in 25ms
	mti->SetDeviceParam(MTIParam::MEMSDriverEnable, false);		// turn off the MEMS driver
	mti->DisconnectDevice();
	mti->DeleteDevice();
	ibonl(dly_ud, 0);




		
    return 0;
}

