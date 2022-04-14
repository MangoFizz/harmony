// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_SERVER_QUERY_HPP
#define HARMONY_SERVER_QUERY_HPP

#include <string>
#include <map>
#include <cstdint>

namespace Harmony::Server {
    using status_t = std::map<std::string, std::string>;

    /**
     * Query status from server
     * @param address   Server address
     * @param port      Server port
     */
    std::string query_status(std::string address, std::uint16_t port);

    /**
     * Parse server status
     * @param status_response   Status response from server
     * @return                  A map with the server status data
     */
    status_t parse_status(std::string status_response);
}

#endif
