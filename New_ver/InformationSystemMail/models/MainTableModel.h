#ifndef MAINTABLEMODEL_H
#define MAINTABLEMODEL_H

#include <QAbstractTableModel>
#include <QApplication>
#include <QDesktopWidget>
#include <QStringList>

namespace {
#define WIDTH_MULT  0.7
#define HEIGHT_MULT 0.6

//OTHER
uint32_t getSizeScreenWidth()
{
    QRect rec = QApplication::desktop()->screenGeometry();
    return rec.width();
}

uint32_t getSizeScreenHeight()
{
    QRect rec = QApplication::desktop()->screenGeometry();
    return rec.height();
}

}

class MainTableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    MainTableModel(const QStringList& model, QObject* parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation,
        int role = Qt::DisplayRole) const override;

    bool setHeaderData(int section, Qt::Orientation orientation,
        const QVariant& value, int role = Qt::EditRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(
        const QModelIndex& index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex& index, const QVariant& value,
        int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void SetRowSelect(const QModelIndex& index);

    // Add data:
    bool insertRows(
        int row, int count, const QModelIndex& parent = QModelIndex()) override;
    bool insertColumns(
        int column, int count, const QModelIndex& parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(
        int row, int count, const QModelIndex& parent = QModelIndex()) override;
    bool removeColumns(
        int column, int count, const QModelIndex& parent = QModelIndex()) override;

    //OTHER
    QStringList getSelectedItem();

private:
    QStringList        header;
    QList<QStringList> model_data;
    int                m_selectedItem { -1 };
};

#endif // MainTableModel_H
