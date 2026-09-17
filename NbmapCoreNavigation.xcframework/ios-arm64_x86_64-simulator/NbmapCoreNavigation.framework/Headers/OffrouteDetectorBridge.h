#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, NBOffrouteDetectorRouteHint) {
    NBOffrouteDetectorRouteHintUncertain = 0,
    NBOffrouteDetectorRouteHintCity = 1,
    NBOffrouteDetectorRouteHintHighway = 2
};

typedef NS_ENUM(NSInteger, NBOffrouteDetectorPuckState) {
    NBOffrouteDetectorPuckStateRaw = 0,
    NBOffrouteDetectorPuckStateSnapped = 1
};

typedef NS_ENUM(NSInteger, NBOffrouteDetectorStepAdjustmentAction) {
    NBOffrouteDetectorStepAdjustmentActionMaintain = 0,
    NBOffrouteDetectorStepAdjustmentActionAdvance = 1,
    NBOffrouteDetectorStepAdjustmentActionRollback = 2
};

typedef NS_ENUM(NSInteger, NBOffrouteDetectorConfigMode) {
    NBOffrouteDetectorConfigModeCity = 0,
    NBOffrouteDetectorConfigModeHighway = 1
};

@interface NBOffrouteDetectorDecision : NSObject
@property(nonatomic, assign) NBOffrouteDetectorPuckState puckState;
@property(nonatomic, assign) BOOL drHold;
@property(nonatomic, assign) BOOL offroute;
@property(nonatomic, assign) BOOL wrongWay;
@property(nonatomic, assign) BOOL junction90;
@property(nonatomic, assign) BOOL reroute;
@property(nonatomic, assign) BOOL requestParallelCheck;
@property(nonatomic, copy) NSString *reason;
@property(nonatomic, copy) NSString *rerouteReason;
@end

@interface NBOffrouteDetectorMatchResult : NSObject
@property(nonatomic, assign) BOOL valid;
@property(nonatomic, assign) BOOL sameRoute;
@property(nonatomic, assign) double meanDistance;
@property(nonatomic, assign) double p90Distance;
@end

@interface NBOffrouteDetectorStepAdjustment : NSObject
@property(nonatomic, assign) BOOL valid;
@property(nonatomic, assign) NBOffrouteDetectorStepAdjustmentAction action;
@property(nonatomic, assign) double confidence;
@property(nonatomic, copy) NSString *reason;
@end

@interface NBOffrouteDetectorBridge : NSObject

- (instancetype)init;
- (void)updateRouteHint:(NBOffrouteDetectorRouteHint)routeHint routeChanged:(BOOL)routeChanged;
- (void)updateParallelRoadConfigEnabled:(BOOL)enabled
             observationDistanceThreshold:(double)observationDistanceThreshold
             observationExitDistanceThreshold:(double)observationExitDistanceThreshold
                         observationHoldSeconds:(double)observationHoldSeconds
                           requestIntervalSeconds:(double)requestIntervalSeconds
                                  rerouteReason:(nullable NSString *)rerouteReason
                        useDistanceTrendDetector:(BOOL)useDistanceTrendDetector
                                    distanceFloor:(double)distanceFloor
                            minDeltaFromBaseline:(double)minDeltaFromBaseline
                             plateauStdThreshold:(double)plateauStdThreshold
                            plateauConfirmSeconds:(double)plateauConfirmSeconds
                        plateauConfirmSecondsFast:(double)plateauConfirmSecondsFast
                          suddenSlopeThresholdMps:(double)suddenSlopeThresholdMps
                             trackerWindowSeconds:(double)trackerWindowSeconds
                               shortWindowSeconds:(double)shortWindowSeconds
                      absoluteElevatedThreshold:(double)absoluteElevatedThreshold;
- (void)updateParallelRoadObservationWithResultReady:(BOOL)resultReady
                                           sameRoute:(BOOL)sameRoute
                                     requestInFlight:(BOOL)requestInFlight;
- (NBOffrouteDetectorMatchResult *)evaluateParallelRoadMatchWithSnappedPath:(NSString *)snappedPath
                                                                   routePath:(NSString *)routePath
                                                                nearLatitude:(double)nearLatitude
                                                               nearLongitude:(double)nearLongitude
                                                          segmentTotalLength:(double)segmentTotalLength
                                                           mismatchThreshold:(double)mismatchThreshold
                                                        minComparableLength:(double)minComparableLength;
- (void)resetEngineState;
- (void)resetEngineStateForReroute;
- (void)beginRerouteRecovery;
- (void)setRawFarFallbackStartTimeForTesting:(double)value;
- (NBOffrouteDetectorConfigMode)currentConfigMode;
- (double)currentConfigConfidence;
- (nullable NBOffrouteDetectorStepAdjustment *)suggestStepAdjustmentWithTimestamp:(double)timestamp
                                                                         latitude:(double)latitude
                                                                        longitude:(double)longitude
                                                                            speed:(double)speed
                                                                          heading:(double)heading
                                                                              cep:(double)cep
                                                                               dr:(BOOL)dr
                                                                         distance:(double)distance
                                                                            theta:(double)theta
                                                                             sdot:(double)sdot
                                                                         parallel:(BOOL)parallel
                                                                              zOK:(BOOL)zOK
                                                                   hasCurrentStep:(BOOL)hasCurrentStep
                                                                  hasUpcomingStep:(BOOL)hasUpcomingStep
                                                                  hasPreviousStep:(BOOL)hasPreviousStep
                                                                distToCurrentStep:(double)distToCurrentStep
                                                               distToUpcomingStep:(double)distToUpcomingStep
                                                               distToPreviousStep:(double)distToPreviousStep
                                                            currentInitialHeading:(double)currentInitialHeading
                                                              currentFinalHeading:(double)currentFinalHeading
                                                           upcomingInitialHeading:(double)upcomingInitialHeading
                                                             upcomingFinalHeading:(double)upcomingFinalHeading
                                                           previousInitialHeading:(double)previousInitialHeading
                                                             previousFinalHeading:(double)previousFinalHeading
                                                                   currentIsUTurn:(BOOL)currentIsUTurn
                                                                  upcomingIsUTurn:(BOOL)upcomingIsUTurn
                                                                  previousIsUTurn:(BOOL)previousIsUTurn
                                                     distanceRemainingToManeuver:(double)distanceRemainingToManeuver
                                                                           cepGate:(double)cepGate
                                                                        vGateStart:(double)vGateStart
                                                              isInitialCalibration:(BOOL)isInitialCalibration;

- (NBOffrouteDetectorDecision *)decideWithTimestamp:(double)timestamp
                                           latitude:(double)latitude
                                          longitude:(double)longitude
                                              speed:(double)speed
                                            heading:(double)heading
                                                cep:(double)cep
                                                 dr:(BOOL)dr
                                           distance:(double)distance
                                              theta:(double)theta
                                               sdot:(double)sdot
                                           parallel:(BOOL)parallel
                                                zOK:(BOOL)zOK;

@end

NS_ASSUME_NONNULL_END
