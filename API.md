# Harmony Lua API v1.0.0

Harmony can be used directly on Chimera scripts, it can be required like any other Lua
C module in your script:

```lua
local harmony = require "mods.harmony"
```

There are some simple [examples](examples/).

### How can I unload Hamorny correctly?
On previous versions, you had to run an unload function to unload harmony. In the current
version, harmony is unloaded when its last reference on the script is removed; otherwise,
the Lua garbage collector do it automaticly when the script is unloaded by Chimera.

Note that for compatibility reasons, the unload function still exists in the latest 
version of the API, but it no longer works.

### Library index
- [Optic](#optic)
    - [Create animation](#create_animation)
    - [Set animation property](#set_animation_property)
    - [Create sprite](#create_sprite)
    - [Create render queue](#create_render_queue)
    - [Render sprite](#render_sprite)
    - [Clear render queue](#clear_render_queue)
    - [Cleate sound](#create_sound)
    - [Create playback queue](#create_playback_queue)
    - [Play sound](#play_sound)
    - [Clear playback queue](#clear_playback_queue)
- [Menu](#menu)
    - [Set aspect ratio](#set_aspect_ratio)
    - [Play sound](#play_sound)
- [Events](#events)
    - [Multiplayer event](#multiplayer-event)
    - [Multiplayer sound](#multiplayer-sound)
    - [Menu accept](#menu-accept)
    - [Menu back](#menu-back)
    - [Menu list tab](#menu-list-tab)
    - [Menu mouse button press](#menu-mouse-button-press)
    - [Menu sound](#menu-sound)

## Optic

### create_animation
Create an animation.

**Takes:** `string` animation_name, `number` duration (milliseconds)

Example:
```lua
harmony.optic.create_animation("fade in", 200)
```

### set_animation_property
Set a property of an animation.

**Takes: (a)** `string` animation_name, `number` bezier_x1, `string` bezier_y1, `string` bezier_x2, `string` bezier_y2, animation_property, `number` transformation_value

**Animation Properties:**
- `position x`
- `position y`
- `scale x`
- `scale y`
- `opacity`
- `rotation`


```lua
harmony.optic.set_animation_property("fade in", 0.4, 0.0, 0.6, 1.0, "position y", 60)
```

Alternatively, there is a set of bezier presets.

**Takes: (b)** `string` animation_name, `string` bezier_preset, `string` animation_property, `number` transformation_value

**Bezier curve presets:**
- `ease in` 
- `ease out` 
- `ease in out` 
- `linear` 

Example:

```lua
harmony.optic.set_animation_property("fade in", "ease in", "position y", -60)
```

### create_sprite
Create a sprite from a texture file.

**Takes:** `string` sprite_name, `string` image_path, `number` width, `number` height

Example:
```lua
harmony.optic.create_sprite("hitmarker", "images/hitmarker.png", 35, 35)
```

### create_render_queue
Create a render queue for sprites.

**Takes:** `string` queue_name, `number` x, `number` y, `number` opacity, `number` rotation, `number` duration (milliseconds), `number` maximum_rendered_sprites, [`string` in_animation], [`string` out_animation], [`string` slide_animation]

Example:
```lua
harmony.optic.create_render_queue("demo", 50, 400, 255, 180, 4000, 0, "fade in", "fade out", "slide")
```

### render_sprite
Render a sprite.

**Takes: (a)** `string` render_queue, `string` sprite_name

Example:
```lua
harmony.optic.render_sprite("demo", "hitmarker")
```

Alternatively, a sprite can be rendered without a render queue.

**Takes: (b)** `string` sprite_name, `number` x, `number` y, `number` opacity, `number` rotation, `number` duration (milliseconds), [`string` in_animation], [`string` out_animation]

Example:
```lua
harmony.optic.render_sprite("hitmarker", 60, 60, 255, 0, 200, "fade in", "fade out")
```

### clear_render_queue
Remove all renders and enqueued sprites from render queue.

**Takes:** `string` render_queue

Example:
```lua
harmony.optic.clear_render_queue("demo")
```

### create_sound
Create a sound from a audio file.

**Takes:** `string` sound_name, `string` file_path

Example:
```lua
harmony.optic.create_sound("hit", "sounds/hit.wav")
```

### create_playback_queue
Create an audio engine instance.

**Takes:** `string` instance_name

Example:
```lua
harmony.optic.create_audio_engine("audio queue")
```

### play_sound
Play a sound in a playback queue.

**Takes:** `string` sound_name, `string` playback_queue_name, [`boolean` no_enqueue]

Example:
```lua
harmony.optic.play_sound("hit", "audio queue")
```

### clear_playback_queue
Stop and remove all sounds in a playback queue.

**Takes:** `string` playback_queue

Example:
```lua
harmony.optic.clear_playback_queue("audio queue")
```

## Menu
These functions are only available on map scripts.

### set_aspect_ratio
Set menu frame aspect ratio.

**Takes:** `number` aspect_ratio_x, `number` aspect_ratio_y

Example:
```lua
harmony.ui.set_aspect_ratio(16, 9)
```

### play_sound
Play a sound from tag.

**Takes: (a)** `string` sound_tag_path

Example:
```lua
harmony.ui.play_sound("sound\\sfx\\impulse\\coolant\\enter_water")
```

**Takes: (b)** `number` sound_tag_id

Example:
```lua
harmony.ui.play_sound(sound_tag_id)
```

## Events
These functions are called when specific events occur. They have to be assigned manually
using the **set_callback** function. Only one function is allowed per callback per 
script. *(Description from Chimera docs)*

**Takes:** `string` callback_name, `string` global_function_name

Example:
```lua
harmony.set_callback("multiplayer sound", "on_multiplayer_sound")
```

### multiplayer event
This is called when a multiplayer event occurs. E.g. player kill, ctf score, killing 
spree, etc.

**Takes:** `string` event_name, `number` local_player_id, `number` killer_id, `number` victim_id

**Events:**
- `falling dead`
- `guardian kill`
- `vehicle kill`
- `player kill`
- `betrayed`
- `suicide`
- `local double kill`
- `local killed player`
- `local triple kill`
- `local killtacular`
- `local killing spree`
- `local running riot`
- `game time left`
- `local ctf score`
- `ctf enemy score`
- `ctf ally score`
- `ctf enemy stole flag`
- `ctf enemy ed flag`
- `ctf ally stole flag`
- `ctf ally ed flag`
- `ctf friendly flag idle ed`
- `ctf enemy flag idle ed`

Example:
```lua
function on_multiplayer_event(event_name, local_player_id, killer_id, victim_id)
    -- Do some stuff
end

harmony.set_callback("multiplayer event", "on_multiplayer_event")
```

### multiplayer sound
This is called when a multiplayer sound is played. E.g. announcer voice, ting, etc.

**Takes:** `string` sound_name

**Sounds:**
- `playball`
- `game over`
- `one minute to win`
- `thirty seconds to win`
- `red team one minute to win`
- `red team thirty seconds to win`
- `blue team one minute to win`
- `red team thirty seconds to win`
- `red team flag taken`
- `red team flag returned`
- `red team flag captured`
- `blue team flag taken`
- `blue team flag returned`
- `blue team flag captured`
- `double kill`
- `triple kill`
- `killtacular`
- `running riot`
- `killing spree`
- `oddball`
- `race`
- `slayer`
- `capture the flag`
- `warthog`
- `ghost`
- `scorpion`
- `countdown timer`
- `teleporter activate`
- `flag failure`
- `countdown for respawn`
- `hill move`
- `player respawn`
- `king of the hill`
- `odd ball`
- `team race`
- `team slayer`
- `team king of the hill`
- `blue team capture the flag`
- `red team capture the flag`
- `contest`
- `control`
- `hill occupied`
- `countdown timer end`
- `ting`

**Note:** This event will be cancelled if the function returns `false`.

Example:
```lua
function on_multiplayer_sound(sound_name)
    if(sound_name == "ting") then
        -- Cancel event
        return false
    end

    return true
end

harmony.set_callback("multiplayer sound", "on_multiplayer_sound")
```

### menu accept
This is called when a widget accept event occurs. E.g. When a menu accept button
is pressed.

**Takes:** `number` button_widget_id

**Note:** This event will be cancelled if the function returns `false`.

Example:
```lua
function on_menu_accept(button_widget_id)
    if(button_widget_id == campaign_accept_button_widget_id) then
        -- Cancel event
        return false
    end

    return true
end

harmony.set_callback("menu accept", "on_menu_accept")
```

### menu back
This is called when returning to the previous menu.

**Takes:** `number` menu_widget_id

**Note:** This event will be cancelled if the function returns `false`.

Example:
```lua
function on_menu_back(menu_widget_id)
    if(menu_widget_id == campaign_menu_widget_id) then
        -- Cancel event
        return false
    end

    return true
end

harmony.set_callback("menu back", "on_menu_back")
```

### menu list tab
This is called when navigating in a menu list using arrow keys.

**Takes:** `string` pressed_key, `number` menu_list_widget_id, `number` menu_button_widget_id

**Keys:**
- `up`
- `down`
- `left`
- `right`

**Note:** This event will be cancelled if the function returns `false`.

Example:
```lua
function on_menu_list_tab(pressed_key, menu_list_widget_id, menu_button_widget_id)
    if(pressed_key == "down") then
        -- Cancel event
        return false
    end

    return true
end

harmony.set_callback("menu list tab", "on_menu_list_tab")
```

### menu mouse button press
This is called when a menu button is pressed with a mouse button.

**Takes:** `number` menu_button_widget_id, `string` pressed_mouse_button

**Mouse buttons:**
- `left button`
- `middle button`
- `right button`
- `double left button`

**Note:** This event will be cancelled if the function returns `false`.

Example:
```lua
function on_menu_mouse_button_press(menu_button_widget_id, pressed_mouse_button)
    if(pressed_mouse_button == "left button") then
        -- Cancel event
        return false
    end

    return true
end

harmony.set_callback("menu mouse button press", "on_menu_mouse_button_press")
```

### menu sound
This is called when a menu sound is played.

**Takes:** `number` menu_button_widget_id, `string` sound_name

**Sounds:**
- `cursor`
- `forward`
- `back`
- `flag failure`

**Note:** This event will be cancelled if the function returns `false`.

Example:
```lua
function on_menu_sound(menu_button_widget_id, sound_name)
    if(sound_name == "cursor") then
        -- Cancel event
        return false
    end

    return true
end

harmony.set_callback("menu sound", "on_menu_sound")
```
