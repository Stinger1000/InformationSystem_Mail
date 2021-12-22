#ifndef CREATEFORWARDPOSTUI_H
#define CREATEFORWARDPOSTUI_H

#include "models/BaseModel.h"
#include "models/MainTableModel.h"
#include <QComboBox>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include <QWidget>

class CreateForwardPostUi : public QWidget {
    Q_OBJECT
public:
    explicit CreateForwardPostUi(QWidget* parent = nullptr);
    void ViewForward(const QList<Post>& model);
    void PostForForward(const QList<Post>& model);

signals:
    void AddForwardPost(int32_t post);
    void DeleteForwardPost(const QList<int32_t>& list);
    void GetCurrentForward();
    void UpdatePostForForward(const QString& country, const QString& region, const QString& local);

private:
    QStringList m_headerTable { "ID", "Адрес(страна)", "Адрес(регион)", "Адрес(населенный пункт)", "Адрес(улица)", "Адрес(дом)", "Адрес(квартира)", "Индекс" };

    QComboBox*      m_cbbPost { nullptr };
    QTableView*     m_tbvCurrentForwardPost { nullptr };
    MainTableModel* m_tbmCurrent { nullptr };
    QPushButton*    m_btnInsertPost { nullptr };
    QPushButton*    m_btnDeleteSelectPost { nullptr };
    QPushButton*    m_btnUpdate { nullptr };
    QLineEdit*      m_lneFilterCountry { nullptr };
    QLineEdit*      m_lneFilterRegion { nullptr };
    QLineEdit*      m_lneFilterLocal { nullptr };

    void onInsertPost();
    void onDeletePost();
    void onUpdate();
};

#endif // CREATEFORWARDPOSTUI_H
