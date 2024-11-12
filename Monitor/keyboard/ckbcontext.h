#ifndef DISP_INPUT_H
#define DISP_INPUT_H

#include <QObject>
#include <QWidget>
#include "ckeyboard.h"

class CKBContext : public QObject
{
    Q_OBJECT
public:
    CKBContext(QWidget *parent = NULL);
    bool eventFilter(QObject *obj, QEvent *event);
    QString identifierName();
    QString language();

    bool isComposing() const;
    void reset();

private slots:
    void sendCharacter(quint32 character);

private:
    CKeyboard *disp_inputkey;
    void updatePosition();
};



#endif // DISP_INPUT_H

