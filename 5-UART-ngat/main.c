/*
 * Chuong trinh giao tiep uart voi may tinh, su dung ngat chop tat LED khi co ki tu tu may tinh gui xuong
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"



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

	//Cau hinh ngat
	IntMasterEnable();	// Cho phep ngat master
	IntEnable(INT_UART0);	//Kich hoat ngat
	UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT); // Thuc hien ngat nhan du lieu

	//Cau hinh Ouput
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);		//Kich hoat portF
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2); // cau hinh output la PF2
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
	UARTCharPut(UART0_BASE, '\n');

	while(1)
	{
//		if(UARTCharsAvail(UART0_BASE))
//			UARTCharPut(UART0_BASE, UARTCharGet(UART0_BASE));
	}

	}
void UARTINtHandler(void)
{
	uint32_t ui32Status;
	ui32Status = UARTIntStatus(UART0_BASE, true); // Thuc hien lay trang thai ngat
	UARTIntClear(UART0_BASE, ui32Status); //Xoa co ngat uart
	while(UARTCharsAvail(UART0_BASE))	//Thuc hien cho ki tu
	{
		UARTCharPutNonBlocking(UART0_BASE, UARTCharGetNonBlocking(UART0_BASE));	//nhan ki tu
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2); //chop tat led
		SysCtlDelay(SysCtlClockGet()/(1000*3)); //Thuc hien delay khoang 1ms
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0); 	//Tat LED
	}
}

