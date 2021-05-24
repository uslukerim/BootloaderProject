/*
 * UART_Parser.h
 *
 *  Created on: Mar 30, 2021
 *      Author: Kerim_USLU
 */

#ifndef INC_UART_PARSER_H_
#define INC_UART_PARSER_H_

#include "stm32f4xx_hal.h"
#include "circularMemory.h"
#include "FlashManager.h"
#include <string.h>
UART_HandleTypeDef huart4;
HAL_StatusTypeDef TState;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
DMA_HandleTypeDef hdma_uart4_rx;
MypacketCBufTypedef CBuf;
MypacketTypedef TransmitPack;
MypacketTypedef parser;

uint8_t FlashErased;

/********************************************************************************************************/
/*Global olarak kullanılan sabitler*/

#define	START_Condition	((uint8_t)0xA3) //Baslangic kosulu
#define	STOP_Condition	((uint8_t)0x25) //Bitis kosulu
#define MyDevice		((uint8_t)0x1)

#define BOOTCOMMAND		((uint8_t)0x1)


/********************************************************************************************************/
uint8_t UART1_rxBuffer [ 15 ] ;
uint16_t saafy;

typedef enum
{
	BootCommand,
	UPDATESW,
	EraseFlash,
	JumpUserAPP,
	/*
	 *
	 *
	 */

} CommandNo;

/***********************************************************************************************/
/*parser algoritması fonksiyonları için oluşturulmuştur */

typedef enum
{//fonksiyonların kullandığı ve döndürdüğü sabitler
	INITSUCCESS,
	INITERROR,
	CMDDoesNotMatch,
	//UPDATESW,
	Receive_OK	,
	Receive_TIMEOUT	,
	Receive_ERROR,
	waiting_commands,
	process_complated,
	transmitCommands,
	waiting_data,
	Transmit_ERROR,



}parser_status;

parser_status UARTParserInit();
parser_status TransmitCommandVia_UART(MypacketTypedef *transmit);//Belirlenen 15 bytelık komut setinin uart üzerinden ilgili birime gönderimini yapar.
parser_status Commands_Processing();//Komut setini circular buffer'dan okuyarak gerekli işlemleri gerçeklestirir.
/********************************************************************************************************/


#endif /* INC_UART_PARSER_H_ */
