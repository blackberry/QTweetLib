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

#include "RESTPhotoPost.h"
#include "qtweetneterror.h"
#include <QNetworkAccessManager>
#include <QDebug>
#include <QFile>
#include <QNetworkReply>
#include <QHttpPart>

RESTPhotoPost::RESTPhotoPost(OAuthTwitter* oauthTwitter, QObject* parent) :
		QTweetNetBase(oauthTwitter, parent) {
}

RESTPhotoPost::~RESTPhotoPost() {
}

void RESTPhotoPost::post(const QHash<QString, QString>& postParams, const QString& filePath) {
	if (!isAuthenticationEnabled()) {
		qCritical("Needs authentication to be enabled");
		return;
	}

	QUrl urlQuery(getEndpointUrl());
	QByteArray oauthHeader = oauthTwitter()->generateAuthorizationHeader(urlQuery, OAuth::POST);

	QNetworkRequest req(urlQuery);
	req.setRawHeader(AUTH_HEADER, oauthHeader);
	req.setRawHeader("User-Agent", userAgent());

	QHttpMultiPart *multiPart(new QHttpMultiPart(QHttpMultiPart::FormDataType));
	foreach(QString key, postParams.keys()){
		QHttpPart part;

		part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"" + key + "\""));
		part.setBody(postParams.value(key).toUtf8());

		multiPart->append(part);
	}

	QHttpPart imagePart;
	if (!filePath.isEmpty()) {
		// Needs a filename, but it doesn't matter what, or else the picture wont upload.
		imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"" + getMediaHeader() +"\"; filename=\"batman.png\";"));
		QFile* imageFile = new QFile(filePath, multiPart);
		if (!imageFile->open(QIODevice::ReadOnly)) {
			qCritical() << "Could not open image file: " << imageFile->error();
			emit failed(imageFile->errorString());
			return;
		}
		imagePart.setBodyDevice(imageFile);

		multiPart->append(imagePart);
	}

	QNetworkReply *reply = oauthTwitter()->networkAccessManager()->post(req, multiPart);
	multiPart->setParent(reply);
	connect(reply, SIGNAL(finished()), this, SLOT(reply()));
}



