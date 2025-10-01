#import <Foundation/Foundation.h>

#pragma mark - Specifying the Routing Profile

typedef NSString * NBNavigationMode NS_EXTENSIBLE_STRING_ENUM;

extern NBNavigationMode const NBNavigationModeCar;
//extern NBNavigationMode const NBNavigationModeAuto;
extern NBNavigationMode const NBNavigationModeBike;
extern NBNavigationMode const NBNavigationModeMotocycle;
//extern NBNavigationMode const NBNavigationMode4W;
//extern NBNavigationMode const NBNavigationMode2W;
extern NBNavigationMode const NBNavigationModeTruck;


typedef NSString * NBMapOption NS_EXTENSIBLE_STRING_ENUM;

extern NBMapOption const NBMapOptionValhalla __attribute__((deprecated("Use NBMapOptionFlexible instead.")));
extern NBMapOption const NBMapOptionFlexible;
extern NBMapOption const NBMapOptionNone;

typedef NSString * NBNavigationRouteType NS_EXTENSIBLE_STRING_ENUM;

extern NBNavigationRouteType const NBNavigationRouteTypeFastest;
extern NBNavigationRouteType const NBNavigationRouteTypeShortest;


typedef NSString * NBNavigationRoadInfo NS_EXTENSIBLE_STRING_ENUM;

extern NBNavigationRoadInfo const NBNavigationRoadInfoMaxSpeed;
