#ifndef HTTP_H
#define HTTP_H

#include <QProgressDialog>
#include <QNetworkAccessManager>
#include <QUrl>
#include <stdlib.h>

class QFile;
class QLabel;
class QLineEdit;
class QPushButton;
class QSslError;
class QAuthenticator;
class QNetworkReply;
class QCheckBox;

/*
class ProgressDialog : public QProgressDialog {
    Q_OBJECT
public:
    explicit ProgressDialog(const QUrl &url, QWidget *parent = Q_NULLPTR);
public slots:
   void networkReplyProgress(qint64 bytesRead, qint64 totalBytes);
};
*/

class HTTP : public QObject
{
    Q_OBJECT

public:
    // explicit HTTP(QWidget *parent = Q_NULLPTR);
    // explicit HTTP();
    HTTP();
    HTTP(HTTP&& src) noexcept;
    HTTP& operator=(HTTP&& src) noexcept;

    void startRequest(const QUrl &requestedUrl);
    void postRequest(QString info);
    void setUrl(QString info);
    void setDownload(QString path);
    void setFileName(QString fileName);
    void setIsPost(bool flag);
    void setSQL(QString sql);
    void infoAppend(QByteArray add);
    void infoClear();
    void setFlag(bool flag);
    void setLength(int length);
    void setTransaction(bool transaction);
    void setRollback(bool rollback);
    void addParameter(QString parameter);
    void addParameter(double value);
    void setCommit(bool commit);
    void clear();
    bool isFinished();
    void setFinished(bool finished);
    void setSync(bool sync);

    int getLength();
    bool getCommit();
    bool getFlag();
    bool getTransaction();
    bool getRollback();
    bool isPost();
    bool isSync();

    QByteArray getParameter();
    QByteArray getInfo();
    QString getDownload();
    QString getUrl();
    QString getFileName();
    QString getSQL();
    QNetworkReply* getReply();

public slots:
    void download();
private slots:
    void cancelDownload();
    void httpFinished();
    void httpReadyRead();
    void enableDownloadButton();
    void slotAuthenticationRequired(QNetworkReply*,QAuthenticator *);
    void slotNetworkReplyProgress(qint64 receivers , qint64 total);
    void slotDownFinish();

#ifndef QT_NO_SSL
    void sslErrors(QNetworkReply*,const QList<QSslError> &errors);
#endif

private:
    QFile *openFileForWrite(const QString &fileName);
    QString urlInfo;
    QString path;
    QString fileName;
    QString sql;

    QLabel *statusLabel;
    QLineEdit *urlLineEdit;
    QPushButton *downloadButton;
    QCheckBox *launchCheckBox;
    QLineEdit *defaultFileLineEdit;
    QLineEdit *downloadDirectoryLineEdit;

    QUrl url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    QFile *file;
    QByteArray info;
    QByteArray parameter;

    int length = 0;
    bool commit = false , transaction = false , rollback = false , flag = false , sync = false;
    bool httpRequestAborted;
    bool post = true;
    bool finished = false;
};

#endif // HTTP_H
