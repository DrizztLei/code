#include <QtWidgets>
#include <QtNetwork>
#include <QUrl>

#include <iostream>

#include "http.h"
#include "ui_authenticationdialog.h"

#ifndef QT_NO_SSL
static const char defaultUrl[] = "https://localhost:8080";
#else
static const char defaultUrl[] = "http://localhost:8080";
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
//HTTP::HTTP(QWidget *parent)
HTTP::HTTP()
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

    // qDebug() << "LOG : HTTP Client init .";

    reply = Q_NULLPTR;
    // file = Q_NULLPTR;

    httpRequestAborted = false;


    connect(&qnam, &QNetworkAccessManager::authenticationRequired,
            this, &HTTP::slotAuthenticationRequired);
#ifndef QT_NO_SSL
    connect(&qnam, &QNetworkAccessManager::sslErrors,
            this, &HTTP::sslErrors);
#endif


    //connect(reply, &QNetworkReply::finished, this, &HTTP::httpFinished);
    //connect(reply, &QIODevice::readyRead, this, &HTTP::httpReadyRead);

    //ProgressDialog *progressDialog = new ProgressDialog(url, this);
    //progressDialog->setAttribute(Qt::WA_DeleteOnClose);
    //connect(progressDialog, &QProgressDialog::canceled, this, &HTTP::cancelDownload);
    //connect(reply, &QNetworkReply::downloadProgress, progressDialog, &ProgressDialog::networkReplyProgress);
    //connect(reply, &QNetworkReply::finished, progressDialog, &ProgressDialog::hide);

    //connect(reply ,&QNetworkReply::downloadProgress , this , &HTTP::slotNetworkReplyProgress);
    //connect(reply, &QNetworkReply::finished , this , &HTTP::slotDownFinish);

    /*
    QFormLayout *formLayout = new QFormLayout;
    urlLineEdit->setClearButtonEnabled(true);
    connect(urlLineEdit, &QLineEdit::textChanged,
            this, &HTTP::enableDownloadButton);
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
    connect(downloadButton, &QAbstractButton::clicked, this, &HTTP::downloadFile);
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

HTTP::HTTP(HTTP&& src) noexcept
{
    this->length = src.length;
    this->commit = src.commit;
    this->flag = src.flag;
    this->httpRequestAborted = src.httpRequestAborted;
    this->post = src.post;
    // this->qnam = src.qnam;
    this->reply = src.reply;
    this->info = src.info;
    this->parameter = src.parameter;
    this->urlInfo = src.urlInfo;
    this->url = src.url;
    this->path = src.path;
    this->fileName = src.fileName;
    this->sql = src.sql;

    reply = Q_NULLPTR;
    // file = Q_NULLPTR;

    httpRequestAborted = false;

    connect(&qnam, &QNetworkAccessManager::authenticationRequired,
            this, &HTTP::slotAuthenticationRequired);
#ifndef QT_NO_SSL
    connect(&qnam, &QNetworkAccessManager::sslErrors,
            this, &HTTP::sslErrors);
#endif
}


void HTTP::startRequest(const QUrl &requestedUrl)
{
    if(isPost())
    {
        url = requestedUrl;
        httpRequestAborted = false;

        QByteArray postData;
        QNetworkRequest request;

        /*
        postData.append("username=elvis");
        postData.append("&passwd=hash");
        postData.append("&client=localhost");
        postData.append("&sql=select * from user");
        */

        postData.append("&sql=" + sql);
        postData.append("&length=" + QString::number(getLength() , 10));
        postData.append("&commit=" + QString(getCommit()?"true":"false"));
        postData.append("&flag=" + QString(getFlag()?"true":"false"));
        postData.append("&transaction=" + QString(getTransaction()?"true":"false"));
        postData.append("&rollback=" + QString(getRollback()?"true":"false"));
        postData.append("&parameter=" + QString(getParameter()));

        request.setUrl(requestedUrl);
        request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

        request.setRawHeader("Accept","text/html, application/xhtml+xml, */*");
        request.setRawHeader("Referer","http://localhost:8080");
        request.setRawHeader("Accept-Language","en-US,*");
        request.setRawHeader("X-Requested-With","XMLHttpRequest");
        request.setRawHeader("User-Agent","Mozilla/5.0");
        request.setRawHeader("Accept-Encoding","gzip,deflate");
        request.setRawHeader("Host","localhost:8080");
        request.setRawHeader("Connection","close"); // "Connection" , "Keey-Alive"
        request.setRawHeader("Cache-Control","no-cache");

        // qDebug() << "LOG : POST DATA : " << postData;

        QByteArray size;
        size.clear();
        size.append(postData.size());

        // request.setRawHeader("Content-Length",size);

        reply = qnam.post(request , postData);

        // connect(reply ,&QNetworkReply::downloadProgress , this , &HTTP::slotNetworkReplyProgress);
        // connect(reply, &QNetworkReply::finished , this , &HTTP::slotDownFinish);

        if(isSync())
        {
            while(!reply->isFinished())
            {
                QApplication::processEvents();
            }

            httpReadyRead();
            httpFinished();
        }
        else
        {
            connect(reply, &QIODevice::readyRead, this, &HTTP::httpReadyRead);
            connect(reply, &QNetworkReply::finished , this , &HTTP::httpFinished);
        }
    }
    else
    {
        url = requestedUrl;
        httpRequestAborted = false;

        reply = qnam.get(QNetworkRequest(url));

        // ProgressDialog *progressDialog = new ProgressDialog(url, this);
        // progressDialog->setAttribute(Qt::WA_DeleteOnClose);
        // connect(progressDialog, &QProgressDialog::canceled, this, &HTTP::cancelDownload);
        // connect(reply, &QNetworkReply::downloadProgress, progressDialog, &ProgressDialog::networkReplyProgress);
        // connect(reply ,&QNetworkReply::downloadProgress , this , &HTTP::slotNetworkReplyProgress);
        // connect(reply, &QNetworkReply::finished, progressDialog, &ProgressDialog::hide);
        // connect(reply, &QNetworkReply::finished , this , &HTTP::slotDownFinish);

        // connect(reply, &QIODevice::readyRead, this, &HTTP::httpReadyRead);
        // connect(reply, &QNetworkReply::finished , this , &HTTP::httpFinished);

        if(isSync())
        {
            while(!reply->isFinished())
            {
                QApplication::processEvents();
            }

            httpReadyRead();
            httpFinished();
        }
        else
        {
            connect(reply, &QIODevice::readyRead, this, &HTTP::httpReadyRead);
            connect(reply, &QNetworkReply::finished , this , &HTTP::httpFinished);
        }

        // progressDialog->show();
        // statusLabel->setText(tr("Downloading %1...").arg(url.toString()));
    }
}

void HTTP::download()
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

    // QString fileName = getFileName();

    /*
    if (fileName.isEmpty())
        fileName = defaultFileLineEdit->text().trimmed();
    */

    /*

    if (fileName.isEmpty())
    {
        fileName = defaultFileName;
    }

    QString downloadDirectory = QDir::cleanPath(getDownloadPath());

    if (!downloadDirectory.isEmpty() && QFileInfo(downloadDirectory).isDir())
    {
        fileName.prepend(downloadDirectory + '/');
    }

    */

    /*

    if (QFile::exists(fileName))
    {


        if (QMessageBox::question(this, tr("Overwrite Existing File"),
                                  tr("There already exists a file called %1 in "
                                     "the current directory. Overwrite?").arg(fileName),
                                  QMessageBox::Yes|QMessageBox::No, QMessageBox::No)
            == QMessageBox::No)
            return;


        qDebug() << "LOG : File exists , remove it .";
        QFile::remove(fileName);
    }
    else
    {
        qDebug() << "LOG : File doesn't exist .";
    }



    // file = openFileForWrite(fileName);

    if (!file)
    {
        return;
    }

    */

    // downloadButton->setEnabled(false);
    // schedule the request

    startRequest(newUrl);

}

QFile *HTTP::openFileForWrite(const QString &fileName)
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

void HTTP::cancelDownload()
{
    // statusLabel->setText(tr("LOG : Download canceled ."));

    httpRequestAborted = true;
    reply->abort();

    // downloadButton->setEnabled(true);
}

void HTTP::httpFinished()
{
    // qDebug() << "LOG : HTTP finished .";
    // qDebug() << "LOG : \n" << this->getInfo() << "\n";
    /*
    QFileInfo fi;
    if (file)
    {
        qDebug() << "ERR : File not exists .";
        fi.setFile(file->fileName());
        file->close();
        delete file;
        file = Q_NULLPTR;
    }
    */

    if (httpRequestAborted)
    {
        qDebug() << "ERR : HTTP request aborted .";
        reply->deleteLater();
        reply = Q_NULLPTR;
        return;
    }

    if (reply->error())
    {
        /*
        statusLabel->setText(tr("Download failed:\n%1.").arg(reply->errorString()));
        downloadButton->setEnabled(true);
        */

        /*
        QFile::remove(fi.absoluteFilePath());
        */

        qDebug() << "ERR : " << reply->errorString() << " .";

        reply->deleteLater();
        reply = Q_NULLPTR;
        return;
    }

    /*

    const QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    reply->deleteLater();
    reply = Q_NULLPTR;

    if (!redirectionTarget.isNull())
    {
        qDebug() << "INFO : Redirection it .";
        const QUrl redirectedUrl = url.resolved(redirectionTarget.toUrl());


        if (QMessageBox::question(this, tr("Redirect"),
                                  tr("Redirect to %1 ?").arg(redirectedUrl.toString()),
                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
            downloadButton->setEnabled(true);
            return;
        }

        file = openFileForWrite(fi.absoluteFilePath());
        if (!file)
        {
            // downloadButton->setEnabled(true);
            qDebug() << "ERR : Unknow err here .";
            return;
        }


        startRequest(redirectedUrl);
        return;
    }

    */

    /*

    using namespace std;
    {
        cout << "LOG : \n" << this->getInfo().toStdString() << endl;
    }

    */

    /*
    statusLabel->setText(tr("Downloaded %1 bytes to %2\nin\n%3")
                         .arg(fi.size()).arg(fi.fileName(), QDir::toNativeSeparators(fi.absolutePath())));
    if (launchCheckBox->isChecked())
        QDesktopServices::openUrl(QUrl::fromLocalFile(fi.absoluteFilePath()));
    downloadButton->setEnabled(true);
    */

    // reply->deleteLater();
    // reply = Q_NULLPTR;

    setFinished(true);

    return;
}

void HTTP::httpReadyRead()
{

    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply

    QByteArray temp;
    /*

    if (file)
    {
        temp = reply->readAll();
        // file->write(reply->readAll());
        file->write(temp);
        info.append(temp);
    }
    else
    {
        qDebug() << "ERR : File not write .";
    }

    */

    temp = reply->readAll();
    // file->write(reply->readAll());
    this->info.append(temp);
}

void HTTP::enableDownloadButton()
{
    downloadButton->setEnabled(!urlLineEdit->text().isEmpty());
}

void HTTP::slotAuthenticationRequired(QNetworkReply*,QAuthenticator *authenticator)
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
void HTTP::sslErrors(QNetworkReply*,const QList<QSslError> &errors)
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

void HTTP::setUrl(QString info)
{
    this->urlInfo = info;
}

QString HTTP::getUrl()
{
    return this->urlInfo;
}

void HTTP::slotNetworkReplyProgress(qint64 receivers, qint64 total)
{
    qDebug() << "LOG : In progressing .";

    /*
    qDebug() << "RECE : " << receivers;
    qDebug() << "TOTAL : " << total;
    */
}

void HTTP::slotDownFinish()
{
    qDebug() << "LOG : Down Finished .";
}

void HTTP::setDownload(QString path)
{
    this->path = path;
}

QString HTTP::getDownload()
{
    return this->path;
}

void HTTP::setFileName(QString fileName)
{
    this->fileName = fileName;
}

QString HTTP::getFileName()
{
    return this->fileName;
}

void HTTP::setIsPost(bool flag)
{
    this->post = flag;
}

bool HTTP::isPost()
{
    return post;
}

void HTTP::postRequest(QString info)
{
    this->setUrl("http://localhost:8080");
    this->setDownload("/home/elvis/trash/");
    this->setFileName("info.sql");
    this->setSQL(info);
    this->setIsPost(true);
    this->setFinished(false);
    this->infoClear();
    this->download();
}

void HTTP::setSQL(QString sql)
{
    this->sql = sql;
}

QString HTTP::getSQL()
{
    return this->sql;
}

QByteArray HTTP::getInfo()
{
    return this->info;
}

void HTTP::infoAppend(QByteArray add)
{
    this->info.append(add);
}

void HTTP::infoClear()
{
    if(&(this->info)!= NULL)
    {
        this->info.clear();
    }
}

void HTTP::setLength(int length)
{
    this->length = length;
}

void HTTP::setCommit(bool commit)
{
    this->commit = commit;
}

void HTTP::addParameter(QString parameter)
{
    this->parameter.append(parameter+"\t");
}

int HTTP::getLength()
{
    return this->length;
}

bool HTTP::getCommit()
{
    return this->commit;
}

QByteArray HTTP::getParameter()
{
    return this->parameter;
}

void HTTP::setFlag(bool flag)
{
    this->flag = flag;
}

bool HTTP::getFlag()
{
    return this->flag;
}

void HTTP::clear()
{
    this->sql.clear();
    this->parameter.clear();
    this->setLength(0);
    this->setFlag(false);
    this->setCommit(false);
    this->setTransaction(false);
    this->setRollback(false);
}

QNetworkReply* HTTP::getReply()
{
    return this->reply;
}

HTTP& HTTP::operator=(HTTP&& src) noexcept
{
    if(this == &src)
    {
        return *this;
    }
    // free old memory .
    this->length = src.length;
    this->commit = src.commit;
    this->flag = src.flag;
    this->httpRequestAborted = src.httpRequestAborted;
    this->post = src.post;
    // this->qnam = src.qnam;
    // QNetworkAccessManager qnam;
    this->reply = src.reply;
    this->info = src.info;
    this->parameter = src.parameter;
    this->urlInfo = src.urlInfo;
    this->url = src.url;
    this->path = src.path;
    this->fileName = src.fileName;
    this->sql = src.sql;

    reply = Q_NULLPTR;
    // file = Q_NULLPTR;

    httpRequestAborted = false;

    connect(&qnam, &QNetworkAccessManager::authenticationRequired,
            this, &HTTP::slotAuthenticationRequired);
#ifndef QT_NO_SSL
    connect(&qnam, &QNetworkAccessManager::sslErrors,
            this, &HTTP::sslErrors);
#endif
}

void HTTP::setFinished(bool finished)
{
    this->finished = finished;
}

bool HTTP::isFinished()
{
    return this->finished;
}

bool HTTP::isSync()
{
    return this->sync;
}

void HTTP::setSync(bool sync)
{
    this->sync = sync;
}

void HTTP::setTransaction(bool transaction)
{
    this->transaction = transaction;
}

bool HTTP::getTransaction()
{
    return this->transaction;
}

void HTTP::setRollback(bool rollback)
{
    this->rollback = rollback;
}

bool HTTP::getRollback()
{
    return this->rollback;
}

void HTTP::addParameter(double value)
{
    this->parameter.append(QString::number(value)+"\t");
}
