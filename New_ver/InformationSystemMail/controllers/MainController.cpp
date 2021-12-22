#include "MainController.h"

MainController::MainController(QObject* parent)
    : QObject(parent)
{
}

void MainController::CreateUser(const User& user)
{
    if (!m_db.isOpen()) {
        return;
    }
    m_db.transaction();

    QSqlQuery query;
    query.prepare("insert into t_user values(:login, :id_post, :first_name, :last_name, "
                  ":pathronymic, :dob, :type_account)");

    query.bindValue(":login", user.login);
    if (user.id_post != -1)
        query.bindValue(":id_post", user.id_post);
    query.bindValue(":first_name", user.name.firs_name);
    query.bindValue(":last_name", user.name.last_name);
    query.bindValue(":pathronymic", user.name.pathronymic);
    query.bindValue(":dob", user.DOB);

    QString type_ac = TypeAcToString(user.type_account);

    query.bindValue(":type_account", type_ac);

    if (!query.exec()) {
        emit Error(ErrorType::not_exec_create_user, query.lastError().text());
        m_db.rollback();
        return;
    }

    QSqlQuery query_2;
    query_2.prepare("create user :login identified by :passw ;");
    query_2.bindValue(":login", user.login);
    query_2.bindValue(":passw", user.password);

    if (!query_2.exec()) {
        emit Error(ErrorType::not_exec_create_user, query_2.lastError().text());
        m_db.rollback();
        return;
    }

    QSqlQuery query_3;
    query_3.prepare("grant :type to :login;");
    query_3.bindValue(":type", type_ac);
    query_3.bindValue(":login", user.login);

    if (!query_3.exec()) {
        emit Error(ErrorType::not_exec_create_user, query_3.lastError().text());
        m_db.rollback();
        return;
    }

    QSqlQuery query_4;
    query_4.prepare("set default role all to :login ;");
    query_4.bindValue(":login", user.login);

    if (!query_4.exec()) {
        emit Error(ErrorType::not_exec_create_user, query_4.lastError().text());
        m_db.rollback();
        return;
    }

    m_db.commit();
}

void MainController::FindUser(const User& user)
{
    if (!m_db.isOpen()) {
        return;
    }

    QString where("where");

    bool status_and { true };

    if (!user.login.isEmpty()) {
        if (!status_and) {
            where += " and";
        }
        where += QString(QString(" l_login = ") + "'" + user.login + "'");
        status_and = false;
    }

    if (user.id_post) {
        if (!status_and) {
            where += " and";
        }
        where += QString(QString(" l_id_post = ") + "'" + QString::number(user.id_post) + "'");
        status_and = false;
    }

    if (!user.name.firs_name.isEmpty()) {
        if (!status_and) {
            where += " and";
        }
        where += QString(QString(" l_first_name = ") + "'" + user.name.firs_name + "'");
        status_and = false;
    }

    if (!user.name.last_name.isEmpty()) {
        if (!status_and) {
            where += " and";
        }
        where += QString(QString(" l_last_name = ") + "'" + user.name.last_name + "'");
        status_and = false;
    }

    if (!user.name.pathronymic.isEmpty()) {
        if (!status_and) {
            where += " and";
        }
        where += QString(QString(" l_pathronymic = ") + "'" + user.name.pathronymic + "'");
        status_and = false;
    }

    if (user.type_account != TypeAccount::none) {

        if (!status_and) {
            where += " and";
        }
        where += QString(QString(" l_type_account = ")
            + "'" + TypeAcToString(user.type_account) + "'");
        status_and = false;
    }

    QSqlQuery query;

    if (where.size() > QString("where ").size())
        query.prepare("select * from t_user " + where);
    else
        query.prepare("select * from t_user");

    if (!query.exec()) {
        emit Error(ErrorType::not_exec_find_user, query.lastError().text());
    } else {
        QList<User> users;
        while (query.next()) {
            User new_user;
            new_user.login = query.value(0).toString();

            if (!query.value(1).toString().isEmpty())
                new_user.id_post = query.value(1).toUInt();

            new_user.name.firs_name   = query.value(2).toString();
            new_user.name.last_name   = query.value(3).toString();
            new_user.name.pathronymic = query.value(4).toString();
            new_user.DOB              = query.value(5).toString();
            new_user.type_account     = TypeAcToStruct(query.value(6).toString());

            users.push_back(new_user);
        }
        emit FindUserList(users);
    }
}

void MainController::DeleteUser(const User& user)
{
    if (!m_db.isOpen()) {
        return;
    }

    m_db.transaction();

    QSqlQuery query;

    query.prepare("delete from t_user where l_login = :log ;");
    query.bindValue(":log", QString(user.login));

    if (!query.exec()) {
        emit Error(ErrorType::not_exec_delete_user, query.lastError().text());
        m_db.rollback();
        return;
    }

    QSqlQuery query_1;
    query_1.prepare("drop user :log");
    query_1.bindValue(":log", QString(user.login));

    if (!query_1.exec()) {
        emit Error(ErrorType::not_exec_delete_user, query_1.lastError().text());
        m_db.rollback();
        return;
    }

    m_db.commit();
}

void MainController::CreatePost(const Post& post)
{
    if (!m_db.isOpen()) {
        return;
    }

    QSqlQuery query;

    query.prepare("insert into t_post values(:id, :adr_country, :adr_region, "
                  ":adr_local, :adr_street, :adr_house, :adr_app, :index)");
    query.bindValue(":id", QString::number(post.id_post));
    query.bindValue(":adr_country", post.address.country);
    query.bindValue(":adr_region", post.address.region);
    query.bindValue(":adr_local", post.address.locality);
    query.bindValue(":adr_street", post.address.street);
    query.bindValue(":adr_house", QString::number(post.address.house));
    query.bindValue(":adr_app", QString::number(post.address.apartment));
    query.bindValue(":index", QString::number(post.address.index));

    if (!query.exec()) {
        emit Error(ErrorType::not_exec_create_post, query.lastError().text());
        return;
    }
}

void MainController::FindPost(const Post& post)
{
    if (!m_db.isOpen()) {
        return;
    }

    QString where("where");

    bool status_and { true };

    if (post.id_post > -1) {
        if (!status_and) {
            where += " and";
        }
        where += " l_id_post = " + QString::number(post.id_post);
        status_and = false;
    }

    if (!post.address.country.isEmpty()) {
        if (!status_and) {
            where += " and";
        }
        where += " l_address_country = " + QString("'" + post.address.country + "'");
        status_and = false;
    }

    if (!post.address.region.isEmpty()) {
        if (!status_and) {
            where += " and";
        }
        where += " l_address_region = " + QString("'" + post.address.region + "'");
        status_and = false;
    }

    if (!post.address.locality.isEmpty()) {
        if (!status_and) {
            where += " and";
        }
        where += " l_address_locality = " + QString("'" + post.address.locality + "'");
        status_and = false;
    }

    if (!post.address.street.isEmpty()) {
        if (!status_and) {
            where += " and";
        }
        where += " l_address_street = " + QString("'" + post.address.street + "'");
        status_and = false;
    }

    if (!post.address.house > 0) {
        if (!status_and) {
            where += " and";
        }
        where += " l_address_house = " + QString::number(post.address.house);
        status_and = false;
    }

    if (!post.address.apartment > 0) {
        if (!status_and) {
            where += " and";
        }
        where += " l_address_appartment = " + QString::number(post.address.apartment);
        status_and = false;
    }

    if (!post.address.index > 0) {
        if (!status_and) {
            where += " and";
        }
        where += " l_address_index = " + QString::number(post.address.index);
        status_and = false;
    }

    QSqlQuery query;

    if (where.size() > QString("where ").size())
        query.prepare("select * from t_post " + where);
    else
        query.prepare("select * from t_post");

    if (!query.exec()) {
        emit Error(ErrorType::not_exec_find_post, query.lastError().text());
    } else {
        QList<Post> posts;
        while (query.next()) {
            Post new_post;
            new_post.id_post           = query.value(0).toUInt();
            new_post.address.country   = query.value(1).toString();
            new_post.address.region    = query.value(2).toString();
            new_post.address.locality  = query.value(3).toString();
            new_post.address.street    = query.value(4).toString();
            new_post.address.house     = query.value(5).toUInt();
            new_post.address.apartment = query.value(6).toUInt();
            new_post.address.index     = query.value(7).toUInt();

            posts.push_back(new_post);
        }
        emit FindPostList(posts);
    }
}

void MainController::DeletePost(const Post& post)
{
    if (!m_db.isOpen()) {
        return;
    }

    QSqlQuery query;

    query.prepare("delete from t_post where l_id_post = :id ;");
    query.bindValue(":id", QString::number(post.id_post));

    QSqlQuery query_2;
    auto      res = query_2.prepare("delete from t_user where l_id_post = :id ;");
    query_2.bindValue(":id", QString::number(post.id_post));
    query_2.exec();

    if (!query.exec()) {
        emit Error(ErrorType::not_exec_delete_post, query.lastError().text());
    }
}

void MainController::CreateDeparture(const Departure& dep)
{
    if (!m_db.isOpen()) {
        return;
    }

    QSqlQuery query;

    query.prepare("insert into t_departure values(null, (select l_id_post from t_user where l_login = substring_index(session_user(), '@', 1)), :firs_name_sdrs, :last_name_sdrs, "
                  ":pathronymic_sdrs, :firs_name_rcvr, :last_name_rcvr, :pathronymic_rcvr, :address_country_sdrs, "
                  ":address_region_sdrs, :address_locality_sdrs, :address_street_sdrs, :address_house_sdrs, "
                  ":address_appartment_sdrs, :address_index_sdrs, :address_country_rcvr, :address_region_rcvr, :address_locality_rcvr, "
                  ":address_street_rcvr, :address_house_rcvr, :address_appartment_rcvr, :address_index_rcvr, :type, :weight); call check_t_departure_limit;");

    query.bindValue(":id_departure", (dep.id_departure == -1) ? "null" : QString::number(dep.id_departure));
    query.bindValue(":id_post_standing", (dep.id_post_standing == -1) ? "null" : QString::number(dep.id_post_standing));
    query.bindValue(":firs_name_sdrs", dep.name_sdrs.firs_name);
    query.bindValue(":last_name_sdrs", dep.name_sdrs.last_name);
    query.bindValue(":pathronymic_sdrs", dep.name_sdrs.pathronymic);
    query.bindValue(":firs_name_rcvr", dep.name_rcvr.firs_name);
    query.bindValue(":last_name_rcvr", dep.name_rcvr.last_name);
    query.bindValue(":pathronymic_rcvr", dep.name_rcvr.pathronymic);

    query.bindValue(":address_country_sdrs", dep.address_sdrs.country);
    query.bindValue(":address_region_sdrs", dep.address_sdrs.region);
    query.bindValue(":address_locality_sdrs", dep.address_sdrs.locality);
    query.bindValue(":address_street_sdrs", dep.address_sdrs.street);
    query.bindValue(":address_house_sdrs", (dep.address_sdrs.house == -1) ? "null" : QString::number(dep.address_sdrs.house));
    query.bindValue(":address_appartment_sdrs", (dep.address_sdrs.apartment == -1) ? "null" : QString::number(dep.address_sdrs.apartment));
    query.bindValue(":address_index_sdrs", (dep.address_sdrs.index == -1) ? "null" : QString::number(dep.address_sdrs.index));

    query.bindValue(":address_country_rcvr", dep.address_rcvr.country);
    query.bindValue(":address_region_rcvr", dep.address_rcvr.region);
    query.bindValue(":address_locality_rcvr", dep.address_rcvr.locality);
    query.bindValue(":address_street_rcvr", dep.address_rcvr.street);
    query.bindValue(":address_house_rcvr", (dep.address_rcvr.house == -1) ? "null" : QString::number(dep.address_rcvr.house));
    query.bindValue(":address_appartment_rcvr", (dep.address_rcvr.apartment == -1) ? "null" : QString::number(dep.address_rcvr.apartment));
    query.bindValue(":address_index_rcvr", (dep.address_rcvr.index == -1) ? "null" : QString::number(dep.address_rcvr.index));

    query.bindValue(":type", TypeDepToString(dep.type));
    query.bindValue(":weight", dep.weight_gramm);

    if (!query.exec()) {
        emit Error(ErrorType::not_exec_create_dep, query.lastError().text());
        return;
    }
}

void MainController::FindDeparture(const Departure& dep)
{
    if (!m_db.isOpen()) {
        return;
    }

    if (m_model)
        delete m_model;

    m_model = new QSqlTableModel(this);
    m_model->setTable("t_departure");
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    QString where;

    if (dep.id_departure > -1)
        where += "l_id_departure = " + QString::number(dep.id_departure) + " and ";

    if (dep.id_post_standing > -1)
        where += "l_id_post_standing = " + QString::number(dep.id_post_standing) + " and ";

    if (!dep.name_sdrs.firs_name.isEmpty())
        where += "l_firs_name_sdrs = '" + dep.name_sdrs.firs_name + "'" + " and ";
    if (!dep.name_sdrs.last_name.isEmpty())
        where += "l_last_name_sdrs = '" + dep.name_sdrs.last_name + "'" + " and ";
    if (!dep.name_sdrs.pathronymic.isEmpty())
        where += "l_pathronymic_sdrs = '" + dep.name_sdrs.pathronymic + "'" + " and ";

    if (!dep.name_rcvr.firs_name.isEmpty())
        where += "l_firs_name_rcvr = '" + dep.name_rcvr.firs_name + "'" + " and ";
    if (!dep.name_rcvr.last_name.isEmpty())
        where += "l_last_name_rcvr = '" + dep.name_rcvr.last_name + "'" + " and ";
    if (!dep.name_rcvr.pathronymic.isEmpty())
        where += "l_pathronymic_rcvr = '" + dep.name_rcvr.pathronymic + "'" + " and ";

    if (!dep.address_sdrs.country.isEmpty())
        where += "l_address_country_sdrs = '" + dep.address_sdrs.country + "'" + " and ";
    if (!dep.address_sdrs.region.isEmpty())
        where += "l_address_region_sdrs = '" + dep.address_sdrs.region + "'" + " and ";
    if (!dep.address_sdrs.locality.isEmpty())
        where += "l_address_locality_sdrs = '" + dep.address_sdrs.locality + "'" + " and ";
    if (!dep.address_sdrs.street.isEmpty())
        where += "l_address_street_sdrs = '" + dep.address_sdrs.street + "'" + " and ";
    if (dep.address_sdrs.house > -1)
        where += "l_address_house_sdrs = " + QString::number(dep.address_sdrs.house) + " and ";
    if (dep.address_sdrs.apartment > -1)
        where += "l_address_appartment_sdrs = " + QString::number(dep.address_sdrs.apartment) + " and ";
    if (dep.address_sdrs.index > -1)
        where += "l_address_index_sdrs = " + QString::number(dep.address_sdrs.index) + " and ";

    if (!dep.address_rcvr.country.isEmpty())
        where += "l_address_country_rcvr = '" + dep.address_rcvr.country + "'" + " and ";
    if (!dep.address_rcvr.region.isEmpty())
        where += "l_address_region_rcvr = '" + dep.address_rcvr.region + "'" + " and ";
    if (!dep.address_rcvr.locality.isEmpty())
        where += "l_address_locality_rcvr = '" + dep.address_rcvr.locality + "'" + " and ";
    if (!dep.address_rcvr.street.isEmpty())
        where += "l_address_street_rcvr = '" + dep.address_rcvr.street + "'" + " and ";
    if (dep.address_rcvr.house > -1)
        where += "l_address_house_rcvr = " + QString::number(dep.address_rcvr.house) + " and ";
    if (dep.address_rcvr.apartment > -1)
        where += "l_address_appartment_rcvr = " + QString::number(dep.address_rcvr.apartment) + " and ";
    if (dep.address_rcvr.index > -1)
        where += "l_address_index_rcvr = " + QString::number(dep.address_rcvr.index) + " and ";

    if (dep.type != TypeDeparture::none)
        where += "l_type = '" + TypeDepToString(dep.type) + "'" + " and ";

    if (!where.isEmpty()) {
        where.remove(where.size() - 5, 4);
        m_model->setFilter(where);
    }

    qDebug() << "!Filter: " << m_model->filter();

    m_model->select();

    emit SelectTable(m_model);
}

void MainController::ActionDep(ActionDeparture action, const QList<Departure>& dep)
{
    if (!m_db.isOpen()) {
        return;
    }

    switch (action) {
    case ActionDeparture::delete_dep:
        for (auto i : qAsConst(dep)) {
            QSqlQuery query;
            query.prepare("delete from t_departure where l_id_departure = :id ;");
            query.bindValue(":id", QString::number(i.id_departure));
            if (!query.exec()) {
                emit Error(ErrorType::not_exec_delete_dep, query.lastError().text());
                return;
            }
        }
        break;
    case ActionDeparture::issue_dep:
        for (auto i : qAsConst(dep)) {
            QSqlQuery query;
            query.prepare("insert into t_issued_by values(substring_index(session_user(), '@', 1),  :id_dep, CURRENT_TIMESTAMP());");
            query.bindValue(":id_dep", QString::number(i.id_departure));
            if (!query.exec()) {
                emit Error(ErrorType::not_exec_dep_issued, query.lastError().text());
                return;
            }
        }
        break;
    case ActionDeparture::issue_note:
        for (auto i : qAsConst(dep)) {
            QSqlQuery query;
            query.prepare("insert into t_notice values(substring_index(session_user(), '@', 1),  :id_dep, CURRENT_TIMESTAMP());");
            query.bindValue(":id_dep", QString::number(i.id_departure));
            if (!query.exec()) {
                emit Error(ErrorType::not_exec_dep_issued, query.lastError().text());
                return;
            }
        }
        break;
    case ActionDeparture::recv_dep:
        for (auto i : qAsConst(dep)) {
            m_db.transaction();

            QSqlQuery query_2;
            query_2.prepare("update t_next_destination set l_date_of_receipt = CURRENT_TIMESTAMP() where l_id_departure = :id_dep and l_id_post = (select l_id_post from t_user where l_login = substring_index(session_user(), '@', 1))");
            query_2.bindValue(":id_dep", QString::number(i.id_departure));
            if (!query_2.exec()) {

                emit Error(ErrorType::not_exec_dep_issued, query_2.lastError().text());
                m_db.rollback();
                return;
            }

            QSqlQuery query;
            query.prepare("update t_departure set l_id_post_standing = (select l_id_post from t_user where l_login = substring_index(session_user(), '@', 1)) where l_id_departure = :id_dep");
            query.bindValue(":id_dep", QString::number(i.id_departure));
            if (!query.exec()) {

                emit Error(ErrorType::not_exec_dep_issued, query.lastError().text());
                m_db.rollback();
                return;
            }
            m_db.commit();
        }
        break;
    }
}

void MainController::SendDepNext(int32_t id_post, const QList<Departure>& dep)
{
    if (!m_db.isOpen()) {
        return;
    }

    for (auto i : qAsConst(dep)) {
        QSqlQuery query;
        query.prepare("insert into t_next_destination values(:id_post, :id_dep, CURRENT_TIMESTAMP(), null)");
        query.bindValue(":id_dep", QString::number(i.id_departure));
        query.bindValue(":id_post", QString::number(id_post));
        if (!query.exec()) {

            emit Error(ErrorType::not_exec_dep_issued, query.lastError().text());
            return;
        }
    }
}

void MainController::ViewDeparture(enum TypeViewDep typeView)
{
    if (!m_db.isOpen()) {
        return;
    }

    if (m_model)
        delete m_model;

    m_model = new QSqlTableModel(this);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    switch (typeView) {
    case TypeViewDep::dep_current:
        m_model->setTable("get_current_dep");
        break;
    case TypeViewDep::dep_issue_dep:
        m_model->setTable("get_issue_dep");
        break;
    case TypeViewDep::dep_issue_note:
        m_model->setTable("get_issue_note");
        break;
    case TypeViewDep::dep_recv:
        m_model->setTable("get_recv_dep");
        break;
    case TypeViewDep::dep_send:
        m_model->setTable("get_send_dep");
        break;
    }
    m_model->select();
    emit SelectTable(m_model);
}

void MainController::GetNextDep()
{
    if (!m_db.isOpen()) {
        return;
    }

    QSqlQuery query;

    bool result = query.exec("select t_post.* from t_post cross join t_forward_post on t_post.l_id_post = t_forward_post.l_id_post_whereto where t_forward_post.l_id_post_wherefrom = (select l_id_post from t_user where l_login = substring_index(session_user(), '@', 1));");

    if (!result) {
        emit Error(ErrorType::not_exec_view_forward, query.lastError().text());
    }

    QList<Post> posts;
    while (query.next()) {
        Post new_post;
        new_post.id_post           = query.value(0).toUInt();
        new_post.address.country   = query.value(1).toString();
        new_post.address.region    = query.value(2).toString();
        new_post.address.locality  = query.value(3).toString();
        new_post.address.street    = query.value(4).toString();
        new_post.address.house     = query.value(5).toUInt();
        new_post.address.apartment = query.value(6).toUInt();
        new_post.address.index     = query.value(7).toUInt();

        posts.push_back(new_post);
    }

    emit ViewForwardPost(posts);
}

void MainController::GetFullInfoDeparture(int32_t id_dep)
{
    if (!m_db.isOpen()) {
        return;
    }

    QSqlQuery query;

    query.prepare("select * from t_passed_post cross join t_post on t_passed_post.l_id_post = t_post.l_id_post where t_passed_post.l_id_departure = :id order by t_passed_post.l_serial_number");
    query.bindValue(":id", id_dep);

    if (!query.exec()) {
        emit Error(ErrorType::not_exec_get_full_info_dep, query.lastError().text());
        return;
    }

    QList<AdditInfoDeparture> info;
    while (query.next()) {
        AdditInfoDeparture elem;
        elem.serial_num             = query.value(2).toUInt();
        elem.time                   = query.value(3).toString();
        elem.post.id_post           = query.value(4).toUInt();
        elem.post.address.country   = query.value(5).toString();
        elem.post.address.region    = query.value(6).toString();
        elem.post.address.locality  = query.value(7).toString();
        elem.post.address.street    = query.value(8).toString();
        elem.post.address.house     = query.value(9).toUInt();
        elem.post.address.apartment = query.value(10).toUInt();
        elem.post.address.index     = query.value(11).toUInt();

        info.push_back(elem);
    }
    emit AdditInfoForDeparture(info);
}

void MainController::UpdatePostForForward(const QString& country, const QString& region, const QString& local)
{
    if (!m_db.isOpen()) {
        return;
    }

    QSqlQuery query;

    QString where { " where" };

    if (!country.isEmpty())
        where += " l_address_country = '" + country + "' and";

    if (!region.isEmpty())
        where += " l_address_region = '" + region + "' and";

    if (!local.isEmpty())
        where += " l_address_locality = '" + local + "' and";

    if (where.size() > 7) {
        where.remove(where.size() - 4, 4);

        query.prepare("select * from t_post" + where);
    } else {
        query.prepare("select * from t_post");
    }

    if (!query.exec()) {
        emit Error(ErrorType::not_exec_post_for_forward, query.lastError().text());
        return;
    }

    QList<Post> posts;
    while (query.next()) {
        Post new_post;
        new_post.id_post           = query.value(0).toUInt();
        new_post.address.country   = query.value(1).toString();
        new_post.address.region    = query.value(2).toString();
        new_post.address.locality  = query.value(3).toString();
        new_post.address.street    = query.value(4).toString();
        new_post.address.house     = query.value(5).toUInt();
        new_post.address.apartment = query.value(6).toUInt();
        new_post.address.index     = query.value(7).toUInt();

        posts.push_back(new_post);
    }

    emit ViewPostForForward(posts);
}

void MainController::AddForwardPost(int32_t post)
{
    if (!m_db.isOpen()) {
        return;
    }

    QSqlQuery query;

    query.prepare("insert into t_forward_post values((select l_id_post from t_user where l_login = substring_index(session_user(), '@', 1)), :id)");
    query.bindValue(":id", post);

    if (!query.exec()) {
        emit Error(ErrorType::not_exec_insert_forward, query.lastError().text());
    }
}

void MainController::DeleteForwardPost(const QList<int32_t>& list)
{
    if (!m_db.isOpen()) {
        return;
    }

    for (auto i : qAsConst(list)) {
        QSqlQuery query;

        query.prepare(
            "delete from t_forward_post where l_id_post_wherefrom = (select l_id_post from t_user where l_login = substring_index(session_user(), '@', 1)) and l_id_post_whereto = :id");

        query.bindValue(":id", i);

        if (!query.exec()) {
            emit Error(ErrorType::not_exec_delete_forward, query.lastError().text());
        }
    }
}

void MainController::LogIn(const User& user)
{
    qDebug() << "Connect to BASE\n Login: " << user.login << "   Password: " << user.password
             << " Host: " << m_current_host << " DataBase Name: " << NAME_BD;

    m_db = QSqlDatabase::addDatabase("QMYSQL");

    m_db.setHostName(m_current_host);
    m_db.setDatabaseName(NAME_BD);
    m_db.setUserName(user.login);
    m_db.setPassword(user.password);

    m_db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=2");

    bool result { false };

    if (m_db.isValid())
        result = m_db.open();

    qDebug() << "!Status Connect to Base: " << result;

    QString l_first_name, l_last_name, l_pathronymic, l_type_account;

    if (result) {
        QSqlQuery query;

        if (result = query.exec("call get_name_and_type(@first_name, @last_name, @pathronymic, @type_ac);")) {
            result = query.exec("select @first_name, @last_name, @pathronymic, @type_ac");
            if (result) {
                query.next();
                User new_user             = user;
                new_user.name.firs_name   = query.value(0).toString();
                new_user.name.last_name   = query.value(1).toString();
                new_user.name.pathronymic = query.value(2).toString();
                new_user.type_account     = TypeAcToStruct(query.value(3).toString());

                emit StatusLogIn(new_user, true);
                return;
            }
        }
    }
    emit StatusLogIn(user, false);
}

void MainController::GetPostList()
{
    if (!m_db.isOpen()) {
        return;
    }

    QSqlQueryModel query;

    query.setQuery("select * from t_post");

    QList<Post> list;

    for (int i = 0; i < query.rowCount(); ++i) {
        Post post;
        post.id_post           = query.record(i).value("l_id_post").toInt();
        post.address.country   = query.record(i).value("l_address_country").toString();
        post.address.region    = query.record(i).value("l_address_region").toString();
        post.address.locality  = query.record(i).value("l_address_locality").toString();
        post.address.street    = query.record(i).value("l_address_street").toString();
        post.address.house     = query.record(i).value("l_address_house").toInt();
        post.address.apartment = query.record(i).value("l_address_appartment").toInt();
        post.address.index     = query.record(i).value("l_address_index").toInt();
        list.push_back(post);
    }
    emit PostList(list);
}

void MainController::SetHost(const QString host)
{
    qDebug() << "Set Host: " << host;
    m_current_host = host;
}
