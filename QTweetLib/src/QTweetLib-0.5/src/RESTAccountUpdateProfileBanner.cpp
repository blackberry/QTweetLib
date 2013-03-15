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

#include "RESTAccountUpdateProfileBanner.h"

#include <QDebug>

RESTAccountUpdateProfileBanner::RESTAccountUpdateProfileBanner(
		OAuthTwitter* oauthTwitter, QObject* parent) :
		RESTPhotoPost(oauthTwitter, parent) {

}

RESTAccountUpdateProfileBanner::~RESTAccountUpdateProfileBanner() {
}

QString RESTAccountUpdateProfileBanner::getMediaHeader() {
	return "banner";
}

QString RESTAccountUpdateProfileBanner::getEndpointUrl() {
	return "https://api.twitter.com/1.1/account/update_profile_banner.json";
}

void RESTAccountUpdateProfileBanner::updateBanner(const QString& filePath){
	QHash<QString, QString> postValues;
	post(postValues, filePath);
}

void RESTAccountUpdateProfileBanner::parsingJsonFinished(const QVariant &json,
		bool ok, const QString &errorMsg) {
	if (ok) {

		emit profileBannerUpdated();
	} else {
		qDebug() << "RESTAccountUpdateProfileImage parser error: " << errorMsg;
		emit error(QTweetJsonError(errorMsg, json.toByteArray()));
	}
}

