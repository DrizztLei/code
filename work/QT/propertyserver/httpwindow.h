
#ifndef HTTPWINDOW_H
#define HTTPWINDOW_H

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
//class HttpWindow : public QDialog
class HttpWindow : public QObject
{
    Q_OBJECT

public:
    //explicit HttpWindow(QWidget *parent = Q_NULLPTR);
    explicit HttpWindow();
    void startRequest(const QUrl &requestedUrl);
    void start();
    void setUrl(QString info);
    void setDownloadPath(QString path);
    void setFileName(QString fileName);
    void setIsPost(bool flag);

    QString getDownloadPath();
    QString getUrl();
    QString getFileName();
    bool isPost();

private slots:
    void downloadFile();
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

    bool httpRequestAborted;
    bool post ;
};

#endif
