# Utility
The *Utility* module, besides RNG functions, also contains things that will came up during programming process, like conversion function (`convertTo<Type>( var )` ).
## RNG
### Example
```cpp
float myRandomFloat = Random<float>( 0, 1 );
int8_t myRandomInt = Random<int8_t>( min, max )
```
### Enforcemets
It's a template function. It has two parameters - `min_` and `max_`, that are casted to given template parameter, so missing float arguments in first example is not an error.