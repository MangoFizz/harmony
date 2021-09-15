// SPDX-License-Identifier: GPL-3.0-only

#include <windows.h>
#include <cstring>
#include <lua.hpp>
#include "events/d3d9_end_scene.hpp"
#include "events/d3d9_reset.hpp"
#include "events/menu_accept.hpp"
#include "events/menu_back.hpp"
#include "events/menu_list_tab.hpp"
#include "events/menu_mouse_button_press.hpp"
#include "events/menu_sound.hpp"
#include "lua/library.hpp"
#include "events/console_command.hpp"
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
   static Harmony *instance = nullptr;
   static void first_tick() noexcept;
   static bool info_command(std::string command) noexcept;

   Signature &Harmony::get_signature(const char *name) noexcept {
      for(auto &signature : this->signatures) {
         if(std::strcmp(signature.get_name(), name) == 0) {
            return signature;
         }
      }

      // What the heck are you looking for?
      char message[256];
      std::sprintf(message, "Invalid %s signature. This may be a bug.", name);
      MessageBoxA(NULL, message, "Harmony: missing signature", MB_OK);
      std::terminate();
   }

   Lua::Library &Harmony::get_lua_library_handler() noexcept{
      return *(this->lua_handler.get());
   }

   Optic::Handler &Harmony::get_optic_handler() noexcept {
      return *(this->optic_handler.get());
   }

   UserInterface::WidescreenOverride &Harmony::get_widescreen_override_handle() noexcept {
      return *(this->widescreen_fix_override.get());
   }

   Harmony::Harmony() : signatures(Signature::find_signatures()) {
      // Set instance pointer
      instance = this;

      // Set up library handler
      this->lua_handler = std::make_unique<Lua::Library>();

      // Set up optic
      this->optic_handler = std::make_unique<Optic::Handler>();

      // Set up widescreen override
      this->widescreen_fix_override = std::make_unique<UserInterface::WidescreenOverride>();

      // Set up tick event hook
      set_up_tick_event();

      // Set up map load hook
      set_up_map_load_event();

      // Add first tick event
      add_tick_event(first_tick);
   }

   Harmony &get_harmony() {
      return *instance;
   }

   extern "C" std::byte *get_address_for_signature(const char *name) noexcept {
      return instance->get_signature(name).get_data();
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

      // Set up menu events
      set_up_menu_accept_event();
      set_up_menu_back_event();
      set_up_menu_mouse_button_press_event();
      set_up_menu_list_tab_event();
      set_up_menu_sound_event();

      // Set up console command event
      set_up_console_command_event();

      // Add info command
      add_console_command_event(info_command);

      // Override Chimera's widescreen fix
      instance->get_widescreen_override_handle().enable(true);
   }

   static bool info_command(std::string command) noexcept {
      if(command == "harmony") {
         ConsoleColor blue = {1, 0.1, 0.8, 0.9};
         console_output(blue, "Harmony version %s", HARMONY_VERSION);
         console_output(blue, "Optic API v%s", OPTIC_API_VERSION);
         return false;
      }
      return true;
   }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
   switch(fdwReason) {
      case DLL_PROCESS_ATTACH: {
         new Harmony::Harmony();
         break;
      }
      case DLL_PROCESS_DETACH: {
         break;
      }
   }
   return TRUE;
}