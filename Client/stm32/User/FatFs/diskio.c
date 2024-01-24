/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "stm32_eval_sdio_sd.h"
#include "string.h"

/* Definitions of physical drive number for each drive */
#define ATA		0	/* Example: Map Ramdisk to physical drive 0 */
#define SPI_Flash		1	/* Example: Map MMC/SD card to physical drive 1 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS status=STA_NOINIT;

	switch (pdrv) {
	case ATA :
	    status&=~STA_NOINIT;
		break;

	case SPI_Flash :
	   break;
	default:
	status=STA_NOINIT;
  }
	return status;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS status =STA_NOINIT;
	switch (pdrv)
	{
	case ATA:
	    if (SD_Init()==0)
		{
			status&=~STA_NOINIT;
		}
		else
		{
			status=STA_NOINIT;
		}
		break;
	case SPI_Flash:
		break;
	default:
		status =STA_NOINIT;
		break;
	}
	return status;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{   
	DRESULT status=RES_PARERR;
	SD_Error SD_state=SD_OK;
	switch (pdrv)
	{
		
	case ATA:
	    if ((DWORD)buff&3)
		{
			DRESULT res=RES_OK;
			DWORD scratch[512/4];
			while (count--)
			{
				res=disk_read(ATA,(void *)scratch,sector++,1);
				if (res!=RES_OK)
				{
					break;
				}
				memcpy(buff,scratch,512);
				buff+=512;
			}
			return res;
		}
		SD_state=SD_ReadMultiBlocks(buff,sector*512,512,count);
		if (SD_state==SD_OK)
		{
			SD_state=SD_WaitReadOperation();
			//while(SD_GetStatus()!=SD_TRANSFER_OK);
		}
		if (SD_state!=SD_OK)
		{
			status=RES_PARERR;
		}
		else
		    status=RES_OK;
		
		break;
	case SPI_Flash:
		break;
	default:
	    status = RES_PARERR;
		break;
	}
	return status;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT status=RES_PARERR;
	SD_Error SD_state=SD_OK;
	if (!count) {
		return RES_PARERR;		/* Check parameter */
	}

	switch (pdrv) {
		case ATA:	/* SD CARD */     
		      if ((DWORD)buff&3)
		{
			DRESULT res=RES_OK;
			DWORD scratch[512/4];
			while (count--)
			{
				memcpy(scratch,buff,512);
				res=disk_write(ATA,(void*)scratch,sector++,1);
			    if (res!=RES_OK)
			    {
				    break;
			    }
				buff+=512;
			}
			return res;
		}
		SD_state=SD_WriteMultiBlocks((uint8_t*)buff,sector*512,512,count);
		if (SD_state==SD_OK)
		{
			SD_state=SD_WaitReadOperation();
			while(SD_GetStatus()!=SD_TRANSFER_OK);
		}
		if (SD_state!=SD_OK)
		{
			status=RES_PARERR;
		}
		else
		    status=RES_OK;
		
		break;

		case SPI_Flash:
		break;
    
		default:
			status = RES_PARERR;
	}
	return status;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res = RES_PARERR;

	//int result;

	switch (pdrv) {
	case ATA :
			switch (cmd) 
			{
				// Get R/W sector size (WORD) 
				case GET_SECTOR_SIZE :    
					*(WORD * )buff = 512;
				break;
				
				// Get erase block size in unit of sector (DWORD)
				case GET_BLOCK_SIZE :      
					*(DWORD * )buff = SDCardInfo.CardBlockSize;
				break;

				case GET_SECTOR_COUNT:
					*(DWORD * )buff = SDCardInfo.CardCapacity/512;
					break;
				
				case CTRL_SYNC :
				break;
			}
			res = RES_OK;
			break;

	case SPI_Flash :
		break;
	
	default:
			res = RES_PARERR;
	}
	return res;
}

__weak DWORD get_fattime(void) {
	return	  ((DWORD)(2015 - 1980) << 25)	/* Year 2015 */
			| ((DWORD)1 << 21)				/* Month 1 */
			| ((DWORD)1 << 16)				/* Mday 1 */
			| ((DWORD)0 << 11)				/* Hour 0 */
			| ((DWORD)0 << 5)				  /* Min 0 */
			| ((DWORD)0 >> 1);				/* Sec 0 */

}
