#include "zcomputer.h"
#include <QDebug>


int INDEX_TO_VALUE[] = {
     100000,//MAN_LORD,      // 0
        175,//MAN_GUARD,      // 1
        175,//MAN_GUARD,      // 2
        150,//MAN_MINISTER,   // 3
        150,//MAN_MINISTER,   // 4
        270,//MAN_HORSE,      // 5
        270,//MAN_HORSE,      // 6
        600,//MAN_VEHICLE,    // 7
        600,//MAN_VEHICLE,    // 8
        260,//MAN_CANNON,     // 9
        260,//MAN_CANNON,     // 10
         30,//MAN_SOLDIER,    // 11
         30,//MAN_SOLDIER,    // 12
         30,//MAN_SOLDIER,    // 13
         30,//MAN_SOLDIER,    // 14
         30//MAN_SOLDIER     // 15
};
int MOVE_GENERATE_ORDER[] = {
    7,//MAN_VEHICLE,    // 7
    8,//MAN_VEHICLE,    // 8
    9,//MAN_CANNON,     // 9
    10,//MAN_CANNON,     // 10
    5,//MAN_HORSE,      // 5
    6,//MAN_HORSE,      // 6
    11,//MAN_SOLDIER,    // 11
    12,//MAN_SOLDIER,    // 12
    13,//MAN_SOLDIER,    // 13
    14,//MAN_SOLDIER,    // 14
    15,//MAN_SOLDIER,     // 15
      3,//MAN_MINISTER,   // 3
      4,//MAN_MINISTER,   // 4
      1,//MAN_GUARD,      // 1
      2,//MAN_GUARD,      // 2
      0//MAN_LORD,      // 0
};
//#define MAN_LORD        (0)
//#define MAN_GUARD       (1)
//#define MAN_MINISTER    (2)
//#define MAN_HORSE       (3)
//#define MAN_VEHICLE     (4)
//#define MAN_CANNON      (5)
//#define MAN_SOLDIER     (6)
//player, type, x, y
int LOCATION_TO_VALUE[2][7][9][10] = {
    {   // BLACK
        {// MAN_LORD        (0)
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            { 10,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
        },
        {//MAN_GUARD       (1)
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            { 10,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            { 10,  10,   0,   0,   0,   0,   0,   0,   0,   0},
            { 10,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
        },
        {//MAN_MINISTER    (2)
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            { 20,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,  20,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            { 20,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
        },
        {//MAN_HORSE       (3)
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,  40,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0, 120,   0},
            {  0,   0,   0,   0,  20,   0,   0,  80,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,  20,   0,   0,  80,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0, 120,   0},
            {  0,   0,   0,   0,   0,   0,  40,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
        },
        {//MAN_VEHICLE     (4)
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            { 60,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {100,  20,   0,   0, 100,   0,   0,   0, 180,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {100,  20,   0,   0, 100,   0,   0,   0, 180,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            { 60,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
        },
        {//MAN_CANNON      (5)
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0, 150,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
        },
        {//MAN_SOLDIER     (6)
            {  0,   0,   0,   0,   0,  10,  20,  20,  20,  10},
            {  0,   0,   0,   0,   0,  10,  20,  20,  20,  10},
            {  0,   0,   0,   0,   0,  10,  20,  20,  20,  10},
            {  0,   0,   0,   0,   0,  10,  20,  20,  50,  10},
            {  0,   0,   0,   0,   0,  10,  20,  20,  20,  10},
            {  0,   0,   0,   0,   0,  10,  20,  20,  50,  10},
            {  0,   0,   0,   0,   0,  10,  20,  20,  20,  10},
            {  0,   0,   0,   0,   0,  10,  20,  20,  20,  10},
            {  0,   0,   0,   0,   0,  10,  20,  20,  20,  10}
        }
    },
    {   // RED
        {// MAN_LORD        (0)
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,  0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,  0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,  0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,  0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,  10},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,  0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,  0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,  0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,  0}
        },
        {//MAN_GUARD       (1)
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,  10},
            {  0,   0,   0,   0,   0,   0,   0,   0,  10,  10},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,  10},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
        },
        {//MAN_MINISTER    (2)
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,  20},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,  20,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,  20},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
        },
        {//MAN_HORSE       (3)
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,  20,   0,   0,   0,   0,   0,   0},
            {  0, 120,   0,   0,   0,  20,   0,   0,   0,   0},
            {  0,   0,  80,  40,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,  80,   0,   0,  20,   0,   0,   0,   0},
            {  0, 120,   0,  40,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,  20,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
        },
        {//MAN_VEHICLE     (4)
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,  60},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0, 180,   0,   0,   0, 100,   0,   0,  20, 100},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0, 180,   0,   0,   0, 100,   0,   0,  20, 100},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,  60},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
        },
        {//MAN_CANNON      (5)
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0, 150,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
        },
        {//MAN_SOLDIER     (6)
            {  10,  20,  20,  20, 10,   0,   0,   0,   0,   0},
            {  10,  20,  20,  20, 10,   0,   0,   0,   0,   0},
            {  10,  20,  20,  20, 10,   0,   0,   0,   0,   0},
            {  10,  50,  20,  20, 10,   0,   0,   0,   0,   0},
            {  10,  20,  20,  20, 10,   0,   0,   0,   0,   0},
            {  10,  50,  20,  20, 10,   0,   0,   0,   0,   0},
            {  10,  20,  20,  20, 10,   0,   0,   0,   0,   0},
            {  10,  20,  20,  20, 10,   0,   0,   0,   0,   0},
            {  10,  20,  20,  20, 10,   0,   0,   0,   0,   0}
        }
    }
};

ZComputer::ZComputer(ChessModel* chess) :
        chessModel (chess)
{
    searchDepth = 2;
    role = PLAYER_BLACK;
}

POSITION ZComputer::calculateStep(int player)
{
    if (player != PLAYER_BLACK && player != PLAYER_RED)
        return INVALID_POSITION;

//    copyBoard();
    bestValue = -100000;
    bestMove = INVALID_POSITION;
    currentDepth = 0;
    searchNext();
    // return the first position searched.
    return searchStack[0];
}


int ZComputer::alphaBetaSearch(int depth, int alpha, int beta) {
    if (depth <= 0) {
        return calculateAdvantage();
    }
    POSITION movables[MAX_MOVABLE];
    for (int index = 0; index < MAN_COUNT; index ++)
    {
        int genIndex = MOVE_GENERATE_ORDER[index];
        CHESS* pChessman = chessModel->chessAt(role * MAN_COUNT + genIndex);
        if (CHESS_DEAD(*pChessman))
            continue;

        chessModel->getPossibleMoves(pChessman, movables);
        for (int s = 0; s < MAX_MOVABLE; s++)
        {
            // No more possible steps.
            if (movables[s] == 0x8080) break;
            int x = POSITION_X(movables[s]);
            int y = POSITION_Y((movables[s]));

//            searchStack[currentDepth] = COMBINE_POSITION(CHESS_INDEX(*pChessman), x, y, CHESS_INDEX(* chessModel->chessAt(x, y)));
            POSITION currentPos = COMBINE_POSITION(CHESS_INDEX(*pChessman), x, y, CHESS_INDEX(* chessModel->chessAt(x, y)));

            if (chessModel->move(pChessman, x, y))
            {
                int childValue = - alphaBetaSearch(depth - 1, -beta, -alpha);
                chessModel->backStep();
                if (childValue >= beta)
                {
                    searchStack[depth - 1] = currentPos;
                    return childValue;
                }
                if (childValue > alpha)
                {
                    searchStack[depth - 1] = currentPos;
                    alpha = childValue;
                }
            }
        }
    }
    return alpha;
}

void ZComputer::searchNext()
{
    if (currentDepth == searchDepth)
    {
        int advantage = calculateAdvantage();
        if (advantage > bestValue)
        {
            bestValue = advantage;
            bestMove  = searchStack[0];
        }
        return;
    }
    if (currentDepth > searchDepth)
        return;

    POSITION movables[MAX_MOVABLE];
    for (int index = 0; index < MAN_COUNT; index ++)
    {
        CHESS* pChessman = chessModel->chessAt(chessModel->currentPlayer() * MAN_COUNT + index);
        if (CHESS_DEAD(*pChessman))
            continue;
        chessModel->getPossibleMoves(pChessman, movables);
        for (int s = 0; s < MAX_MOVABLE; s++)
        {
            // No more possible steps.
            if (movables[s] == 0x8080) break;
            int x = POSITION_X(movables[s]);
            int y = POSITION_Y((movables[s]));

            searchStack[currentDepth] = COMBINE_POSITION(CHESS_INDEX(*pChessman), x, y, CHESS_INDEX(* chessModel->chessAt(x, y)));

            if (chessModel->move(pChessman, x, y))
            {
                currentDepth ++;
                searchNext();
                currentDepth --;
                chessModel->backStep();
            }
        }
    }
}

int ZComputer::calculateAdvantage()
{
    int value = 0;
    CHESS invalidChess = INVALID_CHESS;
    int chessCount = 0;
    for (int x = 0; x < BOARD_COLUMNS; x++)
    {
        for (int y = 0; y < BOARD_ROWS; y++)
        {
            CHESS c = *(chessModel->chessAt(x, y));
            if (c == invalidChess)
            {
                continue;
            }
            PLAYER_ROLE player = CHESS_PLAYER(c);
            // calculate fixed chess value.
            int chessValue = INDEX_TO_VALUE[CHESS_INDEX(c) % MAN_COUNT];
            // location value
            chessValue += LOCATION_TO_VALUE[player][CHESS_TYPE(c)][x][y];
            if (player == PLAYER_RED)
                chessValue *= -1;
            value += chessValue;
            chessCount ++;
        }
    }
//    if (chessCount < MAN_COUNT * PLAYER_COUNT)
//        qDebug() << "Chess checked :" << chessCount;
    return value;
}

void ZComputer::play()
{
    if (chessModel->currentPlayer() != role)
        return;

    bestValue = -100000;
    bestMove = INVALID_POSITION;
    currentDepth = 0;
//    searchNext();
    int value = alphaBetaSearch(5, -100000, 100000);
    qDebug()<<"alphaBeatSearch: value = " << value;
    bestMove = searchStack[4];
    if (bestMove  != INVALID_POSITION)
    {
        int chessmanIndex = POSITION_INDEX(bestMove);
        int x = POSITION_X(bestMove);
        int y = POSITION_Y(bestMove);
        // played
        qDebug() << "Computer: moving chessman (index= " << chessmanIndex << ") to (" << x << y << ")";
        emit moveCalculated(chessmanIndex, x, y);
    }
}

