-- SPDX-License-Identifier: GPL-3.0-only

------------------------------------------------------------------------------
-- Menu fade-in effect
-- This script adds a fade-in effect to menus
-- Source: https://github.com/JerryBrick/harmony
------------------------------------------------------------------------------

clua_version = 2.056

local harmony = require "mods.harmony"
local blam = require "blam"

local animationDurationSecs = 0.20

-- Script globals
local ticksCount = 0
local currentWidget = nil
local animationPlay = false
local animationStartTimestamp = nil
local currentWidgetBackground = nil
local lastWidgetBackground = nil

function OnLoad()
    harmony.math.create_bezier_curve("fade in", "ease in")
end

function OnTick() 
    ticksCount = ticksCount + 1
end

function OnPreframe()
    if(animationPlay and harmony.menu.get_root_widget()) then
        if(animationStartTimestamp == nil) then
            animationStartTimestamp = ticksCount
        end

        -- Calculate elapsed seconds
        local animationElapsedSeconds = (ticksCount - animationStartTimestamp) / 30
        
        if(math.floor(animationElapsedSeconds) < animationDurationSecs) then
            local t = animationElapsedSeconds / animationDurationSecs
            local newOpacity = harmony.math.interpolate_value("fade in", 0, 1, t)
    
            local newWidgetValues = {
                opacity = newOpacity
            }
            
            -- If previous widget background is the same on current widget, just apply the effect to its childs.
            if(currentWidgetBackground == lastWidgetBackground) then
                local currentWidgetValues = harmony.menu.get_widget_values(currentWidget)
                local currentChild = currentWidgetValues.child_widget
                while(currentChild) do
                    harmony.menu.set_widget_values(currentChild, newWidgetValues)
                    local currentWidgetValues = harmony.menu.get_widget_values(currentChild)
                    currentChild = currentWidgetValues.next_widget
                end
            else 
                harmony.menu.set_widget_values(currentWidget, newWidgetValues)
            end
        else
            animationPlay = false
            animationStartTimestamp = nil
        end
    end
end

function OnWidgetOpen(widget)
    currentWidget = widget

    -- Update widget background
    local currentWidgetValues = harmony.menu.get_widget_values(currentWidget)
    local currentWidgetDefinition = blam.uiWidgetDefinition(currentWidgetValues.tag_id)
    lastWidgetBackground = currentWidgetBackground
    currentWidgetBackground = currentWidgetDefinition.backgroundBitmap

    -- Workaround for stock UI widget wrappers. Use wrapped widget instead.
    if(currentWidgetDefinition.name:find("wrapper") or currentWidgetDefinition.name:find("connected")) then
        if(currentWidgetDefinition.childWidgetsCount == 1) then
            local wrappedWidgetDefinition = blam.uiWidgetDefinition(currentWidgetDefinition.childWidgets[1].widgetTag)
            local backgrounBitmap = wrappedWidgetDefinition.backgroundBitmap

            currentWidget = currentWidgetValues.child_widget
            currentWidgetValues = harmony.menu.get_widget_values(currentWidget)
            currentWidgetBackground = backgrounBitmap

            if(wrappedWidgetDefinition.name:find("wrapper")) then
                wrappedWidgetDefinition = blam.uiWidgetDefinition(wrappedWidgetDefinition.childWidgets[1].widgetTag)
                backgrounBitmap = wrappedWidgetDefinition.backgroundBitmap

                local wrappedWidgetValues = harmony.menu.get_widget_values(currentWidgetValues.child_widget)
                currentWidget = wrappedWidgetValues.child_widget
                currentWidgetValues = harmony.menu.get_widget_values(currentWidget)
                currentWidgetBackground = backgrounBitmap
            end
        end
    end

    animationStartTimestamp = nil
    animationPlay = true
end

-- Set up callbacks
set_callback("tick", "OnTick")
set_callback("preframe", "OnPreframe")
harmony.set_callback("widget open", "OnWidgetOpen")

-- Load script stuff
OnLoad()