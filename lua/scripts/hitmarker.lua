-- SPDX-License-Identifier: GPL-3.0-only

------------------------------------------------------------------------------
-- Hitmarker
-- Adds an animated hitmarker
-- Source: https://github.com/JerryBrick/harmony
------------------------------------------------------------------------------

clua_version = 2.056

local blam = require "blam"
local harmony = require "harmony"
local optic = harmony.optic

-- Paramenters
local duration = 140
local size = 3
local enableSound = true

local screenWidth = read_word(blam.addressList.screenWidth)
local screenHeight = read_word(blam.addressList.screenHeight)
local markerCornerSize = screenWidth * (size / 640)
local animationDuration = duration
local fadeOutDuration = duration / 3
local animationDisplacement = markerCornerSize * 2
local killmarker = false

-- Optic resources
local hitmarkerCornerSprite
local killmarkerCornerSprite
local topLeftCornerAnim
local topRightCornerAnim
local bottomLeftCornerAnim
local bottomRightCornerAnim
local FadeOutAnim
local hitSound
local audioEngine

local function renderMarker(sprite) 
    local positionX = (screenWidth - markerCornerSize) / 2
    local positionY = (screenHeight - markerCornerSize) / 2
    local displacement = markerCornerSize * 4.5
    local opacity = 255
    optic.renderSprite(sprite, positionX - displacement, positionY - displacement, opacity, 180, duration, topLeftCornerAnim, FadeOutAnim)
    optic.renderSprite(sprite, positionX + displacement, positionY - displacement, opacity, -90, duration, topRightCornerAnim, FadeOutAnim)
    optic.renderSprite(sprite, positionX - displacement, positionY + displacement, opacity, 90, duration, bottomLeftCornerAnim, FadeOutAnim)
    optic.renderSprite(sprite, positionX + displacement, positionY + displacement, opacity, 0, duration, bottomRightCornerAnim, FadeOutAnim)
end

function OnMultiplayerEvent(eventName, localId, killerId, victimId)
    if(eventName == "local killed player") then
        if(localId == killerId) then
            renderMarker(killmarkerCornerSprite)
            optic.playSound(hitSound, audioEngine, true)

            -- Block hitmarker
            killmarker = true
        end
    end
end

function OnMultiplayerSound(sound)
    if(sound == "ting") then
        if(not killmarker) then
            renderMarker(hitmarkerCornerSprite)
        else
            killmarker = false
            return false
        end
    end
    return true
end

function OnLoad()
    hitmarkerCornerSprite = optic.createSprite("images/hm_blue_corner.png", markerCornerSize, markerCornerSize)
    killmarkerCornerSprite = optic.createSprite("images/hm_red_corner.png", markerCornerSize, markerCornerSize)

    topLeftCornerAnim = optic.createAnimation(animationDuration)
    optic.setAnimationProperty(topLeftCornerAnim, "ease in out", "position x", -animationDisplacement)
    optic.setAnimationProperty(topLeftCornerAnim, "ease in out", "position y", -animationDisplacement)

    topRightCornerAnim = optic.createAnimation(animationDuration)
    optic.setAnimationProperty(topRightCornerAnim, "ease in out", "position x", animationDisplacement)
    optic.setAnimationProperty(topRightCornerAnim, "ease in out", "position y", -animationDisplacement)

    bottomLeftCornerAnim = optic.createAnimation(animationDuration)
    optic.setAnimationProperty(bottomLeftCornerAnim, "ease in out", "position x", -animationDisplacement)
    optic.setAnimationProperty(bottomLeftCornerAnim, "ease in out", "position y", animationDisplacement)

    bottomRightCornerAnim = optic.createAnimation(animationDuration)
    optic.setAnimationProperty(bottomRightCornerAnim, "ease in out", "position x", animationDisplacement)
    optic.setAnimationProperty(bottomRightCornerAnim, "ease in out", "position y", animationDisplacement)

    FadeOutAnim = optic.createAnimation(duration / 3)
    optic.setAnimationProperty(FadeOutAnim, "linear", "opacity", -255)

    hitSound = optic.createSound("sounds/hit.wav")
    audioEngine = optic.createAudioEngine()
    
    -- Set harmony callbacks
    harmony.setCallback("multiplayer event", "OnMultiplayerEvent")
    harmony.setCallback("multiplayer sound", "OnMultiplayerSound")
end

-- Load stuff
OnLoad()
