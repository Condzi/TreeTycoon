# Gameplay Objects
The gamplay objects are the objects that creates gameplay. That can be player, enemy or a tree.
# Entity
It's a base for every game object. 
## Enforcements
Derives from IUpdatable and ILogger. Has `kill` method. Has additional `onSpawn` and `onKill` methods. It's distinguished by *unique id* and *tag*. Has reference to parent *Scene*. It can be temporary disabled, set to *sleep* state. Has `position` variable that can be used as *absolute* in range <0,1>, or relative.  Provides `onUpdate` method that is called every frame if the Entity is active.
# System
Use it to update logic.
## Enforcements
Has read/write acces to the Entities of parent *Scene*.  You can set it's update priority - you may need to update some systems before other. It's **not inheriting** from `IUpdatable` - Scene handles it.
# Scene
A manager for *Entites* and *Systems*. Can be loaded / unloaded or suspended. If unloaded, then all entities are killed. If suspended, then all are disabled. 
## Enforcements
Has `spawn` and `kill` methods to create `Entity` of specified type or kill `Entities` with specified tag or id. Uses helper storage classes for *Entities* and *Systems*. The *Entities* are not removed immidietly - they are marked as 'to delete' first, then, after few seconds, are finally removed.
# Scene Manger
Wrapper for switching between scenes. It's global named `SceneManger`.
## Enforcements
You have to register scenes before switching them via `registerScene<TScene>( idNumber )`, then you can switch them using `pushScene( idNumber )` and `popScene()`. Additional methods are `disableCurrentScene` and `enableCurrentScene` - if you want to push pause scene for example, you may want to disable current scene first, and then push the pause scene. When leaving the pause scene, use `popScene()` and `enableCurrentScene`.