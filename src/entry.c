#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <malloc.h>
#include <dynamic_libs/os_functions.h>
#include <dynamic_libs/sys_functions.h>
#include <dynamic_libs/padscore_functions.h>
#include "common.h"

int __entry_menu(int argc, char **argv)
{
    InitOSFunctionPointers();
	InitSysFunctionPointers();
	InitPadScoreFunctionPointers();

	unsigned long long sysmenu = _SYSGetSystemApplicationTitleId(0);
	if(OSGetTitleID() != sysmenu)
	{
		//CMPT only seems to work properly from system menu
		SYSLaunchMenu();
		return EXIT_RELAUNCH_ON_LOAD;
	}

	//get all the CMPT functions
	unsigned int cmpt_handle;
	OSDynLoad_Acquire("nn_cmpt.rpl", &cmpt_handle);

	int (*CMPTLaunchTitle)(void* CMPTConfigure, int ConfigSize, int titlehigh, int titlelow);
	int (*CMPTAcctSetScreenType)(int screenType);
	int (*CMPTGetDataSize)(int* dataSize);
	int (*CMPTCheckScreenState)();

	OSDynLoad_FindExport(cmpt_handle, 0, "CMPTLaunchTitle", &CMPTLaunchTitle);
	OSDynLoad_FindExport(cmpt_handle, 0, "CMPTAcctSetScreenType", &CMPTAcctSetScreenType);
	OSDynLoad_FindExport(cmpt_handle, 0, "CMPTGetDataSize", &CMPTGetDataSize);
	OSDynLoad_FindExport(cmpt_handle, 0, "CMPTCheckScreenState", &CMPTCheckScreenState);

	//1 = TV Only, 2 = GamePad Only, 3 = Both
	CMPTAcctSetScreenType(1); 
	if(CMPTCheckScreenState() < 0)
	{
		CMPTAcctSetScreenType(2);
		if(CMPTCheckScreenState() < 0)
			CMPTAcctSetScreenType(3);
	}

	int datasize;
	int result = CMPTGetDataSize(&datasize);
	if(result < 0)
		goto prgEnd;

	//needed for CMPT to work
	KPADInit();

	void *databuf = memalign(0x40, datasize);
	//Nintendont forwarder
	CMPTLaunchTitle(databuf, datasize, 0x00010001, 0x57574e44);
	free(databuf);

prgEnd:
	//will launch vwii if launchtitle was successful
	return EXIT_SUCCESS;
}