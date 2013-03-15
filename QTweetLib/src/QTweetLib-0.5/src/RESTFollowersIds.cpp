/* Copyright (c) 2013 Research In Motion Limited.
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
 */

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
#include <QNetworkRequest>
#include <QNetworkReply>
#include "qtweetuserstatusesfollowers.h"
#include "qtweetuser.h"
#include "qtweetconvert.h"

#include "RESTFollowersIds.h"


RESTFollowersIds::RESTFollowersIds(QObject *parent) :
        QTweetNetBase(parent), m_usesCursoring(false)
{
}

RESTFollowersIds::RESTFollowersIds(OAuthTwitter *oauthTwitter, QObject *parent) :
        QTweetNetBase(oauthTwitter, parent), m_usesCursoring(false)
{
}

/**
 *   Starts fetching user followers list
 *   @param userid the ID of the user for whom to return results for.
 *                 Set 0 if you want to fetch followers for authenticaded user
 *   @param cursor breaks the results into pages. Provide a value of "-1" to begin paging.
 *   @param includeEntities when set to true, each tweet will include a node called "entities,".
 */
void RESTFollowersIds::fetch(qint64 userid,
							 const QString &cursor)
{
    //QUrl url("https://api.twitter.com/1/statuses/followers.json");
	QUrl url("https://api.twitter.com/1.1/followers/ids.json");

    if (userid != 0)
        url.addQueryItem("user_id", QString::number(userid));

    if (!cursor.isEmpty()) {
        m_usesCursoring = true;
        url.addQueryItem("cursor", cursor);
    }

    QNetworkRequest req(url);
    req.setRawHeader("User-Agent", userAgent());
    if (isAuthenticationEnabled()) {
        QByteArray oauthHeader = oauthTwitter()->generateAuthorizationHeader(url, OAuth::GET);
        req.setRawHeader(AUTH_HEADER, oauthHeader);
    }

    QNetworkReply *reply = oauthTwitter()->networkAccessManager()->get(req);
    connect(reply, SIGNAL(finished()), this, SLOT(reply()));
}



void RESTFollowersIds::parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg){
	Q_UNUSED(ok);
	Q_UNUSED(errorMsg);

	if (m_usesCursoring) {

			QList < qint64 > idList;

			QVariantMap respMap = json.toMap();

			QVariantList idVarList = respMap["ids"].toList();

			foreach (const QVariant& idVar, idVarList)
			idList.append(idVar.toLongLong());

			QString nextCursor = respMap["next_cursor_str"].toString();
			QString prevCursor = respMap["previous_cursor_str"].toString();

			//QList<QTweetUser> userList = QTweetConvert::variantToUserInfoList(userListVar);

			//emit parsedFollowersList(userList, nextCursor, prevCursor);
			emit parsedFollowersList(idList, nextCursor, prevCursor);
		} else {

			//QList<QTweetUser> userList = QTweetConvert::variantToUserInfoList(json);
			QList < qint64 > idList;
			QVariantMap respMap = json.toMap();
			QVariantList idVarList = respMap["ids"].toList();
			foreach (const QVariant& idVar, idVarList)
			{
				idList.append(idVar.toLongLong());
			}

			emit parsedFollowersList(idList);
		}
}

