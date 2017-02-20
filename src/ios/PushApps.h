//
//  PushApps.h
//  PushApps
//
//  Created by Asaf Ron on 07/11/2016.
//  Copyright © 2016 PushApps. All rights reserved.
//

#import <UserNotifications/UserNotifications.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "PANotificationServiceExtension.h"
#import "PANotificationContentExtension.h"
#import "PATag.h"

#define SDK_VERSION @"1.0.16"

//! Project version number for PushApps.
FOUNDATION_EXPORT double PushAppsVersionNumber;

//! Project version string for PushApps.
FOUNDATION_EXPORT const unsigned char PushAppsVersionString[];

@protocol PushAppsDelegate <NSObject>

@optional
- (void)onDidRegisterToPushNotificationsWithDeviceToken:(NSString *)deviceToken;

@optional
- (void)onDidFailToRegisterToPushNotificationsWithError:(NSError *)error;

@optional
- (void)onDidReceiveRemoteNotificationWithInfo:(NSDictionary *)userInfo;

@end

// Notification click dictionary keys
extern NSString * const PANotificationKeySelectedArticle;

// Notification click identifiers
extern NSString * const PANotificationClickTypeNone;
extern NSString * const PANotificationClickTypeDefault;
extern NSString * const PANotificationClickTypeCancelled;
extern NSString * const PANotificationClickTypePollQuestion;
extern NSString * const PANotificationClickTypePollAnswer;
extern NSString * const PANotificationClickTypeActionButtonCustom;
extern NSString * const PANotificationClickTypeActionButtonReadArticle;
extern NSString * const PANotificationClickTypeActionButtonMoreRecommendations;

extern NSString * const PACategoryNotificationContent;
extern NSString * const PACategoryPollNotificationContent;
extern NSString * const PACategoryRecommendationsNotificationContent;

// In this header, you should import all the public headers of your framework using statements like #import <PushApps/PublicHeader.h>

typedef void (^PASimpleCompletionBlock)();

typedef void (^PANotificationClickHandlerBlock)(NSDictionary *contentInfo);

typedef void (^PACompletionBlock)(id object, NSError *error);

typedef void (^registerDeviceCompletion)(NSError *error);

typedef void (^setTokenCompletion)(NSError *error);

typedef void (^clickCompletion)(NSError *error);

typedef void (^eventCompletion)(NSError *error);

typedef void (^getWidgetFeedCompletion)(NSArray *articles, NSError *error);

typedef void (^getTagsCompletion)(NSArray *tags, NSError *error);

typedef void (^getCampaignDetailsCompletion)(NSDictionary *campaignDetails, NSError *error);

@interface PushApps : NSObject

@property (nonatomic, weak) id<PushAppsDelegate> delegate;
+ (void)setDelegate:(id<PushAppsDelegate>)delegate;

// check this flag to see if the Pushapps service is currently available
+ (BOOL)isPushAppsServiceAvailable;

// initialize push notifications for the application
+ (void)registerForPushNotifications:(NSDictionary *)launchOptions;

+ (void)enablePushNotifications;
+ (void)disablePushNotifications;

+ (BOOL)isRegisterForPushNotifications;

+ (NSString *)getDeviceId;

+ (NSString *)getPushToken;

+ (NSString *)getSdkVersion;

// register to the Pushapps service
+ (void)registerDeviceWithSdkKey:(NSString *)sdkKey andAppGroupsName:(NSString *)appGroupName;
+ (void)registerDeviceWithSdkKey:(NSString *)sdkKey andAppGroupsName:(NSString *)appGroupName withNotificationClickHandler:(PANotificationClickHandlerBlock)handler;

// send APNS device token to the Pushapps service
+ (void)setDevicePushToken:(NSData *)deviceToken;

+ (void)failedToRegisterToPushNotificationsWithError:(NSError *)error;

// handle user action. return YES if handles or NO if not a PushApps notification
+ (BOOL)handleNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(PASimpleCompletionBlock)completionHandler;

+ (void)handleReceivedNotification:(NSDictionary *)userInfo;

// report article view
+ (void)reportArticleView:(NSString *)articleUrl;

+ (void)getWidgetFeedForParams:(NSDictionary *)params withCompletionBlock:(PACompletionBlock)completion;

+ (void)handleOpenUrl:(NSURL *)url withOpenBrowserBlock:(PASimpleCompletionBlock)openBrowserBlock;

+ (void)addTag:(PATag *)tag;

+ (void)addTags:(NSArray *)tags;

+ (void)removeTag:(NSString *)tagName;

+ (void)removeTags:(NSArray *)tags;

+ (void)getTags:(PACompletionBlock)completion;

+ (NSString *)getUrlFromNotificationInfo:(NSDictionary *)userInfo;

+ (void)clearApplicationBadge;

+ (BOOL)payloadContainsPANotification:(NSDictionary *)payload;

// Outbrain
+ (void)setOutbrainKey:(NSString *)key;
+ (NSString *)getOutbrainKey;

// Logger
typedef NS_ENUM(NSUInteger, PA_LOG_LEVEL) {
    PA_LL_NONE, PA_LL_FATAL, PA_LL_ERROR, PA_LL_WARN, PA_LL_INFO, PA_LL_DEBUG, PA_LL_VERBOSE
};

+ (void)setLogLevel:(PA_LOG_LEVEL)logLevel visualLevel:(PA_LOG_LEVEL)visualLogLevel;
+ (void)pushapps_Log:(PA_LOG_LEVEL)logLevel message:(NSString *) message;

@end
