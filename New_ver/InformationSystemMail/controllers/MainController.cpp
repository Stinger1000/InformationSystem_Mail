#include "MainController.h"

MainController::MainController(QObject* parent)
    : QObject(parent)
{
}

void MainController::LogIn(const User& user)
{
    m_db = QSqlDatabase::addDatabase("QMYSQL");

    m_db.setHostName(m_current_host);
    m_db.setDatabaseName(NAME_BD);
    m_db.setUserName(user.login);
    m_db.setPassword(user.password);

    m_db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=2");

    bool result { false };

    if (m_db.isValid())
        result = m_db.open();

    if (result) {
        //TODO:
    } else {
        emit StatusLogIn(user, result);
    }
}

void MainController::SetHost(const QString host)
{
    m_current_host = host;
}
