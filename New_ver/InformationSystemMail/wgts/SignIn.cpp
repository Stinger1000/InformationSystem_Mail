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

    auto menu = new QMenuBar(this);

    auto set_host_widget    = new QWidget(this, Qt::Window);
    auto host_widget_layout = new QGridLayout(set_host_widget);
    auto label_set_ip       = new QLabel("IP адрес:", set_host_widget);
    m_lneHost               = new QLineEdit(set_host_widget);
    auto btn_set_host       = new QPushButton("Применить", set_host_widget);
    host_widget_layout->addWidget(label_set_ip, 0, 0);
    host_widget_layout->addWidget(m_lneHost, 0, 1);
    host_widget_layout->addWidget(btn_set_host, 1, 0, 2, 1);

    menu->addAction("Настройки сервера", set_host_widget, &QWidget::show);
    layout->setMenuBar(menu);

    set_host_widget->setWindowTitle("Настройки сервера");

    //set_validator
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp ipRegex("^" + ipRange
        + "\\." + ipRange
        + "\\." + ipRange
        + "\\." + ipRange + "$");
    auto    ipValidator = new QRegExpValidator(ipRegex, this);
    m_lneHost->setValidator(ipValidator);
    //

    connect(btn_set_host, &QPushButton::clicked, this, [&]() { emit SetHost(m_lneHost->text()); });
    connect(m_btnSignIn, &QPushButton::clicked, this, [&]() {
        User user;
        user.login = m_lneLogin->text();
        user.password = m_lnePassword->text();
        emit LogIn(user); });
}
