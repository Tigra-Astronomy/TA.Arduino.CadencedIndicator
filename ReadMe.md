# `TA.Arduino.CadencedIndicator` Library

An easy-to-use library for switching I/O pins in regular, repeating patterns.
Ideally suited for making advanced LED status indicators.

The emphasis is on ease-of-use over timing accuracy.
The techniques used are excellent for human vision which is not too sensitive to slight timing variations of a few milliseconds.
It is not designed for producing highly accurate timing signals such as controlling stepper motors.

## Theory of Operation

The library defines three main things:

- The `CadenceManager` class.
- The `Indicator` structure.
- Cadence bit patterns in the `Cadence::` namespace.

### `Indicator`

This structure defines one digital output that is to be managed by the `CadenceManager`.
The structure contains the ditial pin to use and the cadence bit pattern.

### `CadenceManager`

This class maintains a list of all the active indicators and generates the timing required for each output pin.

All of the indicators managed by one `CadenceManager` instance are kept "in sync" and will not drift with respect to each other over time.
It is possible to use any number of cadence managers, all configured to run at different speeds.
Multiple `CadenceManager` instances are not gauranteed to stay "in sync" with each other.

### `Cadence::` Bit patterns

The `Cadence::` namespace contains several predefined cadence patterns that are commonly used.
These are defined for convenience.
It is not required to use the predefined patterns; any value of type `CadencePattern` can be used.

Cadences patterns are stored as 32-bit unsigned integers.

Existing cadence patterns can be combined using bitwise operators, such as AND (`&`), OR (`|`) and XOR (`^`).

## Using Cadenced Indicators

First, create an instance of `CadenceManager`.

```lang=cpp
CadenceManager ledManager;
```

The default constructor creates a manager that has a 4 second duration.
That is, a 32-bit patter will play out over 4 seconds, or 125 milliseconds per bit.
That results in a reasonable "human scale" indicator that should be well within the capabilities of even the slowest Arduino.
However, if desired, the cadence speed may be specified by passing a `Duration` in the constructor, like so:

```lang=cpp
CadenceManager ledManager(Timer::Seconds(2));
```

`Timer::Seconds()` is defined in the [`TA.Arduino.Timer` library][timer].

**Note**: 4 seconds is a sensible default.
As the duration decreases it becoms more difficult to maintain consistent timing, depending on the execution time of the main loop and the system clock speed.
Therefore, cadence durations of less than a second are unlikely to be useful.
Use the longest duration that allows you to display the pattern you need in 32-bits of data.

Next, create an indicator and set its cadence pattern.

```lang=cpp
Indicator builtInLed = {pin = LED_BUILTIN, pattern = Cadence::Heartbeat};
```

**Note**: Take care about the object lifetime of your indicators.
The CadenceManager will store a pointer to the item, and if it goes out of scope and gets destroyed, then the CadenceManager may crash or behave incorrectly.
You must ensure that you correctly manage the lifetime of your objects.
The best approach is to declare indicators globally so that they are permanently allocated for the lifetime of the program.
Here we have used struct initializer syntax to ensure that the indicator has the correct starting values.

In your `setup()` method or another suitable location, add the indicator to the cadence manager. Note that you still need to configure I/O pins correctly, this is not done for you.

```lang=cpp
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  ledManager.addIndicator(builtInLed);
}
```

Finally, arrange for `CadenceManager::loop()` to be called in your main loop.

```lang=cpp
void loop() {
  // put your main code here, to run repeatedly:
  ledManager.loop();
}
```

That's it. Your indicator will begin working.
You may change the cadence at any time, by simply updating the indicator:

```lang=cpp
builtInLed.pattern = Cadence::BlinkFast;
```

[timer]: https://github.com/Tigra-Astronomy/TA.Arduino.Timer "A simple easy-to-use timer utility for human scale events"
