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

#ifndef RESTFRIENDSHIPEXISTS_H
#define RESTFRIENDSHIPEXISTS_H

#include "qtweetnetbase.h"

class QTWEETLIBSHARED_EXPORT RESTFriendshipExists : public QTweetNetBase
{
    Q_OBJECT
public:
    RESTFriendshipExists(QObject *parent = 0);
    RESTFriendshipExists(OAuthTwitter *oauthTwitter, QObject *parent = 0);
    void fetch(const qint64& userid1, const qint64& userid2);

signals:
	void friendshipExists(bool);


protected slots:
    void parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg);

};

#endif // RESTFRIENDSHIPEXISTS_H
