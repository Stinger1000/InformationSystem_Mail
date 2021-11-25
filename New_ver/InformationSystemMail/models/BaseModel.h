#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <QString>

enum class TypeAccount {
    general_manager,
    administrator,
    contact_operator,
    postman,
    none,
};

enum class TypeDeparture {
    letter,
    parcel_post,
    package,
};

struct FullName {
    QString firs_name;
    QString last_name;
    QString pathronymic;
};

struct FullAddress {
    QString  country;
    QString  region;
    QString  locality;
    QString  street;
    uint64_t house;
    uint64_t apartment;
    uint64_t index;
};

struct User {
    QString     login;
    uint64_t    id_post { 0 };
    QString     password;
    FullName    name;
    QString     DOB;
    TypeAccount type_account;
};

struct Departure {
    uint64_t      id_departure { 0 };
    uint64_t      id_post_next_destination { 0 };
    uint64_t      id_post_standing { 0 };
    FullName      name_sdrs;
    FullName      name_rcvr;
    FullAddress   address_sdrs;
    FullAddress   address_rcvr;
    TypeDeparture type;
    uint64_t      weight_gramm;
};

struct Post {
    uint64_t    id_post;
    FullAddress address;
};

#endif // BASEMODEL_H
