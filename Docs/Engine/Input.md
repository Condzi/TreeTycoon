# Input
Reads keyboard and mouse key states. It is a global.
## Example
```cpp
if ( Input.isUp( Keyboard::Key::Escape ) )
if ( Input.isDown( Mouse::Button::Left ) )
if ( Input.isHeld( Keyboard::Key::A ) )
```
## Enforcements
Theree button or key states - *up*, *down* or *held*. Methods have overload for `Keyboard::Key` and `Mouse::Button` enumerations.
The `Keyboard::Key` and `Mouse::Button` are aliases for SFML ones.
Also has `mousePosition` method, that returns position of mouse relative to the window.
<!--stackedit_data:
eyJoaXN0b3J5IjpbMTU0OTExNTNdfQ==
-->