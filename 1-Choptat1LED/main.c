/*
 * Chuong trinh bat tat LED
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

//Chuong trinh chinh
int main(void) {

	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN); //De hien ra nhac code ban co the an ctr+space
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);	//Cau hinh su dung port F
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1); //Cau hinh dung pin 1 cua port F, chan nay noi voi led do co san tren led
	while(1)
	{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);	//Bat LED
		SysCtlDelay(1000000);							//Delay
		GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1, 0);		//Tat LED
		SysCtlDelay(1000000);
	}
}
