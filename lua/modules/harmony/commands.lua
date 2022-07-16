-- SPDX-License-Identifier: GPL-3.0-only

------------------------------------------------------------------------------
-- Harmony command parser
-- Source: https://github.com/JerryBrick/harmony
------------------------------------------------------------------------------

local harmony = require "mods.harmony"

local commandsFile = "commands.txt"
local commandsPrefix = nil
local commands = {}

-- Hack from http://lua-users.org/wiki/SplitJoin
function string:split(sep)
    local sep, fields = sep or ":", {}
    local pattern = string.format("([^%s]+)", sep)
    self:gsub(pattern, function(c) fields[#fields+1] = c end)
    return fields
end

local function set_prefix(prefix)
    commandsPrefix = prefix
end

local function check_prefix(command)
    if(commandsPrefix == nil) then
        return true
    end
    return command:sub(1, #commandsPrefix) == commandsPrefix
end

local function get_command_name(name)
    if(commandsPrefix ~= nil) then
        return name:sub(#commandsPrefix + 2)
    end
    return name
end

local function add_command(name, func, desc, minimumArguments, maximumArguments, argumentsTypes, saves)
    commands[name] = {
        func = func,
        desc = desc,
        minimumArguments = minimumArguments,
        maximumArguments = maximumArguments,
        argumentsTypes = argumentsTypes,
        saves = saves
    }
end

local function update_setting(newSetting)
    local settingsFileContents = read_file(commandsFile)
    if(not settingsFileContents) then
        write_file(commandsFile, newSetting)
        return
    end

    local newSettingSlices = harmony.misc.split_command(newSetting)
    local newSettingName = newSettingSlices[1]

    local settings = {}
    local overwrited = false
    for setting in string.gmatch(settingsFileContents, "\n") do
        if(setting ~= "" and setting ~= "\n") then            
            local settingSlices = harmony.misc.split_command(setting)
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

local function print_help(commandName)
    local commandData = commands[commandName]
    local output = ""
    for index, value in ipairs(commandData.argumentsTypes) do
        if(index <= commandData.minimumArguments) then
            output = output .. "<" .. value .. "> "
        else
            output = output .. "[" .. value .. "] "
        end
    end
    local color = {1, 0.66, 0.66, 0.66}
    local prefixedName = get_command_name(commandName)
    console_out("usage: " .. prefixedName .. " " .. output, table.unpack(color))
    console_out(commandData.desc, table.unpack(color))
end

local function execute_command(command, doNotSave)
    local commandSlices = harmony.misc.split_command(command)
    local commandName = commandSlices[1]

    if(not check_prefix(commandName)) then
        if(commandName == "help" and #commandSlices == 2 and check_prefix(commandSlices[2])) then
            commandName = get_command_name(commandSlices[2])
            local commandData = commands[commandName]
            if(commandData) then
                print_help(commandName)
                return true
            else
                return false;
            end
        end
        return
    end

    commandName = get_command_name(commandSlices[1])
    
    -- Remove command name from arguments
    table.remove(commandSlices, 1)
    
    local commandData = commands[commandName]

    if(commandData) then
        local arguments = commandSlices

        if(#arguments < commandData.minimumArguments or #arguments > commandData.maximumArguments) then
            console_out(commandName .. ": invalid number of arguments")
            return true
        end

        for index, argument in ipairs(arguments) do
            local argumentType = commandData.argumentsTypes[index]

            -- Try to resolve types
            if(argumentType == "number" and tonumber(argument)) then
                arguments[index] = tonumber(argument)

            elseif(argumentType == "boolean") then
                if(argument == "true" or argument == "1") then
                    arguments[index] = true
                elseif(argument == "false" or argument == "0") then
                    arguments[index] = false
                end

            elseif(type(argument) ~= argumentType) then
                console_out(commandName .. ": invalid argument #" .. index .. " type (" .. argumentType .. " expected).")
                return true
            end
        end

        commandData.func(table.unpack(arguments))

        -- If there is something to save, save it
        if(#arguments > 0) then
            if((doNotSave == nil or not doNotSave) and commandData.saves) then
                update_setting(command)
            end
        end

        return true
    else
        return false
    end
end

local function read_settings()
    local settingsFileContents = read_file(commandsFile)
    if(not settingsFileContents) then
        return
    end

    local settingsSlices = settingsFileContents:split("\n")
    for _, setting in ipairs(settingsSlices) do
        execute_command(setting, true)
    end
end

return {
    add_command = add_command,
    set_prefix = set_prefix,
    read_settings = read_settings,
    update_setting = update_setting,
    print_help = print_help,
    execute_command = execute_command
}
