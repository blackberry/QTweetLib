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

#ifndef QTWEETSEARCH_H
#define QTWEETSEARCH_H

#include "qtweetnetbase.h"
#include <QDate>

class QTweetStatus;

/**
 *  Gets tweets that match a specified query
 */
class QTWEETLIBSHARED_EXPORT QTweetSearch : public QTweetNetBase
{
    Q_OBJECT
public:

    enum Result_Type{
        mixed,recent,popular
    };

    QTweetSearch(QObject *parent = 0);
    QTweetSearch(OAuthTwitter *oauthTwitter, QObject *parent = 0);
    void start( const QString &query,
                const QString &lang = QString(),
                const QString &geocode = QString(),
                const QString &locale = QString(),
                const Result_Type result_type = mixed,
                int count = 0,
                const QDate &until = QDate(),
                qint64 sinceid = 0,
                qint64 maxid = 0
               );
    void startWithCustomQuery(const QByteArray& encodedQuery);

signals:
    /** Emits page of search results */
    void parsedPageResults(const QList<QTweetStatus>& statuses);

protected slots:
    void parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg);
};

#endif // QTWEETSEARCH_H
