--------------------------------------
-- UI true widescreen demo
--------------------------------------

clua_version = 2.056

local harmony = require "mods.harmony"

harmony.ui.set_aspect_ratio(16, 9)

function onMenuAccept(tag_id)
    console_out("[accept] " .. tag_id)
    return true
end

function onMenuBack(menu_id)
    console_out("[back] " .. menu_id)
    return true
end

function onMenuListTab(key, list_id, button_id)
    console_out("[" .. key .. "] " .. button_id)
    return true
end

function onMenuMouseButtonPress(tag_id, button)
    console_out("[" .. button .. "] " .. button)
    return true
end

function onMenuSound(button_id, sound)
    console_out("[sound] " .. button_id .. " (" .. sound .. ")")
    return true
end

harmony.set_callback("menu accept", "onMenuAccept")
harmony.set_callback("menu back", "onMenuBack")
harmony.set_callback("menu list tab", "onMenuListTab")
harmony.set_callback("menu mouse button press", "onMenuMouseButtonPress")
harmony.set_callback("menu sound", "onMenuSound")
