
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
	CBufINIT(&CBuf);
    if(HAL_UART_Receive_DMA (&huart4, UART1_rxBuffer, 15)==HAL_OK){
    	state=INITSUCCESS;
    }else{
    	state=INITERROR;
    }
    return state;

}

/**********************************************************************************************************************/
parser_status ReceiveCommandFrom_UART(){

	parser_status state = waiting_data;
	if(!CBufRead(&CBuf,&parser)){
		boootdata[saafy]=parser.command;
		saafy++;
	}


	if(TState==HAL_OK){

		TState=HAL_BUSY;
		memcpy(&parser,&UART1_rxBuffer[0],15);


		if(parser.SOF==START_Condition && parser.EOFF==STOP_Condition){
			state=Receive_OK;
		}else{
			state=WrongDataPacket;
		}


}else
{
	state=Receive_ERROR;
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
		while(!CBufRead(&CBuf,&parser)){
			state=process_complated;
			switch(parser.commandNO)
			{
			case BootCommand:
				JumpTo(BootSystemFlashAddr);
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




/**********************************************************************************************************************/

