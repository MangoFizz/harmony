-- SPDX-License-Identifier: GPL-3.0-only

clua_version = 2.056

local harmony = require "mods.harmony"

function on_script_function(script_name, function_name, params)
    local params_str = ""
    for i = 1, #params do
        params_str = params_str .. params[i] .. " "
    end
    console_out((script_name or "null") .. ": " .. function_name .. " " .. params_str)
end

harmony.set_callback("script function", "on_script_function")
