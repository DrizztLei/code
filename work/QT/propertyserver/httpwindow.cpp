#include <QtWidgets>
#include <QtNetwork>
#include <QUrl>

#include <iostream>

#include "httpwindow.h"
#include "ui_authenticationdialog.h"

#ifndef QT_NO_SSL
static const char defaultUrl[] = "https://www.baidu.com/";
#else
static const char defaultUrl[] = "http://www.baidu.com/";
#endif
static const char defaultFileName[] = "index.html";

/*
ProgressDialog::ProgressDialog(const QUrl &url, QWidget *parent)
  : QProgressDialog(parent)
{
    qDebug() << "DIALOG";
    setWindowTitle(tr("Download Progress"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setLabelText(tr("Downloading %1.").arg(url.toDisplayString()));
    setMinimum(0);
    setValue(0);
    setMinimumDuration(0);
}

void ProgressDialog::networkReplyProgress(qint64 bytesRead, qint64 totalBytes)
{
    qDebug() << "NETWORK REPLY PROGRESS";
    setMaximum(totalBytes);
    setValue(bytesRead);
}
*/
//HttpWindow::HttpWindow(QWidget *parent)
HttpWindow::HttpWindow()
/*
    : QDialog(parent)
    , statusLabel(new QLabel(tr("Please enter the URL of a file you want to download.\n\n"), this))
    , urlLineEdit(new QLineEdit(defaultUrl))
    , downloadButton(new QPushButton(tr("Download")))
    , launchCheckBox(new QCheckBox("Launch file"))
    , defaultFileLineEdit(new QLineEdit(defaultFileName))
    , downloadDirectoryLineEdit(new QLineEdit)
    , reply(Q_NULLPTR)
    , file(Q_NULLPTR)
    , httpRequestAborted(false)
*/
{
    //setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    //setWindowTitle(tr("HTTP"));

    qDebug() << "LOG : HTTP Client init .";

    reply = Q_NULLPTR;
    file = Q_NULLPTR;

    httpRequestAborted = false;
    connect(&qnam, &QNetworkAccessManager::authenticationRequired,
            this, &HttpWindow::slotAuthenticationRequired);
#ifndef QT_NO_SSL
    connect(&qnam, &QNetworkAccessManager::sslErrors,
            this, &HttpWindow::sslErrors);
#endif

    //connect(reply, &QNetworkReply::finished, this, &HttpWindow::httpFinished);
    //connect(reply, &QIODevice::readyRead, this, &HttpWindow::httpReadyRead);

    //ProgressDialog *progressDialog = new ProgressDialog(url, this);
    //progressDialog->setAttribute(Qt::WA_DeleteOnClose);
    //connect(progressDialog, &QProgressDialog::canceled, this, &HttpWindow::cancelDownload);
    //connect(reply, &QNetworkReply::downloadProgress, progressDialog, &ProgressDialog::networkReplyProgress);
    //connect(reply, &QNetworkReply::finished, progressDialog, &ProgressDialog::hide);

    //connect(reply ,&QNetworkReply::downloadProgress , this , &HttpWindow::slotNetworkReplyProgress);
    //connect(reply, &QNetworkReply::finished , this , &HttpWindow::slotDownFinish);

    /*
    QFormLayout *formLayout = new QFormLayout;
    urlLineEdit->setClearButtonEnabled(true);
    connect(urlLineEdit, &QLineEdit::textChanged,
            this, &HttpWindow::enableDownloadButton);
    formLayout->addRow(tr("&URL:"), urlLineEdit);
    QString downloadDirectory = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    if (downloadDirectory.isEmpty() || !QFileInfo(downloadDirectory).isDir())
        downloadDirectory = QDir::currentPath();
    downloadDirectoryLineEdit->setText(QDir::toNativeSeparators(downloadDirectory));
    formLayout->addRow(tr("&Download directory:"), downloadDirectoryLineEdit);
    formLayout->addRow(tr("Default &file:"), defaultFileLineEdit);
    launchCheckBox->setChecked(true);
    formLayout->addRow(launchCheckBox);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);

    mainLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));

    statusLabel->setWordWrap(true);
    mainLayout->addWidget(statusLabel);

    downloadButton->setDefault(true);
    connect(downloadButton, &QAbstractButton::clicked, this, &HttpWindow::downloadFile);
    QPushButton *quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);
    connect(quitButton, &QAbstractButton::clicked, this, &QWidget::close);
    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->addButton(downloadButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);
    mainLayout->addWidget(buttonBox);
    urlLineEdit->setFocus();
    */

}

void HttpWindow::startRequest(const QUrl &requestedUrl)
{
    if(isPost())
    {
        url = requestedUrl;
        httpRequestAborted = false;

        QByteArray postData;
        QNetworkRequest request;

        postData.append("username=elvis");
        postData.append("&passwd=hash");
        postData.append("&client=localhost");
        postData.append("&sql=select * from user");

        QByteArray size;
        size.append(postData.size());

        request.setUrl(requestedUrl);
        request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
        request.setRawHeader("Accept","text/html, application/xhtml+xml, */*");
        request.setRawHeader("Referer","http://localhost:8080");
        request.setRawHeader("Accept-Language","en-US,*");
        request.setRawHeader("X-Requested-With","XMLHttpRequest");
        request.setRawHeader("User-Agent","Mozilla/5.0");
        request.setRawHeader("Accept-Encoding","gzip,deflate");
        request.setRawHeader("Host","localhost:8080");

        request.setRawHeader("Content-Length",size);
        request.setRawHeader("Connection","Keep-Alive");
        request.setRawHeader("Cache-Control","no-cache");

        reply = qnam.post(request , postData);

        //connect(reply ,&QNetworkReply::downloadProgress , this , &HttpWindow::slotNetworkReplyProgress);
        //connect(reply, &QNetworkReply::finished , this , &HttpWindow::slotDownFinish);

        connect(reply, &QIODevice::readyRead, this, &HttpWindow::httpReadyRead);
        connect(reply, &QNetworkReply::finished , this , &HttpWindow::httpFinished);
        connect(reply ,&QNetworkReply::downloadProgress , this , &HttpWindow::slotNetworkReplyProgress);

    }
    else
    {
        url = requestedUrl;
        httpRequestAborted = false;

        reply = qnam.get(QNetworkRequest(url));

        connect(reply, &QIODevice::readyRead, this, &HttpWindow::httpReadyRead);

        //ProgressDialog *progressDialog = new ProgressDialog(url, this);
        //progressDialog->setAttribute(Qt::WA_DeleteOnClose);
        //connect(progressDialog, &QProgressDialog::canceled, this, &HttpWindow::cancelDownload);
        //connect(reply, &QNetworkReply::downloadProgress, progressDialog, &ProgressDialog::networkReplyProgress);

        connect(reply ,&QNetworkReply::downloadProgress , this , &HttpWindow::slotNetworkReplyProgress);

        //connect(reply, &QNetworkReply::finished, progressDialog, &ProgressDialog::hide);
        //connect(reply, &QNetworkReply::finished , this , &HttpWindow::slotDownFinish);

        connect(reply, &QNetworkReply::finished , this , &HttpWindow::httpFinished);

        //progressDialog->show();
        //statusLabel->setText(tr("Downloading %1...").arg(url.toString()));
    }
}

void HttpWindow::downloadFile()
{
    const QString urlSpec = getUrl();
    if (urlSpec.isEmpty())
    {
        return;
    }
    const QUrl newUrl = QUrl::fromUserInput(urlSpec);
    if (!newUrl.isValid())
    {
        qDebug() << "ERR : Error for url invalid .";
        return;
    }

    QString fileName = getFileName();

    /*
    if (fileName.isEmpty())
        fileName = defaultFileLineEdit->text().trimmed();
    */

    if (fileName.isEmpty())
    {
        fileName = defaultFileName;
    }

    QString downloadDirectory = QDir::cleanPath(getDownloadPath());

    if (!downloadDirectory.isEmpty() && QFileInfo(downloadDirectory).isDir())
    {
        fileName.prepend(downloadDirectory + '/');
    }

    if (QFile::exists(fileName))
    {

        /*
        if (QMessageBox::question(this, tr("Overwrite Existing File"),
                                  tr("There already exists a file called %1 in "
                                     "the current directory. Overwrite?").arg(fileName),
                                  QMessageBox::Yes|QMessageBox::No, QMessageBox::No)
            == QMessageBox::No)
            return;
        */

        qDebug() << "LOG : File exists , remove it .";
        QFile::remove(fileName);
    }
    else
    {
        qDebug() << "LOG : File doesn't exist .";
    }

    file = openFileForWrite(fileName);

    if (!file)
    {
        return;
    }

    //downloadButton->setEnabled(false);
    // schedule the request

    startRequest(newUrl);

}

QFile *HttpWindow::openFileForWrite(const QString &fileName)
{
    QScopedPointer<QFile> file(new QFile(fileName));

    if (!file->open(QIODevice::WriteOnly))
    {
        /*
        QMessageBox::information(this, tr("Error"),
                                 tr("Unable to save the file %1: %2.")
                                 .arg(QDir::toNativeSeparators(fileName),
                                  file->errorString()));
        */
        qDebug() << "ERR : File not writeonly .";
        return Q_NULLPTR;
    }
    return file.take();
}

void HttpWindow::cancelDownload()
{
    statusLabel->setText(tr("LOG : Download canceled ."));
    httpRequestAborted = true;
    reply->abort();
    downloadButton->setEnabled(true);
}

void HttpWindow::httpFinished()
{
    qDebug() << "LOG : HTTP finished .";
    QFileInfo fi;
    if (file)
    {
        qDebug() << "ERR : File not exists .";
        fi.setFile(file->fileName());
        file->close();
        delete file;
        file = Q_NULLPTR;
    }

    if (httpRequestAborted)
    {
        qDebug() << "ERR : HTTP request aborted .";
        reply->deleteLater();
        reply = Q_NULLPTR;
        return;
    }

    if (reply->error()) {
        /*
        statusLabel->setText(tr("Download failed:\n%1.").arg(reply->errorString()));
        downloadButton->setEnabled(true);
        */
        using namespace  std;
        QFile::remove(fi.absoluteFilePath());
        string errInfo = "ERR : Error in reply finished . " + reply->errorString().toStdString() + " .";
        cout << errInfo << endl;
        reply->deleteLater();
        reply = Q_NULLPTR;
        return;
    }

    const QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    reply->deleteLater();
    reply = Q_NULLPTR;

    if (!redirectionTarget.isNull())
    {
        qDebug() << "INFO : Redirection it .";
        const QUrl redirectedUrl = url.resolved(redirectionTarget.toUrl());
        /*
        if (QMessageBox::question(this, tr("Redirect"),
                                  tr("Redirect to %1 ?").arg(redirectedUrl.toString()),
                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
            downloadButton->setEnabled(true);
            return;
        }
        */
        file = openFileForWrite(fi.absoluteFilePath());
        if (!file)
        {
            downloadButton->setEnabled(true);
            return;
        }
        startRequest(redirectedUrl);
        return;
    }

    /*
    statusLabel->setText(tr("Downloaded %1 bytes to %2\nin\n%3")
                         .arg(fi.size()).arg(fi.fileName(), QDir::toNativeSeparators(fi.absolutePath())));
    if (launchCheckBox->isChecked())
        QDesktopServices::openUrl(QUrl::fromLocalFile(fi.absoluteFilePath()));
    downloadButton->setEnabled(true);
    */
}

void HttpWindow::httpReadyRead()
{
    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
    if (file)
    {
        file->write(reply->readAll());
    }
    else
    {
        qDebug() << "ERR : File not write .";
    }
}

void HttpWindow::enableDownloadButton()
{
    downloadButton->setEnabled(!urlLineEdit->text().isEmpty());
}

void HttpWindow::slotAuthenticationRequired(QNetworkReply*,QAuthenticator *authenticator)
{
    /*
    QDialog authenticationDialog;
    Ui::Dialog ui;
    ui.setupUi(&authenticationDialog);
    authenticationDialog.adjustSize();
    ui.siteDescription->setText(tr("%1 at %2").arg(authenticator->realm(), url.host()));

    // Did the URL have information? Fill the UI
    // This is only relevant if the URL-supplied credentials were wrong
    ui.userEdit->setText(url.userName());
    ui.passwordEdit->setText(url.password());

    if (authenticationDialog.exec() == QDialog::Accepted) {
        authenticator->setUser(ui.userEdit->text());
        authenticator->setPassword(ui.passwordEdit->text());
    }
    */
    qDebug() << "LOG : Need authenticator .";
    authenticator->setUser("elvis");
    authenticator->setPassword("Idon'tknow");
}

#ifndef QT_NO_SSL
void HttpWindow::sslErrors(QNetworkReply*,const QList<QSslError> &errors)
{
    QString errorString;
    foreach (const QSslError &error, errors)
    {
        if (!errorString.isEmpty())
            errorString += '\n';
        errorString += error.errorString();
    }
    /*
    if (QMessageBox::warning(this, tr("SSL Errors"),
                             tr("One or more SSL errors has occurred:\n%1").arg(errorString),
                             QMessageBox::Ignore | QMessageBox::Abort) == QMessageBox::Ignore)
    {
        reply->ignoreSslErrors();
    }
    */
    qDebug() << "ERR : SSL error : " << errorString << " .";
}
#endif

void HttpWindow::setUrl(QString info)
{
    this->urlInfo = info;
}

QString HttpWindow::getUrl()
{
    return this->urlInfo;
}

void HttpWindow::slotNetworkReplyProgress(qint64 receivers, qint64 total)
{
    qDebug() << "LOG : In progressing .";
    /*
    qDebug() << "RECE : " << receivers;
    qDebug() << "TOTAL : " << total;
    */
}

void HttpWindow::slotDownFinish()
{
    qDebug() << "LOG : Down Finished .";
}

void HttpWindow::setDownloadPath(QString path)
{
    this->path = path;
}

QString HttpWindow::getDownloadPath()
{
    return this->path;
}

void HttpWindow::setFileName(QString fileName)
{
    this->fileName = fileName;
}

QString HttpWindow::getFileName()
{
    return this->fileName;
}

void HttpWindow::setIsPost(bool flag)
{
    this->post = flag;
}

bool HttpWindow::isPost()
{
    return post;
}

void HttpWindow::start()
{
    this->setUrl("http://localhost:8080");
    this->setDownloadPath("/home/elvis/trash/");
    this->setFileName("test.html");
    this->setIsPost(true);
    downloadFile();
}
