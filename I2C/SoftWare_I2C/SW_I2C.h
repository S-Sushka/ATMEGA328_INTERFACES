#ifndef SW_I2C_H_
#define SW_I2C_H_

#include <Arduino.h>

class SoftWare_I2C
{
	uint8_t SDA_PIN = 0;
	uint8_t SCL_PIN = 0;
	
	void send_1();
	void send_0();
	uint8_t readByte();
	
	
	void send_ACK();
	void send_NACK();
	void del();
	
public:
	SoftWare_I2C(uint8_t _SDA_PIN, uint8_t _SCL_PIN);
	
	void startCondition();
	void stopCondition();
	void startCondition(uint8_t address);
	
	void write(uint8_t data);
	
	uint8_t read();
	uint8_t readLastByte();
	
	void setSDA(uint8_t _SDA_PIN);
	void setSCL(uint8_t _SCL_PIN);
};

#endif
