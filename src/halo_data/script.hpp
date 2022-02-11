// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_HALO_DATA_SCRIPT_HPP
#define HARMONY_HALO_DATA_SCRIPT_HPP

#include <cstdint>
#include "../memory/struct.hpp"

namespace Harmony::HaloData {
    struct ScriptFunction {
        enum DataType : std::uint16_t {
            DATA_TYPE_PASSTHROUGH = 3,
            DATA_TYPE_VOID,
            DATA_TYPE_BOOLEAN,
            DATA_TYPE_REAL,
            DATA_TYPE_SHORT,
            DATA_TYPE_LONG,
            DATA_TYPE_STRING,
            DATA_TYPE_TRIGGER_VOLUME = 11,
            DATA_TYPE_CUTSCENE_FLAG,
            DATA_TYPE_CUTSCENE_CAMERA_POINT,
            DATA_TYPE_CUTSCENE_TITLE,
            DATA_TYPE_CUTSCENE_RECORDING,
            DATA_TYPE_DEVICE_GROUP,
            DATA_TYPE_AI,
            DATA_TYPE_AI_COMMAND_LIST,
            DATA_TYPE_STARTING_PROFILE,
            DATA_TYPE_CONVERSATION,
            DATA_TYPE_NAVPOINT,
            DATA_TYPE_HUD_MESSAGE,
            DATA_TYPE_OBJECT_LIST,
            DATA_TYPE_SOUND,
            DATA_TYPE_EFFECT,
            DATA_TYPE_DAMAGE,
            DATA_TYPE_LOOPING_SOUND,
            DATA_TYPE_ANIMATION_GRAPH,
            DATA_TYPE_ACTOR_VARIANT,
            DATA_TYPE_OBJECT_DEFINITION = 31,
            DATA_TYPE_GAME_DIFFICULTY,
            DATA_TYPE_TEAM,
            DATA_TYPE_AI_DEFAULT_STATE,
            DATA_TYPE_ACTOR_TYPE,
            DATA_TYPE_HUD_CORNER,
            DATA_TYPE_OBJECT,
            DATA_TYPE_UNIT,
            DATA_TYPE_VEHICLE,
            DATA_TYPE_DEVICE,
            DATA_TYPE_SCENERY,
            DATA_TYPE_OBJECT_NAME
        };

        /** Return type of function */
        std::uint32_t return_type;

        /** Name of the function */
        const char *name;

        /** Console command function */
        void *console_function;

        /** Script function */
        void *script_function;

        /** Help message */
        const char *help_message;

        /** Help parameters */
        const char *help_parameters;

        PADDING(0x2);

        /** Number of parameters */
        std::uint16_t parameter_count;

        const DataType *get_parameters() noexcept {
            return this->parameter_count ? reinterpret_cast<DataType *>(this + 1) : nullptr;
        }
    };
    static_assert(sizeof(ScriptFunction) == 0x1C);
}

#endif
