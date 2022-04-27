-- SPDX-License-Identifier: GPL-3.0-only

------------------------------------------------------------------------------
-- Menu fade-in effect
-- This script adds a fade-in effect to menus
-- Source: https://github.com/JerryBrick/harmony
------------------------------------------------------------------------------

clua_version = 2.056

local harmony = require "mods.harmony"
local blam = require "blam"

-- Duration in milliseconds
local animationDuration = 200

-- Script globals
local animationPlay = false
local animationBezierCurve = nil
local animationStartTimestamp = nil
local currentWidget = nil
local currentWidgetBackground = nil
local lastWidgetBackground = nil

function OnLoad()
    animationBezierCurve = harmony.math.create_bezier_curve("ease in")
end

function OnPreframe()
    if(animationPlay and harmony.menu.get_root_widget()) then
        -- Calculate elapsed seconds
        local animationElapsedMilliseconds = harmony.time.get_elapsed_milliseconds(animationStartTimestamp)
        
        if(animationElapsedMilliseconds < animationDuration) then
            local t = animationElapsedMilliseconds / animationDuration
            local newOpacity = harmony.math.get_bezier_curve_point(animationBezierCurve, 0, 1, t)
    
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
            -- Reset opacity, just in case
            harmony.menu.set_widget_values(currentWidget, { opacity = 1.0 })
            
            animationPlay = false
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

    animationStartTimestamp = harmony.time.set_timestamp()
    animationPlay = true
end

-- Set up callbacks
set_callback("preframe", "OnPreframe")
harmony.set_callback("widget open", "OnWidgetOpen")

-- Load script stuff
OnLoad()
