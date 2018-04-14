# Debug
## Globals
Provides `IS_DEBUG` bool.
## ILogger
Use it to write some info to the console. Every call of `log` is in new line. The output is `std::cout` and `log.txt` file.
## Example
```cpp
log( Priority::Info, "My info: ", someVariable, "." );
```
Result:
`[INFO] ExampleClass: My info: 123.`

# Enforcements
## ILogger
The `ILogger` provides 3 levels of priority: 
* *Info*
* *Warning* 
* *Error*

It also provides `debugLog` - variant of `log`, but it's logging only if debug mode is on.
  You have to override:
`const char* loggerName() const`
It's  the name displayed as `ExampleClass` above.

