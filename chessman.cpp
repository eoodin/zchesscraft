#include <QPainter>
#include <QMimeData>
#include <QDrag>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QVariant>
#include <QApplication>
#include <QWidget>

#include "chessman.h"
#include "chessboard.h"
#include "chessmodel.h"
#include "zchessres.h"

Chessman::Chessman(CHESS* m)
{
    model = m;
    setAcceptDrops(true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setAcceptedMouseButtons(Qt::LeftButton);
    //setOpacity(0.7);
}

void Chessman::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasColor()
        || (qgraphicsitem_cast<Chessman *>(this))) {
        event->setAccepted(true);
        update();
    } else {
        event->setAccepted(false);
    }
}

void Chessman::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    update();
}

void Chessman::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    QString info;
    if (event->mimeData()->hasText())
        info = event->mimeData()->text();
    bool convertOk;
    int dragIndex = info.toInt(&convertOk);
    if (convertOk)
    {
        QPointF pos = event->scenePos();
        QPoint modelPos = Chessboard::toModelPos(pos);
        emit putChessman(dragIndex, modelPos.x(), modelPos.y());
    }
    update();
}

void Chessman::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(this);
}

void Chessman::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }

    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    QString index = QString("%1").arg(CHESS_INDEX(*model));
    mime->setText(index);
    drag->setMimeData(mime);
    drag->exec();
//    setCursor(Qt::OpenHandCursor);
}

void Chessman::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
}

QRectF Chessman::boundingRect() const
{
    return QRectF(- BOARD_GRID_SIZE / 2, - BOARD_GRID_SIZE / 2, BOARD_GRID_SIZE, BOARD_GRID_SIZE);
}


QPoint Chessman::modelPos()
{
    return QPoint(CHESS_X(*model), CHESS_Y(*model));
}

bool Chessman::isKilled()
{
    CHESS c = *model;
    return CHESS_DEAD(c) != 0;
}

void Chessman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath p;
    p.addEllipse(- BOARD_GRID_SIZE / 2, - BOARD_GRID_SIZE / 2, BOARD_GRID_SIZE, BOARD_GRID_SIZE);
    painter->fillPath(p,QBrush(QPixmap(":/images/res/stone8.jpg")));
    painter->drawPath(p);
    QRectF textRect = p.boundingRect();
    // Debug:
//    painter->drawRect(boundingRect());
    textRect.translate(10, 10);
    if (CHESS_PLAYER(*model) == PLAYER_RED)
        painter->setPen(QColor(255,0,0));
    else
        painter->setPen(QColor(0,0,0));

    QFont font = ZChessRes::instance()->chessFont();
    painter->setFont(font);
    painter->drawText(textRect, ZChessRes::instance()->characters().at(CHESS_TYPE(*model)));
}
