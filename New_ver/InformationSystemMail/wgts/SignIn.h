#ifndef SIGNIN_H
#define SIGNIN_H

#include <QWidget>

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class SignIn : public QWidget {
    Q_OBJECT
public:
    explicit SignIn(QWidget* parent = nullptr);

signals:

private:
    QPushButton* m_btnSignIn { nullptr };
    QLineEdit*   m_lneLogin { nullptr };
    QLineEdit*   m_lnePassword { nullptr };
};

#endif // SIGNIN_H
