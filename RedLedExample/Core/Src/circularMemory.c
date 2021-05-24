/*
 * circularMemory.c
 *
 *  Created on: 7 Nis 2021
 *      Author: kerim
 */

#include "circularMemory.h"

void CBufINIT(MypacketCBufTypedef*MyCBuf){

memset(&MyCBuf,0,sizeof(MyCBuf));

}
/***************************************************************************************************************/
int CBufRead(MypacketCBufTypedef*MyCBuf,MypacketTypedef*MyPacket){

	if(MyCBuf->buffer[MyCBuf->tail].SOF!=0){
		memcpy(&MyPacket,&MyCBuf->buffer[MyCBuf->tail],sizeof(MyPacket));
		memset(&MyCBuf->buffer[MyCBuf->tail],0,sizeof(MyCBuf->buffer[MyCBuf->tail]));
		MyCBuf->tail++;
		CircularIndexCTRL(MyCBuf);
		return 0;
	}else{
		return 1;

	}

}
/***************************************************************************************************************/

int CBufWrite(MypacketCBufTypedef*MyCBuf,MypacketTypedef*MyPacket){

	int state=0;
	if(MyCBuf->buffer[MyCBuf->head].SOF==0){
		memcpy(&MyCBuf->buffer[MyCBuf->head],MyPacket ,sizeof(MyCBuf->buffer[MyCBuf->head]));
		MyCBuf->head++;
		CircularIndexCTRL(MyCBuf);
		if(MyCBuf->head==MyCBuf->tail){
			MyCBuf->tail++;
		}
	}else{
		memcpy(&MyCBuf->buffer[MyCBuf->head],MyPacket ,sizeof(MyCBuf->buffer[MyCBuf->head]));
		MyCBuf->head++;
		MyCBuf->tail++;
		CircularIndexCTRL(MyCBuf);
		MyCBuf->MissingPacketCount++;
		state=1;
	}
	CircularIndexCTRL(MyCBuf);

	return state;

}
/***************************************************************************************************************/
void CircularIndexCTRL(MypacketCBufTypedef*MyCBuf){
	if(MyCBuf->head>=MAXMEMORYSIZE){
		MyCBuf->cycle++;
		MyCBuf->head=0;
		//return;
	}
	if(MyCBuf->tail>=MAXMEMORYSIZE){
		MyCBuf->tail=0;

	}

}



