#include "BobLib.Experiments.Standards.VehicleSim_model.h"
#if defined(__cplusplus)
extern "C" {
#endif
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29097(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29096(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31410(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31411(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29095(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29094(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29092(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29318(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29319(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29327(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29357(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30264(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30271(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30279(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29486(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29493(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29501(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29365(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29366(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29368(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29367(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29364(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29363(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30280(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29362(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29361(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29502(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29360(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29359(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29358(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29369(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29370(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29371(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29372(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29373(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29374(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29375(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29376(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29377(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29378(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29379(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29380(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29105(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29106(DATA *data, threadData_t *threadData);


/*
equation index: 2075
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.spaceFrame.midToFore.shape.r[2] = chassis.detailedChassis.spaceFrame.sprungBody.v_0[2] - (chassis.chassisFrame.R.T[1,2] * (0.09245073226067826 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-1.7429613639823153e-6) * yawVel) + chassis.chassisFrame.R.T[2,2] * ((-0.03544608361872592) * yawVel + (-0.09245073226067826) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,2] * (1.7429613639823153e-6 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.03544608361872592 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2075(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2075};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1991]] /* der(chassis.detailedChassis.spaceFrame.midToFore.shape.r[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9940]] /* chassis.detailedChassis.spaceFrame.sprungBody.v_0[2] DUMMY_STATE */) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((0.09245073226067826) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-1.7429613639823153e-6) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((-0.03544608361872592) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (-0.09245073226067826) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * ((1.7429613639823153e-6) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.03544608361872592) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))));
  threadData->lastEquationSolved = 2075;
}

/*
equation index: 2076
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleFrame.r_0[2] = $DER.chassis.detailedChassis.spaceFrame.midToFore.shape.r[2] + 0.7747 * chassis.chassisFrame.R.T[2,2] * yawVel + (-0.7747) * chassis.chassisFrame.R.T[3,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2076(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2076};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1410]] /* der(chassis.detailedChassis.frAxleFrame.r_0[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1991]] /* der(chassis.detailedChassis.spaceFrame.midToFore.shape.r[2]) DUMMY_DER */) + (0.7747) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + (-0.7747) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 2076;
}

/*
equation index: 2077
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rackAndPinion.pinionVisualizer.vis.r[2] = $DER.chassis.detailedChassis.frAxleFrame.r_0[2] + (-0.08618219999999999) * chassis.chassisFrame.R.T[1,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.chassisFrame.R.T[2,2] * (0.05715 * yawVel + 0.08618219999999999 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + (-0.05715) * chassis.chassisFrame.R.T[3,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2077(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2077};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1124]] /* der(chassis.detailedChassis.frAxleDW.rackAndPinion.pinionVisualizer.vis.r[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1410]] /* der(chassis.detailedChassis.frAxleFrame.r_0[2]) DUMMY_DER */) + (-0.08618219999999999) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((0.05715) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.08618219999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + (-0.05715) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 2077;
}

/*
equation index: 2078
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.vis.r[2] = $DER.chassis.detailedChassis.frAxleDW.rackAndPinion.pinionVisualizer.vis.r[2] + chassis.chassisFrame.R.T[1,2] * (-yawVel) * chassis.detailedChassis.frAxleDW.rackAndPinion.rackAxis.s + chassis.chassisFrame.R.T[2,2] * chassis.detailedChassis.frAxleDW.rackAndPinion.rackAxis.v + chassis.chassisFrame.R.T[3,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.rackAndPinion.rackAxis.s
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2078(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2078};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1129]] /* der(chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.vis.r[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1124]] /* der(chassis.detailedChassis.frAxleDW.rackAndPinion.pinionVisualizer.vis.r[2]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * (((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4093]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.rackAxis.s DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4094]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.rackAxis.v DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4093]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.rackAxis.s DUMMY_STATE */)));
  threadData->lastEquationSolved = 2078;
}

/*
equation index: 2079
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rackAndPinion.fromLeft.shape.r[2] = $DER.chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.vis.r[2] - (0.2260092 * chassis.chassisFrame.R.T[1,2] * yawVel + (-0.2260092) * chassis.chassisFrame.R.T[3,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2079(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2079};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1121]] /* der(chassis.detailedChassis.frAxleDW.rackAndPinion.fromLeft.shape.r[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1129]] /* der(chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.vis.r[2]) DUMMY_DER */) - ((0.2260092) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + (-0.2260092) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))));
  threadData->lastEquationSolved = 2079;
}

/*
equation index: 2080
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodShape.r[2] = $DER.chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.vis.r[2] + 0.2260092 * chassis.chassisFrame.R.T[1,2] * yawVel + (-0.2260092) * chassis.chassisFrame.R.T[3,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2080(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2080};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1222]] /* der(chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodShape.r[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1129]] /* der(chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.vis.r[2]) DUMMY_DER */) + (0.2260092) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + (-0.2260092) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)));
  threadData->lastEquationSolved = 2080;
}

/*
equation index: 2081
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[2] = $DER.chassis.detailedChassis.frAxleFrame.r_0[2] + chassis.chassisFrame.R.T[1,2] * (0.014833600000000002 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-0.2366899) * yawVel) + chassis.chassisFrame.R.T[2,2] * (0.016751299999999997 * yawVel + (-0.014833600000000002) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,2] * (0.2366899 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + (-0.016751299999999997) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2081(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2081};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1052]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1410]] /* der(chassis.detailedChassis.frAxleFrame.r_0[2]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((0.014833600000000002) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-0.2366899) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((0.016751299999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (-0.014833600000000002) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * ((0.2366899) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (-0.016751299999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 2081;
}

/*
equation index: 2082
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.cylinder.r[2] = $DER.chassis.detailedChassis.frAxleFrame.r_0[2] + chassis.chassisFrame.R.T[1,2] * ((-0.119888) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-0.226314) * yawVel) + chassis.chassisFrame.R.T[2,2] * (0.012699999999999996 * yawVel + 0.119888 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,2] * (0.226314 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + (-0.012699999999999996) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2082(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2082};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1023]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.cylinder.r[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1410]] /* der(chassis.detailedChassis.frAxleFrame.r_0[2]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((-0.119888) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-0.226314) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((0.012699999999999996) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.119888) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * ((0.226314) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (-0.012699999999999996) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 2082;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32731(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32733(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32732(DATA *data, threadData_t *threadData);


/*
equation index: 2086
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[2] = $DER.chassis.detailedChassis.frAxleFrame.r_0[2] + chassis.chassisFrame.R.T[1,2] * (chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * chassis.detailedChassis.frAxleDW.toRightUpper_i.r[3] - yawVel * chassis.detailedChassis.frAxleDW.toRightUpper_i.r[2]) + chassis.chassisFrame.R.T[2,2] * (yawVel * chassis.detailedChassis.frAxleDW.toRightUpper_i.r[1] - chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.toRightUpper_i.r[3]) + chassis.chassisFrame.R.T[3,2] * (chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.toRightUpper_i.r[2] - chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * chassis.detailedChassis.frAxleDW.toRightUpper_i.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2086(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2086};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1300]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1410]] /* der(chassis.detailedChassis.frAxleFrame.r_0[2]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2554]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2553]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2552]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2554]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2553]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2552]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[1] PARAM */))));
  threadData->lastEquationSolved = 2086;
}

/*
equation index: 2087
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.r[2] = $DER.chassis.detailedChassis.frAxleFrame.r_0[2] + chassis.chassisFrame.R.T[1,2] * (chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * chassis.detailedChassis.frAxleDW.toRightLower_i.r[3] - yawVel * chassis.detailedChassis.frAxleDW.toRightLower_i.r[2]) + chassis.chassisFrame.R.T[2,2] * (yawVel * chassis.detailedChassis.frAxleDW.toRightLower_i.r[1] - chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.toRightLower_i.r[3]) + chassis.chassisFrame.R.T[3,2] * (chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.toRightLower_i.r[2] - chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * chassis.detailedChassis.frAxleDW.toRightLower_i.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2087(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2087};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1271]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.r[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1410]] /* der(chassis.detailedChassis.frAxleFrame.r_0[2]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2522]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2521]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2520]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2522]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2521]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2520]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[1] PARAM */))));
  threadData->lastEquationSolved = 2087;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31781(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31783(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31782(DATA *data, threadData_t *threadData);


/*
equation index: 2091
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftBellcrank.side_1.vis.r[2] = $DER.chassis.detailedChassis.frAxleFrame.r_0[2] + chassis.chassisFrame.R.T[1,2] * (0.170112000136 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-0.250754351932) * yawVel) + chassis.chassisFrame.R.T[2,2] * ((-0.042144464098) * yawVel + (-0.170112000136) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,2] * (0.250754351932 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2091(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2091};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[903]] /* der(chassis.detailedChassis.frAxleDW.leftBellcrank.side_1.vis.r[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1410]] /* der(chassis.detailedChassis.frAxleFrame.r_0[2]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (-0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * ((0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 2091;
}

/*
equation index: 2092
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightBellcrank.side_1.vis.r[2] = $DER.chassis.detailedChassis.frAxleFrame.r_0[2] + chassis.chassisFrame.R.T[1,2] * ((-0.199898 + BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + 0.250754351932 * yawVel) + chassis.chassisFrame.R.T[2,2] * ((-0.042144464098) * yawVel + (0.199898 - BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,2] * ($DER$BobLib$PUtilities$PMath$PVector$PmirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136}, {0.0, 0.0, 0.0})[3] + (-0.250754351932) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2092(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2092};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1146]] /* der(chassis.detailedChassis.frAxleDW.rightBellcrank.side_1.vis.r[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1410]] /* der(chassis.detailedChassis.frAxleFrame.r_0[2]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((-0.199898 + real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.199898 - (real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * (real_get(omc__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData, _OMC_LIT23, _OMC_LIT25), 2) + (-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 2092;
}

/*
equation index: 2093
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.stabar.toRightBarEnd.shape.r[2] = $DER.chassis.detailedChassis.frAxleFrame.r_0[2] + (-0.08178799999999999) * chassis.chassisFrame.R.T[1,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.chassisFrame.R.T[2,2] * ((-0.10664664) * yawVel + 0.08178799999999999 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + 0.10664664 * chassis.chassisFrame.R.T[3,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2093(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2093};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1407]] /* der(chassis.detailedChassis.frAxleDW.stabar.toRightBarEnd.shape.r[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1410]] /* der(chassis.detailedChassis.frAxleFrame.r_0[2]) DUMMY_DER */) + (-0.08178799999999999) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((-0.10664664) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.08178799999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + (0.10664664) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 2093;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29432(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29440(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29441(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29443(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29442(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29439(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29438(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30807(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30808(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29437(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29436(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29868(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29869(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29435(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29434(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29433(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29457(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29460(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29107(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29108(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29109(DATA *data, threadData_t *threadData);


/*
equation index: 2115
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightShockLinkage.frame_b.r_0[2] = $DER.chassis.detailedChassis.frAxleFrame.r_0[2] + chassis.chassisFrame.R.T[1,2] * ((-0.199898 + BobLib.Utilities.Math.Vector.mirrorXZ({-0.020673469702, 0.247847085458, 0.561456926868})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + 0.247847085458 * yawVel) + chassis.chassisFrame.R.T[2,2] * ((-0.020673469702) * yawVel + (0.199898 - BobLib.Utilities.Math.Vector.mirrorXZ({-0.020673469702, 0.247847085458, 0.561456926868})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,2] * ($DER$BobLib$PUtilities$PMath$PVector$PmirrorXZ({-0.020673469702, 0.247847085458, 0.561456926868}, {0.0, 0.0, 0.0})[3] + (-0.247847085458) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.020673469702 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2115(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2115};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1210]] /* der(chassis.detailedChassis.frAxleDW.rightShockLinkage.frame_b.r_0[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1410]] /* der(chassis.detailedChassis.frAxleFrame.r_0[2]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((-0.199898 + real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT24), 2)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (0.247847085458) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((-0.020673469702) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.199898 - (real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT24), 2))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * (real_get(omc__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData, _OMC_LIT24, _OMC_LIT25), 2) + (-0.247847085458) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.020673469702) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 2115;
}

/*
equation index: 2116
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftShockLinkage.frame_b.r_0[2] = $DER.chassis.detailedChassis.frAxleFrame.r_0[2] + chassis.chassisFrame.R.T[1,2] * (0.36155892686799995 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-0.247847085458) * yawVel) + chassis.chassisFrame.R.T[2,2] * ((-0.020673469702) * yawVel + (-0.36155892686799995) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,2] * (0.247847085458 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.020673469702 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2116(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2116};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[967]] /* der(chassis.detailedChassis.frAxleDW.leftShockLinkage.frame_b.r_0[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1410]] /* der(chassis.detailedChassis.frAxleFrame.r_0[2]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((0.36155892686799995) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-0.247847085458) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((-0.020673469702) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (-0.36155892686799995) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * ((0.247847085458) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.020673469702) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 2116;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29110(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29111(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29112(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29113(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29114(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29115(DATA *data, threadData_t *threadData);


/*
equation index: 2123
type: SIMPLE_ASSIGN
chassis.chassisFrame.R.T[3,3] = cos(chassis.cgFreeMotion.phi[2]) * cos(chassis.cgFreeMotion.phi[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2123(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2123};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */) = (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* chassis.cgFreeMotion.phi[2] STATE(1,chassis.cgFreeMotion.phi_d[2]) */))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */)));
  threadData->lastEquationSolved = 2123;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32172(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32189(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32188(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31394(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31401(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31412(DATA *data, threadData_t *threadData);


/*
equation index: 2130
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.midToFore.shape.r[3] = chassis.detailedChassis.spaceFrame.sprungBody.frame_a.r_0[3] - ((-0.03544608361872592) * chassis.chassisFrame.R.T[1,3] + 1.7429613639823153e-6 * chassis.chassisFrame.R.T[2,3] + 0.09245073226067826 * chassis.chassisFrame.R.T[3,3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2130(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2130};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9872]] /* chassis.detailedChassis.spaceFrame.midToFore.shape.r[3] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9910]] /* chassis.detailedChassis.spaceFrame.sprungBody.frame_a.r_0[3] DUMMY_STATE */) - ((-0.03544608361872592) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) + (1.7429613639823153e-6) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) + (0.09245073226067826) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)));
  threadData->lastEquationSolved = 2130;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29118(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29120(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29132(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29134(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29133(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29128(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29125(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32190(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32192(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32191(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32193(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32195(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32197(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32194(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32198(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32256(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29126(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32250(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32246(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32248(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32247(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29127(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32255(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32251(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32253(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32252(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29124(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29123(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31413(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31415(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31414(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31416(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31417(DATA *data, threadData_t *threadData);


/*
equation index: 2164
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.A = (-2.0) * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2164(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2164};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5590]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.A DUMMY_STATE */) = (-2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5634]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5631]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5635]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5632]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5636]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5633]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] DUMMY_STATE */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5623]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5622]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a DUMMY_STATE */))));
  threadData->lastEquationSolved = 2164;
}

/*
equation index: 2165
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.B = 2.0 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2]) + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3]) + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2165(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2165};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5591]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.B DUMMY_STATE */) = (2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5634]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] DUMMY_STATE */)) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5633]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] DUMMY_STATE */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5632]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] DUMMY_STATE */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5635]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] DUMMY_STATE */)) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5631]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] DUMMY_STATE */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5633]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] DUMMY_STATE */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5636]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] DUMMY_STATE */)) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5632]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] DUMMY_STATE */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5631]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] DUMMY_STATE */)))));
  threadData->lastEquationSolved = 2165;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31421(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31479(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29122(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29121(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29119(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29320(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29321(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29328(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29381(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30265(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30272(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30281(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29487(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29494(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29503(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29389(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29390(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29392(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29391(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29388(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29387(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30282(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30285(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30284(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30283(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30287(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30289(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30286(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30290(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29386(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29385(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29504(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29507(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29506(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29505(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29508(DATA *data, threadData_t *threadData);


/*
equation index: 2202
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.A = (-2.0) * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2202(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2202};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9347]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.A DUMMY_STATE */) = (-2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9391]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9388]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9392]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9389]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9393]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9390]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] DUMMY_STATE */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9380]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9379]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a DUMMY_STATE */))));
  threadData->lastEquationSolved = 2202;
}

/*
equation index: 2203
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.B = 2.0 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2]) + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3]) + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2203(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2203};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9348]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.B DUMMY_STATE */) = (2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9391]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] DUMMY_STATE */)) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9390]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] DUMMY_STATE */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9389]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] DUMMY_STATE */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9392]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] DUMMY_STATE */)) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9388]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] DUMMY_STATE */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9390]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] DUMMY_STATE */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9393]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] DUMMY_STATE */)) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9389]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] DUMMY_STATE */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9388]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] DUMMY_STATE */)))));
  threadData->lastEquationSolved = 2203;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29512(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29384(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29383(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29382(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29393(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29394(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29395(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29396(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29397(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29411(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29724(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29720(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29723(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29722(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29721(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29412(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29729(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29725(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29728(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29727(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29726(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29413(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29414(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29415(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30663(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30659(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30662(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30661(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30660(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29416(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30668(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30664(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30667(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30666(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30665(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29417(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29418(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29135(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29136(DATA *data, threadData_t *threadData);


/*
equation index: 2243
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.spaceFrame.midToFore.shape.r[3] = chassis.detailedChassis.spaceFrame.sprungBody.v_0[3] - (chassis.chassisFrame.R.T[1,3] * (0.09245073226067826 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-1.7429613639823153e-6) * yawVel) + chassis.chassisFrame.R.T[2,3] * ((-0.03544608361872592) * yawVel + (-0.09245073226067826) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,3] * (1.7429613639823153e-6 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.03544608361872592 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2243(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2243};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1992]] /* der(chassis.detailedChassis.spaceFrame.midToFore.shape.r[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9941]] /* chassis.detailedChassis.spaceFrame.sprungBody.v_0[3] DUMMY_STATE */) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((0.09245073226067826) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-1.7429613639823153e-6) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((-0.03544608361872592) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (-0.09245073226067826) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * ((1.7429613639823153e-6) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.03544608361872592) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))));
  threadData->lastEquationSolved = 2243;
}

/*
equation index: 2244
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleFrame.r_0[3] = $DER.chassis.detailedChassis.spaceFrame.midToFore.shape.r[3] + 0.7747 * chassis.chassisFrame.R.T[2,3] * yawVel + (-0.7747) * chassis.chassisFrame.R.T[3,3] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2244(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2244};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1411]] /* der(chassis.detailedChassis.frAxleFrame.r_0[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1992]] /* der(chassis.detailedChassis.spaceFrame.midToFore.shape.r[3]) DUMMY_DER */) + (0.7747) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + (-0.7747) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 2244;
}

/*
equation index: 2245
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rackAndPinion.pinionVisualizer.vis.r[3] = $DER.chassis.detailedChassis.frAxleFrame.r_0[3] + (-0.08618219999999999) * chassis.chassisFrame.R.T[1,3] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.chassisFrame.R.T[2,3] * (0.05715 * yawVel + 0.08618219999999999 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + (-0.05715) * chassis.chassisFrame.R.T[3,3] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2245(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2245};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1125]] /* der(chassis.detailedChassis.frAxleDW.rackAndPinion.pinionVisualizer.vis.r[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1411]] /* der(chassis.detailedChassis.frAxleFrame.r_0[3]) DUMMY_DER */) + (-0.08618219999999999) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((0.05715) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.08618219999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + (-0.05715) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 2245;
}

/*
equation index: 2246
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.vis.r[3] = $DER.chassis.detailedChassis.frAxleDW.rackAndPinion.pinionVisualizer.vis.r[3] + chassis.chassisFrame.R.T[1,3] * (-yawVel) * chassis.detailedChassis.frAxleDW.rackAndPinion.rackAxis.s + chassis.chassisFrame.R.T[2,3] * chassis.detailedChassis.frAxleDW.rackAndPinion.rackAxis.v + chassis.chassisFrame.R.T[3,3] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.rackAndPinion.rackAxis.s
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2246(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2246};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1130]] /* der(chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.vis.r[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1125]] /* der(chassis.detailedChassis.frAxleDW.rackAndPinion.pinionVisualizer.vis.r[3]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * (((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4093]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.rackAxis.s DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4094]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.rackAxis.v DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4093]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.rackAxis.s DUMMY_STATE */)));
  threadData->lastEquationSolved = 2246;
}

/*
equation index: 2247
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rackAndPinion.fromLeft.shape.r[3] = $DER.chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.vis.r[3] - (0.2260092 * chassis.chassisFrame.R.T[1,3] * yawVel + (-0.2260092) * chassis.chassisFrame.R.T[3,3] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2247(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2247};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1122]] /* der(chassis.detailedChassis.frAxleDW.rackAndPinion.fromLeft.shape.r[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1130]] /* der(chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.vis.r[3]) DUMMY_DER */) - ((0.2260092) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + (-0.2260092) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))));
  threadData->lastEquationSolved = 2247;
}

/*
equation index: 2248
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodShape.r[3] = $DER.chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.vis.r[3] + 0.2260092 * chassis.chassisFrame.R.T[1,3] * yawVel + (-0.2260092) * chassis.chassisFrame.R.T[3,3] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2248(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2248};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1223]] /* der(chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodShape.r[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1130]] /* der(chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.vis.r[3]) DUMMY_DER */) + (0.2260092) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + (-0.2260092) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)));
  threadData->lastEquationSolved = 2248;
}

/*
equation index: 2249
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[3] = $DER.chassis.detailedChassis.frAxleFrame.r_0[3] + chassis.chassisFrame.R.T[1,3] * (0.014833600000000002 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-0.2366899) * yawVel) + chassis.chassisFrame.R.T[2,3] * (0.016751299999999997 * yawVel + (-0.014833600000000002) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,3] * (0.2366899 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + (-0.016751299999999997) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2249(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2249};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1053]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1411]] /* der(chassis.detailedChassis.frAxleFrame.r_0[3]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((0.014833600000000002) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-0.2366899) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((0.016751299999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (-0.014833600000000002) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * ((0.2366899) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (-0.016751299999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 2249;
}

/*
equation index: 2250
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.cylinder.r[3] = $DER.chassis.detailedChassis.frAxleFrame.r_0[3] + chassis.chassisFrame.R.T[1,3] * ((-0.119888) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-0.226314) * yawVel) + chassis.chassisFrame.R.T[2,3] * (0.012699999999999996 * yawVel + 0.119888 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,3] * (0.226314 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + (-0.012699999999999996) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2250(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2250};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1024]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.cylinder.r[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1411]] /* der(chassis.detailedChassis.frAxleFrame.r_0[3]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((-0.119888) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-0.226314) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((0.012699999999999996) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.119888) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * ((0.226314) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (-0.012699999999999996) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 2250;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32728(DATA *data, threadData_t *threadData);


/*
equation index: 2252
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] = chassis.chassisFrame.R.T[1,1] * (chassis.detailedChassis.frAxleDW.leftLCABody.v_0[1] - $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[1]) + chassis.chassisFrame.R.T[1,2] * (chassis.detailedChassis.frAxleDW.leftLCABody.v_0[2] - $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[2]) + chassis.chassisFrame.R.T[1,3] * (chassis.detailedChassis.frAxleDW.leftLCABody.v_0[3] - $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[3]) + yawVel * (chassis.chassisFrame.R.T[2,1] * (chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[1] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[1]) + chassis.chassisFrame.R.T[2,2] * (chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[2] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[2]) + chassis.chassisFrame.R.T[2,3] * (chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[3] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[3])) - chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * (chassis.chassisFrame.R.T[3,1] * (chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[1] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[1]) + chassis.chassisFrame.R.T[3,2] * (chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[2] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[2]) + chassis.chassisFrame.R.T[3,3] * (chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[3] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[3]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2252(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2252};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1077]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2689]] /* chassis.detailedChassis.frAxleDW.leftLCABody.v_0[1] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1051]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2690]] /* chassis.detailedChassis.frAxleDW.leftLCABody.v_0[2] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1052]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2691]] /* chassis.detailedChassis.frAxleDW.leftLCABody.v_0[3] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1053]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2647]] /* chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[1] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3771]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2648]] /* chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[2] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3772]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2649]] /* chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[3] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3773]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[3] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2647]] /* chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[1] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3771]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2648]] /* chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[2] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3772]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2649]] /* chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[3] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3773]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[3] DUMMY_STATE */))));
  threadData->lastEquationSolved = 2252;
}

/*
equation index: 2253
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] = chassis.chassisFrame.R.T[2,1] * (chassis.detailedChassis.frAxleDW.leftLCABody.v_0[1] - $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[1]) + chassis.chassisFrame.R.T[2,2] * (chassis.detailedChassis.frAxleDW.leftLCABody.v_0[2] - $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[2]) + chassis.chassisFrame.R.T[2,3] * (chassis.detailedChassis.frAxleDW.leftLCABody.v_0[3] - $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[3]) + chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * (chassis.chassisFrame.R.T[3,1] * (chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[1] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[1]) + chassis.chassisFrame.R.T[3,2] * (chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[2] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[2]) + chassis.chassisFrame.R.T[3,3] * (chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[3] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[3])) - yawVel * (chassis.chassisFrame.R.T[1,1] * (chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[1] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[1]) + chassis.chassisFrame.R.T[1,2] * (chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[2] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[2]) + chassis.chassisFrame.R.T[1,3] * (chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[3] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[3]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2253(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2253};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1078]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2689]] /* chassis.detailedChassis.frAxleDW.leftLCABody.v_0[1] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1051]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2690]] /* chassis.detailedChassis.frAxleDW.leftLCABody.v_0[2] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1052]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2691]] /* chassis.detailedChassis.frAxleDW.leftLCABody.v_0[3] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1053]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2647]] /* chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[1] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3771]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2648]] /* chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[2] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3772]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2649]] /* chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[3] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3773]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[3] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2647]] /* chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[1] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3771]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2648]] /* chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[2] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3772]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2649]] /* chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[3] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3773]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[3] DUMMY_STATE */))));
  threadData->lastEquationSolved = 2253;
}

/*
equation index: 2254
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] = chassis.chassisFrame.R.T[3,1] * (chassis.detailedChassis.frAxleDW.leftLCABody.v_0[1] - $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[1]) + chassis.chassisFrame.R.T[3,2] * (chassis.detailedChassis.frAxleDW.leftLCABody.v_0[2] - $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[2]) + chassis.chassisFrame.R.T[3,3] * (chassis.detailedChassis.frAxleDW.leftLCABody.v_0[3] - $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[3]) + chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * (chassis.chassisFrame.R.T[1,1] * (chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[1] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[1]) + chassis.chassisFrame.R.T[1,2] * (chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[2] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[2]) + chassis.chassisFrame.R.T[1,3] * (chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[3] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[3])) - chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * (chassis.chassisFrame.R.T[2,1] * (chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[1] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[1]) + chassis.chassisFrame.R.T[2,2] * (chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[2] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[2]) + chassis.chassisFrame.R.T[2,3] * (chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[3] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[3]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2254(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2254};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1079]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2689]] /* chassis.detailedChassis.frAxleDW.leftLCABody.v_0[1] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1051]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2690]] /* chassis.detailedChassis.frAxleDW.leftLCABody.v_0[2] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1052]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2691]] /* chassis.detailedChassis.frAxleDW.leftLCABody.v_0[3] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1053]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2647]] /* chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[1] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3771]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2648]] /* chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[2] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3772]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2649]] /* chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[3] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3773]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[3] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2647]] /* chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[1] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3771]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2648]] /* chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[2] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3772]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2649]] /* chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[3] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3773]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[3] DUMMY_STATE */))));
  threadData->lastEquationSolved = 2254;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32739(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32741(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32738(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32742(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32740(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32730(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32729(DATA *data, threadData_t *threadData);


/*
equation index: 2262
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[3] = $DER.chassis.detailedChassis.frAxleFrame.r_0[3] + chassis.chassisFrame.R.T[1,3] * (chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * chassis.detailedChassis.frAxleDW.toRightUpper_i.r[3] - yawVel * chassis.detailedChassis.frAxleDW.toRightUpper_i.r[2]) + chassis.chassisFrame.R.T[2,3] * (yawVel * chassis.detailedChassis.frAxleDW.toRightUpper_i.r[1] - chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.toRightUpper_i.r[3]) + chassis.chassisFrame.R.T[3,3] * (chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.toRightUpper_i.r[2] - chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * chassis.detailedChassis.frAxleDW.toRightUpper_i.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2262(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2262};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1301]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1411]] /* der(chassis.detailedChassis.frAxleFrame.r_0[3]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2554]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2553]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2552]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2554]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2553]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2552]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[1] PARAM */))));
  threadData->lastEquationSolved = 2262;
}

/*
equation index: 2263
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.r[3] = $DER.chassis.detailedChassis.frAxleFrame.r_0[3] + chassis.chassisFrame.R.T[1,3] * (chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * chassis.detailedChassis.frAxleDW.toRightLower_i.r[3] - yawVel * chassis.detailedChassis.frAxleDW.toRightLower_i.r[2]) + chassis.chassisFrame.R.T[2,3] * (yawVel * chassis.detailedChassis.frAxleDW.toRightLower_i.r[1] - chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.toRightLower_i.r[3]) + chassis.chassisFrame.R.T[3,3] * (chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.toRightLower_i.r[2] - chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * chassis.detailedChassis.frAxleDW.toRightLower_i.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2263(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2263};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1272]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.r[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1411]] /* der(chassis.detailedChassis.frAxleFrame.r_0[3]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2522]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2521]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2520]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2522]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2521]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2520]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[1] PARAM */))));
  threadData->lastEquationSolved = 2263;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31778(DATA *data, threadData_t *threadData);


/*
equation index: 2265
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] = chassis.chassisFrame.R.T[1,1] * (chassis.detailedChassis.frAxleDW.rightLCABody.v_0[1] - $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[1]) + chassis.chassisFrame.R.T[1,2] * (chassis.detailedChassis.frAxleDW.rightLCABody.v_0[2] - $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[2]) + chassis.chassisFrame.R.T[1,3] * (chassis.detailedChassis.frAxleDW.rightLCABody.v_0[3] - $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[3]) + yawVel * (chassis.chassisFrame.R.T[2,1] * (chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[1]) + chassis.chassisFrame.R.T[2,2] * (chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[2]) + chassis.chassisFrame.R.T[2,3] * (chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[3])) - chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * (chassis.chassisFrame.R.T[3,1] * (chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[1]) + chassis.chassisFrame.R.T[3,2] * (chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[2]) + chassis.chassisFrame.R.T[3,3] * (chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[3]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2265(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2265};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1326]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4449]] /* chassis.detailedChassis.frAxleDW.rightLCABody.v_0[1] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1299]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4450]] /* chassis.detailedChassis.frAxleDW.rightLCABody.v_0[2] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1300]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4451]] /* chassis.detailedChassis.frAxleDW.rightLCABody.v_0[3] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1301]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4409]] /* chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[1] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5526]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4410]] /* chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[2] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5527]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4411]] /* chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[3] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5528]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[3] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4409]] /* chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[1] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5526]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4410]] /* chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[2] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5527]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4411]] /* chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[3] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5528]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[3] DUMMY_STATE */))));
  threadData->lastEquationSolved = 2265;
}

/*
equation index: 2266
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] = chassis.chassisFrame.R.T[2,1] * (chassis.detailedChassis.frAxleDW.rightLCABody.v_0[1] - $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[1]) + chassis.chassisFrame.R.T[2,2] * (chassis.detailedChassis.frAxleDW.rightLCABody.v_0[2] - $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[2]) + chassis.chassisFrame.R.T[2,3] * (chassis.detailedChassis.frAxleDW.rightLCABody.v_0[3] - $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[3]) + chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * (chassis.chassisFrame.R.T[3,1] * (chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[1]) + chassis.chassisFrame.R.T[3,2] * (chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[2]) + chassis.chassisFrame.R.T[3,3] * (chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[3])) - yawVel * (chassis.chassisFrame.R.T[1,1] * (chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[1]) + chassis.chassisFrame.R.T[1,2] * (chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[2]) + chassis.chassisFrame.R.T[1,3] * (chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[3]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2266(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2266};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1327]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4449]] /* chassis.detailedChassis.frAxleDW.rightLCABody.v_0[1] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1299]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4450]] /* chassis.detailedChassis.frAxleDW.rightLCABody.v_0[2] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1300]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4451]] /* chassis.detailedChassis.frAxleDW.rightLCABody.v_0[3] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1301]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4409]] /* chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[1] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5526]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4410]] /* chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[2] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5527]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4411]] /* chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[3] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5528]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[3] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4409]] /* chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[1] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5526]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4410]] /* chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[2] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5527]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4411]] /* chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[3] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5528]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[3] DUMMY_STATE */))));
  threadData->lastEquationSolved = 2266;
}

/*
equation index: 2267
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] = chassis.chassisFrame.R.T[3,1] * (chassis.detailedChassis.frAxleDW.rightLCABody.v_0[1] - $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[1]) + chassis.chassisFrame.R.T[3,2] * (chassis.detailedChassis.frAxleDW.rightLCABody.v_0[2] - $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[2]) + chassis.chassisFrame.R.T[3,3] * (chassis.detailedChassis.frAxleDW.rightLCABody.v_0[3] - $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[3]) + chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * (chassis.chassisFrame.R.T[1,1] * (chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[1]) + chassis.chassisFrame.R.T[1,2] * (chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[2]) + chassis.chassisFrame.R.T[1,3] * (chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[3])) - chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * (chassis.chassisFrame.R.T[2,1] * (chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[1]) + chassis.chassisFrame.R.T[2,2] * (chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[2]) + chassis.chassisFrame.R.T[2,3] * (chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[3]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2267(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2267};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1328]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4449]] /* chassis.detailedChassis.frAxleDW.rightLCABody.v_0[1] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1299]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4450]] /* chassis.detailedChassis.frAxleDW.rightLCABody.v_0[2] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1300]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4451]] /* chassis.detailedChassis.frAxleDW.rightLCABody.v_0[3] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1301]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4409]] /* chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[1] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5526]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4410]] /* chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[2] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5527]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4411]] /* chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[3] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5528]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[3] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4409]] /* chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[1] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5526]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4410]] /* chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[2] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5527]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4411]] /* chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[3] DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5528]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[3] DUMMY_STATE */))));
  threadData->lastEquationSolved = 2267;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31788(DATA *data, threadData_t *threadData);


/*
equation index: 2269
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.A = (-2.0) * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] + $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] + $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] + $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] + (-chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b) * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a - $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2269(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2269};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1302]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.A) DUMMY_DER */) = (-2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5634]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1326]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1329]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5631]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5635]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1327]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1330]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5632]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5636]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1328]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1331]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5633]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] DUMMY_STATE */)) + ((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5623]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1318]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a) DUMMY_DER */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1319]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5622]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a DUMMY_STATE */))));
  threadData->lastEquationSolved = 2269;
}

/*
equation index: 2270
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.B = 2.0 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2]) + $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2]) + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3]) + $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3]) + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1]) + $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2270(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2270};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1303]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.B) DUMMY_DER */) = (2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5634]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] DUMMY_STATE */)) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1328]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3]) DUMMY_DER */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1327]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2]) DUMMY_DER */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1329]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1]) DUMMY_DER */)) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5633]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] DUMMY_STATE */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5632]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] DUMMY_STATE */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5635]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] DUMMY_STATE */)) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1326]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1]) DUMMY_DER */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1328]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3]) DUMMY_DER */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1330]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2]) DUMMY_DER */)) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5631]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] DUMMY_STATE */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5633]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] DUMMY_STATE */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5636]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] DUMMY_STATE */)) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1327]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2]) DUMMY_DER */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1326]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1]) DUMMY_DER */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1331]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3]) DUMMY_DER */)) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5632]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] DUMMY_STATE */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5631]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] DUMMY_STATE */)))));
  threadData->lastEquationSolved = 2270;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31792(DATA *data, threadData_t *threadData);


/*
equation index: 2272
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.C = 2.0 * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] + 2.0 * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] + 2.0 * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] + 2.0 * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] + 2.0 * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] + 2.0 * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] + (-2.0) * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a + $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2272(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2272};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1304]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.C) DUMMY_DER */) = (2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5631]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1326]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1]) DUMMY_DER */))) + (2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5632]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1327]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2]) DUMMY_DER */))) + (2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5633]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1328]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3]) DUMMY_DER */))) + (2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5634]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1329]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1]) DUMMY_DER */))) + (2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5635]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1330]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2]) DUMMY_DER */))) + (2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5636]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1331]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3]) DUMMY_DER */))) + (-2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5623]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1318]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1319]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5622]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a DUMMY_STATE */)));
  threadData->lastEquationSolved = 2272;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31780(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31779(DATA *data, threadData_t *threadData);


/*
equation index: 2275
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftBellcrank.side_1.vis.r[3] = $DER.chassis.detailedChassis.frAxleFrame.r_0[3] + chassis.chassisFrame.R.T[1,3] * (0.170112000136 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-0.250754351932) * yawVel) + chassis.chassisFrame.R.T[2,3] * ((-0.042144464098) * yawVel + (-0.170112000136) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,3] * (0.250754351932 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2275(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2275};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[904]] /* der(chassis.detailedChassis.frAxleDW.leftBellcrank.side_1.vis.r[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1411]] /* der(chassis.detailedChassis.frAxleFrame.r_0[3]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (-0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * ((0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 2275;
}

/*
equation index: 2276
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightBellcrank.side_1.vis.r[3] = $DER.chassis.detailedChassis.frAxleFrame.r_0[3] + chassis.chassisFrame.R.T[1,3] * ((-0.199898 + BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + 0.250754351932 * yawVel) + chassis.chassisFrame.R.T[2,3] * ((-0.042144464098) * yawVel + (0.199898 - BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,3] * ($DER$BobLib$PUtilities$PMath$PVector$PmirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136}, {0.0, 0.0, 0.0})[3] + (-0.250754351932) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2276(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2276};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1147]] /* der(chassis.detailedChassis.frAxleDW.rightBellcrank.side_1.vis.r[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1411]] /* der(chassis.detailedChassis.frAxleFrame.r_0[3]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((-0.199898 + real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.199898 - (real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * (real_get(omc__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData, _OMC_LIT23, _OMC_LIT25), 2) + (-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 2276;
}

/*
equation index: 2277
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.stabar.toRightBarEnd.shape.r[3] = $DER.chassis.detailedChassis.frAxleFrame.r_0[3] + (-0.08178799999999999) * chassis.chassisFrame.R.T[1,3] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.chassisFrame.R.T[2,3] * ((-0.10664664) * yawVel + 0.08178799999999999 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + 0.10664664 * chassis.chassisFrame.R.T[3,3] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2277(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2277};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1408]] /* der(chassis.detailedChassis.frAxleDW.stabar.toRightBarEnd.shape.r[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1411]] /* der(chassis.detailedChassis.frAxleFrame.r_0[3]) DUMMY_DER */) + (-0.08178799999999999) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((-0.10664664) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.08178799999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + (0.10664664) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 2277;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29420(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29428(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29429(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29431(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29430(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29427(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29426(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30805(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30812(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30811(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30810(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30814(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30816(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30813(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30817(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30815(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30806(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29425(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29424(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29866(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29873(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29872(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29871(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29874(DATA *data, threadData_t *threadData);


/*
equation index: 2302
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.A = (-2.0) * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] + $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] + $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] + $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] + (-chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a - $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2302(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2302};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1866]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.A) DUMMY_DER */) = (-2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9391]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1890]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1893]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9388]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9392]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1891]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1894]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9389]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9393]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1892]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1895]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9390]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] DUMMY_STATE */)) + ((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9380]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1882]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a) DUMMY_DER */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1883]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9379]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a DUMMY_STATE */))));
  threadData->lastEquationSolved = 2302;
}

/*
equation index: 2303
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.B = 2.0 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2]) + $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2]) + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3]) + $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3]) + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1]) + $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2303(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2303};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1867]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.B) DUMMY_DER */) = (2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9391]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] DUMMY_STATE */)) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1892]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3]) DUMMY_DER */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1891]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2]) DUMMY_DER */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1893]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1]) DUMMY_DER */)) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9390]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] DUMMY_STATE */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9389]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] DUMMY_STATE */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9392]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] DUMMY_STATE */)) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1890]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1]) DUMMY_DER */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1892]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3]) DUMMY_DER */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1894]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2]) DUMMY_DER */)) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9388]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] DUMMY_STATE */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9390]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] DUMMY_STATE */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9393]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] DUMMY_STATE */)) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1891]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2]) DUMMY_DER */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1890]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1]) DUMMY_DER */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1895]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3]) DUMMY_DER */)) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9389]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] DUMMY_STATE */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9388]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] DUMMY_STATE */)))));
  threadData->lastEquationSolved = 2303;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29878(DATA *data, threadData_t *threadData);


/*
equation index: 2305
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.C = 2.0 * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] + 2.0 * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] + 2.0 * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] + 2.0 * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] + 2.0 * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] + 2.0 * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] + (-2.0) * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a + $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2305(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2305};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1868]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.C) DUMMY_DER */) = (2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9388]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1890]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1]) DUMMY_DER */))) + (2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9389]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1891]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2]) DUMMY_DER */))) + (2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9390]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1892]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3]) DUMMY_DER */))) + (2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9391]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1893]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1]) DUMMY_DER */))) + (2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9392]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1894]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2]) DUMMY_DER */))) + (2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9393]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1895]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3]) DUMMY_DER */))) + (-2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9380]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1882]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1883]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9379]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a DUMMY_STATE */)));
  threadData->lastEquationSolved = 2305;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29867(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29423(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29422(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29421(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29456(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29459(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29129(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29044(DATA *data, threadData_t *threadData);


/*
equation index: 2314
type: SIMPLE_ASSIGN
aeroModel.bodyVelocity[3] = chassis.chassisFrame.R.T[3,1] * $DER.aeroModel.sprungChassisFrame.r_0[1] + chassis.chassisFrame.R.T[3,2] * $DER.aeroModel.sprungChassisFrame.r_0[2] + chassis.chassisFrame.R.T[3,3] * $DER.aeroModel.sprungChassisFrame.r_0[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2314(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2314};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2207]] /* aeroModel.bodyVelocity[3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[873]] /* der(aeroModel.sprungChassisFrame.r_0[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[874]] /* der(aeroModel.sprungChassisFrame.r_0[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[875]] /* der(aeroModel.sprungChassisFrame.r_0[3]) DUMMY_DER */));
  threadData->lastEquationSolved = 2314;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29046(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29140(DATA *data, threadData_t *threadData);


/*
equation index: 2317
type: SIMPLE_ASSIGN
aeroModel.speedScale = max(atmosphere.rho, 0.0) * (aeroModel.relativeAirSpeed / aeroModel.pAero.referenceSpeed) ^ 2.0 / aeroModel.pAero.referenceDensity
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2317(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2317};
  modelica_real tmp658;
  tmp658 = DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2216]] /* aeroModel.relativeAirSpeed variable */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[151]] /* aeroModel.pAero.referenceSpeed PARAM */),"aeroModel.pAero.referenceSpeed",equationIndexes);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2222]] /* aeroModel.speedScale variable */) = (fmax((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[174]] /* atmosphere.rho PARAM */),0.0)) * (DIVISION_SIM((tmp658 * tmp658),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[150]] /* aeroModel.pAero.referenceDensity PARAM */),"aeroModel.pAero.referenceDensity",equationIndexes));
  threadData->lastEquationSolved = 2317;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29142(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29047(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29144(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29235(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29233(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29234(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29145(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29146(DATA *data, threadData_t *threadData);


/*
equation index: 2326
type: SIMPLE_ASSIGN
vcu.speedPI.I.y = (vcu.speedPI.addPID.y - (vcu.speedPI.addPID.k1 * vcu.speedPI.P.y + vcu.speedPI.addPID.k2 * vcu.speedPI.Dzero.k)) / vcu.speedPI.addPID.k3
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2326(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2326};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[45]] /* vcu.speedPI.I.y STATE(1) */) = DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10316]] /* vcu.speedPI.addPID.y variable */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6850]] /* vcu.speedPI.addPID.k1 PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10313]] /* vcu.speedPI.P.y variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6851]] /* vcu.speedPI.addPID.k2 PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6834]] /* vcu.speedPI.Dzero.k PARAM */))),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6852]] /* vcu.speedPI.addPID.k3 PARAM */),"vcu.speedPI.addPID.k3",equationIndexes);
  threadData->lastEquationSolved = 2326;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29246(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29247(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29248(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29398(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29399(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29400(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29401(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29402(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29403(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29404(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29405(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29406(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29407(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29408(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29410(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29409(DATA *data, threadData_t *threadData);


/*
equation index: 2343
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightShockLinkage.frame_b.r_0[3] = $DER.chassis.detailedChassis.frAxleFrame.r_0[3] + chassis.chassisFrame.R.T[1,3] * ((-0.199898 + BobLib.Utilities.Math.Vector.mirrorXZ({-0.020673469702, 0.247847085458, 0.561456926868})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + 0.247847085458 * yawVel) + chassis.chassisFrame.R.T[2,3] * ((-0.020673469702) * yawVel + (0.199898 - BobLib.Utilities.Math.Vector.mirrorXZ({-0.020673469702, 0.247847085458, 0.561456926868})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,3] * ($DER$BobLib$PUtilities$PMath$PVector$PmirrorXZ({-0.020673469702, 0.247847085458, 0.561456926868}, {0.0, 0.0, 0.0})[3] + (-0.247847085458) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.020673469702 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2343(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2343};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1211]] /* der(chassis.detailedChassis.frAxleDW.rightShockLinkage.frame_b.r_0[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1411]] /* der(chassis.detailedChassis.frAxleFrame.r_0[3]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((-0.199898 + real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT24), 2)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (0.247847085458) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((-0.020673469702) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.199898 - (real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT24), 2))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * (real_get(omc__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData, _OMC_LIT24, _OMC_LIT25), 2) + (-0.247847085458) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.020673469702) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 2343;
}

/*
equation index: 2344
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftShockLinkage.frame_b.r_0[3] = $DER.chassis.detailedChassis.frAxleFrame.r_0[3] + chassis.chassisFrame.R.T[1,3] * (0.36155892686799995 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-0.247847085458) * yawVel) + chassis.chassisFrame.R.T[2,3] * ((-0.020673469702) * yawVel + (-0.36155892686799995) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,3] * (0.247847085458 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.020673469702 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2344(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2344};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[968]] /* der(chassis.detailedChassis.frAxleDW.leftShockLinkage.frame_b.r_0[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1411]] /* der(chassis.detailedChassis.frAxleFrame.r_0[3]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((0.36155892686799995) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-0.247847085458) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((-0.020673469702) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (-0.36155892686799995) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * ((0.247847085458) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.020673469702) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 2344;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29249(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31473(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31469(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31472(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31471(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31470(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29250(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31478(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31474(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31477(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31476(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31475(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29251(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29252(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32249(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32254(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29253(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29254(DATA *data, threadData_t *threadData);


/*
equation index: 2363
type: SIMPLE_ASSIGN
$DER.chassis.chassisFrame.R.T[1,2] = sin(chassis.cgFreeMotion.phi[3]) * (-sin(chassis.cgFreeMotion.phi[1])) * chassis.cgFreeMotion.phi_d[1] + cos(chassis.cgFreeMotion.phi[3]) * chassis.cgFreeMotion.phi_d[3] * cos(chassis.cgFreeMotion.phi[1]) + cos(chassis.cgFreeMotion.phi[3]) * (chassis.chassisFrame.R.T[3,1] * cos(chassis.cgFreeMotion.phi[1]) * chassis.cgFreeMotion.phi_d[1] + $DER.chassis.chassisFrame.R.T[3,1] * sin(chassis.cgFreeMotion.phi[1])) - sin(chassis.cgFreeMotion.phi[3]) * chassis.cgFreeMotion.phi_d[3] * chassis.chassisFrame.R.T[3,1] * sin(chassis.cgFreeMotion.phi[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2363(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2363};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[880]] /* der(chassis.chassisFrame.R.T[1,2]) DUMMY_DER */) = (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* chassis.cgFreeMotion.phi_d[1] STATE(1,chassis.cgFreeMotion.phi_dd[1]) */))) + (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* chassis.cgFreeMotion.phi_d[3] STATE(1,chassis.cgFreeMotion.phi_dd[3]) */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */)))) + (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* chassis.cgFreeMotion.phi_d[1] STATE(1,chassis.cgFreeMotion.phi_dd[1]) */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[885]] /* der(chassis.chassisFrame.R.T[3,1]) DUMMY_DER */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */)))) - ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* chassis.cgFreeMotion.phi_d[3] STATE(1,chassis.cgFreeMotion.phi_dd[3]) */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */))))));
  threadData->lastEquationSolved = 2363;
}

/*
equation index: 2364
type: SIMPLE_ASSIGN
$DER.chassis.chassisFrame.R.T[1,3] = sin(chassis.cgFreeMotion.phi[3]) * cos(chassis.cgFreeMotion.phi[1]) * chassis.cgFreeMotion.phi_d[1] + cos(chassis.cgFreeMotion.phi[3]) * chassis.cgFreeMotion.phi_d[3] * sin(chassis.cgFreeMotion.phi[1]) + sin(chassis.cgFreeMotion.phi[3]) * chassis.cgFreeMotion.phi_d[3] * chassis.chassisFrame.R.T[3,1] * cos(chassis.cgFreeMotion.phi[1]) - cos(chassis.cgFreeMotion.phi[3]) * (chassis.chassisFrame.R.T[3,1] * (-sin(chassis.cgFreeMotion.phi[1])) * chassis.cgFreeMotion.phi_d[1] + $DER.chassis.chassisFrame.R.T[3,1] * cos(chassis.cgFreeMotion.phi[1]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2364(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2364};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[881]] /* der(chassis.chassisFrame.R.T[1,3]) DUMMY_DER */) = (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* chassis.cgFreeMotion.phi_d[1] STATE(1,chassis.cgFreeMotion.phi_dd[1]) */))) + (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* chassis.cgFreeMotion.phi_d[3] STATE(1,chassis.cgFreeMotion.phi_dd[3]) */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */)))) + (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* chassis.cgFreeMotion.phi_d[3] STATE(1,chassis.cgFreeMotion.phi_dd[3]) */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */))))) - ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* chassis.cgFreeMotion.phi_d[1] STATE(1,chassis.cgFreeMotion.phi_dd[1]) */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[885]] /* der(chassis.chassisFrame.R.T[3,1]) DUMMY_DER */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */)))));
  threadData->lastEquationSolved = 2364;
}

/*
equation index: 2365
type: SIMPLE_ASSIGN
$DER.chassis.chassisFrame.R.T[2,2] = cos(chassis.cgFreeMotion.phi[3]) * (-sin(chassis.cgFreeMotion.phi[1])) * chassis.cgFreeMotion.phi_d[1] + (-sin(chassis.cgFreeMotion.phi[3])) * (chassis.chassisFrame.R.T[3,1] * cos(chassis.cgFreeMotion.phi[1]) * chassis.cgFreeMotion.phi_d[1] + $DER.chassis.chassisFrame.R.T[3,1] * sin(chassis.cgFreeMotion.phi[1])) - cos(chassis.cgFreeMotion.phi[3]) * chassis.cgFreeMotion.phi_d[3] * chassis.chassisFrame.R.T[3,1] * sin(chassis.cgFreeMotion.phi[1]) - sin(chassis.cgFreeMotion.phi[3]) * chassis.cgFreeMotion.phi_d[3] * cos(chassis.cgFreeMotion.phi[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2365(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2365};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[883]] /* der(chassis.chassisFrame.R.T[2,2]) DUMMY_DER */) = (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* chassis.cgFreeMotion.phi_d[1] STATE(1,chassis.cgFreeMotion.phi_dd[1]) */))) + ((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* chassis.cgFreeMotion.phi_d[1] STATE(1,chassis.cgFreeMotion.phi_dd[1]) */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[885]] /* der(chassis.chassisFrame.R.T[3,1]) DUMMY_DER */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */)))) - ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* chassis.cgFreeMotion.phi_d[3] STATE(1,chassis.cgFreeMotion.phi_dd[3]) */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */)))))) - ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* chassis.cgFreeMotion.phi_d[3] STATE(1,chassis.cgFreeMotion.phi_dd[3]) */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */)))));
  threadData->lastEquationSolved = 2365;
}

/*
equation index: 2366
type: SIMPLE_ASSIGN
$DER.chassis.chassisFrame.R.T[2,3] = cos(chassis.cgFreeMotion.phi[3]) * cos(chassis.cgFreeMotion.phi[1]) * chassis.cgFreeMotion.phi_d[1] + sin(chassis.cgFreeMotion.phi[3]) * (chassis.chassisFrame.R.T[3,1] * (-sin(chassis.cgFreeMotion.phi[1])) * chassis.cgFreeMotion.phi_d[1] + $DER.chassis.chassisFrame.R.T[3,1] * cos(chassis.cgFreeMotion.phi[1])) + cos(chassis.cgFreeMotion.phi[3]) * chassis.cgFreeMotion.phi_d[3] * chassis.chassisFrame.R.T[3,1] * cos(chassis.cgFreeMotion.phi[1]) - sin(chassis.cgFreeMotion.phi[3]) * chassis.cgFreeMotion.phi_d[3] * sin(chassis.cgFreeMotion.phi[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2366(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2366};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[884]] /* der(chassis.chassisFrame.R.T[2,3]) DUMMY_DER */) = (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* chassis.cgFreeMotion.phi_d[1] STATE(1,chassis.cgFreeMotion.phi_dd[1]) */))) + (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* chassis.cgFreeMotion.phi_d[1] STATE(1,chassis.cgFreeMotion.phi_dd[1]) */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[885]] /* der(chassis.chassisFrame.R.T[3,1]) DUMMY_DER */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */)))) + (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* chassis.cgFreeMotion.phi_d[3] STATE(1,chassis.cgFreeMotion.phi_dd[3]) */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */))))) - ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* chassis.cgFreeMotion.phi_d[3] STATE(1,chassis.cgFreeMotion.phi_dd[3]) */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */)))));
  threadData->lastEquationSolved = 2366;
}

/*
equation index: 2367
type: SIMPLE_ASSIGN
$DER.chassis.chassisFrame.R.T[3,2] = sin(chassis.cgFreeMotion.phi[2]) * chassis.cgFreeMotion.phi_d[2] * sin(chassis.cgFreeMotion.phi[1]) - cos(chassis.cgFreeMotion.phi[2]) * cos(chassis.cgFreeMotion.phi[1]) * chassis.cgFreeMotion.phi_d[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2367(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2367};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[886]] /* der(chassis.chassisFrame.R.T[3,2]) DUMMY_DER */) = (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* chassis.cgFreeMotion.phi[2] STATE(1,chassis.cgFreeMotion.phi_d[2]) */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* chassis.cgFreeMotion.phi_d[2] STATE(1,chassis.cgFreeMotion.phi_dd[2]) */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */)))) - ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* chassis.cgFreeMotion.phi[2] STATE(1,chassis.cgFreeMotion.phi_d[2]) */))) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* chassis.cgFreeMotion.phi_d[1] STATE(1,chassis.cgFreeMotion.phi_dd[1]) */))));
  threadData->lastEquationSolved = 2367;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32720(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32824(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32823(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31871(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31876(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31884(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29465(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29470(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29475(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31115(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31120(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31128(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30125(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30130(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30138(DATA *data, threadData_t *threadData);


/*
equation index: 2383
type: SIMPLE_ASSIGN
$DER.chassis.chassisFrame.R.T[3,3] = cos(chassis.cgFreeMotion.phi[2]) * (-sin(chassis.cgFreeMotion.phi[1])) * chassis.cgFreeMotion.phi_d[1] - sin(chassis.cgFreeMotion.phi[2]) * chassis.cgFreeMotion.phi_d[2] * cos(chassis.cgFreeMotion.phi[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2383(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2383};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[887]] /* der(chassis.chassisFrame.R.T[3,3]) DUMMY_DER */) = (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* chassis.cgFreeMotion.phi[2] STATE(1,chassis.cgFreeMotion.phi_d[2]) */))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* chassis.cgFreeMotion.phi_d[1] STATE(1,chassis.cgFreeMotion.phi_dd[1]) */))) - ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* chassis.cgFreeMotion.phi[2] STATE(1,chassis.cgFreeMotion.phi_d[2]) */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* chassis.cgFreeMotion.phi_d[2] STATE(1,chassis.cgFreeMotion.phi_dd[2]) */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */)))));
  threadData->lastEquationSolved = 2383;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32721(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32829(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32828(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31872(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31877(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31888(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29466(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29471(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29476(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31116(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31121(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31132(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30126(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30131(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30142(DATA *data, threadData_t *threadData);


/*
equation index: 2399
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodLength = sqrt(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2399(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2399};
  real_array tmp659;
  real_array tmp660;
  modelica_real tmp661;
  real_array_create(&tmp659, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3849]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp660, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3849]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp661 = mul_real_scalar_product(tmp659, tmp660);
  if(!(tmp661 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia) was %g should be >= 0", tmp661);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3854]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodLength PARAM */) = sqrt(tmp661);
  threadData->lastEquationSolved = 2399;
}

/*
equation index: 2400
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.rodLength = 0.2662364442299615
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2400(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2400};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2762]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.rodLength PARAM */) = 0.2662364442299615;
  threadData->lastEquationSolved = 2400;
}

/*
equation index: 2401
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodLength = sqrt(chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2401(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2401};
  real_array tmp662;
  real_array tmp663;
  modelica_real tmp664;
  real_array_create(&tmp662, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3954]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp663, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3954]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp664 = mul_real_scalar_product(tmp662, tmp663);
  if(!(tmp664 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia) was %g should be >= 0", tmp664);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3959]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodLength PARAM */) = sqrt(tmp664);
  threadData->lastEquationSolved = 2401;
}

/*
equation index: 2402
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodLength = 0.3070684716089231
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2402(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2402};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2870]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodLength PARAM */) = 0.3070684716089231;
  threadData->lastEquationSolved = 2402;
}

/*
equation index: 2403
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rodLength = sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2403(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2403};
  real_array tmp665;
  real_array tmp666;
  modelica_real tmp667;
  real_array_create(&tmp665, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4497]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp666, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4497]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp667 = mul_real_scalar_product(tmp665, tmp666);
  if(!(tmp667 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia) was %g should be >= 0", tmp667);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4502]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rodLength PARAM */) = sqrt(tmp667);
  threadData->lastEquationSolved = 2403;
}

/*
equation index: 2404
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1Length = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rodLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2404(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2404};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4506]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1Length PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4502]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rodLength PARAM */);
  threadData->lastEquationSolved = 2404;
}

/*
equation index: 2405
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.lengthConstraint = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1Length
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2405(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2405};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4475]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.lengthConstraint PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4506]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1Length PARAM */);
  threadData->lastEquationSolved = 2405;
}

/*
equation index: 2406
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.C = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] ^ 2.0 + (-2.0) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.lengthConstraint ^ 2.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2406(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2406};
  modelica_real tmp668;
  modelica_real tmp669;
  modelica_real tmp670;
  modelica_real tmp671;
  modelica_real tmp672;
  modelica_real tmp673;
  modelica_real tmp674;
  tmp668 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9388]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] DUMMY_STATE */);
  tmp669 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9389]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] DUMMY_STATE */);
  tmp670 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9390]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] DUMMY_STATE */);
  tmp671 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9391]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] DUMMY_STATE */);
  tmp672 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9392]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] DUMMY_STATE */);
  tmp673 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9393]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] DUMMY_STATE */);
  tmp674 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4475]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.lengthConstraint PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9349]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.C DUMMY_STATE */) = (tmp668 * tmp668) + (tmp669 * tmp669) + (tmp670 * tmp670) + (tmp671 * tmp671) + (tmp672 * tmp672) + (tmp673 * tmp673) + (-2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9380]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9379]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a DUMMY_STATE */))) - ((tmp674 * tmp674));
  threadData->lastEquationSolved = 2406;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29513(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29514(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29515(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29879(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29880(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29881(DATA *data, threadData_t *threadData);


/*
equation index: 2413
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.positiveBranch = BobLib.Experiments.Standards.VehicleSim.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.selectBranch(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.lengthConstraint, chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e, 0.017453292519943295 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.phi_offset + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.phi_guess), chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a, chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2413(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2413};
  real_array tmp675;
  real_array tmp676;
  real_array tmp677;
  real_array_create(&tmp675, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp676, ((modelica_real*)&((&data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9388]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] DUMMY_STATE */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp677, ((modelica_real*)&((&data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9391]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] DUMMY_STATE */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  (data->simulationInfo->booleanParameter[data->simulationInfo->booleanParamsIndex[463]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.positiveBranch PARAM */) = omc_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_rrAxleDW_rightWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4475]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.lengthConstraint PARAM */), tmp675, (0.017453292519943295) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4480]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.phi_offset PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4479]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.phi_guess PARAM */)), tmp676, tmp677);
  threadData->lastEquationSolved = 2413;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29517(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29516(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29518(DATA *data, threadData_t *threadData);


/*
equation index: 2417
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] ^ 2.0 + (1.0 - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] ^ 2.0) * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2417(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2417};
  modelica_real tmp678;
  modelica_real tmp679;
  tmp678 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */);
  tmp679 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9350]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,1] DUMMY_STATE */) = (tmp678 * tmp678) + (1.0 - ((tmp679 * tmp679))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 2417;
}

/*
equation index: 2418
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,2] = (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2418(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2418};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9351]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,2] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 2418;
}

/*
equation index: 2419
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,3] = (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2419(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2419};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9352]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,3] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))));
  threadData->lastEquationSolved = 2419;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29543(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29539(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29536(DATA *data, threadData_t *threadData);


/*
equation index: 2423
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,1] = (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2423(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2423};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9353]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,1] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))));
  threadData->lastEquationSolved = 2423;
}

/*
equation index: 2424
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] ^ 2.0 + (1.0 - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] ^ 2.0) * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2424(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2424};
  modelica_real tmp680;
  modelica_real tmp681;
  tmp680 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */);
  tmp681 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9354]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,2] DUMMY_STATE */) = (tmp680 * tmp680) + (1.0 - ((tmp681 * tmp681))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 2424;
}

/*
equation index: 2425
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,3] = (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2425(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2425};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9355]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,3] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 2425;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29532(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29531(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29530(DATA *data, threadData_t *threadData);


/*
equation index: 2429
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,1] = (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2429(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2429};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9356]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,1] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 2429;
}

/*
equation index: 2430
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,2] = (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2430(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2430};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9357]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,2] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))));
  threadData->lastEquationSolved = 2430;
}

/*
equation index: 2431
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] ^ 2.0 + (1.0 - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] ^ 2.0) * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2431(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2431};
  modelica_real tmp682;
  modelica_real tmp683;
  tmp682 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */);
  tmp683 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9358]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,3] DUMMY_STATE */) = (tmp682 * tmp682) + (1.0 - ((tmp683 * tmp683))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 2431;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29526(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29544(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29545(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29556(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29525(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29540(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29541(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29542(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29524(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29537(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29715(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29718(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29719(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29716(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29717(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29730(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29731(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29732(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29733(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29734(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29735(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29736(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29737(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29740(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29739(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29738(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29741(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29744(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29743(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29742(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29751(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29753(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29752(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29756(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29748(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29750(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29749(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29755(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29745(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29747(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29746(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29754(DATA *data, threadData_t *threadData);


void BobLib_Experiments_Standards_VehicleSim_eqFunction_2474(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2475(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2476(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2477(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2478(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2479(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2480(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2481(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2482(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2483(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2484(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2485(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2486(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2487(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2488(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2489(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2490(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2491(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2492(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2493(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2494(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2495(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2496(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2497(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2498(DATA*, threadData_t*);
/*
equation index: 2526
indexNonlinear: 2
type: NONLINEAR

vars: {chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.phi}
eqns: {2474, 2475, 2476, 2477, 2478, 2479, 2480, 2481, 2482, 2483, 2484, 2485, 2486, 2487, 2488, 2489, 2490, 2491, 2492, 2493, 2494, 2495, 2496, 2497, 2498}
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2526(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2526};
  int retValue;
  infoStreamPrint(OMC_LOG_DT, 0, "Solving nonlinear system 2526 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
  /* get old value */
  data->simulationInfo->nonlinearSystemData[2].nlsxOld[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9195]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.phi DUMMY_STATE */);
  retValue = solve_nonlinear_system(data, threadData, 2);
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,2526};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving non-linear system 2526 failed at time=%.15g.\nFor more information please use -lv LOG_NLS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9195]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.phi DUMMY_STATE */) = data->simulationInfo->nonlinearSystemData[2].nlsx[0];
  threadData->lastEquationSolved = 2526;
}

/*
equation index: 2527
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.e_xw[1] = chassis.detailedChassis.frameRR.R.T[1,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2527(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2527};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8606]] /* chassis.detailedChassis.rrAxleDW.rightTire.e_xw[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6113]] /* chassis.detailedChassis.frameRR.R.T[1,1] DUMMY_STATE */);
  threadData->lastEquationSolved = 2527;
}

/*
equation index: 2528
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.e_xw[2] = chassis.detailedChassis.frameRR.R.T[1,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2528(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2528};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8607]] /* chassis.detailedChassis.rrAxleDW.rightTire.e_xw[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6114]] /* chassis.detailedChassis.frameRR.R.T[1,2] DUMMY_STATE */);
  threadData->lastEquationSolved = 2528;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29815(DATA *data, threadData_t *threadData);


/*
equation index: 2530
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.e_xw[3] = chassis.detailedChassis.frameRR.R.T[1,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2530(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2530};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8608]] /* chassis.detailedChassis.rrAxleDW.rightTire.e_xw[3] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6115]] /* chassis.detailedChassis.frameRR.R.T[1,3] DUMMY_STATE */);
  threadData->lastEquationSolved = 2530;
}

/*
equation index: 2531
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.e_yw[1] = chassis.detailedChassis.frameRR.R.T[2,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2531(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2531};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8612]] /* chassis.detailedChassis.rrAxleDW.rightTire.e_yw[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6116]] /* chassis.detailedChassis.frameRR.R.T[2,1] DUMMY_STATE */);
  threadData->lastEquationSolved = 2531;
}

/*
equation index: 2532
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.e_yw[2] = chassis.detailedChassis.frameRR.R.T[2,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2532(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2532};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8613]] /* chassis.detailedChassis.rrAxleDW.rightTire.e_yw[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6117]] /* chassis.detailedChassis.frameRR.R.T[2,2] DUMMY_STATE */);
  threadData->lastEquationSolved = 2532;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29822(DATA *data, threadData_t *threadData);


/*
equation index: 2534
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.e_yw[3] = chassis.detailedChassis.frameRR.R.T[2,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2534(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2534};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8614]] /* chassis.detailedChassis.rrAxleDW.rightTire.e_yw[3] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6118]] /* chassis.detailedChassis.frameRR.R.T[2,3] DUMMY_STATE */);
  threadData->lastEquationSolved = 2534;
}

/*
equation index: 2535
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.frame_a.r_0[2] = chassis.detailedChassis.rrAxleDW.rightLCABody.frame_a.r_0[2] + chassis.detailedChassis.frameRR.R.T[1,2] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1] + chassis.detailedChassis.frameRR.R.T[2,2] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2] + chassis.detailedChassis.frameRR.R.T[3,2] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2535(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2535};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8997]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.frame_a.r_0[2] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8167]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.frame_a.r_0[2] DUMMY_STATE */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6114]] /* chassis.detailedChassis.frameRR.R.T[1,2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4817]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6117]] /* chassis.detailedChassis.frameRR.R.T[2,2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4818]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6120]] /* chassis.detailedChassis.frameRR.R.T[3,2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4819]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3] PARAM */));
  threadData->lastEquationSolved = 2535;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29826(DATA *data, threadData_t *threadData);


/*
equation index: 2537
type: SIMPLE_ASSIGN
chassis.detailedChassis.frameRR.r_0[2] = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.wheelVelSensor.der1[2].u - chassis.detailedChassis.frameRR.R.T[3,2] * chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.s
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2537(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2537};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6126]] /* chassis.detailedChassis.frameRR.r_0[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8794]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.wheelVelSensor.der1[2].u DUMMY_STATE */) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6120]] /* chassis.detailedChassis.frameRR.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8739]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.s DUMMY_STATE */)));
  threadData->lastEquationSolved = 2537;
}

/*
equation index: 2538
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[3,2] = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,1] * chassis.detailedChassis.frameRR.R.T[1,2] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,2] * chassis.detailedChassis.frameRR.R.T[2,2] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,3] * chassis.detailedChassis.frameRR.R.T[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2538(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2538};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8787]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[3,2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8688]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6114]] /* chassis.detailedChassis.frameRR.R.T[1,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8689]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6117]] /* chassis.detailedChassis.frameRR.R.T[2,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8690]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6120]] /* chassis.detailedChassis.frameRR.R.T[3,2] DUMMY_STATE */));
  threadData->lastEquationSolved = 2538;
}

/*
equation index: 2539
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[2,2] = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,1] * chassis.detailedChassis.frameRR.R.T[1,2] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,2] * chassis.detailedChassis.frameRR.R.T[2,2] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,3] * chassis.detailedChassis.frameRR.R.T[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2539(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2539};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8785]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[2,2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8685]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6114]] /* chassis.detailedChassis.frameRR.R.T[1,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8686]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6117]] /* chassis.detailedChassis.frameRR.R.T[2,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8687]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6120]] /* chassis.detailedChassis.frameRR.R.T[3,2] DUMMY_STATE */));
  threadData->lastEquationSolved = 2539;
}

/*
equation index: 2540
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.e_spin[2] = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[2,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2540(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2540};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8601]] /* chassis.detailedChassis.rrAxleDW.rightTire.e_spin[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8785]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[2,2] variable */);
  threadData->lastEquationSolved = 2540;
}

/*
equation index: 2541
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[1,2] = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,1] * chassis.detailedChassis.frameRR.R.T[1,2] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,2] * chassis.detailedChassis.frameRR.R.T[2,2] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,3] * chassis.detailedChassis.frameRR.R.T[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2541(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2541};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8783]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[1,2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8682]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6114]] /* chassis.detailedChassis.frameRR.R.T[1,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8683]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6117]] /* chassis.detailedChassis.frameRR.R.T[2,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8684]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6120]] /* chassis.detailedChassis.frameRR.R.T[3,2] DUMMY_STATE */));
  threadData->lastEquationSolved = 2541;
}

/*
equation index: 2542
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.frame_a.r_0[1] = chassis.detailedChassis.rrAxleDW.rightLCABody.frame_a.r_0[1] + chassis.detailedChassis.frameRR.R.T[1,1] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1] + chassis.detailedChassis.frameRR.R.T[2,1] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2] + chassis.detailedChassis.frameRR.R.T[3,1] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2542(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2542};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8996]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.frame_a.r_0[1] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8166]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.frame_a.r_0[1] DUMMY_STATE */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6113]] /* chassis.detailedChassis.frameRR.R.T[1,1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4817]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6116]] /* chassis.detailedChassis.frameRR.R.T[2,1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4818]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6119]] /* chassis.detailedChassis.frameRR.R.T[3,1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4819]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3] PARAM */));
  threadData->lastEquationSolved = 2542;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29820(DATA *data, threadData_t *threadData);


/*
equation index: 2544
type: SIMPLE_ASSIGN
chassis.detailedChassis.frameRR.r_0[1] = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.wheelVelSensor.der1[1].u - chassis.detailedChassis.frameRR.R.T[3,1] * chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.s
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2544(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2544};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6125]] /* chassis.detailedChassis.frameRR.r_0[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8793]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.wheelVelSensor.der1[1].u DUMMY_STATE */) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6119]] /* chassis.detailedChassis.frameRR.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8739]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.s DUMMY_STATE */)));
  threadData->lastEquationSolved = 2544;
}

/*
equation index: 2545
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[3,1] = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,1] * chassis.detailedChassis.frameRR.R.T[1,1] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,2] * chassis.detailedChassis.frameRR.R.T[2,1] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,3] * chassis.detailedChassis.frameRR.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2545(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2545};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8786]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[3,1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8688]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6113]] /* chassis.detailedChassis.frameRR.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8689]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6116]] /* chassis.detailedChassis.frameRR.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8690]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6119]] /* chassis.detailedChassis.frameRR.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 2545;
}

/*
equation index: 2546
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[2,1] = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,1] * chassis.detailedChassis.frameRR.R.T[1,1] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,2] * chassis.detailedChassis.frameRR.R.T[2,1] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,3] * chassis.detailedChassis.frameRR.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2546(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2546};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8784]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[2,1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8685]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6113]] /* chassis.detailedChassis.frameRR.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8686]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6116]] /* chassis.detailedChassis.frameRR.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8687]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6119]] /* chassis.detailedChassis.frameRR.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 2546;
}

/*
equation index: 2547
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.e_spin[1] = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[2,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2547(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2547};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8600]] /* chassis.detailedChassis.rrAxleDW.rightTire.e_spin[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8784]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[2,1] variable */);
  threadData->lastEquationSolved = 2547;
}

/*
equation index: 2548
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[1,1] = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,1] * chassis.detailedChassis.frameRR.R.T[1,1] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,2] * chassis.detailedChassis.frameRR.R.T[2,1] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,3] * chassis.detailedChassis.frameRR.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2548(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2548};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8782]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[1,1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8682]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6113]] /* chassis.detailedChassis.frameRR.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8683]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6116]] /* chassis.detailedChassis.frameRR.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8684]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6119]] /* chassis.detailedChassis.frameRR.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 2548;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29828(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29829(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29830(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29831(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29832(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29833(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29835(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29834(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29836(DATA *data, threadData_t *threadData);


/*
equation index: 2558
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.f_b_a1[1] = chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e3_a[1] * (chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_a[2] * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.t_ia_a[2] + chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_a[3] * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.t_ia_a[3]) / chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2558(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2558};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8491]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.f_b_a1[1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8482]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e3_a[1] variable */)) * (DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8480]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_a[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8579]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.t_ia_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8481]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_a[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8580]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.t_ia_a[3] variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3959]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodLength PARAM */),"chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodLength",equationIndexes));
  threadData->lastEquationSolved = 2558;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29837(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29838(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29855(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29851(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29847(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29843(DATA *data, threadData_t *threadData);


/*
equation index: 2565
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.f_b_a1[3] = chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e3_a[3] * (chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_a[2] * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.t_ia_a[2] + chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_a[3] * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.t_ia_a[3]) / chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodLength - chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_a[3] * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.t_ia_a[1] / (chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e3_a[1] * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodLength)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2565(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2565};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8493]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.f_b_a1[3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8484]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e3_a[3] variable */)) * (DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8480]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_a[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8579]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.t_ia_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8481]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_a[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8580]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.t_ia_a[3] variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3959]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodLength PARAM */),"chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodLength",equationIndexes)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8481]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_a[3] variable */)) * (DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8578]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.t_ia_a[1] variable */),((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8482]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e3_a[1] variable */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3959]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodLength PARAM */)),"chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e3_a[1] * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodLength",equationIndexes)));
  threadData->lastEquationSolved = 2565;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29846(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29845(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29844(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29839(DATA *data, threadData_t *threadData);


/*
equation index: 2570
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.f_b_a1[2] = chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e3_a[2] * (chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_a[2] * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.t_ia_a[2] + chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_a[3] * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.t_ia_a[3]) / chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodLength - chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_a[2] * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.t_ia_a[1] / (chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e3_a[1] * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodLength)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2570(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2570};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8492]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.f_b_a1[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8483]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e3_a[2] variable */)) * (DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8480]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_a[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8579]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.t_ia_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8481]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_a[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8580]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.t_ia_a[3] variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3959]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodLength PARAM */),"chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodLength",equationIndexes)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8480]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_a[2] variable */)) * (DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8578]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.t_ia_a[1] variable */),((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8482]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e3_a[1] variable */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3959]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodLength PARAM */)),"chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e3_a[1] * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodLength",equationIndexes)));
  threadData->lastEquationSolved = 2570;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29842(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29858(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29857(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29856(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29841(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29854(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_functionInitialEquations_4(DATA *data, threadData_t *threadData)
{
  static void (*const eqFunctions[494])(DATA*, threadData_t*) = {
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29097,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29096,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31410,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31411,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29095,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29094,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29092,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29318,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29319,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29327,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29357,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30264,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30271,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30279,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29486,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29493,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29501,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29365,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29366,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29368,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29367,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29364,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29363,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30280,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29362,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29361,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29502,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29360,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29359,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29358,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29369,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29370,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29371,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29372,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29373,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29374,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29375,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29376,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29377,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29378,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29379,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29380,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29105,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29106,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2075,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2076,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2077,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2078,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2079,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2080,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2081,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2082,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32731,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32733,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32732,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2086,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2087,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31781,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31783,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31782,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2091,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2092,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2093,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29432,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29440,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29441,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29443,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29442,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29439,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29438,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30807,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30808,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29437,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29436,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29868,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29869,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29435,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29434,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29433,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29457,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29460,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29107,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29108,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29109,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2115,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2116,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29110,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29111,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29112,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29113,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29114,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29115,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2123,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32172,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32189,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32188,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31394,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31401,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31412,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2130,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29118,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29120,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29132,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29134,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29133,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29128,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29125,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32190,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32192,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32191,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32193,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32195,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32197,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32194,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32198,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32256,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29126,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32250,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32246,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32248,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32247,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29127,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32255,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32251,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32253,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32252,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29124,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29123,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31413,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31415,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31414,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31416,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31417,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2164,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2165,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31421,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31479,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29122,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29121,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29119,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29320,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29321,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29328,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29381,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30265,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30272,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30281,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29487,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29494,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29503,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29389,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29390,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29392,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29391,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29388,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29387,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30282,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30285,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30284,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30283,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30287,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30289,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30286,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30290,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29386,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29385,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29504,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29507,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29506,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29505,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29508,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2202,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2203,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29512,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29384,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29383,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29382,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29393,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29394,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29395,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29396,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29397,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29411,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29724,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29720,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29723,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29722,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29721,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29412,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29729,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29725,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29728,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29727,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29726,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29413,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29414,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29415,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30663,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30659,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30662,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30661,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30660,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29416,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30668,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30664,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30667,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30666,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30665,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29417,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29418,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29135,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29136,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2243,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2244,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2245,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2246,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2247,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2248,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2249,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2250,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32728,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2252,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2253,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2254,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32739,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32741,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32738,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32742,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32740,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32730,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32729,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2262,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2263,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31778,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2265,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2266,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2267,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31788,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2269,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2270,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31792,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2272,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31780,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31779,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2275,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2276,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2277,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29420,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29428,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29429,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29431,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29430,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29427,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29426,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30805,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30812,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30811,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30810,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30814,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30816,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30813,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30817,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30815,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30806,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29425,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29424,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29866,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29873,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29872,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29871,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29874,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2302,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2303,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29878,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2305,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29867,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29423,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29422,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29421,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29456,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29459,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29129,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29044,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2314,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29046,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29140,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2317,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29142,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29047,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29144,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29235,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29233,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29234,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29145,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29146,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2326,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29246,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29247,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29248,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29398,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29399,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29400,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29401,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29402,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29403,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29404,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29405,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29406,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29407,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29408,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29410,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29409,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2343,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2344,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29249,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31473,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31469,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31472,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31471,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31470,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29250,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31478,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31474,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31477,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31476,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31475,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29251,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29252,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32249,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32254,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29253,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29254,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2363,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2364,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2365,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2366,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2367,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32720,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32824,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32823,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31871,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31876,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31884,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29465,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29470,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29475,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31115,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31120,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31128,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30125,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30130,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30138,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2383,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32721,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32829,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32828,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31872,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31877,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31888,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29466,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29471,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29476,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31116,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31121,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31132,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30126,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30131,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30142,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2399,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2400,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2401,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2402,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2403,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2404,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2405,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2406,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29513,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29514,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29515,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29879,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29880,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29881,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2413,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29517,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29516,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29518,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2417,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2418,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2419,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29543,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29539,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29536,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2423,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2424,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2425,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29532,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29531,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29530,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2429,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2430,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2431,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29526,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29544,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29545,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29556,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29525,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29540,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29541,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29542,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29524,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29537,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29715,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29718,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29719,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29716,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29717,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29730,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29731,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29732,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29733,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29734,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29735,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29736,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29737,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29740,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29739,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29738,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29741,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29744,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29743,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29742,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29751,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29753,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29752,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29756,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29748,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29750,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29749,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29755,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29745,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29747,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29746,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29754,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2526,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2527,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2528,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29815,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2530,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2531,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2532,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29822,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2534,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2535,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29826,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2537,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2538,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2539,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2540,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2541,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2542,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29820,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2544,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2545,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2546,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2547,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2548,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29828,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29829,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29830,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29831,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29832,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29833,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29835,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29834,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29836,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2558,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29837,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29838,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29855,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29851,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29847,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29843,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2565,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29846,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29845,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29844,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29839,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2570,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29842,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29858,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29857,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29856,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29841,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29854
  };
  
  for (int id = 0; id < 494; id++) {
    eqFunctions[id](data, threadData);
  }
}
#if defined(__cplusplus)
}
#endif