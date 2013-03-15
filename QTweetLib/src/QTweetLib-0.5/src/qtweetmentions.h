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

#ifndef QTWEETMENTIONS_H
#define QTWEETMENTIONS_H

#include "qtweetnetbase.h"

/**
 *   Fetches mentions (up to 800)
 */
class QTWEETLIBSHARED_EXPORT QTweetMentions : public QTweetNetBase
{
    Q_OBJECT
    Q_PROPERTY(qint64 sinceID READ sinceID WRITE setSinceID)
    Q_PROPERTY(qint64 maxID READ maxID WRITE setMaxID)
    Q_PROPERTY(int count READ count WRITE setCount)
    Q_PROPERTY(bool trimUser READ isTrimUser WRITE setTrimUser)
    Q_PROPERTY(bool includeEntities READ isIncludeEntities WRITE setIncludeEntities)
    Q_PROPERTY(bool contributorDetails READ isContributorsDetails WRITE setContributorsDetails)

public:
    QTweetMentions(QObject *parent = 0);
    QTweetMentions(OAuthTwitter *oauthTwitter, QObject *parent = 0);
    void fetch(qint64 sinceid = 0,
               qint64 maxid = 0,
               int count = 0,
               bool trimUser = false,
               bool includeEntities = false,
               bool contributorDetails = false);

    void get();

    void setSinceID(qint64 sinceid) { m_sinceid = sinceid; }
    qint64 sinceID() const { return m_sinceid; }

    void setMaxID(qint64 maxid) { m_maxid = maxid; }
    qint64 maxID() const { return m_maxid; }

    void setCount(int count) { m_count = count; }
    int count() const { return m_count; }


    void setTrimUser(bool trimUser) { m_trimUser = trimUser; }
    bool isTrimUser() const { return m_trimUser; }


    void setIncludeEntities(bool includeEntities) { m_includeEntities = includeEntities; }
    bool isIncludeEntities() const { return m_includeEntities; }

    void setContributorsDetails(bool contributorsDetails) { m_contributorDetails = contributorsDetails; }
    bool isContributorsDetails() const { return m_contributorDetails; }

signals:
    /** Emits mentions status list */
    void parsedStatuses(const QList<QTweetStatus>& statuses);

protected slots:
    void parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg);

private:
    qint64 m_sinceid;
    qint64 m_maxid;
    int m_count;
    bool m_trimUser;
    bool m_includeEntities;
    bool m_contributorDetails;
};

#endif // QTWEETMENTIONS_H
