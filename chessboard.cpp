#include <QPainter>
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QDebug>

#include "chessboard.h"
#include "chessman.h"
#include "chessmodel.h"

Chessboard::Chessboard(ChessModel* model) :
        chessModel(model)
{
    setAcceptDrops(true);
    setAcceptedMouseButtons(Qt::LeftButton);
    activeChessman = 0;
}

QRectF Chessboard::boundingRect() const
{
    int boardWidth  = BOARD_COLUMNS  * BOARD_GRID_SIZE;
    int boardHeight = BOARD_ROWS  * BOARD_GRID_SIZE;
    int startX      = -boardWidth >> 1;
    int startY      = -boardHeight >> 1;
    return QRectF(startX, startY, boardWidth, boardHeight);
}

void Chessboard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int boardWidth  = (BOARD_COLUMNS - 1) * BOARD_GRID_SIZE;
    int boardHeight = (BOARD_ROWS - 1) * BOARD_GRID_SIZE;
    int startX      = -boardWidth >> 1;
    int startY      = -boardHeight >> 1;
    int endX        = startX + boardWidth;
    int endY        = startY + boardHeight;

    painter->drawRect(startX, startY, boardWidth, boardHeight);
    QPen oldPen = painter->pen();
    oldPen.setWidth( 2 );
    painter->setPen(oldPen);
    painter->drawRect(startX - 5, startY - 5, boardWidth + 10, boardHeight + 10);
    oldPen.setWidth( 1 );
    painter->setPen(oldPen);
    // Draw rows.
    for (int row = 0; row < BOARD_ROWS; row++)
    {
        int offset = BOARD_GRID_SIZE * row;
        painter->drawLine(startX, startY + offset, endX, startY + offset);
    }
    // Draw columns
    for (int column = 0; column < BOARD_COLUMNS; column++)
    {
        int offset = BOARD_GRID_SIZE *column;
        painter->drawLine(startX + offset, startY, startX + offset, startY + BOARD_GRID_SIZE * 4);
        painter->drawLine(startX + offset, startY+ BOARD_GRID_SIZE * 5, startX + offset, endY);
    }

    // Draw basilicas
    painter->drawLine(startX + BOARD_GRID_SIZE * 3, startY,startX + BOARD_GRID_SIZE * 5,startY + BOARD_GRID_SIZE * 2);
    painter->drawLine(startX + BOARD_GRID_SIZE * 5, startY,startX + BOARD_GRID_SIZE * 3,startY + BOARD_GRID_SIZE * 2);
    painter->drawLine(startX + BOARD_GRID_SIZE * 3, endY,startX + BOARD_GRID_SIZE * 5,endY - BOARD_GRID_SIZE * 2);
    painter->drawLine(startX + BOARD_GRID_SIZE * 5, endY,startX + BOARD_GRID_SIZE * 3,endY - BOARD_GRID_SIZE * 2);

    // Draw marks
    drawMark(painter, 1, 2);
    drawMark(painter, 7, 2);
    drawMark(painter, 0, 3);
    drawMark(painter, 2, 3);
    drawMark(painter, 4, 3);
    drawMark(painter, 6, 3);
    drawMark(painter, 8, 3);

    drawMark(painter, 1, 7);
    drawMark(painter, 7, 7);
    drawMark(painter, 0, 6);
    drawMark(painter, 2, 6);
    drawMark(painter, 4, 6);
    drawMark(painter, 6, 6);
    drawMark(painter, 8, 6);

    if (activeChessman != 0)
    {
        QPoint modelPos = activeChessman->modelPos();
        CHESS* chessman = chessModel->chessAt(modelPos.x(), modelPos.y());
        int moves[20];
        chessModel->getPossibleMoves(chessman, moves);
        painter->setBrush(QColor(255, 0, 0));
        for (int i = 0; i < 20; i++)
        {
            if (moves[i] == 0)
                break;
            painter->drawEllipse(startX + BOARD_GRID_SIZE * (moves[i] >> 8) - 5, startY + BOARD_GRID_SIZE * (moves[i] & 0xFF) - 5, 10, 10);
        }
    }
}


void inline Chessboard::drawMark(QPainter* painter, int x, int y)
{
    int boardWidth  = (BOARD_COLUMNS - 1) * BOARD_GRID_SIZE;
    int boardHeight = (BOARD_ROWS - 1) * BOARD_GRID_SIZE;
    int startX      = -boardWidth >> 1;
    int startY      = -boardHeight >> 1;
    if ( x > 0)
    painter->drawLine(BOARD_GRID_SIZE * x - BOARD_GRID_SIZE / 8 + startX,
                      BOARD_GRID_SIZE * y - BOARD_GRID_SIZE / 4 + startY,
                      BOARD_GRID_SIZE * x - BOARD_GRID_SIZE / 8 + startX,
                      BOARD_GRID_SIZE * y - BOARD_GRID_SIZE / 8 + startY);
    if (x < BOARD_COLUMNS - 1)
    painter->drawLine(BOARD_GRID_SIZE * x + BOARD_GRID_SIZE / 8 + startX,
                      BOARD_GRID_SIZE * y - BOARD_GRID_SIZE / 4 + startY,
                      BOARD_GRID_SIZE * x + BOARD_GRID_SIZE / 8 + startX,
                      BOARD_GRID_SIZE * y - BOARD_GRID_SIZE / 8 + startY);
    if ( x > 0)
    painter->drawLine(BOARD_GRID_SIZE * x - BOARD_GRID_SIZE / 4 + startX,
                      BOARD_GRID_SIZE * y - BOARD_GRID_SIZE / 8 + startY,
                      BOARD_GRID_SIZE * x - BOARD_GRID_SIZE / 8 + startX,
                      BOARD_GRID_SIZE * y - BOARD_GRID_SIZE / 8 + startY);
    if (x < BOARD_COLUMNS - 1)
    painter->drawLine(BOARD_GRID_SIZE * x + BOARD_GRID_SIZE / 4 + startX,
                      BOARD_GRID_SIZE * y - BOARD_GRID_SIZE / 8 + startY,
                      BOARD_GRID_SIZE * x + BOARD_GRID_SIZE / 8 + startX,
                      BOARD_GRID_SIZE * y - BOARD_GRID_SIZE / 8 + startY);
    if ( x > 0)
    painter->drawLine(BOARD_GRID_SIZE * x - BOARD_GRID_SIZE / 8 + startX,
                      BOARD_GRID_SIZE * y + BOARD_GRID_SIZE / 4 + startY,
                      BOARD_GRID_SIZE * x - BOARD_GRID_SIZE / 8 + startX,
                      BOARD_GRID_SIZE * y + BOARD_GRID_SIZE / 8 + startY);
    if (x < BOARD_COLUMNS - 1)
    painter->drawLine(BOARD_GRID_SIZE * x + BOARD_GRID_SIZE / 8 + startX,
                      BOARD_GRID_SIZE * y + BOARD_GRID_SIZE / 4 + startY,
                      BOARD_GRID_SIZE * x + BOARD_GRID_SIZE / 8 + startX,
                      BOARD_GRID_SIZE * y + BOARD_GRID_SIZE / 8 + startY);
    if ( x > 0)
    painter->drawLine(BOARD_GRID_SIZE * x - BOARD_GRID_SIZE / 4 + startX,
                      BOARD_GRID_SIZE * y + BOARD_GRID_SIZE / 8 + startY,
                      BOARD_GRID_SIZE * x - BOARD_GRID_SIZE / 8 + startX,
                      BOARD_GRID_SIZE * y + BOARD_GRID_SIZE / 8 + startY);
    if (x < BOARD_COLUMNS - 1)
    painter->drawLine(BOARD_GRID_SIZE * x + BOARD_GRID_SIZE / 4 + startX,
                      BOARD_GRID_SIZE * y + BOARD_GRID_SIZE / 8 + startY,
                      BOARD_GRID_SIZE * x + BOARD_GRID_SIZE / 8 + startX,
                      BOARD_GRID_SIZE * y + BOARD_GRID_SIZE / 8 + startY);

}


QPoint Chessboard::toModelPos(QPointF posInScene)
{
    QPoint pos(posInScene.x(), posInScene.y());
    QRectF  dropArea(
            - BOARD_GRID_SIZE * BOARD_COLUMNS / 2,
            - BOARD_GRID_SIZE * BOARD_ROWS / 2,
            BOARD_GRID_SIZE * BOARD_COLUMNS,
            BOARD_GRID_SIZE * BOARD_ROWS
            );
    if (pos.x() < dropArea.x())pos.setX(dropArea.x());
    if (pos.y() < dropArea.y())pos.setY(dropArea.y());
    if (pos.x() > dropArea.right())pos.setX(dropArea.right() - 1);
    if (pos.x() > dropArea.bottom())pos.setY(dropArea.bottom() - 1);
    int x = (pos.x() - dropArea.x()) / BOARD_GRID_SIZE;
    int y = (pos.y() - dropArea.y()) / BOARD_GRID_SIZE;
    return QPoint(x, y);
}

void Chessboard::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasText()) {
        event->setAccepted(true);
        update();
    } else {
        event->setAccepted(false);
    }
}

void Chessboard::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    QString info;
    if (event->mimeData()->hasText())
        info = event->mimeData()->text();
    bool convertOk;
    int dragIndex = info.toInt(&convertOk);
    if (convertOk)
    {
        QPointF pos = event->scenePos();
        QPoint modelPos = toModelPos(pos);
//        qDebug()<<"Droped to board:"<< dragIndex<<"At "<<x << y;
        emit chessmanMoved(dragIndex, modelPos.x(), modelPos.y());
    }
    update();
}
void Chessboard::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{

}

void Chessboard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void Chessboard::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}

void Chessboard::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

void Chessboard::putChess(int fromIndex, int posX, int posY)
{
    emit chessmanMoved(fromIndex, posX, posY);
}

void Chessboard::showPossibleMoves(Chessman* chessman)
{
    activeChessman = chessman;
    update();
}

