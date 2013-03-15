#ifndef CHESSMAN_H
#define CHESSMAN_H

#include <QGraphicsItem>

#include "chessmodel.h"

class Chessman : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Chessman(CHESS* m);

    void setChess(CHESS m);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

    QPoint modelPos();
    bool isKilled();

signals:
    void clicked(Chessman*);

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    void putChessman(int fromIndex, int posX, int posY);
private:
    CHESS* model;
};

#endif // CHESSMAN_H
