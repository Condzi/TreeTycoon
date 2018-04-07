# Visual
# Drawable
To make something drawable you have to inherit from `IDrawable`. 
### IDrawable enforcements
The IDrawable automaticly registers and unregisters itself (RAII) in the Renderer. It has additional ability to update its position to the position of the `Entity`, however it's not obligatory. It derives from `IUpdatable` for animation.
### Animation
Every drawable can easily be also animationable, you just have to set `isAnimation` to true and pass 1 by `n` dimensional texture, where `n` are the frames, frame switch time and frame width (height is equal to the texture height, that's why texture has to be one dimensional). **If is bounded with `Entity`, check if entity is awake**.
### Basic drawables
Most of them are same as SFML, but just expanded with `IDrawable`, *animatable* are maked with star:
* Rectangle Shape*
* Circle Shape*
* Sprite*
* Text
# Renderer
Uses `Window` to draw. Should inherit from IUpdatable.  Its only usable method is `update`, that sorts Drawables by layer and draws them after this. 