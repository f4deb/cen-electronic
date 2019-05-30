#ifndef BIG_ROBOT_LOCATION_2019_H
#define BIG_ROBOT_LOCATION_2019_H

// Start Area
#define BIG_ROBOT_START_AREA                                                "BSTA"
#define BIG_ROBOT_START_AREA_LABEL                                          "Big Robot Start"
#define BIG_ROBOT_START_AREA_X                                                 800
#define BIG_ROBOT_START_AREA_Y                                                 152
#define BIG_ROBOT_START_AREA_ANGLE_DECI_DEG                                      0

// Chaos Zone Front
#define CHAOS_ZONE_FRONT                                                   "CZFR"
#define CHAOS_ZONE_FRONT_LABEL                                             "Chaos Zone Front"
#define CHAOS_ZONE_FRONT_X                                                  1250
#define CHAOS_ZONE_FRONT_Y                                                  1150
#define CHAOS_ZONE_FRONT_ANGLE_DECI_DEG                        ANGLE_DECI_DEG_135

// Redium Drop Zone
#define REDIUM_DROP_ZONE                                                   "RDRZ"
#define REDIUM_DROP_ZONE_LABEL                                             "Redium Drop Zone"
#define REDIUM_DROP_ZONE_X                                                   550
#define REDIUM_DROP_ZONE_Y                                                   350
#define REDIUM_DROP_ZONE_ANGLE_DECI_DEG                       ANGLE_DECI_DEG_225


// Key Point 1 to be able to go from BigDistributor to Accelerator Drop Zone
#define KEY_POINT_1                                                        "KEP1"
#define KEY_POINT_1_LABEL                                                  "Key Point 1"
#define KEY_POINT_1_X                                                       800
#define KEY_POINT_1_Y                                                       1500
#define KEY_POINT_1_FROM_ACCERATOR_ANGLE_DECI_DEG                           ANGLE_DECI_DEG_180
#define KEY_POINT_1_FROM_REDIUM_DROP_ZONE_ANGLE_DECI_DEG                    ANGLE_DECI_DEG_270
#define KEY_POINT_1_FROM_DISTRIBUTOR_ANGLE_DECI_DEG                         ANGLE_DECI_DEG_0
#define KEY_POINT_1_TO_ACCERATOR_ANGLE_DECI_DEG                             ANGLE_DECI_DEG_180
#define KEY_POINT_1_TO_REDIUM_DROP_ZONE_ANGLE_DECI_DEG                      ANGLE_DECI_DEG_270
#define KEY_POINT_1_TO_DISTRIBUTOR_ANGLE_DECI_DEG                           ANGLE_DECI_DEG_0

// Key point to be able to do a transition from REDIUM_DROP_ZONE then to
// go on BIG_DISTRIBUTOR_LINE_1 or BIG_DISTRIBUTOR_LINE_2
#define KEY_POINT_2                                                        "KEP2"
#define KEY_POINT_2_LABEL                                                  "Key Point 2"
#define KEY_POINT_2_X                                                        900
#define KEY_POINT_2_Y                                                        700
#define KEY_POINT_2_ANGLE_DECI_DEG                            -ANGLE_DECI_DEG_135
#define KEY_POINT_2_FROM_REDIUM_ZONE_ANGLE_DECI_DEG           -ANGLE_DECI_DEG_135
#define KEY_POINT_2_TO_DISTRIBUTOR_ANGLE_DECI_DEG               ANGLE_DECI_DEG_0
#define KEY_POINT_2_FROM_DISTRIBUTOR_ANGLE_DECI_DEG             ANGLE_DECI_DEG_0

#define BLUEIUM_GREENIUM_POINT                                              "BRCP"
#define BLUEIUM_GREENIUM_POINT_LABEL                                         "Blueium Redium Center Point"
#define BLUEIUM_GREENIUM_POINT_X                                             900
#define BLUEIUM_GREENIUM_POINT_Y                                             200
#define BLUEIUM_GREENIUM_ANGLE_DECI_DEG                                       90




#endif
