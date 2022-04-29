-- SPDX-License-Identifier: GPL-3.0-only

------------------------------------------------------------------------------
-- Menu fade-in effect
-- Adds a fade-in effect to menus
-- Source: https://github.com/JerryBrick/harmony
------------------------------------------------------------------------------

clua_version = 2.056

local harmony = require "harmony"
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

function OnPreframe()
    if(animationPlay and harmony.menu.getRootWidget()) then
        -- Calculate elapsed seconds
        local animationElapsedMilliseconds = harmony.time.getElapsedMilliseconds(animationStartTimestamp)
        
        if(animationElapsedMilliseconds < animationDuration) then
            local t = animationElapsedMilliseconds / animationDuration
            local newOpacity = harmony.math.getBezierCurvePoint(animationBezierCurve, 0, 1, t)
    
            local newWidgetValues = {
                opacity = newOpacity
            }
            
            -- If previous widget background is the same on current widget, just apply the effect to its childs.
            if(currentWidgetBackground == lastWidgetBackground) then
                local currentWidgetValues = harmony.menu.getWidgetValues(currentWidget)
                local currentChild = currentWidgetValues.child_widget
                while(currentChild) do
                    harmony.menu.setWidgetValues(currentChild, newWidgetValues)
                    local currentWidgetValues = harmony.menu.getWidgetValues(currentChild)
                    currentChild = currentWidgetValues.next_widget
                end
            else 
                harmony.menu.setWidgetValues(currentWidget, newWidgetValues)
            end
        else
            -- Reset opacity, just in case
            harmony.menu.setWidgetValues(currentWidget, { opacity = 1.0 })
            
            animationPlay = false
        end
    end
end

function OnWidgetOpen(widget)
    currentWidget = widget

    -- Update widget background
    local currentWidgetValues = harmony.menu.getWidgetValues(currentWidget)
    local currentWidgetDefinition = blam.uiWidgetDefinition(currentWidgetValues.tag_id)
    lastWidgetBackground = currentWidgetBackground
    currentWidgetBackground = currentWidgetDefinition.backgroundBitmap

    -- Workaround for stock UI widget wrappers. Use wrapped widget instead.
    if(currentWidgetDefinition.name:find("wrapper") or currentWidgetDefinition.name:find("connected")) then
        if(currentWidgetDefinition.childWidgetsCount == 1) then
            local wrappedWidgetDefinition = blam.uiWidgetDefinition(currentWidgetDefinition.childWidgets[1].widgetTag)
            local backgrounBitmap = wrappedWidgetDefinition.backgroundBitmap

            currentWidget = currentWidgetValues.child_widget
            currentWidgetValues = harmony.menu.getWidgetValues(currentWidget)
            currentWidgetBackground = backgrounBitmap

            if(wrappedWidgetDefinition.name:find("wrapper")) then
                wrappedWidgetDefinition = blam.uiWidgetDefinition(wrappedWidgetDefinition.childWidgets[1].widgetTag)
                backgrounBitmap = wrappedWidgetDefinition.backgroundBitmap

                local wrappedWidgetValues = harmony.menu.getWidgetValues(currentWidgetValues.child_widget)
                currentWidget = wrappedWidgetValues.child_widget
                currentWidgetValues = harmony.menu.getWidgetValues(currentWidget)
                currentWidgetBackground = backgrounBitmap
            end
        end
    end

    animationStartTimestamp = harmony.time.setTimestamp()
    animationPlay = true
end

function OnLoad()
    animationBezierCurve = harmony.math.createBezierCurve("ease in")

    -- Set up callbacks
    set_callback("preframe", "OnPreframe")
    harmony.setCallback("widget open", "OnWidgetOpen")
end

-- Load script stuff
OnLoad()
