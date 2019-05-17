#ifndef SCORE_2019_H
#define SCORE_2019_H

#define SCORE_POINT_2019_NO_POINT                                         0

// CLASSIFY ATOMS
// the Atom is in the periodic table
#define SCORE_POINT_2019_ATOM_PERIODIC_TABLE                              1
// Bonus if the atom is classified (right color)
#define SCORE_POINT_2019_ATOM_PERIODIC_TABLE_CLASSIFIED_BONUS             5
// Bonus for the Goldenium on PERIODIC TABLE
#define SCORE_POINT_2019_GOLDENIUM_PERIODIC_TABLE_CLASSIFIED_BONUS        6

// WEIGHING_MACHINE
#define SCORE_POINT_2019_WEIGHING_MACHINE_REDIUM                          4
#define SCORE_POINT_2019_WEIGHING_MACHINE_GREENIUM                        8
#define SCORE_POINT_2019_WEIGHING_MACHINE_BLUEIUM                        12
#define SCORE_POINT_2019_WEIGHING_MACHINE_GOLDENIUM                      24

// SCALE -> FINAL SERIES
#define SCORE_POINT_2019_FINAL_SERIES_SCALE_MOST_HEAVY_ATOM_BONUS        30

// PERIODIC TABLE

// CHAOS : 2 redium, 1 greenium, 1 blueium + 1 redium / greenium from 
// Dropped in Redium Area
#define SCORE_POINT_2019_CHAOS_5_PUNK   (SCORE_POINT_2019_ATOM_PERIODIC_TABLE * 5 + SCORE_POINT_2019_ATOM_PERIODIC_TABLE_CLASSIFIED_BONUS * 2)

// ACCELERATOR
#define SCORE_POINT_2019_ADD_ATOM_ACCELERATOR                           10
#define SCORE_POINT_2019_LAUNCH_BLUIUM_IN_ACCELERATOR          SCORE_POINT_2019_ADD_ATOM_ACCELERATOR + 10
#define SCORE_POINT_2019_EXTRACT_GOLDENIUM                              20

// EXPERIENCE
#define SCORE_POINT_2019_EXPERIENCE_READY                                5
#define SCORE_POINT_2019_EXPERIENCE_ACTIVATED                           15
#define SCORE_POINT_2019_EXPERIENCE_OK                                  20
#define SCORE_POINT_2019_EXPERIENCE_ACTIVATED_AND_OK   (SCORE_POINT_2019_EXPERIENCE_ACTIVATED + SCORE_POINT_2019_EXPERIENCE_OK)

// BONUS
#define SCORE_POINT_2019_OUTSIDE_START_AREA                             10

#endif
