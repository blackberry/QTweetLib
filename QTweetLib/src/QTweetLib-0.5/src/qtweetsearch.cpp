/* Copyright (c) 2010, Antonie Jovanoski
 *
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Contact e-mail: Antonie Jovanoski <minimoog77_at_gmail.com>
 */

#include <QtDebug>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "qtweetsearch.h"
#include "qtweetstatus.h"
#include "qtweetconvert.h"

QTweetSearch::QTweetSearch(QObject *parent) :
    QTweetNetBase(parent)
{
}

QTweetSearch::QTweetSearch(OAuthTwitter *oauthTwitter, QObject *parent) :
    QTweetNetBase(oauthTwitter, parent)
{
}

/**
 *  Starts searching
 *
 *  @param query search query
 *  @param lang Restricts tweets to the given language, given by an ISO 639-1 code. Language detection is best-effort.
 *  @param geocode Returns tweets by users located within a given radius of the given
 *  @param locale Specify the language of the query you are sending (only ja is currently effective).
 *  @param result_type Specifies what type of search results you would prefer to receive.
 *  @param count The number of tweets to return per page, up to a maximum of 100. Defaults to 15.
 *  @param until Returns tweets generated before the given date.
 *  @param sinceid,
 *  @param maxid
 */
void QTweetSearch::start(const QString &query,
                         const QString &lang,
                         const QString &geocode,
                         const QString &locale,
                         const Result_Type result_type,
                         int count,
                         const QDate &until,
                         qint64 sinceid,
                         qint64 maxid)
{
    QUrl url("https://api.twitter.com/1.1/search/tweets.json");

    url.addEncodedQueryItem("q", QUrl::toPercentEncoding(query));

    if (!lang.isEmpty())
        url.addQueryItem("lang", lang);

    if (!geocode.isEmpty())
        url.addQueryItem("geocode", lang);

     if (!locale.isEmpty())
         url.addQueryItem("locale", locale);

    if (result_type == recent){
        url.addQueryItem("result_type", "recent");
    }else if (result_type == popular){
        url.addQueryItem("result_type", "popular");
    } else {
        url.addQueryItem("result_type", "mixed");
    }

    if (count)
        url.addQueryItem("count", QString::number(count));

    if (!until.isNull()){
        url.addQueryItem("until",until.toString("yyyy-MM-dd"));
    }

    if (sinceid)
        url.addQueryItem("since_id", QString::number(sinceid));

    if (maxid)
        url.addQueryItem("max_id", QString::number(maxid));

    QNetworkRequest req(url);
    req.setRawHeader("User-Agent", userAgent());
    if (isAuthenticationEnabled()) {
        QByteArray oauthHeader = oauthTwitter()->generateAuthorizationHeader(url, OAuth::GET);
        req.setRawHeader(AUTH_HEADER, oauthHeader);
    }

    QNetworkReply *reply = oauthTwitter()->networkAccessManager()->get(req);
    connect(reply, SIGNAL(finished()), this, SLOT(reply()));
}

void QTweetSearch::startWithCustomQuery(const QByteArray &encodedQuery)
{
    QUrl url("https://api.twitter.com/1.1/search/tweets.json");

    //remove ?
    QByteArray query(encodedQuery);
    url.setEncodedQuery(query.remove(0, 1));

    QNetworkRequest req(url);

    QByteArray oauthHeader = oauthTwitter()->generateAuthorizationHeader(url, OAuth::GET);
    req.setRawHeader(AUTH_HEADER, oauthHeader);

    QNetworkReply *reply = oauthTwitter()->networkAccessManager()->get(req);
    connect(reply, SIGNAL(finished()), this, SLOT(reply()));
}

void QTweetSearch::parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg)
{
    if (ok) {
        QList<QTweetStatus> statuses  = QTweetConvert::searchVariantToStatusList(json);
        emit parsedPageResults(statuses);
    } else {
        qDebug() << "QTweetSearch parsing error: " << errorMsg;
        emit error(QTweetJsonError(errorMsg, json.toByteArray()));
    }
}
