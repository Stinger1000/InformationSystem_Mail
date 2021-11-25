#include "SignIn.h"

SignIn::SignIn(QWidget* parent)
    : QWidget(parent)
    , m_btnSignIn(new QPushButton("Войти в систему", this))
    , m_lneLogin { new QLineEdit(this) }
    , m_lnePassword { new QLineEdit(this) }
{
    auto layout       = new QGridLayout(this);
    auto widget       = new QWidget(this);
    auto widgetLayout = new QGridLayout(widget);

    widgetLayout->setMargin(0);

    auto lblLogin = new QLabel("Логин: ", this);
    auto lblPass  = new QLabel("Пароль: ", this);

    widgetLayout->addWidget(lblLogin, 0, 0);
    widgetLayout->addWidget(lblPass, 1, 0);
    widgetLayout->addWidget(m_lneLogin, 0, 1);
    widgetLayout->addWidget(m_lnePassword, 1, 1);
    widgetLayout->addWidget(m_btnSignIn, 2, 0, 1, 2);

    layout->addItem(new QSpacerItem(30, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 0, 0, 3, 1);
    layout->addItem(new QSpacerItem(0, 10, QSizePolicy::Expanding, QSizePolicy::Expanding), 0, 1, 1, 1);
    layout->addItem(new QSpacerItem(30, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 0, 2, 3, 1);
    layout->addWidget(widget, 1, 1, 1, 1);
    layout->addItem(new QSpacerItem(0, 10, QSizePolicy::Expanding, QSizePolicy::Expanding), 2, 1, 1, 1);
}
