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

#ifndef RESTCUSTOMGET_H
#define RESTCUSTOMGET_H

#include "qtweetnetbase.h"

class QTWEETLIBSHARED_EXPORT RESTCustomGet : public QTweetNetBase
{
    Q_OBJECT
public:
    RESTCustomGet(QObject *parent = 0);
    RESTCustomGet(OAuthTwitter *oauthTwitter, QObject *parent = 0);

    void fetch(const QUrl& customApiCallSignature);

signals:
    /** Emits a signal containing a list of user suggestions
     *  @param the list of returned user suggestions
     */
	void parsedJsonData(const QVariant &json);

protected slots:

    void parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg);

};

#endif // RESTCUSTOMGET_H
