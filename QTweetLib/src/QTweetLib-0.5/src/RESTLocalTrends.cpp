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

#include <QtDebug>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "qtweetuserstatusesfollowers.h"
#include "qtweetuser.h"
#include "qtweetconvert.h"

#include "RESTLocalTrends.h"
#include "RESTTrends.h"


RESTLocalTrends::RESTLocalTrends(QObject *parent) :
	QTweetNetBase(parent)
{
}

RESTLocalTrends::RESTLocalTrends(OAuthTwitter *oauthTwitter, QObject *parent) :
	QTweetNetBase(oauthTwitter, parent),
	 m_fetcherTrends(oauthTwitter, parent)
{
	connect(&m_fetcherTrends, SIGNAL(parsedTrendsList(QList<QVariantMap>)),
							this, SIGNAL(parsedTrendsList(QList<QVariantMap>)));
	connect(&m_fetcherTrends, SIGNAL(error(const QTweetNetError&)),
								this, SIGNAL(error(const QTweetNetError&)));
}

/**
 *   Starts fetching user followers list
 *   @param woeid
 *   @param exclusion
 */
void RESTLocalTrends::fetch(const double latitude, const double longitude, qint64 woeid,
					   const QString &exclusion)
{
	QUrl url("https://api.twitter.com/1.1/trends/closest.json?");

    url.addQueryItem("lat", QString::number(latitude));
    url.addQueryItem("long", QString::number(longitude));

    if (!exclusion.isEmpty()) {
        url.addQueryItem("exclude", exclusion);
    }

    QNetworkRequest req(url);
    //fprintf(stderr, "url is: %s \n", url.toString().toStdString().c_str());
    req.setRawHeader("User-Agent", userAgent());
    if (isAuthenticationEnabled()) {
        QByteArray oauthHeader = oauthTwitter()->generateAuthorizationHeader(url, OAuth::GET);
        req.setRawHeader(AUTH_HEADER, oauthHeader);
    }

    QNetworkReply *reply = oauthTwitter()->networkAccessManager()->get(req);
    connect(reply, SIGNAL(finished()), this, SLOT(reply()));
}


void RESTLocalTrends::parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg)
{
	Q_UNUSED(ok);
	Q_UNUSED(errorMsg);

	QList<QVariant> variantList = json.toList();

	if(variantList.at(0).toMap().size() != 0){
		m_fetcherTrends.fetch(variantList.at(0).toMap()["woeid"].toInt());
	}

}

