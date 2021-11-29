#ifndef LOGGER_H
#define LOGGER_H

#include <QFile>
#include <QObject>

class Logger : public QObject {
    Q_OBJECT
public:
    static QFile         logFile;
    const static QString path;

private:
    explicit Logger();
    Logger(Logger const&) = delete;

    ~Logger();

    Logger& operator=(Logger const&) = delete;

public:
    static Logger& instance();

    void setOutputFile(QString filename);

private:
    static void log(QtMsgType type, const QMessageLogContext& context, const QString& msg);

signals:
    void message(const QString& message);

public slots:
    void onError(QString sender, std::exception& ex);
};

#endif // LOGGER_H
