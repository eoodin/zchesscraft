#ifndef ZCHESSRES_H
#define ZCHESSRES_H

#include <QString>
#include <QFont>

#define FONT_SIZE       (30)
#define GRID_SIZE       (FONT_SIZE << 1)

class ZChessRes
{
public:
    static ZChessRes* instance();
    QString    characters();
    QFont      chessFont();
//    void       save
protected:
    ZChessRes();

private:
    QString chars;
    QFont   font;
    static ZChessRes* inst;
};

#endif // ZCHESSRES_H
