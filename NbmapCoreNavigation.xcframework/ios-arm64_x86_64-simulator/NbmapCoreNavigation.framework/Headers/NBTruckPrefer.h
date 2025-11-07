#import <Foundation/Foundation.h>

/**
 Specifies routing preferences for truck navigation.
 
 This is effective only when `option=flexible` and `mode=truck`.
 */
typedef NS_ENUM(NSUInteger, NBTruckPrefer) {
    
    /**
     No preference specified.
     */
    NBTruckPreferNone = 0,
    
    /**
     Prioritize truck-friendly roads when calculating routes.
     This aims to maximize the inclusion of truck-suitable roads in the final route.
     
     When this is set, the `truckType` parameter becomes effective.
     */
    NBTruckPreferTruckRoute = 1,
};

