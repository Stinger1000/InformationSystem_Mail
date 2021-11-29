#ifndef SIGNIN_H
#define SIGNIN_H

#include "models/BaseModel.h"

#include <QWidget>

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMenuBar>
#include <QPushButton>
#include <QRegExpValidator>

class SignIn : public QWidget {
    Q_OBJECT
public:
    explicit SignIn(QWidget* parent = nullptr);

signals:
    void SetHost(const QString& ip);
    void LogIn(const User& user);

private:
    QPushButton* m_btnSignIn { nullptr };
    QLineEdit*   m_lneLogin { nullptr };
    QLineEdit*   m_lnePassword { nullptr };

    QWidget*   m_setHost { nullptr };
    QLineEdit* m_lneHost { nullptr };
};

#endif // SIGNIN_H
