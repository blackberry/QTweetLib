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
#include <QThreadPool>
#include <QNetworkReply>
#include "qtweetnetbase.h"
#include "qtweetstatus.h"
#include "qtweetdmstatus.h"
#include "qtweetuser.h"
#include "qtweetlist.h"
#include "qtweetsearchresult.h"
#include "qtweetsearchpageresults.h"
#include "qtweetplace.h"
#include "qjson/parserrunnable.h"
#include "qjson/parser.h"
#include <QDateTime>

/**
 *   Constructor
 */
QTweetNetBase::QTweetNetBase(QObject *parent) :
    QObject(parent), m_oauthTwitter(0), m_jsonParsingEnabled(true), m_authentication(true)
{
    init();
}

/**
 *   Constructor
 *   @param oauthTwitter OAuth Twitter
 *   @param parent QObject parent
 */
QTweetNetBase::QTweetNetBase(OAuthTwitter *oauthTwitter, QObject *parent) :
        QObject(parent), m_oauthTwitter(oauthTwitter), m_jsonParsingEnabled(true), m_authentication(true)
{
    init();
}

void QTweetNetBase::init()
{
    //m_userAgent = TwitterApp::instance().getUserAgent();
}

/**
 *  Desctructor
 */
QTweetNetBase::~QTweetNetBase()
{
}

/**
 *   Sets OAuth Twitter authorization object
 *   @param oauthTwitter OAuth Twitter object
 */
void QTweetNetBase::setOAuthTwitter(OAuthTwitter *oauthTwitter)
{
    m_oauthTwitter = oauthTwitter;
}

/**
 *   Gets OAuth Twitter authorization object
 *   @return OAuth Twitter object
 */
OAuthTwitter* QTweetNetBase::oauthTwitter() const
{
    return m_oauthTwitter;
}

/**
 *  Gets response
 */
QByteArray QTweetNetBase::response() const
{
    return m_response;
}

/**
 *  Enables/disables json parsing
 *  @remarks When disabled only finished and error signals are emitted
 */
void QTweetNetBase::setJsonParsingEnabled(bool enable)
{
    m_jsonParsingEnabled = enable;
}

/**
 *  Checks if its json parsing enabled
 */
bool QTweetNetBase::isJsonParsingEnabled() const
{
    return m_jsonParsingEnabled;
}

/**
 *  Enables/disables oauth authentication
 *  @remarks Most of classes requires authentication
 */
void QTweetNetBase::setAuthenticationEnabled(bool enable)
{
    m_authentication = enable;
}

/**
 *  Checks if authentication is enabled
 */
bool QTweetNetBase::isAuthenticationEnabled() const
{
    return m_authentication;
}

/**
 *  Parses json response
 */
void QTweetNetBase::parseJson(const QByteArray &jsonData)
{
    QJson::ParserRunnable *jsonParser = new QJson::ParserRunnable;
    jsonParser->setData(jsonData);

    connect(jsonParser, SIGNAL(parsingFinished(QVariant,bool,QString)),
            this, SLOT(parsingJsonFinished(QVariant,bool,QString)));

    QThreadPool::globalInstance()->start(jsonParser);
}

/**
 *  Called after response from twitter
 */
void QTweetNetBase::reply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    // prep m_response for finished() signal
    if (reply) {
    	m_response = reply->readAll();
    } else {
        m_response.clear();
    }

    // ALWAYS emit a finished signal no matter what happens
	emit finished(m_response);


	// now analyze the response
    if (reply) {

    	QString rateLimit(reply->rawHeader("X-Rate-Limit-Limit"));
    	QString rateRemaining(reply->rawHeader("X-Rate-Limit-Remaining"));
    	QString limitRest(reply->rawHeader("X-Rate-Limit-Reset"));

    	uint timeToReset = limitRest.toLongLong()- QDateTime::currentDateTime().toTime_t();

    	QString contentType(reply->rawHeader("content-type"));
    	bool contentTypeHasJson = contentType.contains("application/json", Qt::CaseInsensitive);

        if (reply->error() == QNetworkReply::NoError) {
        	if (isJsonParsingEnabled() && contentTypeHasJson) {
        		parseJson(m_response);
        	}
        } else {
            //dump error
            qDebug() << "Network error: " << reply->error();
            qDebug() << "Error string: " << reply->errorString();
            qDebug() << "Error response: " << m_response;

            //HTTP status code
            int httpStatus = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

            //prep error
            QTweetNetError* err = 0;

            if (!contentTypeHasJson) {
            	err = new QTweetHttpError(httpStatus, m_response);
            } else {
				//try to json parse the error response
				QJson::Parser parser;
				bool ok;
				QVariant json = parser.parse(m_response, &ok);
				QVariantMap errMsgMap = json.toMap();
				QMap<int, QString> twitterErrors;

				if (ok) {
					// here are a few sample responses we've seen:
					//{"request":"\/1\/users\/search.json?q=&per_page=20&page=1","error":"Client must provide a 'q' parameter with a value."}
					//{"error":"You must enter a query."}
					//{"errors":[{"message": "...", "code": 34}]}
					QList<QVariant> errors = errMsgMap["errors"].toList();
					QList<QVariant>::iterator it = errors.begin();

					while (it != errors.end()) {
						QVariantMap error = (*it).toMap();
						int errorCode = error["code"].toInt();
						QString errorMessage = error["message"].toString();

						twitterErrors[errorCode] = errorMessage;

						it++;
					}

					if (twitterErrors.size() > 0) {
						err = new QTweetServiceErrors(httpStatus, m_response, json, twitterErrors);
					} else {
						qDebug() << "Parsing json ok but twitter errors not found";
						err = new QTweetRawServiceError(httpStatus, m_response, json);
					}
				}
				else {
					qDebug() << "Unable to parse json in response";
					err = new QTweetHttpError(httpStatus, m_response);
				}
            }

            //finally emit the error signal
            if (err) {
            	emit error(*err);
            	err->deleteLater();
            } else {
            	Q_ASSERT(false);
            }
		}
        reply->deleteLater();
    }
}
