#ifndef maze_command_h
#define maze_command_h

enum Command {
    COMMAND_NONE,
    GENERATE_BINARY_TREE_INSTANT,
    GENERATE_BINARY_TREE,
    GENERATE_SIDEWINDER_INSTANT,
    GENERATE_SIDEWINDER,
    GENERATE_RANDOM_WALK_INSTANT,
    GENERATE_RANDOM_WALK,
    RESET_MAZE,
    INCREASE_MAZE_HEIGHT,
    INCREASE_MAZE_WIDTH,
    DECREASE_MAZE_HEIGHT,
    DECREASE_MAZE_WIDTH,
    COLOR_GRID_INSTANT,
    COLOR_GRID,
    MOVE_PLAYER_UP,
    MOVE_PLAYER_DOWN,
    MOVE_PLAYER_RIGHT,
    MOVE_PLAYER_LEFT,
    TOGGLE_PLAYER_STATE,
    SET_GOALS_RANDOM
};

#endif