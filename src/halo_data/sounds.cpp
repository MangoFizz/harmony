// SPDX-License-Identifier: GPL-3.0-only

#include "sounds.hpp"

namespace Harmony::HaloData {
    std::string string_from_multiplayer_sound(MultiplayerSound sound) noexcept {
        switch(sound) {
            case HaloData::MultiplayerSound::PLAYBALL:
                return "playball";
            case HaloData::MultiplayerSound::GAME_OVER:
                return "game over";
            case HaloData::MultiplayerSound::ONE_MINUTE_TO_WIN:
                return "one minute to win";
            case HaloData::MultiplayerSound::THIRTY_SECONDS_TO_WIN:
                return "thirty seconds to win";
            case HaloData::MultiplayerSound::RED_TEAM_ONE_MINUTE_TO_WIN:
                return "red team one minute to win";
            case HaloData::MultiplayerSound::RED_TEAM_THIRTY_SECONDS_TO_WIN:
                return "red team thirty seconds to win";
            case HaloData::MultiplayerSound::BLUE_TEAM_ONE_MINUTE_TO_WIN:
                return "blue team one minute to win";
            case HaloData::MultiplayerSound::BLUE_TEAM_THIRTY_SECONDS_TO_WIN:
                return "red team thirty seconds to win";
            case HaloData::MultiplayerSound::RED_TEAM_FLAG_TAKEN:
                return "red team flag taken";
            case HaloData::MultiplayerSound::RED_TEAM_FLAG_RETURNED:
                return "red team flag returned";
            case HaloData::MultiplayerSound::RED_TEAM_FLAG_CAPTURED:
                return "red team flag captured";
            case HaloData::MultiplayerSound::BLUE_TEAM_FLAG_TAKEN:
                return "blue team flag taken";
            case HaloData::MultiplayerSound::BLUE_TEAM_FLAG_RETURNED:
                return "blue team flag returned";
            case HaloData::MultiplayerSound::BLUE_TEAM_FLAG_CAPTURED:
                return "blue team flag captured";
            case HaloData::MultiplayerSound::DOUBLE_KILL:
                return "double kill";
            case HaloData::MultiplayerSound::TRIPLE_KILL:
                return "triple kill";
            case HaloData::MultiplayerSound::KILLTACULAR:
                return "killtacular";
            case HaloData::MultiplayerSound::RUNNING_RIOT:
                return "running riot";
            case HaloData::MultiplayerSound::KILLING_SPREE:
                return "killing spree";
            case HaloData::MultiplayerSound::ODDBALL:
                return "oddball";
            case HaloData::MultiplayerSound::RACE:
                return "race";
            case HaloData::MultiplayerSound::SLAYER:
                return "slayer";
            case HaloData::MultiplayerSound::CAPTURE_THE_FLAG:
                return "capture the flag";
            case HaloData::MultiplayerSound::WARTHOG:
                return "warthog";
            case HaloData::MultiplayerSound::GHOST:
                return "ghost";
            case HaloData::MultiplayerSound::SCORPION:
                return "scorpion";
            case HaloData::MultiplayerSound::COUNTDOWN_TIMER:
                return "countdown timer";
            case HaloData::MultiplayerSound::TELEPORTER_ACTIVATE:
                return "teleporter activate";
            case HaloData::MultiplayerSound::FLAG_FAILURE:
                return "flag failure";
            case HaloData::MultiplayerSound::COUNTDOWN_FOR_RESPAWN:
                return "countdown for respawn";
            case HaloData::MultiplayerSound::HILL_MOVE:
                return "hill move";
            case HaloData::MultiplayerSound::PLAYER_RESPAWN:
                return "player respawn";
            case HaloData::MultiplayerSound::KING_OF_THE_HILL:
                return "king of the hill";
            case HaloData::MultiplayerSound::ODD_BALL:
                return "odd ball";
            case HaloData::MultiplayerSound::TEAM_RACE:
                return "team race";
            case HaloData::MultiplayerSound::TEAM_SLAYER:
                return "team slayer";
            case HaloData::MultiplayerSound::TEAM_KING_OF_THE_HILL:
                return "team king of the hill";
            case HaloData::MultiplayerSound::BLUE_TEAM_CAPTURE_THE_FLAG:
                return "blue team capture the flag";
            case HaloData::MultiplayerSound::RED_TEAM_CAPTURE_THE_FLAG:
                return "red team capture the flag";
            case HaloData::MultiplayerSound::CONTEST:
                return "contest";
            case HaloData::MultiplayerSound::CONTROL:
                return "control";
            case HaloData::MultiplayerSound::HILL_OCCUPIED:
                return "hill occupied";
            case HaloData::MultiplayerSound::COUNTDOWN_TIMER_END:
                return "countdown timer end";
            case HaloData::MultiplayerSound::TING:
                return "ting";
            case HaloData::MultiplayerSound::SOUND:
                return "sound";
            default:
                return "custom";
        }
    }
}