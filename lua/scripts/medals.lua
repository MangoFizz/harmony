-- SPDX-License-Identifier: GPL-3.0-only

------------------------------------------------------------------------------
-- Medals
-- Adds a basic medals system; based on HAC2 medals packs
-- Source: https://github.com/JerryBrick/harmony
------------------------------------------------------------------------------

clua_version = 2.056

local blam = require "blam"
local harmony = require "harmony"
local optic = harmony.optic

-- Paramenters
local size = 20
local offsetX, offsetY = 20, 280
local opacity = 255
local rotation = 0
local duration = 4000
local fadeAnimationsDuration = 200
local slideAnimationDuration = 300
local enableAudio = true

-- More stuff
local screenWidth = read_word(blam.addressList.screenWidth)
local screenHeight = read_word(blam.addressList.screenHeight)
local spriteSize = screenWidth * (size / 640)

-- Optic resources
local fadeInAnimation
local fadeOutAnimation
local slideAnimation
local renderQueue
local audioEngine

-- Spree counters
local killingSpreeCount = 0
local dyingSpreeCount = 0
local deathsCount = 0
local multikillCounts = {}
local multikillTimestamps = {}
local lastDeathTimestamp = nil
local lastkillesby = nil

-- Medals resources
local medals = {
    killjoy = {name = "killjoy"},
    avenger = {name = "avenger", audio = "hologram"},
    fromTheGrave = {name = "from_the_grave", audio = "beam"},
    revenge = {name = "revenge"},
    perfection = {name  = "perfection"},
    suicide = {name = "suicide"},
    flagScore = {name = "flag_score", audio = "flag_captured"},

    -- Multikills
    doubleKill = {name = "double_kill"},
    tripleKill = {name = "triple_kill"},
    overkill = {name = "overkill"},
    killtacular = {name = "killtacular"},
    killtrocity = {name = "killtrocity"},
    killimanjaro = {name = "killimanjaro"},
    killtastrophe = {name = "killtastrophe"},
    killpocalypse = {name = "killpocalypse"},
    killionaire = {name = "killionaire"},

    -- Killing sprees
    killingSpree = {name = "killing_spree"},
    killingFrenzy = {name = "killing_frenzy"},
    runningRiot = {name = "running_riot"},
    rampage = {name = "rampage"},
    untouchable = {name = "untouchable"},
    invincible = {name = "invincible"},
    inconceivable = {name = "inconceivable"},
    unfriggenbelievable = {name = "unfriggenbelievable"}
}

local function printMedalHud(str)
    hud_message(str:gsub("_", " "):gsub("^%l", string.upper) .. "!")
end

local function renderMedal(medal)
    if(medal.sprite) then
        optic.renderSprite(medal.sprite, renderQueue)
    end

    if(enableAudio and medal.sound) then
        optic.playSound(medal.sound, audioEngine)
    end

    printMedalHud(medal.name);
end

function OnMapLoad() 
    killingSpreeCount = 0
    deathsCount = 0
    dyingSpreeCount = 0
    multikillCounts = {}
    multikillTimestamps = {}
    lastDeathTimestamp = nil
    lastkillesby = nil
end

function OnMultiplayerSound(sound)
    if(sound == "game over") then
        if(killingSpreeCount >= 15 and deathsCount == 0) then
            renderMedal(medals.perfection)
        end
    end
    return true
end

function OnMultiplayerEvent(event, localId, killerId, victimId)
    if(event == "local killed player") then
        if(localId == killerId) then
            killingSpreeCount = killingSpreeCount + 1
    
            -- Killing spree medals
            if (killingSpreeCount == 5) then
                renderMedal(medals.killingSpree)
            elseif (killingSpreeCount == 10) then
                renderMedal(medals.killingFrenzy)
            elseif (killingSpreeCount == 15) then
                renderMedal(medals.runningRiot)
            elseif (killingSpreeCount == 20) then
                renderMedal(medals.rampage)
            elseif (killingSpreeCount == 25) then
                renderMedal(medals.untouchable)
            elseif (killingSpreeCount == 30) then
                renderMedal(medals.invincible)
            elseif (killingSpreeCount == 35) then
                renderMedal(medals.inconceivable)
            elseif (killingSpreeCount == 40) then
                renderMedal(medals.unfriggenbelievable)
            end
    
            -- Multikill medals
            if (multikillTimestamps[localId] == nil) then
                multikillTimestamps[localId] = harmony.time.setTimestamp()
                multikillCounts[localId] = 1
            else
                multikillCounts[localId] = multikillCounts[localId] + 1
    
                -- Check if the 4.5 seconds have already elapsed
                local time = harmony.time.getElapsedMilliseconds(multikillTimestamps[localId])
                if(time < 4500) then
                    local multikillCount = multikillCounts[localId] 
                    if(multikillCount == 2) then
                        renderMedal(medals.doubleKill)
                    elseif(multikillCount == 3) then
                        renderMedal(medals.tripleKill)
                    elseif(multikillCount == 4) then
                        renderMedal(medals.overkill)
                    elseif(multikillCount == 5) then
                        renderMedal(medals.killtacular)
                    elseif(multikillCount == 6) then
                        renderMedal(medals.killtrocity)
                    elseif(multikillCount == 7) then
                        renderMedal(medals.killimanjaro)
                    elseif(multikillCount == 8) then
                        renderMedal(medals.killtastrophe)
                    elseif(multikillCount == 9) then
                        renderMedal(medals.killpocalypse)
                    elseif(multikillCount == 10) then
                        renderMedal(medals.killionaire)
                    end

                    if(multikillCount <= 10) then
                        multikillTimestamps[localId] = harmony.time.setTimestamp()
                    else
                        multikillTimestamps[localId] = harmony.time.setTimestamp()
                        multikillCounts[localId] = 1
                    end
                else
                    multikillTimestamps[localId] = harmony.time.setTimestamp()
                    multikillCounts[localId] = 1
                end
            end
        else
            if(multikillTimestamps[killerId] == nil) then
                multikillCounts[killerId] = 1
            else
                multikillCounts[killerId] = multikillCounts[killerId] + 1
            end

            multikillTimestamps[killerId] = harmony.time.setTimestamp()
        end

        if(multikillTimestamps[victimId] ~= nil) then
            local elapsedMS = harmony.time.getElapsedMilliseconds(multikillTimestamps[victimId])
            if(elapsedMS <= 700 and victimId ~= localId) then
                renderMedal(medals.avenger)
            end

            if(multikillCounts[victimId] >= 5) then
                renderMedal(medals.killjoy)
            end
        end

        if(lastDeathTimestamp and harmony.time.getElapsedMilliseconds(lastDeathTimestamp) <= 3000) then
            renderMedal(medals.fromTheGrave)
        end

        if(lastkillesby and lastkillesby == victimId) then
            renderMedal(medals.revenge)
            lastkillesby = nil
        end
        
        -- Count player dead
        if (localId == victimId) then
            killingSpreeCount = 0
            dyingSpreeCount = dyingSpreeCount - 1
            deathsCount = deathsCount + 1
            lastkillesby = killerId
            lastDeathTimestamp = harmony.time.setTimestamp()
        end

        multikillCounts[victimId] = 0
        multikillTimestamps[victimId] = nil
    end

    if(event == "suicide") then
        if(localId == victimId) then
            -- Reset stuff
            killingSpreeCount = 0
            dyingSpreeCount = dyingSpreeCount - 1
            lastkillesby = nil
            lastDeathTimestamp = harmony.time.setTimestamp()

            -- Play suicide sound
            renderMedal(medals.suicide)
        else
            multikillCounts[victimId] = 0
            multikillTimestamps[victimId] = nil
        end
    end

    if(event == "local ctf score") then
        renderMedal(medals.flagScore)
    end
end

function OnUnload() 
    -- Unmute announcer
    harmony.multiplayer.muteAnnouncer(false)
end

function OnLoad()
    local imagesPath = "images/%s.png"
    local soundsPath = "audio/%s.mp3"

    for key, value in pairs(medals) do
        local spritePath = imagesPath:format(value.name)
        if(file_exists(spritePath)) then
            local spriteHandle = optic.createSprite(spritePath, spriteSize, spriteSize)
            medals[key].sprite = spriteHandle
        end

        if(enableAudio) then
            local soundPath = soundsPath:format(value.name)
            if(file_exists(soundPath)) then
                local soundHandle = optic.createSound(soundPath)
                medals[key].sound = soundHandle
            else
                soundPath = soundsPath:format(value.audio)
                if(file_exists(soundPath)) then
                    local soundHandle = optic.createSound(soundPath)
                    medals[key].sound = soundHandle
                end
            end
        end
    end

    fadeInAnimation = optic.createAnimation(fadeAnimationsDuration)
    optic.setAnimationProperty(fadeInAnimation, "ease in", "position x", spriteSize)
    optic.setAnimationProperty(fadeInAnimation, "ease in", "opacity", 255)

    fadeOutAnimation = optic.createAnimation(fadeAnimationsDuration)
    optic.setAnimationProperty(fadeOutAnimation, "ease out", "opacity", -255)
    
    slideAnimation = optic.createAnimation(fadeAnimationsDuration)
    optic.setAnimationProperty(slideAnimation, "ease in out", "position x", spriteSize)
    optic.setAnimationProperty(slideAnimation, "ease in out", "position y", 1)

    local screenOffsetX = screenWidth * (offsetX / 640)
    local screenOffsetY = screenHeight * (offsetY / 480)
    renderQueue = optic.createRenderQueue(screenOffsetX, screenOffsetY, opacity, rotation, duration, 0, fadeInAnimation, fadeOutAnimation, slideAnimation)

    if(enableAudio) then
        audioEngine = optic.createAudioEngine()        
    end

    -- Mute announcer
    harmony.multiplayer.muteAnnouncer(true)

    -- Set harmony callbacks
    harmony.setCallback("multiplayer event", "OnMultiplayerEvent")
    harmony.setCallback("multiplayer sound", "OnMultiplayerSound")

    -- Set chimera callbacks
    set_callback("map load", "OnMapLoad")
    set_callback("unload", "OnUnload")
end

-- Load everything
OnLoad()
