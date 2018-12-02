// RHHardwareSPI.h
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2011 Mike McCauley
// Contributed by Joanna Rutkowska
// $Id: RHHardwareSPI.cpp,v 1.16 2016/07/07 00:02:53 mikem Exp mikem $

#include <RHHardwareSPI.h>

// Declare a single default instance of the hardware SPI interface class
RHHardwareSPI hardware_spi;

//HardwareSPI SPI(1);

RHHardwareSPI::RHHardwareSPI(Frequency frequency, BitOrder bitOrder,
		DataMode dataMode) :
		RHGenericSPI(frequency, bitOrder, dataMode) {

	::BitOrder order;
	if (bitOrder == BitOrderMSBFirst)
		order = MSBFIRST;
	else
		order = LSBFIRST;

	switch (_frequency) {
	case Frequency1MHz:
		_settings = SPISettings(1000000, order, dataMode);
		break;

	case Frequency2MHz:
		_settings = SPISettings(2000000, order, dataMode);
		break;

	case Frequency4MHz:
	default:
		_settings = SPISettings(4000000, order, dataMode);
		break;

	case Frequency8MHz:
		_settings = SPISettings(8000000, order, dataMode);
		break;

	case Frequency16MHz:
		_settings = SPISettings(16000000, order, dataMode);
		break;

	}
}

uint8_t RHHardwareSPI::transfer(uint8_t data) {
	return SPI.transfer(data);
}

void RHHardwareSPI::attachInterrupt() {
	SPI.attachInterrupt();
}

void RHHardwareSPI::detachInterrupt() {
	SPI.detachInterrupt();
}

void RHHardwareSPI::begin() {
	// Sigh: there are no common symbols for some of these SPI options across all platforms

	::BitOrder bitOrder;

	if (_bitOrder == BitOrderLSBFirst)
		bitOrder = LSBFIRST;
	else
		bitOrder = MSBFIRST;
	SPI.setBitOrder(bitOrder);

	uint32_t divider = 0;
	switch (_frequency) {
	case Frequency1MHz:
	default:
		divider = SPI_CLOCK_DIV64;
		break;

	case Frequency2MHz:
		divider = SPI_CLOCK_DIV32;
		break;

	case Frequency4MHz:
		divider = SPI_CLOCK_DIV16;
		break;

	case Frequency8MHz:
		divider = SPI_CLOCK_DIV8;
		break;

	case Frequency16MHz:
		divider = SPI_CLOCK_DIV4;
		break;

	}

	SPI.setClockDivider(divider);
	SPI.begin();

}

void RHHardwareSPI::end() {
	return SPI.end();
}

// If our platform is arduino and we support transactions then lets use the begin/end transaction
void RHHardwareSPI::beginTransaction() {
	SPI.beginTransaction(_settings);
}

void RHHardwareSPI::endTransaction() {
	SPI.endTransaction();
}

