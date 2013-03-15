#ifndef ZCOMPUTER_H
#define ZCOMPUTER_H

#include "chessmodel.h"
#include <QObject>


#define MAX_SEARCH_DEPTH        (20)

class ZComputer : public QObject
{
    Q_OBJECT
public:
    ZComputer(ChessModel* chess);

    POSITION calculateStep(int player);

protected:
    void searchNext();

    int alphaBetaSearch(int depth, int alpha, int beta);

    int calculateAdvantage();


signals:
    void moveCalculated(int chessmanIndex, int x, int y);

public slots:
    void play();

private:
    CHESS board[BOARD_COLUMNS][BOARD_ROWS];

    POSITION searchStack[SEARCH_DEPTH_MAX];
    POSITION bestMove;
    int currentDepth;
    int searchDepth;
    int bestValue;

    int bestStack[MAX_SEARCH_DEPTH];
    int bestChessIndex;

    ChessModel* chessModel;
    int role;
};

#endif // ZCOMPUTER_H
