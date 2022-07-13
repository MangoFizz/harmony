# Harmony
An extension to [Chimera](https://github.com/SnowyMouse/chimera)'s Lua Scripting API
focused on manipulating the game's user interface.

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

**Note:** Like Chimera, Harmony requires DirectX 9 to be installed in your
system.

## Features
Harmony features are meant to be used within Lua scripts, so there are no user-facing
features like commands or any other settings.

### Optic
This was the most important feature, it is a set of functions for displaying external
images and playing sounds in-game. See the repository below for a working Medals
system made using this feature. https://github.com/Sledmine/Optic

### UI manipulation
Harmony allows you to manipulate some aspects of the game's user interface, such as
changing the menu aspect ratio, creating and modifying UI widgets in real time
(which is useful for creating animated menus), playing custom sounds, changing the
cursor scale, and even blocking menu events. This opens a lot of possibilities for
creating more dynamic and flexible user interfaces.

See [Insurrection project](https://github.com/Sledmine/insurrection) for an example of
how these features can be used.

### Event callbacks
Like Chimera, Harmony allows you to register callbacks for some events, such when the
player presses a key, when the player opens or closes a menu, when the player joins a server, when a player dies, etc. (see [API docs](API.md) for more details).

### Lua scripting 
Harmony can be used directly on Chimera scripts, it can be required like any
other Lua C module in your script:
```lua
local harmony = require "mods.harmony"
```
Check out the [Harmony Lua API documentation](API.md).

## Licenses
- [**Chimera**](licenses/chimera) - Project structure, engine data, some events,
commands system.
- [**HAC2**](licenses/hac2) - Codefinder.
- [**Lua**](licenses/lua) - Scripting language used by Chimera.
- [**Soloud**](licenses/soloud) - Sound engine used in the Optic feature.

## Credits
- [**SnowyMouse**](https://github.com/SnowyMouse) - Development of Chimera (the
base of this project).
- [**Sledmine**](https://github.com/Sledmine) - Markdown documentation; testing and
feedback.
- **SnC people** - Testing and feedback (love you guys).
- **Github copilot** - Speeding up the process of writing code and documentation.
