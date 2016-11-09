#include "http.h"

#ifndef QT_NO_SSL
static const char defaultUrl[] = "https://localhost:8080";
#else
static const char defaultUrl[] = "http://localhost:8080";
#endif
static const char defaultFileName[] = "index.html";


HTTP::HTTP()

{

    reply = Q_NULLPTR;

    httpRequestAborted = false;


    connect(&qnam, &QNetworkAccessManager::authenticationRequired,
            this, &HTTP::slotAuthenticationRequired);
#ifndef QT_NO_SSL
    connect(&qnam, &QNetworkAccessManager::sslErrors,
            this, &HTTP::sslErrors);
#endif


}

HTTP::HTTP(HTTP&& src) noexcept
{
    this->length = src.length;
    this->commit = src.commit;
    this->flag = src.flag;
    this->httpRequestAborted = src.httpRequestAborted;
    this->post = src.post;
    this->reply = src.reply;
    this->info = src.info;
    this->parameter = src.parameter;
    this->urlInfo = src.urlInfo;
    this->url = src.url;
    this->path = src.path;
    this->fileName = src.fileName;
    this->sql = src.sql;

    reply = Q_NULLPTR;

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

        QNetworkRequest request;

        request.setUrl(requestedUrl);
        request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

        request.setRawHeader("Accept","text/html, application/xhtml+xml, */*");
        // request.setRawHeader("Referer","http://localhost:8080");
        request.setRawHeader("Referer" , "https://open.ys7.com/api/lapp/token/get");
        request.setRawHeader("Accept-Language","en-US,*");
        request.setRawHeader("X-Requested-With","XMLHttpRequest");
        request.setRawHeader("User-Agent","Mozilla/5.0");
        request.setRawHeader("Accept-Encoding","gzip,deflate");
        request.setRawHeader("Host","localhost:8080");
        request.setRawHeader("Connection","close"); // "Connection" , "Keey-Alive"
        request.setRawHeader("Cache-Control","no-cache");
        request.setRawHeader("Content-Type" , "application/x-www-form-urlencoded");

        QByteArray size;
        size.clear();
        size.append(postData.size());

        request.setRawHeader("Content-Length",size);

        reply = qnam.post(request , postData);

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

        postData.clear();
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

    startRequest(newUrl);

}

QFile *HTTP::openFileForWrite(const QString &fileName)
{
    QScopedPointer<QFile> file(new QFile(fileName));

    if (!file->open(QIODevice::WriteOnly))
    {

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

    if (httpRequestAborted)
    {
        qDebug() << "ERR : HTTP request aborted .";
        reply->deleteLater();
        reply = Q_NULLPTR;
        return;
    }

    if (reply->error())
    {

        qDebug() << "ERR : " << reply->errorString() << " .";

        reply->deleteLater();
        reply = Q_NULLPTR;
        return;
    }

    setFinished(true);

    return;
}

void HTTP::httpReadyRead()
{

    QByteArray temp;


    temp = reply->readAll();
    this->info.append(temp);
}

void HTTP::slotAuthenticationRequired(QNetworkReply*,QAuthenticator *authenticator)
{

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
    // this->setUrl("http://localhost:8080");
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

void HTTP::addPostdata(QString key, QString value)
{
    this->postData.append("&" + key + "=" + value);
}

