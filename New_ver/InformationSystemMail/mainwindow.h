#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QGridLayout>
#include <QMainWindow>
#include <QMessageBox>
#include <QStackedWidget>
#include <QTabWidget>
#include <QTime>
#include <QVector>

#include "controllers/MainController.h"

#include "models/BaseModel.h"

#include "wgts/CreateDeletePostUi.h"
#include "wgts/CreateDeleteUserUi.h"
#include "wgts/CreateForwardPostUi.h"
#include "wgts/DepartureUi.h"
#include "wgts/SignInUi.h"

#include "utils/Logger.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;

public slots:
    void StatusLogIn(const User& user, bool status);
    void PrintError(ErrorType error, const QString& text);

private:
    void UpdateWidgetGeneralManager(QTabWidget& tab_widget);
    void UpdateWidgetAdministrator(QTabWidget& tab_widget);
    void UpdateWidgetContactOperator(QTabWidget& tab_widget);
    void UpdateWidgetPostMan(QTabWidget& tab_widget);

    QStackedWidget* m_stackWgt { nullptr };
    SignInUi*       m_signIn { nullptr };

    QTabWidget* m_tabWidget { nullptr };
    QWidget*    m_wgtGlobal { nullptr };

    //controller
    MainController* m_mainController { nullptr };
    //

    Logger* log { nullptr };
};
#endif // MAINWINDOW_H
