# Visual
# Drawable
### IDrawable enforcements
To make something drawable you have to inherit from `IDrawable`.  The IDrawable automaticly registers and unregisters itself (RAII) in the Renderer. 
### Basic drawables
Most of them are same as SFML, but just expanded with `IDrawable`:
* Rectangle Shape
* Circle Shape
* Sprite
* Text
# Renderer
Uses `Window` to draw.  Provides:
*  `update` - sorts drawables by layer, prepares it to render
*  `render` -  draws everything on screen and displays it
# Animation
TODO. Maybe relation with Renderer? Take advantage of its `update` method to switch frames of animation?
