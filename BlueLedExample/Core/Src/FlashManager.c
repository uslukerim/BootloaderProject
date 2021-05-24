/*
 * FlashManager.c
 *
 *  Created on: 9 Nis 2021
 *      Author: kerim
 */
#include "FlashManager.h"

void FlashErase(uint8_t FromTheSegment,uint8_t SectorNB)
{
	static FLASH_EraseInitTypeDef EraseInitStruct;
	HAL_FLASH_Unlock();
	uint32_t SectorError = 0;
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
	EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	EraseInitStruct.Sector = FromTheSegment;
	EraseInitStruct.NbSectors = SectorNB;

	if(HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError) != HAL_OK)
	{
		     /*
		       Error occurred while sector erase.
		       User can add here some code to deal with this error.
		       SectorError will contain the faulty sector and then to know the code error on this sector,
		       user can call function 'HAL_FLASH_GetError()'
		     */
		     /*
		       FLASH_ErrorTypeDef errorcode = HAL_FLASH_GetError();
		     */

		Error_Handler();
	}
	HAL_FLASH_Lock();
}


void WriteProgram(uint32_t AppADDR,uint32_t Program_Data)
{
	uint32_t addr;
	if(AppADDR==0){
		HAL_FLASH_Unlock();
		addr=APPADDRESS;
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,addr, Program_Data);

	}else{
		addr=APPADDRESS+AppADDR*4;
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,addr, Program_Data);
	}
}
void JumpTo(uint32_t AppADDR){
	HAL_DeInit();
	pFunction Jump_To_Application = *( (pFunction*) (AppADDR + 4) );
	__set_CONTROL(0);
	SysTick->CTRL = 0; //disable SysTick
	SCB->VTOR = AppADDR;
	__set_MSP( *( (uint32_t*) AppADDR ) );
	Jump_To_Application();
}

