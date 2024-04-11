#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <string.h>

class UART_interface
{	
public:
	void begin(uint32_t speed);

	bool available();
	
	
	void write(uint8_t data);	
	uint8_t read();
	
	
	void print(char symbol);
	void print(const char *string);
	
	void print(int8_t number);
	void print(int16_t number);
	void print(int32_t number);
	void print(uint8_t number);
	void print(uint16_t number);
	void print(uint32_t number);
	
	
	void println(char symbol);
	void println(const char *string);
	
	void println(int8_t number);
	void println(int16_t number);
	void println(int32_t number);
	void println(uint8_t number);
	void println(uint16_t number);
	void println(uint32_t number);
	
};

#endif /* UART_H_ */

#ifndef F_CPU
# warning "F_CPU not defined for <I2C.h>"
# define F_CPU 16000000UL
#endif
