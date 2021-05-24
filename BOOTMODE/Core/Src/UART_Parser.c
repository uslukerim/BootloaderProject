
/*
 * UART_Parser.c
 *
 *  Created on: Mar 30, 2021
 *      Author: Kerim_USLU
 */

#include "UART_Parser.h"

#include "circularMemory.h"

/*********************************************************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)//UART üzerinden verilerin alımında kullanılır
{

    TState=HAL_UART_Receive_DMA(&huart4, UART1_rxBuffer, 15);
	memcpy(&parser,&UART1_rxBuffer,sizeof(parser));
    if(UART1_rxBuffer[0]==START_Condition && UART1_rxBuffer[14]==STOP_Condition){
    	memcpy(&Mypacket,&UART1_rxBuffer,sizeof(parser));
    	CBufWrite(&CBuf,&Mypacket);
    }else
    {
    	CBuf.WrongPacketCount++;
    }


}
/**********************************************************************************************************************/
parser_status UARTParserInit(){
	parser_status state;
	FlashErased=0;
	CBufINIT(&CBuf);
    if(HAL_UART_Receive_DMA (&huart4, UART1_rxBuffer, 15)==HAL_OK){
    	state=INITSUCCESS;
    }else{
    	state=INITERROR;
    }
    return state;

}



/**********************************************************************************************************************/

parser_status TransmitCommandVia_UART(MypacketTypedef *transmit){
	parser_status state = Transmit_ERROR;
	uint8_t commands[15];
	memcpy(&commands,transmit,15);
	if(HAL_UART_Transmit(&huart4, commands, 15,1000)==HAL_OK){
		state=transmitCommands;
	}else{
		state=Transmit_ERROR;

	}

	return state;
}



parser_status Commands_Processing(){//Gelen verilerin işlenmesi. Bu fonksiyon farklı kombinasyonlara göre özelleştirilebilir

	parser_status state = waiting_data;
	//uint32_t addr;
	MypacketTypedef TRPack;
	TRPack.SOF=START_Condition;
	TRPack.commandNO=EraseFlash;
	TRPack.slaveNO=1;
	TRPack.commandAdress=0x02;
	TRPack.datatype=1;
	TRPack.command=1;
	TRPack.R_W=0;
	TRPack.EOFF=STOP_Condition;
		while(!CBufRead(&CBuf,&parser)){
			state=process_complated;
			switch(parser.commandNO)
			{
			case BootCommand:
				if(!FlashErased){
					FlashErase(3,9);//Erase flash from  Segment 2 to Segment 11
					FlashErased=1;
					TransmitCommandVia_UART(&TRPack);

				}
				break;
			case UPDATESW:
				WriteProgram(parser.commandAdress, parser.command);
				break;
			case JumpUserAPP:
				HAL_FLASH_Lock();
				JumpTo(APPADDRESS);
				break;
				/*
				 *
				 *
				 */
			default:
				state=CMDDoesNotMatch;
				break;
			}
		}
		return state;
}
void isUpdateSW(){
	TransmitPack.SOF=START_Condition;
	TransmitPack.commandNO=BootCommand;
	TransmitPack.slaveNO=1;
	TransmitPack.commandAdress=0x02;
	TransmitPack.datatype=1;
	TransmitPack.command=1;
	TransmitPack.R_W=0;
	TransmitPack.EOFF=STOP_Condition;
	TransmitCommandVia_UART(&TransmitPack);


}
/**********************************************************************************************************************/

