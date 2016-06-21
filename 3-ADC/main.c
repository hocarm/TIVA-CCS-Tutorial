/*
 * Chuong trinh doc nhiet do ADC
 */
#include <stdint.h>
#include <stdbool.h>
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <driverlib/sysctl.h>
#include <driverlib/adc.h>

int main(void)
{
	uint32_t ui32ADC0Value[4];	//Khai bao mang 4 phan tu chua gia tri doc duoc tu ADC
	volatile uint32_t ui32TemAvg;
	volatile uint32_t ui32TempValueC;
	volatile uint32_t ui32TempValueF;

	SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);	//Cau hinh clock he thong

	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0); //Kich hoat ADC

	ADCSequenceConfigure(ADC0_BASE,1,ADC_TRIGGER_PROCESSOR,0); // cau hinh bat trigger ACD
	ADCSequenceStepConfigure(ADC0_BASE,1,0,ADC_CTL_TS);		//bat du lieu adc luu lan luot vao cac gia tri cua mang adc0value
	ADCSequenceStepConfigure(ADC0_BASE,1,1,ADC_CTL_TS);
	ADCSequenceStepConfigure(ADC0_BASE,1,2,ADC_CTL_TS);
	ADCSequenceStepConfigure(ADC0_BASE,1,3,ADC_CTL_TS | ADC_CTL_IE | ADC_CTL_END);
	ADCSequenceEnable(ADC0_BASE, 1); 	// kich hoat adc nhan du lieu
	while(1)
	{
		ADCIntClear(ADC0_BASE, 1);	//Xoa cac gia tri adc co tu truoc
		ADCProcessorTrigger(ADC0_BASE, 1);	//Thuc nhien trigger adc
		while (!ADCIntStatus(ADC0_BASE,1, false))	//Neu trang thai khoi tao cua ADC ok thi thuc hien buoc tiep theo
		{}
		ADCSequenceDataGet(ADC0_BASE,1 , ui32ADC0Value);	//Thuc hien lay du lieu va luu lai
		ui32TemAvg = (ui32ADC0Value[0] + ui32ADC0Value[1] + ui32ADC0Value[2] + ui32ADC0Value[3] + 2)/4;	//Tinh gia tri trung binh adc
		ui32TempValueC = (1475 - ((2475* ui32TemAvg)) / 4096)/10;	//Tinh gia tri nhiet do C, o day adc kit tiva la 12 bit nen do phan giai adc la 4096
		ui32TempValueF = ((ui32TempValueC*9)+160)/5;	//Tinh gia tri do F dua tren cong thuc chuyen doi tu do C sang do F
	}
	}
