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

#include "RESTUsersReportSpam.h"

#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "qtweetconvert.h"

RESTUsersReportSpam::RESTUsersReportSpam(QObject *parent) :
		QTweetNetBase(parent) {
}

RESTUsersReportSpam::RESTUsersReportSpam(OAuthTwitter *oauthTwitter,
		QObject *parent) :
		QTweetNetBase(oauthTwitter, parent) {
}

RESTUsersReportSpam::~RESTUsersReportSpam() {
}

void RESTUsersReportSpam::reportSpam(const QString& screenName) {
	QUrl url("https://api.twitter.com/1.1/users/report_spam.json");

	QUrl urlQuery(url);

	urlQuery.addQueryItem("screen_name", screenName);

	QNetworkRequest req(url);
	req.setRawHeader("User-Agent", userAgent());

	QByteArray oauthHeader = oauthTwitter()->generateAuthorizationHeader(
			urlQuery, OAuth::POST);
	req.setRawHeader(AUTH_HEADER, oauthHeader);
	req.setHeader(QNetworkRequest::ContentTypeHeader,
			"application/x-www-form-urlencoded");

	QByteArray postBody = urlQuery.toEncoded(
			QUrl::RemoveScheme | QUrl::RemoveAuthority | QUrl::RemovePath);
	postBody.remove(0, 1);

	QNetworkReply *reply = oauthTwitter()->networkAccessManager()->post(req,
			postBody);
	connect(reply, SIGNAL(finished()), this, SLOT(reply()));
}

void RESTUsersReportSpam::reportSpam(qint64 userId) {
	QUrl url("https://api.twitter.com/1.1/users/report_spam.json");

	QUrl urlQuery(url);

	urlQuery.addQueryItem("user_id", QString::number(userId));

	QNetworkRequest req(url);
	req.setRawHeader("User-Agent", userAgent());
	QByteArray oauthHeader = oauthTwitter()->generateAuthorizationHeader(
			urlQuery, OAuth::POST);
	req.setRawHeader(AUTH_HEADER, oauthHeader);
	req.setHeader(QNetworkRequest::ContentTypeHeader,
			"application/x-www-form-urlencoded");

	QByteArray postBody = urlQuery.toEncoded(
			QUrl::RemoveScheme | QUrl::RemoveAuthority | QUrl::RemovePath);
	postBody.remove(0, 1);

	QNetworkReply *reply = oauthTwitter()->networkAccessManager()->post(req,
			postBody);
	connect(reply, SIGNAL(finished()), this, SLOT(reply()));
}

void RESTUsersReportSpam::parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg)
{
    if (ok) {
        QTweetUser user = QTweetConvert::variantMapToUserInfo(json.toMap());

        emit reportedAsSpam(user);
    } else {
        qDebug() << "RESTUsersReportSpam parser error: " << errorMsg;
        emit error(QTweetJsonError(errorMsg, json.toByteArray()));
    }
}
