// SPDX-License-Identifier: GPL-3.0-only

#include <chrono>
#include <stdexcept>
#include <windows.h>
#include "status.hpp"

using timestamp_t = std::chrono::steady_clock::time_point;

namespace Harmony::Server {
    static constexpr const char *query = "\\info\\";
    static constexpr int buffer_size = 4096;
    static constexpr int timeout = 1000;

    using status_t = std::map<std::string, std::string>;

    std::string query_status(std::string address, std::uint16_t port) {
        // Timestamps
        timestamp_t query_start;
        timestamp_t query_finish;

        // Response buffer
        char response_buffer[buffer_size] = {0};

        // Setup Socket
        SOCKET fp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        // Server data
        SOCKADDR_IN sockaddr;
        sockaddr.sin_family = AF_INET;
        sockaddr.sin_port = htons(port);
        sockaddr.sin_addr.s_addr = inet_addr(address.c_str());
        int sockaddr_len = sizeof(sockaddr);

        // Set socket timeout
        setsockopt(fp, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char *>(&timeout), sizeof(timeout));

        // Send request
        int request_result = sendto(fp, query, strlen(query), 0, reinterpret_cast<SOCKADDR *>(&sockaddr), sizeof(sockaddr));
        if(request_result == SOCKET_ERROR) {
            closesocket(fp);
            throw std::runtime_error("failed to send query to server");
        }

        // Recv start timestamp
        query_start = std::chrono::steady_clock::now();

        // Get the server response
        int response_result = recvfrom(fp, response_buffer, buffer_size - 1, 0, reinterpret_cast<SOCKADDR *>(&sockaddr), &sockaddr_len);
        if(response_result == SOCKET_ERROR) {
            throw std::runtime_error("failed to receive data from server");
        }
        else if(response_result < 0) {
            throw std::runtime_error("server timeout");
        }

        // Recv end timestamp
        query_finish = std::chrono::steady_clock::now();

        // Calculate the query duration in milliseconds
        auto ping = std::chrono::duration_cast<std::chrono::milliseconds>(query_finish - query_start);

        // Create output string
        std::string output = "\\ping\\" + std::to_string(ping.count()) + response_buffer;

        return output;
    }

    status_t parse_status(std::string server_response) {
        status_t status;

        // from Chimera <3
        std::pair<std::string, std::string> kv;
        bool key = true;
        char *str_start = server_response.data() + 1;
        for(char *c = str_start; *c; c++) {
            bool break_now = false;
            if(*c != '\\' && c[1] == 0) {
                c++;
                break_now = true;
            }
            if(*c == '\\') {
                if(key) {
                    kv.first = std::string(str_start, c - str_start);
                }
                else {
                    // Strip invalid/whitespace characters from the start. If the string is all invalid, don't strip the last character.
                    for(char *k = str_start; k + 1 < c && *k <= 0x20; k++, str_start++);

                    // And here we go!
                    kv.second = std::string(str_start, c - str_start);

                    // Next, replace any unknown characters with '?'
                    for(char &c : kv.second) {
                        if(c < 0x20) {
                            c = '?';
                        }
                    }

                    status.insert_or_assign(kv.first, kv.second);
                    kv = {};
                }
                key = !key;
                str_start = c + 1;
            }
            if(break_now) {
                break;
            }
        }

        return std::move(status);
    }
}
