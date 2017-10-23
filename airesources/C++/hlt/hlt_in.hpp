#pragma once

#include "map.hpp"

namespace hlt {
    namespace in {
        static std::string get_string() {
            std::string result;
            std::getline(std::cin, result);
            return result;
        }

        static std::pair<EntityIndex, Ship> parse_ship(std::istream& iss) {
            EntityIndex ship_id;
            iss >> ship_id;

            Ship ship;
            iss >> ship.location.pos_x;
            iss >> ship.location.pos_y;
            iss >> ship.health;
            iss >> ship.velocity.vel_x;
            iss >> ship.velocity.vel_y;
            int docking_status;
            iss >> docking_status;
            ship.docking_status = static_cast<DockingStatus>(docking_status);
            iss >> ship.docked_planet;
            iss >> ship.docking_progress;
            iss >> ship.weapon_cooldown;

            ship.radius = constants::SHIP_RADIUS;

            return std::make_pair(ship_id, ship);
        }

        static std::pair<EntityIndex, Planet> parse_planet(std::istream& iss) {
            Planet planet = {};
            EntityIndex planet_id;

            iss >> planet_id;
            iss >> planet.location.pos_x;
            iss >> planet.location.pos_y;
            iss >> planet.health;
            iss >> planet.radius;
            iss >> planet.docking_spots;
            iss >> planet.current_production;
            iss >> planet.remaining_production;
            int owned;
            iss >> owned;
            if (owned == 1) {
                planet.owned = true;
                int owner;
                iss >> owner;
                planet.owner = static_cast<PlayerId>(owner);
            }
            else {
                planet.owned = false;
                int false_owner;
                iss >> false_owner;
            }

            int num_docked_ships;
            iss >> num_docked_ships;
            planet.docked_ships.reserve(num_docked_ships);
            for (auto j = 0; j < num_docked_ships; j++) {
                EntityIndex ship_id;
                iss >> ship_id;
                planet.docked_ships.push_back(ship_id);
            }

            return std::make_pair(planet_id, planet);
        }

        static Map parse_map(const std::string& input, const int map_width, const int map_height) {
            Log::log("mp1");
            std::stringstream iss(input);

            Log::log("mp2");

            int num_players;
            iss >> num_players;

            Log::log("mp3");

            auto map = Map(map_width, map_height);

            Log::log("mp4");

            // Meaningless loop indices, used as bookkeeping
            for (auto i = 0; i < num_players; i++) {
                PlayerId player_id;
                int player_id_int;
                iss >> player_id_int;
                player_id = static_cast<PlayerId>(player_id_int);

                int num_ships;
                iss >> num_ships;

                map.ships[player_id] = {};
                for (auto j = 0; j < num_ships; j++) {
                    const auto& ship_pair = parse_ship(iss);
                    map.ships[player_id].insert(ship_pair);
                }
            }

            Log::log("mp5");

            int num_planets;
            iss >> num_planets;
            for (auto i = 0; i < num_planets; i++) {
                const auto& planet_pair = parse_planet(iss);
                map.planets[planet_pair.first] = planet_pair.second;
            }

            Log::log("mp6");

            return map;
        }

        static Map get_map(const int map_width, const int map_height) {
            Log::log("--- NEW TURN ---");
            const auto input = get_string();
            Log::log("input size: " + std::to_string(input.size()));
            Log::log("input: " + input);
            return parse_map(input, map_width, map_height);
        }
    }
}