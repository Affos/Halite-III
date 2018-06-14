#include "Constants.hpp"
#include "BasicGenerator.hpp"
#include "Halite.hpp"
#include "HaliteImpl.hpp"

namespace hlt {

/** Run the game. */
void Halite::run_game() {
    for (auto &player : players) {
        networking.initialize_player(player);
    }
    const auto &constants = GameConstants::get();
    for (turn_number = 0; turn_number < constants.MAX_TURNS; turn_number++) {
        impl->retrieve_moves();
        impl->process_commands();
        impl->process_entities();
    }
    // TODO: thread the communications with players
}

/**
 * Constructor for the main game.
 *
 * @param config The configuration options for the game.
 * @param parameters The map generation parameters.
 * @param networking_config The networking configuration.
 * @param players The list of players.
 */
Halite::Halite(const Config &config,
               const mapgen::MapParameters &parameters,
               const net::NetworkingConfig &networking_config,
               std::list<Player> players) :
        config(config),
        parameters(parameters),
        networking(net::Networking(networking_config, this)),
        impl(std::make_unique<HaliteImpl>(this)),
        players(std::move(players)),
        game_map(mapgen::BasicGenerator(parameters).generate(players)) {}

/** Default destructor is defined where HaliteImpl is complete. */
Halite::~Halite() = default;

}
