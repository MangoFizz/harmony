// SPDX-License-Identifier: GPL-3.0-only

#include <cstring>
#include <filesystem>
#include <fstream>
#include "../version.hpp"
#include "../command/command.hpp"
#include "../messaging/console_output.hpp"
#include "../harmony.hpp"
#include "config.hpp"

namespace Harmony {    
    const std::vector<std::string> *Config::get_settings_for_command(const char *command) const {
        for(auto &c : this->p_settings) {
            if(std::strcmp(c.first.data(), command) == 0) {
                return &c.second;
            }
        }
        return nullptr;
    }

    void Config::set_settings_for_command(const char *command, const std::vector<std::string> &settings) {
        for(auto &c : this->p_settings) {
            if(std::strcmp(c.first.data(), command) == 0) {
                if(c.second == settings) {
                    return;
                }
                this->p_settings.erase(this->p_settings.begin() + (&c - this->p_settings.data()));
                break;
            }
        }
        this->p_settings.emplace_back(command, settings);

        if(this->p_saving) {
            this->save();
        }
    }

    void Config::save() {
        // Open
        std::ofstream config(this->p_path, std::ios_base::out | std::ios_base::trunc);

        // Set settings
        for(auto &c : this->p_settings) {
            config << unsplit_arguments(split_arguments(c.first.data())) << " " << unsplit_arguments(c.second) << "\n";
        }

        // Flush
        config.flush();
        config.close();
    }

    void Config::load() {
        auto &harmony = Harmony::get();
        std::ifstream config(this->p_path, std::ios_base::in);
        std::string line;
        std::size_t line_count = 0;
        while(std::getline(config, line)) {
            line_count++;

            bool result = harmony.execute_command(line, true);

            if(!result) {
                console_error("harmony: Error loading configs from file %s", this->p_path.c_str());
            }
        }
        this->p_saving = true;
    }

    Config::Config(const char *path) : p_path(path) {}
    Config::Config(const std::filesystem::path path) : p_path(path.string()) {}
}
