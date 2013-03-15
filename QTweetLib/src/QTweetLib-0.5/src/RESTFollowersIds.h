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

#ifndef RESTFOLLOWERSIDS_H
#define RESTFOLLOWERSIDS_H

#include "qtweetnetbase.h"

class QTWEETLIBSHARED_EXPORT RESTFollowersIds : public QTweetNetBase
{
    Q_OBJECT
public:
    RESTFollowersIds(QObject *parent = 0);
    RESTFollowersIds(OAuthTwitter *oauthTwitter, QObject *parent = 0);
    void fetch(qint64 userid = 0,
               const QString& cursor = QString());
    void fetch(const QString& screenName = QString(),
               const QString& cursor = QString());

signals:
    /** Emits page of followers list
     *  @param followersList list of friends
     *  @param nextCursor cursor for next page, "0" if there is no next page, empty if there is no paging
     *  @param prevCursor cursor for prev page, "0" if there is no prev page, empty if there is no paging
     */
    void parsedFollowersList(const QList<qint64> followerIdsList,
                             const QString& nextCursor = QString(),
                             const QString& prevCursor = QString());

protected slots:


    void parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg);

private:
    bool m_usesCursoring;
};

#endif // RESTFOLLOWERSIDS_H
