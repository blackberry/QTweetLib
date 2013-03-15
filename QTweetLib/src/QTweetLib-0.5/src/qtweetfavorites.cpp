/* Copyright (c) 2010, Antonie Jovanoski
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
#include <QNetworkRequest>
#include <QNetworkReply>
#include "qtweetfavorites.h"
#include "qtweetstatus.h"
#include "qtweetconvert.h"

/**
 *  Constructor
 */
QTweetFavorites::QTweetFavorites(QObject *parent) :
    QTweetNetBase(parent)
{
}

/**
 *  Constructor
 *  @param oauthTwitter OAuthTwitter object
 *  @param parent parent QObject
 */
QTweetFavorites::QTweetFavorites(OAuthTwitter *oauthTwitter, QObject *parent) :
        QTweetNetBase(oauthTwitter, parent)
{
}

/**
 *   Starts fetching favorites
 *   @param id the ID of the user for whom to request a list of favorite statuses. 0 for authenticated user
 *   @param screenName, screen name for the user
 *   @param sinceid, the id of the tweet we shall fetch newer than
 *   @param maxid, the id of the tweet we shall fetch older than
 *   @param count, the maxnumber of tweets to fetch
 *   @param includeEntities When set to true, each tweet will include a node called "entities,".
 */
void QTweetFavorites::fetch(qint64 userid,
           const QString& screenName,
           qint64 sinceid,
           qint64 maxid,
           int count,
           bool includeEntities ){

	 QUrl url("https://api.twitter.com/1.1/favorites/list.json");

	    if (userid != 0)
	        url.addQueryItem("user_id", QString::number(userid));

	    if (!screenName.isEmpty())
	        url.addQueryItem("screen_name", screenName);

	    if (sinceid != 0)
	        url.addQueryItem("since_id", QString::number(sinceid));

	    if (maxid != 0)
	        url.addQueryItem("max_id", QString::number(maxid));

	    if (count != 0)
	        url.addQueryItem("count", QString::number(count));

	    if (includeEntities)
	        url.addQueryItem("include_entities", "true");

	    QNetworkRequest req(url);
	    req.setRawHeader("User-Agent", userAgent());
	    if (isAuthenticationEnabled()) {
	        QByteArray oauthHeader = oauthTwitter()->generateAuthorizationHeader(url, OAuth::GET);
	        req.setRawHeader(AUTH_HEADER, oauthHeader);
	    }

	    QNetworkReply *reply = oauthTwitter()->networkAccessManager()->get(req);
	    connect(reply, SIGNAL(finished()), this, SLOT(reply()));
}

void QTweetFavorites::parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg)
{
    if (ok) {
        QList<QTweetStatus> statuses = QTweetConvert::variantToStatusList(json);

        emit parsedFavorites(statuses);
    } else {
        qDebug() << "QTweetFavorites JSON parser error: " << errorMsg;
        emit error(QTweetJsonError(errorMsg, json.toByteArray()));
    }
}
