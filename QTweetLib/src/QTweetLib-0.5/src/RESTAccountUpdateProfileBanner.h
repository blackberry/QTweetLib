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

#ifndef RESTACCOUNTUPDATEPROFILEBANNER_H_
#define RESTACCOUNTUPDATEPROFILEBANNER_H_

#include "RESTPhotoPost.h"

class QTWEETLIBSHARED_EXPORT RESTAccountUpdateProfileBanner : public RESTPhotoPost {
	Q_OBJECT
public:
	RESTAccountUpdateProfileBanner(OAuthTwitter* oauthTwitter, QObject* parent = NULL);
	virtual ~RESTAccountUpdateProfileBanner();

	void updateBanner(const QString& filePath);

signals:
	/**
	 * Emitted when the request completes successfully. Note that this does not
	 * return the URL to the new profile banner. It will be processed asynchronously
	 * on Twitter's side. You can get it by calling users/show at least 5 seconds after
	 * this signal happens. (Maybe, the documentation doesn't say how long to wait for this
	 * call.)
	 */
	void profileBannerUpdated();

protected:

	virtual QString getMediaHeader();
	virtual QString getEndpointUrl();

protected slots:
    void parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg);
};

#endif /* RESTACCOUNTUPDATEPROFILEBANNER_H_ */
