// SPDX-License-Identifier: GPL-3.0-only

#include <filesystem>
#include "../halo_data/path.hpp"
#include "../messaging/console_output.hpp"
#include "../optic/handler.hpp"
#include "../harmony.hpp"
#include "script.hpp"

namespace Harmony::Lua {
    std::string Script::get_name() const noexcept {
        return this->name;
    }

    std::string Script::get_type() const noexcept {
        return this->type;
    }

    std::string Script::get_data_path() const noexcept {
        return this->data_path;
    }

    bool Script::path_is_valid(std::string path) noexcept {
        std::string data_dir = this->data_path;
        auto absolute_path = std::filesystem::absolute(std::filesystem::path(data_dir) / path);
        if(absolute_path.string().find(data_dir) == 0) {
            return true;
        }
        return false;
    }

    std::vector<std::string> &Script::get_callbacks(CallbackType callback) noexcept {
        if(this->callbacks.find(callback) == this->callbacks.end()) {
            this->callbacks.insert_or_assign(callback, std::vector<std::string>());
        }
        return this->callbacks[callback];
    }

    void Script::add_callback(CallbackType callback, std::string function) noexcept {
        this->callbacks[callback].emplace_back(function);
    }

    std::size_t Script::get_require_count() const noexcept {
        return this->require_count;
    }

    Optic::Container *Script::get_optic_container() noexcept {
        return this->optic_container;
    }

    ScriptMathApiStore &Script::get_math_api_store() noexcept {
        return this->math_api_store;
    }

    ScriptTimeApiStore &Script::get_time_api_store() noexcept {
        return this->time_api_store;
    }

    lua_State *Script::get_state() noexcept {
        return this->script;
    }

    void Script::print_last_error() noexcept {
        const char *err = lua_tostring(script, -1);
        console_error("%s", err);
        lua_pop(script, 1);
    }

    std::string Script::get_global_from_state(lua_State *state, const char *global) noexcept {
        lua_getglobal(state, global);
        std::string value = lua_tostring(state, -1);
        lua_pop(state, 1);
        return value;
    }

    std::string Script::get_script_name_from_state(lua_State *state) noexcept {
        return get_global_from_state(state, "script_name");
    }

    std::string Script::get_script_data_path() noexcept {
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
        this->name = get_global_from_state(state, "script_name");
        this->type = get_global_from_state(state, "script_type");
        this->data_path = this->get_script_data_path();
        this->require_count = 1;

        // Create a new optic container
        auto &optic_handler = Harmony::get().get_optic_handler();
        this->optic_container = optic_handler.create_optic(this->type + this->name);
    }

    Script::~Script() noexcept {
        // Remove optic cointainer
        auto &optic_handler = Harmony::get().get_optic_handler();
        optic_handler.remove_optic(this->type + this->name);
    }
}