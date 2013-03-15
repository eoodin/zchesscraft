#include "zchesscraft.h"
#include "ui_zchesscraft.h"
#include "chessboard.h"
#include "chessman.h"
#include "zcomputer.h"
#include <QDebug>

ZChessCraft::ZChessCraft(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ZChessCraft)
{
    ui->setupUi(this);

    setupChessModel();
    setupGraphics();
    setupChessboard();
    setupChessmen();
    setupComputer();
}

ZChessCraft::~ZChessCraft()
{
    delete ui;
    delete chessModel;
    delete board;
    delete computer;
}


void ZChessCraft::setupGraphics()
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(-300, -300, 600, 600);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setBackgroundBrush(QPixmap(":/images/res/stone4.jpg"));
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setGeometry(100, 100, 750, 820);
}

void ZChessCraft::setupChessModel()
{
    chessModel = new ChessModel;
}

void ZChessCraft::setupChessboard()
{
     board = new Chessboard(chessModel);
     scene->addItem(board);
     connect(board, SIGNAL(chessmanMoved(int,int,int)), this, SLOT(moveChessman(int,int,int)));
}

void ZChessCraft::setupChessmen()
{

    for (int player = 0; player < PLAYER_COUNT; player++)
    {
        for (int chessmanIndex = 0; chessmanIndex < MAN_COUNT; chessmanIndex++)
        {
            CHESS* pChessman = chessModel->chessAt(player * MAN_COUNT + chessmanIndex);
            Chessman* chessman = new Chessman(pChessman);
            scene->addItem(chessman);
            connect(chessman, SIGNAL(putChessman(int,int,int)), board, SLOT(putChess(int,int,int)));
            connect(chessman, SIGNAL(clicked(Chessman*)), board, SLOT(showPossibleMoves(Chessman*)));
            chessItems[player * MAN_COUNT + chessmanIndex] = chessman;
        }
    }
    updateChessmen();
}

void ZChessCraft::setupComputer()
{
    computer = new ZComputer(chessModel);
    connect(this, SIGNAL(chessmanMoved(int,int,int)), computer, SLOT(play()));
    connect(computer, SIGNAL(moveCalculated(int,int,int)), this, SLOT(moveChessman(int,int,int)));
}

void ZChessCraft::updateChessmen()
{
    int boardWidth  = (BOARD_COLUMNS - 1) * BOARD_GRID_SIZE;
    int boardHeight = (BOARD_ROWS - 1) * BOARD_GRID_SIZE;
    int boardX      = boardWidth  / 2;
    int boardY      = boardHeight / 2;
    for (int i = 0; i < PLAYER_COUNT * MAN_COUNT; i++)
    {
        Chessman* chessman = chessItems[i];
        if (chessman->isKilled() && !hiddenItems.contains(chessman))
        {
            scene->removeItem(chessman);
            hiddenItems.append(chessman);
            continue;
        }
        int hiddenIndex = hiddenItems.indexOf(chessman);
        if (!chessman->isKilled() && hiddenIndex != -1) // in case the chessman was revived.
        {
            scene->addItem(chessman);
            hiddenItems.removeAt(hiddenIndex);
        }
        QPoint modelPos = chessman->modelPos();
        int x = modelPos.x() * BOARD_GRID_SIZE - boardX;
        int y = modelPos.y() * BOARD_GRID_SIZE - boardY;
        chessman->setPos(x, y);
    }
}

void ZChessCraft::moveChessman(int fromIndex, int toX, int toY)
{
    CHESS* pChess = chessModel->chessAt(fromIndex);
    if (*pChess != INVALID_CHESS && chessModel->canMove(pChess, toX, toY))
    {
        chessModel->move(pChess, toX, toY);
        updateChessmen();
        emit chessmanMoved(fromIndex, toX, toY);
    }
}

void ZChessCraft::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ZChessCraft::on_actionNewGame_triggered()
{
    chessModel->reset();
    updateChessmen();
}

void ZChessCraft::on_actionUndoStep_triggered()
{
    chessModel->backStep(1);
    updateChessmen();
}
