#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QMainWindow>
#include <QStackedWidget>
#include <QTabWidget>
#include <QVector>

#include "controllers/MainController.h"

#include "models/BaseModel.h"

#include "wgts/SignIn.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;

public slots:
    void UpdateTypeAccount(const TypeAccount type);

private:
    QStackedWidget* m_stackWgt { nullptr };
    SignIn*         m_signIn { nullptr };

    QTabWidget* m_tabWidget { nullptr };
    QWidget*    m_mainWidget { nullptr };

    //controller
    MainController* m_mainController { nullptr };
};
#endif // MAINWINDOW_H
