// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_HALO_DATA_MULTIPLAYER_EVENTS_HPP
#define HARMONY_HALO_DATA_MULTIPLAYER_EVENTS_HPP

#include <string>

namespace Harmony::HaloData {
    /**
     * Multiplayer event list
     * @todo Find more events for this
     */
    enum MultiplayerEvent : std::uint32_t {
        FALLING_DEATH = 1,
        GUARDIAN_KILL,
        VEHICLE_KILL,
        PLAYER_KILL,
        BETRAYED,
        SUICIDE,
        LOCAL_DOUBLE_KILL,
        LOCAL_KILLED_PLAYER,
        LOCAL_TRIPLE_KILL,
        LOCAL_KILLTACULAR,
        LOCAL_KILLING_SPREE,
        LOCAL_RUNNING_RIOT,
        GAME_TIME_LEFT = 30,
        ENEMY_SCORE = 34,
        ALLY_SCORE = 35,
        ENEMY_STOLE_FLAG = 38,
        ENEMY_RETURNED_FLAG = 40,
        ALLY_STOLE_FLAG = 41,
        ALLY_RETURNED_FLAG = 42,
        FRIENDLY_FLAG_IDLE_RETURNED = 43,
        ENEMY_FLAG_IDLE_RETURNED = 44
    };

    std::string string_from_multiplayer_event(MultiplayerEvent event) noexcept;
}

#endif
