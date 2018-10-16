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

#ifndef arduino-SU02_h
#define arduino-SU02_h

// System Include
#include <inttypes.h>
#include "xCore.h"

// System Defines
#define ADC_REG_RESULT			0x00
#define ADC_REG_ALERT			0x01
#define ADC_REG_CONF			0x02
#define ADC_REG_LOW_LIM			0x03
#define ADC_REG_HIGH_LIM		0x04
#define ADC_REG_HYSTERESIS		0x05
#define ADC_REG_LOW_CONVR		0x06
#define ADC_REG_HIGH_COVR		0x07

#define ADC_ALERT_OVER_V		0x01
#define ADC_ALERT_UNDER_V		0x00

#define ADC_CONF_CYC_TIME_OFF	0x00
#define ADC_CONF_CYC_TIME_32	0x20	
#define ADC_CONF_CYC_TIME_64	0x40
#define ADC_CONF_CYC_TIME_128	0x50
#define ADC_CONF_CYC_TIME_256	0x80
#define ADC_CONF_CYC_TIME_512	0xA0
#define ADC_CONF_CYC_TIME_1024	0xC0
#define ADC_CONF_CYC_TIME_2048	0xE0
#define ADC_CONF_ALERT_MAN		0x01
#define ADC_CONF_FLAG_EN		0x08

#ifndef HIGH_STATE
	#define HIGH_STATE	3.0
#endif

#ifndef LOW_STATE
	#define LOW_STATE 	1.0
#endif


class xSU02: public xCoreClass
{
	public:
		/**
		* 	Constructor
		* 	Creates a new instance of Sensor class.
		*/	
		xSU02();

		/**
		* 	Constructor
		* 	Creates a new instance of Sensor class.
		* 
		*	@param _addr, alternate I2C address.
		*/	
		xSU02(uint8_t _addr);
		
		/*
		* 	Initialize ADC081C021
		*/
		bool 	begin(void);

		/*
		* 	Request for measurement to made on ADC081C021
		*/
		void 	poll(void);

		/*
		* 	Get the measured state 
		*
		*	@ret, boolean state of input
		*/
		bool	getState(void);
		
		
		/*
		* 	Get the raw voltage 
		*
		*	@ret, float value of raw voltage
		*/
		float	getVoltage(void);
		
	private:
		/*
		* 	Reads voltage from ADC
		*/
		void 	readVoltage(void);


		uint8_t SU02_I2C_ADDR;
		float voltage;
		bool	state;
};

#endif
