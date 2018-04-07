# Visual
# Drawable
### IDrawable enforcements
To make something drawable you have to inherit from `IDrawable`.  The IDrawable automaticly registers and unregisters itself (RAII) in the Renderer. It has additional ability to update its position to the position of the `Entity`, however it's not obligatory.
### Basic drawables
Most of them are same as SFML, but just expanded with `IDrawable`:
* Rectangle Shape
* Circle Shape
* Sprite
* Text
# Renderer
Uses `Window` to draw. Should inherit from IUpdatable.  Its only usable method is `update`, that sorts Drawables by layer and draws them after this. 
# Animation
TODO. Maybe relation with Renderer? Take advantage of its `update` method to switch frames of animation? Or just derive from IUpdatable
