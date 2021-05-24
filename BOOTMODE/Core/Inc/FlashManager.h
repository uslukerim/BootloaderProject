/*
 * FlashManager.h
 *
 *  Created on: 9 Nis 2021
 *      Author: kerim
 */

#ifndef INC_FLASHMANAGER_H_
#define INC_FLASHMANAGER_H_
#include "stm32f4xx_hal.h"
#define APPADDRESS 				((uint32_t)0x0800C000)//Sector3 addr
#define BootSystemFlashAddr		((uint32_t)0x08000000)
void FlashErase(uint8_t FromTheSegment,uint8_t SectorNB);
void WriteProgram(uint32_t AppADDR,uint32_t Program_Data);
typedef void (*pFunction)(void);
void JumpTo(uint32_t AppADDR);
//uint32_t ProgramWordArray[]
#endif /* INC_FLASHMANAGER_H_ */
