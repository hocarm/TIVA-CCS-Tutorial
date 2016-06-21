/*
 * Chuong trinh dung nut nhan bat tat 1 LED
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

//Chuong trinh chinh
int main(void) {

	//Khoi tao clock he thong
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN); //De hien ra nhac code ban co the an ctr+space
	//Kich hoat ngoai vi
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);	//Kich hoat port F
	// Cau hinh output xuat LED
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 |GPIO_PIN_2 | GPIO_PIN_3); //O day su dung pin 1 2 3 cho 3 led RGB tren kit

	// Cau hinh input la nut nhan co san tren kit SW1
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4); //O day pin 4 cua port F noi voi nut nhan SW1 tren kit
	// Cau hinh phim bam
	GPIOPadConfigSet( GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	while(1)
	{
		//Kiem tra
		if (!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4))
			//Bat LED do
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 |GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_1);
		else
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 |GPIO_PIN_2 | GPIO_PIN_3, 0);	//Tat LED do
	}
}
