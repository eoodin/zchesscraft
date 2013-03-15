#include <QFile>

#include "zchessres.h"



ZChessRes* ZChessRes::inst = 0;

ZChessRes::ZChessRes()
{
    QFile charsFile(":/text/res/chars.ansi");
    charsFile.open(QIODevice::ReadOnly | QIODevice::Text);
    chars = QString::fromLocal8Bit(charsFile.readLine(128));
    charsFile.close();

    font = QFont("Œ¢»ÌºÚ¡• È", FONT_SIZE, QFont::Normal);
}

ZChessRes* ZChessRes::instance()
{
    if (inst == 0)
    {
        inst = new ZChessRes;
    }
    return inst;
}

QString ZChessRes::characters()
{
    return chars;
}

QFont ZChessRes::chessFont()
{
    return font;
}
