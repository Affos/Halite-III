# julia 1.0

# Import the Halite SDK, which will let you interact with the game.
include("hlt/Halite.jl")
using Halite

""" <<<Game Begin>>> """
# This game object contains the initial game state.
game = Game()
# At this point "game" variable is populated with initial map data.
# This is a good place to do computationally expensive start-up pre-processing.
# As soon as you call "ready" function below, the 2 second per turn timer will start.
ready(game, "MyJuliaBot")

# Now that your bot is initialized, save a message to yourself in the log file with some important information.
#   Here, you log here your id, which you can always fetch from the game object by using my_id.
info("Successfully created bot! My Player ID is $(game.my_id)")

""" <<<Game Loop>>> """

while true
    # This loop handles each turn of the game. The game object changes every turn, and you refresh that state by
    #   running update_frame().
    update_frame(game)
    # You extract player metadata and the updated map metadata here for convenience.
    me = game.me
    game_map = game.game_map

    # A command queue holds all the commands you will run this turn. You build this list up and submit it at the
    #   end of the turn.
    command_queue = []

    for ship in get_ships(me)
        # For each of your ships, move randomly if the ship is on a low halite location or the ship is full.
        #   Else, collect halite.
        if game_map[ship.position].halite_amount < MAX_HALITE / 10 || ship.is_full:
            append!(command_queue,move(ship,
                    random.choice([ Direction.North, Direction.South, Direction.East, Direction.West ])))
        else:
            append!(command_queue, stay_still(ship))
        end
    end

    # If the game is in the first 200 turns and you have enough halite, spawn a ship.
    # Don't spawn a ship if you currently have a ship at port, though - the ships will collide.
    if game.turn_number <= 200 && me.halite_amount >= SHIP_COST && !game_map[me.shipyard].is_occupied:
        append!(command_queue, me.shipyard.spawn())
    end

    # Send your moves back to the game environment, ending this turn.
    end_turn(game, command_queue)
end