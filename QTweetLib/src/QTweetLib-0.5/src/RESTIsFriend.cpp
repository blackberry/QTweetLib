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

#include "RESTIsFriend.h"

RESTIsFriend::RESTIsFriend(QObject *parent)
{
}

RESTIsFriend::RESTIsFriend(OAuthTwitter *oauthTwitter, QObject *parent):
QTweetNetBase(oauthTwitter, parent)
{
}

//void RESTIsFriend::fetch(const qint64& userid1, const qint64& userid2)
//{
//	QUrl url("https://api.twitter.com/1/friendships/exists.json?");
//	url.addQueryItem("user_id_a", QString::number(userid1));
//	url.addQueryItem("user_id_b", QString::number(userid2));
//
//}
void RESTIsFriend::fetch(const qint64& userid)
{
	//fprintf(stderr, "RESTIsFriend::fetch for %d \n", userid);

	QUrl url("https://api.twitter.com/1.1/friendships/lookup.json");
	url.addQueryItem("user_id", QString::number(userid));
	fetchForUrl(url);
}
void RESTIsFriend::fetch(const QString& screenName)
{
	QUrl url("https://api.twitter.com/1.1/friendships/lookup.json");
	url.addQueryItem("screen_name", screenName);
	fetchForUrl(url);
}

void RESTIsFriend::fetchForUrl(const QUrl& url)
{
//	QUrl url("https://api.twitter.com/1/friendships/lookup.json?screen_name=twitterapi,twitter");
	//QUrl url("https://api.twitter.com/1/friendships/exists.json?screen_name_a=mac_test4&screen_name_b=mac_test1");
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

void RESTIsFriend::parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg){
	Q_UNUSED(ok);
	Q_UNUSED(errorMsg);
	QList<QVariant> variantList = json.toList();
	//fprintf(stderr, "RESTIsFriend::variantList.size %d \n", variantList.size());
	if (variantList.size() == 1) //it should be 1 in this case as we are fetching for single user
	{
		QVariant variant = variantList.at(0);
		QList<QVariant> connectionsList = variant.toMap()["connections"].toList();
		//fprintf(stderr, "connectionsList size is %d", connectionsList.size());

		if(connectionsList.contains("following")){
			//fprintf(stderr, "is following \n");
			emit friendshipInfoFound(true, variant.toMap()["id"].toString(), variant.toMap()["name"].toString());
		} else{
			//fprintf(stderr, "is NOT following \n");
			emit friendshipInfoFound(false, variant.toMap()["id"].toString(), variant.toMap()["name"].toString());
		}
	}
}

