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

#include "RESTCustomGet.h"


RESTCustomGet::RESTCustomGet(QObject *parent) :
        QTweetNetBase(parent)
{
}

RESTCustomGet::RESTCustomGet(OAuthTwitter *oauthTwitter, QObject *parent) :
        QTweetNetBase(oauthTwitter, parent)
{
}

/**
 *   Starts fetching conversations items
 *   @param id The id of the conversation tweet
 *   @param limit the limit of tweets to fetch
 *   @param maxId the Maximum id of the tweet to fetch
 *   @param trimUser flag that enables or disables trimming the user
 *   @param contribDetails flag that enables or disables contributor details
 *   @param includeEntities flag that enables or disables entities to include
 */
void RESTCustomGet::fetch(const QUrl& customApiCallSignature)
{

	QUrl url(customApiCallSignature);

    QNetworkRequest req(url);
    req.setRawHeader("User-Agent", userAgent());
    if (isAuthenticationEnabled()) {
        QByteArray oauthHeader = oauthTwitter()->generateAuthorizationHeader(url, OAuth::GET);
        req.setRawHeader(AUTH_HEADER, oauthHeader);
    }

    QNetworkReply *reply = oauthTwitter()->networkAccessManager()->get(req);
    connect(reply, SIGNAL(finished()), this, SLOT(reply()));

}

void RESTCustomGet::parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg)
{
	if (ok)
	{
		//Send the parsed json data directly to the listener.
		emit parsedJsonData(json);
	} else {
        emit error(QTweetJsonError(errorMsg, json.toByteArray()));
	}

}

