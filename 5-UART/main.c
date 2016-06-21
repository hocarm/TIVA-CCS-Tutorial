/*
 * Chuong trinh giao tiep uart voi may tinh, gui lan luot cac ki tu cua hocarm.org len may tinh
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

int main(void)
{
	// Thiet lap clock he thong
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	// Kich hoat uart0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	//Cau hinh chan PA0 va PA1 lan luot la chan RX va TX
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1); 	//Thieu dinh nghia pin pa1 pa0 la chan cua UART
	//Cau hinh uart 0 baud 115200
	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
	//Gui tung ki tu cua hocarm len may tinh
	UARTCharPut(UART0_BASE, 'H');
	UARTCharPut(UART0_BASE, 'O');
	UARTCharPut(UART0_BASE, 'C');
	UARTCharPut(UART0_BASE, 'A');
	UARTCharPut(UART0_BASE, 'R');
	UARTCharPut(UART0_BASE, 'M');
	UARTCharPut(UART0_BASE, '.');
	UARTCharPut(UART0_BASE, 'O');
	UARTCharPut(UART0_BASE, 'R');
	UARTCharPut(UART0_BASE, 'G');

	while(1)
	{
		if(UARTCharsAvail(UART0_BASE))
			UARTCharPut(UART0_BASE, UARTCharGet(UART0_BASE));
	}

	}