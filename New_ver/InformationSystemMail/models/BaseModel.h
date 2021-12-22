#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <QString>

const QString NAME_BD { "sysmail" };
const QString name_code_string_password("InfSysMail");

enum class TypeViewDep {
    dep_current,
    dep_recv,
    dep_send,
    dep_issue_dep,
    dep_issue_note,
};

enum class ActionDeparture {
    delete_dep,
    recv_dep,
    issue_note,
    issue_dep,
};

enum class TypeAccount {
    general_manager,
    administrator,
    contact_operator,
    postman,
    none,
};

enum class ErrorType {
    not_exec_logIn,
    not_exec_create_user,
    not_exec_find_user,
    not_exec_delete_user,
    not_exec_create_post,
    not_exec_find_post,
    not_exec_delete_post,
    not_exec_create_dep,
    not_exec_delete_dep,
    not_exec_find_dep,
    not_exec_dep_issued,
    not_exec_view_dep,
    not_exec_view_forward,
    not_exec_insert_forward,
    not_exec_delete_forward,
    not_exec_post_for_forward,
    not_exec_get_full_info_dep,
};

enum class TypeDeparture {
    letter,
    parcel_post,
    package,
    none,
};

enum class EmployeeStatus {
    worked,
    fired,
};

struct FullName {
    QString firs_name;
    QString last_name;
    QString pathronymic;
};

struct FullAddress {
    QString country;
    QString region;
    QString locality;
    QString street;
    int64_t house { -1 };
    int64_t apartment { -1 };
    int64_t index { -1 };
};

struct User {
    QString        login;
    int            id_post { -1 };
    QString        password;
    FullName       name;
    QString        DOB;
    TypeAccount    type_account;
    EmployeeStatus emp_status { EmployeeStatus::worked };
};

struct Departure {
    int64_t       id_departure { -1 };
    int64_t       id_post_next_destination { -1 };
    int64_t       id_post_standing { -1 };
    FullName      name_sdrs;
    FullName      name_rcvr;
    FullAddress   address_sdrs;
    FullAddress   address_rcvr;
    TypeDeparture type;
    int64_t       weight_gramm { -1 };
};

struct Post {
    int64_t     id_post { -1 };
    FullAddress address;
};

struct AdditInfoDeparture {
    int32_t serial_num;
    Post    post;
    QString time;
};

//CONVERT
static QString TypeAcToString(TypeAccount type)
{
    QString type_ac;
    if (type == TypeAccount::general_manager)
        type_ac = "general_manager";
    else if (type == TypeAccount::administrator)
        type_ac = "administrator";
    else if (type == TypeAccount::contact_operator)
        type_ac = "postal_operator";
    else if (type == TypeAccount::postman)
        type_ac = "postman";

    return type_ac;
}

static TypeAccount TypeAcToStruct(const QString& type)
{
    TypeAccount type_ac = TypeAccount::none;

    if (type == "general_manager")
        type_ac = TypeAccount::general_manager;
    else if (type == "administrator")
        type_ac = TypeAccount::administrator;
    else if (type == "postal_operator")
        type_ac = TypeAccount::contact_operator;
    else if (type == "postman")
        type_ac = TypeAccount::postman;

    return type_ac;
}

static QString TypeDepToString(TypeDeparture type)
{
    QString type_ac;
    if (type == TypeDeparture::letter)
        type_ac = "letter";
    else if (type == TypeDeparture::package)
        type_ac = "package";
    else if (type == TypeDeparture::parcel_post)
        type_ac = "parcel_post";

    return type_ac;
}

static TypeDeparture TypeDepToStruct(const QString& type)
{
    TypeDeparture type_ac = TypeDeparture::none;

    if (type == "letter")
        type_ac = TypeDeparture::letter;
    else if (type == "parcel_post")
        type_ac = TypeDeparture::parcel_post;
    else if (type == "package")
        type_ac = TypeDeparture::package;

    return type_ac;
}

#endif // BASEMODEL_H
