#pragma once
#ifndef CONNECTION_PARSER_HPP
#define CONNECTION_PARSER_HPP

#include "Generic_connection_parser.hpp"

namespace travel {

class ConnectionParser : public Generic_connection_parser {
public:
    void read_connections(const std::string& filename) override;
    void read_stations(const std::string& filename) override; // Stub implementation
};

} // namespace travel

#endif // CONNECTION_PARSER_HPP
