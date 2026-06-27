#include "BobLib.Experiments.Standards.VehicleSim_model.h"
#if defined(__cplusplus)
extern "C" {
#endif
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28613(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28612(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28610(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28609(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28608(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28606(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28605(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28604(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28883(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28884(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28885(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28603(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28602(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28601(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28600(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28599(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28598(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28597(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28596(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28595(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28594(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28593(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28592(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28591(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28590(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28589(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28588(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28587(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28586(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28585(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28584(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28583(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28582(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28581(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28580(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28973(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28974(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28995(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28997(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28999(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29007(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29009(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29011(DATA *data, threadData_t *threadData);


/*
equation index: 538
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi = $START.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_538(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,538};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */) = ((modelica_real *)((data->modelData->realVarsData[18] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 538;
}

/*
equation index: 539
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,2] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[3] * sin(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_539(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,539};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3605]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,2] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1020]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 539;
}

/*
equation index: 540
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,3] = (-chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[2]) * sin(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_540(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,540};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3606]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,3] DUMMY_STATE */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1019]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[2] PARAM */))) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 540;
}

/*
equation index: 541
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,1] = (-chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[3]) * sin(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_541(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,541};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3607]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,1] DUMMY_STATE */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1020]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[3] PARAM */))) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 541;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32179(DATA *data, threadData_t *threadData);


/*
equation index: 543
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,3] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[1] * sin(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_543(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,543};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3608]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,3] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1018]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 543;
}

/*
equation index: 544
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,1] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[2] * sin(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_544(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,544};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3609]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,1] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1019]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 544;
}

/*
equation index: 545
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,2] = (-chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[1]) * sin(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_545(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,545};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3610]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,2] DUMMY_STATE */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1018]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[1] PARAM */))) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 545;
}

/*
equation index: 546
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w = $START.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_546(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,546};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[19]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */) = ((modelica_real *)((data->modelData->realVarsData[19] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 546;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28900(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28899(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28898(DATA *data, threadData_t *threadData);


/*
equation index: 550
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,2] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[3] * cos(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_550(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,550};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1012]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,2]) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1020]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[19]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */)));
  threadData->lastEquationSolved = 550;
}

/*
equation index: 551
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,3] = (-chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[2]) * cos(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_551(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,551};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1013]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,3]) DUMMY_DER */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1019]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[2] PARAM */))) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[19]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */)));
  threadData->lastEquationSolved = 551;
}

/*
equation index: 552
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,1] = (-chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[3]) * cos(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_552(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,552};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1014]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,1]) DUMMY_DER */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1020]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[3] PARAM */))) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[19]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */)));
  threadData->lastEquationSolved = 552;
}

/*
equation index: 553
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,3] = (-sin(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_553(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,553};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1018]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,3]) DUMMY_DER */) = ((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[19]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */));
  threadData->lastEquationSolved = 553;
}

/*
equation index: 554
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,3] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[1] * cos(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_554(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,554};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1015]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,3]) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1018]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[19]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */)));
  threadData->lastEquationSolved = 554;
}

/*
equation index: 555
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,1] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[2] * cos(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_555(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,555};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1016]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,1]) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1019]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[19]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */)));
  threadData->lastEquationSolved = 555;
}

/*
equation index: 556
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,2] = (-chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[1]) * cos(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_556(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,556};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1017]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,2]) DUMMY_DER */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1018]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[1] PARAM */))) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[19]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */)));
  threadData->lastEquationSolved = 556;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28776(DATA *data, threadData_t *threadData);


/*
equation index: 558
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi = $START.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_558(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,558};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */) = ((modelica_real *)((data->modelData->realVarsData[24] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 558;
}

/*
equation index: 559
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w = $START.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_559(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,559};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[25]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */) = ((modelica_real *)((data->modelData->realVarsData[25] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 559;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28777(DATA *data, threadData_t *threadData);


/*
equation index: 561
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi = $START.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_561(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,561};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */) = ((modelica_real *)((data->modelData->realVarsData[30] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 561;
}

/*
equation index: 562
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,1] = 0.9999962541519682 + 3.745848031755372e-6 * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_562(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,562};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7354]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,1] DUMMY_STATE */) = 0.9999962541519682 + (3.745848031755372e-6) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 562;
}

/*
equation index: 563
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,2] = -2.7370911568422437e-4 + 2.7370911568422437e-4 * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi) + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[3] * sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_563(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,563};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7355]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,2] DUMMY_STATE */) = -2.7370911568422437e-4 + (2.7370911568422437e-4) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */))) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3269]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 563;
}

/*
equation index: 564
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,3] = -0.0019159638097888975 + 0.0019159638097888975 * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi) - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[2] * sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_564(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,564};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7356]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,3] DUMMY_STATE */) = -0.0019159638097888975 + (0.0019159638097888975) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3268]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */))));
  threadData->lastEquationSolved = 564;
}

/*
equation index: 565
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,1] = -2.7370911568422437e-4 + 2.7370911568422437e-4 * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi) - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[3] * sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_565(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,565};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7357]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,1] DUMMY_STATE */) = -2.7370911568422437e-4 + (2.7370911568422437e-4) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3269]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */))));
  threadData->lastEquationSolved = 565;
}

/*
equation index: 566
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,2] = 7.491696063618966e-8 + 0.9999999250830394 * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_566(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,566};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7358]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,2] DUMMY_STATE */) = 7.491696063618966e-8 + (0.9999999250830394) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 566;
}

/*
equation index: 567
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,3] = 5.244187244531434e-7 + (-5.244187244531434e-7) * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi) + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[1] * sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_567(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,567};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7359]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,3] DUMMY_STATE */) = 5.244187244531434e-7 + (-5.244187244531434e-7) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */))) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3267]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 567;
}

/*
equation index: 568
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,1] = -0.0019159638097888975 + 0.0019159638097888975 * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi) + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[2] * sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_568(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,568};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7360]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,1] DUMMY_STATE */) = -0.0019159638097888975 + (0.0019159638097888975) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */))) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3268]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 568;
}

/*
equation index: 569
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,2] = 5.244187244531434e-7 + (-5.244187244531434e-7) * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi) - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[1] * sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_569(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,569};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7361]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,2] DUMMY_STATE */) = 5.244187244531434e-7 + (-5.244187244531434e-7) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3267]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */))));
  threadData->lastEquationSolved = 569;
}

/*
equation index: 570
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,3] = 3.670931071170715e-6 + 0.9999963290689289 * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_570(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,570};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7362]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,3] DUMMY_STATE */) = 3.670931071170715e-6 + (0.9999963290689289) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 570;
}

/*
equation index: 571
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w = $START.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_571(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,571};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[31]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */) = ((modelica_real *)((data->modelData->realVarsData[31] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 571;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28894(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28893(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28892(DATA *data, threadData_t *threadData);


/*
equation index: 575
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,1] = 3.745848031755372e-6 * (-sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_575(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,575};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1576]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,1]) DUMMY_DER */) = (3.745848031755372e-6) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[31]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */)));
  threadData->lastEquationSolved = 575;
}

/*
equation index: 576
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,2] = 2.7370911568422437e-4 * (-sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[3] * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_576(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,576};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1577]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,2]) DUMMY_DER */) = (2.7370911568422437e-4) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[31]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */))) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3269]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[31]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */)));
  threadData->lastEquationSolved = 576;
}

/*
equation index: 577
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,3] = 0.0019159638097888975 * (-sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[2] * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_577(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,577};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1578]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,3]) DUMMY_DER */) = (0.0019159638097888975) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[31]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3268]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[31]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */))));
  threadData->lastEquationSolved = 577;
}

/*
equation index: 578
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,1] = 2.7370911568422437e-4 * (-sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[3] * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_578(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,578};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1579]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,1]) DUMMY_DER */) = (2.7370911568422437e-4) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[31]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3269]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[31]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */))));
  threadData->lastEquationSolved = 578;
}

/*
equation index: 579
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,2] = 0.9999999250830394 * (-sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_579(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,579};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1580]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,2]) DUMMY_DER */) = (0.9999999250830394) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[31]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */)));
  threadData->lastEquationSolved = 579;
}

/*
equation index: 580
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,3] = (-5.244187244531434e-7) * (-sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[1] * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_580(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,580};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1581]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,3]) DUMMY_DER */) = (-5.244187244531434e-7) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[31]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */))) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3267]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[31]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */)));
  threadData->lastEquationSolved = 580;
}

/*
equation index: 581
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,1] = 0.0019159638097888975 * (-sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[2] * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_581(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,581};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1582]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,1]) DUMMY_DER */) = (0.0019159638097888975) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[31]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */))) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3268]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[31]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */)));
  threadData->lastEquationSolved = 581;
}

/*
equation index: 582
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,2] = (-5.244187244531434e-7) * (-sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[1] * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_582(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,582};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1583]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,2]) DUMMY_DER */) = (-5.244187244531434e-7) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[31]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3267]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[31]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */))));
  threadData->lastEquationSolved = 582;
}

/*
equation index: 583
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,3] = 0.9999963290689289 * (-sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_583(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,583};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1584]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,3]) DUMMY_DER */) = (0.9999963290689289) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[31]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.a) */)));
  threadData->lastEquationSolved = 583;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28810(DATA *data, threadData_t *threadData);


/*
equation index: 585
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi = $START.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_585(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,585};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */) = ((modelica_real *)((data->modelData->realVarsData[36] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 585;
}

/*
equation index: 586
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w = $START.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_586(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,586};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[37]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */) = ((modelica_real *)((data->modelData->realVarsData[37] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 586;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28811(DATA *data, threadData_t *threadData);


/*
equation index: 588
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.torsionalRevolute.phi = $START.chassis.detailedChassis.spaceFrame.torsionalRevolute.phi
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_588(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,588};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */) = ((modelica_real *)((data->modelData->realVarsData[38] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 588;
}

/*
equation index: 589
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[1,1] = chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] ^ 2.0 + (1.0 - chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] ^ 2.0) * cos(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_589(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,589};
  modelica_real tmp0;
  modelica_real tmp1;
  tmp0 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4979]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] PARAM */);
  tmp1 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4979]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9947]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[1,1] DUMMY_STATE */) = (tmp0 * tmp0) + (1.0 - ((tmp1 * tmp1))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */)));
  threadData->lastEquationSolved = 589;
}

/*
equation index: 590
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[1,2] = (chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] - chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] * cos(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)) * chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] - chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] * sin(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_590(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,590};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9948]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[1,2] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4979]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4979]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4980]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4981]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */))));
  threadData->lastEquationSolved = 590;
}

/*
equation index: 591
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[1,3] = (chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] - chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] * cos(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)) * chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] + chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] * sin(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_591(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,591};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9949]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[1,3] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4979]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4979]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4981]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4980]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */)));
  threadData->lastEquationSolved = 591;
}

/*
equation index: 592
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[2,1] = (chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] - chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] * cos(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)) * chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] + chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] * sin(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_592(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,592};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9950]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[2,1] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4980]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4980]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4979]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4981]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */)));
  threadData->lastEquationSolved = 592;
}

/*
equation index: 593
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[2,2] = chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] ^ 2.0 + (1.0 - chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] ^ 2.0) * cos(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_593(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,593};
  modelica_real tmp2;
  modelica_real tmp3;
  tmp2 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4980]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] PARAM */);
  tmp3 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4980]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9951]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[2,2] DUMMY_STATE */) = (tmp2 * tmp2) + (1.0 - ((tmp3 * tmp3))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */)));
  threadData->lastEquationSolved = 593;
}

/*
equation index: 594
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[2,3] = (chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] - chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] * cos(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)) * chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] - chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] * sin(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_594(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,594};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9952]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[2,3] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4980]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4980]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4981]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4979]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */))));
  threadData->lastEquationSolved = 594;
}

/*
equation index: 595
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[3,1] = (chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] - chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] * cos(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)) * chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] - chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] * sin(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_595(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,595};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9953]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[3,1] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4981]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4981]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4979]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4980]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */))));
  threadData->lastEquationSolved = 595;
}

/*
equation index: 596
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[3,2] = (chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] - chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] * cos(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)) * chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] + chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] * sin(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_596(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,596};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9954]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[3,2] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4981]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4981]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4980]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4979]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */)));
  threadData->lastEquationSolved = 596;
}

/*
equation index: 597
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[3,3] = chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] ^ 2.0 + (1.0 - chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] ^ 2.0) * cos(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_597(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,597};
  modelica_real tmp4;
  modelica_real tmp5;
  tmp4 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4981]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] PARAM */);
  tmp5 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4981]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9955]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[3,3] DUMMY_STATE */) = (tmp4 * tmp4) + (1.0 - ((tmp5 * tmp5))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */)));
  threadData->lastEquationSolved = 597;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28987(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28837(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28838(DATA *data, threadData_t *threadData);


/*
equation index: 601
type: SIMPLE_ASSIGN
motor.motor.tau_act = $START.motor.motor.tau_act
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_601(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,601};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[43]] /* motor.motor.tau_act STATE(1) */) = ((modelica_real *)((data->modelData->realVarsData[43] /* motor.motor.tau_act STATE(1) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 601;
}

/*
equation index: 602
type: SIMPLE_ASSIGN
$PRE.rampEnding = $START.rampEnding
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_602(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,602};
  (data->simulationInfo->booleanVarsPre[45] /* rampEnding DISCRETE */) = (data->modelData->booleanVarsData[45] /* rampEnding DISCRETE */).attribute .start;
  threadData->lastEquationSolved = 602;
}

/*
equation index: 603
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] = -0.026047699999999997
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_603(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,603};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3883]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] variable */) = -0.026047699999999997;
  threadData->lastEquationSolved = 603;
}

/*
equation index: 604
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] = 0.3053207
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_604(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,604};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3884]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] variable */) = 0.3053207;
  threadData->lastEquationSolved = 604;
}

/*
equation index: 605
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] = 0.0532638
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_605(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,605};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3885]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] variable */) = 0.0532638;
  threadData->lastEquationSolved = 605;
}

/*
equation index: 606
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] = -0.16480789999999979
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_606(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,606};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7640]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] variable */) = -0.16480789999999979;
  threadData->lastEquationSolved = 606;
}

/*
equation index: 607
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] = 0.23623269999999996
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_607(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,607};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7641]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] variable */) = 0.23623269999999996;
  threadData->lastEquationSolved = 607;
}

/*
equation index: 608
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] = 0.04880610000000002
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_608(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,608};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7642]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] variable */) = 0.04880610000000002;
  threadData->lastEquationSolved = 608;
}

/*
equation index: 609
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.rackAxis.s = (chassis.detailedChassis.rearSteerLock.phi0 - chassis.detailedChassis.rrAxleDW.rackAndPinion.mounting1D.phi0) / chassis.detailedChassis.rrAxleDW.rackAndPinion.idealGearR2T.ratio + chassis.detailedChassis.rrAxleDW.rackAndPinion.rackAxis.fixed.s0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_609(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,609};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7850]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.rackAxis.s DUMMY_STATE */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2599]] /* chassis.detailedChassis.rearSteerLock.phi0 PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3662]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.mounting1D.phi0 PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3657]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.idealGearR2T.ratio PARAM */),"chassis.detailedChassis.rrAxleDW.rackAndPinion.idealGearR2T.ratio",equationIndexes) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3675]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.rackAxis.fixed.s0 PARAM */);
  threadData->lastEquationSolved = 609;
}

/*
equation index: 610
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.rackAxis.box.length = if noEvent(abs(chassis.detailedChassis.rrAxleDW.rackAndPinion.rackAxis.s) > 1e-6) then chassis.detailedChassis.rrAxleDW.rackAndPinion.rackAxis.s else 1e-6
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_610(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,610};
  modelica_boolean tmp6;
  tmp6 = Greater(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7850]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.rackAxis.s DUMMY_STATE */)),1e-6);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7837]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.rackAxis.box.length variable */) = (tmp6?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7850]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.rackAxis.s DUMMY_STATE */):1e-6);
  threadData->lastEquationSolved = 610;
}

/*
equation index: 611
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.fixedRadius.s = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.fixed.s0 - (-0.5) * chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.fixedRadius.L
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_611(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,611};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8681]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.fixedRadius.s variable */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4149]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.fixed.s0 PARAM */) - ((-0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4124]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.fixedRadius.L PARAM */)));
  threadData->lastEquationSolved = 611;
}

/*
equation index: 612
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.s = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.fixedRadius.s + 0.5 * chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.fixedRadius.L
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_612(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,612};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8739]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.s DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8681]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.fixedRadius.s variable */) + (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4124]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.fixedRadius.L PARAM */));
  threadData->lastEquationSolved = 612;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28579(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28670(DATA *data, threadData_t *threadData);


/*
equation index: 615
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.fixedRadius.s = chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.prismatic_z.fixed.s0 - (-0.5) * chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.fixedRadius.L
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_615(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,615};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6915]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.fixedRadius.s variable */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3060]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.prismatic_z.fixed.s0 PARAM */) - ((-0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3035]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.fixedRadius.L PARAM */)));
  threadData->lastEquationSolved = 615;
}

/*
equation index: 616
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.prismatic_z.s = chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.fixedRadius.s + 0.5 * chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.fixedRadius.L
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_616(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,616};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6973]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.prismatic_z.s DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6915]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.fixedRadius.s variable */) + (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3035]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.fixedRadius.L PARAM */));
  threadData->lastEquationSolved = 616;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28578(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28677(DATA *data, threadData_t *threadData);


/*
equation index: 619
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.fixedRadius.s = chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.fixed.s0 - (-0.5) * chassis.detailedChassis.frAxleDW.rightTire.wheelModel.fixedRadius.L
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_619(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,619};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4924]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.fixedRadius.s variable */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1900]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.fixed.s0 PARAM */) - ((-0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1875]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.fixedRadius.L PARAM */)));
  threadData->lastEquationSolved = 619;
}

/*
equation index: 620
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.s = chassis.detailedChassis.frAxleDW.rightTire.wheelModel.fixedRadius.s + 0.5 * chassis.detailedChassis.frAxleDW.rightTire.wheelModel.fixedRadius.L
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_620(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,620};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4982]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.s DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4924]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.fixedRadius.s variable */) + (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1875]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.fixedRadius.L PARAM */));
  threadData->lastEquationSolved = 620;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28577(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28733(DATA *data, threadData_t *threadData);


/*
equation index: 623
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.fixedRadius.s = chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.fixed.s0 - (-0.5) * chassis.detailedChassis.frAxleDW.leftTire.wheelModel.fixedRadius.L
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_623(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,623};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3161]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.fixedRadius.s variable */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[811]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.fixed.s0 PARAM */) - ((-0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[786]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.fixedRadius.L PARAM */)));
  threadData->lastEquationSolved = 623;
}

/*
equation index: 624
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.s = chassis.detailedChassis.frAxleDW.leftTire.wheelModel.fixedRadius.s + 0.5 * chassis.detailedChassis.frAxleDW.leftTire.wheelModel.fixedRadius.L
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_624(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,624};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3219]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.s DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3161]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.fixedRadius.s variable */) + (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[786]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.fixedRadius.L PARAM */));
  threadData->lastEquationSolved = 624;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28576(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28740(DATA *data, threadData_t *threadData);


/*
equation index: 627
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.slipModel.Fz0 = max(chassis.detailedChassis.frAxleDW.leftTire.slipModel.FNOMIN, 0.001)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_627(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,627};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3140]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.Fz0 variable */) = fmax((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[770]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.FNOMIN PARAM */),0.001);
  threadData->lastEquationSolved = 627;
}

/*
equation index: 628
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.slipModel.Fz0_scaled = max(chassis.detailedChassis.frAxleDW.leftTire.slipModel.FNOMIN * chassis.detailedChassis.frAxleDW.leftTire.slipModel.LFZO, 0.001)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_628(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,628};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3141]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.Fz0_scaled variable */) = fmax(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[770]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.FNOMIN PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[771]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.LFZO PARAM */)),0.001);
  threadData->lastEquationSolved = 628;
}

/*
equation index: 629
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.slipModel.Fz0 = max(chassis.detailedChassis.frAxleDW.rightTire.slipModel.FNOMIN, 0.001)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_629(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,629};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4903]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.Fz0 variable */) = fmax((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1859]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.FNOMIN PARAM */),0.001);
  threadData->lastEquationSolved = 629;
}

/*
equation index: 630
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.slipModel.Fz0_scaled = max(chassis.detailedChassis.frAxleDW.rightTire.slipModel.FNOMIN * chassis.detailedChassis.frAxleDW.rightTire.slipModel.LFZO, 0.001)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_630(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,630};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4904]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.Fz0_scaled variable */) = fmax(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1859]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.FNOMIN PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1860]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.LFZO PARAM */)),0.001);
  threadData->lastEquationSolved = 630;
}

/*
equation index: 631
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.slipModel.Fz0 = max(chassis.detailedChassis.rrAxleDW.leftTire.slipModel.FNOMIN, 0.001)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_631(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,631};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6894]] /* chassis.detailedChassis.rrAxleDW.leftTire.slipModel.Fz0 variable */) = fmax((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3019]] /* chassis.detailedChassis.rrAxleDW.leftTire.slipModel.FNOMIN PARAM */),0.001);
  threadData->lastEquationSolved = 631;
}

/*
equation index: 632
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.slipModel.Fz0_scaled = max(chassis.detailedChassis.rrAxleDW.leftTire.slipModel.FNOMIN * chassis.detailedChassis.rrAxleDW.leftTire.slipModel.LFZO, 0.001)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_632(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,632};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6895]] /* chassis.detailedChassis.rrAxleDW.leftTire.slipModel.Fz0_scaled variable */) = fmax(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3019]] /* chassis.detailedChassis.rrAxleDW.leftTire.slipModel.FNOMIN PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3020]] /* chassis.detailedChassis.rrAxleDW.leftTire.slipModel.LFZO PARAM */)),0.001);
  threadData->lastEquationSolved = 632;
}

/*
equation index: 633
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.slipModel.Fz0 = max(chassis.detailedChassis.rrAxleDW.rightTire.slipModel.FNOMIN, 0.001)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_633(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,633};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8660]] /* chassis.detailedChassis.rrAxleDW.rightTire.slipModel.Fz0 variable */) = fmax((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4108]] /* chassis.detailedChassis.rrAxleDW.rightTire.slipModel.FNOMIN PARAM */),0.001);
  threadData->lastEquationSolved = 633;
}

/*
equation index: 634
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.slipModel.Fz0_scaled = max(chassis.detailedChassis.rrAxleDW.rightTire.slipModel.FNOMIN * chassis.detailedChassis.rrAxleDW.rightTire.slipModel.LFZO, 0.001)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_634(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,634};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8661]] /* chassis.detailedChassis.rrAxleDW.rightTire.slipModel.Fz0_scaled variable */) = fmax(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4108]] /* chassis.detailedChassis.rrAxleDW.rightTire.slipModel.FNOMIN PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4109]] /* chassis.detailedChassis.rrAxleDW.rightTire.slipModel.LFZO PARAM */)),0.001);
  threadData->lastEquationSolved = 634;
}

/*
equation index: 635
type: SIMPLE_ASSIGN
battery.battery.V_pack_min = (*Real*)(battery.battery.Ns) * battery.battery.V_cell_min
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_635(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,635};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2255]] /* battery.battery.V_pack_min variable */) = (((modelica_real)(data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[8]] /* battery.battery.Ns PARAM */))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[244]] /* battery.battery.V_cell_min PARAM */));
  threadData->lastEquationSolved = 635;
}

/*
equation index: 636
type: SIMPLE_ASSIGN
battery.battery.V_pack_max = (*Real*)(battery.battery.Ns) * battery.battery.V_cell_max
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_636(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,636};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2254]] /* battery.battery.V_pack_max variable */) = (((modelica_real)(data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[8]] /* battery.battery.Ns PARAM */))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[243]] /* battery.battery.V_cell_max PARAM */));
  threadData->lastEquationSolved = 636;
}

/*
equation index: 637
type: SIMPLE_ASSIGN
vcu.rearAxleTorqueCapacity = vcu.tau_max * max(vcu.finalDriveRatio, 1e-6)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_637(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,637};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10308]] /* vcu.rearAxleTorqueCapacity variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6879]] /* vcu.tau_max PARAM */)) * (fmax((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6824]] /* vcu.finalDriveRatio PARAM */),1e-6));
  threadData->lastEquationSolved = 637;
}

/*
equation index: 638
type: SIMPLE_ASSIGN
vcu.rearAxleRegenTorqueCapacity = vcu.regenTorqueLimit * max(vcu.finalDriveRatio, 1e-6)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_638(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,638};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10307]] /* vcu.rearAxleRegenTorqueCapacity variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6833]] /* vcu.regenTorqueLimit PARAM */)) * (fmax((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6824]] /* vcu.finalDriveRatio PARAM */),1e-6));
  threadData->lastEquationSolved = 638;
}

/*
equation index: 639
type: SIMPLE_ASSIGN
inverter.inverter.P_standby_active = if inverter.inverter.enabled then inverter.inverter.P_standby else 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_639(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,639};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10217]] /* inverter.inverter.P_standby_active variable */) = ((data->simulationInfo->booleanParameter[data->simulationInfo->booleanParamsIndex[575]] /* inverter.inverter.enabled PARAM */)?(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5949]] /* inverter.inverter.P_standby PARAM */):0.0);
  threadData->lastEquationSolved = 639;
}

/*
equation index: 640
type: SIMPLE_ASSIGN
vcu.handwheelRampDirection = if noEvent(vcu.targetAy >= 0.0) then 1.0 else -1.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_640(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,640};
  modelica_boolean tmp7;
  tmp7 = GreaterEq((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6877]] /* vcu.targetAy PARAM */),0.0);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10303]] /* vcu.handwheelRampDirection variable */) = (tmp7?1.0:-1.0);
  threadData->lastEquationSolved = 640;
}

/*
equation index: 641
type: SIMPLE_ASSIGN
vcu.steadyStateAyRampDuration = abs(vcu.targetAy) / max(vcu.steadyStateAyRampRate, 1e-6)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_641(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,641};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10323]] /* vcu.steadyStateAyRampDuration variable */) = DIVISION_SIM(fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6877]] /* vcu.targetAy PARAM */)),fmax((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6869]] /* vcu.steadyStateAyRampRate PARAM */),1e-6),"max(vcu.steadyStateAyRampRate, 1e-6)",equationIndexes);
  threadData->lastEquationSolved = 641;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28849(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28851(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28852(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28850(DATA *data, threadData_t *threadData);


/*
equation index: 646
type: SIMPLE_ASSIGN
vcu.regenLimitCmd = if vcu.enablePTNRegenSpeedControl then vcu.regenTorqueLimit else 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_646(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,646};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10310]] /* vcu.regenLimitCmd variable */) = ((data->simulationInfo->booleanParameter[data->simulationInfo->booleanParamsIndex[611]] /* vcu.enablePTNRegenSpeedControl PARAM */)?(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6833]] /* vcu.regenTorqueLimit PARAM */):0.0);
  threadData->lastEquationSolved = 646;
}

/*
equation index: 647
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n[3] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.n_b[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_647(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,647};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1140]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1120]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.n_b[3] PARAM */);
  threadData->lastEquationSolved = 647;
}

/*
equation index: 648
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n[2] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.n_b[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_648(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,648};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1139]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1119]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.n_b[2] PARAM */);
  threadData->lastEquationSolved = 648;
}

/*
equation index: 649
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n[1] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.n_b[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_649(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,649};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1138]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1118]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.n_b[1] PARAM */);
  threadData->lastEquationSolved = 649;
}

/*
equation index: 650
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n / sqrt(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_650(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,650};
  real_array tmp8;
  real_array tmp9;
  real_array tmp10;
  modelica_real tmp11;
  real_array tmp12;
  real_array_create(&tmp8, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1138]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp9, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1138]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp10, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1138]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp11 = mul_real_scalar_product(tmp9, tmp10);
  if(!(tmp11 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n) was %g should be >= 0", tmp11);
    }
  }real_array_create(&tmp12, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1134]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(division_alloc_real_array_scalar(threadData,tmp8,sqrt(tmp11),"sqrt(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n)"), tmp12);
  threadData->lastEquationSolved = 650;
}

/*
equation index: 651
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[3] = (-chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3]) * 0.5 * (0.02 + Modelica.Math.Vectors.norm({0.1696974, 0.0021082000000000045, -8.128000000000024e-4}, 2.0))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_651(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,651};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3866]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[3] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1136]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */))) * ((0.5) * (0.02 + omc_Modelica_Math_Vectors_norm(threadData, _OMC_LIT30, 2.0)));
  threadData->lastEquationSolved = 651;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36406(DATA *data, threadData_t *threadData);


/*
equation index: 653
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[1] = (-chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1]) * 0.5 * (0.02 + Modelica.Math.Vectors.norm({0.1696974, 0.0021082000000000045, -8.128000000000024e-4}, 2.0))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_653(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,653};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3864]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[1] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1134]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */))) * ((0.5) * (0.02 + omc_Modelica_Math_Vectors_norm(threadData, _OMC_LIT30, 2.0)));
  threadData->lastEquationSolved = 653;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36404(DATA *data, threadData_t *threadData);


/*
equation index: 655
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_655(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,655};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3872]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1134]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3883]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1135]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3884]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1136]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3885]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] variable */));
  threadData->lastEquationSolved = 655;
}

/*
equation index: 656
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[2] = (-chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2]) * 0.5 * (0.02 + Modelica.Math.Vectors.norm({0.1696974, 0.0021082000000000045, -8.128000000000024e-4}, 2.0))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_656(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,656};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3865]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[2] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1135]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */))) * ((0.5) * (0.02 + omc_Modelica_Math_Vectors_norm(threadData, _OMC_LIT30, 2.0)));
  threadData->lastEquationSolved = 656;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36405(DATA *data, threadData_t *threadData);


/*
equation index: 658
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia = smooth(0, if noEvent(sqrt(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0) >= 2.220446049250313e-14) then {0.0, (-chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3]) / sqrt(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0), chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] / sqrt(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0)} else {0.0, (-4.503599627370496e13) * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3], 4.503599627370496e13 * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2]})
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_658(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,658};
  modelica_real tmp13;
  modelica_real tmp14;
  modelica_real tmp15;
  modelica_boolean tmp16;
  real_array tmp17;
  modelica_real tmp18;
  modelica_real tmp19;
  modelica_real tmp20;
  modelica_real tmp21;
  modelica_real tmp22;
  modelica_real tmp23;
  real_array tmp24;
  modelica_boolean tmp25;
  real_array tmp26;
  real_array tmp27;
  tmp13 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1154]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */);
  tmp14 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1155]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */);
  tmp15 = (tmp13 * tmp13) + (tmp14 * tmp14);
  if(!(tmp15 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0) was %g should be >= 0", tmp15);
    }
  }tmp16 = GreaterEq(sqrt(tmp15),2.220446049250313e-14);
  tmp25 = (modelica_boolean)tmp16;
  if(tmp25)
  {
    tmp18 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1154]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */);
    tmp19 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1155]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */);
    tmp20 = (tmp18 * tmp18) + (tmp19 * tmp19);
    if(!(tmp20 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0) was %g should be >= 0", tmp20);
      }
    }tmp21 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1154]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */);
    tmp22 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1155]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */);
    tmp23 = (tmp21 * tmp21) + (tmp22 * tmp22);
    if(!(tmp23 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0) was %g should be >= 0", tmp23);
      }
    }array_alloc_scalar_real_array(&tmp17, 3, (modelica_real)0.0, (modelica_real)DIVISION_SIM((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1155]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */)),sqrt(tmp20),"sqrt(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1154]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */),sqrt(tmp23),"sqrt(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0)",equationIndexes));
    tmp26 = tmp17;
  }
  else
  {
    array_alloc_scalar_real_array(&tmp24, 3, (modelica_real)0.0, (modelica_real)(-4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1155]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */)), (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1154]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */)));
    tmp26 = tmp24;
  }
  real_array_create(&tmp27, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1147]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(tmp26, tmp27);
  threadData->lastEquationSolved = 658;
}

/*
equation index: 659
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.e2_ia[2] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_659(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,659};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1110]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.e2_ia[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1148]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2] PARAM */);
  threadData->lastEquationSolved = 659;
}

/*
equation index: 660
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[2] = (-chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2]) * 0.5 * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_660(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,660};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3997]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[2] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1148]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1146]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 660;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29008(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36399(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36402(DATA *data, threadData_t *threadData);


/*
equation index: 664
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.e2_ia[3] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_664(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,664};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1111]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.e2_ia[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1149]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3] PARAM */);
  threadData->lastEquationSolved = 664;
}

/*
equation index: 665
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[3] = (-chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3]) * 0.5 * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_665(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,665};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3998]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[3] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1149]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1146]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 665;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29006(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36400(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36403(DATA *data, threadData_t *threadData);


/*
equation index: 669
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.e2_ia[1] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_669(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,669};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1109]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.e2_ia[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1147]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] PARAM */);
  threadData->lastEquationSolved = 669;
}

/*
equation index: 670
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[1] = (-chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1]) * 0.5 * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_670(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,670};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3996]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[1] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1147]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1146]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 670;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29010(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36398(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36401(DATA *data, threadData_t *threadData);


/*
equation index: 674
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_674(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,674};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1150]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1154]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1149]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1155]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1148]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2] PARAM */)));
  threadData->lastEquationSolved = 674;
}

/*
equation index: 675
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[1] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_675(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,675};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1151]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1155]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1147]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1153]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1149]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3] PARAM */)));
  threadData->lastEquationSolved = 675;
}

/*
equation index: 676
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[1] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_676(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,676};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1152]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1153]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1148]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1154]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1147]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] PARAM */)));
  threadData->lastEquationSolved = 676;
}

/*
equation index: 677
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3] = chassis.detailedChassis.frAxleDW.pRightDW.lower_o[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_677(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,677};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2138]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1364]] /* chassis.detailedChassis.frAxleDW.pRightDW.lower_o[3] PARAM */);
  threadData->lastEquationSolved = 677;
}

/*
equation index: 678
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2] = chassis.detailedChassis.frAxleDW.pRightDW.lower_o[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_678(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,678};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2137]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1363]] /* chassis.detailedChassis.frAxleDW.pRightDW.lower_o[2] PARAM */);
  threadData->lastEquationSolved = 678;
}

/*
equation index: 679
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1] = chassis.detailedChassis.frAxleDW.pRightDW.lower_o[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_679(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,679};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2136]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1362]] /* chassis.detailedChassis.frAxleDW.pRightDW.lower_o[1] PARAM */);
  threadData->lastEquationSolved = 679;
}

/*
equation index: 680
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] = chassis.detailedChassis.frAxleDW.pRightDW.upper_o[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_680(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,680};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2150]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1376]] /* chassis.detailedChassis.frAxleDW.pRightDW.upper_o[3] PARAM */);
  threadData->lastEquationSolved = 680;
}

/*
equation index: 681
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_681(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,681};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2217]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2150]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2138]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3] PARAM */);
  threadData->lastEquationSolved = 681;
}

/*
equation index: 682
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_682(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,682};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2250]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2217]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[3] PARAM */);
  threadData->lastEquationSolved = 682;
}

/*
equation index: 683
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] = chassis.detailedChassis.frAxleDW.pRightDW.upper_o[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_683(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,683};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2149]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1375]] /* chassis.detailedChassis.frAxleDW.pRightDW.upper_o[2] PARAM */);
  threadData->lastEquationSolved = 683;
}

/*
equation index: 684
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_684(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,684};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2216]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2149]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2137]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2] PARAM */);
  threadData->lastEquationSolved = 684;
}

/*
equation index: 685
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_685(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,685};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2249]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2216]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[2] PARAM */);
  threadData->lastEquationSolved = 685;
}

/*
equation index: 686
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] = chassis.detailedChassis.frAxleDW.pRightDW.upper_o[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_686(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,686};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2148]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1374]] /* chassis.detailedChassis.frAxleDW.pRightDW.upper_o[1] PARAM */);
  threadData->lastEquationSolved = 686;
}

/*
equation index: 687
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.n = smooth(0, if noEvent(sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) ^ 2.0) >= 2.220446049250313e-14) then {(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) / sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) ^ 2.0), (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) / sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) ^ 2.0), (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) / sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) ^ 2.0)} else {4.503599627370496e13 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]), 4.503599627370496e13 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]), 4.503599627370496e13 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3])})
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_687(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,687};
  modelica_real tmp28;
  modelica_real tmp29;
  modelica_real tmp30;
  modelica_real tmp31;
  modelica_boolean tmp32;
  real_array tmp33;
  modelica_real tmp34;
  modelica_real tmp35;
  modelica_real tmp36;
  modelica_real tmp37;
  modelica_real tmp38;
  modelica_real tmp39;
  modelica_real tmp40;
  modelica_real tmp41;
  modelica_real tmp42;
  modelica_real tmp43;
  modelica_real tmp44;
  modelica_real tmp45;
  real_array tmp46;
  modelica_boolean tmp47;
  real_array tmp48;
  real_array tmp49;
  tmp28 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2148]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2136]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1] PARAM */);
  tmp29 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2149]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2137]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2] PARAM */);
  tmp30 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2150]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2138]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3] PARAM */);
  tmp31 = (tmp28 * tmp28) + (tmp29 * tmp29) + (tmp30 * tmp30);
  if(!(tmp31 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) ^ 2.0) was %g should be >= 0", tmp31);
    }
  }tmp32 = GreaterEq(sqrt(tmp31),2.220446049250313e-14);
  tmp47 = (modelica_boolean)tmp32;
  if(tmp47)
  {
    tmp34 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2148]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2136]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1] PARAM */);
    tmp35 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2149]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2137]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2] PARAM */);
    tmp36 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2150]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2138]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3] PARAM */);
    tmp37 = (tmp34 * tmp34) + (tmp35 * tmp35) + (tmp36 * tmp36);
    if(!(tmp37 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) ^ 2.0) was %g should be >= 0", tmp37);
      }
    }tmp38 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2148]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2136]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1] PARAM */);
    tmp39 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2149]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2137]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2] PARAM */);
    tmp40 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2150]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2138]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3] PARAM */);
    tmp41 = (tmp38 * tmp38) + (tmp39 * tmp39) + (tmp40 * tmp40);
    if(!(tmp41 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) ^ 2.0) was %g should be >= 0", tmp41);
      }
    }tmp42 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2148]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2136]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1] PARAM */);
    tmp43 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2149]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2137]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2] PARAM */);
    tmp44 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2150]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2138]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3] PARAM */);
    tmp45 = (tmp42 * tmp42) + (tmp43 * tmp43) + (tmp44 * tmp44);
    if(!(tmp45 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) ^ 2.0) was %g should be >= 0", tmp45);
      }
    }array_alloc_scalar_real_array(&tmp33, 3, (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2148]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2136]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1] PARAM */),sqrt(tmp37),"sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2149]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2137]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2] PARAM */),sqrt(tmp41),"sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2150]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2138]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3] PARAM */),sqrt(tmp45),"sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) ^ 2.0)",equationIndexes));
    tmp48 = tmp33;
  }
  else
  {
    array_alloc_scalar_real_array(&tmp46, 3, (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2148]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2136]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1] PARAM */)), (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2149]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2137]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2] PARAM */)), (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2150]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2138]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3] PARAM */)));
    tmp48 = tmp46;
  }
  real_array_create(&tmp49, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2161]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.n[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(tmp48, tmp49);
  threadData->lastEquationSolved = 687;
}

/*
equation index: 688
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.e = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.n / sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.n * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.n)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_688(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,688};
  real_array tmp50;
  real_array tmp51;
  real_array tmp52;
  modelica_real tmp53;
  real_array tmp54;
  real_array_create(&tmp50, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2161]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp51, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2161]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp52, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2161]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp53 = mul_real_scalar_product(tmp51, tmp52);
  if(!(tmp53 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.n * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.n) was %g should be >= 0", tmp53);
    }
  }real_array_create(&tmp54, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2157]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.e[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(division_alloc_real_array_scalar(threadData,tmp50,sqrt(tmp53),"sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.n * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.n)"), tmp54);
  threadData->lastEquationSolved = 688;
}

/*
equation index: 689
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.cylinder.r_shape[3] = (-chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.e[3]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_689(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,689};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5438]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.cylinder.r_shape[3] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2159]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.e[3] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 689;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36382(DATA *data, threadData_t *threadData);


/*
equation index: 691
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.cylinder.r_shape[1] = (-chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.e[1]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_691(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,691};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5436]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.cylinder.r_shape[1] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2157]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.e[1] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 691;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36380(DATA *data, threadData_t *threadData);


/*
equation index: 693
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.cylinder.r_shape[2] = (-chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.e[2]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_693(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,693};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5437]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.cylinder.r_shape[2] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2158]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.e[2] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 693;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36381(DATA *data, threadData_t *threadData);


/*
equation index: 695
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_695(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,695};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2215]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2148]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2136]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1] PARAM */);
  threadData->lastEquationSolved = 695;
}

/*
equation index: 696
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_696(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,696};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2248]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2215]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[1] PARAM */);
  threadData->lastEquationSolved = 696;
}

/*
equation index: 697
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia / sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_697(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,697};
  real_array tmp55;
  real_array tmp56;
  real_array tmp57;
  modelica_real tmp58;
  real_array tmp59;
  real_array_create(&tmp55, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2248]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp56, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2248]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp57, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2248]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp58 = mul_real_scalar_product(tmp56, tmp57);
  if(!(tmp58 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia) was %g should be >= 0", tmp58);
    }
  }real_array_create(&tmp59, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2242]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(division_alloc_real_array_scalar(threadData,tmp55,sqrt(tmp58),"sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia)"), tmp59);
  threadData->lastEquationSolved = 697;
}

/*
equation index: 698
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia = smooth(0, if noEvent(sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0) >= 2.220446049250313e-14) then {0.0, (-chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3]) / sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0), chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] / sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0)} else {0.0, (-4.503599627370496e13) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3], 4.503599627370496e13 * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2]})
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_698(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,698};
  modelica_real tmp60;
  modelica_real tmp61;
  modelica_real tmp62;
  modelica_boolean tmp63;
  real_array tmp64;
  modelica_real tmp65;
  modelica_real tmp66;
  modelica_real tmp67;
  modelica_real tmp68;
  modelica_real tmp69;
  modelica_real tmp70;
  real_array tmp71;
  modelica_boolean tmp72;
  real_array tmp73;
  real_array tmp74;
  tmp60 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2243]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */);
  tmp61 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2244]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */);
  tmp62 = (tmp60 * tmp60) + (tmp61 * tmp61);
  if(!(tmp62 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0) was %g should be >= 0", tmp62);
    }
  }tmp63 = GreaterEq(sqrt(tmp62),2.220446049250313e-14);
  tmp72 = (modelica_boolean)tmp63;
  if(tmp72)
  {
    tmp65 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2243]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */);
    tmp66 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2244]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */);
    tmp67 = (tmp65 * tmp65) + (tmp66 * tmp66);
    if(!(tmp67 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0) was %g should be >= 0", tmp67);
      }
    }tmp68 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2243]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */);
    tmp69 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2244]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */);
    tmp70 = (tmp68 * tmp68) + (tmp69 * tmp69);
    if(!(tmp70 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0) was %g should be >= 0", tmp70);
      }
    }array_alloc_scalar_real_array(&tmp64, 3, (modelica_real)0.0, (modelica_real)DIVISION_SIM((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2244]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */)),sqrt(tmp67),"sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2243]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */),sqrt(tmp70),"sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0)",equationIndexes));
    tmp73 = tmp64;
  }
  else
  {
    array_alloc_scalar_real_array(&tmp71, 3, (modelica_real)0.0, (modelica_real)(-4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2244]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */)), (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2243]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */)));
    tmp73 = tmp71;
  }
  real_array_create(&tmp74, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2236]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(tmp73, tmp74);
  threadData->lastEquationSolved = 698;
}

/*
equation index: 699
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[1] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_699(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,699};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2240]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2244]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2236]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2242]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2238]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3] PARAM */)));
  threadData->lastEquationSolved = 699;
}

/*
equation index: 700
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[1] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_700(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,700};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2241]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2242]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2237]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2243]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2236]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] PARAM */)));
  threadData->lastEquationSolved = 700;
}

/*
equation index: 701
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_701(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,701};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2239]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2243]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2238]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2244]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2237]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2] PARAM */)));
  threadData->lastEquationSolved = 701;
}

/*
equation index: 702
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.e2_ia[2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_702(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,702};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2199]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.e2_ia[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2237]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2] PARAM */);
  threadData->lastEquationSolved = 702;
}

/*
equation index: 703
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[2] = (-chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2]) * 0.5 * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_703(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,703};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5748]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[2] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2237]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2235]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 703;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29002(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36387(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36390(DATA *data, threadData_t *threadData);


/*
equation index: 707
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.e2_ia[1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_707(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,707};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2198]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.e2_ia[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2236]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] PARAM */);
  threadData->lastEquationSolved = 707;
}

/*
equation index: 708
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[1] = (-chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1]) * 0.5 * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_708(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,708};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5747]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[1] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2236]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2235]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 708;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29004(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36386(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36389(DATA *data, threadData_t *threadData);


/*
equation index: 712
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.e2_ia[3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_712(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,712};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2200]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.e2_ia[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2238]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3] PARAM */);
  threadData->lastEquationSolved = 712;
}

/*
equation index: 713
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[3] = (-chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3]) * 0.5 * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_713(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,713};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5749]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[3] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2238]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2235]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 713;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29000(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36388(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36391(DATA *data, threadData_t *threadData);


/*
equation index: 717
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.eRod1_ia[2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_717(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,717};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2202]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.eRod1_ia[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2243]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */);
  threadData->lastEquationSolved = 717;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29003(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36393(DATA *data, threadData_t *threadData);


/*
equation index: 720
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.eRod1_ia[1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_720(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,720};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2201]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.eRod1_ia[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2242]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[1] PARAM */);
  threadData->lastEquationSolved = 720;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29005(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36392(DATA *data, threadData_t *threadData);


/*
equation index: 723
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.eRod1_ia[3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_723(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,723};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2203]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.eRod1_ia[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2244]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */);
  threadData->lastEquationSolved = 723;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29001(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36394(DATA *data, threadData_t *threadData);


/*
equation index: 726
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] = chassis.detailedChassis.frAxleDW.pRightDW.upperAft_i[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_726(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,726};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2144]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1370]] /* chassis.detailedChassis.frAxleDW.pRightDW.upperAft_i[3] PARAM */);
  threadData->lastEquationSolved = 726;
}

/*
equation index: 727
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] = chassis.detailedChassis.frAxleDW.pRightDW.upperFore_i[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_727(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,727};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2147]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1373]] /* chassis.detailedChassis.frAxleDW.pRightDW.upperFore_i[3] PARAM */);
  threadData->lastEquationSolved = 727;
}

/*
equation index: 728
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[3] = 0.5 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_728(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,728};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2172]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[3] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2144]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2147]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] PARAM */));
  threadData->lastEquationSolved = 728;
}

/*
equation index: 729
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.lengthDirection[3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_729(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,729};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2169]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2172]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[3] PARAM */);
  threadData->lastEquationSolved = 729;
}

/*
equation index: 730
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[3] = 0.5 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_730(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,730};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2188]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[3] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2147]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2144]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] PARAM */));
  threadData->lastEquationSolved = 730;
}

/*
equation index: 731
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.lengthDirection[3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_731(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,731};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2185]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2188]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[3] PARAM */);
  threadData->lastEquationSolved = 731;
}

/*
equation index: 732
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] + (-0.5) * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_732(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,732};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2220]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2150]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] PARAM */) + (-0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2147]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2144]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] PARAM */));
  threadData->lastEquationSolved = 732;
}

/*
equation index: 733
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.position_b[3].k = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_733(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,733};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2214]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.position_b[3].k PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2220]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[3] PARAM */);
  threadData->lastEquationSolved = 733;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28764(DATA *data, threadData_t *threadData);


/*
equation index: 735
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_735(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,735};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2266]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2220]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[3] PARAM */);
  threadData->lastEquationSolved = 735;
}

/*
equation index: 736
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.lengthDirection[3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_736(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,736};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2263]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2266]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[3] PARAM */);
  threadData->lastEquationSolved = 736;
}

/*
equation index: 737
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] = chassis.detailedChassis.frAxleDW.pRightDW.upperAft_i[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_737(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,737};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2143]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1369]] /* chassis.detailedChassis.frAxleDW.pRightDW.upperAft_i[2] PARAM */);
  threadData->lastEquationSolved = 737;
}

/*
equation index: 738
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] = chassis.detailedChassis.frAxleDW.pRightDW.upperFore_i[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_738(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,738};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2146]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1372]] /* chassis.detailedChassis.frAxleDW.pRightDW.upperFore_i[2] PARAM */);
  threadData->lastEquationSolved = 738;
}

/*
equation index: 739
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[2] = 0.5 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_739(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,739};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2171]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[2] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2143]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2146]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] PARAM */));
  threadData->lastEquationSolved = 739;
}

/*
equation index: 740
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.lengthDirection[2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_740(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,740};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2168]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2171]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[2] PARAM */);
  threadData->lastEquationSolved = 740;
}

/*
equation index: 741
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[2] = 0.5 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_741(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,741};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2187]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[2] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2146]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2143]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] PARAM */));
  threadData->lastEquationSolved = 741;
}

/*
equation index: 742
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.lengthDirection[2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_742(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,742};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2184]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2187]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[2] PARAM */);
  threadData->lastEquationSolved = 742;
}

/*
equation index: 743
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] + (-0.5) * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_743(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,743};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2219]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2149]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] PARAM */) + (-0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2146]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2143]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] PARAM */));
  threadData->lastEquationSolved = 743;
}

/*
equation index: 744
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.position_b[2].k = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_744(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,744};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2213]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.position_b[2].k PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2219]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[2] PARAM */);
  threadData->lastEquationSolved = 744;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28763(DATA *data, threadData_t *threadData);


/*
equation index: 746
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_746(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,746};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2265]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2219]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[2] PARAM */);
  threadData->lastEquationSolved = 746;
}

/*
equation index: 747
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.lengthDirection[2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_747(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,747};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2262]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2265]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[2] PARAM */);
  threadData->lastEquationSolved = 747;
}

/*
equation index: 748
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] = chassis.detailedChassis.frAxleDW.pRightDW.upperAft_i[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_748(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,748};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2142]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1368]] /* chassis.detailedChassis.frAxleDW.pRightDW.upperAft_i[1] PARAM */);
  threadData->lastEquationSolved = 748;
}

/*
equation index: 749
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] = chassis.detailedChassis.frAxleDW.pRightDW.upperFore_i[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_749(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,749};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2145]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1371]] /* chassis.detailedChassis.frAxleDW.pRightDW.upperFore_i[1] PARAM */);
  threadData->lastEquationSolved = 749;
}

/*
equation index: 750
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[1] = 0.5 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_750(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,750};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2170]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[1] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2142]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2145]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] PARAM */));
  threadData->lastEquationSolved = 750;
}

/*
equation index: 751
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.length = sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_751(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,751};
  modelica_real tmp75;
  modelica_real tmp76;
  modelica_real tmp77;
  modelica_real tmp78;
  tmp75 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2170]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[1] PARAM */);
  tmp76 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2171]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[2] PARAM */);
  tmp77 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2172]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[3] PARAM */);
  tmp78 = (tmp75 * tmp75) + (tmp76 * tmp76) + (tmp77 * tmp77);
  if(!(tmp78 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[3] ^ 2.0) was %g should be >= 0", tmp78);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2166]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.length PARAM */) = sqrt(tmp78);
  threadData->lastEquationSolved = 751;
}

/*
equation index: 752
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.width = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_752(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,752};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2176]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2166]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 752;
}

/*
equation index: 753
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.height = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_753(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,753};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2165]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2176]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.width PARAM */);
  threadData->lastEquationSolved = 753;
}

/*
equation index: 754
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.lengthDirection[1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_754(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,754};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2167]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2170]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[1] PARAM */);
  threadData->lastEquationSolved = 754;
}

/*
equation index: 755
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[1] = 0.5 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_755(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,755};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2186]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[1] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2145]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2142]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] PARAM */));
  threadData->lastEquationSolved = 755;
}

/*
equation index: 756
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.length = sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_756(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,756};
  modelica_real tmp79;
  modelica_real tmp80;
  modelica_real tmp81;
  modelica_real tmp82;
  tmp79 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2186]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[1] PARAM */);
  tmp80 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2187]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[2] PARAM */);
  tmp81 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2188]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[3] PARAM */);
  tmp82 = (tmp79 * tmp79) + (tmp80 * tmp80) + (tmp81 * tmp81);
  if(!(tmp82 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[3] ^ 2.0) was %g should be >= 0", tmp82);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2182]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.length PARAM */) = sqrt(tmp82);
  threadData->lastEquationSolved = 756;
}

/*
equation index: 757
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.width = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_757(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,757};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2192]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2182]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 757;
}

/*
equation index: 758
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.height = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_758(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,758};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2181]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2192]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.width PARAM */);
  threadData->lastEquationSolved = 758;
}

/*
equation index: 759
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.lengthDirection[1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_759(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,759};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2183]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2186]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[1] PARAM */);
  threadData->lastEquationSolved = 759;
}

/*
equation index: 760
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] + (-0.5) * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_760(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,760};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2218]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2148]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] PARAM */) + (-0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2145]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2142]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] PARAM */));
  threadData->lastEquationSolved = 760;
}

/*
equation index: 761
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.position_b[1].k = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_761(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,761};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2212]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.position_b[1].k PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2218]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[1] PARAM */);
  threadData->lastEquationSolved = 761;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28762(DATA *data, threadData_t *threadData);


/*
equation index: 763
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_763(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,763};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2264]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2218]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[1] PARAM */);
  threadData->lastEquationSolved = 763;
}

/*
equation index: 764
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.length = sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_764(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,764};
  modelica_real tmp83;
  modelica_real tmp84;
  modelica_real tmp85;
  modelica_real tmp86;
  tmp83 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2264]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[1] PARAM */);
  tmp84 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2265]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[2] PARAM */);
  tmp85 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2266]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[3] PARAM */);
  tmp86 = (tmp83 * tmp83) + (tmp84 * tmp84) + (tmp85 * tmp85);
  if(!(tmp86 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[3] ^ 2.0) was %g should be >= 0", tmp86);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2260]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.length PARAM */) = sqrt(tmp86);
  threadData->lastEquationSolved = 764;
}

/*
equation index: 765
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.lengthDirection[1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_765(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,765};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2261]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2264]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[1] PARAM */);
  threadData->lastEquationSolved = 765;
}

/*
equation index: 766
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revoluteLength = 0.02 + Modelica.Math.Vectors.norm({chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1], chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2], chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]}, 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_766(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,766};
  real_array tmp87;
  array_alloc_scalar_real_array(&tmp87, 3, (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2145]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2142]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2146]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2143]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2147]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2144]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] PARAM */));
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2233]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revoluteLength PARAM */) = 0.02 + omc_Modelica_Math_Vectors_norm(threadData, tmp87, 2.0);
  threadData->lastEquationSolved = 766;
}

/*
equation index: 767
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinderLength = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revoluteLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_767(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,767};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2222]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinderLength PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2233]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revoluteLength PARAM */);
  threadData->lastEquationSolved = 767;
}

/*
equation index: 768
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.n_b = smooth(0, if noEvent(sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) ^ 2.0) >= 2.220446049250313e-14) then {(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) / sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) ^ 2.0), (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) / sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) ^ 2.0), (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) / sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) ^ 2.0)} else {4.503599627370496e13 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]), 4.503599627370496e13 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]), 4.503599627370496e13 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3])})
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_768(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,768};
  modelica_real tmp88;
  modelica_real tmp89;
  modelica_real tmp90;
  modelica_real tmp91;
  modelica_boolean tmp92;
  real_array tmp93;
  modelica_real tmp94;
  modelica_real tmp95;
  modelica_real tmp96;
  modelica_real tmp97;
  modelica_real tmp98;
  modelica_real tmp99;
  modelica_real tmp100;
  modelica_real tmp101;
  modelica_real tmp102;
  modelica_real tmp103;
  modelica_real tmp104;
  modelica_real tmp105;
  real_array tmp106;
  modelica_boolean tmp107;
  real_array tmp108;
  real_array tmp109;
  tmp88 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2145]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2142]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] PARAM */);
  tmp89 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2146]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2143]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] PARAM */);
  tmp90 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2147]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2144]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] PARAM */);
  tmp91 = (tmp88 * tmp88) + (tmp89 * tmp89) + (tmp90 * tmp90);
  if(!(tmp91 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) ^ 2.0) was %g should be >= 0", tmp91);
    }
  }tmp92 = GreaterEq(sqrt(tmp91),2.220446049250313e-14);
  tmp107 = (modelica_boolean)tmp92;
  if(tmp107)
  {
    tmp94 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2145]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2142]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] PARAM */);
    tmp95 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2146]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2143]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] PARAM */);
    tmp96 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2147]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2144]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] PARAM */);
    tmp97 = (tmp94 * tmp94) + (tmp95 * tmp95) + (tmp96 * tmp96);
    if(!(tmp97 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) ^ 2.0) was %g should be >= 0", tmp97);
      }
    }tmp98 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2145]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2142]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] PARAM */);
    tmp99 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2146]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2143]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] PARAM */);
    tmp100 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2147]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2144]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] PARAM */);
    tmp101 = (tmp98 * tmp98) + (tmp99 * tmp99) + (tmp100 * tmp100);
    if(!(tmp101 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) ^ 2.0) was %g should be >= 0", tmp101);
      }
    }tmp102 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2145]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2142]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] PARAM */);
    tmp103 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2146]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2143]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] PARAM */);
    tmp104 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2147]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2144]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] PARAM */);
    tmp105 = (tmp102 * tmp102) + (tmp103 * tmp103) + (tmp104 * tmp104);
    if(!(tmp105 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) ^ 2.0) was %g should be >= 0", tmp105);
      }
    }array_alloc_scalar_real_array(&tmp93, 3, (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2145]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2142]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] PARAM */),sqrt(tmp97),"sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2146]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2143]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] PARAM */),sqrt(tmp101),"sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2147]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2144]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] PARAM */),sqrt(tmp105),"sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) ^ 2.0)",equationIndexes));
    tmp108 = tmp93;
  }
  else
  {
    array_alloc_scalar_real_array(&tmp106, 3, (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2145]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2142]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] PARAM */)), (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2146]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2143]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] PARAM */)), (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2147]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2144]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] PARAM */)));
    tmp108 = tmp106;
  }
  real_array_create(&tmp109, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2207]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.n_b[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(tmp108, tmp109);
  threadData->lastEquationSolved = 768;
}

/*
equation index: 769
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n[1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.n_b[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_769(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,769};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2227]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2207]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.n_b[1] PARAM */);
  threadData->lastEquationSolved = 769;
}

/*
equation index: 770
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n[3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.n_b[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_770(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,770};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2229]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2209]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.n_b[3] PARAM */);
  threadData->lastEquationSolved = 770;
}

/*
equation index: 771
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n[2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.n_b[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_771(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,771};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2228]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2208]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.n_b[2] PARAM */);
  threadData->lastEquationSolved = 771;
}

/*
equation index: 772
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n / sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_772(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,772};
  real_array tmp110;
  real_array tmp111;
  real_array tmp112;
  modelica_real tmp113;
  real_array tmp114;
  real_array_create(&tmp110, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2227]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp111, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2227]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp112, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2227]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp113 = mul_real_scalar_product(tmp111, tmp112);
  if(!(tmp113 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n) was %g should be >= 0", tmp113);
    }
  }real_array_create(&tmp114, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(division_alloc_real_array_scalar(threadData,tmp110,sqrt(tmp113),"sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n)"), tmp114);
  threadData->lastEquationSolved = 772;
}

/*
equation index: 773
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[3] = (-chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3]) * 0.5 * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_773(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,773};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5617]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[3] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2222]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 773;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36397(DATA *data, threadData_t *threadData);


/*
equation index: 775
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[1] = (-chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1]) * 0.5 * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_775(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,775};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5615]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[1] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2222]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 775;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36395(DATA *data, threadData_t *threadData);


/*
equation index: 777
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[2] = (-chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2]) * 0.5 * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_777(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,777};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5616]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[2] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2222]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 777;
}

/*
equation index: 778
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_778(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,778};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5623]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5634]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5635]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5636]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] DUMMY_STATE */));
  threadData->lastEquationSolved = 778;
}

/*
equation index: 779
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_779(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,779};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1319]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1329]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1]) DUMMY_DER */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1330]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2]) DUMMY_DER */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1331]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3]) DUMMY_DER */));
  threadData->lastEquationSolved = 779;
}

/*
equation index: 780
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * $DER.$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * $DER.$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * $DER.$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_780(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,780};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[368]] /* der(der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b)) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[378]] /* der(der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1])) DUMMY_DER */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[379]] /* der(der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2])) DUMMY_DER */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[380]] /* der(der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3])) DUMMY_DER */));
  threadData->lastEquationSolved = 780;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36396(DATA *data, threadData_t *threadData);


/*
equation index: 782
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] = chassis.detailedChassis.frAxleDW.pRightDW.lowerAft_i[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_782(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,782};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2132]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1358]] /* chassis.detailedChassis.frAxleDW.pRightDW.lowerAft_i[3] PARAM */);
  threadData->lastEquationSolved = 782;
}

/*
equation index: 783
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] = chassis.detailedChassis.frAxleDW.pRightDW.lowerFore_i[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_783(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,783};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2135]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1361]] /* chassis.detailedChassis.frAxleDW.pRightDW.lowerFore_i[3] PARAM */);
  threadData->lastEquationSolved = 783;
}

/*
equation index: 784
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[3] = 0.5 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_784(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,784};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2080]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[3] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2132]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2135]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] PARAM */));
  threadData->lastEquationSolved = 784;
}

/*
equation index: 785
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.lengthDirection[3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_785(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,785};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2077]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2080]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[3] PARAM */);
  threadData->lastEquationSolved = 785;
}

/*
equation index: 786
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[3] = 0.5 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_786(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,786};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2096]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[3] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2135]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2132]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] PARAM */));
  threadData->lastEquationSolved = 786;
}

/*
equation index: 787
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.lengthDirection[3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_787(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,787};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2093]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2096]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[3] PARAM */);
  threadData->lastEquationSolved = 787;
}

/*
equation index: 788
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.r[3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3] + (-0.5) * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_788(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,788};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2122]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.r[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2138]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[3] PARAM */) + (-0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2135]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2132]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] PARAM */));
  threadData->lastEquationSolved = 788;
}

/*
equation index: 789
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.lengthDirection[3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_789(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,789};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2119]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2122]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.r[3] PARAM */);
  threadData->lastEquationSolved = 789;
}

/*
equation index: 790
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] = chassis.detailedChassis.frAxleDW.pRightDW.lowerAft_i[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_790(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,790};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2131]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1357]] /* chassis.detailedChassis.frAxleDW.pRightDW.lowerAft_i[2] PARAM */);
  threadData->lastEquationSolved = 790;
}

/*
equation index: 791
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] = chassis.detailedChassis.frAxleDW.pRightDW.lowerFore_i[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_791(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,791};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2134]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1360]] /* chassis.detailedChassis.frAxleDW.pRightDW.lowerFore_i[2] PARAM */);
  threadData->lastEquationSolved = 791;
}

/*
equation index: 792
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[2] = 0.5 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_792(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,792};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2079]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[2] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2131]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2134]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] PARAM */));
  threadData->lastEquationSolved = 792;
}

/*
equation index: 793
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.lengthDirection[2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_793(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,793};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2076]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2079]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[2] PARAM */);
  threadData->lastEquationSolved = 793;
}

/*
equation index: 794
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[2] = 0.5 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_794(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,794};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2095]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[2] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2134]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2131]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] PARAM */));
  threadData->lastEquationSolved = 794;
}

/*
equation index: 795
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.lengthDirection[2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_795(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,795};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2092]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2095]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[2] PARAM */);
  threadData->lastEquationSolved = 795;
}

/*
equation index: 796
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.r[2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2] + (-0.5) * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_796(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,796};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2121]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.r[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2137]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[2] PARAM */) + (-0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2134]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2131]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] PARAM */));
  threadData->lastEquationSolved = 796;
}

/*
equation index: 797
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.lengthDirection[2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_797(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,797};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2118]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2121]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.r[2] PARAM */);
  threadData->lastEquationSolved = 797;
}

/*
equation index: 798
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] = chassis.detailedChassis.frAxleDW.pRightDW.lowerAft_i[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_798(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,798};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2130]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1356]] /* chassis.detailedChassis.frAxleDW.pRightDW.lowerAft_i[1] PARAM */);
  threadData->lastEquationSolved = 798;
}

/*
equation index: 799
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] = chassis.detailedChassis.frAxleDW.pRightDW.lowerFore_i[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_799(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,799};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2133]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1359]] /* chassis.detailedChassis.frAxleDW.pRightDW.lowerFore_i[1] PARAM */);
  threadData->lastEquationSolved = 799;
}

/*
equation index: 800
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[1] = 0.5 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_800(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,800};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2078]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[1] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2130]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2133]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] PARAM */));
  threadData->lastEquationSolved = 800;
}

/*
equation index: 801
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.length = sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_801(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,801};
  modelica_real tmp115;
  modelica_real tmp116;
  modelica_real tmp117;
  modelica_real tmp118;
  tmp115 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2078]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[1] PARAM */);
  tmp116 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2079]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[2] PARAM */);
  tmp117 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2080]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[3] PARAM */);
  tmp118 = (tmp115 * tmp115) + (tmp116 * tmp116) + (tmp117 * tmp117);
  if(!(tmp118 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[3] ^ 2.0) was %g should be >= 0", tmp118);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2074]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.length PARAM */) = sqrt(tmp118);
  threadData->lastEquationSolved = 801;
}

/*
equation index: 802
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.width = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_802(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,802};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2084]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2074]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 802;
}

/*
equation index: 803
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.height = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_803(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,803};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2073]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2084]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.width PARAM */);
  threadData->lastEquationSolved = 803;
}

/*
equation index: 804
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.lengthDirection[1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_804(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,804};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2075]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2078]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[1] PARAM */);
  threadData->lastEquationSolved = 804;
}

/*
equation index: 805
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[1] = 0.5 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_805(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,805};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2094]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[1] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2133]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2130]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] PARAM */));
  threadData->lastEquationSolved = 805;
}

/*
equation index: 806
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.length = sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_806(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,806};
  modelica_real tmp119;
  modelica_real tmp120;
  modelica_real tmp121;
  modelica_real tmp122;
  tmp119 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2094]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[1] PARAM */);
  tmp120 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2095]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[2] PARAM */);
  tmp121 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2096]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[3] PARAM */);
  tmp122 = (tmp119 * tmp119) + (tmp120 * tmp120) + (tmp121 * tmp121);
  if(!(tmp122 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[3] ^ 2.0) was %g should be >= 0", tmp122);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2090]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.length PARAM */) = sqrt(tmp122);
  threadData->lastEquationSolved = 806;
}

/*
equation index: 807
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.width = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_807(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,807};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2100]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2090]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 807;
}

/*
equation index: 808
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.height = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_808(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,808};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2089]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2100]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.width PARAM */);
  threadData->lastEquationSolved = 808;
}

/*
equation index: 809
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.lengthDirection[1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_809(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,809};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2091]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2094]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[1] PARAM */);
  threadData->lastEquationSolved = 809;
}

/*
equation index: 810
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.r[1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1] + (-0.5) * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_810(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,810};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2120]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.r[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2136]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lower_o[1] PARAM */) + (-0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2133]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2130]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] PARAM */));
  threadData->lastEquationSolved = 810;
}

/*
equation index: 811
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.length = sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_811(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,811};
  modelica_real tmp123;
  modelica_real tmp124;
  modelica_real tmp125;
  modelica_real tmp126;
  tmp123 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2120]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.r[1] PARAM */);
  tmp124 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2121]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.r[2] PARAM */);
  tmp125 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2122]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.r[3] PARAM */);
  tmp126 = (tmp123 * tmp123) + (tmp124 * tmp124) + (tmp125 * tmp125);
  if(!(tmp126 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.r[3] ^ 2.0) was %g should be >= 0", tmp126);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2116]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.length PARAM */) = sqrt(tmp126);
  threadData->lastEquationSolved = 811;
}

/*
equation index: 812
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.lengthDirection[1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_812(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,812};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2117]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2120]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerLink.r[1] PARAM */);
  threadData->lastEquationSolved = 812;
}

/*
equation index: 813
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.n = smooth(0, if noEvent(sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) ^ 2.0) >= 2.220446049250313e-14) then {(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) / sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) ^ 2.0), (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) / sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) ^ 2.0), (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) / sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) ^ 2.0)} else {4.503599627370496e13 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]), 4.503599627370496e13 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]), 4.503599627370496e13 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3])})
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_813(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,813};
  modelica_real tmp127;
  modelica_real tmp128;
  modelica_real tmp129;
  modelica_real tmp130;
  modelica_boolean tmp131;
  real_array tmp132;
  modelica_real tmp133;
  modelica_real tmp134;
  modelica_real tmp135;
  modelica_real tmp136;
  modelica_real tmp137;
  modelica_real tmp138;
  modelica_real tmp139;
  modelica_real tmp140;
  modelica_real tmp141;
  modelica_real tmp142;
  modelica_real tmp143;
  modelica_real tmp144;
  real_array tmp145;
  modelica_boolean tmp146;
  real_array tmp147;
  real_array tmp148;
  tmp127 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2133]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2130]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] PARAM */);
  tmp128 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2134]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2131]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] PARAM */);
  tmp129 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2135]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2132]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] PARAM */);
  tmp130 = (tmp127 * tmp127) + (tmp128 * tmp128) + (tmp129 * tmp129);
  if(!(tmp130 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) ^ 2.0) was %g should be >= 0", tmp130);
    }
  }tmp131 = GreaterEq(sqrt(tmp130),2.220446049250313e-14);
  tmp146 = (modelica_boolean)tmp131;
  if(tmp146)
  {
    tmp133 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2133]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2130]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] PARAM */);
    tmp134 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2134]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2131]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] PARAM */);
    tmp135 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2135]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2132]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] PARAM */);
    tmp136 = (tmp133 * tmp133) + (tmp134 * tmp134) + (tmp135 * tmp135);
    if(!(tmp136 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) ^ 2.0) was %g should be >= 0", tmp136);
      }
    }tmp137 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2133]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2130]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] PARAM */);
    tmp138 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2134]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2131]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] PARAM */);
    tmp139 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2135]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2132]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] PARAM */);
    tmp140 = (tmp137 * tmp137) + (tmp138 * tmp138) + (tmp139 * tmp139);
    if(!(tmp140 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) ^ 2.0) was %g should be >= 0", tmp140);
      }
    }tmp141 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2133]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2130]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] PARAM */);
    tmp142 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2134]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2131]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] PARAM */);
    tmp143 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2135]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2132]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] PARAM */);
    tmp144 = (tmp141 * tmp141) + (tmp142 * tmp142) + (tmp143 * tmp143);
    if(!(tmp144 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) ^ 2.0) was %g should be >= 0", tmp144);
      }
    }array_alloc_scalar_real_array(&tmp132, 3, (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2133]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2130]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] PARAM */),sqrt(tmp136),"sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2134]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2131]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] PARAM */),sqrt(tmp140),"sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2135]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2132]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] PARAM */),sqrt(tmp144),"sqrt((chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) ^ 2.0)",equationIndexes));
    tmp147 = tmp132;
  }
  else
  {
    array_alloc_scalar_real_array(&tmp145, 3, (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2133]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2130]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] PARAM */)), (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2134]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2131]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] PARAM */)), (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2135]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2132]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] PARAM */)));
    tmp147 = tmp145;
  }
  real_array_create(&tmp148, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2111]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.n[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(tmp147, tmp148);
  threadData->lastEquationSolved = 813;
}

/*
equation index: 814
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.n / sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.n * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.n)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_814(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,814};
  real_array tmp149;
  real_array tmp150;
  real_array tmp151;
  modelica_real tmp152;
  real_array tmp153;
  real_array_create(&tmp149, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2111]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp150, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2111]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp151, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2111]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp152 = mul_real_scalar_product(tmp150, tmp151);
  if(!(tmp152 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.n * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.n) was %g should be >= 0", tmp152);
    }
  }real_array_create(&tmp153, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2107]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(division_alloc_real_array_scalar(threadData,tmp149,sqrt(tmp152),"sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.n * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.n)"), tmp153);
  threadData->lastEquationSolved = 814;
}

/*
equation index: 815
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] ^ 2.0 + (1.0 - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] ^ 2.0) * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_815(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,815};
  modelica_real tmp154;
  modelica_real tmp155;
  tmp154 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2108]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */);
  tmp155 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2108]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5363]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,2] DUMMY_STATE */) = (tmp154 * tmp154) + (1.0 - ((tmp155 * tmp155))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 815;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28896(DATA *data, threadData_t *threadData);


/*
equation index: 817
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,2] = (1.0 - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] ^ 2.0) * (-sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_817(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,817};
  modelica_real tmp156;
  tmp156 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2108]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1262]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,2]) DUMMY_DER */) = (1.0 - ((tmp156 * tmp156))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[25]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */)));
  threadData->lastEquationSolved = 817;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36384(DATA *data, threadData_t *threadData);


/*
equation index: 819
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] ^ 2.0 + (1.0 - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] ^ 2.0) * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_819(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,819};
  modelica_real tmp157;
  modelica_real tmp158;
  tmp157 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2107]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */);
  tmp158 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2107]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5359]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,1] DUMMY_STATE */) = (tmp157 * tmp157) + (1.0 - ((tmp158 * tmp158))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 819;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28897(DATA *data, threadData_t *threadData);


/*
equation index: 821
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,1] = (1.0 - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] ^ 2.0) * (-sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_821(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,821};
  modelica_real tmp159;
  tmp159 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2107]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1258]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,1]) DUMMY_DER */) = (1.0 - ((tmp159 * tmp159))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[25]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */)));
  threadData->lastEquationSolved = 821;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36383(DATA *data, threadData_t *threadData);


/*
equation index: 823
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,2] = (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] * sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_823(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,823};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5360]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,2] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2107]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2107]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2108]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2109]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 823;
}

/*
equation index: 824
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,3] = (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] * sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_824(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,824};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5361]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,3] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2107]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2107]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2109]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2108]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))));
  threadData->lastEquationSolved = 824;
}

/*
equation index: 825
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,1] = (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] * sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_825(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,825};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5362]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,1] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2108]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2108]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2107]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2109]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))));
  threadData->lastEquationSolved = 825;
}

/*
equation index: 826
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,3] = (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] * sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_826(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,826};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5364]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,3] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2108]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2108]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2109]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2107]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 826;
}

/*
equation index: 827
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,1] = (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] * sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_827(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,827};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5365]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,1] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2109]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2109]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2107]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2108]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 827;
}

/*
equation index: 828
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,2] = (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] * sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_828(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,828};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5366]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,2] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2109]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2109]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2108]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2107]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))));
  threadData->lastEquationSolved = 828;
}

/*
equation index: 829
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] ^ 2.0 + (1.0 - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] ^ 2.0) * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_829(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,829};
  modelica_real tmp160;
  modelica_real tmp161;
  tmp160 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2109]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */);
  tmp161 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2109]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5367]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,3] DUMMY_STATE */) = (tmp160 * tmp160) + (1.0 - ((tmp161 * tmp161))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 829;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28895(DATA *data, threadData_t *threadData);


/*
equation index: 831
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] * (-sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_831(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,831};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1259]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,2]) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2109]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[25]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2107]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[25]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2108]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)))));
  threadData->lastEquationSolved = 831;
}

/*
equation index: 832
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,3] = (-chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1]) * (-sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_832(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,832};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1260]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,3]) DUMMY_DER */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2107]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[25]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2109]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2108]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[25]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */))));
  threadData->lastEquationSolved = 832;
}

/*
equation index: 833
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,1] = (-chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2]) * (-sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_833(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,833};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1261]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,1]) DUMMY_DER */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2108]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[25]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2107]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2109]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[25]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */))));
  threadData->lastEquationSolved = 833;
}

/*
equation index: 834
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] * (-sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_834(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,834};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1263]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,3]) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2107]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[25]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2108]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[25]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2109]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)))));
  threadData->lastEquationSolved = 834;
}

/*
equation index: 835
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] * (-sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_835(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,835};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1264]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,1]) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2108]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[25]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2109]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[25]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2107]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)))));
  threadData->lastEquationSolved = 835;
}

/*
equation index: 836
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,2] = (-chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3]) * (-sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_836(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,836};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1265]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,2]) DUMMY_DER */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2109]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[25]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2108]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2107]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[25]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */))));
  threadData->lastEquationSolved = 836;
}

/*
equation index: 837
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,3] = (1.0 - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] ^ 2.0) * (-sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_837(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,837};
  modelica_real tmp162;
  tmp162 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2109]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1266]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,3]) DUMMY_DER */) = (1.0 - ((tmp162 * tmp162))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[25]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */)));
  threadData->lastEquationSolved = 837;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36385(DATA *data, threadData_t *threadData);


/*
equation index: 839
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinderLength = 0.02 + Modelica.Math.Vectors.norm({chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1], chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2], chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]}, 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_839(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,839};
  real_array tmp163;
  array_alloc_scalar_real_array(&tmp163, 3, (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2133]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2130]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2134]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2131]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2135]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2132]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] PARAM */));
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2106]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinderLength PARAM */) = 0.02 + omc_Modelica_Math_Vectors_norm(threadData, tmp163, 2.0);
  threadData->lastEquationSolved = 839;
}

/*
equation index: 840
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.r_shape[3] = (-chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3]) * 0.5 * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_840(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,840};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5386]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.r_shape[3] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2109]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2106]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 840;
}

/*
equation index: 841
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.r_shape[2] = (-chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2]) * 0.5 * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_841(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,841};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5385]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.r_shape[2] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2108]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2106]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 841;
}

/*
equation index: 842
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.r_shape[1] = (-chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1]) * 0.5 * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_842(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,842};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5384]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.r_shape[1] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2107]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2106]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 842;
}

/*
equation index: 843
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_ia = smooth(0, if noEvent(sqrt(chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[2] ^ 2.0) >= 2.220446049250313e-14) then {0.0, (-chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[3]) / sqrt(chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[2] ^ 2.0), chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[2] / sqrt(chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[2] ^ 2.0)} else {0.0, (-4.503599627370496e13) * chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[3], 4.503599627370496e13 * chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[2]})
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_843(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,843};
  modelica_real tmp164;
  modelica_real tmp165;
  modelica_real tmp166;
  modelica_boolean tmp167;
  real_array tmp168;
  modelica_real tmp169;
  modelica_real tmp170;
  modelica_real tmp171;
  modelica_real tmp172;
  modelica_real tmp173;
  modelica_real tmp174;
  real_array tmp175;
  modelica_boolean tmp176;
  real_array tmp177;
  real_array tmp178;
  tmp164 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[612]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[3] PARAM */);
  tmp165 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[611]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[2] PARAM */);
  tmp166 = (tmp164 * tmp164) + (tmp165 * tmp165);
  if(!(tmp166 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[2] ^ 2.0) was %g should be >= 0", tmp166);
    }
  }tmp167 = GreaterEq(sqrt(tmp166),2.220446049250313e-14);
  tmp176 = (modelica_boolean)tmp167;
  if(tmp176)
  {
    tmp169 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[612]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[3] PARAM */);
    tmp170 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[611]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[2] PARAM */);
    tmp171 = (tmp169 * tmp169) + (tmp170 * tmp170);
    if(!(tmp171 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[2] ^ 2.0) was %g should be >= 0", tmp171);
      }
    }tmp172 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[612]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[3] PARAM */);
    tmp173 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[611]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[2] PARAM */);
    tmp174 = (tmp172 * tmp172) + (tmp173 * tmp173);
    if(!(tmp174 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[2] ^ 2.0) was %g should be >= 0", tmp174);
      }
    }array_alloc_scalar_real_array(&tmp168, 3, (modelica_real)0.0, (modelica_real)DIVISION_SIM((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[612]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[3] PARAM */)),sqrt(tmp171),"sqrt(chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[2] ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[611]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[2] PARAM */),sqrt(tmp174),"sqrt(chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[2] ^ 2.0)",equationIndexes));
    tmp177 = tmp168;
  }
  else
  {
    array_alloc_scalar_real_array(&tmp175, 3, (modelica_real)0.0, (modelica_real)(-4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[612]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[3] PARAM */)), (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[611]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[2] PARAM */)));
    tmp177 = tmp175;
  }
  real_array_create(&tmp178, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[604]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_ia[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(tmp177, tmp178);
  threadData->lastEquationSolved = 843;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28783(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36379(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28779(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36377(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28781(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36378(DATA *data, threadData_t *threadData);


/*
equation index: 850
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTieRod.rod.e3_ia[1] = chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[2] * chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_ia[3] - chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[3] * chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_850(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,850};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[607]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.e3_ia[1] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[611]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[606]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[612]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[605]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_ia[2] PARAM */)));
  threadData->lastEquationSolved = 850;
}

/*
equation index: 851
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTieRod.rod.e3_ia[2] = chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[3] * chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_ia[1] - chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[1] * chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_851(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,851};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[608]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.e3_ia[2] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[612]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[604]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[610]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[606]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_ia[3] PARAM */)));
  threadData->lastEquationSolved = 851;
}

/*
equation index: 852
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTieRod.rod.e3_ia[3] = chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[1] * chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_ia[2] - chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[2] * chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_852(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,852};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[609]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.e3_ia[3] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[610]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[605]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[611]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[604]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_ia[1] PARAM */)));
  threadData->lastEquationSolved = 852;
}

/*
equation index: 853
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieRod.r_b[3] = chassis.detailedChassis.frAxleDW.pRightDW.tie_o[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_853(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,853};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1690]] /* chassis.detailedChassis.frAxleDW.rightTieRod.r_b[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1367]] /* chassis.detailedChassis.frAxleDW.pRightDW.tie_o[3] PARAM */);
  threadData->lastEquationSolved = 853;
}

/*
equation index: 854
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia[3] = chassis.detailedChassis.frAxleDW.rightTieRod.r_b[3] - chassis.detailedChassis.frAxleDW.rightTieRod.r_a[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_854(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,854};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1707]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1690]] /* chassis.detailedChassis.frAxleDW.rightTieRod.r_b[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1687]] /* chassis.detailedChassis.frAxleDW.rightTieRod.r_a[3] PARAM */);
  threadData->lastEquationSolved = 854;
}

/*
equation index: 855
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieRod.r_b[2] = chassis.detailedChassis.frAxleDW.pRightDW.tie_o[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_855(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,855};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1689]] /* chassis.detailedChassis.frAxleDW.rightTieRod.r_b[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1366]] /* chassis.detailedChassis.frAxleDW.pRightDW.tie_o[2] PARAM */);
  threadData->lastEquationSolved = 855;
}

/*
equation index: 856
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia[2] = chassis.detailedChassis.frAxleDW.rightTieRod.r_b[2] - chassis.detailedChassis.frAxleDW.rightTieRod.r_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_856(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,856};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1706]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1689]] /* chassis.detailedChassis.frAxleDW.rightTieRod.r_b[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1686]] /* chassis.detailedChassis.frAxleDW.rightTieRod.r_a[2] PARAM */);
  threadData->lastEquationSolved = 856;
}

/*
equation index: 857
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieRod.r_b[1] = chassis.detailedChassis.frAxleDW.pRightDW.tie_o[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_857(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,857};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1688]] /* chassis.detailedChassis.frAxleDW.rightTieRod.r_b[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1365]] /* chassis.detailedChassis.frAxleDW.pRightDW.tie_o[1] PARAM */);
  threadData->lastEquationSolved = 857;
}

/*
equation index: 858
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia[1] = chassis.detailedChassis.frAxleDW.rightTieRod.r_b[1] - chassis.detailedChassis.frAxleDW.rightTieRod.r_a[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_858(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,858};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1705]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1688]] /* chassis.detailedChassis.frAxleDW.rightTieRod.r_b[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1685]] /* chassis.detailedChassis.frAxleDW.rightTieRod.r_a[1] PARAM */);
  threadData->lastEquationSolved = 858;
}

/*
equation index: 859
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia = chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia / sqrt(chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia * chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_859(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,859};
  real_array tmp179;
  real_array tmp180;
  real_array tmp181;
  modelica_real tmp182;
  real_array tmp183;
  real_array_create(&tmp179, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1705]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp180, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1705]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp181, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1705]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp182 = mul_real_scalar_product(tmp180, tmp181);
  if(!(tmp182 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia * chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia) was %g should be >= 0", tmp182);
    }
  }real_array_create(&tmp183, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1699]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(division_alloc_real_array_scalar(threadData,tmp179,sqrt(tmp182),"sqrt(chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia * chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia)"), tmp183);
  threadData->lastEquationSolved = 859;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28788(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36376(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28786(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36375(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28784(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36374(DATA *data, threadData_t *threadData);


/*
equation index: 866
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_ia = smooth(0, if noEvent(sqrt(chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[2] ^ 2.0) >= 2.220446049250313e-14) then {0.0, (-chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[3]) / sqrt(chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[2] ^ 2.0), chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[2] / sqrt(chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[2] ^ 2.0)} else {0.0, (-4.503599627370496e13) * chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[3], 4.503599627370496e13 * chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[2]})
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_866(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,866};
  modelica_real tmp184;
  modelica_real tmp185;
  modelica_real tmp186;
  modelica_boolean tmp187;
  real_array tmp188;
  modelica_real tmp189;
  modelica_real tmp190;
  modelica_real tmp191;
  modelica_real tmp192;
  modelica_real tmp193;
  modelica_real tmp194;
  real_array tmp195;
  modelica_boolean tmp196;
  real_array tmp197;
  real_array tmp198;
  tmp184 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1701]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[3] PARAM */);
  tmp185 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1700]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[2] PARAM */);
  tmp186 = (tmp184 * tmp184) + (tmp185 * tmp185);
  if(!(tmp186 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[2] ^ 2.0) was %g should be >= 0", tmp186);
    }
  }tmp187 = GreaterEq(sqrt(tmp186),2.220446049250313e-14);
  tmp196 = (modelica_boolean)tmp187;
  if(tmp196)
  {
    tmp189 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1701]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[3] PARAM */);
    tmp190 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1700]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[2] PARAM */);
    tmp191 = (tmp189 * tmp189) + (tmp190 * tmp190);
    if(!(tmp191 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[2] ^ 2.0) was %g should be >= 0", tmp191);
      }
    }tmp192 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1701]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[3] PARAM */);
    tmp193 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1700]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[2] PARAM */);
    tmp194 = (tmp192 * tmp192) + (tmp193 * tmp193);
    if(!(tmp194 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[2] ^ 2.0) was %g should be >= 0", tmp194);
      }
    }array_alloc_scalar_real_array(&tmp188, 3, (modelica_real)0.0, (modelica_real)DIVISION_SIM((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1701]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[3] PARAM */)),sqrt(tmp191),"sqrt(chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[2] ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1700]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[2] PARAM */),sqrt(tmp194),"sqrt(chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[2] ^ 2.0)",equationIndexes));
    tmp197 = tmp188;
  }
  else
  {
    array_alloc_scalar_real_array(&tmp195, 3, (modelica_real)0.0, (modelica_real)(-4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1701]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[3] PARAM */)), (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1700]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[2] PARAM */)));
    tmp197 = tmp195;
  }
  real_array_create(&tmp198, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1693]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_ia[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(tmp197, tmp198);
  threadData->lastEquationSolved = 866;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28785(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36371(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28789(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36373(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28787(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36372(DATA *data, threadData_t *threadData);


/*
equation index: 873
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieRod.rod.e3_ia[1] = chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[2] * chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_ia[3] - chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[3] * chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_873(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,873};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1696]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.e3_ia[1] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1700]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1695]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1701]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1694]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_ia[2] PARAM */)));
  threadData->lastEquationSolved = 873;
}

/*
equation index: 874
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieRod.rod.e3_ia[2] = chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[3] * chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_ia[1] - chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[1] * chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_874(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,874};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1697]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.e3_ia[2] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1701]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1693]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1699]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1695]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_ia[3] PARAM */)));
  threadData->lastEquationSolved = 874;
}

/*
equation index: 875
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieRod.rod.e3_ia[3] = chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[1] * chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_ia[2] - chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[2] * chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_875(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,875};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1698]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.e3_ia[3] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1699]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1694]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1700]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1693]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_ia[1] PARAM */)));
  threadData->lastEquationSolved = 875;
}

/*
equation index: 876
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieConnection.r[3] = chassis.detailedChassis.frAxleDW.pRightDW.lower_o[3] - chassis.detailedChassis.frAxleDW.pRightDW.tie_o[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_876(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,876};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1672]] /* chassis.detailedChassis.frAxleDW.rightTieConnection.r[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1364]] /* chassis.detailedChassis.frAxleDW.pRightDW.lower_o[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1367]] /* chassis.detailedChassis.frAxleDW.pRightDW.tie_o[3] PARAM */);
  threadData->lastEquationSolved = 876;
}

/*
equation index: 877
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieConnection.lengthDirection[3] = chassis.detailedChassis.frAxleDW.rightTieConnection.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_877(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,877};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1669]] /* chassis.detailedChassis.frAxleDW.rightTieConnection.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1672]] /* chassis.detailedChassis.frAxleDW.rightTieConnection.r[3] PARAM */);
  threadData->lastEquationSolved = 877;
}

/*
equation index: 878
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieConnection.r[2] = chassis.detailedChassis.frAxleDW.pRightDW.lower_o[2] - chassis.detailedChassis.frAxleDW.pRightDW.tie_o[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_878(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,878};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1671]] /* chassis.detailedChassis.frAxleDW.rightTieConnection.r[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1363]] /* chassis.detailedChassis.frAxleDW.pRightDW.lower_o[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1366]] /* chassis.detailedChassis.frAxleDW.pRightDW.tie_o[2] PARAM */);
  threadData->lastEquationSolved = 878;
}

/*
equation index: 879
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieConnection.lengthDirection[2] = chassis.detailedChassis.frAxleDW.rightTieConnection.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_879(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,879};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1668]] /* chassis.detailedChassis.frAxleDW.rightTieConnection.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1671]] /* chassis.detailedChassis.frAxleDW.rightTieConnection.r[2] PARAM */);
  threadData->lastEquationSolved = 879;
}

/*
equation index: 880
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieConnection.r[1] = chassis.detailedChassis.frAxleDW.pRightDW.lower_o[1] - chassis.detailedChassis.frAxleDW.pRightDW.tie_o[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_880(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,880};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1670]] /* chassis.detailedChassis.frAxleDW.rightTieConnection.r[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1362]] /* chassis.detailedChassis.frAxleDW.pRightDW.lower_o[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1365]] /* chassis.detailedChassis.frAxleDW.pRightDW.tie_o[1] PARAM */);
  threadData->lastEquationSolved = 880;
}

/*
equation index: 881
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieConnection.length = sqrt(chassis.detailedChassis.frAxleDW.rightTieConnection.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightTieConnection.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightTieConnection.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_881(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,881};
  modelica_real tmp199;
  modelica_real tmp200;
  modelica_real tmp201;
  modelica_real tmp202;
  tmp199 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1670]] /* chassis.detailedChassis.frAxleDW.rightTieConnection.r[1] PARAM */);
  tmp200 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1671]] /* chassis.detailedChassis.frAxleDW.rightTieConnection.r[2] PARAM */);
  tmp201 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1672]] /* chassis.detailedChassis.frAxleDW.rightTieConnection.r[3] PARAM */);
  tmp202 = (tmp199 * tmp199) + (tmp200 * tmp200) + (tmp201 * tmp201);
  if(!(tmp202 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightTieConnection.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightTieConnection.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightTieConnection.r[3] ^ 2.0) was %g should be >= 0", tmp202);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1666]] /* chassis.detailedChassis.frAxleDW.rightTieConnection.length PARAM */) = sqrt(tmp202);
  threadData->lastEquationSolved = 881;
}

/*
equation index: 882
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieConnection.width = chassis.detailedChassis.frAxleDW.rightTieConnection.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_882(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,882};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1676]] /* chassis.detailedChassis.frAxleDW.rightTieConnection.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1666]] /* chassis.detailedChassis.frAxleDW.rightTieConnection.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 882;
}

/*
equation index: 883
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieConnection.height = chassis.detailedChassis.frAxleDW.rightTieConnection.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_883(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,883};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1665]] /* chassis.detailedChassis.frAxleDW.rightTieConnection.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1676]] /* chassis.detailedChassis.frAxleDW.rightTieConnection.width PARAM */);
  threadData->lastEquationSolved = 883;
}

/*
equation index: 884
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieConnection.lengthDirection[1] = chassis.detailedChassis.frAxleDW.rightTieConnection.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_884(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,884};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1667]] /* chassis.detailedChassis.frAxleDW.rightTieConnection.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1670]] /* chassis.detailedChassis.frAxleDW.rightTieConnection.r[1] PARAM */);
  threadData->lastEquationSolved = 884;
}

/*
equation index: 885
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3] = chassis.detailedChassis.frAxleDW.pRightDW.wheelCenter[3] - chassis.detailedChassis.frAxleDW.pRightDW.lower_o[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_885(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,885};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2570]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1379]] /* chassis.detailedChassis.frAxleDW.pRightDW.wheelCenter[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1364]] /* chassis.detailedChassis.frAxleDW.pRightDW.lower_o[3] PARAM */);
  threadData->lastEquationSolved = 885;
}

/*
equation index: 886
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightWheelCenter.lengthDirection[3] = chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_886(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,886};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2567]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2570]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3] PARAM */);
  threadData->lastEquationSolved = 886;
}

/*
equation index: 887
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2] = chassis.detailedChassis.frAxleDW.pRightDW.wheelCenter[2] - chassis.detailedChassis.frAxleDW.pRightDW.lower_o[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_887(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,887};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2569]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1378]] /* chassis.detailedChassis.frAxleDW.pRightDW.wheelCenter[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1363]] /* chassis.detailedChassis.frAxleDW.pRightDW.lower_o[2] PARAM */);
  threadData->lastEquationSolved = 887;
}

/*
equation index: 888
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightWheelCenter.lengthDirection[2] = chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_888(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,888};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2566]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2569]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2] PARAM */);
  threadData->lastEquationSolved = 888;
}

/*
equation index: 889
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1] = chassis.detailedChassis.frAxleDW.pRightDW.wheelCenter[1] - chassis.detailedChassis.frAxleDW.pRightDW.lower_o[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_889(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,889};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2568]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1377]] /* chassis.detailedChassis.frAxleDW.pRightDW.wheelCenter[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1362]] /* chassis.detailedChassis.frAxleDW.pRightDW.lower_o[1] PARAM */);
  threadData->lastEquationSolved = 889;
}

/*
equation index: 890
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightWheelCenter.length = sqrt(chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_890(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,890};
  modelica_real tmp203;
  modelica_real tmp204;
  modelica_real tmp205;
  modelica_real tmp206;
  tmp203 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2568]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1] PARAM */);
  tmp204 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2569]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2] PARAM */);
  tmp205 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2570]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3] PARAM */);
  tmp206 = (tmp203 * tmp203) + (tmp204 * tmp204) + (tmp205 * tmp205);
  if(!(tmp206 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3] ^ 2.0) was %g should be >= 0", tmp206);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2564]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.length PARAM */) = sqrt(tmp206);
  threadData->lastEquationSolved = 890;
}

/*
equation index: 891
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightWheelCenter.width = chassis.detailedChassis.frAxleDW.toRightWheelCenter.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_891(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,891};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2574]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2564]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 891;
}

/*
equation index: 892
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightWheelCenter.height = chassis.detailedChassis.frAxleDW.toRightWheelCenter.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_892(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,892};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2563]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2574]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.width PARAM */);
  threadData->lastEquationSolved = 892;
}

/*
equation index: 893
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightWheelCenter.lengthDirection[1] = chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_893(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,893};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2565]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2568]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1] PARAM */);
  threadData->lastEquationSolved = 893;
}

/*
equation index: 894
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightUpper_i.r[3] = -0.199898 + 0.5 * (chassis.detailedChassis.frAxleDW.pRightDW.upperFore_i[3] + chassis.detailedChassis.frAxleDW.pRightDW.upperAft_i[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_894(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,894};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2554]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[3] PARAM */) = -0.199898 + (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1373]] /* chassis.detailedChassis.frAxleDW.pRightDW.upperFore_i[3] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1370]] /* chassis.detailedChassis.frAxleDW.pRightDW.upperAft_i[3] PARAM */));
  threadData->lastEquationSolved = 894;
}

/*
equation index: 895
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightUpper_i.lengthDirection[3] = chassis.detailedChassis.frAxleDW.toRightUpper_i.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_895(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,895};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2551]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2554]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[3] PARAM */);
  threadData->lastEquationSolved = 895;
}

/*
equation index: 896
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightUpper_i.r[2] = 0.5 * (chassis.detailedChassis.frAxleDW.pRightDW.upperFore_i[2] + chassis.detailedChassis.frAxleDW.pRightDW.upperAft_i[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_896(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,896};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2553]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[2] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1372]] /* chassis.detailedChassis.frAxleDW.pRightDW.upperFore_i[2] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1369]] /* chassis.detailedChassis.frAxleDW.pRightDW.upperAft_i[2] PARAM */));
  threadData->lastEquationSolved = 896;
}

/*
equation index: 897
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightUpper_i.lengthDirection[2] = chassis.detailedChassis.frAxleDW.toRightUpper_i.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_897(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,897};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2550]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2553]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[2] PARAM */);
  threadData->lastEquationSolved = 897;
}

/*
equation index: 898
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightUpper_i.r[1] = 0.5 * (chassis.detailedChassis.frAxleDW.pRightDW.upperFore_i[1] + chassis.detailedChassis.frAxleDW.pRightDW.upperAft_i[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_898(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,898};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2552]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[1] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1371]] /* chassis.detailedChassis.frAxleDW.pRightDW.upperFore_i[1] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1368]] /* chassis.detailedChassis.frAxleDW.pRightDW.upperAft_i[1] PARAM */));
  threadData->lastEquationSolved = 898;
}

/*
equation index: 899
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightUpper_i.length = sqrt(chassis.detailedChassis.frAxleDW.toRightUpper_i.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.toRightUpper_i.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.toRightUpper_i.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_899(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,899};
  modelica_real tmp207;
  modelica_real tmp208;
  modelica_real tmp209;
  modelica_real tmp210;
  tmp207 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2552]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[1] PARAM */);
  tmp208 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2553]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[2] PARAM */);
  tmp209 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2554]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[3] PARAM */);
  tmp210 = (tmp207 * tmp207) + (tmp208 * tmp208) + (tmp209 * tmp209);
  if(!(tmp210 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.toRightUpper_i.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.toRightUpper_i.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.toRightUpper_i.r[3] ^ 2.0) was %g should be >= 0", tmp210);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2548]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.length PARAM */) = sqrt(tmp210);
  threadData->lastEquationSolved = 899;
}

/*
equation index: 900
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightUpper_i.width = chassis.detailedChassis.frAxleDW.toRightUpper_i.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_900(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,900};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2558]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2548]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 900;
}

/*
equation index: 901
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightUpper_i.height = chassis.detailedChassis.frAxleDW.toRightUpper_i.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_901(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,901};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2547]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2558]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.width PARAM */);
  threadData->lastEquationSolved = 901;
}

/*
equation index: 902
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightUpper_i.lengthDirection[1] = chassis.detailedChassis.frAxleDW.toRightUpper_i.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_902(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,902};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2549]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2552]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[1] PARAM */);
  threadData->lastEquationSolved = 902;
}

/*
equation index: 903
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightLower_i.r[3] = -0.199898 + 0.5 * (chassis.detailedChassis.frAxleDW.pRightDW.lowerFore_i[3] + chassis.detailedChassis.frAxleDW.pRightDW.lowerAft_i[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_903(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,903};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2522]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[3] PARAM */) = -0.199898 + (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1361]] /* chassis.detailedChassis.frAxleDW.pRightDW.lowerFore_i[3] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1358]] /* chassis.detailedChassis.frAxleDW.pRightDW.lowerAft_i[3] PARAM */));
  threadData->lastEquationSolved = 903;
}

/*
equation index: 904
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightLower_i.lengthDirection[3] = chassis.detailedChassis.frAxleDW.toRightLower_i.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_904(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,904};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2519]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2522]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[3] PARAM */);
  threadData->lastEquationSolved = 904;
}

/*
equation index: 905
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightLower_i.r[2] = 0.5 * (chassis.detailedChassis.frAxleDW.pRightDW.lowerFore_i[2] + chassis.detailedChassis.frAxleDW.pRightDW.lowerAft_i[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_905(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,905};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2521]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[2] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1360]] /* chassis.detailedChassis.frAxleDW.pRightDW.lowerFore_i[2] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1357]] /* chassis.detailedChassis.frAxleDW.pRightDW.lowerAft_i[2] PARAM */));
  threadData->lastEquationSolved = 905;
}

/*
equation index: 906
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightLower_i.lengthDirection[2] = chassis.detailedChassis.frAxleDW.toRightLower_i.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_906(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,906};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2518]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2521]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[2] PARAM */);
  threadData->lastEquationSolved = 906;
}

/*
equation index: 907
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightLower_i.r[1] = 0.5 * (chassis.detailedChassis.frAxleDW.pRightDW.lowerFore_i[1] + chassis.detailedChassis.frAxleDW.pRightDW.lowerAft_i[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_907(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,907};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2520]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[1] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1359]] /* chassis.detailedChassis.frAxleDW.pRightDW.lowerFore_i[1] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1356]] /* chassis.detailedChassis.frAxleDW.pRightDW.lowerAft_i[1] PARAM */));
  threadData->lastEquationSolved = 907;
}

/*
equation index: 908
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightLower_i.length = sqrt(chassis.detailedChassis.frAxleDW.toRightLower_i.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.toRightLower_i.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.toRightLower_i.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_908(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,908};
  modelica_real tmp211;
  modelica_real tmp212;
  modelica_real tmp213;
  modelica_real tmp214;
  tmp211 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2520]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[1] PARAM */);
  tmp212 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2521]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[2] PARAM */);
  tmp213 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2522]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[3] PARAM */);
  tmp214 = (tmp211 * tmp211) + (tmp212 * tmp212) + (tmp213 * tmp213);
  if(!(tmp214 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.toRightLower_i.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.toRightLower_i.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.toRightLower_i.r[3] ^ 2.0) was %g should be >= 0", tmp214);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2516]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.length PARAM */) = sqrt(tmp214);
  threadData->lastEquationSolved = 908;
}

/*
equation index: 909
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightLower_i.width = chassis.detailedChassis.frAxleDW.toRightLower_i.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_909(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,909};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2526]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2516]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 909;
}

/*
equation index: 910
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightLower_i.height = chassis.detailedChassis.frAxleDW.toRightLower_i.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_910(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,910};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2515]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2526]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.width PARAM */);
  threadData->lastEquationSolved = 910;
}

/*
equation index: 911
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightLower_i.lengthDirection[1] = chassis.detailedChassis.frAxleDW.toRightLower_i.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_911(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,911};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2517]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2520]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[1] PARAM */);
  threadData->lastEquationSolved = 911;
}

/*
equation index: 912
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.r_CM[1] = chassis.detailedChassis.frAxleDW.pRightAxleMass.ucaMass.rCM[1] - chassis.detailedChassis.frAxleDW.pRightDW.upper_o[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_912(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,912};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2011]] /* chassis.detailedChassis.frAxleDW.rightUCABody.r_CM[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1340]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.ucaMass.rCM[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1374]] /* chassis.detailedChassis.frAxleDW.pRightDW.upper_o[1] PARAM */);
  threadData->lastEquationSolved = 912;
}

/*
equation index: 913
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.sphere.r_shape[1] = chassis.detailedChassis.frAxleDW.rightUCABody.r_CM[1] - 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_913(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,913};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5202]] /* chassis.detailedChassis.frAxleDW.rightUCABody.sphere.r_shape[1] variable */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2011]] /* chassis.detailedChassis.frAxleDW.rightUCABody.r_CM[1] PARAM */) - 0.015;
  threadData->lastEquationSolved = 913;
}

/*
equation index: 914
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.r_CM[2] = chassis.detailedChassis.frAxleDW.pRightAxleMass.ucaMass.rCM[2] - chassis.detailedChassis.frAxleDW.pRightDW.upper_o[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_914(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,914};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2012]] /* chassis.detailedChassis.frAxleDW.rightUCABody.r_CM[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1341]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.ucaMass.rCM[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1375]] /* chassis.detailedChassis.frAxleDW.pRightDW.upper_o[2] PARAM */);
  threadData->lastEquationSolved = 914;
}

/*
equation index: 915
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.r_CM[3] = chassis.detailedChassis.frAxleDW.pRightAxleMass.ucaMass.rCM[3] - chassis.detailedChassis.frAxleDW.pRightDW.upper_o[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_915(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,915};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2013]] /* chassis.detailedChassis.frAxleDW.rightUCABody.r_CM[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1342]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.ucaMass.rCM[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1376]] /* chassis.detailedChassis.frAxleDW.pRightDW.upper_o[3] PARAM */);
  threadData->lastEquationSolved = 915;
}

/*
equation index: 916
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.cylinder.length = if sqrt(chassis.detailedChassis.frAxleDW.rightUCABody.r_CM * chassis.detailedChassis.frAxleDW.rightUCABody.r_CM) > 0.015 then sqrt(chassis.detailedChassis.frAxleDW.rightUCABody.r_CM * chassis.detailedChassis.frAxleDW.rightUCABody.r_CM) else 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_916(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,916};
  real_array tmp215;
  real_array tmp216;
  modelica_real tmp217;
  modelica_boolean tmp218;
  real_array tmp219;
  real_array tmp220;
  modelica_real tmp221;
  modelica_boolean tmp222;
  modelica_real tmp223;
  real_array_create(&tmp215, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2011]] /* chassis.detailedChassis.frAxleDW.rightUCABody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp216, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2011]] /* chassis.detailedChassis.frAxleDW.rightUCABody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp217 = mul_real_scalar_product(tmp215, tmp216);
  if(!(tmp217 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightUCABody.r_CM * chassis.detailedChassis.frAxleDW.rightUCABody.r_CM) was %g should be >= 0", tmp217);
    }
  }tmp218 = Greater(sqrt(tmp217),0.015);
  tmp222 = (modelica_boolean)tmp218;
  if(tmp222)
  {
    real_array_create(&tmp219, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2011]] /* chassis.detailedChassis.frAxleDW.rightUCABody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
    real_array_create(&tmp220, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2011]] /* chassis.detailedChassis.frAxleDW.rightUCABody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
    tmp221 = mul_real_scalar_product(tmp219, tmp220);
    if(!(tmp221 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightUCABody.r_CM * chassis.detailedChassis.frAxleDW.rightUCABody.r_CM) was %g should be >= 0", tmp221);
      }
    }
    tmp223 = sqrt(tmp221);
  }
  else
  {
    tmp223 = 0.0;
  }
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5156]] /* chassis.detailedChassis.frAxleDW.rightUCABody.cylinder.length variable */) = tmp223;
  threadData->lastEquationSolved = 916;
}

/*
equation index: 917
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.I_11 = chassis.detailedChassis.frAxleDW.pRightAxleMass.ucaMass.inertia[1,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_917(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,917};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1981]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I_11 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1330]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.ucaMass.inertia[1,1] PARAM */);
  threadData->lastEquationSolved = 917;
}

/*
equation index: 918
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.I[1,1] = chassis.detailedChassis.frAxleDW.rightUCABody.I_11
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_918(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,918};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1972]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I[1,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1981]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I_11 PARAM */);
  threadData->lastEquationSolved = 918;
}

/*
equation index: 919
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.I_21 = chassis.detailedChassis.frAxleDW.pRightAxleMass.ucaMass.inertia[2,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_919(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,919};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1982]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I_21 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1333]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.ucaMass.inertia[2,1] PARAM */);
  threadData->lastEquationSolved = 919;
}

/*
equation index: 920
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.I[2,1] = chassis.detailedChassis.frAxleDW.rightUCABody.I_21
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_920(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,920};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1975]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I[2,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1982]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I_21 PARAM */);
  threadData->lastEquationSolved = 920;
}

/*
equation index: 921
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.I[1,2] = chassis.detailedChassis.frAxleDW.rightUCABody.I_21
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_921(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,921};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1973]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I[1,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1982]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I_21 PARAM */);
  threadData->lastEquationSolved = 921;
}

/*
equation index: 922
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.I_22 = chassis.detailedChassis.frAxleDW.pRightAxleMass.ucaMass.inertia[2,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_922(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,922};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1983]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I_22 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1334]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.ucaMass.inertia[2,2] PARAM */);
  threadData->lastEquationSolved = 922;
}

/*
equation index: 923
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.I[2,2] = chassis.detailedChassis.frAxleDW.rightUCABody.I_22
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_923(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,923};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1976]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I[2,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1983]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I_22 PARAM */);
  threadData->lastEquationSolved = 923;
}

/*
equation index: 924
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.I_31 = chassis.detailedChassis.frAxleDW.pRightAxleMass.ucaMass.inertia[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_924(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,924};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1984]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I_31 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1336]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.ucaMass.inertia[3,1] PARAM */);
  threadData->lastEquationSolved = 924;
}

/*
equation index: 925
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.I[3,1] = chassis.detailedChassis.frAxleDW.rightUCABody.I_31
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_925(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,925};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1978]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I[3,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1984]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I_31 PARAM */);
  threadData->lastEquationSolved = 925;
}

/*
equation index: 926
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.I[1,3] = chassis.detailedChassis.frAxleDW.rightUCABody.I_31
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_926(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,926};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1974]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I[1,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1984]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I_31 PARAM */);
  threadData->lastEquationSolved = 926;
}

/*
equation index: 927
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.I_32 = chassis.detailedChassis.frAxleDW.pRightAxleMass.ucaMass.inertia[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_927(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,927};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1985]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I_32 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1337]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.ucaMass.inertia[3,2] PARAM */);
  threadData->lastEquationSolved = 927;
}

/*
equation index: 928
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.I[3,2] = chassis.detailedChassis.frAxleDW.rightUCABody.I_32
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_928(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,928};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1979]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I[3,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1985]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I_32 PARAM */);
  threadData->lastEquationSolved = 928;
}

/*
equation index: 929
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.I[2,3] = chassis.detailedChassis.frAxleDW.rightUCABody.I_32
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_929(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,929};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1977]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I[2,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1985]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I_32 PARAM */);
  threadData->lastEquationSolved = 929;
}

/*
equation index: 930
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.I_33 = chassis.detailedChassis.frAxleDW.pRightAxleMass.ucaMass.inertia[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_930(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,930};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1986]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I_33 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1338]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.ucaMass.inertia[3,3] PARAM */);
  threadData->lastEquationSolved = 930;
}

/*
equation index: 931
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.I[3,3] = chassis.detailedChassis.frAxleDW.rightUCABody.I_33
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_931(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,931};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1980]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I[3,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1986]] /* chassis.detailedChassis.frAxleDW.rightUCABody.I_33 PARAM */);
  threadData->lastEquationSolved = 931;
}

/*
equation index: 932
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.r_CM[1] = chassis.detailedChassis.frAxleDW.pRightAxleMass.lcaMass.rCM[1] - chassis.detailedChassis.frAxleDW.pRightDW.lower_o[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_932(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,932};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1565]] /* chassis.detailedChassis.frAxleDW.rightLCABody.r_CM[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1314]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.lcaMass.rCM[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1362]] /* chassis.detailedChassis.frAxleDW.pRightDW.lower_o[1] PARAM */);
  threadData->lastEquationSolved = 932;
}

/*
equation index: 933
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.sphere.r_shape[1] = chassis.detailedChassis.frAxleDW.rightLCABody.r_CM[1] - 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_933(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,933};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4444]] /* chassis.detailedChassis.frAxleDW.rightLCABody.sphere.r_shape[1] variable */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1565]] /* chassis.detailedChassis.frAxleDW.rightLCABody.r_CM[1] PARAM */) - 0.015;
  threadData->lastEquationSolved = 933;
}

/*
equation index: 934
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.r_CM[2] = chassis.detailedChassis.frAxleDW.pRightAxleMass.lcaMass.rCM[2] - chassis.detailedChassis.frAxleDW.pRightDW.lower_o[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_934(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,934};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1566]] /* chassis.detailedChassis.frAxleDW.rightLCABody.r_CM[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1315]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.lcaMass.rCM[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1363]] /* chassis.detailedChassis.frAxleDW.pRightDW.lower_o[2] PARAM */);
  threadData->lastEquationSolved = 934;
}

/*
equation index: 935
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.r_CM[3] = chassis.detailedChassis.frAxleDW.pRightAxleMass.lcaMass.rCM[3] - chassis.detailedChassis.frAxleDW.pRightDW.lower_o[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_935(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,935};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1567]] /* chassis.detailedChassis.frAxleDW.rightLCABody.r_CM[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1316]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.lcaMass.rCM[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1364]] /* chassis.detailedChassis.frAxleDW.pRightDW.lower_o[3] PARAM */);
  threadData->lastEquationSolved = 935;
}

/*
equation index: 936
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.cylinder.length = if sqrt(chassis.detailedChassis.frAxleDW.rightLCABody.r_CM * chassis.detailedChassis.frAxleDW.rightLCABody.r_CM) > 0.015 then sqrt(chassis.detailedChassis.frAxleDW.rightLCABody.r_CM * chassis.detailedChassis.frAxleDW.rightLCABody.r_CM) else 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_936(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,936};
  real_array tmp224;
  real_array tmp225;
  modelica_real tmp226;
  modelica_boolean tmp227;
  real_array tmp228;
  real_array tmp229;
  modelica_real tmp230;
  modelica_boolean tmp231;
  modelica_real tmp232;
  real_array_create(&tmp224, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1565]] /* chassis.detailedChassis.frAxleDW.rightLCABody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp225, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1565]] /* chassis.detailedChassis.frAxleDW.rightLCABody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp226 = mul_real_scalar_product(tmp224, tmp225);
  if(!(tmp226 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightLCABody.r_CM * chassis.detailedChassis.frAxleDW.rightLCABody.r_CM) was %g should be >= 0", tmp226);
    }
  }tmp227 = Greater(sqrt(tmp226),0.015);
  tmp231 = (modelica_boolean)tmp227;
  if(tmp231)
  {
    real_array_create(&tmp228, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1565]] /* chassis.detailedChassis.frAxleDW.rightLCABody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
    real_array_create(&tmp229, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1565]] /* chassis.detailedChassis.frAxleDW.rightLCABody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
    tmp230 = mul_real_scalar_product(tmp228, tmp229);
    if(!(tmp230 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightLCABody.r_CM * chassis.detailedChassis.frAxleDW.rightLCABody.r_CM) was %g should be >= 0", tmp230);
      }
    }
    tmp232 = sqrt(tmp230);
  }
  else
  {
    tmp232 = 0.0;
  }
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4398]] /* chassis.detailedChassis.frAxleDW.rightLCABody.cylinder.length variable */) = tmp232;
  threadData->lastEquationSolved = 936;
}

/*
equation index: 937
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.I_11 = chassis.detailedChassis.frAxleDW.pRightAxleMass.lcaMass.inertia[1,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_937(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,937};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1535]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I_11 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1304]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.lcaMass.inertia[1,1] PARAM */);
  threadData->lastEquationSolved = 937;
}

/*
equation index: 938
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.I[1,1] = chassis.detailedChassis.frAxleDW.rightLCABody.I_11
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_938(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,938};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1526]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I[1,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1535]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I_11 PARAM */);
  threadData->lastEquationSolved = 938;
}

/*
equation index: 939
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.I_21 = chassis.detailedChassis.frAxleDW.pRightAxleMass.lcaMass.inertia[2,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_939(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,939};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1536]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I_21 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1307]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.lcaMass.inertia[2,1] PARAM */);
  threadData->lastEquationSolved = 939;
}

/*
equation index: 940
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.I[2,1] = chassis.detailedChassis.frAxleDW.rightLCABody.I_21
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_940(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,940};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1529]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I[2,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1536]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I_21 PARAM */);
  threadData->lastEquationSolved = 940;
}

/*
equation index: 941
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.I[1,2] = chassis.detailedChassis.frAxleDW.rightLCABody.I_21
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_941(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,941};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1527]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I[1,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1536]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I_21 PARAM */);
  threadData->lastEquationSolved = 941;
}

/*
equation index: 942
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.I_22 = chassis.detailedChassis.frAxleDW.pRightAxleMass.lcaMass.inertia[2,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_942(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,942};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1537]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I_22 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1308]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.lcaMass.inertia[2,2] PARAM */);
  threadData->lastEquationSolved = 942;
}

/*
equation index: 943
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.I[2,2] = chassis.detailedChassis.frAxleDW.rightLCABody.I_22
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_943(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,943};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1530]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I[2,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1537]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I_22 PARAM */);
  threadData->lastEquationSolved = 943;
}

/*
equation index: 944
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.I_31 = chassis.detailedChassis.frAxleDW.pRightAxleMass.lcaMass.inertia[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_944(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,944};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1538]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I_31 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1310]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.lcaMass.inertia[3,1] PARAM */);
  threadData->lastEquationSolved = 944;
}

/*
equation index: 945
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.I[3,1] = chassis.detailedChassis.frAxleDW.rightLCABody.I_31
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_945(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,945};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1532]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I[3,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1538]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I_31 PARAM */);
  threadData->lastEquationSolved = 945;
}

/*
equation index: 946
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.I[1,3] = chassis.detailedChassis.frAxleDW.rightLCABody.I_31
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_946(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,946};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1528]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I[1,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1538]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I_31 PARAM */);
  threadData->lastEquationSolved = 946;
}

/*
equation index: 947
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.I_32 = chassis.detailedChassis.frAxleDW.pRightAxleMass.lcaMass.inertia[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_947(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,947};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1539]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I_32 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1311]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.lcaMass.inertia[3,2] PARAM */);
  threadData->lastEquationSolved = 947;
}

/*
equation index: 948
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.I[3,2] = chassis.detailedChassis.frAxleDW.rightLCABody.I_32
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_948(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,948};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1533]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I[3,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1539]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I_32 PARAM */);
  threadData->lastEquationSolved = 948;
}

/*
equation index: 949
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.I[2,3] = chassis.detailedChassis.frAxleDW.rightLCABody.I_32
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_949(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,949};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1531]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I[2,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1539]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I_32 PARAM */);
  threadData->lastEquationSolved = 949;
}

/*
equation index: 950
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.I_33 = chassis.detailedChassis.frAxleDW.pRightAxleMass.lcaMass.inertia[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_950(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,950};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1540]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I_33 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1312]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.lcaMass.inertia[3,3] PARAM */);
  threadData->lastEquationSolved = 950;
}

/*
equation index: 951
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.I[3,3] = chassis.detailedChassis.frAxleDW.rightLCABody.I_33
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_951(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,951};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1534]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I[3,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1540]] /* chassis.detailedChassis.frAxleDW.rightLCABody.I_33 PARAM */);
  threadData->lastEquationSolved = 951;
}

/*
equation index: 952
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.r_CM[1] = chassis.detailedChassis.frAxleDW.pRightAxleMass.unsprungMass.rCM[1] - chassis.detailedChassis.frAxleDW.pRightDW.wheelCenter[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_952(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,952};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2060]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.r_CM[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1353]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.unsprungMass.rCM[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1377]] /* chassis.detailedChassis.frAxleDW.pRightDW.wheelCenter[1] PARAM */);
  threadData->lastEquationSolved = 952;
}

/*
equation index: 953
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.sphere.r_shape[1] = chassis.detailedChassis.frAxleDW.rightUnsprungBody.r_CM[1] - 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_953(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,953};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5265]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.sphere.r_shape[1] variable */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2060]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.r_CM[1] PARAM */) - 0.015;
  threadData->lastEquationSolved = 953;
}

/*
equation index: 954
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.r_CM[2] = chassis.detailedChassis.frAxleDW.pRightAxleMass.unsprungMass.rCM[2] - chassis.detailedChassis.frAxleDW.pRightDW.wheelCenter[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_954(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,954};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2061]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.r_CM[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1354]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.unsprungMass.rCM[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1378]] /* chassis.detailedChassis.frAxleDW.pRightDW.wheelCenter[2] PARAM */);
  threadData->lastEquationSolved = 954;
}

/*
equation index: 955
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.r_CM[3] = chassis.detailedChassis.frAxleDW.pRightAxleMass.unsprungMass.rCM[3] - chassis.detailedChassis.frAxleDW.pRightDW.wheelCenter[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_955(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,955};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2062]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.r_CM[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1355]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.unsprungMass.rCM[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1379]] /* chassis.detailedChassis.frAxleDW.pRightDW.wheelCenter[3] PARAM */);
  threadData->lastEquationSolved = 955;
}

/*
equation index: 956
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.cylinder.length = if sqrt(chassis.detailedChassis.frAxleDW.rightUnsprungBody.r_CM * chassis.detailedChassis.frAxleDW.rightUnsprungBody.r_CM) > 0.015 then sqrt(chassis.detailedChassis.frAxleDW.rightUnsprungBody.r_CM * chassis.detailedChassis.frAxleDW.rightUnsprungBody.r_CM) else 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_956(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,956};
  real_array tmp233;
  real_array tmp234;
  modelica_real tmp235;
  modelica_boolean tmp236;
  real_array tmp237;
  real_array tmp238;
  modelica_real tmp239;
  modelica_boolean tmp240;
  modelica_real tmp241;
  real_array_create(&tmp233, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2060]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp234, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2060]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp235 = mul_real_scalar_product(tmp233, tmp234);
  if(!(tmp235 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightUnsprungBody.r_CM * chassis.detailedChassis.frAxleDW.rightUnsprungBody.r_CM) was %g should be >= 0", tmp235);
    }
  }tmp236 = Greater(sqrt(tmp235),0.015);
  tmp240 = (modelica_boolean)tmp236;
  if(tmp240)
  {
    real_array_create(&tmp237, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2060]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
    real_array_create(&tmp238, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2060]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
    tmp239 = mul_real_scalar_product(tmp237, tmp238);
    if(!(tmp239 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightUnsprungBody.r_CM * chassis.detailedChassis.frAxleDW.rightUnsprungBody.r_CM) was %g should be >= 0", tmp239);
      }
    }
    tmp241 = sqrt(tmp239);
  }
  else
  {
    tmp241 = 0.0;
  }
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5228]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.cylinder.length variable */) = tmp241;
  threadData->lastEquationSolved = 956;
}

/*
equation index: 957
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_11 = chassis.detailedChassis.frAxleDW.pRightAxleMass.unsprungMass.inertia[1,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_957(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,957};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2030]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_11 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1343]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.unsprungMass.inertia[1,1] PARAM */);
  threadData->lastEquationSolved = 957;
}

/*
equation index: 958
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.I[1,1] = chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_11
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_958(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,958};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2021]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I[1,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2030]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_11 PARAM */);
  threadData->lastEquationSolved = 958;
}

/*
equation index: 959
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_21 = chassis.detailedChassis.frAxleDW.pRightAxleMass.unsprungMass.inertia[2,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_959(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,959};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2031]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_21 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1346]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.unsprungMass.inertia[2,1] PARAM */);
  threadData->lastEquationSolved = 959;
}

/*
equation index: 960
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.I[2,1] = chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_21
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_960(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,960};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2024]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I[2,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2031]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_21 PARAM */);
  threadData->lastEquationSolved = 960;
}

/*
equation index: 961
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.I[1,2] = chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_21
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_961(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,961};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2022]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I[1,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2031]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_21 PARAM */);
  threadData->lastEquationSolved = 961;
}

/*
equation index: 962
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_22 = chassis.detailedChassis.frAxleDW.pRightAxleMass.unsprungMass.inertia[2,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_962(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,962};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2032]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_22 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1347]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.unsprungMass.inertia[2,2] PARAM */);
  threadData->lastEquationSolved = 962;
}

/*
equation index: 963
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.I[2,2] = chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_22
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_963(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,963};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2025]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I[2,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2032]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_22 PARAM */);
  threadData->lastEquationSolved = 963;
}

/*
equation index: 964
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_31 = chassis.detailedChassis.frAxleDW.pRightAxleMass.unsprungMass.inertia[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_964(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,964};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2033]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_31 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1349]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.unsprungMass.inertia[3,1] PARAM */);
  threadData->lastEquationSolved = 964;
}

/*
equation index: 965
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.I[3,1] = chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_31
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_965(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,965};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2027]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I[3,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2033]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_31 PARAM */);
  threadData->lastEquationSolved = 965;
}

/*
equation index: 966
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.I[1,3] = chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_31
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_966(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,966};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2023]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I[1,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2033]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_31 PARAM */);
  threadData->lastEquationSolved = 966;
}

/*
equation index: 967
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_32 = chassis.detailedChassis.frAxleDW.pRightAxleMass.unsprungMass.inertia[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_967(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,967};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2034]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_32 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1350]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.unsprungMass.inertia[3,2] PARAM */);
  threadData->lastEquationSolved = 967;
}

/*
equation index: 968
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.I[3,2] = chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_32
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_968(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,968};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2028]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I[3,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2034]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_32 PARAM */);
  threadData->lastEquationSolved = 968;
}

/*
equation index: 969
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.I[2,3] = chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_32
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_969(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,969};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2026]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I[2,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2034]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_32 PARAM */);
  threadData->lastEquationSolved = 969;
}

/*
equation index: 970
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_33 = chassis.detailedChassis.frAxleDW.pRightAxleMass.unsprungMass.inertia[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_970(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,970};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2035]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_33 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1351]] /* chassis.detailedChassis.frAxleDW.pRightAxleMass.unsprungMass.inertia[3,3] PARAM */);
  threadData->lastEquationSolved = 970;
}

/*
equation index: 971
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.I[3,3] = chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_33
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_971(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,971};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2029]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I[3,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2035]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.I_33 PARAM */);
  threadData->lastEquationSolved = 971;
}

/*
equation index: 972
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.r[3] = chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[3] - chassis.detailedChassis.frAxleDW.rightBellcrank.pivot[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_972(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,972};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1481]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.r[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1450]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1459]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pivot[3] PARAM */);
  threadData->lastEquationSolved = 972;
}

/*
equation index: 973
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.lengthDirection[3] = chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_973(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,973};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1478]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1481]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.r[3] PARAM */);
  threadData->lastEquationSolved = 973;
}

/*
equation index: 974
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.r[2] = chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[2] - chassis.detailedChassis.frAxleDW.rightBellcrank.pivot[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_974(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,974};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1480]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.r[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1449]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1458]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pivot[2] PARAM */);
  threadData->lastEquationSolved = 974;
}

/*
equation index: 975
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.lengthDirection[2] = chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_975(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,975};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1477]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1480]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.r[2] PARAM */);
  threadData->lastEquationSolved = 975;
}

/*
equation index: 976
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.r[1] = chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[1] - chassis.detailedChassis.frAxleDW.rightBellcrank.pivot[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_976(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,976};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1479]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.r[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1448]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1457]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pivot[1] PARAM */);
  threadData->lastEquationSolved = 976;
}

/*
equation index: 977
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.length = sqrt(chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_977(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,977};
  modelica_real tmp242;
  modelica_real tmp243;
  modelica_real tmp244;
  modelica_real tmp245;
  tmp242 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1479]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.r[1] PARAM */);
  tmp243 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1480]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.r[2] PARAM */);
  tmp244 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1481]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.r[3] PARAM */);
  tmp245 = (tmp242 * tmp242) + (tmp243 * tmp243) + (tmp244 * tmp244);
  if(!(tmp245 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.r[3] ^ 2.0) was %g should be >= 0", tmp245);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1475]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.length PARAM */) = sqrt(tmp245);
  threadData->lastEquationSolved = 977;
}

/*
equation index: 978
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.width = chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_978(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,978};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1485]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1475]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 978;
}

/*
equation index: 979
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.height = chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_979(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,979};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1474]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1485]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.width PARAM */);
  threadData->lastEquationSolved = 979;
}

/*
equation index: 980
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.lengthDirection[1] = chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_980(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,980};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1476]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1479]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toFirstPickup.r[1] PARAM */);
  threadData->lastEquationSolved = 980;
}

/*
equation index: 981
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] = chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[3] - chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_981(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,981};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1497]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1453]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1450]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[3] PARAM */);
  threadData->lastEquationSolved = 981;
}

/*
equation index: 982
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.lengthDirection[3] = chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_982(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,982};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1494]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1497]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */);
  threadData->lastEquationSolved = 982;
}

/*
equation index: 983
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] = chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[2] - chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_983(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,983};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1496]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1452]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1449]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[2] PARAM */);
  threadData->lastEquationSolved = 983;
}

/*
equation index: 984
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.lengthDirection[2] = chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_984(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,984};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1493]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1496]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */);
  threadData->lastEquationSolved = 984;
}

/*
equation index: 985
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] = chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[1] - chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_985(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,985};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1495]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1451]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1448]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[1] PARAM */);
  threadData->lastEquationSolved = 985;
}

/*
equation index: 986
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.length = sqrt(chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_986(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,986};
  modelica_real tmp246;
  modelica_real tmp247;
  modelica_real tmp248;
  modelica_real tmp249;
  tmp246 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1495]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */);
  tmp247 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1496]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */);
  tmp248 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1497]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */);
  tmp249 = (tmp246 * tmp246) + (tmp247 * tmp247) + (tmp248 * tmp248);
  if(!(tmp249 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] ^ 2.0) was %g should be >= 0", tmp249);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1491]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.length PARAM */) = sqrt(tmp249);
  threadData->lastEquationSolved = 986;
}

/*
equation index: 987
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.width = chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_987(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,987};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1501]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1491]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 987;
}

/*
equation index: 988
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.height = chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_988(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,988};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1490]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1501]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.width PARAM */);
  threadData->lastEquationSolved = 988;
}
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_functionInitialEquations_1(DATA *data, threadData_t *threadData)
{
  static void (*const eqFunctions[494])(DATA*, threadData_t*) = {
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28613,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28612,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28610,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28609,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28608,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28606,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28605,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28604,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28883,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28884,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28885,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28603,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28602,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28601,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28600,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28599,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28598,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28597,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28596,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28595,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28594,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28593,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28592,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28591,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28590,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28589,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28588,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28587,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28586,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28585,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28584,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28583,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28582,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28581,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28580,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28973,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28974,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28995,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28997,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28999,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29007,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29009,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29011,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_538,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_539,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_540,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_541,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32179,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_543,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_544,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_545,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_546,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28900,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28899,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28898,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_550,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_551,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_552,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_553,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_554,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_555,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_556,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28776,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_558,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_559,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28777,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_561,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_562,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_563,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_564,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_565,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_566,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_567,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_568,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_569,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_570,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_571,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28894,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28893,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28892,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_575,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_576,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_577,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_578,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_579,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_580,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_581,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_582,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_583,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28810,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_585,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_586,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28811,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_588,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_589,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_590,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_591,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_592,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_593,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_594,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_595,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_596,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_597,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28987,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28837,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28838,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_601,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_602,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_603,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_604,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_605,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_606,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_607,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_608,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_609,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_610,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_611,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_612,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28579,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28670,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_615,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_616,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28578,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28677,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_619,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_620,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28577,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28733,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_623,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_624,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28576,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28740,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_627,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_628,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_629,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_630,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_631,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_632,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_633,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_634,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_635,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_636,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_637,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_638,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_639,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_640,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_641,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28849,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28851,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28852,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28850,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_646,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_647,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_648,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_649,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_650,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_651,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36406,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_653,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36404,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_655,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_656,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36405,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_658,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_659,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_660,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29008,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36399,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36402,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_664,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_665,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29006,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36400,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36403,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_669,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_670,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29010,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36398,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36401,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_674,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_675,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_676,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_677,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_678,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_679,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_680,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_681,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_682,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_683,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_684,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_685,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_686,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_687,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_688,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_689,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36382,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_691,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36380,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_693,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36381,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_695,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_696,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_697,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_698,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_699,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_700,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_701,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_702,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_703,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29002,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36387,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36390,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_707,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_708,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29004,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36386,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36389,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_712,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_713,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29000,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36388,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36391,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_717,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29003,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36393,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_720,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29005,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36392,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_723,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29001,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36394,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_726,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_727,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_728,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_729,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_730,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_731,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_732,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_733,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28764,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_735,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_736,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_737,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_738,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_739,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_740,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_741,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_742,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_743,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_744,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28763,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_746,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_747,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_748,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_749,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_750,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_751,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_752,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_753,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_754,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_755,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_756,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_757,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_758,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_759,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_760,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_761,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28762,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_763,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_764,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_765,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_766,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_767,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_768,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_769,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_770,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_771,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_772,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_773,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36397,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_775,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36395,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_777,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_778,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_779,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_780,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36396,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_782,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_783,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_784,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_785,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_786,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_787,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_788,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_789,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_790,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_791,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_792,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_793,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_794,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_795,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_796,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_797,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_798,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_799,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_800,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_801,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_802,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_803,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_804,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_805,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_806,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_807,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_808,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_809,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_810,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_811,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_812,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_813,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_814,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_815,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28896,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_817,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36384,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_819,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28897,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_821,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36383,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_823,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_824,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_825,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_826,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_827,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_828,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_829,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28895,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_831,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_832,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_833,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_834,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_835,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_836,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_837,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36385,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_839,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_840,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_841,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_842,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_843,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28783,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36379,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28779,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36377,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28781,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36378,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_850,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_851,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_852,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_853,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_854,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_855,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_856,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_857,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_858,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_859,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28788,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36376,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28786,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36375,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28784,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36374,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_866,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28785,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36371,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28789,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36373,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28787,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36372,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_873,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_874,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_875,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_876,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_877,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_878,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_879,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_880,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_881,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_882,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_883,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_884,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_885,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_886,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_887,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_888,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_889,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_890,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_891,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_892,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_893,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_894,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_895,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_896,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_897,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_898,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_899,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_900,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_901,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_902,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_903,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_904,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_905,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_906,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_907,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_908,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_909,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_910,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_911,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_912,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_913,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_914,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_915,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_916,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_917,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_918,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_919,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_920,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_921,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_922,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_923,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_924,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_925,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_926,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_927,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_928,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_929,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_930,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_931,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_932,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_933,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_934,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_935,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_936,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_937,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_938,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_939,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_940,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_941,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_942,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_943,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_944,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_945,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_946,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_947,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_948,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_949,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_950,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_951,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_952,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_953,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_954,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_955,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_956,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_957,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_958,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_959,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_960,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_961,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_962,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_963,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_964,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_965,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_966,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_967,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_968,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_969,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_970,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_971,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_972,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_973,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_974,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_975,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_976,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_977,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_978,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_979,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_980,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_981,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_982,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_983,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_984,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_985,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_986,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_987,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_988
  };
  
  for (int id = 0; id < 494; id++) {
    eqFunctions[id](data, threadData);
  }
}
#if defined(__cplusplus)
}
#endif