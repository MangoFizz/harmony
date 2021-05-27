# Optic API 0.0.1

## register_animation
Register an animation to be used later.

**Takes:** `string` animation_name, `number` duration (milliseconds)

Example:
```lua
optic.register_animation("fade out", 200)
```

## add_animation_target
Add an animation sequence to previously created animation.

**Takes: (a)** `string` animation_name, `string` animation_type, `string` animation_property, `number` transformation_value

**Takes: (b)** `string` animation_name, `number` bezier_x1, `string` bezier_y1, `string` bezier_x2, `string` bezier_y2, animation_property, `number` transformation_value

**Note:** There are a set of default animation types and properties to use on these functions:

**Animation Types:**
- `ease in` 
- `ease out` 
- `ease in out` 
- `linear` 

**Animation Properties:**
- `position x`
- `position y`
- `scale x`
- `scale y`
- `opacity`
- `rotation`

Example:

```lua
optic.add_animation_target("fade in", "ease in", "position y", -60)

-- Or giving bezier curve values

optic.add_animation_target("fade in", 0.4, 0.0, 0.6, 1.0, "position y", 60)
```

## create_group
Creates a render group for sprites with specific animations.

**Takes:** `string` group_name, `number` x, `number` y, `number` opacity, `number` rotation, `number` duration (milliseconds), `number` maximum_rendered_groups, `string` in_animation, `string` out_animation, `string` slide_animation

Example:
```lua
optic.create_group("demo", 50, 400, 255, 180, 4000, 0, "fade in", "fade out", "slide")
```

## register_sprite
Creates a sprite from an image.

**Takes:** `string` sprite_name, `string` image_path, `number` width, `number` height

Example:
```lua
optic.register_sprite("hitmarker", "images/hitmarker.png", 35, 35)
```

## render_sprite
Renders a sprite on the specified render group.

**Takes:** `string` render_group, `string` sprite_name

Example:
```lua
optic.render_sprite("demo", "hitmarker")
```

## add_sound_to_sprite
Attach a sound to a specific sprite.

**Takes:** `string` sprite_name, `string` sound_path

Example:
```lua
optic.add_sound_to_sprite("hitmarker", "sounds/hit.wav")
```