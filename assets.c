#include "assets.h"

// I Piece:
Pieces i_piece = {
    .piece = 'i',
    .piece_size = 3,
    .rotation_stages[0] = 1,
    .rotation_stages[1] = 4,
    .array = {
        {0, 0, 0, 0,},
        {0, 0, 0, 0,},
        {1, 1, 1, 1,},
        {0, 0, 0, 0,}
    }
};

// O Piece:
Pieces o_piece = {
    .piece = 'o',
    .piece_size = 3,
    .rotation_stages[0] = 1,
    .array = {
        {0, 0, 0, 0,},
        {0, 1, 1, 0,},
        {0, 1, 1, 0,},
        {0, 0, 0, 0,}
    }
};


// S Piece:
Pieces s_piece = {
    .piece = 's',
    .piece_size = 2,
    .rotation_stages[0] = 1,
    .rotation_stages[1] = 2,
    .array = {
        {0, 0, 0,},
        {0, 1, 1,},
        {1, 1, 0,},
    }
};

// Z Piece:
Pieces z_piece = {
    .piece = 'z',
    .piece_size = 2,
    .rotation_stages[0] = 1,
    .rotation_stages[1] = 2,
    .array = {
        {0, 0, 0,},
        {1, 1, 0,},
        {0, 1, 1,},
    }
};

// J Piece:
Pieces j_piece = {
    .piece = 'j',
    .piece_size = 2,
    .rotation_stages[0] = 1,
    .rotation_stages[1] = 2,
    .rotation_stages[2] = 3,
    .rotation_stages[3] = 4,
    .array = {
        {0, 0, 0,},
        {1, 1, 1,},
        {0, 0, 1,},
    }
};

// L Piece:
Pieces l_piece = {
    .piece = 'l',
    .piece_size = 2,
    .rotation_stages[0] = 1,
    .rotation_stages[1] = 2,
    .rotation_stages[2] = 3,
    .rotation_stages[3] = 4,
    .array = {
        {0, 0, 0,},
        {1, 1, 1,},
        {1, 0, 0,},
    }
};

// L Piece:
Pieces t_piece = {
    .piece = 't',
    .piece_size = 2,
    .rotation_stages[0] = 1,
    .rotation_stages[1] = 2,
    .rotation_stages[2] = 3,
    .rotation_stages[3] = 4,
    .array = {
        {0, 0, 0,},
        {1, 1, 1,},
        {0, 1, 0,},
    }
};
