// SPDX-License-Identifier: GPL-3.0-only

#include <memory>
#include <cstring>
#include "../messaging/console_output.hpp"
#include "../version.hpp"
#include "commands/client.hpp"
#include "command.hpp"

namespace Harmony {
    static bool harmony_info_command(int, const char **) {
        clear_output_prefix();
        HaloData::ColorARGB blue = {1, 0.1, 0.8, 0.9};
        console_output(blue, "Harmony version %s", HARMONY_VERSION);
        return true;
    }

    CommandResult Command::call(std::size_t arg_count, const char **args) const noexcept {
        if(arg_count > this->max_args()) {
            return CommandResult::COMMAND_RESULT_FAILED_TOO_MANY_ARGUMENTS;
        }
        else if(arg_count < this->min_args()) {
            return CommandResult::COMMAND_RESULT_FAILED_NOT_ENOUGH_ARGUMENTS;
        }
        else {
            return this->p_function(arg_count, args) ? CommandResult::COMMAND_RESULT_SUCCESS : CommandResult::COMMAND_RESULT_FAILED_ERROR;
        }
    }

    CommandResult Command::call(const std::vector<std::string> &arguments) const noexcept {
        // Get argument count
        std::size_t arg_count = arguments.size();

        // If no arguments were passed, just call it.
        if(arg_count == 0) {
            return this->call(0, nullptr);
        }

        // Make our array
        auto arguments_alloc(std::make_unique<const char *[]>(arg_count));
        for(std::size_t i = 0; i < arg_count; i++) {
            arguments_alloc[i] = arguments[i].data();
        }

        // Do it!
        return this->call(arg_count, arguments_alloc.get());
    }

    Command::Command(const char *name, const char *category, const char *help, CommandFunction function, bool autosave, std::size_t min_args, std::size_t max_args) :
        p_name(name), p_category(category), p_help(help), p_function(function), p_autosave(autosave), p_min_args(min_args), p_max_args(max_args) {}

    Command::Command(const char *name, const char *category, const char *help, CommandFunction function, bool autosave, std::size_t args) : Command(name, category, help, function, autosave, args, args) {}

    std::vector<Command> Command::get_commands() noexcept {
        auto commands = get_client_commands();
        
        // Add info command
        commands.emplace_back("harmony", "core", "Shows harmony info.", harmony_info_command, false, 0);

        return std::move(commands);
    }

    std::vector<std::string> split_arguments(std::string command) noexcept {
        // This is the vector to return.
        std::vector<std::string> arguments;

        // This value will be true if we are inside quotes, during which the word will not separate into arguments.
        bool in_quotes = false;

        // If using a backslash, add the next character to the string regardless of what it is.
        bool escape_character = false;

        // Regardless of if there were any characters, there was an argument.
        bool allow_empty_argument = false;

        // Get the command
        std::size_t command_size = command.size();

        // Get the argument
        std::string argument;
        for(std::size_t i = 0; i < command_size; i++) {
            if(escape_character) {
                escape_character = false;
            }
            // Escape character - this will be used to include the next character regardless of what it is
            else if(command[i] == '\\') {
                escape_character = true;
                continue;
            }
            // If a whitespace or octotothorpe is in quotations in the argument, then it is considered part of the argument.
            else if(command[i] == '"') {
                in_quotes = !in_quotes;
                allow_empty_argument = true;
                continue;
            }
            else if((command[i] == ' ' || command[i] == '\r' || command[i] == '\n' || command[i] == '#') && !in_quotes) {
                // Add argument if not empty.
                if(argument != "" || allow_empty_argument) {
                    arguments.push_back(argument);
                    argument = "";
                    allow_empty_argument = false;
                }

                // Terminate if beginning a comment.
                if(command[i] == '#') {
                    break;
                }
                continue;
            }
            argument += command[i];
        }

        // Add the last argument.
        if(argument != "" || allow_empty_argument) {
            arguments.push_back(argument);
        }

        return std::move(arguments);
    }

    std::string unsplit_arguments(const std::vector<std::string> &arguments) noexcept {
        // This is the string to return.
        std::string unsplit;

        for(std::size_t i = 0; i < arguments.size(); i++) {
            // This is a reference to the argument we're dealing with.
            const std::string &argument = arguments[i];

            // This will be the final string we append to the unsplit string.
            std::string argument_final;

            // Set this to true if we need to surround this argument with quotes.
            bool surround_with_quotes = false;

            // Go through each character and add them one-by-one to argument_final.
            for(const char &c : argument) {
                switch(c) {
                    // Backslashes and quotation marks should be escaped.
                    case '\\':
                    case '"':
                        argument_final += '\\';
                        break;

                    // If we're using spaces or octothorpes, the argument should be surrounded with quotation marks. We could escape those, but this is more readable.
                    case '#':
                    case ' ':
                        surround_with_quotes = true;
                        break;

                    default:
                        break;
                }
                argument_final += c;
            }

            if(surround_with_quotes) {
                argument_final = std::string("\"") + argument_final + "\"";
            }

            unsplit += argument_final;

            // Add the space to separate the next argument.
            if(i + 1 < arguments.size()) {
                unsplit += " ";
            }
        }

        return unsplit;
    }
}
