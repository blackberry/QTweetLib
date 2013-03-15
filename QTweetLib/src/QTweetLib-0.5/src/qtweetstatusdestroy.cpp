/* Copyright (c) 2010, Antonie Jovanoski
 *
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 *
 * Contact e-mail: Antonie Jovanoski <minimoog77_at_gmail.com>
 */

#include <QtDebug>
#include <QNetworkReply>
#include <QNetworkRequest>
#include "qtweetstatusdestroy.h"
#include "qtweetstatus.h"
#include "qtweetconvert.h"

QTweetStatusDestroy::QTweetStatusDestroy(QObject *parent) :
    QTweetNetBase(parent)
{
}

QTweetStatusDestroy::QTweetStatusDestroy(OAuthTwitter *oauthTwitter, QObject *parent) :
        QTweetNetBase(oauthTwitter, parent)
{
}

/**
 *   Destroys tweet with id
 *   @param id tweet ID
 *   @param trimUser trims users info
 *   @param includeEntities true to include node entities in response
 */
void QTweetStatusDestroy::destroy(qint64 id,
                                  bool trimUser)
{
    if (!isAuthenticationEnabled()) {
        qCritical("Needs authentication to be enabled");
        return;
    }

    QUrl url(QString("https://api.twitter.com/1.1/statuses/destroy/%1.json").arg(id));

    QUrl urlQuery(url);


    if (trimUser)
        urlQuery.addQueryItem("trim_user", "true");

    QNetworkRequest req(url);
    req.setRawHeader("User-Agent", userAgent());
    QByteArray oauthHeader = oauthTwitter()->generateAuthorizationHeader(urlQuery, OAuth::POST);
    req.setRawHeader(AUTH_HEADER, oauthHeader);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QByteArray postBody = urlQuery.toEncoded(QUrl::RemoveScheme | QUrl::RemoveAuthority | QUrl::RemovePath);
    postBody.remove(0, 1);

    QNetworkReply *reply = oauthTwitter()->networkAccessManager()->post(req, postBody);
    connect(reply, SIGNAL(finished()), this, SLOT(reply()));
}

void QTweetStatusDestroy::parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg)
{
    if (ok) {
        QTweetStatus status = QTweetConvert::variantMapToStatus(json.toMap());

        emit deletedStatus(status);
    } else {
        qDebug() << "QTweetStatusDestroy parse error: " << errorMsg;
        emit error(QTweetJsonError(errorMsg, json.toByteArray()));
    }
}

