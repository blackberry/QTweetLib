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

#ifndef RESTPHOTOPOST_H_
#define RESTPHOTOPOST_H_

#include "qtweetnetbase.h"
#include <QObject>
#include <QHash>

class QTWEETLIBSHARED_EXPORT RESTPhotoPost: public QTweetNetBase {
	Q_OBJECT

public:
	RESTPhotoPost(OAuthTwitter* oauthTwitter, QObject* parent = NULL);
	virtual ~RESTPhotoPost();

signals:
	void failed(QString errorMsg);

protected:

	/**
	 *   Post a multi-part http form request with post params and a photo
	 *   @param postValues the key/value pairs for the post body of the request. Assumed to be encoded properly for transmission
	 *   @param photoPath the path to the photograph to be uploaded
	 */
	void post(const QHash<QString, QString>& postValues, const QString& photoPath);

	virtual QString getMediaHeader() = 0;
	virtual QString getEndpointUrl() = 0;

};

#endif /* RESTPHOTOPOST_H_ */
