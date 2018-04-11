# Gameplay Objects
The gamplay objects are the objects that creates gameplay. That can be player, enemy or a tree.
# Entity
It's a base for every game object. 
## Enforcements
Derives from IUpdatable. Has `kill` method. Has additional `onSpawn` and `onKill` methods. It's distinguished by *unique id* and *tag*. Has reference to parent *Scene*. It can be temporary disabled, set to *sleep* state. Has `position` variable that can be used as *absolute* in range <0,1>, or relative. 
# System
Use it to update logic.
## Enforcements
Has read/write acces to the Entities of parent *Scene*.  You can set it's update priority - you may need to update some systems before other.
# Scene
A manager for *Entites* and *Systems*.
## Enforcements
Has `spawn` and `kill` methods to create `Entity` of specified type or kill `Entities` with specified tag or id. Uses helper storage classes for *Entities* and *Systems*.