module Halite

using Memento

include("init.jl")
include("constants.jl")
include("commands.jl")
include("common.jl")
include("entity.jl")
include("game_map.jl")
include("networking.jl")
include("positionals.jl")

"""
    read_input()

Reads input from stdin, shutting down logging and exiting if an EOFError occurs
"""
function read_input()
    try
        return readline()
    catch err
        log(err)
        rethrow(err)
    end
end

export Direction, logging

end #module Halite