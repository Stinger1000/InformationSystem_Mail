#include "Logger.h"

#include <QDateTime>
#include <QDir>
#include <QLoggingCategory>
#include <QMessageBox>

QFile         Logger::logFile = QFile();
const QString Logger::path    = "log";
auto          defaultHandler  = qInstallMessageHandler(nullptr);

void Logger::setOutputFile(QString filename)
{
    auto name = QString("%1%2%3").arg(path).arg(QDir::separator()).arg(filename);

    Logger::logFile.setFileName(name);

    if (Logger::logFile.open(QFile::WriteOnly | QFile::Truncate | QFile::Text))
        qInstallMessageHandler(log);
    else
        qWarning("Ошибка создания лог-файла: %s", logFile.errorString().toStdString().c_str());
}

void Logger::log(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    try {
        QString     message;
        QTextStream out(&Logger::logFile);
        out.setCodec("UTF-8");

        out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
        message.append(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz "));

        switch (type) {
        case QtInfoMsg:
            out << "INF ";
            message.append("INF ");
            break;
        case QtDebugMsg:

            if (msg.at(0) == '!') {
                defaultHandler(type, context, msg);
                return;
            }

            out << "DBG ";
            message.append("DBG ");
            break;
        case QtWarningMsg:
            out << "WRN ";
            message.append("WRN ");
            break;
        case QtCriticalMsg:
            out << "CRT ";
            message.append("CRT ");
            break;
        case QtFatalMsg:
            out << "FTL ";
            message.append("FTL ");
            break;
        }

        message.append(": ");
        message.append(msg);

        emit Logger::instance().message(message);

        out
            << QString().asprintf("%s -> %s:%d", context.function, context.file, context.line)
            << ": "
            << msg.toUtf8()
            << Qt::endl;

        out.flush();

    } catch (std::exception& ex) {
        QMessageBox::critical(nullptr, "Ошибка логгирования", QString("%1").arg(ex.what()));
    }
}

Logger::Logger()
    : QObject(nullptr)
{
    const QFileInfo outputDir(path);
    if (!outputDir.exists()) {
        qDebug("mkdir %s", QDir().mkpath(path) ? "ok" : "not ok");
    }
}

Logger::~Logger()
{
    qInstallMessageHandler(nullptr);
}

Logger& Logger::instance()
{
    static auto instance = Logger();

    return instance;
}

void Logger::onError(QString sender, std::exception& ex)
{
    qCritical("%s -> %s", sender.toStdString().c_str(), ex.what());

    //    QMessageBox::warning(nullptr, sender, ex.what());
}
