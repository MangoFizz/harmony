--------------------------------------
-- UI true widescreen demo
--------------------------------------

clua_version = 2.056

local harmony = require "mods.harmony"

function onMapLoad()
    harmony.ui.set_aspect_ratio(16, 9)
end

function onUnload()
    harmony.ui.set_aspect_ratio(4, 3)
end

set_callback("map load", "onMapLoad")
set_callback("unload", "onUnload")
