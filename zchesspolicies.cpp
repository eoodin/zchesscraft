#include "zchesspolicies.h"

bool MovingPolicy::canMove(ChessModel* chess, CHESS* chessman, int toX, int toY)
{
    if (!generalCanMove(chess, chessman, toX, toY))
    {
        return false;
    }
    return canMoveTo(chess, chessman, toX, toY);
}

bool MovingPolicy::generalCanMove(ChessModel* chess, CHESS* chessman, int toX, int toY)
{
    if (toX < 0 || toY < 0) return false;
    if (toX > 8 || toY > 9) return false;
    CHESS* exist = chess->chessAt(toX, toY);
    if (*exist != INVALID_CHESS && CHESS_PLAYER(*exist) == CHESS_PLAYER(*chessman))
    {
        return false;
    }
    // Have not moved any.
    if (CHESS_X(*chessman) == toX && CHESS_Y(*chessman) == toY) return false;
    return true;
}


bool LordMovingPolicy::canMoveTo(ChessModel* chess, CHESS* chessman, int toX, int toY)
{

    if ( toX < 3 || toX > 5) return false;
    if ( CHESS_PLAYER(*chessman) == PLAYER_BLACK && toY > 2) return false;
    if ( CHESS_PLAYER(*chessman) == PLAYER_RED   && toY < 7) return false;
    // Only can move one grid.
    if (qAbs(toX - CHESS_X(*chessman)) + qAbs(toY - CHESS_Y(*chessman)) > 1)return false;

    return true;
}

void LordMovingPolicy::fillMovables(ChessModel* chess, int* movables,  CHESS* manModel)
{
    int x = CHESS_X(*manModel);
    int y = CHESS_Y(*manModel);
    int fillIndex = 0;
    // up
    if (canMove(chess, manModel, x - 1, y)) movables[fillIndex++] = ((x - 1) << 8) | y;
    if (canMove(chess, manModel, x + 1, y)) movables[fillIndex++] = ((x + 1) << 8) | y;
    if (canMove(chess, manModel, x, y - 1)) movables[fillIndex++] = (x << 8) | (y - 1);
    if (canMove(chess, manModel, x, y + 1)) movables[fillIndex++] = (x << 8) | (y + 1);
    movables[fillIndex] = 0x8080;
}

bool GuardMovingPolicy::canMoveTo(ChessModel* chess, CHESS* chessman, int toX, int toY)
{
    if ( toX < 3 || toX > 5) return false;
    if ( CHESS_PLAYER(*chessman) == PLAYER_BLACK && toY > 2) return false;
    if ( CHESS_PLAYER(*chessman) == PLAYER_RED   && toY < 7) return false;
    if (qAbs(toX - CHESS_X(*chessman)) != 1 || qAbs(toY - CHESS_Y(*chessman)) != 1)return false;
    return true;
}

void GuardMovingPolicy::fillMovables(ChessModel* chess, int* movables,  CHESS* manModel)
{
    int x = CHESS_X(*manModel);
    int y = CHESS_Y(*manModel);
    int fillIndex = 0;
    // up
    if (canMove(chess, manModel, x - 1, y - 1)) movables[fillIndex++] = ((x - 1) << 8) | (y - 1);
    if (canMove(chess, manModel, x + 1, y + 1)) movables[fillIndex++] = ((x + 1) << 8) | (y + 1);
    if (canMove(chess, manModel, x + 1, y - 1)) movables[fillIndex++] = ((x + 1) << 8) | (y - 1);
    if (canMove(chess, manModel, x - 1, y + 1)) movables[fillIndex++] = ((x - 1)<< 8) | (y + 1);
    movables[fillIndex] = 0x8080;
}

bool MinisterMovingPolicy::canMoveTo(ChessModel* chess, CHESS* chessman, int toX, int toY)
{
    if ( CHESS_PLAYER(*chessman) == PLAYER_BLACK && toY > 4) return false;
    if ( CHESS_PLAYER(*chessman) == PLAYER_RED   && toY < 5) return false;
    if (qAbs(toX - CHESS_X(*chessman)) != 2 || qAbs(toY - CHESS_Y(*chessman)) != 2)return false;
    if (*chess->chessAt((CHESS_X(*chessman) + toX)/2, (CHESS_Y(*chessman) + toY) / 2) != INVALID_CHESS) return false;
    return true;
}

void MinisterMovingPolicy::fillMovables(ChessModel* chess, int* movables,  CHESS* manModel)
{
    int x = CHESS_X(*manModel);
    int y = CHESS_Y(*manModel);
    int fillIndex = 0;
    // up
    if (canMove(chess, manModel, x - 2, y - 2)) movables[fillIndex++] = ((x - 2) << 8) | (y - 2);
    if (canMove(chess, manModel, x + 2, y + 2)) movables[fillIndex++] = ((x + 2) << 8) | (y + 2);
    if (canMove(chess, manModel, x + 2, y - 2)) movables[fillIndex++] = ((x + 2) << 8) | (y - 2);
    if (canMove(chess, manModel, x - 2, y + 2)) movables[fillIndex++] = ((x - 2)<< 8) | (y + 2);
    movables[fillIndex] = 0x8080;
}

bool HorseMovingPolicy::canMoveTo(ChessModel* chess, CHESS* chessman, int toX, int toY)
{
    if (qAbs(toX - CHESS_X(*chessman)) == 2 && qAbs(toY - CHESS_Y(*chessman)) == 1)
    {
        CHESS* exist = chess->chessAt((CHESS_X(*chessman) + toX) / 2,CHESS_Y(*chessman));
        if (*exist == INVALID_CHESS) return true;
    }
    if (qAbs(toX - CHESS_X(*chessman)) == 1 && qAbs(toY - CHESS_Y(*chessman)) == 2)
    {
        CHESS* exist = chess->chessAt(CHESS_X(*chessman) ,(CHESS_Y(*chessman) + toY) / 2);
        if (*exist == INVALID_CHESS) return true;
    }
    return false;
}

void HorseMovingPolicy::fillMovables(ChessModel* chess, int* movables,  CHESS* manModel)
{
    int x = CHESS_X(*manModel);
    int y = CHESS_Y(*manModel);
    int fillIndex = 0;
    // up
    if (canMove(chess, manModel, x - 2, y - 1)) movables[fillIndex++] = ((x - 2) << 8) | (y - 1);
    if (canMove(chess, manModel, x + 2, y + 1)) movables[fillIndex++] = ((x + 2) << 8) | (y + 1);
    if (canMove(chess, manModel, x + 2, y - 1)) movables[fillIndex++] = ((x + 2) << 8) | (y - 1);
    if (canMove(chess, manModel, x - 2, y + 1)) movables[fillIndex++] = ((x - 2) << 8) | (y + 1);

    if (canMove(chess, manModel, x - 1, y - 2)) movables[fillIndex++] = ((x - 1) << 8) | (y - 2);
    if (canMove(chess, manModel, x + 1, y + 2)) movables[fillIndex++] = ((x + 1) << 8) | (y + 2);
    if (canMove(chess, manModel, x + 1, y - 2)) movables[fillIndex++] = ((x + 1) << 8) | (y - 2);
    if (canMove(chess, manModel, x - 1, y + 2)) movables[fillIndex++] = ((x - 1) << 8) | (y + 2);

    movables[fillIndex] = 0x8080;
}

bool VehicleMovingPolicy::canMoveTo(ChessModel* chess, CHESS* chessman, int toX, int toY)
{
    int fromX = CHESS_X(*chessman);
    int fromY = CHESS_Y(*chessman);
    if ( fromX != toX && fromY != toY) return false;
    if (fromY == toY)
    {
        if (fromX < toX)
        {
            for (int s = fromX + 1; s < toX; s++)
            {
                if (*chess->chessAt(s, fromY) != INVALID_CHESS) return false;
            }
        }
        else
        {
            for (int s = fromX - 1; s > toX; s--)
            {
                if (*chess->chessAt(s, fromY) != INVALID_CHESS) return false;
            }
        }
    }
    if (fromX == toX)
    {
        if (fromY < toY)
        {
            for (int s = fromY + 1; s < toY; s++)
            {
                if (*chess->chessAt(fromX, s) != INVALID_CHESS) return false;
            }
        }
        else
        {
            for (int s = fromY - 1; s > toY; s--)
            {
                if (*chess->chessAt(fromX, s) != INVALID_CHESS) return false;
            }
        }
    }
    return true;
}

void VehicleMovingPolicy::fillMovables(ChessModel* chess, int* movables,  CHESS* manModel)
{
    int fromX = CHESS_X(*manModel);
    int fromY = CHESS_Y(*manModel);
    int fillIndex = 0;

    for (int s = fromX + 1; s < 9; s++)
    {
        if (*chess->chessAt(s, fromY) != INVALID_CHESS)
        {
            if (CHESS_PLAYER(*chess->chessAt(s, fromY)) == CHESS_PLAYER(*manModel))
            {
                break;
            }
            movables[fillIndex++] = ((s) << 8) | fromY;
            break;
        }
        movables[fillIndex++] = ((s) << 8) | fromY;
    }

    for (int s = fromX - 1; s >= 0; s--)
    {
        if (*chess->chessAt(s, fromY) != INVALID_CHESS)
        {
            if (CHESS_PLAYER(*chess->chessAt(s, fromY)) == CHESS_PLAYER(*manModel))
            {
                break;
            }
            movables[fillIndex++] = ((s) << 8) | fromY;
            break;
        }
        movables[fillIndex++] = ((s) << 8) | fromY;
    }

    for (int s = fromY + 1; s < 10; s++)
    {
        if (*chess->chessAt(fromX, s) != INVALID_CHESS)
        {
            if (CHESS_PLAYER(*chess->chessAt(fromX, s)) == CHESS_PLAYER(*manModel))
            {
                break;
            }
            movables[fillIndex++] = ((fromX) << 8) | s;
            break;
        }
        movables[fillIndex++] = ((fromX) << 8) | s;
    }

    for (int s = fromY - 1; s >= 0; s--)
    {
        if (*chess->chessAt(fromX, s) != INVALID_CHESS)
        {
            if (CHESS_PLAYER(*chess->chessAt(fromX, s)) == CHESS_PLAYER(*manModel))
            {
                break;
            }
            movables[fillIndex++] = ((fromX) << 8) | s;
            break;
        }
        movables[fillIndex++] = ((fromX) << 8) | s;
    }
    movables[fillIndex] = 0x8080;
}

bool CannonMovingPolicy::canMoveTo(ChessModel* chess, CHESS* chessman, int toX, int toY)
{
    int fromX = CHESS_X(*chessman);
    int fromY = CHESS_Y(*chessman);
    if ( fromX != toX && fromY != toY) return false;
    CHESS*  exist = chess->chessAt(toX, toY);
    bool isKilling = false;
    if (*exist != INVALID_CHESS)
        isKilling = CHESS_PLAYER(*exist) != CHESS_PLAYER(*chessman);

    int overred = 0;
    // killing:
    if (fromY == toY)
    {
        if (fromX < toX)
        {
            for (int s = fromX + 1; s < toX; s++)
            {
                if (!isKilling && *chess->chessAt(s, fromY) != INVALID_CHESS) return false;
                if (isKilling && *chess->chessAt(s, fromY) != INVALID_CHESS) overred++;
                if (overred > 1)return false;
            }
        }
        else
        {
            for (int s = fromX - 1; s > toX; s--)
            {
                if (!isKilling && *chess->chessAt(s, fromY) != INVALID_CHESS) return false;
                if (isKilling && *chess->chessAt(s, fromY) != INVALID_CHESS) overred++;
                if (overred > 1)return false;
            }
        }
    }
    if (fromX == toX)
    {
        if (fromY < toY)
        {
            for (int s = fromY + 1; s < toY; s++)
            {
                if (!isKilling && *chess->chessAt(fromX, s) != INVALID_CHESS) return false;
                if (isKilling && *chess->chessAt(fromX, s) != INVALID_CHESS) overred++;
                if (overred > 1)return false;
            }
        }
        else
        {
            for (int s = fromY - 1; s > toY; s--)
            {
                if (!isKilling && *chess->chessAt(fromX, s) != INVALID_CHESS) return false;
                if (isKilling && *chess->chessAt(fromX, s) != INVALID_CHESS) overred++;
                if (overred > 1)return false;
            }
        }
    }
    // No cannon flatfrom.
    if (isKilling && overred != 1) return false;
    return true;
}

void CannonMovingPolicy::fillMovables(ChessModel* chess, int* movables,  CHESS* manModel)
{
    int fillIndex = 0;
    int fromX = CHESS_X(* manModel);
    int fromY = CHESS_Y(* manModel);
    int up = fromY;
    int down = fromY;
    int left = fromX;
    int right = fromX;

    for (int s = fromX + 1; s < 9; s++) // to right
    {
        if (*chess->chessAt(s, fromY) != INVALID_CHESS)  // enconter own *chessman.
        {
            right = s;
            break;
        }
        movables[fillIndex++] = ((s) << 8) | fromY;
    }

    for (int s = fromX - 1; s >= 0; s--) // to left
    {
        if (*chess->chessAt(s, fromY) != INVALID_CHESS) // enconter own *chessman.
        {
            left = s;
            break;
        }
        movables[fillIndex++] = (s << 8) | fromY;
    }


    for (int s = fromY + 1; s < 10; s++) // to down
    {
        if (*chess->chessAt(fromX, s) != INVALID_CHESS){
            down = s;
            break;
        }
        movables[fillIndex++] = (fromX << 8) | s;
    }

    for (int s = fromY - 1; s >= 0; s--) // to up
    {
        if (*chess->chessAt(fromX, s) != INVALID_CHESS){
            up = s;
            break;
        }
        movables[fillIndex++] = (fromX << 8) | s;
    }
    // killing
    for (int s = right + 1; s < 9; s++)
    {
        if (*chess->chessAt(s, fromY) != INVALID_CHESS &&
            CHESS_PLAYER(*chess->chessAt(s, fromY)) != CHESS_PLAYER(*manModel))
        {
            movables[fillIndex++] = ((s) << 8) | fromY;
            break;
        }
    }

    for (int s = left - 1; s >= 0; s--)
    {
        if (*chess->chessAt(s, fromY) != INVALID_CHESS &&
            CHESS_PLAYER(*chess->chessAt(s, fromY)) != CHESS_PLAYER(*manModel))
        {
            movables[fillIndex++] = ((s) << 8) | fromY;
            break;
        }
    }

    for (int s = down + 1; s < 10; s++)
    {
        if (*chess->chessAt(fromX, s) != INVALID_CHESS &&
            CHESS_PLAYER(*chess->chessAt(fromX, s)) != CHESS_PLAYER(*manModel)){
            movables[fillIndex++] = (fromX << 8) | s;
            break;
        }
    }

    for (int s = up - 1; s >= 0; s--)
    {
        if (*chess->chessAt(fromX, s) != INVALID_CHESS &&
            CHESS_PLAYER(*chess->chessAt(fromX, s)) != CHESS_PLAYER(*manModel)){
            movables[fillIndex++] = (fromX << 8) | s;
            break;
        }
    }
    movables[fillIndex] = 0x8080;
}

bool SoldierMovingPolicy::canMoveTo(ChessModel* chess, CHESS* chessman, int toX, int toY)
{
    // Only can move one grid.
    if (qAbs(toX - CHESS_X(*chessman)) + qAbs(toY - CHESS_Y(*chessman)) > 1)return false;
    if (CHESS_PLAYER(*chessman) == PLAYER_BLACK && toY < CHESS_Y(*chessman)) return false;
    if (CHESS_PLAYER(*chessman) == PLAYER_RED   && toY > CHESS_Y(*chessman)) return false;
    if (CHESS_PLAYER(*chessman) == PLAYER_BLACK && toY < 5 && CHESS_X(*chessman) != toX) return false;
    if (CHESS_PLAYER(*chessman) == PLAYER_RED   && toY > 4 && CHESS_X(*chessman) != toX) return false;
    return true;
}

void SoldierMovingPolicy::fillMovables(ChessModel* chess, int* movables,  CHESS* manModel)
{
    int fillIndex = 0;
    int fromX = CHESS_X(*manModel);
    int fromY = CHESS_Y(*manModel);
    if (canMove(chess, manModel, fromX, fromY + 1)) movables[fillIndex++] = (fromX << 8) | (fromY + 1);
    if (canMove(chess, manModel, fromX, fromY - 1)) movables[fillIndex++] = (fromX << 8) | (fromY - 1);
    if (canMove(chess, manModel, fromX + 1, fromY)) movables[fillIndex++] = ((fromX + 1) << 8) | fromY;
    if (canMove(chess, manModel, fromX - 1, fromY)) movables[fillIndex++] = ((fromX - 1) << 8) | fromY;
    movables[fillIndex] = 0x8080;
}
