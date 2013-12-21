#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QList>
#include <QImage>
#include <QObject>

class Case;

class Player : public QObject
{
    Q_OBJECT

public:
    Player(const QString &name, const QString &imgPath, const QString &imgPathEnlighten, QObject *parent = NULL);
    virtual ~Player();

    inline const QString& name() const { return _name; }
    inline void setName(const QString &name) { _name = name; }

    inline int nbCaseOwn() const { return _cases.size(); }
    inline const QList<const Case*>& caseOwn() const { return _cases; }

    bool addCase(const Case *c);
    bool removeCase(const Case *c);

    inline const QImage& image() const { return _img; }
    inline const QImage& imageEnlighten() const { return _imgEnlighten; }

    inline int pairTaken() const { return _pairTaken; }
    inline void addPairTaken(int nb) { _pairTaken += nb; }
    inline void setPairTaken(int nb) { _pairTaken = nb; }

    void reset();

private:
    QString _name;
    QList<const Case*> _cases;
    QImage _img;
    QImage _imgEnlighten;
    int _pairTaken;

signals:
    void movePlayed(int x, int y);
};

#endif // PLAYER_H
