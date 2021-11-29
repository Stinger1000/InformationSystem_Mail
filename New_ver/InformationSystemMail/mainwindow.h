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

#include "wgts/SignIn.h"

#include "utils/Logger.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;

public slots:
    void StatusLogIn(const User& user, bool status);

private:
    QStackedWidget* m_stackWgt { nullptr };
    SignIn*         m_signIn { nullptr };

    QTabWidget* m_tabWidget { nullptr };
    QWidget*    m_mainWidget { nullptr };

    //controller
    MainController* m_mainController { nullptr };
    //

    Logger* log { nullptr };
};
#endif // MAINWINDOW_H
