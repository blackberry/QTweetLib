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

#include "RESTFriendshipExists.h"

RESTFriendshipExists::RESTFriendshipExists(QObject *parent)
{
}

RESTFriendshipExists::RESTFriendshipExists(OAuthTwitter *oauthTwitter, QObject *parent):
QTweetNetBase(oauthTwitter, parent)
{
}

void RESTFriendshipExists::fetch(const qint64& userid1, const qint64& userid2)
{
	QUrl url("https://api.twitter.com/1/friendships/exists.json?");
	url.addQueryItem("user_id_a", QString::number(userid1));
	url.addQueryItem("user_id_b", QString::number(userid2));

	//fprintf(stderr, "fetchForUrl  %s \n", url.toString().toStdString().c_str());
	QNetworkRequest req(url);
	req.setRawHeader("User-Agent", userAgent());
	if (isAuthenticationEnabled()) {
		QByteArray oauthHeader = oauthTwitter()->generateAuthorizationHeader(url, OAuth::GET);
		req.setRawHeader(AUTH_HEADER, oauthHeader);
	}

	QNetworkReply *reply = oauthTwitter()->networkAccessManager()->get(req);
	connect(reply, SIGNAL(finished()), this, SLOT(reply()));
}


void RESTFriendshipExists::parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg){
	Q_UNUSED(ok);
	Q_UNUSED(errorMsg);
	emit friendshipExists(json.toBool());

}

