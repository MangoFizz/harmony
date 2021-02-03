// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_HALO_DATA_SOUNDS
#define HARMONY_HALO_DATA_SOUNDS

#include <string>

namespace Harmony::HaloData {
    enum struct MultiplayerSound {
        PLAYBALL,
        GAME_OVER,
        ONE_MINUTE_TO_WIN,
        THIRTY_SECONDS_TO_WIN,
        RED_TEAM_ONE_MINUTE_TO_WIN,
        RED_TEAM_THIRTY_SECONDS_TO_WIN,
        BLUE_TEAM_ONE_MINUTE_TO_WIN,
        BLUE_TEAM_THIRTY_SECONDS_TO_WIN,
        RED_TEAM_FLAG_TAKEN,
        RED_TEAM_FLAG_RETURNED,
        RED_TEAM_FLAG_CAPTURED,
        BLUE_TEAM_FLAG_TAKEN,
        BLUE_TEAM_FLAG_RETURNED,
        BLUE_TEAM_FLAG_CAPTURED,
        DOUBLE_KILL,
        TRIPLE_KILL,
        KILLTACULAR,
        RUNNING_RIOT,
        KILLING_SPREE,
        ODDBALL,
        RACE,
        SLAYER,
        CAPTURE_THE_FLAG,
        WARTHOG,
        GHOST,
        SCORPION,
        COUNTDOWN_TIMER,
        TELEPORTER_ACTIVATE,
        FLAG_FAILURE,
        COUNTDOWN_FOR_RESPAWN,
        HILL_MOVE,
        PLAYER_RESPAWN,
        KING_OF_THE_HILL,
        ODD_BALL,
        TEAM_RACE,
        TEAM_SLAYER,
        TEAM_KING_OF_THE_HILL,
        BLUE_TEAM_CAPTURE_THE_FLAG,
        RED_TEAM_CAPTURE_THE_FLAG,
        CONTEST,
        CONTROL,
        HILL_OCCUPIED,
        COUNTDOWN_TIMER_END,
        TING,

        CUSTOM_1,
        CUSTOM_2,
        CUSTOM_3,
        CUSTOM_4,
        CUSTOM_5,
        CUSTOM_6,
        CUSTOM_7,
        CUSTOM_8,
        CUSTOM_9,
        CUSTOM_10,
        CUSTOM_11,
        CUSTOM_12,
        CUSTOM_13,
        CUSTOM_14,
        CUSTOM_15,
        CUSTOM_16
    };

    std::string string_from_multiplayer_sound(MultiplayerSound sound) noexcept;
}

#endif
