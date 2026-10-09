#import <Foundation/Foundation.h>
#include <stdint.h>

NS_ASSUME_NONNULL_BEGIN

typedef void (^VHRoutingProgressBlock)(NSInteger operation,
                                        NSInteger phaseOrdinal,
                                        int64_t nativeElapsedMs,
                                        NSInteger sequence,
                                        NSInteger attemptIndex);

@interface ValhallaBridge : NSObject

+ (nullable instancetype)initEngineWithConfig:(NSString *)configJson
                                        error:(NSError **)error;

- (BOOL)loadDataWithRoot:(NSString *)dataRoot
                   error:(NSError **)error;

- (BOOL)clearTileCacheWithError:(NSError **)error;
- (BOOL)invalidateRoutingDataWithError:(NSError **)error;

- (nullable NSString *)reclaimTileDiskIfBloatedWithError:(NSError **)error;
- (nullable NSString *)reclaimTileDiskSpaceWithError:(NSError **)error;

- (nullable NSString *)requestWithAction:(NSString *)action
                             payloadJson:(NSString *)payloadJson
                                   error:(NSError **)error;

- (nullable NSString *)requestWithAction:(NSString *)action
                             payloadJson:(NSString *)payloadJson
                                progress:(nullable VHRoutingProgressBlock)progress
                                   error:(NSError **)error;

/// Isolated offline Snap To Route entry point. This does not use the shared
/// route/reroute cancellation domain.
- (nullable NSString *)snapToRouteWithRequestJson:(NSString *)requestJson
                                     requestToken:(uint64_t)requestToken
                                            error:(NSError **)error;

/// Lock-free cooperative cancellation for requestToken and older Snap calls.
- (BOOL)cancelSnapToRouteWithRequestToken:(uint64_t)requestToken
                                    error:(NSError **)error;

- (nullable NSString *)rerouteToOriginalRouteWithPayloadJson:(NSString *)payloadJson
                                                       error:(NSError **)error;

- (nullable NSString *)rerouteToOriginalRouteWithPayloadJson:(NSString *)payloadJson
                                                     progress:(nullable VHRoutingProgressBlock)progress
                                                        error:(NSError **)error;

- (BOOL)cancelRerouteWithError:(NSError **)error;
- (BOOL)clearRerouteCancelWithError:(NSError **)error;
- (BOOL)cancelRoutingWithError:(NSError **)error;
- (BOOL)clearRoutingCancelWithError:(NSError **)error;

- (nullable NSString *)verifyRouteCorridorWithOriginLat:(double)originLat
                                              originLon:(double)originLon
                                                 destLat:(double)destLat
                                                 destLon:(double)destLon
                                              bufferDeg:(double)bufferDeg
                                                  error:(NSError **)error;

- (nullable NSString *)healthCheckWithError:(NSError **)error;

- (nullable NSString *)syncRegionListWithRegionsApiBase:(NSString *)regionsApiBase
                                               syncMode:(NSString *)syncMode
                                                  error:(NSError **)error;

- (nullable NSDictionary *)listRegionCountriesWithError:(NSError **)error;

- (nullable NSDictionary *)listRegionsWithCountries:(nullable NSArray<NSString *> *)countries
                                              error:(NSError **)error;

- (nullable NSString *)queryCountiesWithRegionsApiBase:(NSString *)regionsApiBase
                                           requestJson:(NSString *)requestJson
                                                 error:(NSError **)error;

- (void)cancelCountyQuery;

typedef void (^VHRegionDownloadProgressBlock)(int64_t regionId,
                                              NSInteger phase,
                                              NSInteger tilesDone,
                                              NSInteger tilesTotal,
                                              NSInteger percent);

- (nullable NSString *)prefetchRegionTilesWithRegionId:(int64_t)regionId
                                        regionsApiBase:(NSString *)regionsApiBase
                                           tilesApiBase:(NSString *)tilesApiBase
                                     requestTimestampMs:(int64_t)requestTimestampMs
                                               progress:(nullable VHRegionDownloadProgressBlock)progress
                                                 error:(NSError **)error;

- (nullable NSString *)deleteRegionDataWithRegionId:(int64_t)regionId error:(NSError **)error;
- (nullable NSString *)pauseRegionDownloadWithRegionId:(int64_t)regionId error:(NSError **)error;
- (nullable NSString *)cancelRegionDownloadWithRegionId:(int64_t)regionId error:(NSError **)error;

- (nullable NSString *)fetchRegionDetailWithRegionId:(int64_t)regionId
                                      regionsApiBase:(NSString *)regionsApiBase
                                               error:(NSError **)error;

- (nullable NSString *)getRegionBoundaryWithRegionId:(int64_t)regionId
                                               error:(NSError **)error;

- (nullable NSString *)getInstalledRegionCoverageBoundsWithError:(NSError **)error;

- (void)shutdown;

+ (nullable NSString *)buildConfigWithTileExtract:(NSString *)tileExtractPath
                                          tileDir:(NSString *)tileDirPath;

+ (NSString *)sdkVersion;
+ (NSString *)engineVersion;
+ (NSString *)nativeBuildVersion;

@end

NS_ASSUME_NONNULL_END
