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

#ifndef QTWEETCONVERT_H
#define QTWEETCONVERT_H

#include <QVariant>
#include "qtweetlib_global.h"

class QTweetStatus;
class QTweetUser;
class QTweetDMStatus;
class QTweetList;
class QTweetSearchResult;
class QTweetSearchPageResults;
class QTweetPlace;
class QTweetEntityUrl;
class QTweetEntityHashtag;
class QTweetEntityUserMentions;
class QTweetEntityMedia;

/**
 *  Contains static converting functions
 */
class QTWEETLIBSHARED_EXPORT QTweetConvert
{
public:
    enum ProfileImageSize{
    	normal, bigger, mini, original
    };
    static QString normalizeString(const QString& str, const QString& suffix);
    static QString convertProfileImageSizeUrl(const QString& profileImageUrl, ProfileImageSize sizeFormat);
    static QList<QTweetStatus> variantToStatusList(const QVariant& fromParser);
    static QTweetStatus variantMapToStatus(const QVariantMap& var);
    static QTweetEntityMedia varMapToEntityMedia(const QVariantMap &varMap);
    static QTweetUser variantMapToUserInfo(const QVariantMap& var);
    static QList<QTweetDMStatus> variantToDirectMessagesList(const QVariant& fromParser);
    static QTweetDMStatus variantMapToDirectMessage(const QVariantMap& var);
    static QTweetList variantMapToTweetList(const QVariantMap& var);
    static QList<QTweetUser> variantToUserInfoList(const QVariant& fromParser);
    static QList<QTweetList> variantToTweetLists(const QVariant& var);
    static QTweetSearchResult variantMapToSearchResult(const QVariantMap& var);
    static QTweetSearchPageResults variantToSearchPageResults(const QVariant& var);
    static QTweetPlace variantMapToPlace(const QVariantMap& var);
    static QTweetPlace variantMapToPlaceRecursive(const QVariantMap& var);
    static QList<QTweetPlace> variantToPlaceList(const QVariant& fromParser);
    static QTweetEntityUrl variantMapToEntityUrl(const QVariantMap& var);
    static QTweetEntityHashtag variantMapToEntityHashtag(const QVariantMap& var);
    static QTweetEntityUserMentions variantMapToEntityUserMentions(const QVariantMap& var);
    static QList<QTweetStatus> searchVariantToStatusList(const QVariant &fromParser);
};

#endif // QTWEETCONVERT_H
