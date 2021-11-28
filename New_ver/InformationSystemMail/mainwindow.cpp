#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_stackWgt(new QStackedWidget(this))
    , m_signIn(new SignIn(this))
    , m_mainController(new MainController(this))
{
    m_stackWgt->addWidget(m_signIn);
    setMinimumSize(500, 300);
    setCentralWidget(m_stackWgt);

    //connects TO CONTROLLER
    connect(m_signIn, &SignIn::SetHost, m_mainController, &MainController::SetHost);
    connect(m_signIn, &SignIn::LogIn, m_mainController, &MainController::LogIn);

    //

    setWindowTitle("Информационная система 'Почта'");
}

void MainWindow::StatusLogIn(const User& user, bool status)
{
    if (m_mainWidget)
        return;

    if ((!status) || (user.type_account == TypeAccount::none)) {
        QMessageBox::critical(nullptr, "Ошибка входа", "Проверьте правильность данных.");
        return;
    }

    m_mainWidget = new QWidget(this);
    m_tabWidget  = new QTabWidget(m_mainWidget);

    auto widgetLayout
        = new QGridLayout(m_mainWidget);

    switch (user.type_account) {
    case TypeAccount::general_manager:
        break;
    case TypeAccount::administrator:
        break;
    case TypeAccount::contact_operator:
        break;
    case TypeAccount::postman:
        break;

    default:
        break;
    }
}
