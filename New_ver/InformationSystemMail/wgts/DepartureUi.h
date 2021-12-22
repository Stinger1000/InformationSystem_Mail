#ifndef DEPARTUREUI_H
#define DEPARTUREUI_H

#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSqlTableModel>
#include <QTableView>
#include <QTextEdit>
#include <QWidget>

#include "models/BaseModel.h"
#include "models/MainTableModel.h"

class DepartureUi : public QWidget {
    Q_OBJECT
public:
    explicit DepartureUi(QWidget* parent = nullptr);
    ~DepartureUi();

    void UpdateTable(QSqlTableModel* model);

    void ViewForwardPost(const QList<Post>& list);

    void ViewFullInfoDep(const QList<AdditInfoDeparture>& info);

signals:
    void CreateDeparture(const Departure& dep);
    void FindDeparture(const Departure& dep);

    void Action(ActionDeparture action, const QList<Departure>& dep);
    void ActionSendNextDep(int post, const QList<Departure>& dep);

    void GetNextDeparture();

    void GetFullInfoDep(int32_t dep);

    void ViewDep(TypeViewDep type);

private:
    QWidget*         m_wgtSelectPost { nullptr };
    QList<Departure> m_lastDeparture;
    QComboBox*       m_cbbSendNextDep { nullptr };

    void onCreateDeparture();
    void onFindDeparture();
    void onDeleteDeparture();
    void onSendNextDeparture();
    void onRecvDeparture();
    void onIssueNote();
    void onIssueDep();
    void onViewInfoDep();

    void onView();

    QLabel* m_lblIdDep { nullptr };
    QLabel* m_lblIdPostSt { nullptr };
    QLabel* m_lblFirstNameSdrs { nullptr };
    QLabel* m_lblLastNameSdrs { nullptr };
    QLabel* m_lblPathronymicSdrs { nullptr };
    QLabel* m_lblFirstNameRcvr { nullptr };
    QLabel* m_lblLastNameRcvr { nullptr };
    QLabel* m_lblPathronymicRcvr { nullptr };
    QLabel* m_lblAddressCountrySdrs { nullptr };
    QLabel* m_lblAddressRegionSdrs { nullptr };
    QLabel* m_lblAddressLocalitySdrs { nullptr };
    QLabel* m_lblAddressStreetSdrs { nullptr };
    QLabel* m_lblAddressHouseSdrs { nullptr };
    QLabel* m_lblAddressAppartmentSdrs { nullptr };
    QLabel* m_lblAddressIndexSdrs { nullptr };
    QLabel* m_lblAddressCountryRcvr { nullptr };
    QLabel* m_lblAddressRegionRcvr { nullptr };
    QLabel* m_lblAddressLocalityRcvr { nullptr };
    QLabel* m_lblAddressStreetRcvr { nullptr };
    QLabel* m_lblAddressHouseRcvr { nullptr };
    QLabel* m_lblAddressAppartmentRcvr { nullptr };
    QLabel* m_lblAddressIndexRcvr { nullptr };
    QLabel* m_lblType { nullptr };
    QLabel* m_lblWeight { nullptr };

    QLineEdit* m_lneIdDep { nullptr };
    QLineEdit* m_lneIdPostSt { nullptr };
    QLineEdit* m_lneFirstNameSdrs { nullptr };
    QLineEdit* m_lneLastNameSdrs { nullptr };
    QLineEdit* m_lnePathronymicSdrs { nullptr };
    QLineEdit* m_lneFirstNameRcvr { nullptr };
    QLineEdit* m_lneLastNameRcvr { nullptr };
    QLineEdit* m_lnePathronymicRcvr { nullptr };
    QLineEdit* m_lneAddressCountrySdrs { nullptr };
    QLineEdit* m_lneAddressRegionSdrs { nullptr };
    QLineEdit* m_lneAddressLocalitySdrs { nullptr };
    QLineEdit* m_lneAddressStreetSdrs { nullptr };
    QLineEdit* m_lneAddressHouseSdrs { nullptr };
    QLineEdit* m_lneAddressAppartmentSdrs { nullptr };
    QLineEdit* m_lneAddressIndexSdrs { nullptr };
    QLineEdit* m_lneAddressCountryRcvr { nullptr };
    QLineEdit* m_lneAddressRegionRcvr { nullptr };
    QLineEdit* m_lneAddressLocalityRcvr { nullptr };
    QLineEdit* m_lneAddressStreetRcvr { nullptr };
    QLineEdit* m_lneAddressHouseRcvr { nullptr };
    QLineEdit* m_lneAddressAppartmentRcvr { nullptr };
    QLineEdit* m_lneAddressIndexRcvr { nullptr };
    QComboBox* m_cbbType { nullptr };
    QLineEdit* m_lneWeight { nullptr };

    QPushButton* m_btnCreate { nullptr };
    QPushButton* m_btnFind { nullptr };

    QPushButton* m_btnDelete { nullptr };
    QPushButton* m_btnSendNext { nullptr };
    QPushButton* m_btnRecvDep { nullptr };
    QPushButton* m_btnIssueNotice { nullptr };
    QPushButton* m_btnIssueDep { nullptr };
    QPushButton* m_btnViewInfoDep { nullptr };

    QPushButton* m_btnView { nullptr };
    QComboBox*   m_cbbTypeView { nullptr };

    QCheckBox* m_chbIdDep { nullptr };
    QCheckBox* m_chbIdPostSt { nullptr };
    QCheckBox* m_chbFirstNameSdrs { nullptr };
    QCheckBox* m_chbLastNameSdrs { nullptr };
    QCheckBox* m_chbPathronymicSdrs { nullptr };
    QCheckBox* m_chbFirstNameRcvr { nullptr };
    QCheckBox* m_chbLastNameRcvr { nullptr };
    QCheckBox* m_chbPathronymicRcvr { nullptr };
    QCheckBox* m_chbAddressCountrySdrs { nullptr };
    QCheckBox* m_chbAddressRegionSdrs { nullptr };
    QCheckBox* m_chbAddressLocalitySdrs { nullptr };
    QCheckBox* m_chbAddressStreetSdrs { nullptr };
    QCheckBox* m_chbAddressHouseSdrs { nullptr };
    QCheckBox* m_chbAddressAppartmentSdrs { nullptr };
    QCheckBox* m_chbAddressIndexSdrs { nullptr };
    QCheckBox* m_chbAddressCountryRcvr { nullptr };
    QCheckBox* m_chbAddressRegionRcvr { nullptr };
    QCheckBox* m_chbAddressLocalityRcvr { nullptr };
    QCheckBox* m_chbAddressStreetRcvr { nullptr };
    QCheckBox* m_chbAddressHouseRcvr { nullptr };
    QCheckBox* m_chbAddressAppartmentRcvr { nullptr };
    QCheckBox* m_chbAddressIndexRcvr { nullptr };
    QCheckBox* m_chbType { nullptr };
    QCheckBox* m_chbWeight { nullptr };

    QTableView*     m_tbvMainTable { nullptr };
    QSqlTableModel* m_tbmMainTable { nullptr };

    QTextEdit* m_txeInfoDep { nullptr };
};

#endif // DEPARTUREUI_H
