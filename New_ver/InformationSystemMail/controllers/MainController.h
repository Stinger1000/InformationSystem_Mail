#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>

class MainController : public QObject {
    Q_OBJECT
public:
    explicit MainController(QObject* parent = nullptr);

    //actions
    void CreateNewDep();
    void AddAdminToDep();
    void RemoveAdminFromDep();
    void RemoveDep();
    void AddTelecomOperPostman();
    void RemoveTelecomOperPostman();
    void AddForwardPoints();
    void RemoveForwardPoints();
    void IssueShip();
    void SendShipToNextPoint();
    void ViewListShipInDep();
    void ViewShipInfo();
    void AcceptShip();
    void DeliverNotice();
    void AcceptShipFromDep();
    void LogIn();
    //

signals:

private:
};

#endif // MAINCONTROLLER_H
