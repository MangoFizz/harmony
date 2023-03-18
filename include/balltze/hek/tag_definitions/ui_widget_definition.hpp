// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__UI_WIDGET_DEFINITION_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__UI_WIDGET_DEFINITION_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
	enum class UIGameDataInputReferenceFunction : std::uint16_t {
		NULL_VALUE = 0,
		PLAYER_SETTINGS_MENU_UPDATE_DESC,
		UNUSED,
		PLAYLIST_SETTINGS_MENU_UPDATE_DESC,
		GAMETYPE_SELECT_MENU_UPDATE_DESC,
		MULTIPLAYER_TYPE_MENU_UPDATE_DESC,
		SOLO_LEVEL_SELECT_UPDATE,
		DIFFICULTY_MENU_UPDATE_DESC,
		BUILD_NUMBER_TEXTBOX_ONLY,
		SERVER_LIST_UPDATE,
		NETWORK_PREGAME_STATUS_UPDATE,
		SPLITSCREEN_PREGAME_STATUS_UPDATE,
		NET_SPLITSCREEN_PREJOIN_PLAYERS,
		MP_PROFILE_LIST_UPDATE,
		_3WIDE_PLAYER_PROFILE_LIST_UPDATE,
		PLYR_PROF_EDIT_SELECT_MENU_UPD8,
		PLAYER_PROFILE_SMALL_MENU_UPDATE,
		GAME_SETTINGS_LISTS_TEXT_UPDATE,
		SOLO_GAME_OBJECTIVE_TEXT,
		COLOR_PICKER_UPDATE,
		GAME_SETTINGS_LISTS_PIC_UPDATE,
		MAIN_MENU_FAKE_ANIMATE,
		MP_LEVEL_SELECT_UPDATE,
		GET_ACTIVE_PLYR_PROFILE_NAME,
		GET_EDIT_PLYR_PROFILE_NAME,
		GET_EDIT_GAME_SETTINGS_NAME,
		GET_ACTIVE_PLYR_PROFILE_COLOR,
		MP_SET_TEXTBOX_MAP_NAME,
		MP_SET_TEXTBOX_GAME_RULESET,
		MP_SET_TEXTBOX_TEAMS_NOTEAMS,
		MP_SET_TEXTBOX_SCORE_LIMIT,
		MP_SET_TEXTBOX_SCORE_LIMIT_TYPE,
		MP_SET_BITMAP_FOR_MAP,
		MP_SET_BITMAP_FOR_RULESET,
		MP_SET_TEXTBOX,
		MP_EDIT_PROFILE_SET_RULE_TEXT,
		SYSTEM_LINK_STATUS_CHECK,
		MP_GAME_DIRECTIONS,
		TEAMS_NO_TEAMS_BITMAP_UPDATE,
		WARN_IF_DIFF_WILL_NUKE_SAVED_GAME,
		DIM_IF_NO_NET_CABLE,
		PAUSE_GAME_SET_TEXTBOX_INVERTED,
		DIM_UNLESS_TWO_CONTROLLERS,
		CONTROLS_UPDATE_MENU,
		VIDEO_MENU_UPDATE,
		GAMESPY_SCREEN_UPDATE,
		COMMON_BUTTON_BAR_UPDATE,
		GAMEPAD_UPDATE_MENU,
		SERVER_SETTINGS_UPDATE,
		AUDIO_MENU_UPDATE,
		MP_PROF_VEHICLES_UPDATE,
		SOLO_MAP_LIST_UPDATE,
		MP_MAP_LIST_UPDATE,
		GT_SELECT_LIST_UPDATE,
		GT_EDIT_LIST_UPDATE,
		LOAD_GAME_LIST_UPDATE,
		CHECKING_FOR_UPDATES,
		DIRECT_IP_CONNECT_UPDATE,
		NETWORK_SETTINGS_UPDATE,
	};

	enum class UIEventType : std::uint16_t {
		A_BUTTON = 0,
		B_BUTTON,
		X_BUTTON,
		Y_BUTTON,
		BLACK_BUTTON,
		WHITE_BUTTON,
		LEFT_TRIGGER,
		RIGHT_TRIGGER,
		DPAD_UP,
		DPAD_DOWN,
		DPAD_LEFT,
		DPAD_RIGHT,
		START_BUTTON,
		BACK_BUTTON,
		LEFT_THUMB,
		RIGHT_THUMB,
		LEFT_ANALOG_STICK_UP,
		LEFT_ANALOG_STICK_DOWN,
		LEFT_ANALOG_STICK_LEFT,
		LEFT_ANALOG_STICK_RIGHT,
		LEFT_ANALOG_STICK_UP_1,
		RIGHT_ANALOG_STICK_DOWN,
		RIGHT_ANALOG_STICK_LEFT,
		RIGHT_ANALOG_STICK_RIGHT,
		CREATED,
		DELETED,
		GET_FOCUS,
		LOSE_FOCUS,
		LEFT_MOUSE,
		MIDDLE_MOUSE,
		RIGHT_MOUSE,
		DOUBLE_CLICK_EVENT,
		CUSTOM_ACTIVATION,
		POST_RENDER,
	};

	enum class UIEventHandlerReferenceFunction : std::uint16_t {
		NULL_VALUE = 0,
		LIST_GOTO_NEXT_ITEM,
		LIST_GOTO_PREVIOUS_ITEM,
		UNUSED,
		UNUSED1,
		INITIALIZE_SP_LEVEL_LIST_SOLO,
		INITIALIZE_SP_LEVEL_LIST_COOP,
		DISPOSE_SP_LEVEL_LIST,
		SOLO_LEVEL_SET_MAP,
		SET_DIFFICULTY,
		START_NEW_GAME,
		PAUSE_GAME_RESTART_AT_CHECKPOINT,
		PAUSE_GAME_RESTART_LEVEL,
		PAUSE_GAME_RETURN_TO_MAIN_MENU,
		CLEAR_MULTIPLAYER_PLAYER_JOINS,
		JOIN_CONTROLLER_TO_MP_GAME,
		INITIALIZE_NET_GAME_SERVER_LIST,
		START_NETWORK_GAME_SERVER,
		DISPOSE_NET_GAME_SERVER_LIST,
		SHUTDOWN_NETWORK_GAME,
		NET_GAME_JOIN_FROM_SERVER_LIST,
		SPLIT_SCREEN_GAME_INITIALIZE,
		COOP_GAME_INITIALIZE,
		MAIN_MENU_INTIALIZE,
		MP_TYPE_MENU_INITIALIZE,
		PICK_PLAY_STAGE_FOR_QUICK_START,
		MP_LEVEL_LIST_INITIALIZE,
		MP_LEVEL_LIST_DISPOSE,
		MP_LEVEL_SELECT,
		MP_PROFILES_LIST_INITIALIZE,
		MP_PROFILES_LIST_DISPOSE,
		MP_PROFILE_SET_FOR_GAME,
		SWAP_PLAYER_TEAM,
		NET_GAME_JOIN_PLAYER,
		PLAYER_PROFILE_LIST_INITIALIZE,
		PLAYER_PROFILE_LIST_DISPOSE,
		_3WIDE_PLYR_PROF_SET_FOR_GAME,
		_1WIDE_PLYR_PROF_SET_FOR_GAME,
		MP_PROFILE_BEGIN_EDITING,
		MP_PROFILE_END_EDITING,
		MP_PROFILE_SET_GAME_ENGINE,
		MP_PROFILE_CHANGE_NAME,
		MP_PROFILE_SET_CTF_RULES,
		MP_PROFILE_SET_KOTH_RULES,
		MP_PROFILE_SET_SLAYER_RULES,
		MP_PROFILE_SET_ODDBALL_RULES,
		MP_PROFILE_SET_RACING_RULES,
		MP_PROFILE_SET_PLAYER_OPTIONS,
		MP_PROFILE_SET_ITEM_OPTIONS,
		MP_PROFILE_SET_INDICATOR_OPTS,
		MP_PROFILE_INIT_GAME_ENGINE,
		MP_PROFILE_INIT_NAME,
		MP_PROFILE_INIT_CTF_RULES,
		MP_PROFILE_INIT_KOTH_RULES,
		MP_PROFILE_INIT_SLAYER_RULES,
		MP_PROFILE_INIT_ODDBALL_RULES,
		MP_PROFILE_INIT_RACING_RULES,
		MP_PROFILE_INIT_PLAYER_OPTS,
		MP_PROFILE_INIT_ITEM_OPTIONS,
		MP_PROFILE_INIT_INDICATOR_OPTS,
		MP_PROFILE_SAVE_CHANGES,
		COLOR_PICKER_MENU_INITIALIZE,
		COLOR_PICKER_MENU_DISPOSE,
		COLOR_PICKER_SELECT_COLOR,
		PLAYER_PROFILE_BEGIN_EDITING,
		PLAYER_PROFILE_END_EDITING,
		PLAYER_PROFILE_CHANGE_NAME,
		PLAYER_PROFILE_SAVE_CHANGES,
		PLYR_PRF_INIT_CNTL_SETTINGS,
		PLYR_PRF_INIT_ADV_CNTL_SET,
		PLYR_PRF_SAVE_CNTL_SETTINGS,
		PLYR_PRF_SAVE_ADV_CNTL_SET,
		MP_GAME_PLAYER_QUIT,
		MAIN_MENU_SWITCH_TO_SOLO_GAME,
		REQUEST_DEL_PLAYER_PROFILE,
		REQUEST_DEL_PLAYLIST_PROFILE,
		FINAL_DEL_PLAYER_PROFILE,
		FINAL_DEL_PLAYLIST_PROFILE,
		CANCEL_PROFILE_DELETE,
		CREATE_EDIT_PLAYLIST_PROFILE,
		CREATE_EDIT_PLAYER_PROFILE,
		NET_GAME_SPEED_START,
		NET_GAME_DELAY_START,
		NET_SERVER_ACCEPT_CONX,
		NET_SERVER_DEFER_START,
		NET_SERVER_ALLOW_START,
		DISABLE_IF_NO_XDEMOS,
		RUN_XDEMOS,
		SP_RESET_CONTROLLER_CHOICES,
		SP_SET_P1_CONTROLLER_CHOICE,
		SP_SET_P2_CONTROLLER_CHOICE,
		ERROR_IF_NO_NETWORK_CONNECTION,
		START_SERVER_IF_NONE_ADVERTISED,
		NET_GAME_UNJOIN_PLAYER,
		CLOSE_IF_NOT_EDITING_PROFILE,
		EXIT_TO_XBOX_DASHBOARD,
		NEW_CAMPAIGN_CHOSEN,
		NEW_CAMPAIGN_DECISION,
		POP_HISTORY_STACK_ONCE,
		DIFFICULTY_MENU_INIT,
		BEGIN_MUSIC_FADE_OUT,
		NEW_GAME_IF_NO_PLYR_PROFILES,
		EXIT_GRACEFULLY_TO_XBOX_DASHBOARD,
		PAUSE_GAME_INVERT_PITCH,
		START_NEW_COOP_GAME,
		PAUSE_GAME_INVERT_SPINNER_GET,
		PAUSE_GAME_INVERT_SPINNER_SET,
		MAIN_MENU_QUIT_GAME,
		MOUSE_EMIT_ACCEPT_EVENT,
		MOUSE_EMIT_BACK_EVENT,
		MOUSE_EMIT_DPAD_LEFT_EVENT,
		MOUSE_EMIT_DPAD_RIGHT_EVENT,
		MOUSE_SPINNER_3WIDE_CLICK,
		CONTROLS_SCREEN_INIT,
		VIDEO_SCREEN_INIT,
		CONTROLS_BEGIN_BINDING,
		GAMESPY_SCREEN_INIT,
		GAMESPY_SCREEN_DISPOSE,
		GAMESPY_SELECT_HEADER,
		GAMESPY_SELECT_ITEM,
		GAMESPY_SELECT_BUTTON,
		PLR_PROF_INIT_MOUSE_SET,
		PLR_PROF_CHANGE_MOUSE_SET,
		PLR_PROF_INIT_AUDIO_SET,
		PLR_PROF_CHANGE_AUDIO_SET,
		PLR_PROF_CHANGE_VIDEO_SET,
		CONTROLS_SCREEN_DISPOSE,
		CONTROLS_SCREEN_CHANGE_SET,
		MOUSE_EMIT_X_EVENT,
		GAMEPAD_SCREEN_INIT,
		GAMEPAD_SCREEN_DISPOSE,
		GAMEPAD_SCREEN_CHANGE_GAMEPADS,
		GAMEPAD_SCREEN_SELECT_ITEM,
		MOUSE_SCREEN_DEFAULTS,
		AUDIO_SCREEN_DEFAULTS,
		VIDEO_SCREEN_DEFAULTS,
		CONTROLS_SCREEN_DEFAULTS,
		PROFILE_SET_EDIT_BEGIN,
		PROFILE_MANAGER_DELETE,
		PROFILE_MANAGER_SELECT,
		GAMESPY_DISMISS_ERROR,
		SERVER_SETTINGS_INIT,
		SS_EDIT_SERVER_NAME,
		SS_EDIT_SERVER_PASSWORD,
		SS_START_GAME,
		VIDEO_TEST_DIALOG_INIT,
		VIDEO_TEST_DIALOG_DISPOSE,
		VIDEO_TEST_DIALOG_ACCEPT,
		GAMESPY_DISMISS_FILTERS,
		GAMESPY_UPDATE_FILTER_SETTINGS,
		GAMESPY_BACK_HANDLER,
		MOUSE_SPINNER_1WIDE_CLICK,
		CONTROLS_BACK_HANDLER,
		CONTROLS_ADVANCED_LAUNCH,
		CONTROLS_ADVANCED_OK,
		MP_PAUSE_MENU_OPEN,
		MP_GAME_OPTIONS_OPEN,
		MP_CHOOSE_TEAM,
		MP_PROF_INIT_VEHICLE_OPTIONS,
		MP_PROF_SAVE_VEHICLE_OPTIONS,
		SINGLE_PREV_CL_ITEM_ACTIVATED,
		MP_PROF_INIT_TEAMPLAY_OPTIONS,
		MP_PROF_SAVE_TEAMPLAY_OPTIONS,
		MP_GAME_OPTIONS_CHOOSE,
		EMIT_CUSTOM_ACTIVATION_EVENT,
		PLR_PROF_CANCEL_AUDIO_SET,
		PLR_PROF_INIT_NETWORK_OPTIONS,
		PLR_PROF_SAVE_NETWORK_OPTIONS,
		CREDITS_POST_RENDER,
		DIFFICULTY_ITEM_SELECT,
		CREDITS_INITIALIZE,
		CREDITS_DISPOSE,
		GAMESPY_GET_PATCH,
		VIDEO_SCREEN_DISPOSE,
		CAMPAIGN_MENU_INIT,
		CAMPAIGN_MENU_CONTINUE,
		LOAD_GAME_MENU_INIT,
		LOAD_GAME_MENU_DISPOSE,
		LOAD_GAME_MENU_ACTIVATED,
		SOLO_MENU_SAVE_CHECKPOINT,
		MP_TYPE_SET_MODE,
		CHECKING_FOR_UPDATES_OK,
		CHECKING_FOR_UPDATES_DISMISS,
		DIRECT_IP_CONNECT_INIT,
		DIRECT_IP_CONNECT_GO,
		DIRECT_IP_EDIT_FIELD,
		NETWORK_SETTINGS_EDIT_A_PORT,
		NETWORK_SETTINGS_DEFAULTS,
		LOAD_GAME_MENU_DELETE_REQUEST,
		LOAD_GAME_MENU_DELETE_FINISH,
	};

	enum class UIReplaceFunction : std::uint16_t {
		NULL_VALUE = 0,
		WIDGET_S_CONTROLLER,
		BUILD_NUMBER,
		PID,
	};

	enum class UIWidgetType : std::uint16_t {
		CONTAINER = 0,
		TEXT_BOX,
		SPINNER_LIST,
		COLUMN_LIST,
		GAME_MODEL_NOT_IMPLEMENTED,
		MOVIE_NOT_IMPLEMENTED,
		CUSTOM_NOT_IMPLEMENTED,
	};

	enum class UIControllerIndex : std::uint16_t {
		PLAYER_1 = 0,
		PLAYER_2,
		PLAYER_3,
		PLAYER_4,
		ANY_PLAYER,
	};

	enum class UIJustification : std::uint16_t {
		LEFT_JUSTIFY = 0,
		RIGHT_JUSTIFY,
		CENTER_JUSTIFY,
	};

	struct EventHandlerReferencesFlags {
		std::uint32_t close_current_widget : 1;
		std::uint32_t close_other_widget : 1;
		std::uint32_t close_all_widgets : 1;
		std::uint32_t open_widget : 1;
		std::uint32_t reload_self : 1;
		std::uint32_t reload_other_widget : 1;
		std::uint32_t give_focus_to_widget : 1;
		std::uint32_t run_function : 1;
		std::uint32_t replace_self_w_widget : 1;
		std::uint32_t go_back_to_previous_widget : 1;
		std::uint32_t run_scenario_script : 1;
		std::uint32_t try_to_branch_on_failure : 1;
	};
	static_assert(sizeof(EventHandlerReferencesFlags) == sizeof(std::uint32_t));

	struct ConditionalWidgetReferenceFlags {
		std::uint16_t load_if_event_handler_function_fails : 1;
	};
	static_assert(sizeof(ConditionalWidgetReferenceFlags) == sizeof(std::uint16_t));

	struct ChildWidgetReferenceFlags {
		std::uint16_t use_custom_controller_index : 1;
	};
	static_assert(sizeof(ChildWidgetReferenceFlags) == sizeof(std::uint16_t));

	struct UIWidgetDefinitionFlags {
		std::uint32_t pass_unhandled_events_to_focused_child : 1;
		std::uint32_t pause_game_time : 1;
		std::uint32_t flash_background_bitmap : 1;
		std::uint32_t dpad_up_down_tabs_thru_children : 1;
		std::uint32_t dpad_left_right_tabs_thru_children : 1;
		std::uint32_t dpad_up_down_tabs_thru_list_items : 1;
		std::uint32_t dpad_left_right_tabs_thru_list_items : 1;
		std::uint32_t dont_focus_a_specific_child_widget : 1;
		std::uint32_t pass_unhandled_events_to_all_children : 1;
		std::uint32_t render_regardless_of_controller_index : 1;
		std::uint32_t pass_handled_events_to_all_children : 1;
		std::uint32_t return_to_main_menu_if_no_history : 1;
		std::uint32_t always_use_tag_controller_index : 1;
		std::uint32_t always_use_nifty_render_fx : 1;
		std::uint32_t dont_push_history : 1;
		std::uint32_t force_handle_mouse : 1;
	};
	static_assert(sizeof(UIWidgetDefinitionFlags) == sizeof(std::uint32_t));

	struct UIWidgetDefinitionFlags1 {
		std::uint16_t editable : 1;
		std::uint16_t password : 1;
		std::uint16_t flashing : 1;
		std::uint16_t dont_do_that_weird_focus_test : 1;
	};
	static_assert(sizeof(UIWidgetDefinitionFlags1) == sizeof(std::uint16_t));

	struct UIWidgetDefinitionFlags2 {
		std::uint32_t list_items_generated_in_code : 1;
		std::uint32_t list_items_from_string_list_tag : 1;
		std::uint32_t list_items_only_one_tooltip : 1;
		std::uint32_t list_single_preview_no_scroll : 1;
	};
	static_assert(sizeof(UIWidgetDefinitionFlags2) == sizeof(std::uint32_t));

	struct GameDataInputReference {
		Memory::BigEndian<UIGameDataInputReferenceFunction> function;
		PADDING(2);
		PADDING(32);
	};
	static_assert(sizeof(GameDataInputReference) == 36);

	struct EventHandlerReference {
		Memory::BigEndian<EventHandlerReferencesFlags> flags;
		Memory::BigEndian<UIEventType> event_type;
		Memory::BigEndian<UIEventHandlerReferenceFunction> function;
		TagDependency widget_tag;
		TagDependency sound_effect;
		TagString script;
	};
	static_assert(sizeof(EventHandlerReference) == 72);

	struct SearchAndReplaceReference {
		TagString search_string;
		Memory::BigEndian<UIReplaceFunction> replace_function;
	};
	static_assert(sizeof(SearchAndReplaceReference) == 34);

	struct ConditionalWidgetReference {
		TagDependency widget_tag;
		TagString name;
		Memory::BigEndian<ConditionalWidgetReferenceFlags> flags;
		Index custom_controller_index;
		PADDING(26);
	};
	static_assert(sizeof(ConditionalWidgetReference) == 80);

	struct ChildWidgetReference {
		TagDependency widget_tag;
		TagString name;
		Memory::BigEndian<ChildWidgetReferenceFlags> flags;
		Index custom_controller_index;
		Memory::BigEndian<std::int16_t> vertical_offset;
		Memory::BigEndian<std::int16_t> horizontal_offset;
		PADDING(22);
	};
	static_assert(sizeof(ChildWidgetReference) == 80);

	struct UiWidgetDefinition {
		Memory::BigEndian<UIWidgetType> widget_type;
		Memory::BigEndian<UIControllerIndex> controller_index;
		TagString name;
		Rectangle2D bounds;
		Memory::BigEndian<UIWidgetDefinitionFlags> flags;
		Memory::BigEndian<std::int32_t> milliseconds_to_auto_close;
		Memory::BigEndian<std::int32_t> milliseconds_auto_close_fade_time;
		TagDependency background_bitmap;
		TagReflexive<GameDataInputReference> game_data_inputs;
		TagReflexive<EventHandlerReference> event_handlers;
		TagReflexive<SearchAndReplaceReference> search_and_replace_functions;
		PADDING(128);
		TagDependency text_label_unicode_strings_list;
		TagDependency text_font;
		ColorARGB text_color;
		Memory::BigEndian<UIJustification> justification;
		Memory::BigEndian<UIWidgetDefinitionFlags1> flags_1;
		PADDING(12);
		Index string_list_index;
		Memory::BigEndian<std::int16_t> horiz_offset;
		Memory::BigEndian<std::int16_t> vert_offset;
		PADDING(26);
		PADDING(2);
		Memory::BigEndian<UIWidgetDefinitionFlags2> flags_2;
		TagDependency list_header_bitmap;
		TagDependency list_footer_bitmap;
		Rectangle2D header_bounds;
		Rectangle2D footer_bounds;
		PADDING(32);
		TagDependency extended_description_widget;
		PADDING(32);
		PADDING(256);
		TagReflexive<ConditionalWidgetReference> conditional_widgets;
		PADDING(128);
		PADDING(128);
		TagReflexive<ChildWidgetReference> child_widgets;
	};
	static_assert(sizeof(UiWidgetDefinition) == 1004);

}

#endif

