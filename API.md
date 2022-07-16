# Harmony Lua API v3.0.0

Harmony can be used directly on Chimera scripts, it can be required like any other Lua
C module in your script:

```lua
local harmony = require "mods.harmony"
```

There are some [scripts](lua/scripts/global) you can use as reference.

### Functions
- [Math](#math)
    - [Create bezier curve](#create_bezier_curve)
    - [Get bezier curve point](#get_bezier_curve_point)
- [Menu](#menu)
    - [Set aspect ratio](#set_aspect_ratio)
    - [Play sound](#play_sound)
    - [Get widget values](#get_widget_values)
    - [Set widget values](#set_widget_values)
    - [Open widget](#open_widget)
    - [Close widget](#close_widget)
    - [Replace widget](#replace_widget)
    - [Reload widget](#reload_widget)
    - [Find widgets](#find_widgets)
    - [Focus widget](#focus_widget)
    - [Get root widget](#get_root_widget)
    - [Block input](#block_input)
    - [Set cursor scale](#set_cursor_scale)
- [Misc](#misc)
    - [Split command string](#split_command)
- [Multiplayer](#multiplayer)
    - [Query server status](#query_server_status)
    - [Mute announcer](#mute_announcer)
- [Optic](#optic)
    - [Create animation](#create_animation)
    - [Set animation property](#set_animation_property)
    - [Create sprite](#create_sprite)
    - [Create render queue](#create_render_queue)
    - [Render sprite](#render_sprite)
    - [Clear render queue](#clear_render_queue)
    - [Create sound](#create_sound)
    - [Create audio engine](#create_audio_engine)
    - [Play sound](#play_sound)
    - [Clear audio engine](#clear_audio_engine)
    - [Set audio engine gain](#set_audio_engine_gain)
- [Time](#time)
    - [Set timestamp](#set_timestamp)
    - [Get elapsed milliseconds](#get_elapsed_milliseconds)
    - [Get elapsed seconds](#get_elapsed_seconds)

### Events
- [Set callback](#set_callback)
    - [Multiplayer event](#multiplayer-event)
    - [Multiplayer sound](#multiplayer-sound)
    - [Multiplayer hit sound](#multiplayer-hit-sound)
    - [Widget accept](#widget-accept)
    - [Widget close](#widget-close)
    - [Widget list tab](#widget-list-tab)
    - [Widget mouse button press](#widget-mouse-button-press)
    - [Widget mouse focus](#widget-mouse-focus)
    - [Widget open](#widget-open)
    - [Widget sound](#widget-sound)
    - [HS function](#hs-function)
    - [Key press](#key-press)

## Math

### create_bezier_curve

Create a bezier curve.

**Takes: (a)** `number` bezier_x1, `number` bezier_y1, `number` bezier_x2, `number` bezier_y2

Example:

```lua
harmony.math.create_bezier_curve(0.4, 0.0, 0.6, 1.0)
```

Alternatively, there is a set of bezier presets.

**Takes: (b)** `string` bezier_preset

**Bezier curve presets:**
- `ease in` 
- `ease out` 
- `ease in out` 
- `linear` 

Example:

```lua
harmony.math.create_bezier_curve("ease in")
```

### get_bezier_curve_point

Get a point from a bezier curve.

**Takes:** `number` x_value

**Returns:** `number` y_value

Example:

```lua
harmony.math.get_bezier_curve_point(0.5)
```

## Menu
These functions are only available on map scripts.

### set_aspect_ratio

Set menu frame aspect ratio.

**Takes:** `number` aspect_ratio_x, `number` aspect_ratio_y

Example:
```lua
harmony.menu.set_aspect_ratio(16, 9)
```

### play_sound

Play a sound from tag.

**Takes: (a)** `string` sound_tag_path

Example:
```lua
harmony.menu.play_sound("sound\\sfx\\impulse\\coolant\\enter_water")
```

**Takes: (b)** `number` sound_tag_id

Example:
```lua
harmony.menu.play_sound(sound_tag_id)
```

### get_widget_values

Get values from a widget.

**Takes:** `number` widget_handle

**Returns:** `table` widget_values

**Returned values:**
- `name`
- `tag_id`
- `top_bound`
- `left_bound`
- `opacity`
- `bitmap_index`
- `previous_widget`
- `next_widget`
- `parent_widget`
- `child_widget`
- `focused_widget`

Example:

```lua
local widgetValues = harmony.menu.get_widget_values(widgetHandle)
```

### set_widget_values

Set values to a widget.

**Takes:** `number` widget_handle, `table` widget_values

**Widget values:**
- `top_bound`
- `left_bound`
- `opacity`
- `bitmap_index`
- `previous_widget`
- `next_widget`
- `parent_widget`
- `child_widget`
- `focused_widget`

Example:

```lua
harmony.menu.set_widget_values(widgetHandle, {
    top_bound = 50,
    left_bound = 20,
    opacity = 1.0,
    bitmap_index = 1,
    previous_widget = previousWidget,
    next_widget = nextWidget,
})
```

### open_widget

Open an UI widget.

**Takes: (a)** `string` widget_definition_tag_path, [`boolean` dont_push_history]

**Returns:** `number` widget_handle

```lua
harmony.menu.open_widget("ui\\shell\\main_menu\\main_menu", true)
```

**Takes: (b)** `number` widget_definition_tag_id, [`boolean` dont_push_history]

**Returns:** `number` widget_handle

Example:

```lua
harmony.menu.open_widget(widget_definition_tag_id)
```

### close_widget

Close the current UI widget.

Example:

```lua
harmony.menu.close_widget()
```

### replace_widget

Replace a given UI widget.

**Takes: (a)** `number` widget_handle `string` widget_definition_tag_path

**Returns:** `number` new_widget_handle

Example:

```lua
harmony.menu.replace_widget(widgetHandle, "ui\\shell\\main_menu\\main_menu")
```

**Takes: (b)** `number` widget_handle `number` widget_definition_tag_id

**Returns:** `number` new_widget_handle

Example:

```lua
harmony.menu.replace_widget(widgetHandle, widget_definition_tag_id)
```

### reload_widget

Reload a given UI widget. If no widget is given, the current root widget will be reloaded.

**Takes:** [`number` widget_handle]

**Returns:** `number` new_widget_handle

Example:

```lua
harmony.menu.reload_widget()
```

### find_widgets

Find widgets by a given widget definition.

**Takes (a):** `number` widget_definition_tag_id

**Returns:** `table` found_widget_handles

Example:

```lua
local foundWidgetHandles = harmony.menu.find_widgets(widgetDefinitionTagId)
```

**Takes (b):** `string` widget_definition_tag_path

**Returns:** `table` found_widget_handles

Example:

```lua
local foundWidgetHandles = harmony.menu.find_widgets("ui\\shell\\common_back")
```

### focus_widget

Focus a given widget.

**Takes:** `number` widget_handle

Example:

```lua
harmony.menu.focus_widget(widgetHandle)
```

### get_root_widget

Get the current root widget.

**Returns:** `number` widget_handle

Example:

```lua
harmony.menu.get_root_widget()
```

### block_input

Block menu input.

**Takes:** `boolean` block_input

Example:

```lua
harmony.menu.block_input(true)
```

### set_cursor_scale

Set menu cursor scale.

**Takes:** `number` scale

Example:

```lua
harmony.menu.set_cursor_scale(0.65)
```

## Misc

### split_command

Split arguments from command string.

**Takes:** `string` command_string

**Returns:** `table` arguments

Example:

```lua
local arguments = harmony.misc.split_command("command arg1 \"arg 2\" arg3")
```

## Multiplayer

### query_server_status

Query server status.

**Takes:** `string` server_ip, `number` server_port

**Returns:** `table` server_status

Example:

```lua
local serverStatus = harmony.multiplayer.query_server_status("localhost", 7777)
```

### mute_announcer

Mute multiplayer announcer.

**Takes:** `boolean` mute_announcer

Example:

```lua
harmony.multiplayer.mute_announcer(true)
```

## Optic

### create_bezier_curve
Create a bezier curve.

**Takes:** `number` duration (milliseconds)

**Returns:** `number` animation_handle

Example:
```lua
local fadeInAnim = harmony.optic.create_animation(200)
```

### set_animation_property
Set a property of an animation.

**Takes: (a)** `number` animation_handle, `number` bezier_x1, `number` bezier_y1, `number` bezier_x2, `number` bezier_y2, `string` animation_property, `number` transformation_value

**Animation Properties:**
- `position x`
- `position y`
- `scale x`
- `scale y`
- `opacity`
- `rotation`


```lua
harmony.optic.set_animation_property(fadeInAnim, 0.4, 0.0, 0.6, 1.0, "position y", 60)
```

Alternatively, there is a set of bezier presets.

**Takes: (b)** `number` animation_handle, `string` bezier_preset, `string` animation_property, `number` transformation_value

**Bezier curve presets:**
- `ease in` 
- `ease out` 
- `ease in out` 
- `linear` 

Example:

```lua
harmony.optic.set_animation_property(fadeInAnim, "ease in", "position y", -60)
```

### create_sprite
Create a sprite from a texture file.

**Takes (a):** `string` image_path, `number` width, `number` height

**Returns:** `number` sprite_handle

Example:
```lua
local hitmarkerSprite = harmony.optic.create_sprite("images/hitmarker.png", 35, 35)
```

**Takes (b):** `string` image_path, `number` width, `number` height, `number` sheet_rows, `number` sheet_columns, `number` frames, `number` frames_per_second

**Returns:** `number` sprite_handle

Example:
```lua
local hitmarkerSprite = harmony.optic.create_sprite("images/hitmarker.png", 35, 35, 3, 3, 7, 10)
```

### create_render_queue
Create a render queue for sprites.

**Takes:** `number` x, `number` y, `number` opacity, `number` rotation, `number` duration (milliseconds), `number` maximum_rendered_sprites, [`string` in_animation], [`string` out_animation], [`string` slide_animation]

**Returns:** `number` render_queue_handle

Example:
```lua
local demoRenderQueue = harmony.optic.create_render_queue(50, 400, 255, 180, 4000, 0, fadeInAnim, fadeOutAnim, slideAnim)
```

### render_sprite
Render a sprite.

**Takes: (a)** `number` render_queue_handle, `number` sprite_handle

Example:
```lua
harmony.optic.render_sprite(demoRenderQueue, hitmarkerSprite)
```

Alternatively, a sprite can be rendered without a render queue.

**Takes: (b)** `number` sprite_handle, `number` x, `number` y, `number` opacity, `number` rotation, `number` duration (milliseconds), [`string` in_animation], [`string` out_animation]

Example:
```lua
harmony.optic.render_sprite(hitmarkerSprite, 60, 60, 255, 0, 200, fadeInAnim, fadeOutAnim)
```

### clear_render_queue
Remove all renders and enqueued sprites from render queue.

**Takes:** `number` render_queue_handle

Example:
```lua
harmony.optic.clear_render_queue(demoRenderQueue)
```

### create_sound
Create a sound from a audio file.

**Takes:** `string` file_path

**Returns:** `number` sound_handle

Example:
```lua
local hitSound = harmony.optic.create_sound("sounds/hit.wav")
```

### create_audio_engine
Create an audio engine instance.

**Return:** `number` audio_engine_instance_handle

Example:
```lua
local audioEngine = harmony.optic.create_audio_engine()
```

### play_sound
Play a sound in an audio engine instance.

**Takes:** `number` sound_handle, `number` audio_engine_instance_handle, [`boolean` no_enqueue]

Example:
```lua
harmony.optic.play_sound(hitSound, audioEngine)
```

### clear_audio_engine
Stop and remove all sounds in an audio engine instance.

**Takes:** `number` audio_engine_instance_handle

Example:
```lua
harmony.optic.clear_audio_engine(audioEngine)
```

## Time

### set_timestamp

Set a timestamp.

**Returns:** `number` timestamp_handle

Example:

```lua
local timestamp = harmony.time.set_timestamp()
```

### get_elapsed_milliseconds

Get elapsed milliseconds since a timestamp.

**Takes:** `number` timestamp_handle

**Returns:** `number` elapsed_milliseconds

Example:

```lua
local elapsedMilliseconds = harmony.time.get_elapsed_milliseconds(timestamp)
```

### get_elapsed_seconds

Get elapsed seconds since a timestamp.

**Takes:** `number` timestamp_handle

**Returns:** `number` elapsed_seconds

Example:

```lua
local elapsedSeconds = harmony.time.get_elapsed_seconds(timestamp)
```

## Events

### set_callback

These functions are called when specific events occur. They have to be assigned manually
using the **set_callback** function. Only one function is allowed per callback per 
script. *(Description from Chimera docs)*

**Takes:** `string` callback_name, `string` global_function_name

Example:
```lua
harmony.set_callback("multiplayer sound", "on_multiplayer_sound")
```

#### multiplayer event
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

#### multiplayer sound
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

#### multiplayer hit sound

This is called when the multiplayer ting sound is played.

**Takes:** `number` sound_volume

**Note:** This event will be cancelled if the function returns `false`.

Example:
```lua
function on_multiplayer_hit_sound(sound_volume)
    if(sound_volume == 0) then
        -- Cancel event
        return false
    end

    return true
end

harmony.set_callback("multiplayer hit sound", "on_multiplayer_hit_sound")
```

#### widget accept
This is called when a widget accept event occurs. E.g. When a menu accept button
is pressed.

**Takes:** `number` widget_handle

**Note:** This event will be cancelled if the function returns `false`.

Example:
```lua
function on_widget_accept(widget_handle)
    if(widget_handle == campaign_accept_button_widget_handle) then
        -- Cancel event
        return false
    end

    return true
end

harmony.set_callback("widget accept", "on_widget_accept")
```

### widget close
This is called when returning to the previous menu.

**Takes:** `number` widget_handle

**Note:** This event will be cancelled if the function returns `false`.

Example:
```lua
function on_widget_close(widget_handle)
    if(widget_handle == campaign_accept_button_widget_handle) then
        -- Cancel event
        return false
    end

    return true
end

harmony.set_callback("widget close", "on_widget_close")
```

### widget list tab
This is called when navigating in a widget list using arrow keys.

**Takes:** `string` pressed_button, `number` list_widget_handle, `number` pressed_widget_handle

**Buttons:**
- `a`
- `b`
- `x`
- `y`
- `black`
- `white`
- `left trigger`
- `right trigger`
- `dpad up`
- `dpad down`
- `dpad left`
- `dpad right`
- `start`
- `back`
- `left thumb`
- `right thumb`

**Note:** This event will be cancelled if the function returns `false`.

Example:
```lua
function on_widget_list_tab(pressed_button, list_widget_handle, pressed_widget_handle)
    if(pressed_button == "a") then
        -- Cancel event
        return false
    end

    return true
end

harmony.set_callback("widget list tab", "on_widget_list_tab")
```

### widget mouse button press
This is called when a widget is pressed with a mouse button.

**Takes:** `number` widget_handle, `string` pressed_mouse_button

**Mouse buttons:**
- `left button`
- `middle button`
- `right button`
- `double left button`

**Note:** This event will be cancelled if the function returns `false`.

Example:
```lua
function on_widget_mouse_button_press(widget_handle, pressed_mouse_button)
    if(pressed_mouse_button == "left button") then
        -- Cancel event
        return false
    end

    return true
end

harmony.set_callback("widget mouse button press", "on_widget_mouse_button_press")
```

### widget mouse focus
This is called when a widget is focused by the cursor.

**Takes:** `number` widget_handle

**Note:** This event will be cancelled if the function returns `false`.

Example:
```lua
function on_widget_mouse_focus(widget_handle)
    if(widget_handle == campaign_accept_button_widget_handle) then
        -- Cancel event
        return false
    end

    return true
end

harmony.set_callback("widget mouse focus", "on_widget_mouse_focus")
```

### widget open
This is called when a widget is opened.

**Takes:** `number` widget_handle

**Note:** This event CANNOT be cancelled.

Example:
```lua
function on_widget_open(widget_handle)
    -- Do some stuff
end

harmony.set_callback("widget open", "on_widget_open")
```

### menu sound
This is called when a widget sound is played.

**Takes:** `number` widget_handle, `string` sound_name

**Sounds:**
- `cursor`
- `forward`
- `back`
- `flag failure`

**Note:** This event will be cancelled if the function returns `false`.

Example:
```lua
function on_menu_sound(widget_handle, sound_name)
    if(sound_name == "flag failure") then
        -- Cancel event
        return false
    end

    return true
end

harmony.set_callback("menu sound", "on_menu_sound")
```

### hs function

This is called when a halo script function is called.

**Takes:** `string` script_name, `string` function_name, `table` arguments

**Note:** This event will be cancelled if the function returns `false`. BE CAREFUL WITH THIS.

Example:
```lua
function on_hs_function(script_name, function_name, arguments)
    if(script_name == "ring_loop" and function_name == "camera_set") then
        -- Cancel event
        return false
    end

    return true
end

harmony.set_callback("hs function", "on_hs_function")
```

### key press
This is called when a key is pressed.

**Takes:** `table` modifiers, `string` character, `string` keycode

**Modifiers:**
- `shift`
- `alt`

Example:
```lua
function on_key_press(modifiers, character, keycode)
    if(character == "D") then
        -- Cancel event
        return false
    end

    return true
end

harmony.set_callback("key press", "on_key_press")
```
