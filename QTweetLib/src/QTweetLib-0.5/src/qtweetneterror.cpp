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

#include "qtweetneterror.h"
#include <QStringBuilder>


//
// QTweetNetError

QTweetNetError::QTweetNetError(QTweetNetError::Type type, QObject* parent)
: QObject(parent)
, m_type(type)
{
	// void
}

QString QTweetNetError::toString() const
{
	switch (m_type) {
	case JsonParsing:
		return "JsonParsing";
	case Http:
		return "Http";
	case ServiceRaw:
		return "ServiceRaw";
	case ServiceErrors:
		return "ServiceErrors";
	}

	return QString::number((int)m_type, 10);
}


//
// QTweetJsonError

QTweetJsonError::QTweetJsonError(const QString& error, const QByteArray& data, QObject* parent)
: QTweetNetError(QTweetNetError::JsonParsing, parent)
, m_data(data)
, m_error(error)
{
	// void
}

QString QTweetJsonError::toString() const
{
	QString retval;

	retval = "QTweetJsonError; error = \"" % m_error % "\"; data = \"" % QString(m_data.mid(0, 20));

	if (m_data.size() > 20) {
		retval = retval % "...";
	}
	retval = retval % "\"";

	return retval;
}

//
// QTweetHttpError

QTweetHttpError::QTweetHttpError(int status, const QByteArray& response, QObject* parent)
: QTweetNetError(QTweetNetError::Http, parent)
, m_status(status)
, m_response(response)
{
	// void
}

QTweetHttpError::QTweetHttpError(int status, const QByteArray& response, QTweetNetError::Type type, QObject *parent)
: QTweetNetError(type, parent)
, m_status(status)
, m_response(response)
{
	// void
}

QString QTweetHttpError::toString() const
{
	QString retval;

	retval = "QTweetHttpError; status = " % QString::number(m_status, 10) % "; response = \"" % QString(m_response.mid(0, 20));

	if (m_response.size() > 20) {
		retval = retval % "...";
	}
	retval = retval % "\"";

	return retval;
}


//
// QTweetRawServiceError

QTweetRawServiceError::QTweetRawServiceError(int httpStatus, const QByteArray& httpResponse, const QVariant& parsedJson, QObject *parent)
: QTweetHttpError(httpStatus, httpResponse, QTweetNetError::ServiceRaw, parent)
, m_json(parsedJson)
{
	// void
}

QTweetRawServiceError::QTweetRawServiceError(int httpStatus, const QByteArray& httpResponse, const QVariant& parsedJson, QTweetNetError::Type type, QObject *parent)
: QTweetHttpError(httpStatus, httpResponse, type, parent)
, m_json(parsedJson)
{
	// void
}

QString QTweetRawServiceError::toString() const
{
	QString retval;
	QByteArray rawJson = m_json.toByteArray(); 

	retval = "QTweetRawServiceError; status = " % QString::number(status(), 10) % "; json = \"" % QString(rawJson.mid(0, 20));

	if (rawJson.size() > 20) {
		retval = retval % "...";
	}
	retval = retval % "\"";

	return retval;
}


//
// QTweetServiceErrors

QTweetServiceErrors::QTweetServiceErrors(int httpStatus, const QByteArray& httpResponse, const QVariant& parsedJson, const QMap<int, QString>& serviceErrors, QObject *parent)
: QTweetRawServiceError(httpStatus, httpResponse, parsedJson, QTweetNetError::ServiceErrors, parent)
, m_errors(serviceErrors)
{
	// void
}

QString QTweetServiceErrors::toString() const
{
	QString retval;

	retval = "QTweetServiceErrors; status = " % QString::number(status(), 10) % "; errors = ";

	QIntStringMap::const_iterator it = m_errors.constBegin();

	while (it != m_errors.constEnd()) {
		retval = retval % QString::number(it.key(), 10) % ", \"" % it.value() % "\"";
		it++;
		if (it != m_errors.constEnd()) {
			retval = retval  % ", ";
		}
	}

	return retval;
}
