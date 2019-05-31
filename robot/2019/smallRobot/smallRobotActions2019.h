#ifndef SMALL_ROBOT_ACTIONS_2019_H
#define SMALL_ROBOT_ACTIONS_2019_H

#include <stdbool.h>

// ACCELERATOR

bool acceleratorArmOn(int* context);

bool acceleratorRotationIfNeeded(int* context);

bool acceleratorArmOff(int* context);

// GOLDENIUM

bool goldeniumPrepareTake(int* context);

bool goldeniumTake(int* context);

bool goldeniumPrepareDrop(int* context);

bool goldeniumDrop(int* context);

// SMALL DISTRIBUTOR

bool smallDistributorLinePrepare(int* context);

bool smallDistributorLineTake(int* context);

bool smallDistributorAcceleratorDrop(int* context);

// BIG DISTRIBUTOR LINE 3

bool bigDistributorLine3Prepare(int* context);

bool bigDistributorLine3Take(int* context);

bool bigDistributorLine3Drop(int* context);

// BIG DISTRIBUTOR LINE 2

bool bigDistributorLine2Prepare(int* context);

bool bigDistributorLine2Take(int* context);

bool bigDistributorLine2Drop(int* context);

#endif

