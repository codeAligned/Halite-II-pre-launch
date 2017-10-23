#pragma once

#include <iostream>
#include <sstream>

#include "log.hpp"
#include "move.hpp"

namespace hlt {
    namespace out {
        static bool send_string(const std::string& text) {
            // note that std::endl flushes
            std::cout << text << std::endl;
            return !std::cout.bad();
        }

        /** Send all queued moves to the game engine. */
        static bool send_moves(const std::vector<Move>& moves) {
            std::ostringstream oss;
            for (const auto& move : moves) {
                switch (move.type) {
                    case MoveType::Noop:
                        continue;
                    case MoveType::Undock:
                        oss << "u " << move.ship_id << " ";
                        break;
                    case MoveType::Dock:
                        oss << "d " << move.ship_id << " "
                            << move.move.dock_to << " ";
                        break;
                    case MoveType::Thrust:
                        oss << "t " << move.ship_id << " "
                            << move.move.thrust.thrust << " "
                            << move.move.thrust.angle << " ";
                        break;
                }
            }
            Log::log(oss.str());
            return send_string(oss.str());
        }
    }
}