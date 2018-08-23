/*
	This is a library for the SU02 
	Digital Input
	
	Max input 3.3V

	The board uses I2C for communication.
	
	The board communicates with one I2C devices:
	- ADC081C021
	
	Data Sheets:
	ADC081C021 - http://www.ti.com/lit/ds/symlink/adc081c021.pdf
*/

#include <xSU02.h>
#include <math.h>

/*-----------------Public Class Function----------------*/

/*!
	@brief 	Instantiates a new xSU02 Class 
*/
xSU02::xSU02(){
	SU02_I2C_ADDR = 0x55;
}

/*!
	@brief 	Instantiates a new xSU02 Class 
	@param	_addr	Alternate I2C Address of Device
*/
xSU02::xSU02(uint8_t _addr){
	SU02_I2C_ADDR = _addr;
}

/*!
	@brief 	Configure the sensor
*/
bool xSU02::begin(void){
	xCore.write8(SU02_I2C_ADDR, ADC_REG_CONF, ADC_CONF_CYC_TIME_256); 
	uint8_t conf = xCore.read8(SU02_I2C_ADDR, ADC_REG_CONF);

	if(conf != ADC_CONF_CYC_TIME_256)
	{
		return false;
	}
	return true;
}

/*!
	@brief 	Request Read to be done from ADC081C021
*/
void xSU02::poll(void){
	readVoltage();
}

/*!
	@brief 	Get the State of the Button

	@ret	boolean state
*/
bool xSU02::getState(void){
	return state;
}

/*!
	@brief 	Get the value of the raw voltage

	@ret	float voltage
*/
float xSU02::getVoltage(void){
	return voltage;
}

/*-----------------Private Class Function----------------*/

/*!
	@brief 	Read ADC Voltage from ADC081C021
*/
void xSU02::readVoltage(void){
	uint8_t a,b;
	uint16_t data;
	
	data = xCore.read16(SU02_I2C_ADDR, ADC_REG_RESULT);
	
	a = (uint8_t)((data & 0xFF00) >> 8);
	b = (uint8_t)((data & 0x00FF) >> 0);
	
	voltage = (((((a & 0x0F)*256) + (b & 0xF0))/0x10)*(3.3/256));

	if(voltage > HIGH_STATE){
		state = true;
	} else if(voltage < LOW_STATE){
		state = false;
	}
}




