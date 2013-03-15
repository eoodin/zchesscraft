#ifndef ZCHESS_H
#define ZCHESS_H

#include <QString>
#include <QPoint>
#include <QStack>

// Chinese chess definitions

#define PLAYER_ROLE     qint32
#define PLAYER_RED      (1)
#define PLAYER_BLACK    (0)
#define PLAYER_COUNT    (2)

// chessman types
#define MAN_LORD        (0)
#define MAN_GUARD       (1)
#define MAN_MINISTER    (2)
#define MAN_HORSE       (3)
#define MAN_VEHICLE     (4)
#define MAN_CANNON      (5)
#define MAN_SOLDIER     (6)

#define MAN_TYPE_COUNT  (7)
#define MAN_COUNT       (16)

#define BOARD_COLUMNS   (9)
#define BOARD_ROWS      (10)

#define PLAYER_BLACK     (0)
#define PLAYER_RED       (1)
#define PLAYER_OPPONENT(player)  ((~player) & 0x01)

#define CHESS   qint32

//    31       30       29     24 23     16   15      8   7       0
// |<dead>||<player>|   |<type>|  |<index>|    |<--x-->|   |<--y-->|

#define CHESS_TYPE(a)   ( ((a) >> 24) & 0x3F)
#define CHESS_PLAYER(a) ( ((a) >> 30) & 0x01)   // only allow PLAYER_BLACK OR PLAYER_RED
#define CHESS_INDEX(a)  ( ((a) >> 16) & 0xFF)
#define CHESS_X(a)      ( ((a) >> 8)  & 0xFF)
#define CHESS_Y(a)      (  (a)        & 0xFF)
#define CHESS_DEAD(a)   ( ((a) >> 31) & 0x01)

#define CHESS_KILL(a)   (  (a) | (0x01 << 31) )
#define CHESS_REVIVE(a) (  (a)        & (~(0x01 << 31)))

#define CHESS_MOVE(a,x,y) (  (a & 0xFFFF0000) | ((x) << 8) | (y))

#define INVALID_INDEX   (0x80)
#define MAX_CHESS_INDEX (PLAYER_COUNT * MAN_COUNT - 1)

// Combine a properties of a chessman to a CHESS
#define COMBINE_CHESS(player, type, index, x, y)  \
            (((player) << 30) | ((type) << 24) | ((index) << 16) | (x << 8) | (y))

// The Invalid chess indicated by CHESS_TYPE = 7
#define INVALID_CHESS   COMBINE_CHESS(0, 7, 0, 0, 0)

#define AGGRESSIVE(chess) ((CHESS_TYPE(chess)) >= MAN_HORSE)

//  Position definition,
//  Store where the chessman indicated by index located.
//
//  31       23        15       7       0
//  |<kill>| |<index>| |<--x-->||<--y-->|
#define POSITION    qint32

#define POSITION_X(pos)     ( ((pos) >> 8)  & 0xFF )
#define POSITION_Y(pos)     (  (pos)        & 0xFF )
#define POSITION_INDEX(pos) ( ((pos) >> 16) & 0xFF )
#define POSITION_KILL(pos)  ( ((pos) >> 24) & 0xFF )

#define COMBINE_POSITION(index, x, y, kill) \
            (((kill) << 24) | ((index) << 16) | ((x) << 8) | (y))

#define INVALID_POSITION    COMBINE_POSITION(INVALID_INDEX, 0, 0, INVALID_INDEX)

#define SEARCH_DEPTH_MAX    (20)
#define HISTROY_MAX         (1024)

#define MAX_MOVABLE         (20)

class MovingPolicy;

class ChessModel
{
public:
    ChessModel();

    ~ChessModel();

    void reset();

    bool backStep(int step = 1);

    bool isOver();

    bool canMove(CHESS* pChess, int x, int y);

    bool move(CHESS* pChess, int toX, int toY);

    CHESS* chessAt(int x, int y);

    CHESS* chessAt(int index);

    PLAYER_ROLE currentPlayer();

    /**
      * Fill the pPositions with possible moves for given chessman
      */
    void getPossibleMoves(CHESS* pChessman, POSITION* pPositions);

protected:

    void setupChessmenPolicies();

    void updateBoard();


private:
    CHESS           chessmen[PLAYER_COUNT * MAN_COUNT];

    PLAYER_ROLE     activePlayer;

    // Store indexes
    qint32          board[BOARD_COLUMNS][BOARD_ROWS];

    MovingPolicy*   policies[MAN_TYPE_COUNT];

    POSITION        histroy[HISTROY_MAX];

    int             histroyIndex;

    // The characters
    QString         characters;

    int             lastKill;
};

#endif // ZCHESS_H
