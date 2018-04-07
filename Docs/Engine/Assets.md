# Assets
**Always** provides defaults upon failure. Derives from `ILogger` (see `Debug.md`) It's a global that provides:
* Sound and Music playing
* Texture access
* Font acces
* Settings access
# Example
```cpp
Game::init()
{
	Assets.Settings.load( "settings.ini" );
	auto windowWidth = convertTo<int32_t>( Assets.Settings.get( "window_width" );
	window.setSize(windowWidth, ...);
}

Menu::update()
{
	if( Assets.Music.isNotPlaying() )
		Assets.Music.play( "menuTheme" );
	
	if( /*button clicked*/ )
		Assets.Sound.play( "buttonClick" );	
	
	mySprite.setTexture( Asset.Texture.get( "texture ") );
}
```
# Enforcements
Settings, Texture, Font and Sound have to have `load( path, name )` methods. If you try to load two or more resources of same name, the'll be overwritten.
## Sound
Many sounds can be played at once.
## Music
Music is a special asset because it can't be stored. It has to be streamed. One *Music* asset can be streamed at same time.
## Texture and Font
Both can be accesed using `get( name )`, then `cref` is returned. 
## Settings
Settings are loaded from `.ini` file. They can be saved, accessed and changed. 
<!--stackedit_data:
eyJoaXN0b3J5IjpbLTExMTg2MjE4MzVdfQ==
-->