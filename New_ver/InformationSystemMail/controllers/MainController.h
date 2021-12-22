#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QDebug>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlTableModel>

#include "models/BaseModel.h"

class MainController : public QObject {
    Q_OBJECT
public:
    explicit MainController(QObject* parent = nullptr);

public slots:
    //actions //--FROM UI--//
    //    void CreateNewDep();
    void CreateUser(const User& user);
    void FindUser(const User& user);
    void DeleteUser(const User& user);

    void CreatePost(const Post& post);
    void FindPost(const Post& post);
    void DeletePost(const Post& post);

    void CreateDeparture(const Departure& dep);
    void FindDeparture(const Departure& dep);

    void ActionDep(ActionDeparture action, const QList<Departure>& dep);

    void SendDepNext(int32_t id_dep, const QList<Departure>& dep);

    void ViewDeparture(enum TypeViewDep typeView);

    void GetNextDep();

    void GetFullInfoDeparture(int32_t id_dep);

    void UpdatePostForForward(const QString& country, const QString& region, const QString& local);

    void AddForwardPost(int32_t post);
    void DeleteForwardPost(const QList<int32_t>& list);

    void LogIn(const User& user);
    void GetPostList();
    //--

    void SetHost(const QString host);

signals:
    //ANSWER //--TO UI--//
    void StatusLogIn(const User& user, bool status);
    void PostList(const QList<Post>& list);
    void FindUserList(const QList<User>& users);
    void FindPostList(const QList<Post>& posts);

    void SelectTable(QSqlTableModel* model);

    void ViewPostForForward(const QList<Post>& list);

    void ViewForwardPost(const QList<Post>& list);

    void AdditInfoForDeparture(const QList<AdditInfoDeparture>& info);

    void Error(ErrorType error, const QString& text);

private:
    QSqlDatabase m_db;
    bool         m_status_connect { false };
    QString      m_current_host { "localhost" };

    QSqlTableModel* m_model { nullptr };
};

#endif // MAINCONTROLLER_H
