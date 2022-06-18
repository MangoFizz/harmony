// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY__DEBUG__CLIENT_PLAYER_UPDATE_HISTORY_HPP
#define HARMONY__DEBUG__CLIENT_PLAYER_UPDATE_HISTORY_HPP

namespace Harmony::Debug {
    /**
     * Set whether or not log client player updates
     * @param setting   enable it or not
     */
    void enable_client_player_update_log(bool setting) noexcept;

    /**
     * Set up client player update log
     */
    void set_up_client_player_update_log() noexcept;
}

#endif
