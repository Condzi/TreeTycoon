# IUpdatable
## Example
```cpp
class MyClass :
    public IUpdatable
{
public:
    // Optional
    int16_t getPriority() const override
    {
        return 1;
    }
    
    void update() override
    {
        // Do stuff
    }   
};
```
## Enforcements
Calls `update` every frame. The order of the calls is random, however you can suggest it by using `setPriorirty` - **lower** priority - **faster** update. For example, you want to have `Physic` module update after `Entities` update and before *Renderer* update, that draws everything on screen, so you can assing the priority like this:
* Entities - 0
* Scene - 1
* Physic - 2
* Renderer - 3  

Note: mark `getPriority` as `final` in polymorphic classes like `Entity`.
## Implementation details
Like `IDrawable` registers to the `Renderer`, `IUpdatable` should register to some global object like `Updater` or something.