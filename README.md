QTweetLib v.0.5 originates from https://github.com/minimoog/QTweetLib

Overview:
===================
- Uses QJson library by Flavio Castelli for parsing JSON responses
- JSON parsing is done in multithreaded way using QThreadPool
- User Streams support is not fully completed (fetches responses correctly,
  JSON parsing is not full implemented)

Modifications:
=======================
- QTweetLib encapsulated in a Cascades™ for BlackBerry 10 project
- Calls to the Twitter API are made using HTTPS
- Calls to the Twitter API have been updated to 1.1 for rollover in March 2013
- New components with simliar design patterns to existing QTweetLib API calls have been added:
  - RESTAccountUpdateProfile: Call interface to:
    "https://api.twitter.com/1.1/account/update_profile.json"
  - RESTAccountProfileBanner: Call interface to:
    "https://api.twitter.com/1.1/account/update_profile_banner.json"
  - RESTAccountUpdateProfileImage: Call interface to:
    "https://api.twitter.com/1.1/account/update_profile_image.json"
  - RESTFollowersId: Call interface to:
    "https://api.twitter.com/1.1/followers/ids.json"
  - RESTFriendshipExists: Call interface to:
    "https://api.twitter.com/1/friendships/exists.json?"
  - RESTFriendshipLookup: Call interface to:
    "https://api.twitter.com/1.1/friendships/lookup.json"
  - RESTIsFriend: Call interface to:
    "https://api.twitter.com/1.1/friendships/lookup.json"
  - RESTLocalTrends: Call interface to:
    "https://api.twitter.com/1.1/trends/closest.json?"
  - RESTStatusUpdateMedia: Call interface to:
    "https://api.twitter.com/1.1/statuses/update_with_media.json"
  - RESTTrends: Call interface to:
    "https://api.twitter.com/1.1/trends/place.json?"
  - RESTUsersReportSpan: Call interface to:
    "https://api.twitter.com/1.1/users/report_spam.json"
  - RESTPhotoPost: Convenience class that uploads a photo to the Twitter server
  for the logged-in user.
  - RESTCustomGet: This class adds extra flexibility to the developer by allowing
  custom API calls to be made. It takes a QUrl in parameter and returns a
  QVariant in its callback. This mechanism could be used to make all Twitter
  API calls, however, the user must assemble the parameters himself/herself
  as well as disassemble the generic QVariant returned from the callback.

Requirements:
===============================
BlackBerry 10 Native SDK and Simulator: http://developer.blackberry.com/native/download/#blackberry10

Building:
==================================
1. Clone or download/extract this code locally
2. Start the SDK and click "File" > "Import" > "General" > "Existing Projects into Workspace"
3. Click "Browse" to "Select root directory:" and "Finish" to import.
4. From the "Project Explorer", right-click "QTweetLib" and select "Build-Configurations" > "Set Active" > "Device-Release"
5. From the "Project Explorer", right-click "QTweetLib" and select "Build Project"
6. The build output is QTweetLib/QTweetLib/arm/o.le-v7/libQTwLib05.so

Creating your own BlackBerry 10 app:
==================================
1. Start the SDK and click "File" > "New" > "Project" > "BlackBerry Project" > "Application" > "Cascades"
2. Click "Next" and select the "Template" for your app.
3. Click "Next" and enter your "Project name:" and other "Basic Settings"
4. Add required includes from QTweetLib to your project code.
5. Link to libQTwLib05.so in your bar-descriptor.
6. Develop and build your app using the SDK and Simulators or a BlackBerry 10 device.