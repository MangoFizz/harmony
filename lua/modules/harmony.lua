-- SPDX-License-Identifier: GPL-3.0-only

------------------------------------------------------------------------------
-- Harmony cC wrapper
-- This allows you to use Harmony with a camel case naming convention
-- Source: https://github.com/JerryBrick/harmony
------------------------------------------------------------------------------

local harmonyWrapper = {
    _table = require "mods.harmony"
}

-- Function by cyclaminist from https://codegolf.stackexchange.com/a/177958
local function toSneakCase(s)
    return s:gsub('%f[^%l]%u','_%1'):gsub('%f[^%a]%d','_%1'):gsub('%f[^%d]%a','_%1'):gsub('(%u)(%u%l)','%1_%2'):lower()
end

local metatable = {}
metatable.__index = function(object, key)
    local sneakCaseKey = toSneakCase(key)
    local field = object._table[sneakCaseKey]
    if(type(field) == "table") then
        local tableWrapper = {
            _table = field
        }
        setmetatable(tableWrapper, metatable)
        return tableWrapper
    end
    return field
end

setmetatable(harmonyWrapper, metatable)

return harmonyWrapper
