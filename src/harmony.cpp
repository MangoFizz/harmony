// SPDX-License-Identifier: GPL-3.0-only

#include <windows.h>
#include "events/console_command.hpp"
#include "events/d3d9_end_scene.hpp"
#include "events/d3d9_reset.hpp"
#include "events/hs_function.hpp"
#include "events/keypress.hpp"
#include "events/widget_accept.hpp"
#include "events/widget_close.hpp"
#include "events/widget_list_tab.hpp"
#include "events/widget_mouse_button_press.hpp"
#include "events/widget_sound.hpp"
#include "lua/library.hpp"
#include "events/map_load.hpp"
#include "events/multiplayer_event.hpp"
#include "events/multiplayer_sound.hpp"
#include "events/tick.hpp"
#include "memory/signature.hpp"
#include "messaging/console_output.hpp"
#include "messaging/message_box.hpp"
#include "optic/handler.hpp"
#include "menu/widescreen_override.hpp"
#include "version.hpp"
#include "harmony.hpp"

namespace Harmony {
   static void first_tick() noexcept;
   static bool info_command(std::string command) noexcept;
   static void terminate() noexcept;

   Harmony *Harmony::instance = nullptr;

   Signature &Harmony::get_signature(const char *name) noexcept {
      for(auto &signature : this->signatures) {
         if(signature.get_name() == name) {
            return signature;
         }
      }

      // oops
      message_box("Signature %s does not exists. This may be a bug.", name);
      std::terminate();
   }

   bool Harmony::signature_exists(const char *name) noexcept {
      for(auto &signature : this->signatures) {
         if(signature.get_name() == name) {
            return true;
         }
      }
      return false;
   }

   Lua::Library &Harmony::get_lua_library_handler() noexcept{
      return *this->lua_handler;
   }

   Optic::Handler &Harmony::get_optic_handler() noexcept {
      return *this->optic_handler;
   }

   Menu::WidescreenOverride &Harmony::get_widescreen_override_handle() noexcept {
      return *this->widescreen_fix_override;
   }

   Harmony::Harmony() : signatures(Signature::find_signatures()) {
      // Set instance pointer
      instance = this;

      // Set up library handler
      this->lua_handler = std::make_unique<Lua::Library>();

      // Set up optic
      this->optic_handler = std::make_unique<Optic::Handler>();

      // Set up widescreen override
      this->widescreen_fix_override = std::make_unique<Menu::WidescreenOverride>();

      // Set error handling
      std::set_terminate(terminate);

      // Set up tick event hook
      set_up_tick_event();

      // Set up map load hook
      set_up_map_load_event();

      // Add first tick event
      add_tick_event(first_tick);
   }

   Harmony &Harmony::get() {
      return *Harmony::instance;
   }

   extern "C" std::byte *get_address_for_signature(const char *name) noexcept {
      return Harmony::get().get_signature(name).get_data();
   }

   static void first_tick() noexcept {
      // remove this event, we only need to run it once
      remove_tick_event(first_tick);

      // Enable console output
      enable_output(true);

      // Set up d3d9 events
      set_up_d3d9_end_scene_event();
      set_up_d3d9_reset_event();

      // Set up multiplayer events
      set_up_multiplayer_event();
      set_up_multiplayer_sounds_event();

      // Widget events
      set_up_widget_accept_event();
      set_up_widget_close_event();
      set_up_widget_mouse_button_press_event();
      set_up_widget_list_tab_event();
      set_up_widget_sound_event();

      // Set up script event
      set_up_hs_function_event();

      // Set up input event
      set_up_keypress_event();

      // Set up console commands
      set_up_console_command_event();

      // Add info command
      add_console_command_event(info_command);

      // Override Chimera's widescreen fix
      Harmony::get().get_widescreen_override_handle().enable(true);
   }

   static bool info_command(std::string command) noexcept {
      if(command == "harmony") {
         ConsoleColor blue = {1, 0.1, 0.8, 0.9};
         console_output(blue, "Harmony version %s", HARMONY_VERSION);
         return false;
      }
      return true;
   }

   static void terminate() noexcept {
      message_box("Uncaught exception. This may be a bug.");
      std::abort();
   }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
   switch(fdwReason) {
      case DLL_PROCESS_ATTACH:
         new Harmony::Harmony();
         break;

      default:
         break;
   }
   return TRUE;
}