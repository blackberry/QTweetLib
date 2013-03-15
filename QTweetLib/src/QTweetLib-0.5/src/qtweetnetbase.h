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

#ifndef QTWEETNETBASE_H
#define QTWEETNETBASE_H

#include <QObject>
#include <QVariantMap>
#include <QByteArray>
#include "oauthtwitter.h"
#include "qtweetlib_global.h"
#include "qtweetneterror.h"

class QTweetStatus;
class QTweetUser;
class QTweetDMStatus;
class QTweetList;
class QTweetSearchResult;
class QTweetSearchPageResults;
class QTweetPlace;

/**
 *   Base class for Twitter API classes
 */
class QTWEETLIBSHARED_EXPORT QTweetNetBase : public QObject
{
    Q_OBJECT
    Q_PROPERTY(OAuthTwitter* oauthTwitter READ oauthTwitter WRITE setOAuthTwitter)
    Q_PROPERTY(bool jsonParsing READ isJsonParsingEnabled WRITE setJsonParsingEnabled)
    Q_PROPERTY(bool authenticaion READ isAuthenticationEnabled WRITE setAuthenticationEnabled)
public: 
    QTweetNetBase(QObject *parent = 0);
    QTweetNetBase(OAuthTwitter *oauthTwitter, QObject *parent = 0);
    virtual ~QTweetNetBase();

    void setOAuthTwitter(OAuthTwitter* oauthTwitter);
    OAuthTwitter* oauthTwitter() const;

    QByteArray userAgent() const { return m_userAgent.toLatin1(); }

    void setJsonParsingEnabled(bool enable);
    bool isJsonParsingEnabled() const;

    void setAuthenticationEnabled(bool enable);
    bool isAuthenticationEnabled() const;

    QByteArray response() const;

signals:
    /**
     *   Emited when fetching is finished, with or without errors.
     *   @param response contains the QNetworkReply's content.
     */
    void finished(const QByteArray& response);

    /** Emited when there is error preventing the normal operation
     *  to complete. This could be an HTTP error, a service error
     *  or even a json parsing error, if json parsing is enabled.
     *  @param error
     */
    void error(const QTweetNetError& error);

protected slots:
    virtual void parsingJsonFinished(const QVariant& json, bool ok, const QString& errorMsg) = 0;
    virtual void reply();

protected:
    void parseJson(const QByteArray& jsonData);

private:
    void init();
    OAuthTwitter *m_oauthTwitter;
    QByteArray m_response;
    bool m_jsonParsingEnabled;
    bool m_authentication;
    QString m_userAgent;
};

#endif // QTWEETNETBASE_H
