#include "SW_I2C.h"

SoftWare_I2C::SoftWare_I2C(uint8_t _SDA_PIN, uint8_t _SCL_PIN) 
{	
	setSDA(_SDA_PIN);
	setSCL(_SCL_PIN);
} 



void SoftWare_I2C::startCondition() 
{
	// RESET LINES
	digitalWrite(SCL_PIN, 0);
	digitalWrite(SDA_PIN, 0);
	
	
	digitalWrite(SCL_PIN, 1);
	
	digitalWrite(SDA_PIN, 1);
	digitalWrite(SDA_PIN, 0);
	
	digitalWrite(SCL_PIN, 0);
	
}

void SoftWare_I2C::stopCondition() 
{
	// RESET LINES
	digitalWrite(SCL_PIN, 0);
	digitalWrite(SDA_PIN, 0);
	
	
	digitalWrite(SCL_PIN, 1);
	
	digitalWrite(SDA_PIN, 0);
	digitalWrite(SDA_PIN, 1);
	
	digitalWrite(SCL_PIN, 0); 
	digitalWrite(SDA_PIN, 0); // !
}

void SoftWare_I2C::startCondition(uint8_t address) 
{
	startCondition();
	write(address);
}



void SoftWare_I2C::write(uint8_t data) 
{
	uint8_t mask = 0x80;
	
	for (uint8_t i = 0; i < 8; i++) 
	{	
		if ((data & mask) == 0) 
			send_0(); 
		else 
			send_1();
		
		mask >>= 1;
	} 
	send_ACK();
}


uint8_t SoftWare_I2C::read() 
{
	uint8_t result = readByte();
	send_ACK();
	return result;
}

uint8_t SoftWare_I2C::readLastByte() 
{
	uint8_t result = readByte();
	send_NACK();
	return result;
}


void SoftWare_I2C::send_ACK() 
{
	digitalWrite(SDA_PIN, 0);
	
	digitalWrite(SCL_PIN, 1);
	digitalWrite(SCL_PIN, 0); 
}

void SoftWare_I2C::send_NACK() 
{
	digitalWrite(SDA_PIN, 1);

	digitalWrite(SCL_PIN, 1);
	digitalWrite(SCL_PIN, 0);
}



void SoftWare_I2C::send_0() 
{
	digitalWrite(SDA_PIN, 0);
	
	// LATCH
	digitalWrite(SCL_PIN, 1);
	digitalWrite(SCL_PIN, 0);
}

void SoftWare_I2C::send_1() 
{	
	digitalWrite(SDA_PIN, 1);
	
	// LATCH
	digitalWrite(SCL_PIN, 1);
	digitalWrite(SCL_PIN, 0);
}

uint8_t SoftWare_I2C::readByte()
{
	uint8_t result = 0;
	
	pinMode(SDA_PIN, INPUT_PULLUP);
	
	digitalWrite(SCL_PIN, 1);	
	if (digitalRead(SDA_PIN) != 0)
		result |= 0x80;
	digitalWrite(SCL_PIN, 0);
	
	for (uint8_t i = 1; i < 8; i++) 
	{	
		digitalWrite(SCL_PIN, 1);
		if (digitalRead(SDA_PIN) != 0)
			result |= (0x80>>i);
		digitalWrite(SCL_PIN, 0);
	} 	
	
	pinMode(SDA_PIN, OUTPUT);
	
	return result;
}



void SoftWare_I2C::setSDA(uint8_t _SDA_PIN) 
{
	if (_SDA_PIN != -1) 
	{
		SDA_PIN = _SDA_PIN;
		pinMode(SDA_PIN, OUTPUT);	
	}	
}
void SoftWare_I2C::setSCL(uint8_t _SCL_PIN)
{
	if (_SCL_PIN != -1) 
	{
		SCL_PIN = _SCL_PIN;
		pinMode(SCL_PIN, OUTPUT);	
	}	
}