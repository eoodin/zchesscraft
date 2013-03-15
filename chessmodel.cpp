#include <QFile>
#include <QDebug>
#include <qmessagebox.h>


#include "chessmodel.h"
#include "zchesspolicies.h"
#include "zchessres.h"

int INDEX_TO_TYPE[]    = {
    MAN_LORD,      // 0
    MAN_GUARD,      // 1
    MAN_GUARD,      // 2
    MAN_MINISTER,   // 3
    MAN_MINISTER,   // 4
    MAN_HORSE,      // 5
    MAN_HORSE,      // 6
    MAN_VEHICLE,    // 7
    MAN_VEHICLE,    // 8
    MAN_CANNON,     // 9
    MAN_CANNON,     // 10
    MAN_SOLDIER,    // 11
    MAN_SOLDIER,    // 12
    MAN_SOLDIER,    // 13
    MAN_SOLDIER,    // 14
    MAN_SOLDIER     // 15
    };

int INITIAL_TABLE[] = {4,0,
3,0,
5,0,
2,0,
6,0,
1,0,
7,0,
0,0,
8,0,
1,2,
7,2,
0,3,
2,3,
4,3,
6,3,
8,3,

4,9,
3,9,
5,9,
2,9,
6,9,
1,9,
7,9,
0,9,
8,9,
1,7,
7,7,
0,6,
2,6,
4,6,
6,6,
8,6};

CHESS InvalidChess = INVALID_CHESS;
int InvalidIndex = INVALID_INDEX;
ChessModel::ChessModel()
{
    histroyIndex = -1;
    characters   = ZChessRes::instance()->characters();
    reset();
    setupChessmenPolicies();
}

ChessModel::~ChessModel()
{
    for (int i = 0; i < MAN_TYPE_COUNT; i++)
    {
        delete policies[i];
    }
}

void ChessModel::reset()
{
    // initialize positions
    for (int player = 0; player < PLAYER_COUNT; player++)
    {
        for (int index = 0; index < MAN_COUNT; index++)
        {
            int chessIndex = player * MAN_COUNT + index;
            chessmen[chessIndex] = COMBINE_CHESS(player, INDEX_TO_TYPE[index],
                  chessIndex, INITIAL_TABLE[chessIndex * 2], INITIAL_TABLE[chessIndex * 2 + 1]);
        }
    }
    histroyIndex = -1;
    activePlayer = PLAYER_RED;
    updateBoard();
}

bool ChessModel::move(CHESS* pChess, int toX, int toY)
{
    qint32 chessIndex = CHESS_INDEX(* pChess);

    if (chessIndex == INVALID_INDEX)  // No chessman located there.
        return false;

    if (canMove(pChess, toX, toY))
    {
        qint32 killedIndex = board[toX][toY];
        if (killedIndex != INVALID_INDEX)  // There is a chess.
        {
            chessmen[killedIndex] = CHESS_KILL(chessmen[killedIndex]);
        }
        int fromX = CHESS_X(*pChess);
        int fromY = CHESS_Y(*pChess);

        chessmen[chessIndex]    = CHESS_MOVE(*pChess, toX, toY); //Move it in chessmen
        histroy[++histroyIndex] = COMBINE_POSITION(chessIndex, fromX, fromY, killedIndex);
        activePlayer            = PLAYER_OPPONENT(activePlayer); // turn to opponent.

        updateBoard();
        return true;
    }
    return false;
}


bool ChessModel::backStep(int step)
{
    if (histroyIndex + 1 < step) // There is no so much histroy items
    {
        qDebug() << "There is no more history.";
        return false;
    }
    bool changed = false;
    for (;step > 0; step--)
    {
        POSITION hisItem = histroy[histroyIndex];
        qint32 chessIndex = POSITION_INDEX(hisItem);
        qint32 killedIndex = POSITION_KILL(hisItem);
        if (chessIndex != INVALID_INDEX)
        {
            CHESS theChessman        = chessmen[chessIndex];
            chessmen[chessIndex]     = CHESS_MOVE(theChessman, POSITION_X(hisItem), POSITION_Y(hisItem));
            if (killedIndex != INVALID_INDEX)
            {
                chessmen[killedIndex] = CHESS_REVIVE((chessmen[killedIndex]));
            }
            histroyIndex --;
        }
        activePlayer = PLAYER_OPPONENT(activePlayer);
        changed = true;
    }
    if (changed)
        updateBoard();
    return changed;
}

bool ChessModel::isOver()
{
    if (CHESS_DEAD(chessmen[PLAYER_BLACK * MAN_COUNT + MAN_LORD]))
        return true;
    if (CHESS_DEAD(chessmen[PLAYER_RED   * MAN_COUNT + MAN_LORD]))
        return true;
    return false;
}

void ChessModel::setupChessmenPolicies()
{
    policies[MAN_LORD]      = new LordMovingPolicy;
    policies[MAN_GUARD]     = new GuardMovingPolicy;
    policies[MAN_MINISTER]  = new MinisterMovingPolicy;
    policies[MAN_HORSE]     = new HorseMovingPolicy;
    policies[MAN_VEHICLE]   = new VehicleMovingPolicy;
    policies[MAN_CANNON]    = new CannonMovingPolicy;
    policies[MAN_SOLDIER]   = new SoldierMovingPolicy;
}

void ChessModel::updateBoard()
{
    for (int x = 0; x < BOARD_COLUMNS; x++)
    {
        for (int y = 0; y < BOARD_ROWS; y++)
        {
            board[x][y] = INVALID_INDEX;
        }
    }

    for (int j = 0; j < PLAYER_COUNT; j++)
    {
        for (int i = 0; i < MAN_COUNT; i ++)
        {
            CHESS chess = chessmen[j * MAN_COUNT + i];
            if (CHESS_DEAD(chess)) continue;
            board[CHESS_X(chess)][CHESS_Y(chess)] = j * MAN_COUNT + i;
        }
    }
}

bool ChessModel::canMove(CHESS* pChessman, int toX, int toY)
{
    return policies[CHESS_TYPE(*pChessman)]->canMove(this, pChessman, toX, toY);
}


PLAYER_ROLE ChessModel::currentPlayer()
{
    return activePlayer;
}

void ChessModel::getPossibleMoves(CHESS* pChessman, POSITION* pPositions)
{
    policies[CHESS_TYPE(*pChessman)]->fillMovables(this, pPositions, pChessman);
}

CHESS* ChessModel::chessAt(int x, int y)
{
    if (x < 0 || x >= BOARD_COLUMNS) {qDebug()<<"ChessModel: Wrong player"; }
    if (y < 0 || y >= BOARD_ROWS) {qDebug()<<"ChessModel: Wrong index";}
    if (x >= 0 && x < BOARD_COLUMNS && y >= 0 && y < BOARD_ROWS && board[x][y] != InvalidIndex)
        return & chessmen[board[x][y]];
    return & InvalidChess;
}

CHESS* ChessModel::chessAt(int index)
{
    if (index > -1 && index <= MAX_CHESS_INDEX)
    {
        return &(chessmen[index]);
    }
    return & InvalidChess;
}

