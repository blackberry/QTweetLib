/* Copyright (c) 2011, Antonie Jovanoski
 *
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Contact e-mail: Antonie Jovanoski <minimoog77_at_gmail.com>
 */

#include <QtDebug>
#include "qtweetblockscreate.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include "qtweetuser.h"
#include "qtweetconvert.h"

/**
 *  Constructor
 */
QTweetBlocksCreate::QTweetBlocksCreate(QObject *parent) :
    QTweetNetBase(parent)
{
}

/**
 *  Constructor
 *  @param oauthTwitter OAuthTwitter object
 *  @param parent parent QObject
 */
QTweetBlocksCreate::QTweetBlocksCreate(OAuthTwitter *oauthTwitter, QObject *parent) :
    QTweetNetBase(oauthTwitter, parent)
{
}

/**
 *  Blocks user
 *  @param userid id of the user to be blocked
 *  @param includeEntities When set to true, each tweet will include a node called "entities"
 */
void QTweetBlocksCreate::create(qint64 userid, bool includeEntities)
{
    if (!isAuthenticationEnabled()) {
        qCritical("Needs authentication to be enabled");
        return;
    }

    QUrl url("https://api.twitter.com/1.1/blocks/create.json");

    QUrl urlQuery(url);

    urlQuery.addQueryItem("user_id", QString::number(userid));

    if (includeEntities)
        urlQuery.addQueryItem("include_entities", "true");

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

/**
 *  Blocks user
 *  @param screenName screen name of the user to be blocked
 *  @param includeEntities When set to true, each tweet will include a node called "entities"
 */
void QTweetBlocksCreate::create(const QString& screenName, bool includeEntities)
{
    if (!isAuthenticationEnabled()) {
        qCritical("Needs authentication to be enabled");
        return;
    }

    QUrl url("https://api.twitter.com/1.1/blocks/create.json");

    QUrl urlQuery(url);

    urlQuery.addQueryItem("screen_name", screenName);

    if (includeEntities)
        urlQuery.addQueryItem("include_entities", "true");

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

void QTweetBlocksCreate::parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg)
{
    if (ok) {
        QTweetUser user = QTweetConvert::variantMapToUserInfo(json.toMap());

        emit finishedCreatingBlock(user);
    } else {
        qDebug() << "QTweetBlocksCreate parser error: " << errorMsg;
        emit error(QTweetJsonError(errorMsg, json.toByteArray()));
    }
}
