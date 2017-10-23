#pragma once

namespace hlt {
    /** Uniquely identifies each player. */
    typedef int PlayerId;

    /**
     * Used to identify a ship or planet.
     *
     * Ships are uniquely identified by a combination of the PlayerId of their
     * owner and their EntityIndex. Planets are uniquely identified by their
     * EntityIndex alone.
     */
    typedef unsigned int EntityIndex;
}