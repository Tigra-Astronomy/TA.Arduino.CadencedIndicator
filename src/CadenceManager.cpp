/*
 Name:		CadencedIndicator.cpp
 Created:	9/10/2019 9:55:27 PM
 Author:	Tim
 Editor:	http://www.visualmicro.com
*/

#include <vector>
#include "CadencedIndicator.h"

CadenceManager::CadenceManager(const Duration &cadencePeriod)
{
	bitInterval = cadencePeriod / cadenceBitWidth;
	cadenceTimer.setDuration(bitInterval);
}

void CadenceManager::addIndicator(Indicator &indicator)
{
	indicators.push_back(&indicator);
}

void CadenceManager::iterateIndicators(CadencePattern mask)
{
	for (Indicator *indicator : indicators)
	{
		const bool bitSet = (indicator->pattern & mask) != 0;
		pinMode(indicator->pin, OUTPUT); // Always refresh the pin mode
		digitalWrite(indicator->pin, bitSet ? HIGH : LOW);
	}
}

void CadenceManager::loop()
{
	if (cadenceTimer.expired())
	{
		cadenceTimer.setDuration(bitInterval);
		CadencePattern mask = 1;
		mask <<= bitIndex++;
		bitIndex %= cadenceBitWidth;
		iterateIndicators(mask);
	}
}
