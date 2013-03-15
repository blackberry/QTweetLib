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
#include "qtweetgetSearchquery.h"
#include "qtweetstatus.h"
#include "qtweetconvert.h"

QTweetGetSearchQuery::QTweetGetSearchQuery(QObject *parent) :
    QTweetNetBase(parent)
{
}

QTweetGetSearchQuery::QTweetGetSearchQuery(OAuthTwitter *oauthTwitter, QObject *parent) :
        QTweetNetBase(oauthTwitter, parent)
{
}

/**
 *   save a search query
 */
void QTweetGetSearchQuery::fetch()
{
    if (!isAuthenticationEnabled()) {
        qCritical("Needs authentication to be enabled");
        return;
    }

    QUrl url("https://api.twitter.com/1.1/saved_searches/list.json");

    QUrl urlQuery(url);


    QNetworkRequest req(url);
    req.setRawHeader("User-Agent", userAgent());
    QByteArray oauthHeader = oauthTwitter()->generateAuthorizationHeader(url, OAuth::GET);
    req.setRawHeader(AUTH_HEADER, oauthHeader);

    QNetworkReply *reply = oauthTwitter()->networkAccessManager()->get(req);
    connect(reply, SIGNAL(finished()), this, SLOT(reply()));
}

void QTweetGetSearchQuery::parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg)
{
    if (ok) {
    	QList<QVariant> list = json.toList();
    	QList<QString> queryList;
    	foreach(QVariant var, list){
    		QVariantMap map = var.toMap();

    		queryList.append(map["query"].toString());

    	}

        emit queryListParsed(queryList);
    } else {
        qDebug() << "QTweetGetSearchQuery parse error: " << errorMsg;
        emit error(QTweetJsonError(errorMsg, json.toByteArray()));
    }
}

