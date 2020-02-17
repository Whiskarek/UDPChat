#include "../state.hpp"
#include "../../client.hpp"
#include "../../strings.hpp"
#include "../connected_state.hpp"

using namespace states;

void State::help() {
    _client.out() << strings::help << std::endl;
}

void State::login(const std::string &username) {
    _client._username = username;
    socket().set_username(username);
    strings::success::username_changed(_client.out(), username);
}

void State::connect_server(const std::string &ip, const std::string &port) {
    auto handler = [&](bool connected) -> void {
        if (connected) {
            strings::success::connected_to_server(_client.out(), ip, port);
            _client.set_state<ConnectedState>();
        } else {
            strings::error::connection_failed(_client.out(), ip, port);
        }
    };
    socket().connect(ip, port);
    handler(true);
}

std::string State::username() const {
    return _client._username;
}

Socket &State::socket() const {
    return _client._socket;
}