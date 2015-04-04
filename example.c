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
#include <stdio.h>
#include <string.h>
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

//
// This example shows a possible method of storing and retrieving the 
// regulatory domain value.  The intent is to allow you to access a storage
// area that is not modifiable by the end user, and is also persistent
// in case you erase the file system, for example, with a system upgrade.
// Although the example uses a file on the file-system, other options 
// include an eeprom, uboot environment, or an area unique to your device.

#define Domain_File "/etc/summit/domain.txt"

SDCERR LRD_WF_PIL_GetRegDomain( REG_DOMAIN * regDomain )
{
	FILE *f;
	char key[256], set=0;
	int value;

	if(regDomain==NULL)
		return SDCERR_INVALID_PARAMETER;

	f = fopen(Domain_File, "r");
	if (f == NULL)
	{
		//TODO: debug log something like: perror("fopen for read");
		return SDCERR_FAIL;
	}

	while(!feof(f))
	{
		if (fscanf(f,"%s %d", key, &value) !=2)
		{
			break;
		}
		if (strcmp( key, "domain")==0)
		{
			*regDomain = (REG_DOMAIN) value;
			set = 1;
			break;
		}
	}

	fclose(f);

	if (set)
		return SDCERR_SUCCESS;
	return SDCERR_FAIL;
}

SDCERR LRD_WF_PIL_SetRegDomain( REG_DOMAIN regDomain )
{
	FILE *f;

	f=fopen(Domain_File, "w");

	if (f == NULL)
	{
		//TODO: debug log something like: perror("fopen for write");
		return SDCERR_FAIL;
	}
	fprintf(f, "domain %d\n", regDomain);

	fclose(f);

	return SDCERR_SUCCESS;
}
