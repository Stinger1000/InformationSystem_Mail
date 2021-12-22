#ifndef CREATEDELETEPOSTUI_H
#define CREATEDELETEPOSTUI_H

#include "models/BaseModel.h"
#include "models/MainTableModel.h"

#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QTableWidget>
#include <QWidget>

class CreateDeletePostUi : public QWidget {
    Q_OBJECT
public:
    explicit CreateDeletePostUi(QWidget* parent = nullptr);

    void UpdateTable(const QList<Post>& post);

signals:
    void SetCreatePost(const Post& post);
    void SetFindPost(const Post& post);
    void SetDeletePost(const Post& post);

private:
    void onCreatePost();
    void onFindPost();
    void onDeletePost();

    QStringList m_headerTable { "ID", "Адрес(страна)", "Адрес(регион)", "Адрес(населенный пункт)", "Адрес(улица)", "Адрес(дом)", "Адрес(квартира)", "Индекс" };

    QLabel* m_lblID { nullptr };
    QLabel* m_lblAddressCountry { nullptr };
    QLabel* m_lblAddressRegion { nullptr };
    QLabel* m_lblAddressLocal { nullptr };
    QLabel* m_lblAddressStreet { nullptr };
    QLabel* m_lblAddressHouse { nullptr };
    QLabel* m_lblAddressAppartment { nullptr };
    QLabel* m_lblIndex { nullptr };

    QLineEdit* m_lneID { nullptr };
    QLineEdit* m_lneAddressCountry { nullptr };
    QLineEdit* m_lneAddressRegion { nullptr };
    QLineEdit* m_lneAddressLocal { nullptr };
    QLineEdit* m_lneAddressStreet { nullptr };
    QLineEdit* m_lneAddressHouse { nullptr };
    QLineEdit* m_lneAddressAppartment { nullptr };
    QLineEdit* m_lneIndex { nullptr };

    QPushButton* m_btnCreate { nullptr };
    QPushButton* m_btnFind { nullptr };
    QPushButton* m_btnDelete { nullptr };

    QTableView*     m_tbvMainTable { nullptr };
    MainTableModel* m_tableModel { nullptr };
};

#endif // CREATEDELETEPOSTUI_H
