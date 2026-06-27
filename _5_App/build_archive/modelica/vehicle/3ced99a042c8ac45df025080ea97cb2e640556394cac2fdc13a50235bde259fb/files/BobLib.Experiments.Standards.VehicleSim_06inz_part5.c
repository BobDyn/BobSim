#include "BobLib.Experiments.Standards.VehicleSim_model.h"
#if defined(__cplusplus)
extern "C" {
#endif
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29853(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29852(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29840(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29850(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29849(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29848(DATA *data, threadData_t *threadData);


/*
equation index: 2583
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.frame_a.r_0[3] = chassis.detailedChassis.rrAxleDW.rightLCABody.frame_a.r_0[3] + chassis.detailedChassis.frameRR.R.T[1,3] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1] + chassis.detailedChassis.frameRR.R.T[2,3] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2] + chassis.detailedChassis.frameRR.R.T[3,3] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2583(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2583};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8998]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.frame_a.r_0[3] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8168]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.frame_a.r_0[3] DUMMY_STATE */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6115]] /* chassis.detailedChassis.frameRR.R.T[1,3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4817]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6118]] /* chassis.detailedChassis.frameRR.R.T[2,3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4818]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6121]] /* chassis.detailedChassis.frameRR.R.T[3,3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4819]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3] PARAM */));
  threadData->lastEquationSolved = 2583;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29860(DATA *data, threadData_t *threadData);


/*
equation index: 2585
type: SIMPLE_ASSIGN
chassis.detailedChassis.frameRR.r_0[3] = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.wheelVelSensor.der1[3].u - chassis.detailedChassis.frameRR.R.T[3,3] * chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.s
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2585(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2585};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6127]] /* chassis.detailedChassis.frameRR.r_0[3] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8795]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.wheelVelSensor.der1[3].u DUMMY_STATE */) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6121]] /* chassis.detailedChassis.frameRR.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8739]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.s DUMMY_STATE */)));
  threadData->lastEquationSolved = 2585;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29862(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29863(DATA *data, threadData_t *threadData);


/*
equation index: 2588
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.e_zw[3] = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,1] * chassis.detailedChassis.frameRR.R.T[1,3] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,2] * chassis.detailedChassis.frameRR.R.T[2,3] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,3] * chassis.detailedChassis.frameRR.R.T[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2588(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2588};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8617]] /* chassis.detailedChassis.rrAxleDW.rightTire.e_zw[3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8688]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6115]] /* chassis.detailedChassis.frameRR.R.T[1,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8689]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6118]] /* chassis.detailedChassis.frameRR.R.T[2,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8690]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6121]] /* chassis.detailedChassis.frameRR.R.T[3,3] DUMMY_STATE */));
  threadData->lastEquationSolved = 2588;
}

/*
equation index: 2589
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.e_zw[2] = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,1] * chassis.detailedChassis.frameRR.R.T[1,3] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,2] * chassis.detailedChassis.frameRR.R.T[2,3] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,3] * chassis.detailedChassis.frameRR.R.T[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2589(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2589};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8616]] /* chassis.detailedChassis.rrAxleDW.rightTire.e_zw[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8685]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6115]] /* chassis.detailedChassis.frameRR.R.T[1,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8686]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6118]] /* chassis.detailedChassis.frameRR.R.T[2,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8687]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6121]] /* chassis.detailedChassis.frameRR.R.T[3,3] DUMMY_STATE */));
  threadData->lastEquationSolved = 2589;
}

/*
equation index: 2590
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.gamma = asin(max(-1.0, min(1.0, chassis.detailedChassis.rrAxleDW.rightTire.e_zw[2])))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2590(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2590};
  modelica_real tmp684;
  tmp684 = fmax(-1.0,fmin(1.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8616]] /* chassis.detailedChassis.rrAxleDW.rightTire.e_zw[2] variable */)));
  if(!(tmp684 >= -1.0 && tmp684 <= 1.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of asin(max(-1.0, min(1.0, chassis.detailedChassis.rrAxleDW.rightTire.e_zw[2]))) outside the domain -1.0 <= %g <= 1.0", tmp684);
    }
  }
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8657]] /* chassis.detailedChassis.rrAxleDW.rightTire.gamma variable */) = asin(tmp684);
  threadData->lastEquationSolved = 2590;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31266(DATA *data, threadData_t *threadData);


/*
equation index: 2592
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.e_spin[3] = chassis.detailedChassis.rrAxleDW.rightTire.e_zw[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2592(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2592};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8602]] /* chassis.detailedChassis.rrAxleDW.rightTire.e_spin[3] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8616]] /* chassis.detailedChassis.rrAxleDW.rightTire.e_zw[2] variable */);
  threadData->lastEquationSolved = 2592;
}

/*
equation index: 2593
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.e_zw[1] = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,1] * chassis.detailedChassis.frameRR.R.T[1,3] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,2] * chassis.detailedChassis.frameRR.R.T[2,3] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,3] * chassis.detailedChassis.frameRR.R.T[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2593(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2593};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8615]] /* chassis.detailedChassis.rrAxleDW.rightTire.e_zw[1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8682]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6115]] /* chassis.detailedChassis.frameRR.R.T[1,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8683]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6118]] /* chassis.detailedChassis.frameRR.R.T[2,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8684]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6121]] /* chassis.detailedChassis.frameRR.R.T[3,3] DUMMY_STATE */));
  threadData->lastEquationSolved = 2593;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29550(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29546(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29549(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29548(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29547(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29555(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29551(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29554(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29553(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29552(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29538(DATA *data, threadData_t *threadData);


void BobLib_Experiments_Standards_VehicleSim_eqFunction_2605(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2606(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2607(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2608(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2609(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2610(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2611(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2612(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2613(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2614(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2615(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2616(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2617(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2618(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2619(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2620(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2621(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2622(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2623(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2624(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2625(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2626(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2627(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2628(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2629(DATA*, threadData_t*);
/*
equation index: 2657
indexNonlinear: 3
type: NONLINEAR

vars: {chassis.detailedChassis.rrAxleDW.rightBellcrank.revolute.phi}
eqns: {2605, 2606, 2607, 2608, 2609, 2610, 2611, 2612, 2613, 2614, 2615, 2616, 2617, 2618, 2619, 2620, 2621, 2622, 2623, 2624, 2625, 2626, 2627, 2628, 2629}
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2657(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2657};
  int retValue;
  infoStreamPrint(OMC_LOG_DT, 0, "Solving nonlinear system 2657 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
  /* get old value */
  data->simulationInfo->nonlinearSystemData[3].nlsxOld[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7936]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.revolute.phi DUMMY_STATE */);
  retValue = solve_nonlinear_system(data, threadData, 3);
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,2657};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving non-linear system 2657 failed at time=%.15g.\nFor more information please use -lv LOG_NLS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7936]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.revolute.phi DUMMY_STATE */) = data->simulationInfo->nonlinearSystemData[3].nlsx[0];
  threadData->lastEquationSolved = 2657;
}

/*
equation index: 2658
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.widthDirection[1] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2658(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2658};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8432]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.widthDirection[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8326]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */);
  threadData->lastEquationSolved = 2658;
}

/*
equation index: 2659
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.widthDirection[2] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2659(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2659};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8433]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.widthDirection[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8327]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */);
  threadData->lastEquationSolved = 2659;
}

/*
equation index: 2660
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.widthDirection[3] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2660(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2660};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8434]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.widthDirection[3] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8328]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */);
  threadData->lastEquationSolved = 2660;
}

/*
equation index: 2661
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[2] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2661(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2661};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8427]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[2] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8367]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r[2] DUMMY_STATE */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8324]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8327]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8330]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */));
  threadData->lastEquationSolved = 2661;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29668(DATA *data, threadData_t *threadData);


/*
equation index: 2663
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.vis.r[2] = chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2663(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2663};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8026]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.vis.r[2] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8427]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[2] DUMMY_STATE */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8324]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8327]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8330]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */));
  threadData->lastEquationSolved = 2663;
}

/*
equation index: 2664
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[3] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r[3] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2664(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2664};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8428]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[3] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8368]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r[3] DUMMY_STATE */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8325]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8328]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8331]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */));
  threadData->lastEquationSolved = 2664;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29620(DATA *data, threadData_t *threadData);


/*
equation index: 2666
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.vis.r[3] = chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[3] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2666(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2666};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8027]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.vis.r[3] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8428]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[3] DUMMY_STATE */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8325]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8328]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8331]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */));
  threadData->lastEquationSolved = 2666;
}

/*
equation index: 2667
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[1] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2667(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2667};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8426]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[1] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8366]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r[1] DUMMY_STATE */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8323]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8326]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8329]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */));
  threadData->lastEquationSolved = 2667;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29615(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29669(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29670(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29672(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29678(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29673(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29674(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29675(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29676(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29677(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29671(DATA *data, threadData_t *threadData);


/*
equation index: 2679
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.vis.r[1] = chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2679(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2679};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8025]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.vis.r[1] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8426]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[1] DUMMY_STATE */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8323]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8326]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8329]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */));
  threadData->lastEquationSolved = 2679;
}

void BobLib_Experiments_Standards_VehicleSim_eqFunction_2680(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2681(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2682(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2683(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2684(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2685(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2686(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2687(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2688(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2689(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2690(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2691(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2692(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2693(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2694(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2695(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2696(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2697(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2698(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2699(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2700(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2701(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2702(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2703(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2704(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2705(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2706(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2707(DATA*, threadData_t*);
/*
equation index: 2708
indexNonlinear: 4
type: NONLINEAR

vars: {chassis.detailedChassis.rrAxleDW.stabar.mountAxis.phi}
eqns: {2680, 2681, 2682, 2683, 2684, 2685, 2686, 2687, 2688, 2689, 2690, 2691, 2692, 2693, 2694, 2695, 2696, 2697, 2698, 2699, 2700, 2701, 2702, 2703, 2704, 2705, 2706, 2707}
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2708(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2708};
  int retValue;
  infoStreamPrint(OMC_LOG_DT, 0, "Solving nonlinear system 2708 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
  /* get old value */
  data->simulationInfo->nonlinearSystemData[4].nlsxOld[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9556]] /* chassis.detailedChassis.rrAxleDW.stabar.mountAxis.phi DUMMY_STATE */);
  retValue = solve_nonlinear_system(data, threadData, 4);
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,2708};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving non-linear system 2708 failed at time=%.15g.\nFor more information please use -lv LOG_NLS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9556]] /* chassis.detailedChassis.rrAxleDW.stabar.mountAxis.phi DUMMY_STATE */) = data->simulationInfo->nonlinearSystemData[4].nlsx[0];
  threadData->lastEquationSolved = 2708;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29656(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29657(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29658(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29659(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29660(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29661(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29662(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29663(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29664(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29665(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29666(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29667(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29679(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29680(DATA *data, threadData_t *threadData);


/*
equation index: 2723
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[2] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2723(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2723};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8283]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8326]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8279]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8327]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8280]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8328]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8281]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[3] DUMMY_STATE */));
  threadData->lastEquationSolved = 2723;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29682(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29683(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29684(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29685(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29687(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29686(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29688(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29689(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29692(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29691(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29693(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29690(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29710(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29706(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29702(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29698(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29701(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29700(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29699(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29694(DATA *data, threadData_t *threadData);


/*
equation index: 2744
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a1[3] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[3] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[3]) / chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodLength - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[3] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[3]) / ((chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[3]) * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodLength)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2744(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2744};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8260]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a1[3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8251]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[3] variable */)) * (DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8246]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8319]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8247]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8320]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8248]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8321]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[3] variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3854]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodLength PARAM */),"chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodLength",equationIndexes)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8248]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[3] variable */)) * (DIVISION_SIM(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3846]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8319]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[1] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3847]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8320]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[2] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3848]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8321]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[3] variable */)),(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3846]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8249]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[1] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3847]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8250]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[2] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3848]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8251]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[3] variable */))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3854]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodLength PARAM */)),"(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[3]) * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodLength",equationIndexes)));
  threadData->lastEquationSolved = 2744;
}

/*
equation index: 2745
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a1[2] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[2] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[3]) / chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodLength - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[2] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[3]) / ((chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[3]) * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodLength)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2745(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2745};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8259]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a1[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8250]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[2] variable */)) * (DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8246]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8319]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8247]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8320]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8248]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8321]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[3] variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3854]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodLength PARAM */),"chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodLength",equationIndexes)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8247]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[2] variable */)) * (DIVISION_SIM(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3846]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8319]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[1] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3847]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8320]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[2] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3848]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8321]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[3] variable */)),(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3846]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8249]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[1] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3847]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8250]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[2] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3848]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8251]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[3] variable */))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3854]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodLength PARAM */)),"(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[3]) * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodLength",equationIndexes)));
  threadData->lastEquationSolved = 2745;
}

/*
equation index: 2746
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a1[1] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[1] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[3]) / chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodLength - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[1] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[3]) / ((chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[3]) * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodLength)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2746(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2746};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8258]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a1[1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8249]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[1] variable */)) * (DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8246]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8319]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8247]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8320]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8248]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8321]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[3] variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3854]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodLength PARAM */),"chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodLength",equationIndexes)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8246]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_a[1] variable */)) * (DIVISION_SIM(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3846]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8319]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[1] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3847]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8320]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[2] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3848]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8321]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.t_ia_a[3] variable */)),(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3846]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8249]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[1] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3847]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8250]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[2] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3848]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8251]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[3] variable */))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3854]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodLength PARAM */)),"(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_a[3]) * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodLength",equationIndexes)));
  threadData->lastEquationSolved = 2746;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29697(DATA *data, threadData_t *threadData);


/*
equation index: 2748
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.R.T[3,3] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[3,1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[3,2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[3,3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2748(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2748};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8353]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.R.T[3,3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8227]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[3,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8325]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8228]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[3,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8328]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8229]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[3,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8331]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */));
  threadData->lastEquationSolved = 2748;
}

/*
equation index: 2749
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.R.T[3,2] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[3,1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[3,2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[3,3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2749(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2749};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8352]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.R.T[3,2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8227]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[3,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8324]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8228]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[3,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8327]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8229]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[3,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8330]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */));
  threadData->lastEquationSolved = 2749;
}

/*
equation index: 2750
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.R.T[3,1] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[3,1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[3,2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[3,3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2750(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2750};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8351]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.R.T[3,1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8227]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[3,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8323]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8228]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[3,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8326]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8229]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[3,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8329]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 2750;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29696(DATA *data, threadData_t *threadData);


/*
equation index: 2752
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.R.T[2,3] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[2,1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[2,2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[2,3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2752(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2752};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8350]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.R.T[2,3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8224]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[2,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8325]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8225]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[2,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8328]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8226]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[2,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8331]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */));
  threadData->lastEquationSolved = 2752;
}

/*
equation index: 2753
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.R.T[2,2] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[2,1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[2,2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[2,3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2753(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2753};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8349]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.R.T[2,2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8224]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[2,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8324]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8225]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[2,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8327]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8226]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[2,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8330]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */));
  threadData->lastEquationSolved = 2753;
}

/*
equation index: 2754
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.R.T[2,1] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[2,1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[2,2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[2,3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2754(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2754};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8348]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.R.T[2,1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8224]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[2,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8323]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8225]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[2,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8326]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8226]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[2,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8329]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 2754;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29695(DATA *data, threadData_t *threadData);


/*
equation index: 2756
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.R.T[1,3] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[1,1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[1,2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[1,3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2756(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2756};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8347]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.R.T[1,3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8221]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[1,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8325]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8222]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[1,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8328]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8223]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[1,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8331]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */));
  threadData->lastEquationSolved = 2756;
}

/*
equation index: 2757
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.R.T[1,2] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[1,1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[1,2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[1,3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2757(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2757};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8346]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.R.T[1,2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8221]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[1,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8324]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8222]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[1,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8327]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8223]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[1,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8330]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */));
  threadData->lastEquationSolved = 2757;
}

/*
equation index: 2758
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.R.T[1,1] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[1,1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[1,2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[1,3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2758(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2758};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8345]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.R.T[1,1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8221]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[1,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8323]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8222]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[1,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8326]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8223]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.R_rel_ia.T[1,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8329]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 2758;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29864(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29714(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29883(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29882(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29884(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29907(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29908(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29905(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29906(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29903(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29904(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29917(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30086(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29918(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29913(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29914(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29915(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29909(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29910(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30109(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30110(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30102(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30103(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30088(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30089(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30104(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30105(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30107(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30118(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30106(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30114(DATA *data, threadData_t *threadData);


/*
equation index: 2790
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[1,2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] + $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] + $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2790(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2790};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1897]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[1,2]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9406]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1923]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1908]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9426]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9407]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1917]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1909]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9420]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4488]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1920]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[2]) DUMMY_DER */));
  threadData->lastEquationSolved = 2790;
}

/*
equation index: 2791
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[2,2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] + $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] + $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2791(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2791};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1900]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[2,2]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9408]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1923]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1910]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9426]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9409]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1917]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1911]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9420]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4489]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1920]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[2]) DUMMY_DER */));
  threadData->lastEquationSolved = 2791;
}

/*
equation index: 2792
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[3,2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] + $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] + $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2792(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2792};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1903]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[3,2]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9410]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1923]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1912]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9426]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9411]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1917]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1913]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9420]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4490]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1920]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[2]) DUMMY_DER */));
  threadData->lastEquationSolved = 2792;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30108(DATA *data, threadData_t *threadData);


/*
equation index: 2794
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[1,1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] + $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2794(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2794};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1896]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[1,1]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9406]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1922]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1908]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9425]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4488]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1919]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[1]) DUMMY_DER */));
  threadData->lastEquationSolved = 2794;
}

/*
equation index: 2795
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[2,1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] + $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2795(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2795};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1899]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[2,1]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9408]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1922]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1910]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9425]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4489]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1919]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[1]) DUMMY_DER */));
  threadData->lastEquationSolved = 2795;
}

/*
equation index: 2796
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[3,1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] + $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2796(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2796};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1902]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[3,1]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9410]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1922]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1912]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9425]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4490]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1919]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[1]) DUMMY_DER */));
  threadData->lastEquationSolved = 2796;
}

/*
equation index: 2797
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[1,3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] + $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] + $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2797(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2797};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1898]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[1,3]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9406]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1924]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1908]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9427]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9407]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1918]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1909]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9421]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4488]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1921]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[3]) DUMMY_DER */));
  threadData->lastEquationSolved = 2797;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30137(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30141(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30145(DATA *data, threadData_t *threadData);


/*
equation index: 2801
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[2,3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] + $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] + $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2801(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2801};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1901]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[2,3]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9408]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1924]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1910]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9427]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9409]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1918]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1911]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9421]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4489]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1921]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[3]) DUMMY_DER */));
  threadData->lastEquationSolved = 2801;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30136(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30140(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30144(DATA *data, threadData_t *threadData);


/*
equation index: 2805
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[3,3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] + $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] + $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2805(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2805};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1904]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[3,3]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9410]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1924]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1912]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9427]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9411]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1918]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1913]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9421]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4490]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1921]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[3]) DUMMY_DER */));
  threadData->lastEquationSolved = 2805;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30135(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30139(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30143(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30094(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30091(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30087(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30093(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30095(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30092(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30098(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30101(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30097(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30100(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30096(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30099(DATA *data, threadData_t *threadData);


/*
equation index: 2882
type: LINEAR

<var>chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.w</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2882(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2882};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[data->simulationInfo->realVarsIndex[9196]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.w DUMMY_STATE */) };
  infoStreamPrint(OMC_LOG_DT, 0, "Solving linear system 2882 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);

  retValue = solve_linear_system(data, threadData, 2, &aux_x[0]);

  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,2882};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 2882 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9196]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.w DUMMY_STATE */) = aux_x[0];

  threadData->lastEquationSolved = 2882;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30242(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30206(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30208(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30245(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30244(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30248(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30246(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30243(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30247(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30253(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30254(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30251(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30252(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30249(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30250(DATA *data, threadData_t *threadData);


/*
equation index: 2898
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.v_0[1] = chassis.detailedChassis.rrAxleDW.rightLCABody.v_0[1] + chassis.detailedChassis.frameRR.R.T[1,1] * (chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[2] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3] - chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[3] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2]) + chassis.detailedChassis.frameRR.R.T[2,1] * (chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[3] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1] - chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[1] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3]) + chassis.detailedChassis.frameRR.R.T[3,1] * (chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[1] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2] - chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[2] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2898(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2898};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9027]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.v_0[1] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8206]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.v_0[1] DUMMY_STATE */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6113]] /* chassis.detailedChassis.frameRR.R.T[1,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9031]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4819]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9032]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4818]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6116]] /* chassis.detailedChassis.frameRR.R.T[2,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9032]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4817]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9030]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4819]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6119]] /* chassis.detailedChassis.frameRR.R.T[3,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9030]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4818]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9031]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4817]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1] PARAM */))));
  threadData->lastEquationSolved = 2898;
}

/*
equation index: 2899
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightUnsprungBody.frame_a.r_0[1] = chassis.detailedChassis.rrAxleDW.rightUnsprungBody.v_0[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2899(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2899};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1813]] /* der(chassis.detailedChassis.rrAxleDW.rightUnsprungBody.frame_a.r_0[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9027]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.v_0[1] DUMMY_STATE */);
  threadData->lastEquationSolved = 2899;
}

/*
equation index: 2900
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.v_g[1] = chassis.detailedChassis.rrAxleDW.rightUnsprungBody.v_0[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2900(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2900};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8678]] /* chassis.detailedChassis.rrAxleDW.rightTire.v_g[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9027]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.v_0[1] DUMMY_STATE */);
  threadData->lastEquationSolved = 2900;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30225(DATA *data, threadData_t *threadData);


/*
equation index: 2902
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.v_0[2] = chassis.detailedChassis.rrAxleDW.rightLCABody.v_0[2] + chassis.detailedChassis.frameRR.R.T[1,2] * (chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[2] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3] - chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[3] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2]) + chassis.detailedChassis.frameRR.R.T[2,2] * (chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[3] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1] - chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[1] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3]) + chassis.detailedChassis.frameRR.R.T[3,2] * (chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[1] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2] - chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[2] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2902(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2902};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9028]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.v_0[2] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8207]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.v_0[2] DUMMY_STATE */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6114]] /* chassis.detailedChassis.frameRR.R.T[1,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9031]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4819]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9032]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4818]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6117]] /* chassis.detailedChassis.frameRR.R.T[2,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9032]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4817]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9030]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4819]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6120]] /* chassis.detailedChassis.frameRR.R.T[3,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9030]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4818]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9031]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4817]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1] PARAM */))));
  threadData->lastEquationSolved = 2902;
}

/*
equation index: 2903
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightUnsprungBody.frame_a.r_0[2] = chassis.detailedChassis.rrAxleDW.rightUnsprungBody.v_0[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2903(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2903};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1814]] /* der(chassis.detailedChassis.rrAxleDW.rightUnsprungBody.frame_a.r_0[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9028]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.v_0[2] DUMMY_STATE */);
  threadData->lastEquationSolved = 2903;
}

/*
equation index: 2904
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.v_g[2] = chassis.detailedChassis.rrAxleDW.rightUnsprungBody.v_0[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2904(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2904};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8679]] /* chassis.detailedChassis.rrAxleDW.rightTire.v_g[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9028]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.v_0[2] DUMMY_STATE */);
  threadData->lastEquationSolved = 2904;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30222(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30218(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30221(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30220(DATA *data, threadData_t *threadData);


/*
equation index: 2909
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.slipModel.Vsx = chassis.detailedChassis.rrAxleDW.rightTire.slipModel.Vx - chassis.detailedChassis.rrAxleDW.rightTire.slipModel.R0 * chassis.detailedChassis.rrAxleDW.rightTire.slipModel.omega
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2909(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2909};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8664]] /* chassis.detailedChassis.rrAxleDW.rightTire.slipModel.Vsx variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8665]] /* chassis.detailedChassis.rrAxleDW.rightTire.slipModel.Vx variable */) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8663]] /* chassis.detailedChassis.rrAxleDW.rightTire.slipModel.R0 variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8673]] /* chassis.detailedChassis.rrAxleDW.rightTire.slipModel.omega variable */)));
  threadData->lastEquationSolved = 2909;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30216(DATA *data, threadData_t *threadData);


/*
equation index: 2911
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.v_0[3] = chassis.detailedChassis.rrAxleDW.rightLCABody.v_0[3] + chassis.detailedChassis.frameRR.R.T[1,3] * (chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[2] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3] - chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[3] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2]) + chassis.detailedChassis.frameRR.R.T[2,3] * (chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[3] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1] - chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[1] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3]) + chassis.detailedChassis.frameRR.R.T[3,3] * (chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[1] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2] - chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[2] * chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2911(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2911};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9029]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.v_0[3] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8208]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.v_0[3] DUMMY_STATE */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6115]] /* chassis.detailedChassis.frameRR.R.T[1,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9031]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4819]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9032]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4818]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6118]] /* chassis.detailedChassis.frameRR.R.T[2,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9032]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4817]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9030]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4819]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6121]] /* chassis.detailedChassis.frameRR.R.T[3,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9030]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4818]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9031]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4817]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1] PARAM */))));
  threadData->lastEquationSolved = 2911;
}

/*
equation index: 2912
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightUnsprungBody.frame_a.r_0[3] = chassis.detailedChassis.rrAxleDW.rightUnsprungBody.v_0[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2912(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2912};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1815]] /* der(chassis.detailedChassis.rrAxleDW.rightUnsprungBody.frame_a.r_0[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9029]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.v_0[3] DUMMY_STATE */);
  threadData->lastEquationSolved = 2912;
}

/*
equation index: 2913
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.v_cp[3] = chassis.detailedChassis.rrAxleDW.rightUnsprungBody.v_0[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2913(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2913};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8677]] /* chassis.detailedChassis.rrAxleDW.rightTire.v_cp[3] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9029]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.v_0[3] DUMMY_STATE */);
  threadData->lastEquationSolved = 2913;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30212(DATA *data, threadData_t *threadData);


/*
equation index: 2915
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frameRR.r_0[3] = chassis.detailedChassis.rrAxleDW.rightTire.v_cp[3] + chassis.detailedChassis.frameRR.R.T[1,3] * (-chassis.detailedChassis.frameRR.R.w[2]) * chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.s + chassis.detailedChassis.frameRR.R.T[2,3] * chassis.detailedChassis.frameRR.R.w[1] * chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.s
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2915(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2915};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1451]] /* der(chassis.detailedChassis.frameRR.r_0[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8677]] /* chassis.detailedChassis.rrAxleDW.rightTire.v_cp[3] variable */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6115]] /* chassis.detailedChassis.frameRR.R.T[1,3] DUMMY_STATE */)) * (((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6123]] /* chassis.detailedChassis.frameRR.R.w[2] variable */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8739]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.s DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6118]] /* chassis.detailedChassis.frameRR.R.T[2,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6122]] /* chassis.detailedChassis.frameRR.R.w[1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8739]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.s DUMMY_STATE */)));
  threadData->lastEquationSolved = 2915;
}

/*
equation index: 2916
type: SIMPLE_ASSIGN
$DER.chassis.ground_4.r_rel_z = $DER.chassis.detailedChassis.frameRR.r_0[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2916(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2916};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2020]] /* der(chassis.ground_4.r_rel_z) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1451]] /* der(chassis.detailedChassis.frameRR.r_0[3]) DUMMY_DER */);
  threadData->lastEquationSolved = 2916;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30227(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30228(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30229(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30230(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30231(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31267(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30232(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30233(DATA *data, threadData_t *threadData);


/*
equation index: 2925
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.f = chassis.detailedChassis.rrAxleDW.rightTire.constantZero.k + chassis.ground_4.f_z
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2925(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2925};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8736]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.f variable */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3962]] /* chassis.detailedChassis.rrAxleDW.rightTire.constantZero.k PARAM */) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10107]] /* chassis.ground_4.f_z variable */);
  threadData->lastEquationSolved = 2925;
}

/*
equation index: 2926
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.toHub.frame_b.f[3] = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.f - chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.frame_a.f[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2926(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2926};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8748]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.toHub.frame_b.f[3] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8736]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.f variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8706]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.frame_a.f[3] variable */);
  threadData->lastEquationSolved = 2926;
}

/*
equation index: 2927
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.chassisFrame.f[3] = -chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.toHub.frame_b.f[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2927(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2927};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8593]] /* chassis.detailedChassis.rrAxleDW.rightTire.chassisFrame.f[3] variable */) = (-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8748]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.toHub.frame_b.f[3] variable */));
  threadData->lastEquationSolved = 2927;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30207(DATA *data, threadData_t *threadData);


/*
equation index: 2929
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.w[3] = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,1] * chassis.detailedChassis.frameRR.R.w[1] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,2] * chassis.detailedChassis.frameRR.R.w[2] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,3] * chassis.detailedChassis.frameRR.R.w[3] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.w[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2929(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2929};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8790]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.w[3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8688]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6122]] /* chassis.detailedChassis.frameRR.R.w[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8689]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6123]] /* chassis.detailedChassis.frameRR.R.w[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8690]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6124]] /* chassis.detailedChassis.frameRR.R.w[3] variable */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8693]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.w[3] variable */);
  threadData->lastEquationSolved = 2929;
}

/*
equation index: 2930
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.w[2] = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,1] * chassis.detailedChassis.frameRR.R.w[1] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,2] * chassis.detailedChassis.frameRR.R.w[2] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,3] * chassis.detailedChassis.frameRR.R.w[3] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.w[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2930(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2930};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8789]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.w[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8685]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6122]] /* chassis.detailedChassis.frameRR.R.w[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8686]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6123]] /* chassis.detailedChassis.frameRR.R.w[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8687]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6124]] /* chassis.detailedChassis.frameRR.R.w[3] variable */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8692]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.w[2] variable */);
  threadData->lastEquationSolved = 2930;
}

/*
equation index: 2931
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.w[1] = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,1] * chassis.detailedChassis.frameRR.R.w[1] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,2] * chassis.detailedChassis.frameRR.R.w[2] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,3] * chassis.detailedChassis.frameRR.R.w[3] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.w[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2931(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2931};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8788]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.w[1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8682]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6122]] /* chassis.detailedChassis.frameRR.R.w[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8683]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6123]] /* chassis.detailedChassis.frameRR.R.w[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8684]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6124]] /* chassis.detailedChassis.frameRR.R.w[3] variable */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8691]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.w[1] variable */);
  threadData->lastEquationSolved = 2931;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29911(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29919(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29916(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29912(DATA *data, threadData_t *threadData);


/*
equation index: 2936
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,1] = (1.0 - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] ^ 2.0) * (-sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2936(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2936};
  modelica_real tmp685;
  tmp685 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1869]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,1]) DUMMY_DER */) = (1.0 - ((tmp685 * tmp685))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)));
  threadData->lastEquationSolved = 2936;
}

/*
equation index: 2937
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * (-sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2937(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2937};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1870]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,2]) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)))));
  threadData->lastEquationSolved = 2937;
}

/*
equation index: 2938
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,3] = (-chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1]) * (-sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2938(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2938};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1871]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,3]) DUMMY_DER */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */))));
  threadData->lastEquationSolved = 2938;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29902(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29901(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29900(DATA *data, threadData_t *threadData);


/*
equation index: 2942
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,1] = (-chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2]) * (-sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2942(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2942};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1872]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,1]) DUMMY_DER */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */))));
  threadData->lastEquationSolved = 2942;
}

/*
equation index: 2943
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,2] = (1.0 - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] ^ 2.0) * (-sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2943(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2943};
  modelica_real tmp686;
  tmp686 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1873]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,2]) DUMMY_DER */) = (1.0 - ((tmp686 * tmp686))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)));
  threadData->lastEquationSolved = 2943;
}

/*
equation index: 2944
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * (-sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2944(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2944};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1874]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,3]) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)))));
  threadData->lastEquationSolved = 2944;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29896(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29895(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29894(DATA *data, threadData_t *threadData);


/*
equation index: 2948
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * (-sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2948(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2948};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1875]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,1]) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)))));
  threadData->lastEquationSolved = 2948;
}

/*
equation index: 2949
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,2] = (-chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3]) * (-sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2949(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2949};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1876]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,2]) DUMMY_DER */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */))));
  threadData->lastEquationSolved = 2949;
}

/*
equation index: 2950
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,3] = (1.0 - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] ^ 2.0) * (-sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2950(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2950};
  modelica_real tmp687;
  tmp687 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1877]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,3]) DUMMY_DER */) = (1.0 - ((tmp687 * tmp687))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)));
  threadData->lastEquationSolved = 2950;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29890(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29889(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29888(DATA *data, threadData_t *threadData);


/*
equation index: 3015
type: LINEAR

<var>chassis.detailedChassis.rrAxleDW.rightBellcrank.revolute.w</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3015(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3015};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[data->simulationInfo->realVarsIndex[7937]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.revolute.w DUMMY_STATE */) };
  infoStreamPrint(OMC_LOG_DT, 0, "Solving linear system 3015 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);

  retValue = solve_linear_system(data, threadData, 3, &aux_x[0]);

  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,3015};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 3015 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7937]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.revolute.w DUMMY_STATE */) = aux_x[0];

  threadData->lastEquationSolved = 3015;
}

/*
equation index: 3016
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[1] = $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3016(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3016};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1776]] /* der(chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1769]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r[1]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8323]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8326]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8329]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */))));
  threadData->lastEquationSolved = 3016;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29987(DATA *data, threadData_t *threadData);


/*
equation index: 3018
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[2] = $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3018(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3018};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1777]] /* der(chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1770]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r[2]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8324]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8327]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8330]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */))));
  threadData->lastEquationSolved = 3018;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29984(DATA *data, threadData_t *threadData);


/*
equation index: 3020
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[3] = $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r[3] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3020(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3020};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1778]] /* der(chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1771]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r[3]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8325]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8328]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8331]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */))));
  threadData->lastEquationSolved = 3020;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29981(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29988(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29989(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29990(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29991(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29992(DATA *data, threadData_t *threadData);


/*
equation index: 3027
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fb = chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularSpring.combiTable1D.y[1] + chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularDamper.combiTable1D.y[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3027(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3027};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8403]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fb variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8385]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularSpring.combiTable1D.y[1] variable */) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8379]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularDamper.combiTable1D.y[1] variable */);
  threadData->lastEquationSolved = 3027;
}

/*
equation index: 3028
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightShock.frame_a.f[3] = (-chassis.detailedChassis.rrAxleFrame.R.T[3,2]) * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[2] * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fb - chassis.detailedChassis.rrAxleFrame.R.T[3,3] * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[3] * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fb - chassis.detailedChassis.rrAxleFrame.R.T[3,1] * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[1] * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fb
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3028(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3028};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9774]] /* chassis.detailedChassis.rrAxleDW.toRightShock.frame_a.f[3] variable */) = ((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9815]] /* chassis.detailedChassis.rrAxleFrame.R.T[3,2] DUMMY_STATE */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8400]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8403]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fb variable */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9816]] /* chassis.detailedChassis.rrAxleFrame.R.T[3,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8401]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8403]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fb variable */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9814]] /* chassis.detailedChassis.rrAxleFrame.R.T[3,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8399]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8403]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fb variable */))));
  threadData->lastEquationSolved = 3028;
}

/*
equation index: 3029
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightShock.frame_a.f[2] = (-chassis.detailedChassis.rrAxleFrame.R.T[2,2]) * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[2] * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fb - chassis.detailedChassis.rrAxleFrame.R.T[2,3] * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[3] * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fb - chassis.detailedChassis.rrAxleFrame.R.T[2,1] * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[1] * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fb
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3029(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3029};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9773]] /* chassis.detailedChassis.rrAxleDW.toRightShock.frame_a.f[2] variable */) = ((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9812]] /* chassis.detailedChassis.rrAxleFrame.R.T[2,2] DUMMY_STATE */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8400]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8403]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fb variable */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9813]] /* chassis.detailedChassis.rrAxleFrame.R.T[2,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8401]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8403]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fb variable */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9811]] /* chassis.detailedChassis.rrAxleFrame.R.T[2,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8399]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8403]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fb variable */))));
  threadData->lastEquationSolved = 3029;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29998(DATA *data, threadData_t *threadData);


/*
equation index: 3031
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightShock.frame_a.f[1] = (-chassis.detailedChassis.rrAxleFrame.R.T[1,2]) * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[2] * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fb - chassis.detailedChassis.rrAxleFrame.R.T[1,3] * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[3] * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fb - chassis.detailedChassis.rrAxleFrame.R.T[1,1] * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[1] * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fb
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3031(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3031};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9772]] /* chassis.detailedChassis.rrAxleDW.toRightShock.frame_a.f[1] variable */) = ((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9809]] /* chassis.detailedChassis.rrAxleFrame.R.T[1,2] DUMMY_STATE */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8400]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8403]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fb variable */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9810]] /* chassis.detailedChassis.rrAxleFrame.R.T[1,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8401]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8403]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fb variable */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9808]] /* chassis.detailedChassis.rrAxleFrame.R.T[1,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8399]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8403]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fb variable */))));
  threadData->lastEquationSolved = 3031;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29996(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29999(DATA *data, threadData_t *threadData);


/*
equation index: 3034
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fa = -chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fb
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3034(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3034};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8402]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fa variable */) = (-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8403]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fb variable */));
  threadData->lastEquationSolved = 3034;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30002(DATA *data, threadData_t *threadData);


/*
equation index: 3036
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightShockLinkage.frame_a.f[2] = (-chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2]) * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[2] * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fa - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[3] * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fa - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[1] * chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fa
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3036(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3036};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8391]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.frame_a.f[2] variable */) = ((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8327]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8400]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8402]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fa variable */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8328]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8401]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8402]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fa variable */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8326]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8399]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.e_rel_0[1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8402]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.fa variable */))));
  threadData->lastEquationSolved = 3036;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30000(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30004(DATA *data, threadData_t *threadData);


/*
equation index: 3039
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.vis.r[1] = $DER.chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3039(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3039};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1712]] /* der(chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.vis.r[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1776]] /* der(chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[1]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8323]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8326]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8329]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */))));
  threadData->lastEquationSolved = 3039;
}

/*
equation index: 3040
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.vis.r[2] = $DER.chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3040(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3040};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1713]] /* der(chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.vis.r[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1777]] /* der(chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[2]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8324]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8327]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8330]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */))));
  threadData->lastEquationSolved = 3040;
}

/*
equation index: 3041
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.vis.r[3] = $DER.chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[3] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3041(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3041};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1714]] /* der(chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.vis.r[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1778]] /* der(chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[3]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8325]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8328]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8331]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */))));
  threadData->lastEquationSolved = 3041;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30006(DATA *data, threadData_t *threadData);


/*
equation index: 3110
type: LINEAR

<var>chassis.detailedChassis.rrAxleDW.stabar.mountAxis.w</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3110(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3110};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[data->simulationInfo->realVarsIndex[9557]] /* chassis.detailedChassis.rrAxleDW.stabar.mountAxis.w DUMMY_STATE */) };
  infoStreamPrint(OMC_LOG_DT, 0, "Solving linear system 3110 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);

  retValue = solve_linear_system(data, threadData, 4, &aux_x[0]);

  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,3110};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 3110 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9557]] /* chassis.detailedChassis.rrAxleDW.stabar.mountAxis.w DUMMY_STATE */) = aux_x[0];

  threadData->lastEquationSolved = 3110;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30073(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30076(DATA *data, threadData_t *threadData);


/*
equation index: 3113
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.der_rRod_a_L[2] = (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] * $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] * $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] * $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[3] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[1]) / chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3113(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3113};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8244]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.der_rRod_a_L[2] variable */) = DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8326]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1751]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8327]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1752]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8328]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1753]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8284]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[3] variable */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8282]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[1] variable */))),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3854]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodLength PARAM */),"chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodLength",equationIndexes);
  threadData->lastEquationSolved = 3113;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30074(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30079(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30078(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30077(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30084(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30085(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30082(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30083(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30080(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30081(DATA *data, threadData_t *threadData);


/*
equation index: 3124
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodLength = 0.18537941992928988
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3124(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3124};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3413]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodLength PARAM */) = 0.18537941992928988;
  threadData->lastEquationSolved = 3124;
}

/*
equation index: 3125
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1Length = chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3125(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3125};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3417]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1Length PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3413]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodLength PARAM */);
  threadData->lastEquationSolved = 3125;
}

/*
equation index: 3126
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.lengthConstraint = chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1Length
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3126(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3126};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3386]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.lengthConstraint PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3417]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1Length PARAM */);
  threadData->lastEquationSolved = 3126;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30288(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30291(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30292(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30293(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30818(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30819(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30820(DATA *data, threadData_t *threadData);


/*
equation index: 3134
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.positiveBranch = BobLib.Experiments.Standards.VehicleSim.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.selectBranch(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.lengthConstraint, chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e, 0.017453292519943295 * (chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.phi_offset + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.phi_guess), chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_a, chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3134(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3134};
  real_array tmp688;
  real_array tmp689;
  real_array tmp690;
  real_array_create(&tmp688, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp689, ((modelica_real*)&((&data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7637]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] DUMMY_STATE */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp690, ((modelica_real*)&((&data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7640]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] variable */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  (data->simulationInfo->booleanParameter[data->simulationInfo->booleanParamsIndex[356]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.positiveBranch PARAM */) = omc_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_rrAxleDW_leftWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3386]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.lengthConstraint PARAM */), tmp688, (0.017453292519943295) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3391]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.phi_offset PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3390]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.phi_guess PARAM */)), tmp689, tmp690);
  threadData->lastEquationSolved = 3134;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30295(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30294(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30296(DATA *data, threadData_t *threadData);


/*
equation index: 3138
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,1] = chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] ^ 2.0 + (1.0 - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] ^ 2.0) * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3138(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3138};
  modelica_real tmp691;
  modelica_real tmp692;
  tmp691 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */);
  tmp692 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7598]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,1] DUMMY_STATE */) = (tmp691 * tmp691) + (1.0 - ((tmp692 * tmp692))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 3138;
}

/*
equation index: 3139
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,2] = (chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3139(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3139};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7599]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,2] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3384]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3385]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 3139;
}

/*
equation index: 3140
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,3] = (chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3140(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3140};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7600]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,3] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3385]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3384]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))));
  threadData->lastEquationSolved = 3140;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30321(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30317(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30314(DATA *data, threadData_t *threadData);


/*
equation index: 3144
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,1] = (chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3144(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3144};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7601]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,1] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3384]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3384]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3385]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))));
  threadData->lastEquationSolved = 3144;
}

/*
equation index: 3145
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,2] = chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] ^ 2.0 + (1.0 - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] ^ 2.0) * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3145(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3145};
  modelica_real tmp693;
  modelica_real tmp694;
  tmp693 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3384]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */);
  tmp694 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3384]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7602]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,2] DUMMY_STATE */) = (tmp693 * tmp693) + (1.0 - ((tmp694 * tmp694))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 3145;
}

/*
equation index: 3146
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,3] = (chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3146(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3146};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7603]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,3] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3384]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3384]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3385]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 3146;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30310(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30309(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30308(DATA *data, threadData_t *threadData);


/*
equation index: 3150
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,1] = (chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3150(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3150};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7604]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,1] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3385]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3385]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3384]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 3150;
}

/*
equation index: 3151
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,2] = (chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3151(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3151};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7605]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,2] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3385]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3385]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3384]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))));
  threadData->lastEquationSolved = 3151;
}

/*
equation index: 3152
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,3] = chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] ^ 2.0 + (1.0 - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] ^ 2.0) * cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3152(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3152};
  modelica_real tmp695;
  modelica_real tmp696;
  tmp695 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3385]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */);
  tmp696 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3385]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7606]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,3] DUMMY_STATE */) = (tmp695 * tmp695) + (1.0 - ((tmp696 * tmp696))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 3152;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30304(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30322(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30323(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30334(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30303(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30318(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30319(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30320(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30302(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30315(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30654(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30657(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30658(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30655(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30656(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30669(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30670(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30671(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30672(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30673(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30674(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30675(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30676(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30679(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30678(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30677(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30680(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30683(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30682(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30681(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30690(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30692(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30691(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30695(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30687(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30689(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30688(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30694(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30684(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30686(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30685(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30693(DATA *data, threadData_t *threadData);


void BobLib_Experiments_Standards_VehicleSim_eqFunction_3195(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3196(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3197(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3198(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3199(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3200(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3201(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3202(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3203(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3204(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3205(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3206(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3207(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3208(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3209(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3210(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3211(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3212(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3213(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3214(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3215(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3216(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3217(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3218(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3219(DATA*, threadData_t*);
/*
equation index: 3247
indexNonlinear: 5
type: NONLINEAR

vars: {chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.steeringAxis.phi}
eqns: {3195, 3196, 3197, 3198, 3199, 3200, 3201, 3202, 3203, 3204, 3205, 3206, 3207, 3208, 3209, 3210, 3211, 3212, 3213, 3214, 3215, 3216, 3217, 3218, 3219}
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3247(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3247};
  int retValue;
  infoStreamPrint(OMC_LOG_DT, 0, "Solving nonlinear system 3247 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
  /* get old value */
  data->simulationInfo->nonlinearSystemData[5].nlsxOld[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7440]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.steeringAxis.phi DUMMY_STATE */);
  retValue = solve_nonlinear_system(data, threadData, 5);
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,3247};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving non-linear system 3247 failed at time=%.15g.\nFor more information please use -lv LOG_NLS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7440]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.steeringAxis.phi DUMMY_STATE */) = data->simulationInfo->nonlinearSystemData[5].nlsx[0];
  threadData->lastEquationSolved = 3247;
}

/*
equation index: 3248
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.e_xw[1] = chassis.detailedChassis.frameRL.R.T[1,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3248(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3248};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6840]] /* chassis.detailedChassis.rrAxleDW.leftTire.e_xw[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6095]] /* chassis.detailedChassis.frameRL.R.T[1,1] DUMMY_STATE */);
  threadData->lastEquationSolved = 3248;
}

/*
equation index: 3249
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.e_xw[2] = chassis.detailedChassis.frameRL.R.T[1,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3249(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3249};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6841]] /* chassis.detailedChassis.rrAxleDW.leftTire.e_xw[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6096]] /* chassis.detailedChassis.frameRL.R.T[1,2] DUMMY_STATE */);
  threadData->lastEquationSolved = 3249;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30764(DATA *data, threadData_t *threadData);


/*
equation index: 3251
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.e_xw[3] = chassis.detailedChassis.frameRL.R.T[1,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3251(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3251};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6842]] /* chassis.detailedChassis.rrAxleDW.leftTire.e_xw[3] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6097]] /* chassis.detailedChassis.frameRL.R.T[1,3] DUMMY_STATE */);
  threadData->lastEquationSolved = 3251;
}

/*
equation index: 3252
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.e_yw[1] = chassis.detailedChassis.frameRL.R.T[2,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3252(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3252};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6846]] /* chassis.detailedChassis.rrAxleDW.leftTire.e_yw[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6098]] /* chassis.detailedChassis.frameRL.R.T[2,1] DUMMY_STATE */);
  threadData->lastEquationSolved = 3252;
}

/*
equation index: 3253
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.e_yw[2] = chassis.detailedChassis.frameRL.R.T[2,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3253(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3253};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6847]] /* chassis.detailedChassis.rrAxleDW.leftTire.e_yw[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6099]] /* chassis.detailedChassis.frameRL.R.T[2,2] DUMMY_STATE */);
  threadData->lastEquationSolved = 3253;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30756(DATA *data, threadData_t *threadData);


/*
equation index: 3255
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.e_yw[3] = chassis.detailedChassis.frameRL.R.T[2,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3255(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3255};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6848]] /* chassis.detailedChassis.rrAxleDW.leftTire.e_yw[3] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6100]] /* chassis.detailedChassis.frameRL.R.T[2,3] DUMMY_STATE */);
  threadData->lastEquationSolved = 3255;
}

/*
equation index: 3256
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.frame_a.r_0[1] = chassis.detailedChassis.rrAxleDW.leftLCABody.frame_a.r_0[1] + 0.005079999999999973 * chassis.detailedChassis.frameRL.R.T[1,1] + 0.02953077000000004 * chassis.detailedChassis.frameRL.R.T[2,1] + 0.08381999999999999 * chassis.detailedChassis.frameRL.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3256(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3256};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7238]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.frame_a.r_0[1] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6401]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.frame_a.r_0[1] DUMMY_STATE */) + (0.005079999999999973) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6095]] /* chassis.detailedChassis.frameRL.R.T[1,1] DUMMY_STATE */)) + (0.02953077000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6098]] /* chassis.detailedChassis.frameRL.R.T[2,1] DUMMY_STATE */)) + (0.08381999999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6101]] /* chassis.detailedChassis.frameRL.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 3256;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30763(DATA *data, threadData_t *threadData);


/*
equation index: 3258
type: SIMPLE_ASSIGN
chassis.detailedChassis.frameRL.r_0[1] = chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.wheelVelSensor.der1[1].u - chassis.detailedChassis.frameRL.R.T[3,1] * chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.prismatic_z.s
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3258(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3258};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6107]] /* chassis.detailedChassis.frameRL.r_0[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7027]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.wheelVelSensor.der1[1].u DUMMY_STATE */) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6101]] /* chassis.detailedChassis.frameRL.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6973]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.prismatic_z.s DUMMY_STATE */)));
  threadData->lastEquationSolved = 3258;
}

/*
equation index: 3259
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[3,1] = chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,1] * chassis.detailedChassis.frameRL.R.T[1,1] + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,2] * chassis.detailedChassis.frameRL.R.T[2,1] + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,3] * chassis.detailedChassis.frameRL.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3259(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3259};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7020]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[3,1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6922]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6095]] /* chassis.detailedChassis.frameRL.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6923]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6098]] /* chassis.detailedChassis.frameRL.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6924]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6101]] /* chassis.detailedChassis.frameRL.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 3259;
}

/*
equation index: 3260
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[2,1] = chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,1] * chassis.detailedChassis.frameRL.R.T[1,1] + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,2] * chassis.detailedChassis.frameRL.R.T[2,1] + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,3] * chassis.detailedChassis.frameRL.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3260(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3260};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7018]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[2,1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6919]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6095]] /* chassis.detailedChassis.frameRL.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6920]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6098]] /* chassis.detailedChassis.frameRL.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6921]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6101]] /* chassis.detailedChassis.frameRL.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 3260;
}

/*
equation index: 3261
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.e_spin[1] = chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[2,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3261(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3261};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6834]] /* chassis.detailedChassis.rrAxleDW.leftTire.e_spin[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7018]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[2,1] variable */);
  threadData->lastEquationSolved = 3261;
}

/*
equation index: 3262
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[1,1] = chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,1] * chassis.detailedChassis.frameRL.R.T[1,1] + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,2] * chassis.detailedChassis.frameRL.R.T[2,1] + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,3] * chassis.detailedChassis.frameRL.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3262(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3262};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7016]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[1,1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6916]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6095]] /* chassis.detailedChassis.frameRL.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6917]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6098]] /* chassis.detailedChassis.frameRL.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6918]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6101]] /* chassis.detailedChassis.frameRL.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 3262;
}

/*
equation index: 3263
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.frame_a.r_0[3] = chassis.detailedChassis.rrAxleDW.leftLCABody.frame_a.r_0[3] + 0.005079999999999973 * chassis.detailedChassis.frameRL.R.T[1,3] + 0.02953077000000004 * chassis.detailedChassis.frameRL.R.T[2,3] + 0.08381999999999999 * chassis.detailedChassis.frameRL.R.T[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3263(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3263};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7240]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.frame_a.r_0[3] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6403]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.frame_a.r_0[3] DUMMY_STATE */) + (0.005079999999999973) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6097]] /* chassis.detailedChassis.frameRL.R.T[1,3] DUMMY_STATE */)) + (0.02953077000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6100]] /* chassis.detailedChassis.frameRL.R.T[2,3] DUMMY_STATE */)) + (0.08381999999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6103]] /* chassis.detailedChassis.frameRL.R.T[3,3] DUMMY_STATE */));
  threadData->lastEquationSolved = 3263;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30801(DATA *data, threadData_t *threadData);


/*
equation index: 3265
type: SIMPLE_ASSIGN
chassis.detailedChassis.frameRL.r_0[3] = chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.wheelVelSensor.der1[3].u - chassis.detailedChassis.frameRL.R.T[3,3] * chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.prismatic_z.s
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3265(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3265};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6109]] /* chassis.detailedChassis.frameRL.r_0[3] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7029]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.wheelVelSensor.der1[3].u DUMMY_STATE */) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6103]] /* chassis.detailedChassis.frameRL.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6973]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.prismatic_z.s DUMMY_STATE */)));
  threadData->lastEquationSolved = 3265;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30799(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30800(DATA *data, threadData_t *threadData);


/*
equation index: 3268
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.e_zw[3] = chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,1] * chassis.detailedChassis.frameRL.R.T[1,3] + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,2] * chassis.detailedChassis.frameRL.R.T[2,3] + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,3] * chassis.detailedChassis.frameRL.R.T[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3268(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3268};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6851]] /* chassis.detailedChassis.rrAxleDW.leftTire.e_zw[3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6922]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6097]] /* chassis.detailedChassis.frameRL.R.T[1,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6923]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6100]] /* chassis.detailedChassis.frameRL.R.T[2,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6924]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6103]] /* chassis.detailedChassis.frameRL.R.T[3,3] DUMMY_STATE */));
  threadData->lastEquationSolved = 3268;
}

/*
equation index: 3269
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.e_zw[2] = chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,1] * chassis.detailedChassis.frameRL.R.T[1,3] + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,2] * chassis.detailedChassis.frameRL.R.T[2,3] + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,3] * chassis.detailedChassis.frameRL.R.T[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3269(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3269};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6850]] /* chassis.detailedChassis.rrAxleDW.leftTire.e_zw[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6919]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6097]] /* chassis.detailedChassis.frameRL.R.T[1,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6920]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6100]] /* chassis.detailedChassis.frameRL.R.T[2,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6921]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6103]] /* chassis.detailedChassis.frameRL.R.T[3,3] DUMMY_STATE */));
  threadData->lastEquationSolved = 3269;
}

/*
equation index: 3270
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.gamma = asin(max(-1.0, min(1.0, chassis.detailedChassis.rrAxleDW.leftTire.e_zw[2])))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3270(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3270};
  modelica_real tmp697;
  tmp697 = fmax(-1.0,fmin(1.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6850]] /* chassis.detailedChassis.rrAxleDW.leftTire.e_zw[2] variable */)));
  if(!(tmp697 >= -1.0 && tmp697 <= 1.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of asin(max(-1.0, min(1.0, chassis.detailedChassis.rrAxleDW.leftTire.e_zw[2]))) outside the domain -1.0 <= %g <= 1.0", tmp697);
    }
  }
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6891]] /* chassis.detailedChassis.rrAxleDW.leftTire.gamma variable */) = asin(tmp697);
  threadData->lastEquationSolved = 3270;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31318(DATA *data, threadData_t *threadData);


/*
equation index: 3272
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.e_spin[3] = chassis.detailedChassis.rrAxleDW.leftTire.e_zw[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3272(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3272};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6836]] /* chassis.detailedChassis.rrAxleDW.leftTire.e_spin[3] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6850]] /* chassis.detailedChassis.rrAxleDW.leftTire.e_zw[2] variable */);
  threadData->lastEquationSolved = 3272;
}

/*
equation index: 3273
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.e_zw[1] = chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,1] * chassis.detailedChassis.frameRL.R.T[1,3] + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,2] * chassis.detailedChassis.frameRL.R.T[2,3] + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,3] * chassis.detailedChassis.frameRL.R.T[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3273(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3273};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6849]] /* chassis.detailedChassis.rrAxleDW.leftTire.e_zw[1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6916]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6097]] /* chassis.detailedChassis.frameRL.R.T[1,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6917]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6100]] /* chassis.detailedChassis.frameRL.R.T[2,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6918]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6103]] /* chassis.detailedChassis.frameRL.R.T[3,3] DUMMY_STATE */));
  threadData->lastEquationSolved = 3273;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30766(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30767(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30768(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30769(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30770(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30771(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30773(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30772(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30774(DATA *data, threadData_t *threadData);


/*
equation index: 3283
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieRod.rod.f_b_a1[1] = chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e3_a[1] * (chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_a[2] * chassis.detailedChassis.rrAxleDW.leftTieRod.rod.t_ia_a[2] + chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_a[3] * chassis.detailedChassis.rrAxleDW.leftTieRod.rod.t_ia_a[3]) / chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3283(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3283};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6728]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.f_b_a1[1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6719]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e3_a[1] variable */)) * (DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6717]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_a[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6813]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.t_ia_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6718]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_a[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6814]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.t_ia_a[3] variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2870]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodLength PARAM */),"chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodLength",equationIndexes));
  threadData->lastEquationSolved = 3283;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30775(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30776(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30793(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30789(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30785(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30781(DATA *data, threadData_t *threadData);


/*
equation index: 3290
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieRod.rod.f_b_a1[3] = chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e3_a[3] * (chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_a[2] * chassis.detailedChassis.rrAxleDW.leftTieRod.rod.t_ia_a[2] + chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_a[3] * chassis.detailedChassis.rrAxleDW.leftTieRod.rod.t_ia_a[3]) / chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodLength - chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_a[3] * chassis.detailedChassis.rrAxleDW.leftTieRod.rod.t_ia_a[1] / (chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e3_a[1] * chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodLength)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3290(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3290};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6730]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.f_b_a1[3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6721]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e3_a[3] variable */)) * (DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6717]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_a[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6813]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.t_ia_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6718]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_a[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6814]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.t_ia_a[3] variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2870]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodLength PARAM */),"chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodLength",equationIndexes)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6718]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_a[3] variable */)) * (DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6812]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.t_ia_a[1] variable */),((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6719]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e3_a[1] variable */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2870]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodLength PARAM */)),"chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e3_a[1] * chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodLength",equationIndexes)));
  threadData->lastEquationSolved = 3290;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30784(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30783(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30782(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30777(DATA *data, threadData_t *threadData);


/*
equation index: 3295
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieRod.rod.f_b_a1[2] = chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e3_a[2] * (chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_a[2] * chassis.detailedChassis.rrAxleDW.leftTieRod.rod.t_ia_a[2] + chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_a[3] * chassis.detailedChassis.rrAxleDW.leftTieRod.rod.t_ia_a[3]) / chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodLength - chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_a[2] * chassis.detailedChassis.rrAxleDW.leftTieRod.rod.t_ia_a[1] / (chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e3_a[1] * chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodLength)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3295(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3295};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6729]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.f_b_a1[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6720]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e3_a[2] variable */)) * (DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6717]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_a[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6813]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.t_ia_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6718]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_a[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6814]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.t_ia_a[3] variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2870]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodLength PARAM */),"chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodLength",equationIndexes)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6717]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_a[2] variable */)) * (DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6812]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.t_ia_a[1] variable */),((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6719]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e3_a[1] variable */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2870]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodLength PARAM */)),"chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e3_a[1] * chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodLength",equationIndexes)));
  threadData->lastEquationSolved = 3295;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30780(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30796(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30795(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30794(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30779(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30792(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30791(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30790(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30778(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30788(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30787(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30786(DATA *data, threadData_t *threadData);


/*
equation index: 3308
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.frame_a.r_0[2] = chassis.detailedChassis.rrAxleDW.leftLCABody.frame_a.r_0[2] + 0.005079999999999973 * chassis.detailedChassis.frameRL.R.T[1,2] + 0.02953077000000004 * chassis.detailedChassis.frameRL.R.T[2,2] + 0.08381999999999999 * chassis.detailedChassis.frameRL.R.T[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3308(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3308};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7239]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.frame_a.r_0[2] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6402]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.frame_a.r_0[2] DUMMY_STATE */) + (0.005079999999999973) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6096]] /* chassis.detailedChassis.frameRL.R.T[1,2] DUMMY_STATE */)) + (0.02953077000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6099]] /* chassis.detailedChassis.frameRL.R.T[2,2] DUMMY_STATE */)) + (0.08381999999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6102]] /* chassis.detailedChassis.frameRL.R.T[3,2] DUMMY_STATE */));
  threadData->lastEquationSolved = 3308;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30759(DATA *data, threadData_t *threadData);


/*
equation index: 3310
type: SIMPLE_ASSIGN
chassis.detailedChassis.frameRL.r_0[2] = chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.wheelVelSensor.der1[2].u - chassis.detailedChassis.frameRL.R.T[3,2] * chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.prismatic_z.s
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3310(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3310};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6108]] /* chassis.detailedChassis.frameRL.r_0[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7028]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.wheelVelSensor.der1[2].u DUMMY_STATE */) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6102]] /* chassis.detailedChassis.frameRL.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6973]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.prismatic_z.s DUMMY_STATE */)));
  threadData->lastEquationSolved = 3310;
}

/*
equation index: 3311
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[3,2] = chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,1] * chassis.detailedChassis.frameRL.R.T[1,2] + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,2] * chassis.detailedChassis.frameRL.R.T[2,2] + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,3] * chassis.detailedChassis.frameRL.R.T[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3311(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3311};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7021]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[3,2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6922]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6096]] /* chassis.detailedChassis.frameRL.R.T[1,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6923]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6099]] /* chassis.detailedChassis.frameRL.R.T[2,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6924]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6102]] /* chassis.detailedChassis.frameRL.R.T[3,2] DUMMY_STATE */));
  threadData->lastEquationSolved = 3311;
}

/*
equation index: 3312
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[2,2] = chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,1] * chassis.detailedChassis.frameRL.R.T[1,2] + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,2] * chassis.detailedChassis.frameRL.R.T[2,2] + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,3] * chassis.detailedChassis.frameRL.R.T[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3312(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3312};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7019]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[2,2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6919]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6096]] /* chassis.detailedChassis.frameRL.R.T[1,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6920]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6099]] /* chassis.detailedChassis.frameRL.R.T[2,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6921]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6102]] /* chassis.detailedChassis.frameRL.R.T[3,2] DUMMY_STATE */));
  threadData->lastEquationSolved = 3312;
}

/*
equation index: 3313
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.e_spin[2] = chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[2,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3313(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3313};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6835]] /* chassis.detailedChassis.rrAxleDW.leftTire.e_spin[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7019]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[2,2] variable */);
  threadData->lastEquationSolved = 3313;
}

/*
equation index: 3314
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[1,2] = chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,1] * chassis.detailedChassis.frameRL.R.T[1,2] + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,2] * chassis.detailedChassis.frameRL.R.T[2,2] + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,3] * chassis.detailedChassis.frameRL.R.T[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3314(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3314};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7017]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[1,2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6916]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6096]] /* chassis.detailedChassis.frameRL.R.T[1,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6917]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6099]] /* chassis.detailedChassis.frameRL.R.T[2,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6918]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6102]] /* chassis.detailedChassis.frameRL.R.T[3,2] DUMMY_STATE */));
  threadData->lastEquationSolved = 3314;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30328(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30324(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30327(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30326(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30325(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30333(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30329(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30332(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30331(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30330(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30316(DATA *data, threadData_t *threadData);


void BobLib_Experiments_Standards_VehicleSim_eqFunction_3326(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3327(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3328(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3329(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3330(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3331(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3332(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3333(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3334(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3335(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3336(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3337(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3338(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3339(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3340(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3341(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3342(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3343(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3344(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3345(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3346(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3347(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3348(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3349(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3350(DATA*, threadData_t*);
/*
equation index: 3378
indexNonlinear: 6
type: NONLINEAR

vars: {chassis.detailedChassis.rrAxleDW.leftBellcrank.revolute.phi}
eqns: {3326, 3327, 3328, 3329, 3330, 3331, 3332, 3333, 3334, 3335, 3336, 3337, 3338, 3339, 3340, 3341, 3342, 3343, 3344, 3345, 3346, 3347, 3348, 3349, 3350}
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3378(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3378};
  int retValue;
  infoStreamPrint(OMC_LOG_DT, 0, "Solving nonlinear system 3378 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
  /* get old value */
  data->simulationInfo->nonlinearSystemData[6].nlsxOld[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6168]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.revolute.phi DUMMY_STATE */);
  retValue = solve_nonlinear_system(data, threadData, 6);
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,3378};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving non-linear system 3378 failed at time=%.15g.\nFor more information please use -lv LOG_NLS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6168]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.revolute.phi DUMMY_STATE */) = data->simulationInfo->nonlinearSystemData[6].nlsx[0];
  threadData->lastEquationSolved = 3378;
}

/*
equation index: 3379
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.widthDirection[1] = chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3379(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3379};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6669]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.widthDirection[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6563]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */);
  threadData->lastEquationSolved = 3379;
}

/*
equation index: 3380
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.widthDirection[2] = chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3380(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3380};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6670]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.widthDirection[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6564]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */);
  threadData->lastEquationSolved = 3380;
}

/*
equation index: 3381
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.widthDirection[3] = chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3381(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3381};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6671]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.widthDirection[3] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6565]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */);
  threadData->lastEquationSolved = 3381;
}

/*
equation index: 3382
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[1] = chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.r[1] + (-0.025337289999999957) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] + 0.009399680000000021 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] + 0.056759840000000006 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3382(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3382};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6663]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[1] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6603]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.r[1] DUMMY_STATE */) + (-0.025337289999999957) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6560]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) + (0.009399680000000021) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6563]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) + (0.056759840000000006) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6566]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 3382;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30401(DATA *data, threadData_t *threadData);


/*
equation index: 3384
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.vis.r[1] = chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[1] + 0.02454310999999998 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] + (-0.05079721000000004) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] + (-0.018531649999999997) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3384(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3384};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6257]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.vis.r[1] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6663]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[1] DUMMY_STATE */) + (0.02454310999999998) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6560]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) + (-0.05079721000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6563]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) + (-0.018531649999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6566]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 3384;
}

/*
equation index: 3385
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[2] = chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.r[2] + (-0.025337289999999957) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] + 0.009399680000000021 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] + 0.056759840000000006 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3385(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3385};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6664]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[2] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6604]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.r[2] DUMMY_STATE */) + (-0.025337289999999957) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6561]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) + (0.009399680000000021) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6564]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) + (0.056759840000000006) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6567]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */));
  threadData->lastEquationSolved = 3385;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30393(DATA *data, threadData_t *threadData);


/*
equation index: 3387
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.vis.r[2] = chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[2] + 0.02454310999999998 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] + (-0.05079721000000004) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] + (-0.018531649999999997) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3387(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3387};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6258]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.vis.r[2] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6664]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[2] DUMMY_STATE */) + (0.02454310999999998) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6561]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) + (-0.05079721000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6564]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) + (-0.018531649999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6567]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */));
  threadData->lastEquationSolved = 3387;
}

/*
equation index: 3388
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[3] = chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.r[3] + (-0.025337289999999957) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] + 0.009399680000000021 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] + 0.056759840000000006 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3388(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3388};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6665]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[3] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6605]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.r[3] DUMMY_STATE */) + (-0.025337289999999957) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6562]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) + (0.009399680000000021) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6565]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) + (0.056759840000000006) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6568]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */));
  threadData->lastEquationSolved = 3388;
}

/*
equation index: 3389
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.vis.r[3] = chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[3] + 0.02454310999999998 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] + (-0.05079721000000004) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] + (-0.018531649999999997) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3389(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3389};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6259]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.vis.r[3] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6665]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[3] DUMMY_STATE */) + (0.02454310999999998) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6562]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) + (-0.05079721000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6565]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) + (-0.018531649999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6568]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */));
  threadData->lastEquationSolved = 3389;
}

void BobLib_Experiments_Standards_VehicleSim_eqFunction_3390(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3391(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3392(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3393(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3394(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3395(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3396(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3397(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3398(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3399(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3400(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3401(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3402(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3403(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3404(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3405(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3406(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3407(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3408(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3409(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3410(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3411(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3412(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3413(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3414(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3415(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3416(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3417(DATA*, threadData_t*);
/*
equation index: 3448
indexNonlinear: 7
type: NONLINEAR

vars: {chassis.detailedChassis.rrAxleDW.stabar.stabarAxis.phi}
eqns: {3390, 3391, 3392, 3393, 3394, 3395, 3396, 3397, 3398, 3399, 3400, 3401, 3402, 3403, 3404, 3405, 3406, 3407, 3408, 3409, 3410, 3411, 3412, 3413, 3414, 3415, 3416, 3417}
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3448(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3448};
  int retValue;
  infoStreamPrint(OMC_LOG_DT, 0, "Solving nonlinear system 3448 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
  /* get old value */
  data->simulationInfo->nonlinearSystemData[7].nlsxOld[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9597]] /* chassis.detailedChassis.rrAxleDW.stabar.stabarAxis.phi DUMMY_STATE */);
  retValue = solve_nonlinear_system(data, threadData, 7);
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,3448};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving non-linear system 3448 failed at time=%.15g.\nFor more information please use -lv LOG_NLS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9597]] /* chassis.detailedChassis.rrAxleDW.stabar.stabarAxis.phi DUMMY_STATE */) = data->simulationInfo->nonlinearSystemData[7].nlsx[0];
  threadData->lastEquationSolved = 3448;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30476(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30477(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30478(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30479(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30480(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30481(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30482(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30483(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30484(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30485(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30486(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30487(DATA *data, threadData_t *threadData);


/*
equation index: 3479
type: LINEAR

<var>chassis.detailedChassis.rrAxleDW.leftDroplink.f_rod</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3479(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3479};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[data->simulationInfo->realVarsIndex[6301]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.f_rod variable */) };
  infoStreamPrint(OMC_LOG_DT, 0, "Solving linear system 3479 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);

  retValue = solve_linear_system(data, threadData, 5, &aux_x[0]);

  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,3479};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 3479 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6301]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.f_rod variable */) = aux_x[0];

  threadData->lastEquationSolved = 3479;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30612(DATA *data, threadData_t *threadData);


/*
equation index: 3481
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftDroplink.frame_b.f[2] = chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] * (chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.R.T[2,1] * chassis.detailedChassis.rrAxleDW.stabar.leftArmFrame.f[2] + chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.R.T[3,1] * chassis.detailedChassis.rrAxleDW.stabar.leftArmFrame.f[3] + chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.R.T[1,1] * chassis.detailedChassis.rrAxleDW.stabar.leftArmFrame.f[1]) + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] * (chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.R.T[3,2] * chassis.detailedChassis.rrAxleDW.stabar.leftArmFrame.f[3] - ((-chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.R.T[1,2]) * chassis.detailedChassis.rrAxleDW.stabar.leftArmFrame.f[1] - chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.R.T[2,2] * chassis.detailedChassis.rrAxleDW.stabar.leftArmFrame.f[2])) + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] * (chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.R.T[3,3] * chassis.detailedChassis.rrAxleDW.stabar.leftArmFrame.f[3] - ((-chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.R.T[1,3]) * chassis.detailedChassis.rrAxleDW.stabar.leftArmFrame.f[1] - chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.R.T[2,3] * chassis.detailedChassis.rrAxleDW.stabar.leftArmFrame.f[2]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3481(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3481};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6306]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.frame_b.f[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6563]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6333]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9530]] /* chassis.detailedChassis.rrAxleDW.stabar.leftArmFrame.f[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6336]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9531]] /* chassis.detailedChassis.rrAxleDW.stabar.leftArmFrame.f[3] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6330]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9529]] /* chassis.detailedChassis.rrAxleDW.stabar.leftArmFrame.f[1] variable */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6564]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6337]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9531]] /* chassis.detailedChassis.rrAxleDW.stabar.leftArmFrame.f[3] variable */)) - (((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6331]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.R.T[1,2] DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9529]] /* chassis.detailedChassis.rrAxleDW.stabar.leftArmFrame.f[1] variable */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6334]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9530]] /* chassis.detailedChassis.rrAxleDW.stabar.leftArmFrame.f[2] variable */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6565]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6338]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9531]] /* chassis.detailedChassis.rrAxleDW.stabar.leftArmFrame.f[3] variable */)) - (((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6332]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.R.T[1,3] DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9529]] /* chassis.detailedChassis.rrAxleDW.stabar.leftArmFrame.f[1] variable */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6335]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9530]] /* chassis.detailedChassis.rrAxleDW.stabar.leftArmFrame.f[2] variable */)))));
  threadData->lastEquationSolved = 3481;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30616(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30611(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30615(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30613(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30603(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30601(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30599(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30511(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30510(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30509(DATA *data, threadData_t *threadData);


/*
equation index: 3521
type: LINEAR

<var>chassis.detailedChassis.rrAxleDW.stabar.mountAxis.frame_a.t[2]</var>
<var>chassis.detailedChassis.rrAxleDW.stabar.mountAxis.frame_a.t[1]</var>
<var>chassis.detailedChassis.rrAxleDW.stabar.mountAxis.frame_a.t[3]</var>
<var>chassis.detailedChassis.rrAxleDW.rightDroplink.f_rod</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3521(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3521};
  /* Linear equation system */
  int retValue;
  double aux_x[4] = { (data->localData[1]->realVars[data->simulationInfo->realVarsIndex[9554]] /* chassis.detailedChassis.rrAxleDW.stabar.mountAxis.frame_a.t[2] variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[9553]] /* chassis.detailedChassis.rrAxleDW.stabar.mountAxis.frame_a.t[1] variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[9555]] /* chassis.detailedChassis.rrAxleDW.stabar.mountAxis.frame_a.t[3] variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[8069]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.f_rod variable */) };
  infoStreamPrint(OMC_LOG_DT, 0, "Solving linear system 3521 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);

  retValue = solve_linear_system(data, threadData, 6, &aux_x[0]);

  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,3521};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 3521 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9554]] /* chassis.detailedChassis.rrAxleDW.stabar.mountAxis.frame_a.t[2] variable */) = aux_x[0];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9553]] /* chassis.detailedChassis.rrAxleDW.stabar.mountAxis.frame_a.t[1] variable */) = aux_x[1];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9555]] /* chassis.detailedChassis.rrAxleDW.stabar.mountAxis.frame_a.t[3] variable */) = aux_x[2];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8069]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.f_rod variable */) = aux_x[3];

  threadData->lastEquationSolved = 3521;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30604(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30548(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30551(DATA *data, threadData_t *threadData);


/*
equation index: 3525
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightDroplink.frame_b.f[2] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] * (chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.R.T[2,1] * chassis.detailedChassis.rrAxleDW.stabar.rightArmFrame.f[2] + chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.R.T[3,1] * chassis.detailedChassis.rrAxleDW.stabar.rightArmFrame.f[3] + chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.R.T[1,1] * chassis.detailedChassis.rrAxleDW.stabar.rightArmFrame.f[1]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] * (chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.R.T[3,2] * chassis.detailedChassis.rrAxleDW.stabar.rightArmFrame.f[3] - ((-chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.R.T[1,2]) * chassis.detailedChassis.rrAxleDW.stabar.rightArmFrame.f[1] - chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.R.T[2,2] * chassis.detailedChassis.rrAxleDW.stabar.rightArmFrame.f[2])) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] * (chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.R.T[3,3] * chassis.detailedChassis.rrAxleDW.stabar.rightArmFrame.f[3] - ((-chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.R.T[1,3]) * chassis.detailedChassis.rrAxleDW.stabar.rightArmFrame.f[1] - chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.R.T[2,3] * chassis.detailedChassis.rrAxleDW.stabar.rightArmFrame.f[2]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3525(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3525};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8074]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.frame_b.f[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8326]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8101]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9559]] /* chassis.detailedChassis.rrAxleDW.stabar.rightArmFrame.f[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8104]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9560]] /* chassis.detailedChassis.rrAxleDW.stabar.rightArmFrame.f[3] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8098]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9558]] /* chassis.detailedChassis.rrAxleDW.stabar.rightArmFrame.f[1] variable */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8327]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8105]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9560]] /* chassis.detailedChassis.rrAxleDW.stabar.rightArmFrame.f[3] variable */)) - (((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8099]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.R.T[1,2] DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9558]] /* chassis.detailedChassis.rrAxleDW.stabar.rightArmFrame.f[1] variable */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8102]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9559]] /* chassis.detailedChassis.rrAxleDW.stabar.rightArmFrame.f[2] variable */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8328]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8106]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9560]] /* chassis.detailedChassis.rrAxleDW.stabar.rightArmFrame.f[3] variable */)) - (((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8100]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.R.T[1,3] DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9558]] /* chassis.detailedChassis.rrAxleDW.stabar.rightArmFrame.f[1] variable */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8103]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9559]] /* chassis.detailedChassis.rrAxleDW.stabar.rightArmFrame.f[2] variable */)))));
  threadData->lastEquationSolved = 3525;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30549(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30546(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30552(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30542(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30545(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30550(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30543(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30547(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30553(DATA *data, threadData_t *threadData);


/*
equation index: 3564
type: LINEAR

<var>chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_rod</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3564(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3564};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[data->simulationInfo->realVarsIndex[8264]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_rod variable */) };
  infoStreamPrint(OMC_LOG_DT, 0, "Solving linear system 3564 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);

  retValue = solve_linear_system(data, threadData, 7, &aux_x[0]);

  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,3564};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 3564 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8264]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_rod variable */) = aux_x[0];

  threadData->lastEquationSolved = 3564;
}

/*
equation index: 3565
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightApex.frame_a.f[3] = chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.R.T[3,1] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[3]) + chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.R.T[3,2] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[3]) + chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.R.T[3,3] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3565(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3565};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9747]] /* chassis.detailedChassis.rrAxleDW.toRightApex.frame_a.f[3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8947]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.R.T[3,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8323]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8255]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8326]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8256]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8329]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8257]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[3] variable */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8948]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.R.T[3,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8324]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8255]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8327]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8256]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8330]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8257]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[3] variable */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8949]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.R.T[3,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8325]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8255]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8328]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8256]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8331]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8257]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[3] variable */)));
  threadData->lastEquationSolved = 3565;
}

/*
equation index: 3566
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightApex.frame_a.f[2] = chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.R.T[2,1] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[3]) + chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.R.T[2,2] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[3]) + chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.R.T[2,3] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3566(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3566};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9746]] /* chassis.detailedChassis.rrAxleDW.toRightApex.frame_a.f[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8944]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.R.T[2,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8323]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8255]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8326]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8256]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8329]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8257]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[3] variable */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8945]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.R.T[2,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8324]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8255]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8327]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8256]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8330]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8257]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[3] variable */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8946]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.R.T[2,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8325]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8255]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8328]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8256]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8331]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8257]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[3] variable */)));
  threadData->lastEquationSolved = 3566;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30596(DATA *data, threadData_t *threadData);


/*
equation index: 3568
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightApex.frame_a.f[1] = chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.R.T[1,1] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[3]) + chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.R.T[1,2] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[3]) + chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.R.T[1,3] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_3568(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3568};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9745]] /* chassis.detailedChassis.rrAxleDW.toRightApex.frame_a.f[1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8941]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.R.T[1,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8323]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8255]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8326]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8256]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8329]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8257]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[3] variable */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8942]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.R.T[1,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8324]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8255]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8327]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8256]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8330]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8257]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[3] variable */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8943]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.R.T[1,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8325]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8255]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8328]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8256]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8331]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8257]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.f_b_a[3] variable */)));
  threadData->lastEquationSolved = 3568;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30594(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30597(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30585(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30584(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30583(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30589(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30587(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30590(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30586(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_functionInitialEquations_5(DATA *data, threadData_t *threadData)
{
  static void (*const eqFunctions[494])(DATA*, threadData_t*) = {
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29853,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29852,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29840,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29850,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29849,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29848,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2583,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29860,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2585,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29862,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29863,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2588,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2589,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2590,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31266,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2592,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2593,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29550,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29546,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29549,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29548,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29547,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29555,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29551,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29554,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29553,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29552,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29538,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2657,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2658,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2659,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2660,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2661,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29668,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2663,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2664,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29620,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2666,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2667,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29615,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29669,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29670,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29672,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29678,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29673,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29674,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29675,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29676,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29677,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29671,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2679,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2708,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29656,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29657,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29658,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29659,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29660,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29661,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29662,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29663,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29664,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29665,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29666,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29667,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29679,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29680,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2723,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29682,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29683,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29684,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29685,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29687,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29686,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29688,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29689,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29692,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29691,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29693,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29690,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29710,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29706,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29702,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29698,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29701,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29700,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29699,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29694,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2744,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2745,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2746,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29697,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2748,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2749,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2750,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29696,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2752,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2753,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2754,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29695,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2756,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2757,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2758,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29864,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29714,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29883,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29882,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29884,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29907,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29908,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29905,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29906,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29903,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29904,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29917,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30086,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29918,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29913,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29914,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29915,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29909,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29910,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30109,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30110,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30102,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30103,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30088,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30089,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30104,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30105,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30107,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30118,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30106,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30114,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2790,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2791,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2792,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30108,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2794,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2795,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2796,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2797,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30137,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30141,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30145,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2801,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30136,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30140,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30144,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2805,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30135,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30139,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30143,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30094,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30091,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30087,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30093,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30095,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30092,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30098,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30101,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30097,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30100,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30096,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30099,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2882,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30242,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30206,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30208,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30245,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30244,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30248,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30246,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30243,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30247,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30253,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30254,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30251,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30252,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30249,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30250,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2898,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2899,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2900,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30225,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2902,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2903,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2904,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30222,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30218,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30221,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30220,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2909,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30216,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2911,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2912,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2913,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30212,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2915,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2916,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30227,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30228,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30229,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30230,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30231,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31267,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30232,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30233,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2925,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2926,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2927,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30207,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2929,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2930,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2931,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29911,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29919,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29916,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29912,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2936,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2937,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2938,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29902,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29901,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29900,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2942,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2943,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2944,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29896,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29895,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29894,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2948,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2949,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2950,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29890,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29889,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29888,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3015,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3016,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29987,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3018,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29984,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3020,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29981,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29988,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29989,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29990,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29991,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29992,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3027,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3028,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3029,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29998,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3031,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29996,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29999,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3034,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30002,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3036,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30000,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30004,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3039,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3040,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3041,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30006,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3110,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30073,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30076,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3113,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30074,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30079,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30078,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30077,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30084,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30085,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30082,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30083,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30080,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30081,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3124,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3125,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3126,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30288,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30291,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30292,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30293,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30818,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30819,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30820,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3134,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30295,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30294,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30296,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3138,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3139,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3140,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30321,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30317,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30314,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3144,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3145,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3146,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30310,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30309,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30308,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3150,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3151,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3152,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30304,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30322,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30323,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30334,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30303,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30318,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30319,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30320,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30302,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30315,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30654,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30657,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30658,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30655,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30656,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30669,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30670,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30671,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30672,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30673,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30674,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30675,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30676,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30679,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30678,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30677,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30680,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30683,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30682,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30681,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30690,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30692,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30691,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30695,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30687,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30689,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30688,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30694,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30684,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30686,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30685,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30693,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3247,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3248,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3249,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30764,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3251,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3252,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3253,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30756,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3255,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3256,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30763,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3258,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3259,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3260,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3261,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3262,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3263,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30801,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3265,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30799,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30800,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3268,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3269,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3270,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31318,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3272,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3273,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30766,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30767,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30768,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30769,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30770,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30771,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30773,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30772,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30774,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3283,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30775,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30776,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30793,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30789,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30785,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30781,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3290,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30784,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30783,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30782,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30777,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3295,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30780,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30796,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30795,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30794,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30779,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30792,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30791,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30790,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30778,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30788,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30787,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30786,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3308,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30759,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3310,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3311,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3312,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3313,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3314,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30328,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30324,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30327,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30326,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30325,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30333,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30329,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30332,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30331,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30330,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30316,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3378,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3379,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3380,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3381,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3382,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30401,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3384,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3385,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30393,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3387,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3388,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3389,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3448,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30476,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30477,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30478,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30479,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30480,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30481,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30482,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30483,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30484,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30485,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30486,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30487,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3479,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30612,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3481,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30616,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30611,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30615,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30613,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30603,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30601,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30599,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30511,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30510,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30509,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3521,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30604,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30548,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30551,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3525,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30549,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30546,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30552,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30542,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30545,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30550,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30543,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30547,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30553,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3564,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3565,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3566,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30596,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_3568,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30594,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30597,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30585,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30584,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30583,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30589,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30587,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30590,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30586
  };
  
  for (int id = 0; id < 494; id++) {
    eqFunctions[id](data, threadData);
  }
}
#if defined(__cplusplus)
}
#endif