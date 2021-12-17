// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_HALO_DATA_WIDGET_HPP
#define HARMONY_HALO_DATA_WIDGET_HPP

#include <string>
#include <cstdint>
#include <limits>
#include <utility>
#include "../math/geometry.hpp"
#include "../memory/struct.hpp"
#include "tag.hpp"

namespace Harmony::HaloData {
    /**
     * A WidgetEvent that indicates an analog stick has a non-zero axis value.
     */ 
    struct AnalogStickWidgetEvent {
        using Count = std::int16_t;

        /**
         * If an axis count reaches max_count or min_count, then the widget receives
         * the (left/right)_analog_stick_(up/down/left/right) events.
         */
        static constexpr Count MAX_COUNT = std::numeric_limits<Count>::max();
        static constexpr Count MIN_COUNT = std::numeric_limits<Count>::min();

        /** The measure of the analog stick along the vertical axis. */
        Count vertical;

        /** The measure of the analog stick along the horizontal axis. */
        Count horizontal;

        /** 
         * Tests if the analog stick is fully up.
         * @return `true` if the analog stick is fully up, otherwise `false`.
         */
        bool is_fully_up() const {
            return vertical == MAX_COUNT;
        }
        
        /** 
         * Tests if the analog stick is fully down.
         * @return `true` if the analog stick is fully down, otherwise `false`.
         */
        bool is_fully_down() const {
            return vertical == MIN_COUNT;
        }
        
        /** 
         * Tests if the analog stick is fully left.
         * @return `true` if the analog stick is fully left, otherwise `false`.
         */
        bool is_fully_left() const {
            return horizontal == MIN_COUNT;
        }
        
        /** 
         * Tests if the analog stick is fully right.
         * @return `true` if the analog stick is fully right, otherwise `false`.
         */
        bool is_fully_right() const {
            return horizontal == MAX_COUNT;
        }
    };
    
    /**
     * A WidgetEvent that represents a pressed button on the gamepad.
     *
     * The PC version uses these events even for keypresses.
     * If inspecting the queues, assume that menu navigation is taking place on a controller.
     * For instance, the arrow keys will emit `button_dpad_*` events.
     *
     * Technically speaking, these events can trigger any widget event handler.
     * However, Halo only ever fills the gamepad button events.
     */
    struct GamepadButtonWidgetEvent {
        enum Button : std::int8_t {
            BUTTON_A = 0,
            BUTTON_B,
            BUTTON_X,
            BUTTON_Y,
            BUTTON_BLACK,
            BUTTON_WHITE,
            BUTTON_LEFT_TRIGGER,
            BUTTON_RIGHT_TRIGGER,
            BUTTON_DPAD_UP,
            BUTTON_DPAD_DOWN,
            BUTTON_DPAD_LEFT,
            BUTTON_DPAD_RIGHT,
            BUTTON_START,
            BUTTON_BACK,
            BUTTON_LEFT_THUMB,
            BUTTON_RIGHT_THUMB
        };

        /** The gamepad button pressed. */
        Button button;

        /**
         * The duration #button has been pressed for.
         * This must be `1`, otherwise the event gets dropped during processing.
         */
        std::uint8_t duration;
        
        /**
         * Get string for a gamepad button
         * @param btn   Gamepad button code
         * @return      Stringified button
         */
        static std::string string_for_button(Button btn) noexcept;
    };
    
    /**
     * A WidgetEvent that represents a pressed or held button on the mouse.
     */
    struct MouseButtonWidgetEvent {
        /** Maximum duration for event */
        static constexpr auto duration_max = std::numeric_limits<std::uint8_t>::max();

        enum Button : std::int8_t {
            BUTTON_LEFT = 0,
            BUTTON_MIDDLE,
            BUTTON_RIGHT,
            BUTTON_DOUBLE_LEFT
        };

        /** The mouse button pressed. */
        Button button;

        /** The duration #button was held for, up to #duration_max. */
        std::uint8_t duration;

        /**
         * Get string for a mouse button
         * @param btn   Mouse button code
         * @return      Stringified button
         */
        static std::string string_for_button(Button btn) noexcept;
    };
    
    /** 
     * Describes an event for the widget system to process.
     *
     * The top-level widget receives these events and calls upon its handlers to process the events.
     * Depending on how the widget is set up, the events may be sent down to child widgets.
     */
    struct WidgetEvent {
        enum EventType : std::int16_t {
            TYPE_NONE = 0,
            TYPE_LEFT_ANALOG_STICK, 
            TYPE_RIGHT_ANALOG_STICK,
            TYPE_GAMEPAD_BUTTON,
            TYPE_MOUSE_BUTTON,
            TYPE_CUSTOM_ACTIVATION
        };

        union Event {
            /** Parameters for an analog stick event. */
            AnalogStickWidgetEvent analog;

            /** Parameters for a gamepad button event. */
            GamepadButtonWidgetEvent gamepad;

            /** Parameters for a mouse button event. */
            MouseButtonWidgetEvent mouse;

            /** Event raw value */
            std::int32_t value;
        };

        /** Indicates the variant of event. */
        EventType event_type;

        /** The player the event is for, or -1 for any player. */
        std::int16_t local_player_index;

        /** The event descriptor. The variant is determined by the event type. */
        Event event;
    }; 
    static_assert(sizeof(WidgetEvent) == 0x08);
    
    /**
     * Contains data necessary to store and process widget events.
     */
    struct WidgetEventGlobals {
        /**
         * A FIFO queue where the front of the queue is the last element in the array that has 
         * an `event_type` not equal to `type_none`.
         *
         * Pushing onto the queue involves a `memmove`, but Halo does not call it correctly and swaps
         * the destination and source operands.
         * As a result, when a widget event is pushed, Halo evicts the first element in the array.
         * Then it writes over the second-now-first element in the array.
         * Halo drops two events per push because of this bug.
         */
        using EventQueue = WidgetEvent[8];

        bool initialized;
        bool drop_events;

        /** The time of the last input, in milliseconds. */
        std::int32_t input_time;

        /** The time of the last update, in milliseconds. */
        std::int32_t update_time;

        /** The widget event queues, for each player. */
        EventQueue queues[4];
        
        /**
         * Get the widget event globals
         * @return reference to the widget event globals
         */
        static WidgetEventGlobals &get();
    };
    static_assert(sizeof(bool) == 0x1);
    
    /**
     * The widget cursor's positioning and movement.
     *
     * Widgets and the widget cursor in vanilla Halo work in a 640 by 480 grid.
     * Chimera upgrades this with the widescreen fix.
     * A couple of functions are provided to ease translation.
     */
    struct WidgetCursorGlobals {
        /** Lock to prevent recursion on cursor-related operations (speculation). */
        bool lock;
        
        /** If `true`, Halo will use `GetCursor()` to calculate changes in cursor position. */
        bool use_get_cursor;
        
        /** Halo sets this to `true` if the cursor has moved since its last update. */
        bool position_changed;

        /** The position of the cursor, in widget coordinates. */
        struct {
            /** The horizontal coordinate of the cursor, in widget coordinates. */
            std::int32_t x;

            /** The vertical coordinate of the cursor, in widget coordinates. */
            std::int32_t y;
        } position;
        
        /**
         * Gets the position of the cursor in window client space, with each
         * coordinate normalized to the range `[0,1]`.
         *
         * The top-left corner of the client window is `(0, 0)`.
         * The bottom-right corner of the client window is `(1, 1)`.
         * 
         * @return Cursor position.
         */
        Math::Point2D get_normalized_position() const;
        
        /**
         * Gets the position of the cursor with respect to the screen coordinates of the framebuffer.
         *
         * Unlike normalized position, this is based on the dimensions of the framebuffer.
         * For a 1024 by 720 framebuffer, the bottom right corner will be `(1024, 720)`.
         *
         * @return Cursor position.
         */
        Math::Point2D get_framebuffer_position() const;
        
        /**
         * Get the widget cursor globals
         * @return reference to the widget cursor globals
         */
        static WidgetCursorGlobals &get();
    };
    static_assert(sizeof(WidgetCursorGlobals) == 0x0C);

    struct WidgetInstance {
        enum Type : std::uint16_t {
            WIDGET_TYPE_CONTAINER = 0,
            WIDGET_TYPE_TEXT_BOX,
            WIDGET_TYPE_SPINNER_LIST,
            WIDGET_TYPE_COLUMN_LIST,
            WIDGET_TYPE_GAME_MODEL,
            WIDGET_TYPE_MOVIE,
            WIDGET_TYPE_CUSTOM
        };

        /** ID of the widget tag */
        TagID tag_id;

        /** Name of the widget */
        const char *name;

        /** Sets if the widget is hidden */
        std::uint16_t hidden;

        /** Widget frame left bound */
        std::int16_t left_bound;

        /** Widget frame top bound */
        std::int16_t top_bound;

        /** Widget type */
        Type type;

        /** Unknown flags related to the widget history */
        std::uint16_t visible;
        PADDING(0x2);
        PADDING(0x4);

        /** A widget instance related to the history */
        WidgetInstance *unknown_history_thing_1;

        /** Milliseconds to close widgets */
        std::uint32_t ms_to_close;

        /** Widget close fade time in milliseconds */
        std::uint32_t ms_to_close_fade_time;
        
        /** Widget opacity (from 0 to 1) */
        float opacity;

        /** Previous widget of the list. Null in the first list item. */
        WidgetInstance *previous_widget;

        /** Next widget of the list. Null in the last list item. */
        WidgetInstance *next_widget;

        /** Parent widget. Null in the root widget. */
        WidgetInstance *parent;

        /** Child widget. */
        WidgetInstance *child;

        /** Focussed child widget. Null in non-list widgets. */
        WidgetInstance *focused_child;

        /** Text box content. Null in non-text box widgets. */
        const wchar_t *text;

        /** Last widget list element focussed by cursor */
        std::uint16_t cursor_index;
        PADDING(0x2);

        PADDING(0x4);
        PADDING(0x4);
        PADDING(0x4);

        PADDING(0x4);
        PADDING(0x4);

        /** Currently focussed */
        std::uint32_t focused;

        PADDING(0x4);
    }; 
    static_assert(sizeof(WidgetInstance) == 0x60);

    struct WidgetHistoryEntry {
        /** Previous menu root widget */
        WidgetInstance *previous_menu;

        /** Previous menu list widget */
        WidgetInstance *previous_menu_list;

        /** Unknown flags */
        PADDING(0x2);
        PADDING(0x2);

        /** Previous history entry */
        WidgetHistoryEntry *previous;
    };
    static_assert(sizeof(WidgetHistoryEntry) == 0x10);
    
    /**
     * Describes the general state of widgets and widget display.
     */ 
    struct WidgetGlobals {
        /** An error that is in queue. */
        struct EnqueuedErrorDescriptor {
            /** Index of the error in the error strings tag. */
            std::int16_t error_string;

            /** Index of the local player the error is for. */
            std::int16_t local_player;

            /** Are a modal error? */
            bool display_modal;

            /** Pauses the game? */
            bool display_paused;
        };
        static_assert(sizeof(EnqueuedErrorDescriptor) == 0x06);

        /** An error that is waiting for the current cinematic to end before being displayed. */
        struct DeferredErrorDescriptor {
            /** Index of the error in the error strings tag. */
            std::int16_t error_string;

            /** Are a modal error? */
            bool display_modal;

            /** Pauses the game? */
            bool display_paused;
        };
        static_assert(sizeof(DeferredErrorDescriptor) == 0x04);

        /** The root widget instance for current menu. */
        WidgetInstance *root_widget_instance;

        /** Last widget history entry */
        WidgetHistoryEntry *history_top_entry;

        /** Current time in milliseconds */
        std::int32_t current_time;

        /** Ticks remaining for popup (i think) */
        std::int32_t popup_display_time;
        
        std::int16_t error_message_index;
        std::int16_t widget_pause_counter;

        PADDING(0x4); // float

        /** Errors queue for each local player */
        EnqueuedErrorDescriptor enqueued_errors[1];

        /** takes precedence over enqueued_errors, always displays modal, non-paused */
        DeferredErrorDescriptor priority_warning;

        /** Deferred errors for each local player */
        DeferredErrorDescriptor deferred_for_cinematic_errors[1];

        /** no path sets this, real type is HANDLE* */
        void *initialization_thread;

        /**
         * 1 = all progress will be lost, 2 = insert another quarter
         * only used on the widget update after initialization_thread exits
         * does anyone know if an arcade version of Halo 1 was planned?
         */
        std::int16_t demo_error;

        /** Is this struct initialized? */
        bool initialized;

        PADDING(0x01); // bool
        PADDING(0x01); // bool
        PADDING(0x01); // bool
        PADDING(0x01); // bool
        PADDING(0x01); // bool
        
        /**
         * Get the widget globals
         * @return reference to the widget globals
         */
        static WidgetGlobals &get();
    };
    static_assert(sizeof(WidgetGlobals) == 0x34);

    /**
     * Open a UI widget
     * @param widget_id         Tag ID of the widget that will be opened.
     * @param push_history      Do not create an entry in the history, just override the current widget.
     */
    void open_widget(TagID widget_id, bool push_history = true) noexcept;
}

#endif
