// SPDX-License-Identifier: GPL-3.0-only

#include "multiplayer_events.hpp"

namespace Harmony::HaloData {
    std::string string_from_multiplayer_event(MultiplayerEvent event) noexcept {
        switch(event) {
            case HaloData::MultiplayerEvent::FALLING_DEATH:
                return "falling dead";
            case HaloData::MultiplayerEvent::GUARDIAN_KILL:
                return "guardian kill";
            case HaloData::MultiplayerEvent::VEHICLE_KILL:
                return "vehicle kill";
            case HaloData::MultiplayerEvent::PLAYER_KILL:
                return "player kill";
            case HaloData::MultiplayerEvent::BETRAYED:
                return "betrayed"; // betrayado
            case HaloData::MultiplayerEvent::SUICIDE:
                return "suicide";
            case HaloData::MultiplayerEvent::LOCAL_DOUBLE_KILL:
                return "local double kill";
            case HaloData::MultiplayerEvent::LOCAL_KILLED_PLAYER:
                return "local killed player";
            case HaloData::MultiplayerEvent::LOCAL_TRIPLE_KILL:
                return "local triple kill";
            case HaloData::MultiplayerEvent::LOCAL_KILLTACULAR:
                return "local killtacular";
            case HaloData::MultiplayerEvent::LOCAL_KILLING_SPREE:
                return "local killing spree";
            case HaloData::MultiplayerEvent::LOCAL_RUNNING_RIOT:
                return "local running riot";
            case HaloData::MultiplayerEvent::GAME_TIME_LEFT:
                return "game time left";
            case HaloData::LOCAL_CTF_SCORE:
                return "local ctf score";
            case HaloData::MultiplayerEvent::CTF_ENEMY_SCORE:
                return "ctf enemy score";
            case HaloData::MultiplayerEvent::CTF_ALLY_SCORE:
                return "ctf ally score";
            case HaloData::MultiplayerEvent::CTF_ENEMY_STOLE_FLAG:
                return "ctf enemy stole flag";
            case HaloData::MultiplayerEvent::CTF_ENEMY_RETURNED_FLAG:
                return "ctf enemy returned flag";
            case HaloData::MultiplayerEvent::CTF_ALLY_STOLE_FLAG:
                return "ctf ally stole flag";
            case HaloData::MultiplayerEvent::CTF_ALLY_RETURNED_FLAG:
                return "ctf ally returned flag";
            case HaloData::MultiplayerEvent::CTF_FRIENDLY_FLAG_IDLE_RETURNED:
                return "ctf friendly flag idle returned";
            case HaloData::MultiplayerEvent::CTF_ENEMY_FLAG_IDLE_RETURNED:
                return "ctf enemy flag idle returned";
            default: {
                auto str = "unknown event (" + std::to_string(event) + ")";
                return str.c_str();
            }
        }
    }
}