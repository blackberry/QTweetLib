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
#include "RESTStatusUpdateMedia.h"
#include "qtweetstatus.h"
#include "qtweetgeocoord.h"
#include "qtweetconvert.h"

RESTStatusUpdateMedia::RESTStatusUpdateMedia(OAuthTwitter* oauthTwitter, QObject *parent) :
	RESTPhotoPost(oauthTwitter, parent)
{
}
/**
 *   Posts a tweet
 *   @param status text of the status update
 *   @param inReplyToStatus ID of a existing tweet is in reply to
 *   @param latLong latitude and longitude
 *   @param placeid a place in the world (use reverse geocoding)
 *   @param displayCoordinates whether or not to put a exact coordinates a tweet has been sent from
 */
void RESTStatusUpdateMedia::updateStatusWithMedia(const QString &status,
                              const QString &filePath,
                              qint64 inReplyToStatus,
                              const QTweetGeoCoord& latLong,
                              const QString &placeid,
                              bool displayCoordinates,
                              bool trimUser,
                              bool includeEntities)
{
	QHash<QString, QString> postParams;
    postParams.insert("status", status);

    if (inReplyToStatus != 0)
        postParams.insert("in_reply_to_status_id", QString::number(inReplyToStatus));

    if (latLong.isValid()) {
        postParams.insert("lat", QString::number(latLong.latitude()));
        postParams.insert("long", QString::number(latLong.longitude()));
    }

    if (!placeid.isEmpty()){
        postParams.insert("place_id", placeid);
    }

    if (displayCoordinates){
        postParams.insert("display_coordinates", "true");
    }

    if (trimUser){
        postParams.insert("trim_user", "true");
    }

    if (includeEntities){
        postParams.insert("include_entities", "true");
    }

    post(postParams, filePath);



}

void RESTStatusUpdateMedia::parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg)
{
    if (ok) {
        QTweetStatus status = QTweetConvert::variantMapToStatus(json.toMap());
        emit postedStatus(status);
    } else {
        qDebug() << "QTweetStatusUpdate JSON parser error: " << errorMsg;
        emit error(QTweetJsonError(errorMsg, json.toByteArray()));
    }
}

QString RESTStatusUpdateMedia::getMediaHeader(){
	return "media[]";
}

QString RESTStatusUpdateMedia::getEndpointUrl(){
    return "https://api.twitter.com/1.1/statuses/update_with_media.json";
}

