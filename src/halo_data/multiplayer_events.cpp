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
            case HaloData::MultiplayerEvent::ENEMY_SCORE:
                return "enemy score";
            case HaloData::MultiplayerEvent::ALLY_SCORE:
                return "ally score";
            case HaloData::MultiplayerEvent::ENEMY_STOLE_FLAG:
                return "enemy stole flag";
            case HaloData::MultiplayerEvent::ENEMY_RETURNED_FLAG:
                return "enemy returned flag";
            case HaloData::MultiplayerEvent::ALLY_STOLE_FLAG:
                return "ally stole flag";
            case HaloData::MultiplayerEvent::ALLY_RETURNED_FLAG:
                return "ally returned flag";
            case HaloData::MultiplayerEvent::FRIENDLY_FLAG_IDLE_RETURNED:
                return "friendly flag idle returned";
            case HaloData::MultiplayerEvent::ENEMY_FLAG_IDLE_RETURNED:
                return "enemy flag idle returned";
            default: {
                auto str = "unknown event " + std::to_string(static_cast<std::uint32_t>(event));
                return str.c_str();
            }
        }
    }
}