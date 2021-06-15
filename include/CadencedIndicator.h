/*
 Name:		CadencedIndicator.h
 Created:	9/10/2019 9:55:27 PM
 Author:	Tim Long (Tigra Astronomy)
*/

#pragma once
#include <Timer.h>
#if defined(ARDUINO_ARCH_AVR)
	#include "ArduinoSTL.h"
#else
	#if defined(ARDUINOSTL_M_H)
		#error Do not reference the ArduinoSTL library for arm cores (the STL is built in and conflicts with ArduinoSTL)
	#endif
	#include <vector>
	#include <functional>
#endif


using CadencePattern = unsigned long;
constexpr int cadenceBitWidth = sizeof(CadencePattern) * 8;

namespace Cadence
	{
	constexpr CadencePattern SteadyOn	= 0b11111111111111111111111111111111ul;
	constexpr CadencePattern SteadyOff	= 0b00000000000000000000000000000000ul;
	constexpr CadencePattern Wink		= 0b11111111111111111111111111111110ul;
	constexpr CadencePattern Blip		= 0b00000000000000000000000000000001ul;
	constexpr CadencePattern BlinkSlow	= 0b11111111000000001111111100000000ul;
	constexpr CadencePattern BlinkFast	= 0b11110000111100001111000011110000ul;
	constexpr CadencePattern BlinkAlarm = 0b10101010101010101010101010101010ul;
	constexpr CadencePattern Pulse1		= 0b00000000000000000000000000000011ul;
	constexpr CadencePattern Pulse2		= 0b00000000000000000000000000110011ul;
	constexpr CadencePattern Pulse3		= 0b00000000000000000000001100110011ul;
	constexpr CadencePattern Pulse4		= 0b00000000000000000011001100110011ul;
	constexpr CadencePattern Heartbeat	= 0b00000000000000000000000000001010ul;
	constexpr CadencePattern Offbeat	= 0b00000000000010100000000000000000ul;
	}

struct Indicator
	{
	int pin;
	CadencePattern pattern;
	explicit Indicator(const int& pin, const CadencePattern& pattern);
	void setPattern(const CadencePattern& pattern);
	};

class CadenceManager
	{
public:
	explicit CadenceManager(const Duration& cadencePeriod = Timer::Seconds(4));
	void loop();
	void addIndicator(Indicator& indicator);

private:
	unsigned short bitIndex{};
	Timer cadenceTimer;
	Duration bitInterval;
	std::vector<Indicator*> indicators;
	void iterateIndicators(CadencePattern mask);
	};
