#include "model.h"

#include <float.h>  // for DBL_MIN
#include <math.h>   // for fabs()
#include <string.h>
#include <time.h>

#include "config.h"
#include "network.h"

#define V_MIN (0.1)
#define EVENT_EPSILON (1e-10)

#define IP_MAX_LEN (45)
#define UDP_SEND_VALUES (64)
#define UDP_TIMEOUT_SECONDS (2)

static int maxRecvId = 0;
static int sendId = 0;
static bool uniqueId = true;
static bool shouldReceive = true;

void setStartValues(ModelInstance *comp) {
    memset(&comp->modelData, 0, sizeof(comp->modelData));

    M(socket_inPort) = 64890;
    strcpy(M(socket_inAddress), "127.0.0.1");
    M(socket_outPort) = 64891;
    strcpy(M(socket_outAddress), "127.0.0.1");
}

Status calculateValues(ModelInstance *comp) {
    UNUSED(comp);
    // nothing to do
    return OK;
}

Status getFloat64(ModelInstance *comp, ValueReference vr, double values[], size_t nValues, size_t *index) {
    ASSERT_NVALUES(1);

    switch (vr) {
    case vr_time:
        values[(*index)++] = comp->time;
        return OK;
    case vr_throttle:
        values[(*index)++] = M(throttle);
        return OK;
    case vr_throttleInput:
        values[(*index)++] = M(throttleInput);
        return OK;
    case vr_brake:
        values[(*index)++] = M(brake);
        return OK;
    case vr_brakeInput:
        values[(*index)++] = M(brakeInput);
        return OK;
    case vr_clutch:
        values[(*index)++] = M(clutch);
        return OK;
    case vr_clutchInput:
        values[(*index)++] = M(clutchInput);
        return OK;
    case vr_parkingbrake:
        values[(*index)++] = M(parkingbrake);
        return OK;
    case vr_parkingbrakeInput:
        values[(*index)++] = M(parkingbrakeInput);
        return OK;
    case vr_steering:
        values[(*index)++] = M(steering);
        return OK;
    case vr_steeringInput:
        values[(*index)++] = M(steeringInput);
        return OK;
    case vr_posX:
        values[(*index)++] = M(posX);
        return OK;
    case vr_posY:
        values[(*index)++] = M(posY);
        return OK;
    case vr_posZ:
        values[(*index)++] = M(posZ);
        return OK;
    case vr_velX:
        values[(*index)++] = M(velX);
        return OK;
    case vr_velY:
        values[(*index)++] = M(velY);
        return OK;
    case vr_velZ:
        values[(*index)++] = M(velZ);
        return OK;
    case vr_groundspeed:
        values[(*index)++] = M(groundspeed);
        return OK;
    case vr_accX:
        values[(*index)++] = M(accX);
        return OK;
    case vr_accY:
        values[(*index)++] = M(accY);
        return OK;
    case vr_accZ:
        values[(*index)++] = M(accZ);
        return OK;
    case vr_roll:
        values[(*index)++] = M(roll);
        return OK;
    case vr_pitch:
        values[(*index)++] = M(pitch);
        return OK;
    case vr_yaw:
        values[(*index)++] = M(yaw);
        return OK;
    case vr_altitude:
        values[(*index)++] = M(altitude);
        return OK;
    case vr_fuel:
        values[(*index)++] = M(fuel);
        return OK;
    case vr_engineLoad:
        values[(*index)++] = M(engineLoad);
        return OK;
    case vr_maxrpm:
        values[(*index)++] = M(maxrpm);
        return OK;
    case vr_rpm:
        values[(*index)++] = M(rpm);
        return OK;
    case vr_wheelspeed:
        values[(*index)++] = M(wheelspeed);
        return OK;
    case vr_wheelFL_angularVelocity:
        values[(*index)++] = M(wheelFL_angularVelocity);
        return OK;
    case vr_wheelFL_wheelSpeed:
        values[(*index)++] = M(wheelFL_wheelSpeed);
        return OK;
    case vr_wheelFL_brakingTorque:
        values[(*index)++] = M(wheelFL_brakingTorque);
        return OK;
    case vr_wheelFL_propulsionTorque:
        values[(*index)++] = M(wheelFL_propulsionTorque);
        return OK;
    case vr_wheelFL_frictionTorque:
        values[(*index)++] = M(wheelFL_frictionTorque);
        return OK;
    case vr_wheelFL_downForce:
        values[(*index)++] = M(wheelFL_downForce);
        return OK;
    case vr_wheelFR_angularVelocity:
        values[(*index)++] = M(wheelFR_angularVelocity);
        return OK;
    case vr_wheelFR_wheelSpeed:
        values[(*index)++] = M(wheelFR_wheelSpeed);
        return OK;
    case vr_wheelFR_brakingTorque:
        values[(*index)++] = M(wheelFR_brakingTorque);
        return OK;
    case vr_wheelFR_propulsionTorque:
        values[(*index)++] = M(wheelFR_propulsionTorque);
        return OK;
    case vr_wheelFR_frictionTorque:
        values[(*index)++] = M(wheelFR_frictionTorque);
        return OK;
    case vr_wheelFR_downForce:
        values[(*index)++] = M(wheelFR_downForce);
        return OK;
    case vr_wheelRL_angularVelocity:
        values[(*index)++] = M(wheelRL_angularVelocity);
        return OK;
    case vr_wheelRL_wheelSpeed:
        values[(*index)++] = M(wheelRL_wheelSpeed);
        return OK;
    case vr_wheelRL_brakingTorque:
        values[(*index)++] = M(wheelRL_brakingTorque);
        return OK;
    case vr_wheelRL_propulsionTorque:
        values[(*index)++] = M(wheelRL_propulsionTorque);
        return OK;
    case vr_wheelRL_frictionTorque:
        values[(*index)++] = M(wheelRL_frictionTorque);
        return OK;
    case vr_wheelRL_downForce:
        values[(*index)++] = M(wheelRL_downForce);
        return OK;
    case vr_wheelRR_angularVelocity:
        values[(*index)++] = M(wheelRR_angularVelocity);
        return OK;
    case vr_wheelRR_wheelSpeed:
        values[(*index)++] = M(wheelRR_wheelSpeed);
        return OK;
    case vr_wheelRR_brakingTorque:
        values[(*index)++] = M(wheelRR_brakingTorque);
        return OK;
    case vr_wheelRR_propulsionTorque:
        values[(*index)++] = M(wheelRR_propulsionTorque);
        return OK;
    case vr_wheelRR_frictionTorque:
        values[(*index)++] = M(wheelRR_frictionTorque);
        return OK;
    case vr_wheelRR_downForce:
        values[(*index)++] = M(wheelRR_downForce);
        return OK;
    case vr_input_throttleInput:
        values[(*index)++] = M(input_throttleInput);
        return OK;
    case vr_input_brakeInput:
        values[(*index)++] = M(input_brakeInput);
        return OK;
    case vr_input_steeringInput:
        values[(*index)++] = M(input_steeringInput);
        return OK;
    case vr_input_wheelFL_brakingTorque:
        values[(*index)++] = M(input_wheelFL_brakingTorque);
        return OK;
    case vr_input_wheelFL_propulsionTorque:
        values[(*index)++] = M(input_wheelFL_propulsionTorque);
        return OK;
    case vr_input_wheelFR_brakingTorque:
        values[(*index)++] = M(input_wheelFR_brakingTorque);
        return OK;
    case vr_input_wheelFR_propulsionTorque:
        values[(*index)++] = M(input_wheelFR_propulsionTorque);
        return OK;
    case vr_input_wheelRL_brakingTorque:
        values[(*index)++] = M(input_wheelRL_brakingTorque);
        return OK;
    case vr_input_wheelRL_propulsionTorque:
        values[(*index)++] = M(input_wheelRL_propulsionTorque);
        return OK;
    case vr_input_wheelRR_brakingTorque:
        values[(*index)++] = M(input_wheelRR_brakingTorque);
        return OK;
    case vr_input_wheelRR_propulsionTorque:
        values[(*index)++] = M(input_wheelRR_propulsionTorque);
        return OK;
    default:
        logError(comp, "Get Float64 is not allowed for value reference %u.", vr);
        return Error;
    }
}

Status setFloat64(ModelInstance *comp, ValueReference vr, const double values[], size_t nValues, size_t *index) {
    ASSERT_NVALUES(1);

    switch (vr) {
    case vr_input_throttleInput:
        M(input_throttleInput) = values[(*index)++];
        return OK;
    case vr_input_brakeInput:
        M(input_brakeInput) = values[(*index)++];
        return OK;
    case vr_input_steeringInput:
        M(input_steeringInput) = values[(*index)++];
        return OK;
    case vr_input_wheelFL_brakingTorque:
        M(input_wheelFL_brakingTorque) = values[(*index)++];
        return OK;
    case vr_input_wheelFL_propulsionTorque:
        M(input_wheelFL_propulsionTorque) = values[(*index)++];
        return OK;
    case vr_input_wheelFR_brakingTorque:
        M(input_wheelFR_brakingTorque) = values[(*index)++];
        return OK;
    case vr_input_wheelFR_propulsionTorque:
        M(input_wheelFR_propulsionTorque) = values[(*index)++];
        return OK;
    case vr_input_wheelRL_brakingTorque:
        M(input_wheelRL_brakingTorque) = values[(*index)++];
        return OK;
    case vr_input_wheelRL_propulsionTorque:
        M(input_wheelRL_propulsionTorque) = values[(*index)++];
        return OK;
    case vr_input_wheelRR_brakingTorque:
        M(input_wheelRR_brakingTorque) = values[(*index)++];
        return OK;
    case vr_input_wheelRR_propulsionTorque:
        M(input_wheelRR_propulsionTorque) = values[(*index)++];
        return OK;
    default:
        logError(comp, "Unexpected value reference: %u.", vr);
        return Error;
    }
}

Status getInt32(ModelInstance *comp, ValueReference vr, int32_t values[], size_t nValues, size_t *index) {
    ASSERT_NVALUES(1);

    switch (vr) {
    case vr_ignitionLevel:
        values[(*index)++] = M(ignitionLevel);
        return OK;
    case vr_gear:
        values[(*index)++] = M(gear);
        return OK;
    case vr_input_gear:
        values[(*index)++] = M(input_gear);
        return OK;
    case vr_socket_inPort:
        values[(*index)++] = M(socket_inPort);
        return OK;
    case vr_socket_outPort:
        values[(*index)++] = M(socket_outPort);
        return OK;
    default:
        logError(comp, "Get Int32 is not allowed for value reference %u.", vr);
        return Error;
    }
}

Status setInt32(ModelInstance *comp, ValueReference vr, const int32_t values[], size_t nValues, size_t *index) {
    ASSERT_NVALUES(1);

    switch (vr) {
    case vr_input_gear:
        M(input_gear) = values[(*index)++];
        return OK;
    case vr_socket_inPort:
        M(socket_inPort) = values[(*index)++];
        return OK;
    case vr_socket_outPort:
        M(socket_outPort) = values[(*index)++];
        return OK;
    default:
        logError(comp, "Unexpected value reference: %u.", vr);
        return Error;
    }
}

Status getBoolean(ModelInstance *comp, ValueReference vr, bool values[], size_t nValues, size_t *index) {
    ASSERT_NVALUES(1);

    switch (vr) {
    case vr_highbeam:
        values[(*index)++] = M(highbeam);
        return OK;
    case vr_lowbeam:
        values[(*index)++] = M(lowbeam);
        return OK;
    case vr_reverse:
        values[(*index)++] = M(reverse);
        return OK;
    case vr_signalL:
        values[(*index)++] = M(signalL);
        return OK;
    case vr_signalR:
        values[(*index)++] = M(signalR);
        return OK;
    case vr_input_driveMode:
        values[(*index)++] = M(input_driveMode);
        return OK;
    default:
        logError(comp, "Get Boolean is not allowed for value reference %u.", vr);
        return Error;
    }
}

Status setBoolean(ModelInstance *comp, ValueReference vr, const bool values[], size_t nValues, size_t *index) {
    ASSERT_NVALUES(1);

    switch (vr) {
    case vr_input_driveMode:
        M(input_driveMode) = values[(*index)++];
        return OK;
    default:
        logError(comp, "Unexpected value reference: %u.", vr);
        return Error;
    }
}

Status getString(ModelInstance *comp, ValueReference vr, const char *values[], size_t nValues, size_t *index) {
    ASSERT_NVALUES(1);

    switch (vr) {
    case vr_socket_inAddress:
        values[(*index)++] = M(socket_inAddress);
        return OK;
    case vr_socket_outAddress:
        values[(*index)++] = M(socket_outAddress);
        return OK;
    default:
        logError(comp, "Get String is not allowed for value reference %u.", vr);
        return Error;
    }
}

Status setString(ModelInstance *comp, ValueReference vr, const char *const values[], size_t nValues, size_t *index) {
    ASSERT_NVALUES(1);

    switch (vr) {
    case vr_socket_inAddress:
        if (strlen(values[*index]) >= IP_MAX_LEN) {
            logError(comp, "Max. IP length is %d bytes.", IP_MAX_LEN);
            return Error;
        }
        strcpy(M(socket_inAddress), values[(*index)++]);
        break;
    case vr_socket_outAddress:
        if (strlen(values[*index]) >= IP_MAX_LEN) {
            logError(comp, "Max. IP length is %d bytes.", IP_MAX_LEN);
            return Error;
        }
        strcpy(M(socket_outAddress), values[(*index)++]);
        break;
    default:
        logError(comp, "Set String is not allowed for value reference %u.", vr);
        return Error;
    }

    comp->isDirtyValues = true;

    return OK;
}

Status getOutputDerivative(ModelInstance *comp, ValueReference valueReference, int order, double *value) {
    UNUSED(value);

    if (order != 1) {
        logError(comp, "The output derivative order %d for value reference %u is not available.", order, valueReference);
        return Error;
    }

    switch (valueReference) {
    default:
        logError(comp, "The output derivative for value reference %u is not available.", valueReference);
        return Error;
    }
}

size_t getNumberOfEventIndicators(ModelInstance *comp) {
    UNUSED(comp);

    return 0;
}

size_t getNumberOfContinuousStates(ModelInstance *comp) {
    UNUSED(comp);

    return 0;
}

static void parseReceivedData(ModelInstance *comp, double data[]) {
    M(throttle) = data[1];
    M(throttleInput) = data[2];
    M(brake) = data[3];
    M(brakeInput) = data[4];
    M(clutch) = data[5];
    M(clutchInput) = data[6];
    M(parkingbrake) = data[7];
    M(parkingbrakeInput) = data[8];
    M(steering) = data[9];
    M(steeringInput) = data[10];
    M(posX) = data[11];
    M(posY) = data[12];
    M(posZ) = data[13];
    M(velX) = data[14];
    M(velY) = data[15];
    M(velZ) = data[16];
    M(groundspeed) = data[17];
    M(accX) = data[18];
    M(accY) = data[19];
    M(accZ) = data[20];
    M(roll) = data[21];
    M(pitch) = data[22];
    M(yaw) = data[23];
    M(altitude) = data[24];
    M(ignitionLevel) = (int32_t)data[25];
    M(gear) = (int32_t)data[26];
    M(fuel) = data[27];
    M(engineLoad) = data[28];
    M(highbeam) = (bool)data[29];
    M(lowbeam) = (bool)data[30];
    M(maxrpm) = data[31];
    M(reverse) = (bool)data[32];
    M(rpm) = data[33];
    M(signalL) = (bool)data[34];
    M(signalR) = (bool)data[35];
    M(wheelspeed) = data[36];
    M(wheelFL_angularVelocity) = data[37];
    M(wheelFL_wheelSpeed) = data[38];
    M(wheelFL_brakingTorque) = data[39];
    M(wheelFL_propulsionTorque) = data[40];
    M(wheelFL_frictionTorque) = data[41];
    M(wheelFL_downForce) = data[42];
    M(wheelFR_angularVelocity) = data[43];
    M(wheelFR_wheelSpeed) = data[44];
    M(wheelFR_brakingTorque) = data[45];
    M(wheelFR_propulsionTorque) = data[46];
    M(wheelFR_frictionTorque) = data[47];
    M(wheelFR_downForce) = data[48];
    M(wheelRL_angularVelocity) = data[49];
    M(wheelRL_wheelSpeed) = data[50];
    M(wheelRL_brakingTorque) = data[51];
    M(wheelRL_propulsionTorque) = data[52];
    M(wheelRL_frictionTorque) = data[53];
    M(wheelRL_downForce) = data[54];
    M(wheelRR_angularVelocity) = data[55];
    M(wheelRR_wheelSpeed) = data[56];
    M(wheelRR_brakingTorque) = data[57];
    M(wheelRR_propulsionTorque) = data[58];
    M(wheelRR_frictionTorque) = data[59];
    M(wheelRR_downForce) = data[60];
}

static void prepareDataToSend(ModelInstance *comp, double data[]) {
    data[0] = (double)++sendId;
    data[1] = M(input_throttleInput);
    data[2] = M(input_brakeInput);
    data[3] = M(input_steeringInput);
    data[4] = (double)M(input_gear);
    data[5] = M(input_wheelFL_brakingTorque);
    data[6] = M(input_wheelFL_propulsionTorque);
    data[7] = M(input_wheelFR_brakingTorque);
    data[8] = M(input_wheelFR_propulsionTorque);
    data[9] = M(input_wheelRL_brakingTorque);
    data[10] = M(input_wheelRL_propulsionTorque);
    data[11] = M(input_wheelRR_brakingTorque);
    data[12] = M(input_wheelRR_propulsionTorque);
    data[13] = (double)M(input_driveMode);

    // Custom user values
    // data[14] = ...
    // ...
    // data[63] = ...
}

static bool communicationRecv(ModelInstance *comp) {
    // this function is called at each iteration
    double recvData[UDP_BUF_SIZE / sizeof(double)] = {0};
    bool invalid = true;

    clock_t t1, t2;
    double elapsedTime;

    t1 = clock();

    while (invalid) {
        if (!udpReceive((char *)recvData, comp)) {
            return false;
        }
        int transactionId = (int)recvData[0];

        if (transactionId > maxRecvId) {
            invalid = false;
            uniqueId = true;
            maxRecvId = transactionId;
        } else if (transactionId == maxRecvId && uniqueId) {
            invalid = false;
            uniqueId = false;
        } else {
            t2 = clock() - t1;
            elapsedTime = ((double)t2) / CLOCKS_PER_SEC;

            if (elapsedTime > UDP_TIMEOUT_SECONDS) {
                invalid = false;
                uniqueId = true;
                maxRecvId = 0;
            }
        }
    }
    parseReceivedData(comp, recvData);
    shouldReceive = false;
    return true;
}

static void communicationSend(ModelInstance *comp) {
    double sendData[UDP_SEND_VALUES] = {0};
    prepareDataToSend(comp, sendData);
    udpSend((char *)sendData, sizeof(sendData), (unsigned short)M(socket_outPort), M(socket_outAddress));
    shouldReceive = true;
}

Status doFixedStep(ModelInstance *comp, bool *stateEvent, bool *timeEvent, double stepSize) {
    if (shouldReceive && !communicationRecv(comp)) {
        logError(comp, "Cannot connect to BeamNG. Check that the simulator is running and the vehicle coupling is on.");
        modelinstance_terminate(comp);
        return Error;
    }
    communicationSend(comp);

    uint64_t stepsToDo = 1;
    if (stepSize > 0) {
        stepsToDo = (uint64_t)ceil(stepSize / FIXED_SOLVER_STEP);
    }

    comp->nSteps += stepsToDo;
    comp->time = comp->startTime + comp->nSteps * FIXED_SOLVER_STEP;

    // state event
    *stateEvent = false;

    // time event
    *timeEvent = comp->nextEventTimeDefined && comp->time >= comp->nextEventTime;

    bool earlyReturnRequested;
    double earlyReturnTime;

    // intermediate update
    if (comp->intermediateUpdate) {
        comp->intermediateUpdate(comp->componentEnvironment,  // instanceEnvironment
                                 comp->time,                  // intermediateUpdateTime
                                 false,                       // intermediateVariableSetRequested
                                 true,                        // intermediateVariableGetAllowed
                                 true,                        // intermediateStepFinished
                                 false,                       // canReturnEarly
                                 &earlyReturnRequested,       // earlyReturnRequested
                                 &earlyReturnTime);           // earlyReturnTime
    }

    return OK;
}

Status modelinstance_configurate(ModelInstance *comp) {
    unsigned short inport = (unsigned short)M(socket_inPort);
    char *inaddr = M(socket_inAddress);
    if (udpSetup(inport, inaddr, comp) != 0) {
        logError(comp, "The UDP socket could not be set up (%s:%d).", inaddr, inport);
        return Error;
    }
    if (!communicationRecv(comp)) {
        logError(comp, "Cannot connect to the UDP socket (%s:%d->%s:%d). Start BeamNG's vehicle coupling controller first.", inaddr, inport,
                 M(socket_outAddress), M(socket_outPort));
        udpTerminate();
        return Error;
    }
    logEvent(comp, "Configured the UDP socket to (%s:%d->%s:%d)", inaddr, inport, M(socket_outAddress), M(socket_outPort));
    return OK;
}

Status modelinstance_terminate(ModelInstance *comp) {
    udpTerminate();
    comp->state = Terminated;
    logEvent(comp, "Closed UDP connection, FMU terminating.");

    return OK;
}
