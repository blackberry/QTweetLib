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

#include "RESTAccountUpdateProfile.h"

#include <QDebug>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include "qtweetUser.h"
#include "qtweetconvert.h"

RESTAccountUpdateProfile::RESTAccountUpdateProfile(QObject *parent) :
		QTweetNetBase(parent) {
}

RESTAccountUpdateProfile::RESTAccountUpdateProfile(OAuthTwitter *oauthTwitter,
		QObject *parent) :
		QTweetNetBase(oauthTwitter, parent) {
}

RESTAccountUpdateProfile::~RESTAccountUpdateProfile() {

}


void RESTAccountUpdateProfile::post(const QString& name, const QString& profileUrl,
		const QString& location, const QString& description) {
	QUrl url("https://api.twitter.com/1.1/account/update_profile.json");

    QUrl urlQuery("https://api.twitter.com/1.1/account/update_profile.json");

    if (!name.isEmpty()) {
    	urlQuery.addQueryItem("name", name);
    }

    if (!profileUrl.isEmpty()) {
    	urlQuery.addQueryItem("url", profileUrl);
    }

    if (!location.isEmpty()) {
    	urlQuery.addQueryItem("location", location);
    }

    if (!description.isEmpty()) {
    	urlQuery.addQueryItem("description", description);
    }

	QByteArray oauthHeader = oauthTwitter()->generateAuthorizationHeader(
			urlQuery, OAuth::POST);
	QNetworkRequest req(url);
	req.setRawHeader(AUTH_HEADER, oauthHeader);
	req.setHeader(QNetworkRequest::ContentTypeHeader,
			"application/x-www-form-urlencoded");
	req.setRawHeader("User-Agent", userAgent());
	//build status post array
	QByteArray accountUpdatePost = urlQuery.toEncoded(
			QUrl::RemoveScheme | QUrl::RemoveAuthority | QUrl::RemovePath);


    //remove '?'
	accountUpdatePost.remove(0, 1);

    QNetworkReply *reply = oauthTwitter()->networkAccessManager()->post(req, accountUpdatePost);
    connect(reply, SIGNAL(finished()), this, SLOT(reply()));
}

void RESTAccountUpdateProfile::parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg){
	if (ok) {
		QTweetUser user = QTweetConvert::variantMapToUserInfo(json.toMap());

		emit profileUpdated(user);
	} else {
		qDebug() << "RESTAccountUpdateProfile parser error: " << errorMsg;
		emit error(QTweetJsonError(errorMsg, json.toByteArray()));
	}
}
