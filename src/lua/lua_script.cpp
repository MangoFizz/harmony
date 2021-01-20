// SPDX-License-Identifier: GPL-3.0-only

#include <filesystem>
#include "../halo_data/path.hpp"
#include "lua_script.hpp"

namespace Harmony::Lua {
    const char *Script::get_name() const noexcept {
        return this->name.c_str();
    }

    const char *Script::get_type() const noexcept {
        return this->type.c_str();
    }

    const char *Script::get_data_path() const noexcept {
        return this->data_path.c_str();
    }

    std::vector<std::string> &Script::get_callbacks(const char *callback) noexcept {
        if(this->callbacks.find(callback) != this->callbacks.end()) {
            return this->callbacks[callback];
        }
        else if(this->callbacks.find("invalid") == this->callbacks.end()) {
            this->callbacks["invalid"] = std::vector<std::string>();
        }
        return this->callbacks["invalid"];
    }

    OpticStore &Script::get_optic_store() noexcept {
        return this->optic_store;
    }

    lua_State *Script::get_state() noexcept {
        return this->script;
    }

    void Script::register_callback_function(const char *callback, const char *function) noexcept {
        this->callbacks[callback].emplace_back(function);
    }

    std::string Script::get_global(lua_State *state, const char *global) noexcept {
        lua_getglobal(state, global);
        std::string value = lua_tostring(state, -1);
        lua_pop(state, 1);
        return value;
    }

    std::string Script::get_script_data_path() noexcept {
        auto state = this->script;
        static auto chimera_folder = HaloData::get_path() / "chimera";
        static auto scripts_data_directory = chimera_folder / "lua" / "data";

        // Remove script file extension
        auto script_name = this->name.substr(0, this->name.size() - 4);

        // Create script data folder
        auto data_path = scripts_data_directory / this->type / script_name;

        return data_path.string();
    }

    Script::Script(lua_State *state) noexcept {
        this->script = state;
        this->name = get_global(state, "script_name");
        this->type = get_global(state, "script_type");
        this->data_path = this->get_script_data_path();
    }
}