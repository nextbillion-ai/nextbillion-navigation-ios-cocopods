#import <Foundation/Foundation.h>

/**
 Option set that defines truck types for route calculation.
 
 Multiple truck types can be combined using bitwise OR.
 This is effective only when `option=flexible` and `mode=truck`.
 */
typedef NS_OPTIONS(NSUInteger, NBTruckTypes) {
    
    /**
     Rigid truck - truck with fixed body and chassis
     */
    NBTruckTypesRigidTruck = (1 << 0),
    
    /**
     Semi-trailer - truck with detachable trailer
     */
    NBTruckTypesSemiTrailer = (1 << 1),
    
    /**
     B-double - truck with two trailers
     */
    NBTruckTypesBDouble = (1 << 2),
    
    /**
     Road train - truck with multiple trailers
     */
    NBTruckTypesRoadTrain = (1 << 3),
    
    /**
     Generic truck - unspecified truck type
     */
    NBTruckTypesGenericTruck = (1 << 4),
};

