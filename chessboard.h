#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QGraphicsItem>
#include "zchessres.h"

// Chess Board definitions

#define BOARD_GRID_SIZE     (GRID_SIZE)
#define BOARD_ROWS          (10)
#define BOARD_COLUMNS        (9)

class QPainter;
class Chessman;
class ChessModel;

class Chessboard : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Chessboard(ChessModel* model);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

public:
    static QPoint toModelPos(QPointF posInScene);
protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    // drawing
    void inline drawMark(QPainter* painter, int x, int y);

public slots:
    void putChess(int fromIndex, int posX, int posY);
    void showPossibleMoves(Chessman* chessman);
signals:
    void chessmanMoved(int chessIndex, int toX, int toY);

private:
    Chessman* activeChessman;
    ChessModel* chessModel;
};

#endif // CHESSBOARD_H
