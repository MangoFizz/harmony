# Harmony
A set of additional features for Chimera using the Lua API.

## Features summary
- [Optic](#optic)
- [Multiplayer events callbacks](#multiplayer-events-callbacks)
- [UI custom aspect ratio](#ui-custom-aspect-ratio)
- [UI input callbacks](#ui-input-callbacks)
- [Lua API](#lua-api)

## Installation
### Manual
1. [Install Chimera](https://github.com/SnowyMouse/chimera#installation)
2. Create a folder called "mods" (e.g. "D:\Halo Custom Edition\mods")
3. Copy harmony.dll file to your mods folder  

### Mercury
Get Harmony on [Mercury](https://github.com/Sledmine/Mercury) by using the
following command:
```
mercury install harmony
```

Note: Like Chimera, Harmony requires DirectX 9 to be installed in your
system.

## List of features
Harmony features are mainly related to the User Interface of the game, but it
also contains some extra features (like an HAC2 Optic reimplementation).

#### Optic
A set of functions for displaying external images and playing sounds. The main
use of this feature is to create a medal system like in most recent Halo
games. See the repository below for a working Medal system made using this
feature. https://github.com/Sledmine/Optic

#### Multiplayer events callbacks
Some useful multiplayer callbacks:
- Multiplayer event (player dead, team score, etc.)
- Multiplayer sounds (announcer voice, hit sound, etc.)

#### UI custom aspect ratio
A Chimera's widescreen fix override. Can set a custom aspect ratio for the 
menus (e.g. 16:9).

#### UI input callbacks
A set of callbacks for the main events of the user interface:
- Menu accept event
- Menu Back event
- Menu navigation arrows
- Menu sounds
- Mouse button press

#### Lua API
Harmony can be used directly on Chimera scripts, it can be required like any
other Lua library in your script:
```lua
local harmony = require "mods.harmony"
```
Check out the [Harmony Lua API documentation](API.md).

## Credits
- [**Snowy**](https://github.com/SnowyMouse) - Development of Chimera, the
base of this project.
- [**Sledmine**](https://github.com/Sledmine) - Help with Lua API docs; testing and feedback.
