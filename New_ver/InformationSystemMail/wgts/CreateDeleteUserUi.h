#ifndef CREATEDELETEUSERUI_H
#define CREATEDELETEUSERUI_H

#include <QComboBox>
#include <QDate>
#include <QDateEdit>
#include <QDebug>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QMessageBox>
#include <QPushButton>
#include <QSizePolicy>
#include <QSpinBox>
#include <QTableView>
#include <QTimer>
#include <QWidget>

#include "models/BaseModel.h"
#include "models/MainTableModel.h"

namespace {
#define TIME_UPDATE_MS 20000
#define MAX_YEAR       16
}

class CreateDeleteUserUi : public QWidget {
    Q_OBJECT
public:
    explicit CreateDeleteUserUi(QWidget* parent = nullptr);

public slots:
    void ListPost(const QList<Post>& posts);
    void UpdateTable(const QList<User>& ports);

signals:
    void GetListPost();
    void SetCreateUser(const User& user);
    void SetFindUser(const User& user);
    void SetDeleteUser(const User& user);

private:
    void onCreateUser();
    void onFindUser();
    void onDeleteUser();

    QStringList m_headerTable { "Логин", "Отделение", "Имя", "Фамилия", "Отчество", "Дата рождения", "Тип учетной записи" };

    QLineEdit* m_lneFirstName { nullptr };
    QLineEdit* m_lneLastName { nullptr };
    QLineEdit* m_lnePathron { nullptr };

    QDateEdit* m_dteDOB { nullptr };
    QComboBox* m_cbbTypeAc { nullptr };
    QComboBox* m_cbbIdPost { nullptr };

    QLineEdit* m_lneLogin { nullptr };
    QLineEdit* m_lnePassword { nullptr };

    QTableView*     m_tbvMainTable { nullptr };
    MainTableModel* m_tableModel { nullptr };

    QPushButton* m_btnCreate { nullptr };
    QPushButton* m_btnFind { nullptr };
    QPushButton* m_btnDelete { nullptr };
};

#endif // CREATEDELETEUSERUI_H
