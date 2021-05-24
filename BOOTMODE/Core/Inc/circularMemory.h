/*
 * circularMemory.h
 *
 *  Created on: 7 Nis 2021
 *      Author: kerim
 */

#ifndef INC_CIRCULARMEMORY_H_
#define INC_CIRCULARMEMORY_H_
#include <stdio.h>
#include <string.h>
#define MAXMEMORYSIZE	100

#pragma pack(push, 1)
typedef struct
{
	char SOF;
	uint16_t commandNO;           	/*Emir numarasi*/
	uint8_t slaveNO;          		/*Birim slave numarasi */
	uint32_t commandAdress;        	/*Emir Adresi*/
	uint8_t R_W;        				/*Read/Write*/
	uint8_t datatype;      				/*Data Tipi */
    uint32_t command;				/*Data*/
	char EOFF;
}MypacketTypedef;
#pragma pack(pop)

MypacketTypedef Mypacket;

#pragma pack(push, 1)
typedef struct
{
	uint16_t cycle;
	uint16_t head;
	uint16_t tail;
	uint16_t WrongPacketCount;
	uint16_t MissingPacketCount;
	MypacketTypedef buffer[MAXMEMORYSIZE];
}MypacketCBufTypedef;
#pragma pack(pop)


void CBufINIT(MypacketCBufTypedef*MyCBuf);
int CBufIsEmpty(MypacketCBufTypedef*MyCBuf);
//int CBufGetIndex(MypacketCBufTypedef*MyCBuf);
int CBufGetTail(MypacketCBufTypedef*MyCBuf);
int CBufGetHead(MypacketCBufTypedef*MyCBuf);
int CBufRead(MypacketCBufTypedef*MyCBuf,MypacketTypedef*MyPacket);
int CBufWrite(MypacketCBufTypedef*MyCBuf,MypacketTypedef*MyPacket);
void CircularIndexCTRL(MypacketCBufTypedef*MyCBuf);


#endif /* INC_CIRCULARMEMORY_H_ */
