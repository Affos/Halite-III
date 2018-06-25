#ifndef HALITE_STATISTICS_HPP
#define HALITE_STATISTICS_HPP

#include <set>
#include <string>
#include <vector>

#include "json.hpp"
#include "Constants.hpp"

namespace hlt {
class PlayerStatistics {
public:
    id_type player_id;                           /**< The ID of the player. */
    long rank{};                                 /**< The rank of the player (1 = highest) */
    unsigned long last_turn_alive{};             /**< The last turn the player remained alive */
    energy_type total_production{};              /**< Over the turns they were alive, the total production gained by a player */
    std::vector<energy_type> turn_productions{}; /**< Production granted to player each turn, turn 1 at front of vector */

    /**
     * Convert Player statistics to json format
     *
     * @param[out] json Empty json object to fill
     * @param statistics Player statistics struct to convert to json
     */
    friend void to_json(nlohmann::json &json, const PlayerStatistics &statistics);

    /**
     * Construct PlayerStatistics from Player ID
     * @param player_id The player ID.
     */
    explicit PlayerStatistics(id_type player_id) : player_id(player_id) {}
};

struct GameStatistics {
    std::vector<PlayerStatistics> player_statistics;     /**< Vector of statistics for each player. */
    unsigned long number_turns{};                        /**< Total number of turns that finished before game ende. */

    /**
     * Convert game statistics to json format
     *
     * @param[out] json Empty json object to fill
     * @param statistics Game statistics struct to convert to json
     */
    friend void to_json(nlohmann::json &json, const GameStatistics &statistics);
};

}
#endif //HALITE_STATISTICS_HPP