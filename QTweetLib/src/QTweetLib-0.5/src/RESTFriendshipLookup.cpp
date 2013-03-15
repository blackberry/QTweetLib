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
#include <qstringlist.h>
#include "qtweetuserstatusesfollowers.h"
#include "qtweetuser.h"
#include "qtweetconvert.h"

#include "RESTFriendshipLookup.h"

RESTFriendshipLookup::RESTFriendshipLookup(QObject *parent) :
        QTweetNetBase(parent), m_usesCursoring(false)
{
}

RESTFriendshipLookup::RESTFriendshipLookup(OAuthTwitter *oauthTwitter, QObject *parent) :
        QTweetNetBase(oauthTwitter, parent), m_usesCursoring(false)
{
}
RESTFriendshipLookup::~RESTFriendshipLookup()
{
}

void RESTFriendshipLookup::fetch(const QList<qint64>& userInfoList)
{
	QUrl url("https://api.twitter.com/1.1/friendships/lookup.json");
	int maxElements = 100;
	int i = 0;
	QString ids;
	 QList<qint64>::const_iterator idit = userInfoList.begin();
	for(; idit != userInfoList.end() && ++i < maxElements; ++idit){
		ids.append(QString::number(*idit) + ',');
	}
	if(!ids.isEmpty()){
		ids.chop(1);
		url.addQueryItem("user_id", ids);
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

void RESTFriendshipLookup::parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg)
{
	Q_UNUSED(ok);
	Q_UNUSED(errorMsg);
	//	fprintf(stderr, "parsingJsonFinished is");
	QMap<qint64, bool> friendshipData;
	QList<QVariant> variantList = json.toList();
	if (variantList.size() != 0)
	{
		foreach (const QVariant& variant, variantList) {
			QList<QVariant> connectionsList = variant.toMap()["connections"].toList();
			friendshipData[variant.toMap()["id"].toULongLong()] = connectionsList.contains("following");
		}
		emit friendshipInfoFound(friendshipData);
	}
}

