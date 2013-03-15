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

#ifndef QTWEETNETERROR_H
#define QTWEETNETERROR_H

#include <QObject>
#include <QVariant>
#include <QString>
#include <QMap>
#include <QByteArray>
#include "qtweetlib_global.h"
#include <bb/cascades/controls/ScrollPosition.h>

/**
 * Base class for QTweetNetBase errors.
 */
class QTWEETLIBSHARED_EXPORT QTweetNetError : public QObject
{

    Q_OBJECT

public:
    enum Type {
    	JsonParsing = 1,
		Http,
		ServiceRaw,
		ServiceErrors
	};

    Q_PROPERTY(Type type READ type CONSTANT FINAL);

    Type type() const { return m_type; }

public:
	virtual QString toString() const;

private:
    const Type m_type;

protected:
    QTweetNetError(Type type, QObject *parent = 0);
};

/**
 * Error emitted when a json parsing error occurs.
 */
class QTWEETLIBSHARED_EXPORT QTweetJsonError : public QTweetNetError
{

    Q_OBJECT

public:
    QTweetJsonError(const QString& error, const QByteArray& data = QByteArray(), QObject *parent = 0);

    Q_PROPERTY(QByteArray data READ data CONSTANT FINAL)
    Q_PROPERTY(QString error READ error CONSTANT FINAL);

    const QByteArray& data() const { return m_data; }
    const QString& error() const { return m_error; }

public:
	virtual QString toString() const;

private:
    const QByteArray m_data;
    const QString m_error;

};

/**
 * Error emitted when an HTTP error occurs
 *
 * Here are some documented cases, in the context of the Twitter service:
 *   JsonParsingError = 1,       - JSON parsing error
 *   UnknownError = 2,           - Unknown error
 *   NotModified = 304,          - There was no new data to return.
 *   BadRequest = 400,           - The request was invalid. This is the status code will be returned during rate limiting.
 *   Unauthorized = 401,         - Authentication credentials were missing or incorrect.
 *   Forbidden = 403,            - The request is understood, but it has been refused, due to update limits.
 *   NotFound = 404,             - The URI requested is invalid or the resource requested, such as a user, does not exists.
 *   NotAcceptable = 406,        - Returned by the Search API when an invalid format is specified in the request.
 *   EnhanceYourCalm = 420,      - Returned by the Search and Trends API when you are being rate limited.
 *   InternalServerError = 500,  - Something is broken in Twitter
 *   BadGateway = 502,           - Twitter is down or being upgraded.
 *   ServiceUnavailable = 503    - The Twitter servers are up, but overloaded with requests. Try again later.
 */
class QTWEETLIBSHARED_EXPORT QTweetHttpError : public QTweetNetError
{

    Q_OBJECT

public:
    QTweetHttpError(int status, const QByteArray& response, QObject *parent = 0);

    Q_PROPERTY(int status READ status CONSTANT FINAL);
	Q_PROPERTY(QByteArray response READ response CONSTANT FINAL);

	int status() const { return m_status; }
	const QByteArray& response() const { return m_response; }

private:
	const int m_status;
	const QByteArray m_response;

public:
	virtual QString toString() const;

protected:
    QTweetHttpError(int status, const QByteArray& response, QTweetNetError::Type type, QObject *parent = 0);
};

/**
 * Error emitted when an HTTP error occurs and the result's content-type is application/json
 */
class QTWEETLIBSHARED_EXPORT QTweetRawServiceError : public QTweetHttpError
{

    Q_OBJECT

public:
    QTweetRawServiceError(int httpStatus, const QByteArray& httpResponse, const QVariant& parsedJson, QObject *parent = 0);

    Q_PROPERTY(QVariant json READ json CONSTANT FINAL);

    const QVariant& json() const { return m_json; }

public:
	virtual QString toString() const;

private:
	const QVariant m_json;

protected:
	QTweetRawServiceError(int httpStatus, const QByteArray& httpResponse, const QVariant& parsedJson, QTweetNetError::Type type, QObject *parent = 0);
};

/**
 * Error emitted when an HTTP error occurs and the result's content-type is application/json
 * and we've successfully interpreted it as a specific error.
 */
class QTWEETLIBSHARED_EXPORT QTweetServiceErrors : public QTweetRawServiceError
{

    Q_OBJECT

public:
	typedef QMap<int, QString> QIntStringMap;

    QTweetServiceErrors(int httpStatus, const QByteArray& httpResponse, const QVariant& parsedJson, const QIntStringMap& serviceErrors, QObject *parent = 0);

    Q_PROPERTY(QIntStringMap errors READ errors CONSTANT FINAL);

    const QIntStringMap& errors() const { return m_errors; }

public:
	virtual QString toString() const;

private:
	const QIntStringMap m_errors;
};

#endif // QTWEETNETERROR_H
