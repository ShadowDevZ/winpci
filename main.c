#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <SetupAPI.h>
#pragma comment(lib, "SetupApi.lib")


//todo add option to arguments
BOOL PCI_INFO() {
	int i = 0;
	    
	    DWORD dwSize, dwPropertyRegDataType;
	    HDEVINFO hdev;
	    SP_DEVINFO_DATA data;
	    WCHAR buffer[1024];
	
	    hdev = SetupDiGetClassDevsW(NULL, L"PCI", NULL, DIGCF_PRESENT | DIGCF_ALLCLASSES);    // List all connected PCI devices
	    if (hdev == INVALID_HANDLE_VALUE) return FALSE;
	    
	    for (i = 0;i < 99;i++)
	    {
	        data.cbSize = sizeof(data);
	        if (!SetupDiEnumDeviceInfo(hdev, i, &data)) break;
	       
	        SetupDiGetDeviceRegistryPropertyW(hdev, &data, SPDRP_HARDWAREID, &dwPropertyRegDataType, (BYTE*)buffer, sizeof(buffer), &dwSize);
			wprintf(L"[%s] ", buffer);

			SetupDiGetDeviceRegistryPropertyW(hdev, &data, SPDRP_DEVICEDESC, &dwPropertyRegDataType, (BYTE*)buffer, sizeof(buffer), &dwSize);
			wprintf(L"%s\n", buffer);

	       //SetupDiGetDeviceRegistryProperty(hdev, &data, SPDRP_LOCATION_INFORMATION, &dwPropertyRegDataType, (BYTE*)buffer, sizeof(buffer), &dwSize);
			//printf(" [LOCATION] %s \n", buffer);
	      
		
	    }
		SetupDiDestroyDeviceInfoList(&data);
	   
	    return TRUE;

}
BOOL PCI_INFO_EX() {
	int devcount = 0;

	DWORD dwSize, dwPropertyRegDataType;
	HDEVINFO hdev;
	SP_DEVINFO_DATA data;
	WCHAR buffer[1024];

	hdev = SetupDiGetClassDevsW(NULL, L"PCI", NULL, DIGCF_PRESENT | DIGCF_ALLCLASSES);    // List all connected PCI devices
	if (hdev == INVALID_HANDLE_VALUE) return FALSE;
	

	data.cbSize = sizeof(data);
	
	
	while (SetupDiEnumDeviceInfo(hdev, devcount, &data)) {

		SetupDiGetDeviceRegistryPropertyW(hdev, &data, SPDRP_HARDWAREID, &dwPropertyRegDataType, (BYTE*)buffer, sizeof(buffer), &dwSize);
		wprintf(L"[%s] ", buffer);

		SetupDiGetDeviceRegistryPropertyW(hdev, &data, SPDRP_DEVICEDESC, &dwPropertyRegDataType, (BYTE*)buffer, sizeof(buffer), &dwSize);
		wprintf(L"%-40s ", buffer);

		SetupDiGetDeviceRegistryPropertyW(hdev, &data, SPDRP_LOCATION_INFORMATION, &dwPropertyRegDataType, (BYTE*)buffer, sizeof(buffer), &dwSize);
		wprintf(L"%s \n\n", buffer);
		++devcount;
	}
	
	SetupDiDestroyDeviceInfoList(&data);
	
	return TRUE;

}


int main(void) {
	PCI_INFO_EX();
	return 0;
	

}

