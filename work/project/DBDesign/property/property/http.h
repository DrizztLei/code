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
    //explicit HTTP(QWidget *parent = Q_NULLPTR);
    explicit HTTP();

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
    void addParameter(QString parameter);
    void setCommit(bool commit);
    void clear();

    int getLength();
    QByteArray getParameter();
    bool getCommit();

    QByteArray getInfo();
    QString getDownload();
    QString getUrl();
    QString getFileName();
    QString getSQL();
    bool getFlag();
    bool isPost();
    QNetworkReply* getReply();

private slots:
    void download();
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
    bool commit = false;
    bool flag; // flag for the get the info of if exec() succeed .
    bool httpRequestAborted;
    bool post;
};

#endif // HTTP_H
