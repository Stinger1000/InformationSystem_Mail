#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QDebug>
#include <QObject>
#include <QSqlDatabase>

#include "models/BaseModel.h"

class MainController : public QObject {
    Q_OBJECT
public:
    explicit MainController(QObject* parent = nullptr);

public slots:
    //actions //--FROM UI--//
    //    void CreateNewDep();
    //    void AddAdminToDep();
    //    void RemoveAdminFromDep();
    //    void RemoveDep();
    //    void AddTelecomOperPostman();
    //    void RemoveTelecomOperPostman();
    //    void AddForwardPoints();
    //    void RemoveForwardPoints();
    //    void IssueShip();
    //    void SendShipToNextPoint();
    //    void ViewListShipInDep();
    //    void ViewShipInfo();
    //    void AcceptShip();
    //    void DeliverNotice();
    //    void AcceptShipFromDep();
    void LogIn(const User& user);
    //--

    void SetHost(const QString host);

signals:
    //ANSWER //--TO UI--//
    void StatusLogIn(const User& user, bool status);

private:
    QSqlDatabase m_db;
    bool         m_status_connect { false };
    QString      m_current_host { "localhost" };
};

#endif // MAINCONTROLLER_H
