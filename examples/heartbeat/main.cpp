#include <Arduino.h>
#include <CadencedIndicator.h>

CadenceManager ledManager;
Indicator builtInLed(LED_BUILTIN, Cadence::Heartbeat);

void setup()
{
    // put your setup code here, to run once:
    pinMode(LED_BUILTIN, OUTPUT);
    ledManager.addIndicator(builtInLed);
}

void loop()
{
    // put your main code here, to run repeatedly:
    ledManager.loop();
}