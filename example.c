/*

Copyright (c) 2013, Laird

Permission to use, copy, modify, and/or distribute this software for any 
purpose with or without fee is hereby granted, provided that the above 
copyright notice and this permission notice appear in all copies.
THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES 
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF 
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY 
SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES 
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN 
CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

*/

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
SDCERR LRD_WF_PIL_GetRegDomain( REG_DOMAIN * regDomain )
{
	if(regDomain==NULL)
		return SDCERR_INVALID_PARAMETER;
	*regDomain = myStoredRd;
	return SDCERR_SUCCESS;
}

SDCERR LRD_WF_PIL_SetRegDomain( REG_DOMAIN regDomain )
{
	myStoredRd = regDomain;
	return SDCERR_SUCCESS;
}


