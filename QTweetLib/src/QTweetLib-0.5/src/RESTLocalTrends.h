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

#ifndef RESTLOCALTRENDS_H
#define RESTLOCALTRENDS_H

#include "qtweetnetbase.h"
#include "RESTTrends.h"

class QTWEETLIBSHARED_EXPORT RESTLocalTrends : public QTweetNetBase
{
    Q_OBJECT
public:
    RESTLocalTrends(QObject *parent = 0);
    RESTLocalTrends(OAuthTwitter *oauthTwitter, QObject *parent = 0);
    void fetch(const double latitude, const double longitude,
    		qint64 woeid = 1, //Default Global WOEID
                   const QString& exclusion = QString());

signals:
    /** Emits page of trends list
     *  @param followersList list of friends
     */
    void parsedTrendsList(const QList<QVariantMap> trendsList);

protected slots:

    void parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg);
private:
    RESTTrends m_fetcherTrends;

};

#endif // RESTLOCALTRENDS_H
