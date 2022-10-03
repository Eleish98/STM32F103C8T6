
#include "1- LIB/STD_TYPES.h"
#include "1- LIB/BIT_MATH.h"

#include "2- MCAL/ST/04- RCC/RCC_interface.h"
#include "2- MCAL/ST/05- GPIO/GPIO_interface.h"
#include "2- MCAL/ST/06- AFIO/AFIO_interface.h"
#include "2- MCAL/ST/19- I2C/I2C_interface.h"

#include "3- HAL/04- RTC/ExRTC_interface.h"


u8 Senddata[] = "Hello from STM32F103\nThis is a very Long Sentence";
u8 Receivedata[100];
volatile I2C_Status_t Status;

void HH(char*);

void HH(char * H){

	asm("NOP");
}
int main(void){

	MRCC_voidInitClock();

	MRCC_voidEnablePeripheral(RCC_PER_GPIOB);
	MRCC_voidEnablePeripheral(RCC_PER_GPIOC);
	MRCC_voidEnablePeripheral(RCC_PER_AFIO);
	MRCC_voidEnablePeripheral(RCC_PER_I2C1);

	MAFIO_voidRemapI2C1(AFIO_I2C1_MODE_1);

	MGPIO_voidSetPinDirection(GPIO_PORTB,GPIO_PIN_6,GPIO_DIR_ALTERNATE_FUNCTION_OPEN_DRAIN);
	MGPIO_voidSetPinDirection(GPIO_PORTB,GPIO_PIN_7,GPIO_DIR_ALTERNATE_FUNCTION_OPEN_DRAIN);

	MGPIO_voidSetPinDirection(GPIO_PORTC,GPIO_PIN_13,GPIO_DIR_OUTPUT_PUSH_PULL);
	MGPIO_voidSetPin(GPIO_PORTC,13);


	ERTCTime_t Time = {10,40,50};
	ERTCCalender_t Date = {22,4,19};

	ERTC_Config_t RTC = {I2C1,ERTC_MODE_12_HOURS};

	HRTC_voidInit(&RTC);
	HRTC_voidSetOutputMode(&RTC,ERTC_OUTPUT_MODE_4096HZ);
	MGPIO_voidClearPin(GPIO_PORTC,13);

//	Status = MI2C_enuConnect(I2C1,8,I2C_DIRECTION_WRITE);
//
//	Status = MI2C_enuWriteNoStopSynch(I2C1,Senddata,10);
//
//	Status = MI2C_enuConnect(I2C1,8,I2C_DIRECTION_READ);
//
//	Status = MI2C_enuReadNoStopSynch(I2C1,Receivedata,4);
//
//	Status = MI2C_enuConnect(I2C1,8,I2C_DIRECTION_WRITE);
//
//	Status = MI2C_enuWriteNoStopSynch(I2C1,Senddata,10);
//
//	Status = MI2C_enuDisconnect(I2C1);
//
//	Status = MI2C_enuMasterWriteSynch(I2C1,0x8,Senddata,1);
//
//	Status = MI2C_enuMasterReadSynch(I2C1,8,Receivedata,4);

	while(1){

		HRTC_voidGetDateTime(&RTC,&Date,&Time);
	}

	return 0;
}
