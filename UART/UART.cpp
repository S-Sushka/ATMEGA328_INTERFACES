#include <USART.h>

void USART_interface::begin(uint32_t speed) 
{
	speed = (F_CPU/(16*speed)-1) ;
	
	UBRR0H = (uint8_t)(speed >> 8);
	UBRR0L = (uint8_t)(speed & 0xFF);
	
	UCSR0A = 0;						// Асинхронный режим, 1 стоповый бит, без проверки четности
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);					// Включаем передатчик
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00) | (1<<UCPOL0);	// 8 бит данных
}


bool USART_interface::available() 
{
	return (UCSR0A & (1<<RXC0));
}


void USART_interface::write(uint8_t data)
{
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

uint8_t USART_interface::read() 
{
	UCSR0A &= ~(1<<RXC0);
	
	while (!(UCSR0A & (1<<RXC0)));
	return UDR0;
}



// -------------
// >>> PRINT <<<
// -------------

void USART_interface::print(char symbol) 
{
	write(symbol); 
}

void USART_interface::print(const char *string) 
{
	uint16_t length = strlen(string);
	
	for (uint16_t i = 0; i < length; i++) 
		write(string[i]);
}



void USART_interface::print(int8_t number) 
{	
	if (number < 0) 
	{
		write('-');
		print((uint32_t)(number*-1));
	}
	else
		print((uint32_t)number);		
}

void USART_interface::print(int16_t number) 
{	
	if (number < 0) 
	{
		write('-');
		print((uint32_t)(number*-1));
	}
	else
		print((uint32_t)number);		
}

void USART_interface::print(int32_t number) 
{	
	if (number < 0) 
	{
		write('-');
		print((uint32_t)(number*-1));
	}
	else
		print((uint32_t)number);		
}

void USART_interface::print(uint8_t number) 
{
	print((uint32_t)number);
}

void USART_interface::print(uint16_t number) 
{
	print((uint32_t)number);
}

void USART_interface::print(uint32_t number) 
{
	char numberAsString[10] = {0};
	uint8_t pointer = 9;

	bool showZero = false;
	
	
	while (number > 0) 
	{
		numberAsString[pointer] = number % 10;
		
		number /= 10;
		pointer--;
	}	
	
	
	for (uint8_t i = 0; i < 10; i++) 
	{
		if (numberAsString[i] > 0 || showZero) 
		{
			showZero = true;
			write(numberAsString[i] + 0x30);
		}
	}
}



// ---------------
// >>> PRINTLN <<<
// ---------------

void USART_interface::println(char symbol) 
{
	write(symbol); 
	write('\n'); 
}

void USART_interface::println(const char *string) 
{
	uint16_t length = strlen(string);
	
	for (uint16_t i = 0; i < length; i++) 
		write(string[i]);
	
	write('\n');
}



void USART_interface::println(int8_t number) 
{	
	if (number < 0) 
	{
		write('-');
		println((uint32_t)(number*-1));
	}
	else
		println((uint32_t)number);		
}

void USART_interface::println(int16_t number) 
{	
	if (number < 0) 
	{
		write('-');
		println((uint32_t)(number*-1));
	}
	else
		println((uint32_t)number);		
}

void USART_interface::println(int32_t number) 
{	
	if (number < 0) 
	{
		write('-');
		println((uint32_t)(number*-1));
	}
	else
		println((uint32_t)number);		
}

void USART_interface::println(uint8_t number) 
{
	println((uint32_t)number);
}

void USART_interface::println(uint16_t number) 
{
	println((uint32_t)number);
}

void USART_interface::println(uint32_t number) 
{
	char numberAsString[10] = {0};
	uint8_t pointer = 9;

	bool showZero = false;
	
	
	while (number > 0) 
	{
		numberAsString[pointer] = number % 10;
		
		number /= 10;
		pointer--;
	}	
	
	
	for (uint8_t i = 0; i < 10; i++) 
	{
		if (numberAsString[i] > 0 || showZero) 
		{
			showZero = true;
			write(numberAsString[i] + 0x30);
		}
	}
	
	write('\n');
}
