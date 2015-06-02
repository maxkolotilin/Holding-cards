#ifndef QCOMPUTERPLAYER_H
#define QCOMPUTERPLAYER_H

#include <QObject>

class QComputerPlayer : public QObject
{
    Q_OBJECT
public:
    explicit QComputerPlayer(QObject *parent = 0);
    ~QComputerPlayer();

signals:

public slots:
};

#endif // QCOMPUTERPLAYER_H
