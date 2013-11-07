#include <stdlib.h>
#include "sdc_sdk.h"
#include "lrd_sdk_pil.h"

LRD_WF_PilInfo pil_info = {
	.api_version =  PIL_API,  // do not modify
	.company_name = "example corp",
	.version_string = "example pil library version 1.0",
	.serial_number = 0,
	.product_id = 0,
	.data = NULL,
};

SDCERR LRD_WF_PIL_Init()
{
	pil_info.serial_number = "00000001";
	pil_info.product_id = "example 1.0";
	if((pil_info.data = malloc(1024)))
		return SDCERR_SUCCESS;
	return SDCERR_INSUFFICIENT_MEMORY;
}

SDCERR LRD_WF_PIL_Deinit()
{
	if (pil_info.data)
		free(pil_info.data);
	return SDCERR_SUCCESS;
}

static REG_DOMAIN myStoredRd = REG_WW;
SDCERR LRD_WF_PIL_GetRegDomain( unsigned long * regDomain )
{
	if(regDomain==NULL)
		return SDCERR_INVALID_PARAMETER;
	*regDomain = myStoredRd;
	return SDCERR_SUCCESS;
}

SDCERR LRD_WF_PIL_SetRegDomain( unsigned long regDomain )
{
	myStoredRd = regDomain;
	return SDCERR_SUCCESS;
}


