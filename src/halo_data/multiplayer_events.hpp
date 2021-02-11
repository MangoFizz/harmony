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
        LOCAL_CTF_SCORE = 33,
        CTF_ENEMY_SCORE,
        CTF_ALLY_SCORE,
        CTF_ENEMY_STOLE_FLAG = 38,
        CTF_ENEMY_RETURNED_FLAG = 40,
        CTF_ALLY_STOLE_FLAG,
        CTF_ALLY_RETURNED_FLAG,
        CTF_FRIENDLY_FLAG_IDLE_RETURNED,
        CTF_ENEMY_FLAG_IDLE_RETURNED
    };

    std::string string_from_multiplayer_event(MultiplayerEvent event) noexcept;
}

#endif
