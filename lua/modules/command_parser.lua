-- SPDX-License-Identifier: GPL-3.0-only

------------------------------------------------------------------------------
-- Harmony command parser
-- Source: https://github.com/JerryBrick/harmony
------------------------------------------------------------------------------

local harmony = require "harmony"

local commandParser = {}
local commandsFile = "commands.txt"

-- Commands store
commandParser.commands = {}

-- Hack from http://lua-users.org/wiki/SplitJoin
function string:split(sep)
    local sep, fields = sep or ":", {}
    local pattern = string.format("([^%s]+)", sep)
    self:gsub(pattern, function(c) fields[#fields+1] = c end)
    return fields
 end

local function addCommand(name, func, minimumArguments, maximumArguments, argumentsTypes, saves)
    commandParser.commands[name] = {
        func = func,
        minimumArguments = minimumArguments,
        maximumArguments = maximumArguments,
        argumentsTypes = argumentsTypes,
        saves = saves
    }
end

local function updateSetting(newSetting)
    local settingsFileContents = read_file(commandsFile)
    if(not settingsFileContents) then
        write_file(commandsFile, newSetting)
        return
    end

    local newSettingSlices = harmony.misc.splitCommand(newSetting)
    local newSettingName = newSettingSlices[1]

    local settings = {}
    local overwrited = false
    for setting in string.gmatch(settingsFileContents, "\n") do
        if(setting ~= "") then            
            local settingSlices = harmony.misc.splitCommand(setting)
            local settingName = settingSlices[1]
            if(settingName == newSettingName) then
                table.insert(settings, newSetting)
                overwrited = true
            else
                table.insert(settings, setting)
            end
        end
    end

    if(not overwrited) then
        table.insert(settings, newSetting)
    end

    local settingsOutput = ""
    for _, setting in ipairs(settings) do
        settingsOutput = settingsOutput .. setting .. "\n"
    end
    write_file(commandsFile, settingsOutput)
end

local function printHelp(commandName)
    local commandData = commandParser.commands[commandName]
    local output = ""
    for index, value in ipairs(commandData.argumentsTypes) do
        if(index <= commandData.minimumArguments) then
            output = output .. "<" .. value .. "> "
        else
            output = output .. "[" .. value .. "] "
        end
    end
    console_out("Usage: " .. commandName .. " " .. output)
end

local function executeCommand(command, doNotSave)
    local commandSlices = harmony.misc.splitCommand(command)
    local commandName = commandSlices[1]

    if(commandName == "help" and #commandSlices == 2) then
        local commandData = commandParser.commands[commandSlices[2]]
        if(commandData) then
            printHelp(commandSlices[2])
            return true
        end
    end
    
    -- Remove command name from arguments
    table.remove(commandSlices, 1)

    local commandData = commandParser.commands[commandName]

    if(commandData) then
        local arguments = commandSlices
        if(#arguments == 0) then
            console_out(commandName .. ": " .. commandData.lastValue)
            return true
        end

        if(#arguments < commandData.minimumArguments or #arguments > commandData.maximumArguments) then
            console_out(commandName .. ": invalid number of arguments")
            return true
        end

        for index, value in ipairs(commandData.argumentsTypes) do
            -- Try to resolve types
            if(value == "number" and tonumber(arguments[index])) then
                arguments[index] = tonumber(arguments[index])
                
            elseif(value == "boolean") then
                if(arguments[index] == "true" or arguments[index] == 1) then
                    arguments[index] = true
                elseif(arguments[index] == "false" or arguments[index] == 0) then
                    arguments[index] = false
                end
            end

            if(type(arguments[index]) ~= value) then
                console_out(commandName .. ": invalid argument #" .. index .. " type (" .. value .. " expected).")
                return true
            end
        end

        commandData.func(table.unpack(arguments))

        -- Save last value
        commandParser.commands[commandName].lastValue = table.concat(arguments, " ")

        -- Save command
        if((doNotSave == nil or not doNotSave) and commandData.saves) then
            updateSetting(command)
            console_out(commandName .. ": " .. table.concat(arguments, " "))
        end
        
        return true
    else
        return false
    end
end

local function readSettings()
    local settingsFileContents = read_file(commandsFile)
    if(not settingsFileContents) then
        return
    end

    local settingsSlices = settingsFileContents:split("\n")
    for _, setting in ipairs(settingsSlices) do
        executeCommand(setting, true)
    end
end

commandParser.addCommand = addCommand
commandParser.updateSetting = updateSetting
commandParser.executeCommand = executeCommand
commandParser.readSettings = readSettings

return commandParser
