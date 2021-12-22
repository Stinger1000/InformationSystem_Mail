#ifndef SIGNINUI_H
#define SIGNINUI_H

#include "models/BaseModel.h"

#include "utils/Configs.h"

#include <QWidget>

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMenuBar>
#include <QPushButton>
#include <QRegExpValidator>

class SignInUi : public QWidget {
    Q_OBJECT
public:
    explicit SignInUi(QWidget* parent = nullptr);

signals:
    void SetHost(const QString& ip);
    void LogIn(const User& user);

    void AutoLogin();

private:
    void LoadConfig();
    void WriteConfig();

    QPushButton* m_btnSignIn { nullptr };
    QLineEdit*   m_lneLogin { nullptr };
    QLineEdit*   m_lnePassword { nullptr };

    QWidget*   m_setHost { nullptr };
    QLineEdit* m_lneHost { nullptr };
};

#endif // SIGNINUI_H
