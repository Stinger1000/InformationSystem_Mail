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

    //connect to UI
    connect(m_mainController, &MainController::StatusLogIn, this, &MainWindow::StatusLogIn);

    //

    log          = &log->instance();
    auto current = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
    Logger::instance().setOutputFile(QString("%1.txt").arg(current)); //.hh:mm:ss

    qDebug() << "Start MainWindow";
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
