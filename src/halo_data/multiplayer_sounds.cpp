// SPDX-License-Identifier: GPL-3.0-only

#include "multiplayer_sounds.hpp"

namespace Harmony::HaloData {
    std::string string_from_multiplayer_sound(MultiplayerSound sound) noexcept {
        switch(sound) {
            case MULTIPLAYER_SOUND_PLAYBALL:
                return "playball";
            case MULTIPLAYER_SOUND_GAME_OVER:
                return "game over";
            case MULTIPLAYER_SOUND_ONE_MINUTE_TO_WIN:
                return "one minute to win";
            case MULTIPLAYER_SOUND_THIRTY_SECONDS_TO_WIN:
                return "thirty seconds to win";
            case MULTIPLAYER_SOUND_RED_TEAM_ONE_MINUTE_TO_WIN:
                return "red team one minute to win";
            case MULTIPLAYER_SOUND_RED_TEAM_THIRTY_SECONDS_TO_WIN:
                return "red team thirty seconds to win";
            case MULTIPLAYER_SOUND_BLUE_TEAM_ONE_MINUTE_TO_WIN:
                return "blue team one minute to win";
            case MULTIPLAYER_SOUND_BLUE_TEAM_THIRTY_SECONDS_TO_WIN:
                return "red team thirty seconds to win";
            case MULTIPLAYER_SOUND_RED_TEAM_FLAG_TAKEN:
                return "red team flag taken";
            case MULTIPLAYER_SOUND_RED_TEAM_FLAG_RETURNED:
                return "red team flag returned";
            case MULTIPLAYER_SOUND_RED_TEAM_FLAG_CAPTURED:
                return "red team flag captured";
            case MULTIPLAYER_SOUND_BLUE_TEAM_FLAG_TAKEN:
                return "blue team flag taken";
            case MULTIPLAYER_SOUND_BLUE_TEAM_FLAG_RETURNED:
                return "blue team flag returned";
            case MULTIPLAYER_SOUND_BLUE_TEAM_FLAG_CAPTURED:
                return "blue team flag captured";
            case MULTIPLAYER_SOUND_DOUBLE_KILL:
                return "double kill";
            case MULTIPLAYER_SOUND_TRIPLE_KILL:
                return "triple kill";
            case MULTIPLAYER_SOUND_KILLTACULAR:
                return "killtacular";
            case MULTIPLAYER_SOUND_RUNNING_RIOT:
                return "running riot";
            case MULTIPLAYER_SOUND_KILLING_SPREE:
                return "killing spree";
            case MULTIPLAYER_SOUND_ODDBALL:
                return "oddball";
            case MULTIPLAYER_SOUND_RACE:
                return "race";
            case MULTIPLAYER_SOUND_SLAYER:
                return "slayer";
            case MULTIPLAYER_SOUND_CAPTURE_THE_FLAG:
                return "capture the flag";
            case MULTIPLAYER_SOUND_WARTHOG:
                return "warthog";
            case MULTIPLAYER_SOUND_GHOST:
                return "ghost";
            case MULTIPLAYER_SOUND_SCORPION:
                return "scorpion";
            case MULTIPLAYER_SOUND_COUNTDOWN_TIMER:
                return "countdown timer";
            case MULTIPLAYER_SOUND_TELEPORTER_ACTIVATE:
                return "teleporter activate";
            case MULTIPLAYER_SOUND_FLAG_FAILURE:
                return "flag failure";
            case MULTIPLAYER_SOUND_COUNTDOWN_FOR_RESPAWN:
                return "countdown for respawn";
            case MULTIPLAYER_SOUND_HILL_MOVE:
                return "hill move";
            case MULTIPLAYER_SOUND_PLAYER_RESPAWN:
                return "player respawn";
            case MULTIPLAYER_SOUND_KING_OF_THE_HILL:
                return "king of the hill";
            case MULTIPLAYER_SOUND_ODD_BALL:
                return "odd ball";
            case MULTIPLAYER_SOUND_TEAM_RACE:
                return "team race";
            case MULTIPLAYER_SOUND_TEAM_SLAYER:
                return "team slayer";
            case MULTIPLAYER_SOUND_TEAM_KING_OF_THE_HILL:
                return "team king of the hill";
            case MULTIPLAYER_SOUND_BLUE_TEAM_CAPTURE_THE_FLAG:
                return "blue team capture the flag";
            case MULTIPLAYER_SOUND_RED_TEAM_CAPTURE_THE_FLAG:
                return "red team capture the flag";
            case MULTIPLAYER_SOUND_CONTEST:
                return "contest";
            case MULTIPLAYER_SOUND_CONTROL:
                return "control";
            case MULTIPLAYER_SOUND_HILL_OCCUPIED:
                return "hill occupied";
            case MULTIPLAYER_SOUND_COUNTDOWN_TIMER_END:
                return "countdown timer end";
            case MULTIPLAYER_SOUND_TING:
                return "ting";
            case MULTIPLAYER_SOUND_CUSTOM_1:
                return "custom 1";
            case MULTIPLAYER_SOUND_CUSTOM_2:
                return "custom 2";
            case MULTIPLAYER_SOUND_CUSTOM_3:
                return "custom 3";
            case MULTIPLAYER_SOUND_CUSTOM_4:
                return "custom 4";
            case MULTIPLAYER_SOUND_CUSTOM_5:
                return "custom 5";
            case MULTIPLAYER_SOUND_CUSTOM_6:
                return "custom 6";
            case MULTIPLAYER_SOUND_CUSTOM_7:
                return "custom 7";
            case MULTIPLAYER_SOUND_CUSTOM_8:
                return "custom 8";
            case MULTIPLAYER_SOUND_CUSTOM_9:
                return "custom 9";
            case MULTIPLAYER_SOUND_CUSTOM_10:
                return "custom 10";
            case MULTIPLAYER_SOUND_CUSTOM_11:
                return "custom 11";
            case MULTIPLAYER_SOUND_CUSTOM_12:
                return "custom 12";
            case MULTIPLAYER_SOUND_CUSTOM_13:
                return "custom 13";
            case MULTIPLAYER_SOUND_CUSTOM_14:
                return "custom 14";
            case MULTIPLAYER_SOUND_CUSTOM_15:
                return "custom 15";
            case MULTIPLAYER_SOUND_CUSTOM_16:
                return "custom 16";
            default:
                return "invalid sound";
        }
    }
}