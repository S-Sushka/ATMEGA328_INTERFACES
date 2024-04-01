#include "I2C.h"

I2C_interface::I2C_interface(uint32_t speed) 
{
	TWBR = ((F_CPU/speed)-16)/2;
}


void I2C_interface::startCondition() 
{
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    while(!(TWCR & (1<<TWINT)));	
}

void I2C_interface::stopCondition() 
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
    while(TWCR & (1<<TWSTO));
}

void I2C_interface::startCondition(uint8_t address) 
{
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    while(!(TWCR & (1<<TWINT)));

	write(address);
}


void I2C_interface::write(uint8_t data) 
{
    TWDR = data;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while(!(TWCR & (1<<TWINT)));	
}


uint8_t I2C_interface::read() 
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}

uint8_t I2C_interface::readLastByte() 
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}