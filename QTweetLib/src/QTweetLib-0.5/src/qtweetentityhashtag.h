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

#ifndef QTWEETENTITYHASHTAG_H
#define QTWEETENTITYHASHTAG_H

#include <QSharedDataPointer>
#include "qtweetlib_global.h"

class QTweetEntityHashtagData;

class QTWEETLIBSHARED_EXPORT QTweetEntityHashtag
{

public:
    QTweetEntityHashtag();
    QTweetEntityHashtag(const QTweetEntityHashtag &);
    QTweetEntityHashtag &operator=(const QTweetEntityHashtag &);
    ~QTweetEntityHashtag();

    void setText(const QString& text);
    QString text() const;

    bool operator==(const QTweetEntityHashtag& right);
private:
    QSharedDataPointer<QTweetEntityHashtagData> data;
};

#endif // QTWEETENTITYHASHTAG_H
