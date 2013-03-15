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

#ifndef RESTACCOUNTUPDATEPROFILEIMAGE_H_
#define RESTACCOUNTUPDATEPROFILEIMAGE_H_

#include "RESTPhotoPost.h"

class QTWEETLIBSHARED_EXPORT RESTAccountUpdateProfileImage : public RESTPhotoPost {
	Q_OBJECT
public:
	RESTAccountUpdateProfileImage(OAuthTwitter* oauthTwitter, QObject* parent = NULL);
	virtual ~RESTAccountUpdateProfileImage();

	void updateProfileImage(const QString& filePath);

signals:
	/**
	 * Emitted when the request completes successfully. Note to get the link to
	 * the updated profile image you will need to call users/show at least 5 seconds after
	 * this signal happens.
	 */
	void profileImageUpdated();

protected:

	virtual QString getMediaHeader();
	virtual QString getEndpointUrl();

protected slots:
    void parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg);
};

#endif /* RESTACCOUNTUPDATEPROFILEIMAGE_H_ */
