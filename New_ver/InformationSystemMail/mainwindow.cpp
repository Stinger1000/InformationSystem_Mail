#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_stackWgt(new QStackedWidget(this))
    , m_signIn(new SignInUi(this))
    , m_mainController(new MainController(this))
{
    m_stackWgt->addWidget(m_signIn);
    setMinimumSize(500, 300);
    setCentralWidget(m_stackWgt);

    //connects TO CONTROLLER
    connect(m_signIn, &SignInUi::SetHost, m_mainController, &MainController::SetHost);
    connect(m_signIn, &SignInUi::LogIn, m_mainController, &MainController::LogIn);

    //

    //connect to UI
    connect(m_mainController, &MainController::StatusLogIn, this, &MainWindow::StatusLogIn);
    connect(m_mainController, &MainController::Error, this, &MainWindow::PrintError);
    //

    log          = &log->instance();
    auto current = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
    Logger::instance().setOutputFile(QString("%1.txt").arg(current)); //.hh:mm:ss

    qDebug() << "Start MainWindow";
    setWindowTitle("Информационная система 'Почта'");

    emit m_signIn->AutoLogin();
}

void MainWindow::StatusLogIn(const User& user, bool status)
{
    if ((!status) || (user.type_account == TypeAccount::none)) {
        QMessageBox::critical(nullptr, "Ошибка входа", "Проверьте правильность данных.");
        return;
    }

    window()->resize(getSizeScreenWidth() * 0.95, getSizeScreenHeight() * 0.8);
    window()->move(QApplication::desktop()->screen()->rect().center() - window()->rect().center());

    m_wgtGlobal       = new QWidget(this);
    auto layoutGlobal = new QGridLayout(m_wgtGlobal);

    m_wgtGlobal->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_tabWidget = new QTabWidget(m_wgtGlobal);

    layoutGlobal->addWidget(m_tabWidget);

    m_stackWgt->addWidget(m_wgtGlobal);

    m_stackWgt->setCurrentIndex(1);

    switch (user.type_account) {
    case TypeAccount::general_manager:
        UpdateWidgetGeneralManager(*m_tabWidget);
        break;
    case TypeAccount::administrator:
        UpdateWidgetAdministrator(*m_tabWidget);
        break;
    case TypeAccount::contact_operator:
        UpdateWidgetContactOperator(*m_tabWidget);
        break;
    case TypeAccount::postman:
        UpdateWidgetPostMan(*m_tabWidget);
        break;

    default:
        break;
    }
}

void MainWindow::PrintError(ErrorType error, const QString& text)
{
    QMessageBox::critical(nullptr, "Ошибка",
        "Последняя команда не выполнена, проверьте правильность данных\n КОД ОШИБКИ: "
            + QString::number(uint8_t(error)));

    qDebug() << "!Error Num " << int(error) << " " << text;
}

void MainWindow::UpdateWidgetGeneralManager(QTabWidget& tab_widget)
{

    //CREATE_USER
    auto create_user = new CreateDeleteUserUi(&tab_widget);
    connect(create_user, &CreateDeleteUserUi::GetListPost, m_mainController, &MainController::GetPostList);
    connect(m_mainController, &MainController::PostList, create_user, &CreateDeleteUserUi::ListPost);
    connect(m_mainController, &MainController::FindUserList, create_user, &CreateDeleteUserUi::UpdateTable);
    connect(create_user, &CreateDeleteUserUi::SetFindUser, m_mainController, &MainController::FindUser);
    connect(create_user, &CreateDeleteUserUi::SetDeleteUser, m_mainController, &MainController::DeleteUser);
    connect(create_user, &CreateDeleteUserUi::SetCreateUser, m_mainController, &MainController::CreateUser);
    emit create_user->GetListPost();
    //

    //CREATE POST
    auto create_post = new CreateDeletePostUi(&tab_widget);
    connect(create_post, &CreateDeletePostUi::SetFindPost, m_mainController, &MainController::FindPost);
    connect(create_post, &CreateDeletePostUi::SetDeletePost, m_mainController, &MainController::DeletePost);
    connect(create_post, &CreateDeletePostUi::SetCreatePost, m_mainController, &MainController::CreatePost);
    connect(m_mainController, &MainController::FindPostList, create_post, &CreateDeletePostUi::UpdateTable);
    //

    tab_widget.addTab(create_user, "Создать и удалить пользователя");
    tab_widget.addTab(create_post, "Создать и удалить отделение");
}

void MainWindow::UpdateWidgetAdministrator(QTabWidget& tab_widget)
{
    //CREATE_USER
    auto create_user = new CreateDeleteUserUi(&tab_widget);
    connect(create_user, &CreateDeleteUserUi::GetListPost, m_mainController, &MainController::GetPostList);
    connect(m_mainController, &MainController::PostList, create_user, &CreateDeleteUserUi::ListPost);
    connect(m_mainController, &MainController::FindUserList, create_user, &CreateDeleteUserUi::UpdateTable);
    connect(create_user, &CreateDeleteUserUi::SetFindUser, m_mainController, &MainController::FindUser);
    connect(create_user, &CreateDeleteUserUi::SetDeleteUser, m_mainController, &MainController::DeleteUser);
    connect(create_user, &CreateDeleteUserUi::SetCreateUser, m_mainController, &MainController::CreateUser);
    emit create_user->GetListPost();
    //

    //CREATE_FORWARD_POST
    auto forward_post = new CreateForwardPostUi(&tab_widget);
    connect(forward_post, &CreateForwardPostUi::AddForwardPost, m_mainController, &MainController::AddForwardPost);
    connect(forward_post, &CreateForwardPostUi::DeleteForwardPost, m_mainController, &MainController::DeleteForwardPost);
    connect(forward_post, &CreateForwardPostUi::GetCurrentForward, m_mainController, &MainController::GetNextDep);
    connect(forward_post, &CreateForwardPostUi::UpdatePostForForward, m_mainController, &MainController::UpdatePostForForward);

    connect(m_mainController, &MainController::ViewForwardPost, forward_post, &CreateForwardPostUi::ViewForward);
    connect(m_mainController, &MainController::ViewPostForForward, forward_post, &CreateForwardPostUi::PostForForward);
    //

    tab_widget.addTab(create_user, "Создать и удалить пользователя");
    tab_widget.addTab(forward_post, "Управление пунктами пересылки");
}

void MainWindow::UpdateWidgetContactOperator(QTabWidget& tab_widget)
{
    auto departure_wgt = new DepartureUi(&tab_widget);
    connect(m_mainController, &MainController::SelectTable, departure_wgt, &DepartureUi::UpdateTable);
    connect(m_mainController, &MainController::ViewForwardPost, departure_wgt, &DepartureUi::ViewForwardPost);
    connect(m_mainController, &MainController::AdditInfoForDeparture, departure_wgt, &DepartureUi::ViewFullInfoDep);
    connect(departure_wgt, &DepartureUi::CreateDeparture, m_mainController, &MainController::CreateDeparture);
    connect(departure_wgt, &DepartureUi::FindDeparture, m_mainController, &MainController::FindDeparture);
    connect(departure_wgt, &DepartureUi::Action, m_mainController, &MainController::ActionDep);
    connect(departure_wgt, &DepartureUi::ActionSendNextDep, m_mainController, &MainController::SendDepNext);
    connect(departure_wgt, &DepartureUi::GetNextDeparture, m_mainController, &MainController::GetNextDep);
    connect(departure_wgt, &DepartureUi::GetFullInfoDep, m_mainController, &MainController::GetFullInfoDeparture);
    connect(departure_wgt, &DepartureUi::ViewDep, m_mainController, &MainController::ViewDeparture);
    tab_widget.addTab(departure_wgt, "Работа с отправлениями");
}

void MainWindow::UpdateWidgetPostMan(QTabWidget& tab_widget)
{
    auto departure_wgt = new DepartureUi(&tab_widget);
    connect(m_mainController, &MainController::SelectTable, departure_wgt, &DepartureUi::UpdateTable);
    connect(m_mainController, &MainController::ViewForwardPost, departure_wgt, &DepartureUi::ViewForwardPost);
    connect(m_mainController, &MainController::AdditInfoForDeparture, departure_wgt, &DepartureUi::ViewFullInfoDep);
    connect(departure_wgt, &DepartureUi::CreateDeparture, m_mainController, &MainController::CreateDeparture);
    connect(departure_wgt, &DepartureUi::FindDeparture, m_mainController, &MainController::FindDeparture);
    connect(departure_wgt, &DepartureUi::Action, m_mainController, &MainController::ActionDep);
    connect(departure_wgt, &DepartureUi::ActionSendNextDep, m_mainController, &MainController::SendDepNext);
    connect(departure_wgt, &DepartureUi::GetNextDeparture, m_mainController, &MainController::GetNextDep);
    connect(departure_wgt, &DepartureUi::GetFullInfoDep, m_mainController, &MainController::GetFullInfoDeparture);
    connect(departure_wgt, &DepartureUi::ViewDep, m_mainController, &MainController::ViewDeparture);
    tab_widget.addTab(departure_wgt, "Работа с отправлениями");
}
