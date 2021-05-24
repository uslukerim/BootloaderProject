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


/********************************************************************************************************/
/*Global olarak kullanılan sabitler*/

#define	START_Condition	((uint8_t)0xA3) //Baslangic kosulu
#define	STOP_Condition	((uint8_t)0x25) //Bitis kosulu
#define MyDevice		((uint8_t)0x1)

#define readSTATE		((uint8_t)0x3)	// slave den deger okunmak istendiginde kullanılır
#define waitSTATE		((uint8_t)0x2)	// slave den deger okunma işlemi tamamlandıgında,
										//4 byte dan daha fazla veri okumamak için kullanılır.
#define writeSTATE		((uint8_t)0x1)	// slave den deger okunmak istendiginde kullanılır

#define BOOTCOMMAND		((uint8_t)0x1)


/********************************************************************************************************/
/*UART veri alımında kullanılan değişkenler */
uint8_t rx_command_count,rx_command_buffer[4],rx_buffer[20],rx_index,rx_data,Transfer_cplt,command_cplt,buffer[20],len;
uint8_t UART1_rxBuffer [ 100 ] ;
uint32_t boootdata[1500];
uint16_t saafy;

/********************************************************************************************************/
/*komut paketinin alımı için oluşturulmuş yapı
#pragma pack(push, 1)
typedef struct
{
  char SOF;
  uint16_t commandNO;
  uint8_t slaveNO;
  uint32_t commandAdress;
  uint8_t R_W;
  uint8_t datatype;
  uint32_t command;
  char EOFF;
}pars;*/
//#pragma pack(pop)

//pars parser;
/********************************************************************************************************/

typedef enum
{
	BootCommand,
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
	Receive_OK	,
	Receive_TIMEOUT	,
	Receive_ERROR,
	waiting_commands,
	process_complated,
	read_cptl_from_slave,
	transmitCommands,
	waiting_data,
	Transmit_ERROR,
	requestedData_sent,
	WrongDataPacket,



}parser_status;

parser_status UARTParserInit();
parser_status ReceiveCommandFrom_UART();//15 bytelık komut setinin uart üzerinden okunması ve ayıklanması işlemlerini yapar.
parser_status TransmitCommandVia_UART(MypacketTypedef *transmit);//Belirlenen 15 bytelık komut setinin uart üzerinden ilgili birime gönderimini yapar.
parser_status Commands_Processing();//ReceiveCommandFrom_UART() fonksiyonu ile alınan komut setini uygulamaya geçirir.
/********************************************************************************************************/


#endif /* INC_UART_PARSER_H_ */
