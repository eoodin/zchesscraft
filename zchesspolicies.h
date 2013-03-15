#ifndef ZCHESSPOLICIES_H
#define ZCHESSPOLICIES_H

#include "chessmodel.h"

class MovingPolicy
{
public:
    virtual void fillMovables(ChessModel* chess, int* movables, CHESS* manModel) = 0;
    virtual bool canMove(ChessModel* chess, CHESS* chessman, int toX, int toY);
    bool generalCanMove(ChessModel* chess, CHESS* chessman, int toX, int toY);
protected:
    virtual bool canMoveTo(ChessModel* chess, CHESS* chessman, int toX, int toY) = 0;
};

class LordMovingPolicy : public MovingPolicy
{
public:
    bool canMoveTo(ChessModel* chess, CHESS* chessman, int toX, int toY);
    void fillMovables(ChessModel* chess, int* movables, CHESS* manModel);
};

class GuardMovingPolicy : public MovingPolicy
{
public:
    bool canMoveTo(ChessModel* chess, CHESS* chessman, int toX, int toY);
    void fillMovables(ChessModel* chess, int* movables, CHESS* manModel);
};

class MinisterMovingPolicy : public MovingPolicy
{
public:
    bool canMoveTo(ChessModel* chess, CHESS* chessman, int toX, int toY);
    void fillMovables(ChessModel* chess, int* movables, CHESS* manModel);
};

class HorseMovingPolicy : public MovingPolicy
{
public:
    bool canMoveTo(ChessModel* chess, CHESS* chessman, int toX, int toY);
    void fillMovables(ChessModel* chess, int* movables, CHESS* manModel);
};

class VehicleMovingPolicy : public MovingPolicy
{
public:
    bool canMoveTo(ChessModel* chess, CHESS* chessman, int toX, int toY);
    void fillMovables(ChessModel* chess, int* movables, CHESS* manModel);
};

class CannonMovingPolicy : public MovingPolicy
{
public:
    bool canMoveTo(ChessModel* chess, CHESS* chessman, int toX, int toY);
    void fillMovables(ChessModel* chess, int* movables, CHESS* manModel);
};

class SoldierMovingPolicy : public MovingPolicy
{
public:
    bool canMoveTo(ChessModel* chess, CHESS* chessman, int toX, int toY);
    void fillMovables(ChessModel* chess, int* movables, CHESS* manModel);
};

#endif // ZCHESSPOLICIES_H
