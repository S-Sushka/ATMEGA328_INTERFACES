#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>

class I2C_interface
{	
public:
	I2C_interface(uint32_t speed);	
	
	void startCondition();
	void stopCondition();
	void startCondition(uint8_t address);
	
	void write(uint8_t data);
	
	uint8_t read();
	uint8_t readLastByte();
};

#endif /* I2C_H_ */

#ifndef F_CPU
# warning "F_CPU not defined for <I2C.h>"
# define F_CPU 16000000UL
#endif
