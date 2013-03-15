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
#include "qtweetmentions.h"
#include "qtweetstatus.h"
#include "qtweetconvert.h"

QTweetMentions::QTweetMentions(QObject *parent) :
    QTweetNetBase(parent),
    m_sinceid(0),
    m_maxid(0),
    m_count(0),
    m_trimUser(false),
    m_includeEntities(false),
    m_contributorDetails(false)
{
}

QTweetMentions::QTweetMentions(OAuthTwitter *oauthTwitter, QObject *parent) :
    QTweetNetBase(oauthTwitter, parent),
    m_sinceid(0),
    m_maxid(0),
    m_count(0),
    m_trimUser(false),
    m_includeEntities(false),
    m_contributorDetails(false)
{
}

/**
 *   Start fetching
 *   @param sinceid fetches tweets with ID greater (more recent) then sinceid
 *   @param maxid fetches tweets with ID less (older) then maxid
 *   @param count number of tweets to fetch (up to 200)
 *   @param includeEntities true to include a node called "entities"
 *   @param contributorDetails true to enhance the contributors element of the status response
 *   @remarks Put parameter to default value to not to be put in query
 */
void QTweetMentions::fetch(qint64 sinceid,
                           qint64 maxid,
                           int count,
                           bool trimUser,
                           bool includeEntities,
                           bool contributorDetails)
{
    if (!isAuthenticationEnabled()) {
        qCritical("Needs authentication to be enabled");
        return;
    }

    QUrl url("https://api.twitter.com/1.1/statuses/mentions_timeline.json");

    if (sinceid != 0)
        url.addQueryItem("since_id", QString::number(sinceid));

    if (maxid != 0)
        url.addQueryItem("max_id", QString::number(maxid));

    if (count != 0)
        url.addQueryItem("count", QString::number(count));


    if (trimUser)
        url.addQueryItem("trim_user", "true");


    if (includeEntities)
        url.addQueryItem("include_entities", "true");


    if (contributorDetails)
        url.addQueryItem("contributor_details", "true");
    url.addQueryItem("include_my_retweet", "true");
    QNetworkRequest req(url);
    req.setRawHeader("User-Agent", userAgent());
    QByteArray oauthHeader = oauthTwitter()->generateAuthorizationHeader(url, OAuth::GET);
    req.setRawHeader(AUTH_HEADER, oauthHeader);

    QNetworkReply *reply = oauthTwitter()->networkAccessManager()->get(req);
    connect(reply, SIGNAL(finished()), this, SLOT(reply()));
}

void QTweetMentions::get()
{
    fetch(m_sinceid, m_maxid, m_count, m_trimUser, m_includeEntities,  m_contributorDetails);
}

void QTweetMentions::parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg)
{
    if (ok) {
        QList<QTweetStatus> statuses = QTweetConvert::variantToStatusList(json);

        emit parsedStatuses(statuses);
    } else {
        qDebug() << "QTweetMentions JSON parser error: " << errorMsg;
        emit error(QTweetJsonError(errorMsg, json.toByteArray()));
    }
}

