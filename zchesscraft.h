#ifndef ZCHESSCRAFT_H
#define ZCHESSCRAFT_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>

#include "chessmodel.h"

class ChessModel;
class Chessboard;
class ZComputer;
class Chessman;

namespace Ui {
    class ZChessCraft;
}

class ZChessCraft : public QMainWindow {
    Q_OBJECT
public:
    ZChessCraft(QWidget *parent = 0);
    ~ZChessCraft();

protected:
    void changeEvent(QEvent *e);


    void setupGraphics();
    void setupChessModel();
    void setupChessboard();
    void setupChessmen();
    void setupComputer();

    void updateChessmen();

signals:
    void chessmanMoved(int chessmanIndex, int x, int y);

protected slots:
    void moveChessman(int fromIndex, int toX, int toY);

private:
    Ui::ZChessCraft *ui;
    QGraphicsScene* scene;

    Chessboard* board;
    Chessman*   chessItems[PLAYER_COUNT * MAN_COUNT];
    QList<Chessman*>   hiddenItems;
    // Logical chess
    ChessModel* chessModel;
    ZComputer*  computer;

private slots:
    void on_actionUndoStep_triggered();
    void on_actionNewGame_triggered();
};

#endif // ZCHESSCRAFT_H
