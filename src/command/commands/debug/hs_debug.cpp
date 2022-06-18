// SPDX-License-Identifier: GPL-3.0-only

#include <sstream>
#include "../../../events/hs_function.hpp"
#include "../../../halo_data/script.hpp"
#include "../../../messaging/console_output.hpp"
#include "../../command.hpp"

namespace Harmony {
    static bool hs_debug(const char *script, HaloData::ScriptFunction *function, const std::uint32_t *params) noexcept {
        if(!script) {
            script = "null";
        }

        std::stringstream paramters;
        for(std::size_t i = 0; i < function->parameter_count; i++) {
            switch(function->get_parameters()[i]) {
                case HaloData::ScriptFunction::DATA_TYPE_BOOLEAN: {
                    paramters << *reinterpret_cast<const std::uint8_t *>(params + i);
                    break;
                }

                case HaloData::ScriptFunction::DATA_TYPE_REAL: {
                    paramters << *reinterpret_cast<const float *>(params + i);
                    break;
                }

                case HaloData::ScriptFunction::DATA_TYPE_SHORT: {
                    paramters << *reinterpret_cast<const std::uint16_t *>(params + i);
                    break;
                }

                case HaloData::ScriptFunction::DATA_TYPE_LONG: {
                    paramters << params[i];
                    break;
                }

                case HaloData::ScriptFunction::DATA_TYPE_STRING: {
                    paramters << reinterpret_cast<const char *>(params[i]);
                    break;
                }

                default: {
                    paramters << params[i];
                    break;
                }
            }
            paramters << " ";
        }

        console_output("[%s] %s %s", script, function->name, paramters.str().c_str());

        return true;
    }

    bool hs_debug_command(int argc, const char **argv) {
        static bool setting = false;
        if(argc) {
            bool new_setting = STR_TO_BOOL(argv[0]);
            if(new_setting != setting) {
                setting = new_setting;

                if(setting) {
                    add_hs_function_event(hs_debug);
                }
                else {
                    remove_hs_function_event(hs_debug);
                }
            }
        }
        console_output(BOOL_TO_STR(setting));
        return true;
    }
}
