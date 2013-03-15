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

#include "RESTAccountUpdateProfileImage.h"

#include <QDebug>

RESTAccountUpdateProfileImage::RESTAccountUpdateProfileImage(
		OAuthTwitter* oauthTwitter, QObject* parent) :
		RESTPhotoPost(oauthTwitter, parent) {

}

RESTAccountUpdateProfileImage::~RESTAccountUpdateProfileImage() {
}

QString RESTAccountUpdateProfileImage::getMediaHeader() {
	return "image";
}

QString RESTAccountUpdateProfileImage::getEndpointUrl() {
	return "https://api.twitter.com/1.1/account/update_profile_image.json";
}

void RESTAccountUpdateProfileImage::updateProfileImage(const QString& filePath){
	QHash<QString, QString> postParams;
	postParams["skip_status"] = "1";
	post(postParams, filePath);

}

void RESTAccountUpdateProfileImage::parsingJsonFinished(const QVariant &json,
		bool ok, const QString &errorMsg) {
	if (ok) {
		emit profileImageUpdated();
	} else {
		qDebug() << "RESTAccountUpdateProfileImage parser error: " << errorMsg;
		emit error(QTweetJsonError(errorMsg, json.toByteArray()));
	}
}
