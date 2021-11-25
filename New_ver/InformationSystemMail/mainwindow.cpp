#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_stackWgt(new QStackedWidget(this))
    , m_signIn(new SignIn(this))
    , m_mainController(new MainController(this))
{
    m_stackWgt->addWidget(m_signIn);
    setMinimumSize(500, 300);
    setCentralWidget(m_stackWgt);
}

void MainWindow::UpdateTypeAccount(const TypeAccount type)
{
    if (m_mainWidget)
        return;

    m_mainWidget = new QWidget(this);
    m_tabWidget  = new QTabWidget(m_mainWidget);

    auto widgetLayout = new QGridLayout(m_mainWidget);

    switch (type) {
    case TypeAccount::general_manager:
        break;
    case TypeAccount::administrator:
        break;
    case TypeAccount::contact_operator:
        break;
    case TypeAccount::postman:
        break;
    }
}
