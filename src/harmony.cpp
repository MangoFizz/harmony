// SPDX-License-Identifier: GPL-3.0-only

#include <windows.h>
#include <cstring>
#include <lua.hpp>
#include "events/d3d9_end_scene.hpp"
#include "events/d3d9_reset.hpp"
#include "lua/library.hpp"
#include "events/map_load.hpp"
#include "events/multiplayer_sound.hpp"
#include "events/tick.hpp"
#include "memory/signature.hpp"
#include "messaging/console_output.hpp"
#include "messaging/message_box.hpp"
#include "optic/handler.hpp"
#include "harmony.hpp"

namespace Harmony {
   static Harmony *instance = nullptr;
   static void first_tick() noexcept;

   Signature &Harmony::get_signature(const char *name) noexcept {
      for(auto &signature : this->signatures) {
         if(std::strcmp(signature.get_name(), name) == 0) {
            return signature;
         }
      }

      // What the heck are you looking for?
      char message[256];
      std::sprintf(message, "Could not find %s signature.", name);
      MessageBoxA(NULL, message, "Harmony: missing signature", MB_OK);
      std::terminate();
   }

   Lua::Library &Harmony::get_lua_library_handler() noexcept{
      return *(this->lua_handler.get());
   }

   Optic::Handler &Harmony::get_optic_handler() noexcept {
      return *(this->optic_handler.get());
   }

   Harmony::Harmony() : signatures(Signature::find_signatures()) {
      // Set instance pointer
      instance = this;

      // Set up library handler
      this->lua_handler = std::make_unique<Lua::Library>();

      // Set up optic
      this->optic_handler = std::make_unique<Optic::Handler>();

      // Set up tick event hook
      enable_tick_event();

      // Set up map load hook
      enable_map_load_hook();

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
      enable_d3d9_end_scene_hook();
      enable_d3d9_reset_hook();

      // Set up multiplayer sounds event
      enable_multiplayer_sounds_hook();
   }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
   switch(fdwReason) {
      case DLL_PROCESS_ATTACH: {
         auto *harmony = new Harmony::Harmony();
         break;
      }
      case DLL_PROCESS_DETACH: {
         break;
      }
   }
   return TRUE;
}