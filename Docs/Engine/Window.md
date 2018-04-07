# Window
The *Window* is... representation of the game window. Basic overlay for `sf::RenderWindow`. Derives from `IUpdatable` to perform event polling. It's a global.
## Enforcements
Public:
* Get/Set size
* set title and icon
* is open

Intenal:
* Event polling (in `update`), relation with `Input` - only when window is focused
* for internal use - `clear`, `draw` and `display` methods.