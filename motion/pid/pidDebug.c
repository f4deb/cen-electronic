#include "pidDebug.h"

#include "instructionType.h"
#include "motionInstruction.h"
#include "pid.h"
#include "pidMotion.h"
#include "../extended/bsplineDebug.h"

#include "../../common/commons.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

// PID MOTION INSTRUCTION
#define PID_DEBUG_INDEX_COLUMN_LENGTH						4
#define PID_DEBUG_INSTRUCTION_TYPE_COLUMN_LENGTH			6
#define PID_DEBUG_A_COLUMN_LENGTH							3
#define PID_DEBUG_SPEED_COLUMN_LENGTH						3
#define PID_DEBUG_SPEED_MAX_COLUMN_LENGTH					5
#define PID_DEBUG_T1_COLUMN_LENGTH							4
#define PID_DEBUG_T2_COLUMN_LENGTH							4
#define PID_DEBUG_T3_COLUMN_LENGTH							4
#define PID_DEBUG_P1_COLUMN_LENGTH							6
#define PID_DEBUG_P2_COLUMN_LENGTH							6
#define PID_DEBUG_NEXT_POSITION_COLUMN_LENGTH				6
#define PID_DEBUG_PROFILE_TYPE_COLUMN_LENGTH				8
#define PID_DEBUG_MOTION_PARAMETER_TYPE_COLUMN_LENGTH		15
#define PID_DEBUG_PID_TYPE_COLUMN_LENGTH		            10
#define PID_DEBUG_LAST_COLUMN_LENGTH		                0

/**
* Private.
*/
void printMotionInstructionHeader(OutputStream* outputStream, PidMotion* pidMotion) {
	println(outputStream);
	appendStringAndDec(outputStream, "readIndex=", pidMotion->readIndex);
	appendStringAndDec(outputStream, ", writeIndex=", pidMotion->writeIndex);
	appendStringAndDec(outputStream, ", length=", pidMotion->length);
	appendStringAndBool(outputStream, ", stackMotionDefinitions=", pidMotion->stackMotionDefinitions);
	appendStringAndBool(outputStream, ", mustReachPosition=", pidMotion->mustReachPosition);
	appendStringAndBool(outputStream, ", rollingTestMode=", pidMotion->rollingTestMode);
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "Idx", PID_DEBUG_INDEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "T/A", PID_DEBUG_INSTRUCTION_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "a", PID_DEBUG_A_COLUMN_LENGTH);
	appendStringHeader(outputStream, "s", PID_DEBUG_SPEED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "sMax", PID_DEBUG_SPEED_MAX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "t1", PID_DEBUG_T1_COLUMN_LENGTH);
	appendStringHeader(outputStream, "t2", PID_DEBUG_T2_COLUMN_LENGTH);
	appendStringHeader(outputStream, "t3", PID_DEBUG_T3_COLUMN_LENGTH);
	appendStringHeader(outputStream, "p1", PID_DEBUG_P1_COLUMN_LENGTH);
	appendStringHeader(outputStream, "p2", PID_DEBUG_P2_COLUMN_LENGTH);
	appendStringHeader(outputStream, "p3", PID_DEBUG_NEXT_POSITION_COLUMN_LENGTH);
	appendStringHeader(outputStream, "profile", PID_DEBUG_PROFILE_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "motionParamType", PID_DEBUG_MOTION_PARAMETER_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "pidType", PID_DEBUG_PID_TYPE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);
}

void printMotionInstructionLine(OutputStream* outputStream, PidMotion* pidMotion, int index, enum InstructionType instructionType, MotionInstruction* motionInstruction) {
	appendDecTableData(outputStream, index, PID_DEBUG_INDEX_COLUMN_LENGTH);
	addInstructionTypeTableData(outputStream, instructionType, PID_DEBUG_INSTRUCTION_TYPE_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) motionInstruction->a, PID_DEBUG_A_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) motionInstruction->speed, PID_DEBUG_SPEED_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) motionInstruction->speedMax, PID_DEBUG_SPEED_MAX_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) motionInstruction->t1, PID_DEBUG_T1_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) motionInstruction->t2, PID_DEBUG_T2_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) motionInstruction->t3, PID_DEBUG_T3_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) motionInstruction->p1, PID_DEBUG_P1_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) motionInstruction->p2, PID_DEBUG_P2_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) motionInstruction->nextPosition, PID_DEBUG_NEXT_POSITION_COLUMN_LENGTH);
	addMotionProfileTypeTableData(outputStream, motionInstruction->profileType, PID_DEBUG_PROFILE_TYPE_COLUMN_LENGTH);
	addMotionParameterTypeTableData(outputStream, motionInstruction->motionParameterType, PID_DEBUG_MOTION_PARAMETER_TYPE_COLUMN_LENGTH);
	addPidTypeTableData(outputStream, motionInstruction->pidType, PID_DEBUG_PID_TYPE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_LAST_COLUMN_LENGTH);
}

void printMotionInstructionTable(OutputStream* outputStream, PidMotion* pidMotion) {
	enum PidMotionType currentPidMotionType = MOTION_TYPE_UNDEFINED;
	bool firstSeparator = true;
	unsigned int i;
	unsigned int count = getPidMotionElementsCount(pidMotion);
	for (i = 0; i < count; i++) {
		PidMotionDefinition* pidMotionDefinition = getMotionDefinition(pidMotion, i);

		// Header Management
		if (currentPidMotionType != pidMotionDefinition->motionType) {
			currentPidMotionType = pidMotionDefinition->motionType;
			if (!firstSeparator) {
				appendTableHeaderSeparatorLine(outputStream);
			}
			firstSeparator = false;
			switch (currentPidMotionType) {
				case MOTION_TYPE_NORMAL: {
					printMotionInstructionHeader(outputStream, pidMotion);
					break;
				}
				case MOTION_TYPE_BSPLINE: {
					appendTableHeaderSeparatorLine(outputStream);
					writeBSplineDefinitionTableHeader(outputStream);
					break;
				}
				case MOTION_TYPE_UNDEFINED:
					break;
			}
		}
		// Content
		switch (currentPidMotionType) {
		case MOTION_TYPE_NORMAL: {
			MotionInstruction* theta = &(pidMotionDefinition->inst[THETA]);
			printMotionInstructionLine(outputStream, pidMotion, i, THETA, theta);
			MotionInstruction* alpha = &(pidMotionDefinition->inst[ALPHA]);
			printMotionInstructionLine(outputStream, pidMotion, i, ALPHA, alpha);
			appendTableHeaderSeparatorLine(outputStream);
			break;
		}
		case MOTION_TYPE_BSPLINE: {
			writeBSplineDefinitionRow(outputStream, i, &(pidMotionDefinition->curve));
			break;
		}
		case MOTION_TYPE_UNDEFINED:
			break;
		}
	}
}

// PID DEBUG DATA

#define PID_DEBUG_DATA_INSTRUCTION_TYPE_COLUMN_LENGTH                     10
#define PID_DEBUG_DATA_PID_TIME_COLUMN_LENGTH                             8
#define PID_DEBUG_DATA_PID_TYPE_TYPE_COLUMN_LENGTH                        8
#define PID_DEBUG_DATA_NORMAL_POSITION_COLUMN_LENGTH                      10
#define PID_DEBUG_DATA_POSITION_COLUMN_LENGTH                             8
#define PID_DEBUG_DATA_ERROR_COLUMN_LENGTH                                5
#define PID_DEBUG_DATA_U_COLUMN_LENGTH                                    4
#define PID_DEBUG_DATA_MOTION_END_INTEGRAL_TIME_COLUMN_LENGTH             17
#define PID_DEBUG_DATA_MOTION_END_ABS_DELTA_POSITION_INT_COLUMN_LENGTH    17
#define PID_DEBUG_DATA_MOTION_END_ABS_INTEGRAL_COLUMN_LENGTH              17
#define PID_DEBUG_DATA_LAST_COLUMN_LENGTH_COLUMN_LENGTH		            0


/**
* Private.
*/
void printDebugDataHeader(OutputStream* outputStream) {
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "Inst Type", PID_DEBUG_DATA_INSTRUCTION_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Pid Time", PID_DEBUG_DATA_PID_TIME_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Pid Type", PID_DEBUG_DATA_PID_TYPE_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Normal Pos", PID_DEBUG_DATA_NORMAL_POSITION_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Position", PID_DEBUG_DATA_POSITION_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Error", PID_DEBUG_DATA_ERROR_COLUMN_LENGTH);
	appendStringHeader(outputStream, "U", PID_DEBUG_DATA_U_COLUMN_LENGTH);
	appendStringHeader(outputStream, "End Integral Time", PID_DEBUG_DATA_MOTION_END_INTEGRAL_TIME_COLUMN_LENGTH);
	appendStringHeader(outputStream, "End Abs Delta Pos", PID_DEBUG_DATA_MOTION_END_ABS_DELTA_POSITION_INT_COLUMN_LENGTH);
	appendStringHeader(outputStream, "End Abs Integral", PID_DEBUG_DATA_MOTION_END_ABS_INTEGRAL_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_DATA_LAST_COLUMN_LENGTH_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);
}


/**
 * Print a line of data for a specific Instruction Type
 */
void printDebugDataInstructionTypeLine(OutputStream* outputStream, PidMotion* pidMotion, enum InstructionType instructionType) {
    PidComputationValues* computationValues = &(pidMotion->computationValues);
    PidMotionDefinition* motionDefinition = pidMotionGetCurrentMotionDefinition(pidMotion);
    MotionInstruction motionInstruction = motionDefinition->inst[instructionType];
    PidMotionError* localError = &(computationValues->errors[instructionType]);

    PidCurrentValues* pidCurrentValues = &(computationValues->currentValues[instructionType]);
	enum PidType pidType = getPidType(motionInstruction.motionParameterType);

	addInstructionTypeTableData(outputStream, instructionType, PID_DEBUG_DATA_INSTRUCTION_TYPE_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) computationValues->pidTime, PID_DEBUG_DATA_PID_TIME_COLUMN_LENGTH);
	addPidTypeTableData(outputStream, pidType, PID_DEBUG_DATA_PID_TYPE_TYPE_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) pidCurrentValues->normalPosition, PID_DEBUG_DATA_NORMAL_POSITION_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) pidCurrentValues->position, PID_DEBUG_DATA_POSITION_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) localError->error, PID_DEBUG_DATA_ERROR_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) pidCurrentValues->u, PID_DEBUG_DATA_U_COLUMN_LENGTH);

    MotionEndInfo* motionEnd = &(computationValues->motionEnd[instructionType]);
	appendDecTableData(outputStream, motionEnd->integralTime, PID_DEBUG_DATA_MOTION_END_INTEGRAL_TIME_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) motionEnd->absDeltaPositionIntegral, PID_DEBUG_DATA_MOTION_END_ABS_DELTA_POSITION_INT_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) motionEnd->absUIntegral, PID_DEBUG_DATA_MOTION_END_ABS_INTEGRAL_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_DATA_LAST_COLUMN_LENGTH_COLUMN_LENGTH);
}

void printPidDataDebugTable(OutputStream* outputStream, PidMotion* pidMotion) {
	printDebugDataHeader(outputStream);
	printDebugDataInstructionTypeLine(outputStream, pidMotion, THETA);
	printDebugDataInstructionTypeLine(outputStream, pidMotion, ALPHA);
	appendTableHeaderSeparatorLine(outputStream);
}
