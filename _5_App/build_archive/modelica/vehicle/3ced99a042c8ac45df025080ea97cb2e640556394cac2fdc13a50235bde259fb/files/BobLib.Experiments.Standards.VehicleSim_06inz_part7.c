#include "BobLib.Experiments.Standards.VehicleSim_model.h"
#if defined(__cplusplus)
extern "C" {
#endif
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32518(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32516(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32519(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32515(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32517(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32520(DATA *data, threadData_t *threadData);


/*
equation index: 4720
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightApex.frame_a.f[3] = chassis.detailedChassis.frAxleDW.rightLCABody.sphere.R.T[3,1] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[1] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[2] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[3]) + chassis.detailedChassis.frAxleDW.rightLCABody.sphere.R.T[3,2] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[1] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[2] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[3]) + chassis.detailedChassis.frAxleDW.rightLCABody.sphere.R.T[3,3] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[1] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[2] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4720(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4720};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5989]] /* chassis.detailedChassis.frAxleDW.toRightApex.frame_a.f[3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4432]] /* chassis.detailedChassis.frAxleDW.rightLCABody.sphere.R.T[3,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4566]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4498]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4569]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4499]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4572]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4500]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[3] variable */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4433]] /* chassis.detailedChassis.frAxleDW.rightLCABody.sphere.R.T[3,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4567]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4498]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4570]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4499]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4573]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4500]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[3] variable */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4434]] /* chassis.detailedChassis.frAxleDW.rightLCABody.sphere.R.T[3,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4568]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4498]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4571]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4499]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4574]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4500]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[3] variable */)));
  threadData->lastEquationSolved = 4720;
}

/*
equation index: 4721
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightApex.frame_a.f[2] = chassis.detailedChassis.frAxleDW.rightLCABody.sphere.R.T[2,1] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[1] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[2] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[3]) + chassis.detailedChassis.frAxleDW.rightLCABody.sphere.R.T[2,2] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[1] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[2] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[3]) + chassis.detailedChassis.frAxleDW.rightLCABody.sphere.R.T[2,3] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[1] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[2] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4721(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4721};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5988]] /* chassis.detailedChassis.frAxleDW.toRightApex.frame_a.f[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4429]] /* chassis.detailedChassis.frAxleDW.rightLCABody.sphere.R.T[2,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4566]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4498]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4569]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4499]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4572]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4500]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[3] variable */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4430]] /* chassis.detailedChassis.frAxleDW.rightLCABody.sphere.R.T[2,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4567]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4498]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4570]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4499]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4573]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4500]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[3] variable */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4431]] /* chassis.detailedChassis.frAxleDW.rightLCABody.sphere.R.T[2,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4568]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4498]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4571]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4499]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4574]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4500]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[3] variable */)));
  threadData->lastEquationSolved = 4721;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32509(DATA *data, threadData_t *threadData);


/*
equation index: 4723
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toRightApex.frame_a.f[1] = chassis.detailedChassis.frAxleDW.rightLCABody.sphere.R.T[1,1] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[1] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[2] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[3]) + chassis.detailedChassis.frAxleDW.rightLCABody.sphere.R.T[1,2] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[1] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[2] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[3]) + chassis.detailedChassis.frAxleDW.rightLCABody.sphere.R.T[1,3] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[1] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[2] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4723(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4723};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5987]] /* chassis.detailedChassis.frAxleDW.toRightApex.frame_a.f[1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4426]] /* chassis.detailedChassis.frAxleDW.rightLCABody.sphere.R.T[1,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4566]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4498]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4569]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4499]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4572]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4500]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[3] variable */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4427]] /* chassis.detailedChassis.frAxleDW.rightLCABody.sphere.R.T[1,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4567]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4498]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4570]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4499]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4573]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4500]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[3] variable */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4428]] /* chassis.detailedChassis.frAxleDW.rightLCABody.sphere.R.T[1,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4568]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4498]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4571]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4499]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4574]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4500]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.f_b_a[3] variable */)));
  threadData->lastEquationSolved = 4723;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32507(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32510(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32522(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32526(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32531(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32528(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32530(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32529(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32527(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32532(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32410(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32411(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32533(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32537(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32535(DATA *data, threadData_t *threadData);


/*
equation index: 4800
type: LINEAR

<var>chassis.detailedChassis.frAxleDW.leftBellcrank.revolute.w</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4800(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4800};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[data->simulationInfo->realVarsIndex[2415]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.revolute.w DUMMY_STATE */) };
  infoStreamPrint(OMC_LOG_DT, 0, "Solving linear system 4800 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);

  retValue = solve_linear_system(data, threadData, 18, &aux_x[0]);

  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,4800};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 4800 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2415]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.revolute.w DUMMY_STATE */) = aux_x[0];

  threadData->lastEquationSolved = 4800;
}

/*
equation index: 4801
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[1] = $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.r[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] * (0.036645724016000025 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.002875737454000049 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] * (0.003465897055999999 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + (-0.036645724016000025) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,1] * ((-0.002875737454000049) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + (-0.003465897055999999) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4801(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4801};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[969]] /* der(chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[962]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.r[1]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2806]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) * ((0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2809]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * ((0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (-0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2812]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */)) * ((-0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (-0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 4801;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33025(DATA *data, threadData_t *threadData);


/*
equation index: 4803
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[2] = $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.r[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] * (0.036645724016000025 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.002875737454000049 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] * (0.003465897055999999 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + (-0.036645724016000025) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,2] * ((-0.002875737454000049) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + (-0.003465897055999999) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4803(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4803};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[970]] /* der(chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[963]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.r[2]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2807]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) * ((0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2810]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * ((0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (-0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2813]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */)) * ((-0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (-0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 4803;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33022(DATA *data, threadData_t *threadData);


/*
equation index: 4805
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[3] = $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.r[3] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] * (0.036645724016000025 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.002875737454000049 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] * (0.003465897055999999 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + (-0.036645724016000025) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,3] * ((-0.002875737454000049) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + (-0.003465897055999999) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4805(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4805};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[971]] /* der(chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[964]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.r[3]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2808]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) * ((0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2811]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * ((0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (-0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2814]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */)) * ((-0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (-0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 4805;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33019(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33026(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33027(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33028(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33029(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33030(DATA *data, threadData_t *threadData);


/*
equation index: 4812
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fb = chassis.detailedChassis.frAxleDW.leftShockLinkage.TabularSpring.combiTable1D.y[1] + chassis.detailedChassis.frAxleDW.leftShockLinkage.TabularDamper.combiTable1D.y[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4812(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4812};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2886]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fb variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2868]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.TabularSpring.combiTable1D.y[1] variable */) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2862]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.TabularDamper.combiTable1D.y[1] variable */);
  threadData->lastEquationSolved = 4812;
}

/*
equation index: 4813
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toLeftShock.frame_a.f[3] = (-chassis.chassisFrame.R.T[3,2]) * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[2] * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fb - chassis.chassisFrame.R.T[3,3] * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[3] * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fb - chassis.chassisFrame.R.T[3,1] * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[1] * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fb
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4813(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4813};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5954]] /* chassis.detailedChassis.frAxleDW.toLeftShock.frame_a.f[3] variable */) = ((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2883]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2886]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fb variable */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2884]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2886]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fb variable */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2882]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2886]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fb variable */))));
  threadData->lastEquationSolved = 4813;
}

/*
equation index: 4814
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toLeftShock.frame_a.f[2] = (-chassis.chassisFrame.R.T[2,2]) * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[2] * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fb - chassis.chassisFrame.R.T[2,3] * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[3] * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fb - chassis.chassisFrame.R.T[2,1] * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[1] * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fb
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4814(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4814};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5953]] /* chassis.detailedChassis.frAxleDW.toLeftShock.frame_a.f[2] variable */) = ((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2883]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2886]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fb variable */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2884]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2886]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fb variable */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2882]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2886]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fb variable */))));
  threadData->lastEquationSolved = 4814;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33036(DATA *data, threadData_t *threadData);


/*
equation index: 4816
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toLeftShock.frame_a.f[1] = (-chassis.chassisFrame.R.T[1,2]) * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[2] * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fb - chassis.chassisFrame.R.T[1,3] * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[3] * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fb - chassis.chassisFrame.R.T[1,1] * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[1] * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fb
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4816(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4816};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5952]] /* chassis.detailedChassis.frAxleDW.toLeftShock.frame_a.f[1] variable */) = ((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2883]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2886]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fb variable */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2884]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2886]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fb variable */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2882]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2886]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fb variable */))));
  threadData->lastEquationSolved = 4816;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33034(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33037(DATA *data, threadData_t *threadData);


/*
equation index: 4819
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fa = -chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fb
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4819(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4819};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2885]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fa variable */) = (-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2886]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fb variable */));
  threadData->lastEquationSolved = 4819;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33043(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33044(DATA *data, threadData_t *threadData);


/*
equation index: 4822
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftShockLinkage.frame_a.f[2] = (-chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2]) * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[2] * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fa - chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[3] * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fa - chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[1] * chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fa
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4822(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4822};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2874]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.frame_a.f[2] variable */) = ((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2810]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2883]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2885]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fa variable */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2811]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2884]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2885]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fa variable */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2809]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2882]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.e_rel_0[1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2885]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.fa variable */))));
  threadData->lastEquationSolved = 4822;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33041(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33045(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33038(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33039(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33042(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33046(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33093(DATA *data, threadData_t *threadData);


/*
equation index: 4830
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftBellcrank.side_4.vis.r[1] = $DER.chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] * ((-0.039062922128) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.048393882129999954 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] * ((-0.017982744577999997) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + 0.039062922128 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,1] * ((-0.048393882129999954) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + 0.017982744577999997 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4830(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4830};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[905]] /* der(chassis.detailedChassis.frAxleDW.leftBellcrank.side_4.vis.r[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[969]] /* der(chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[1]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2806]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) * ((-0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2809]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * ((-0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2812]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */)) * ((-0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 4830;
}

/*
equation index: 4831
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftBellcrank.side_4.vis.r[2] = $DER.chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] * ((-0.039062922128) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.048393882129999954 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] * ((-0.017982744577999997) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + 0.039062922128 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,2] * ((-0.048393882129999954) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + 0.017982744577999997 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4831(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4831};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[906]] /* der(chassis.detailedChassis.frAxleDW.leftBellcrank.side_4.vis.r[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[970]] /* der(chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[2]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2807]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) * ((-0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2810]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * ((-0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2813]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */)) * ((-0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 4831;
}

/*
equation index: 4832
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftBellcrank.side_4.vis.r[3] = $DER.chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[3] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] * ((-0.039062922128) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.048393882129999954 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] * ((-0.017982744577999997) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + 0.039062922128 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,3] * ((-0.048393882129999954) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + 0.017982744577999997 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4832(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4832};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[907]] /* der(chassis.detailedChassis.frAxleDW.leftBellcrank.side_4.vis.r[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[971]] /* der(chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[3]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2808]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) * ((-0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2811]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * ((-0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2814]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */)) * ((-0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 4832;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33095(DATA *data, threadData_t *threadData);


/*
equation index: 4901
type: LINEAR

<var>chassis.detailedChassis.frAxleDW.stabar.stabarAxis.w</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4901(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4901};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[data->simulationInfo->realVarsIndex[5841]] /* chassis.detailedChassis.frAxleDW.stabar.stabarAxis.w DUMMY_STATE */) };
  infoStreamPrint(OMC_LOG_DT, 0, "Solving linear system 4901 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);

  retValue = solve_linear_system(data, threadData, 19, &aux_x[0]);

  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,4901};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 4901 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5841]] /* chassis.detailedChassis.frAxleDW.stabar.stabarAxis.w DUMMY_STATE */) = aux_x[0];

  threadData->lastEquationSolved = 4901;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33162(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32540(DATA *data, threadData_t *threadData);


/*
equation index: 4904
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.rRod_a[2] = chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.rRod_0[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.rRod_0[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.rRod_0[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4904(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4904};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2766]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.rRod_a[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2809]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2762]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.rRod_0[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2810]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2763]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.rRod_0[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2811]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2764]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.rRod_0[3] DUMMY_STATE */));
  threadData->lastEquationSolved = 4904;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32545(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33165(DATA *data, threadData_t *threadData);


/*
equation index: 4907
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.der_rRod_a_L[2] = (chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.rRod_0[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.rRod_0[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.rRod_0[3] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.rRod_a[3] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.rRod_a[1]) / chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4907(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4907};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2727]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.der_rRod_a_L[2] variable */) = DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2809]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[944]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.rRod_0[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2810]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[945]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.rRod_0[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2811]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[946]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.rRod_0[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2767]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.rRod_a[3] variable */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2765]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.rRod_a[1] variable */))),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[513]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodLength PARAM */),"chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodLength",equationIndexes);
  threadData->lastEquationSolved = 4907;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33163(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32541(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32543(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32544(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32546(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32548(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32547(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32549(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32550(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32553(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32552(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32554(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32551(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32571(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32567(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32563(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33168(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32559(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32562(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32561(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32560(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32555(DATA *data, threadData_t *threadData);


/*
equation index: 4930
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a1[3] = chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[3] * (chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[3]) / chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodLength - chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[3] * (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[3]) / ((chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[3]) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodLength)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4930(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4930};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2743]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a1[3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2734]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[3] variable */)) * (DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2729]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2802]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2730]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2803]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2731]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2804]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[3] variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[513]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodLength PARAM */),"chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodLength",equationIndexes)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2731]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[3] variable */)) * (DIVISION_SIM(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[505]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2802]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[1] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[506]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2803]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[2] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[507]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2804]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[3] variable */)),(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[505]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2732]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[1] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[506]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2733]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[2] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[507]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2734]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[3] variable */))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[513]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodLength PARAM */)),"(chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[3]) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodLength",equationIndexes)));
  threadData->lastEquationSolved = 4930;
}

/*
equation index: 4931
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a1[2] = chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[2] * (chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[3]) / chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodLength - chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[2] * (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[3]) / ((chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[3]) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodLength)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4931(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4931};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2742]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a1[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2733]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[2] variable */)) * (DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2729]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2802]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2730]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2803]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2731]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2804]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[3] variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[513]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodLength PARAM */),"chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodLength",equationIndexes)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2730]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[2] variable */)) * (DIVISION_SIM(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[505]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2802]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[1] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[506]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2803]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[2] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[507]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2804]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[3] variable */)),(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[505]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2732]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[1] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[506]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2733]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[2] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[507]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2734]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[3] variable */))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[513]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodLength PARAM */)),"(chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[3]) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodLength",equationIndexes)));
  threadData->lastEquationSolved = 4931;
}

/*
equation index: 4932
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a1[1] = chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[1] * (chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[3]) / chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodLength - chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[1] * (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[3]) / ((chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[3]) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodLength)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4932(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4932};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2741]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a1[1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2732]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[1] variable */)) * (DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2729]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2802]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2730]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2803]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2731]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2804]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[3] variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[513]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodLength PARAM */),"chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodLength",equationIndexes)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2729]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_a[1] variable */)) * (DIVISION_SIM(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[505]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2802]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[1] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[506]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2803]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[2] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[507]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2804]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.t_ia_a[3] variable */)),(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[505]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2732]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[1] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[506]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2733]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[2] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[507]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2734]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[3] variable */))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[513]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodLength PARAM */)),"(chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_a[3]) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodLength",equationIndexes)));
  threadData->lastEquationSolved = 4932;
}

/*
equation index: 4962
type: LINEAR

<var>chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_rod</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4962(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4962};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[data->simulationInfo->realVarsIndex[2747]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_rod variable */) };
  infoStreamPrint(OMC_LOG_DT, 0, "Solving linear system 4962 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);

  retValue = solve_linear_system(data, threadData, 20, &aux_x[0]);

  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,4962};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 4962 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2747]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_rod variable */) = aux_x[0];

  threadData->lastEquationSolved = 4962;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33078(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33077(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33076(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33082(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33080(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33083(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33079(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33081(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33084(DATA *data, threadData_t *threadData);


/*
equation index: 4972
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toLeftApex.frame_a.f[3] = chassis.detailedChassis.frAxleDW.leftLCABody.sphere.R.T[3,1] * (chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[3]) + chassis.detailedChassis.frAxleDW.leftLCABody.sphere.R.T[3,2] * (chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[3]) + chassis.detailedChassis.frAxleDW.leftLCABody.sphere.R.T[3,3] * (chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4972(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4972};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5927]] /* chassis.detailedChassis.frAxleDW.toLeftApex.frame_a.f[3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2670]] /* chassis.detailedChassis.frAxleDW.leftLCABody.sphere.R.T[3,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2806]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2738]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2809]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2739]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2812]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2740]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[3] variable */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2671]] /* chassis.detailedChassis.frAxleDW.leftLCABody.sphere.R.T[3,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2807]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2738]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2810]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2739]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2813]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2740]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[3] variable */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2672]] /* chassis.detailedChassis.frAxleDW.leftLCABody.sphere.R.T[3,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2808]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2738]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2811]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2739]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2814]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2740]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[3] variable */)));
  threadData->lastEquationSolved = 4972;
}

/*
equation index: 4973
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toLeftApex.frame_a.f[2] = chassis.detailedChassis.frAxleDW.leftLCABody.sphere.R.T[2,1] * (chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[3]) + chassis.detailedChassis.frAxleDW.leftLCABody.sphere.R.T[2,2] * (chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[3]) + chassis.detailedChassis.frAxleDW.leftLCABody.sphere.R.T[2,3] * (chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4973(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4973};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5926]] /* chassis.detailedChassis.frAxleDW.toLeftApex.frame_a.f[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2667]] /* chassis.detailedChassis.frAxleDW.leftLCABody.sphere.R.T[2,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2806]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2738]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2809]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2739]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2812]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2740]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[3] variable */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2668]] /* chassis.detailedChassis.frAxleDW.leftLCABody.sphere.R.T[2,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2807]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2738]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2810]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2739]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2813]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2740]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[3] variable */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2669]] /* chassis.detailedChassis.frAxleDW.leftLCABody.sphere.R.T[2,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2808]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2738]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2811]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2739]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2814]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2740]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[3] variable */)));
  threadData->lastEquationSolved = 4973;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33089(DATA *data, threadData_t *threadData);


/*
equation index: 4975
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.toLeftApex.frame_a.f[1] = chassis.detailedChassis.frAxleDW.leftLCABody.sphere.R.T[1,1] * (chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[3]) + chassis.detailedChassis.frAxleDW.leftLCABody.sphere.R.T[1,2] * (chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[3]) + chassis.detailedChassis.frAxleDW.leftLCABody.sphere.R.T[1,3] * (chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4975(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4975};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5925]] /* chassis.detailedChassis.frAxleDW.toLeftApex.frame_a.f[1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2664]] /* chassis.detailedChassis.frAxleDW.leftLCABody.sphere.R.T[1,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2806]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2738]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2809]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2739]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2812]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2740]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[3] variable */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2665]] /* chassis.detailedChassis.frAxleDW.leftLCABody.sphere.R.T[1,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2807]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2738]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2810]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2739]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2813]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2740]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[3] variable */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2666]] /* chassis.detailedChassis.frAxleDW.leftLCABody.sphere.R.T[1,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2808]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2738]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2811]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2739]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2814]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2740]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.f_b_a[3] variable */)));
  threadData->lastEquationSolved = 4975;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33087(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33090(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32558(DATA *data, threadData_t *threadData);


/*
equation index: 4979
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.R.T[3,3] = chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[3,1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[3,2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[3,3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4979(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4979};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2836]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.R.T[3,3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2710]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[3,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2808]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2711]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[3,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2811]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2712]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[3,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2814]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */));
  threadData->lastEquationSolved = 4979;
}

/*
equation index: 4980
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.R.T[3,2] = chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[3,1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[3,2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[3,3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4980(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4980};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2835]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.R.T[3,2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2710]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[3,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2807]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2711]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[3,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2810]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2712]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[3,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2813]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */));
  threadData->lastEquationSolved = 4980;
}

/*
equation index: 4981
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.R.T[3,1] = chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[3,1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[3,2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[3,3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4981(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4981};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2834]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.R.T[3,1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2710]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[3,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2806]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2711]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[3,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2809]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2712]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[3,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2812]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 4981;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32557(DATA *data, threadData_t *threadData);


/*
equation index: 4983
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.R.T[2,3] = chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[2,1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[2,2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[2,3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4983(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4983};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2833]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.R.T[2,3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2707]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[2,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2808]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2708]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[2,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2811]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2709]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[2,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2814]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */));
  threadData->lastEquationSolved = 4983;
}

/*
equation index: 4984
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.R.T[2,2] = chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[2,1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[2,2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[2,3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4984(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4984};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2832]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.R.T[2,2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2707]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[2,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2807]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2708]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[2,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2810]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2709]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[2,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2813]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */));
  threadData->lastEquationSolved = 4984;
}

/*
equation index: 4985
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.R.T[2,1] = chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[2,1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[2,2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[2,3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4985(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4985};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2831]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.R.T[2,1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2707]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[2,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2806]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2708]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[2,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2809]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2709]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[2,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2812]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 4985;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32556(DATA *data, threadData_t *threadData);


/*
equation index: 4987
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.R.T[1,3] = chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[1,1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[1,2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[1,3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4987(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4987};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2830]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.R.T[1,3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2704]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[1,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2808]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2705]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[1,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2811]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2706]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[1,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2814]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */));
  threadData->lastEquationSolved = 4987;
}

/*
equation index: 4988
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.R.T[1,2] = chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[1,1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[1,2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[1,3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4988(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4988};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2829]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.R.T[1,2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2704]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[1,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2807]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2705]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[1,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2810]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2706]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[1,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2813]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */));
  threadData->lastEquationSolved = 4988;
}

/*
equation index: 4989
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.R.T[1,1] = chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[1,1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[1,2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[1,3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4989(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4989};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2828]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.R.T[1,1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2704]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[1,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2806]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2705]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[1,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2809]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2706]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.R_rel_ia.T[1,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2812]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 4989;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33167(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33166(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33173(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33174(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33171(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33172(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33169(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33170(DATA *data, threadData_t *threadData);


/*
equation index: 4998
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength = sqrt(chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia * chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4998(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4998};
  real_array tmp730;
  real_array tmp731;
  modelica_real tmp732;
  real_array_create(&tmp730, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1705]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp731, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1705]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp732 = mul_real_scalar_product(tmp730, tmp731);
  if(!(tmp732 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia * chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia) was %g should be >= 0", tmp732);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1710]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength PARAM */) = sqrt(tmp732);
  threadData->lastEquationSolved = 4998;
}

/*
equation index: 4999
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength = 0.3232812986777304
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_4999(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4999};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[621]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength PARAM */) = 0.3232812986777304;
  threadData->lastEquationSolved = 4999;
}

/*
equation index: 5000
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rodLength = sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5000(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5000};
  real_array tmp733;
  real_array tmp734;
  modelica_real tmp735;
  real_array_create(&tmp733, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2248]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp734, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2248]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp735 = mul_real_scalar_product(tmp733, tmp734);
  if(!(tmp735 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia) was %g should be >= 0", tmp735);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2253]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rodLength PARAM */) = sqrt(tmp735);
  threadData->lastEquationSolved = 5000;
}

/*
equation index: 5001
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1Length = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rodLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5001(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5001};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2257]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1Length PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2253]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rodLength PARAM */);
  threadData->lastEquationSolved = 5001;
}

/*
equation index: 5002
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.lengthConstraint = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1Length
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5002(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5002};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2226]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.lengthConstraint PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2257]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1Length PARAM */);
  threadData->lastEquationSolved = 5002;
}

/*
equation index: 5003
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.C = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] ^ 2.0 + (-2.0) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.lengthConstraint ^ 2.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5003(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5003};
  modelica_real tmp736;
  modelica_real tmp737;
  modelica_real tmp738;
  modelica_real tmp739;
  modelica_real tmp740;
  modelica_real tmp741;
  modelica_real tmp742;
  tmp736 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5631]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] DUMMY_STATE */);
  tmp737 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5632]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[2] DUMMY_STATE */);
  tmp738 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5633]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[3] DUMMY_STATE */);
  tmp739 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5634]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] DUMMY_STATE */);
  tmp740 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5635]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] DUMMY_STATE */);
  tmp741 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5636]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] DUMMY_STATE */);
  tmp742 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2226]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.lengthConstraint PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5592]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.C DUMMY_STATE */) = (tmp736 * tmp736) + (tmp737 * tmp737) + (tmp738 * tmp738) + (tmp739 * tmp739) + (tmp740 * tmp740) + (tmp741 * tmp741) + (-2.0) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5623]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5622]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_a DUMMY_STATE */))) - ((tmp742 * tmp742));
  threadData->lastEquationSolved = 5003;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31422(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31423(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31424(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31793(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31794(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31795(DATA *data, threadData_t *threadData);


/*
equation index: 5010
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.positiveBranch = BobLib.Experiments.Standards.VehicleSim.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.selectBranch(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.lengthConstraint, chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e, 0.017453292519943295 * (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.phi_offset + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.phi_guess), chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a, chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5010(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5010};
  real_array tmp743;
  real_array tmp744;
  real_array tmp745;
  real_array_create(&tmp743, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp744, ((modelica_real*)&((&data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5631]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] DUMMY_STATE */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp745, ((modelica_real*)&((&data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5634]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] DUMMY_STATE */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  (data->simulationInfo->booleanParameter[data->simulationInfo->booleanParamsIndex[235]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.positiveBranch PARAM */) = omc_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_frAxleDW_rightWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2226]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.lengthConstraint PARAM */), tmp743, (0.017453292519943295) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2231]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.phi_offset PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2230]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.phi_guess PARAM */)), tmp744, tmp745);
  threadData->lastEquationSolved = 5010;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31426(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31425(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31427(DATA *data, threadData_t *threadData);


/*
equation index: 5014
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] ^ 2.0 + (1.0 - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] ^ 2.0) * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5014(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5014};
  modelica_real tmp746;
  modelica_real tmp747;
  tmp746 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */);
  tmp747 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5593]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,1] DUMMY_STATE */) = (tmp746 * tmp746) + (1.0 - ((tmp747 * tmp747))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 5014;
}

/*
equation index: 5015
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,2] = (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5015(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5015};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5594]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,2] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 5015;
}

/*
equation index: 5016
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,3] = (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5016(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5016};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5595]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,3] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))));
  threadData->lastEquationSolved = 5016;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31435(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31436(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31437(DATA *data, threadData_t *threadData);


/*
equation index: 5020
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,1] = (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5020(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5020};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5596]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,1] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))));
  threadData->lastEquationSolved = 5020;
}

/*
equation index: 5021
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] ^ 2.0 + (1.0 - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] ^ 2.0) * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5021(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5021};
  modelica_real tmp748;
  modelica_real tmp749;
  tmp748 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */);
  tmp749 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5597]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,2] DUMMY_STATE */) = (tmp748 * tmp748) + (1.0 - ((tmp749 * tmp749))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 5021;
}

/*
equation index: 5022
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,3] = (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5022(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5022};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5598]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,3] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 5022;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31440(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31441(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31442(DATA *data, threadData_t *threadData);


/*
equation index: 5026
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,1] = (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5026(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5026};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5599]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,1] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 5026;
}

/*
equation index: 5027
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,2] = (chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5027(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5027};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5600]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,2] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))));
  threadData->lastEquationSolved = 5027;
}

/*
equation index: 5028
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] ^ 2.0 + (1.0 - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] ^ 2.0) * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5028(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5028};
  modelica_real tmp750;
  modelica_real tmp751;
  tmp750 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */);
  tmp751 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5601]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,3] DUMMY_STATE */) = (tmp750 * tmp750) + (1.0 - ((tmp751 * tmp751))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 5028;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31445(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31446(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31447(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31448(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31449(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31450(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31451(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31452(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31464(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31467(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31468(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31465(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31466(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31637(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31638(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31639(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31640(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31641(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31642(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31643(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31644(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31647(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31646(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31645(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31648(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31651(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31650(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31649(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31658(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31660(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31659(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31663(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31655(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31657(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31656(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31662(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31652(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31654(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31653(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31661(DATA *data, threadData_t *threadData);


void BobLib_Experiments_Standards_VehicleSim_eqFunction_5069(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5070(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5071(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5072(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5073(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5074(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5075(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5076(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5077(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5078(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5079(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5080(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5081(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5082(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5083(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5084(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5085(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5086(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5087(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5088(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5089(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5090(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5091(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5092(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5093(DATA*, threadData_t*);
/*
equation index: 5121
indexNonlinear: 12
type: NONLINEAR

vars: {chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.phi}
eqns: {5069, 5070, 5071, 5072, 5073, 5074, 5075, 5076, 5077, 5078, 5079, 5080, 5081, 5082, 5083, 5084, 5085, 5086, 5087, 5088, 5089, 5090, 5091, 5092, 5093}
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5121(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5121};
  int retValue;
  infoStreamPrint(OMC_LOG_DT, 0, "Solving nonlinear system 5121 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
  /* get old value */
  data->simulationInfo->nonlinearSystemData[12].nlsxOld[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5444]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.phi DUMMY_STATE */);
  retValue = solve_nonlinear_system(data, threadData, 12);
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,5121};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving non-linear system 5121 failed at time=%.15g.\nFor more information please use -lv LOG_NLS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5444]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.phi DUMMY_STATE */) = data->simulationInfo->nonlinearSystemData[12].nlsx[0];
  threadData->lastEquationSolved = 5121;
}

/*
equation index: 5122
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.e_xw[1] = chassis.detailedChassis.frameFR.R.T[1,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5122(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5122};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4849]] /* chassis.detailedChassis.frAxleDW.rightTire.e_xw[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6077]] /* chassis.detailedChassis.frameFR.R.T[1,1] DUMMY_STATE */);
  threadData->lastEquationSolved = 5122;
}

/*
equation index: 5123
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.e_xw[2] = chassis.detailedChassis.frameFR.R.T[1,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5123(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5123};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4850]] /* chassis.detailedChassis.frAxleDW.rightTire.e_xw[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6078]] /* chassis.detailedChassis.frameFR.R.T[1,2] DUMMY_STATE */);
  threadData->lastEquationSolved = 5123;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31722(DATA *data, threadData_t *threadData);


/*
equation index: 5125
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.e_xw[3] = chassis.detailedChassis.frameFR.R.T[1,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5125(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5125};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4851]] /* chassis.detailedChassis.frAxleDW.rightTire.e_xw[3] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6079]] /* chassis.detailedChassis.frameFR.R.T[1,3] DUMMY_STATE */);
  threadData->lastEquationSolved = 5125;
}

/*
equation index: 5126
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.frame_a.r_0[1] = chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[1] + chassis.detailedChassis.frameFR.R.T[1,1] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1] + chassis.detailedChassis.frameFR.R.T[2,1] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2] + chassis.detailedChassis.frameFR.R.T[3,1] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5126(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5126};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5239]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.frame_a.r_0[1] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4409]] /* chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[1] DUMMY_STATE */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6077]] /* chassis.detailedChassis.frameFR.R.T[1,1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2568]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6080]] /* chassis.detailedChassis.frameFR.R.T[2,1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2569]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6083]] /* chassis.detailedChassis.frameFR.R.T[3,1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2570]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3] PARAM */));
  threadData->lastEquationSolved = 5126;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31730(DATA *data, threadData_t *threadData);


/*
equation index: 5128
type: SIMPLE_ASSIGN
chassis.detailedChassis.frameFR.r_0[1] = chassis.detailedChassis.frAxleDW.rightTire.wheelModel.wheelVelSensor.der1[1].u - chassis.detailedChassis.frameFR.R.T[3,1] * chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.s
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5128(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5128};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6089]] /* chassis.detailedChassis.frameFR.r_0[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5036]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.wheelVelSensor.der1[1].u DUMMY_STATE */) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6083]] /* chassis.detailedChassis.frameFR.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4982]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.s DUMMY_STATE */)));
  threadData->lastEquationSolved = 5128;
}

/*
equation index: 5129
type: SIMPLE_ASSIGN
chassis.rightWheelVector[3] = chassis.chassisFrame.R.T[1,3] * chassis.detailedChassis.frameFR.R.T[1,1] + chassis.chassisFrame.R.T[2,3] * chassis.detailedChassis.frameFR.R.T[2,1] + chassis.chassisFrame.R.T[3,3] * chassis.detailedChassis.frameFR.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5129(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5129};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10137]] /* chassis.rightWheelVector[3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6077]] /* chassis.detailedChassis.frameFR.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6080]] /* chassis.detailedChassis.frameFR.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6083]] /* chassis.detailedChassis.frameFR.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 5129;
}

/*
equation index: 5130
type: SIMPLE_ASSIGN
chassis.rightWheelVector[2] = chassis.chassisFrame.R.T[1,2] * chassis.detailedChassis.frameFR.R.T[1,1] + chassis.chassisFrame.R.T[2,2] * chassis.detailedChassis.frameFR.R.T[2,1] + chassis.chassisFrame.R.T[3,2] * chassis.detailedChassis.frameFR.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5130(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5130};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10136]] /* chassis.rightWheelVector[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6077]] /* chassis.detailedChassis.frameFR.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6080]] /* chassis.detailedChassis.frameFR.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6083]] /* chassis.detailedChassis.frameFR.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 5130;
}

/*
equation index: 5131
type: SIMPLE_ASSIGN
chassis.rightWheelVector[1] = chassis.chassisFrame.R.T[1,1] * chassis.detailedChassis.frameFR.R.T[1,1] + chassis.chassisFrame.R.T[2,1] * chassis.detailedChassis.frameFR.R.T[2,1] + chassis.chassisFrame.R.T[3,1] * chassis.detailedChassis.frameFR.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5131(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5131};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10135]] /* chassis.rightWheelVector[1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6077]] /* chassis.detailedChassis.frameFR.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6080]] /* chassis.detailedChassis.frameFR.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6083]] /* chassis.detailedChassis.frameFR.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 5131;
}

/*
equation index: 5132
type: SIMPLE_ASSIGN
rightSteerAngle = -atan(chassis.rightWheelVector[2] / chassis.rightWheelVector[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5132(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5132};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10252]] /* rightSteerAngle variable */) = (-atan(DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10136]] /* chassis.rightWheelVector[2] variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10135]] /* chassis.rightWheelVector[1] variable */),"chassis.rightWheelVector[1]",equationIndexes)));
  threadData->lastEquationSolved = 5132;
}

/*
equation index: 5133
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.e_yw[1] = chassis.detailedChassis.frameFR.R.T[2,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5133(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5133};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4855]] /* chassis.detailedChassis.frAxleDW.rightTire.e_yw[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6080]] /* chassis.detailedChassis.frameFR.R.T[2,1] DUMMY_STATE */);
  threadData->lastEquationSolved = 5133;
}

/*
equation index: 5134
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[3,1] = chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,1] * chassis.detailedChassis.frameFR.R.T[1,1] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,2] * chassis.detailedChassis.frameFR.R.T[2,1] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,3] * chassis.detailedChassis.frameFR.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5134(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5134};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5029]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[3,1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4931]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6077]] /* chassis.detailedChassis.frameFR.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4932]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6080]] /* chassis.detailedChassis.frameFR.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4933]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6083]] /* chassis.detailedChassis.frameFR.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 5134;
}

/*
equation index: 5135
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[2,1] = chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,1] * chassis.detailedChassis.frameFR.R.T[1,1] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,2] * chassis.detailedChassis.frameFR.R.T[2,1] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,3] * chassis.detailedChassis.frameFR.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5135(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5135};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5027]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[2,1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4928]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6077]] /* chassis.detailedChassis.frameFR.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4929]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6080]] /* chassis.detailedChassis.frameFR.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4930]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6083]] /* chassis.detailedChassis.frameFR.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 5135;
}

/*
equation index: 5136
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.e_spin[1] = chassis.detailedChassis.frAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[2,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5136(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5136};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4843]] /* chassis.detailedChassis.frAxleDW.rightTire.e_spin[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5027]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[2,1] variable */);
  threadData->lastEquationSolved = 5136;
}

/*
equation index: 5137
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[1,1] = chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,1] * chassis.detailedChassis.frameFR.R.T[1,1] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,2] * chassis.detailedChassis.frameFR.R.T[2,1] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,3] * chassis.detailedChassis.frameFR.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5137(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5137};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5025]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[1,1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4925]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6077]] /* chassis.detailedChassis.frameFR.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4926]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6080]] /* chassis.detailedChassis.frameFR.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4927]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6083]] /* chassis.detailedChassis.frameFR.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 5137;
}

/*
equation index: 5138
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.e_yw[3] = chassis.detailedChassis.frameFR.R.T[2,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5138(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5138};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4857]] /* chassis.detailedChassis.frAxleDW.rightTire.e_yw[3] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6082]] /* chassis.detailedChassis.frameFR.R.T[2,3] DUMMY_STATE */);
  threadData->lastEquationSolved = 5138;
}

/*
equation index: 5139
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.frame_a.r_0[2] = chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[2] + chassis.detailedChassis.frameFR.R.T[1,2] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1] + chassis.detailedChassis.frameFR.R.T[2,2] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2] + chassis.detailedChassis.frameFR.R.T[3,2] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5139(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5139};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5240]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.frame_a.r_0[2] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4410]] /* chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[2] DUMMY_STATE */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6078]] /* chassis.detailedChassis.frameFR.R.T[1,2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2568]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6081]] /* chassis.detailedChassis.frameFR.R.T[2,2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2569]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6084]] /* chassis.detailedChassis.frameFR.R.T[3,2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2570]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3] PARAM */));
  threadData->lastEquationSolved = 5139;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31738(DATA *data, threadData_t *threadData);


/*
equation index: 5141
type: SIMPLE_ASSIGN
chassis.detailedChassis.frameFR.r_0[2] = chassis.detailedChassis.frAxleDW.rightTire.wheelModel.wheelVelSensor.der1[2].u - chassis.detailedChassis.frameFR.R.T[3,2] * chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.s
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5141(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5141};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6090]] /* chassis.detailedChassis.frameFR.r_0[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5037]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.wheelVelSensor.der1[2].u DUMMY_STATE */) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6084]] /* chassis.detailedChassis.frameFR.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4982]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.s DUMMY_STATE */)));
  threadData->lastEquationSolved = 5141;
}

/*
equation index: 5142
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.e_yw[2] = chassis.detailedChassis.frameFR.R.T[2,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5142(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5142};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4856]] /* chassis.detailedChassis.frAxleDW.rightTire.e_yw[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6081]] /* chassis.detailedChassis.frameFR.R.T[2,2] DUMMY_STATE */);
  threadData->lastEquationSolved = 5142;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31726(DATA *data, threadData_t *threadData);


/*
equation index: 5144
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[3,2] = chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,1] * chassis.detailedChassis.frameFR.R.T[1,2] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,2] * chassis.detailedChassis.frameFR.R.T[2,2] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,3] * chassis.detailedChassis.frameFR.R.T[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5144(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5144};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5030]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[3,2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4931]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6078]] /* chassis.detailedChassis.frameFR.R.T[1,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4932]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6081]] /* chassis.detailedChassis.frameFR.R.T[2,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4933]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6084]] /* chassis.detailedChassis.frameFR.R.T[3,2] DUMMY_STATE */));
  threadData->lastEquationSolved = 5144;
}

/*
equation index: 5145
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[2,2] = chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,1] * chassis.detailedChassis.frameFR.R.T[1,2] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,2] * chassis.detailedChassis.frameFR.R.T[2,2] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,3] * chassis.detailedChassis.frameFR.R.T[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5145(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5145};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5028]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[2,2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4928]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6078]] /* chassis.detailedChassis.frameFR.R.T[1,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4929]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6081]] /* chassis.detailedChassis.frameFR.R.T[2,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4930]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6084]] /* chassis.detailedChassis.frameFR.R.T[3,2] DUMMY_STATE */));
  threadData->lastEquationSolved = 5145;
}

/*
equation index: 5146
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.e_spin[2] = chassis.detailedChassis.frAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[2,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5146(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5146};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4844]] /* chassis.detailedChassis.frAxleDW.rightTire.e_spin[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5028]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[2,2] variable */);
  threadData->lastEquationSolved = 5146;
}

/*
equation index: 5147
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[1,2] = chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,1] * chassis.detailedChassis.frameFR.R.T[1,2] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,2] * chassis.detailedChassis.frameFR.R.T[2,2] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,3] * chassis.detailedChassis.frameFR.R.T[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5147(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5147};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5026]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.T[1,2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4925]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6078]] /* chassis.detailedChassis.frameFR.R.T[1,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4926]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6081]] /* chassis.detailedChassis.frameFR.R.T[2,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4927]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6084]] /* chassis.detailedChassis.frameFR.R.T[3,2] DUMMY_STATE */));
  threadData->lastEquationSolved = 5147;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31740(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31741(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31742(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31743(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31744(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31745(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31747(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31746(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31748(DATA *data, threadData_t *threadData);


/*
equation index: 5157
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieRod.rod.f_b_a1[1] = chassis.detailedChassis.frAxleDW.rightTieRod.rod.e3_a[1] * (chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_a[2] * chassis.detailedChassis.frAxleDW.rightTieRod.rod.t_ia_a[2] + chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_a[3] * chassis.detailedChassis.frAxleDW.rightTieRod.rod.t_ia_a[3]) / chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5157(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5157};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4734]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.f_b_a1[1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4725]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.e3_a[1] variable */)) * (DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4723]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_a[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4822]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.t_ia_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4724]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_a[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4823]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.t_ia_a[3] variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1710]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength PARAM */),"chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength",equationIndexes));
  threadData->lastEquationSolved = 5157;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31749(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31750(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31767(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31763(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31759(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31755(DATA *data, threadData_t *threadData);


/*
equation index: 5164
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieRod.rod.f_b_a1[3] = chassis.detailedChassis.frAxleDW.rightTieRod.rod.e3_a[3] * (chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_a[2] * chassis.detailedChassis.frAxleDW.rightTieRod.rod.t_ia_a[2] + chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_a[3] * chassis.detailedChassis.frAxleDW.rightTieRod.rod.t_ia_a[3]) / chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength - chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_a[3] * chassis.detailedChassis.frAxleDW.rightTieRod.rod.t_ia_a[1] / (chassis.detailedChassis.frAxleDW.rightTieRod.rod.e3_a[1] * chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5164(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5164};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4736]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.f_b_a1[3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4727]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.e3_a[3] variable */)) * (DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4723]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_a[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4822]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.t_ia_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4724]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_a[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4823]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.t_ia_a[3] variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1710]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength PARAM */),"chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength",equationIndexes)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4724]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_a[3] variable */)) * (DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4821]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.t_ia_a[1] variable */),((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4725]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.e3_a[1] variable */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1710]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength PARAM */)),"chassis.detailedChassis.frAxleDW.rightTieRod.rod.e3_a[1] * chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength",equationIndexes)));
  threadData->lastEquationSolved = 5164;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31758(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31757(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31756(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31751(DATA *data, threadData_t *threadData);


/*
equation index: 5169
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieRod.rod.f_b_a1[2] = chassis.detailedChassis.frAxleDW.rightTieRod.rod.e3_a[2] * (chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_a[2] * chassis.detailedChassis.frAxleDW.rightTieRod.rod.t_ia_a[2] + chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_a[3] * chassis.detailedChassis.frAxleDW.rightTieRod.rod.t_ia_a[3]) / chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength - chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_a[2] * chassis.detailedChassis.frAxleDW.rightTieRod.rod.t_ia_a[1] / (chassis.detailedChassis.frAxleDW.rightTieRod.rod.e3_a[1] * chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5169(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5169};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4735]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.f_b_a1[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4726]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.e3_a[2] variable */)) * (DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4723]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_a[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4822]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.t_ia_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4724]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_a[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4823]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.t_ia_a[3] variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1710]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength PARAM */),"chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength",equationIndexes)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4723]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.e2_a[2] variable */)) * (DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4821]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.t_ia_a[1] variable */),((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4725]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.e3_a[1] variable */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1710]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength PARAM */)),"chassis.detailedChassis.frAxleDW.rightTieRod.rod.e3_a[1] * chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength",equationIndexes)));
  threadData->lastEquationSolved = 5169;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31754(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31770(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31769(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31768(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31753(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31766(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31765(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31764(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31752(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31762(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31761(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31760(DATA *data, threadData_t *threadData);


/*
equation index: 5182
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.frame_a.r_0[3] = chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[3] + chassis.detailedChassis.frameFR.R.T[1,3] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1] + chassis.detailedChassis.frameFR.R.T[2,3] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2] + chassis.detailedChassis.frameFR.R.T[3,3] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5182(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5182};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5241]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.frame_a.r_0[3] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4411]] /* chassis.detailedChassis.frAxleDW.rightLCABody.frame_a.r_0[3] DUMMY_STATE */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6079]] /* chassis.detailedChassis.frameFR.R.T[1,3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2568]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6082]] /* chassis.detailedChassis.frameFR.R.T[2,3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2569]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6085]] /* chassis.detailedChassis.frameFR.R.T[3,3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2570]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3] PARAM */));
  threadData->lastEquationSolved = 5182;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31772(DATA *data, threadData_t *threadData);


/*
equation index: 5184
type: SIMPLE_ASSIGN
chassis.detailedChassis.frameFR.r_0[3] = chassis.detailedChassis.frAxleDW.rightTire.wheelModel.wheelVelSensor.der1[3].u - chassis.detailedChassis.frameFR.R.T[3,3] * chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.s
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5184(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5184};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6091]] /* chassis.detailedChassis.frameFR.r_0[3] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5038]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.wheelVelSensor.der1[3].u DUMMY_STATE */) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6085]] /* chassis.detailedChassis.frameFR.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4982]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.s DUMMY_STATE */)));
  threadData->lastEquationSolved = 5184;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31774(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31775(DATA *data, threadData_t *threadData);


/*
equation index: 5187
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.e_zw[3] = chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,1] * chassis.detailedChassis.frameFR.R.T[1,3] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,2] * chassis.detailedChassis.frameFR.R.T[2,3] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,3] * chassis.detailedChassis.frameFR.R.T[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5187(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5187};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4860]] /* chassis.detailedChassis.frAxleDW.rightTire.e_zw[3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4931]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6079]] /* chassis.detailedChassis.frameFR.R.T[1,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4932]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6082]] /* chassis.detailedChassis.frameFR.R.T[2,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4933]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6085]] /* chassis.detailedChassis.frameFR.R.T[3,3] DUMMY_STATE */));
  threadData->lastEquationSolved = 5187;
}

/*
equation index: 5188
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.e_zw[2] = chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,1] * chassis.detailedChassis.frameFR.R.T[1,3] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,2] * chassis.detailedChassis.frameFR.R.T[2,3] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,3] * chassis.detailedChassis.frameFR.R.T[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5188(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5188};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4859]] /* chassis.detailedChassis.frAxleDW.rightTire.e_zw[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4928]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6079]] /* chassis.detailedChassis.frameFR.R.T[1,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4929]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6082]] /* chassis.detailedChassis.frameFR.R.T[2,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4930]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6085]] /* chassis.detailedChassis.frameFR.R.T[3,3] DUMMY_STATE */));
  threadData->lastEquationSolved = 5188;
}

/*
equation index: 5189
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.gamma = asin(max(-1.0, min(1.0, chassis.detailedChassis.frAxleDW.rightTire.e_zw[2])))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5189(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5189};
  modelica_real tmp752;
  tmp752 = fmax(-1.0,fmin(1.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4859]] /* chassis.detailedChassis.frAxleDW.rightTire.e_zw[2] variable */)));
  if(!(tmp752 >= -1.0 && tmp752 <= 1.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of asin(max(-1.0, min(1.0, chassis.detailedChassis.frAxleDW.rightTire.e_zw[2]))) outside the domain -1.0 <= %g <= 1.0", tmp752);
    }
  }
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4900]] /* chassis.detailedChassis.frAxleDW.rightTire.gamma variable */) = asin(tmp752);
  threadData->lastEquationSolved = 5189;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33195(DATA *data, threadData_t *threadData);


/*
equation index: 5191
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.e_spin[3] = chassis.detailedChassis.frAxleDW.rightTire.e_zw[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5191(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5191};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4845]] /* chassis.detailedChassis.frAxleDW.rightTire.e_spin[3] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4859]] /* chassis.detailedChassis.frAxleDW.rightTire.e_zw[2] variable */);
  threadData->lastEquationSolved = 5191;
}

/*
equation index: 5192
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.e_zw[1] = chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,1] * chassis.detailedChassis.frameFR.R.T[1,3] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,2] * chassis.detailedChassis.frameFR.R.T[2,3] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,3] * chassis.detailedChassis.frameFR.R.T[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5192(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5192};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4858]] /* chassis.detailedChassis.frAxleDW.rightTire.e_zw[1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4925]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6079]] /* chassis.detailedChassis.frameFR.R.T[1,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4926]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6082]] /* chassis.detailedChassis.frameFR.R.T[2,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4927]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6085]] /* chassis.detailedChassis.frameFR.R.T[3,3] DUMMY_STATE */));
  threadData->lastEquationSolved = 5192;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31457(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31453(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31456(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31455(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31454(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31462(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31458(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31461(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31460(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31459(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31776(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31463(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31797(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31796(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31798(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31803(DATA *data, threadData_t *threadData);


/*
equation index: 5209
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.w_a[1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,3] * yawVel + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.w[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5209(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5209};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5210]] /* chassis.detailedChassis.frAxleDW.rightUCABody.w_a[1] DUMMY_STATE */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5593]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5594]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5595]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5602]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.w[1] DUMMY_STATE */);
  threadData->lastEquationSolved = 5209;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31801(DATA *data, threadData_t *threadData);


/*
equation index: 5211
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.w_a[2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,3] * yawVel + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.w[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5211(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5211};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5211]] /* chassis.detailedChassis.frAxleDW.rightUCABody.w_a[2] DUMMY_STATE */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5596]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5597]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5598]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5603]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.w[2] DUMMY_STATE */);
  threadData->lastEquationSolved = 5211;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31799(DATA *data, threadData_t *threadData);


/*
equation index: 5213
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.w_a[3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,3] * yawVel + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.w[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5213(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5213};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5212]] /* chassis.detailedChassis.frAxleDW.rightUCABody.w_a[3] DUMMY_STATE */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5599]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5600]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5601]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5604]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.w[3] DUMMY_STATE */);
  threadData->lastEquationSolved = 5213;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31811(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31831(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31812(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31808(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31809(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31810(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31805(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31806(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31855(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31856(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31848(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31849(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31833(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31834(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31850(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31851(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31853(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31864(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31852(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31860(DATA *data, threadData_t *threadData);


/*
equation index: 5234
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[1,2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] + $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] + $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5234(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5234};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1333]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[1,2]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5649]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1359]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1344]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5669]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5650]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1353]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1345]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5663]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2239]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1356]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[2]) DUMMY_DER */));
  threadData->lastEquationSolved = 5234;
}

/*
equation index: 5235
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[2,2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] + $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] + $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5235(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5235};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1336]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[2,2]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5651]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1359]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1346]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5669]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5652]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1353]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1347]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5663]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2240]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1356]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[2]) DUMMY_DER */));
  threadData->lastEquationSolved = 5235;
}

/*
equation index: 5236
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[3,2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] + $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] + $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5236(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5236};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1339]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[3,2]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5653]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1359]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1348]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5669]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5654]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1353]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1349]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5663]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2241]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1356]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[2]) DUMMY_DER */));
  threadData->lastEquationSolved = 5236;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31854(DATA *data, threadData_t *threadData);


/*
equation index: 5238
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[1,1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] + $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5238(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5238};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1332]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[1,1]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5649]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1358]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1344]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5668]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2239]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1355]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[1]) DUMMY_DER */));
  threadData->lastEquationSolved = 5238;
}

/*
equation index: 5239
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[2,1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] + $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5239(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5239};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1335]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[2,1]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5651]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1358]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1346]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5668]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2240]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1355]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[1]) DUMMY_DER */));
  threadData->lastEquationSolved = 5239;
}

/*
equation index: 5240
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[3,1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] + $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5240(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5240};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1338]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[3,1]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5653]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1358]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1348]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5668]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2241]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1355]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[1]) DUMMY_DER */));
  threadData->lastEquationSolved = 5240;
}

/*
equation index: 5241
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[1,3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] + $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] + $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5241(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5241};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1334]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[1,3]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5649]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1360]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1344]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5670]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5650]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1354]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1345]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5664]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2239]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1357]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[3]) DUMMY_DER */));
  threadData->lastEquationSolved = 5241;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31883(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31887(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32057(DATA *data, threadData_t *threadData);


/*
equation index: 5245
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[2,3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] + $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] + $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5245(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5245};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1337]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[2,3]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5651]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1360]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1346]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5670]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5652]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1354]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1347]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5664]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2240]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1357]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[3]) DUMMY_DER */));
  threadData->lastEquationSolved = 5245;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31882(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31886(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32056(DATA *data, threadData_t *threadData);


/*
equation index: 5249
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[3,3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] + $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] + $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2] * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5249(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5249};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1340]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[3,3]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5653]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1360]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1348]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5670]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5654]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1354]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1349]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5664]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2241]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1357]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[3]) DUMMY_DER */));
  threadData->lastEquationSolved = 5249;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31881(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31885(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32055(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31840(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31837(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31832(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31839(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31841(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31838(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31844(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31847(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31843(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31846(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31842(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31845(DATA *data, threadData_t *threadData);


/*
equation index: 5326
type: LINEAR

<var>chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.w</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5326(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5326};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[data->simulationInfo->realVarsIndex[5445]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.w DUMMY_STATE */) };
  infoStreamPrint(OMC_LOG_DT, 0, "Solving linear system 5326 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);

  retValue = solve_linear_system(data, threadData, 21, &aux_x[0]);

  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,5326};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 5326 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5445]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.w DUMMY_STATE */) = aux_x[0];

  threadData->lastEquationSolved = 5326;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32154(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32119(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32120(DATA *data, threadData_t *threadData);


/*
equation index: 5330
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieRod.rod.der_rRod_a_L[3] = (chassis.chassisFrame.R.T[3,1] * $DER.chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[1] + chassis.chassisFrame.R.T[3,2] * $DER.chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[2] + chassis.chassisFrame.R.T[3,3] * $DER.chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[3] + chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[1] - chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[2]) / chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5330(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5330};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4721]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.der_rRod_a_L[3] variable */) = DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1218]] /* der(chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1219]] /* der(chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1220]] /* der(chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4756]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[1] variable */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4757]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[2] variable */))),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1710]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength PARAM */),"chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength",equationIndexes);
  threadData->lastEquationSolved = 5330;
}

/*
equation index: 5331
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieRod.rod.der_rRod_a_L[2] = (chassis.chassisFrame.R.T[2,1] * $DER.chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[1] + chassis.chassisFrame.R.T[2,2] * $DER.chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[2] + chassis.chassisFrame.R.T[2,3] * $DER.chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[3] + chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[3] - yawVel * chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[1]) / chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5331(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5331};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4720]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.der_rRod_a_L[2] variable */) = DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1218]] /* der(chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1219]] /* der(chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1220]] /* der(chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4758]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[3] variable */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4756]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[1] variable */))),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1710]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength PARAM */),"chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength",equationIndexes);
  threadData->lastEquationSolved = 5331;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32160(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32158(DATA *data, threadData_t *threadData);


/*
equation index: 5334
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieRod.rod.der_rRod_a_L[1] = (chassis.chassisFrame.R.T[1,1] * $DER.chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[1] + chassis.chassisFrame.R.T[1,2] * $DER.chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[2] + chassis.chassisFrame.R.T[1,3] * $DER.chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[3] + yawVel * chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[2] - chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[3]) / chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5334(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5334};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4719]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.der_rRod_a_L[1] variable */) = DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1218]] /* der(chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1219]] /* der(chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1220]] /* der(chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4757]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[2] variable */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4758]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[3] variable */))),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1710]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength PARAM */),"chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodLength",equationIndexes);
  threadData->lastEquationSolved = 5334;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32159(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32165(DATA *data, threadData_t *threadData);


/*
equation index: 5337
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodShape.R.w[3] = chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.T[3,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.T[3,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.T[3,3] * yawVel + chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.w[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5337(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5337};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4770]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodShape.R.w[3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4703]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.T[3,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4704]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.T[3,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4705]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.T[3,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4708]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.w[3] variable */);
  threadData->lastEquationSolved = 5337;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32163(DATA *data, threadData_t *threadData);


/*
equation index: 5339
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodShape.R.w[2] = chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.T[2,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.T[2,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.T[2,3] * yawVel + chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.w[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5339(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5339};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4769]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodShape.R.w[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4700]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.T[2,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4701]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.T[2,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4702]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.T[2,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4707]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.w[2] variable */);
  threadData->lastEquationSolved = 5339;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32161(DATA *data, threadData_t *threadData);


/*
equation index: 5341
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodShape.R.w[1] = chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.T[1,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.T[1,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.T[1,3] * yawVel + chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.w[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5341(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5341};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4768]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodShape.R.w[1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4697]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.T[1,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4698]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.T[1,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4699]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.T[1,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4706]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.R_rel_ia.w[1] variable */);
  threadData->lastEquationSolved = 5341;
}

/*
equation index: 5342
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.v_0[1] = chassis.detailedChassis.frAxleDW.rightLCABody.v_0[1] + chassis.detailedChassis.frameFR.R.T[1,1] * (chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[2] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3] - chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[3] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2]) + chassis.detailedChassis.frameFR.R.T[2,1] * (chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[3] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1] - chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3]) + chassis.detailedChassis.frameFR.R.T[3,1] * (chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2] - chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[2] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5342(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5342};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5270]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.v_0[1] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4449]] /* chassis.detailedChassis.frAxleDW.rightLCABody.v_0[1] DUMMY_STATE */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6077]] /* chassis.detailedChassis.frameFR.R.T[1,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5274]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2570]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5275]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2569]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6080]] /* chassis.detailedChassis.frameFR.R.T[2,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5275]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2568]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5273]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2570]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6083]] /* chassis.detailedChassis.frameFR.R.T[3,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5273]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2569]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5274]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2568]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1] PARAM */))));
  threadData->lastEquationSolved = 5342;
}

/*
equation index: 5343
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightUnsprungBody.frame_a.r_0[1] = chassis.detailedChassis.frAxleDW.rightUnsprungBody.v_0[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5343(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5343};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1249]] /* der(chassis.detailedChassis.frAxleDW.rightUnsprungBody.frame_a.r_0[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5270]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.v_0[1] DUMMY_STATE */);
  threadData->lastEquationSolved = 5343;
}

/*
equation index: 5344
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.v_g[1] = chassis.detailedChassis.frAxleDW.rightUnsprungBody.v_0[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5344(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5344};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4921]] /* chassis.detailedChassis.frAxleDW.rightTire.v_g[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5270]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.v_0[1] DUMMY_STATE */);
  threadData->lastEquationSolved = 5344;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32137(DATA *data, threadData_t *threadData);


/*
equation index: 5346
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.v_0[2] = chassis.detailedChassis.frAxleDW.rightLCABody.v_0[2] + chassis.detailedChassis.frameFR.R.T[1,2] * (chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[2] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3] - chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[3] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2]) + chassis.detailedChassis.frameFR.R.T[2,2] * (chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[3] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1] - chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3]) + chassis.detailedChassis.frameFR.R.T[3,2] * (chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2] - chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[2] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5346(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5346};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5271]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.v_0[2] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4450]] /* chassis.detailedChassis.frAxleDW.rightLCABody.v_0[2] DUMMY_STATE */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6078]] /* chassis.detailedChassis.frameFR.R.T[1,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5274]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2570]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5275]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2569]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6081]] /* chassis.detailedChassis.frameFR.R.T[2,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5275]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2568]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5273]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2570]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6084]] /* chassis.detailedChassis.frameFR.R.T[3,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5273]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2569]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5274]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2568]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1] PARAM */))));
  threadData->lastEquationSolved = 5346;
}

/*
equation index: 5347
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightUnsprungBody.frame_a.r_0[2] = chassis.detailedChassis.frAxleDW.rightUnsprungBody.v_0[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5347(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5347};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1250]] /* der(chassis.detailedChassis.frAxleDW.rightUnsprungBody.frame_a.r_0[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5271]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.v_0[2] DUMMY_STATE */);
  threadData->lastEquationSolved = 5347;
}

/*
equation index: 5348
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.v_g[2] = chassis.detailedChassis.frAxleDW.rightUnsprungBody.v_0[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5348(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5348};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4922]] /* chassis.detailedChassis.frAxleDW.rightTire.v_g[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5271]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.v_0[2] DUMMY_STATE */);
  threadData->lastEquationSolved = 5348;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32134(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32130(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32133(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32132(DATA *data, threadData_t *threadData);


/*
equation index: 5353
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.slipModel.Vsx = chassis.detailedChassis.frAxleDW.rightTire.slipModel.Vx - chassis.detailedChassis.frAxleDW.rightTire.slipModel.R0 * chassis.detailedChassis.frAxleDW.rightTire.slipModel.omega
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5353(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5353};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4907]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.Vsx variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4908]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.Vx variable */) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4906]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.R0 variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4916]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.omega variable */)));
  threadData->lastEquationSolved = 5353;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32128(DATA *data, threadData_t *threadData);


/*
equation index: 5355
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.v_0[3] = chassis.detailedChassis.frAxleDW.rightLCABody.v_0[3] + chassis.detailedChassis.frameFR.R.T[1,3] * (chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[2] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3] - chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[3] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2]) + chassis.detailedChassis.frameFR.R.T[2,3] * (chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[3] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1] - chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3]) + chassis.detailedChassis.frameFR.R.T[3,3] * (chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2] - chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[2] * chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5355(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5355};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5272]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.v_0[3] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4451]] /* chassis.detailedChassis.frAxleDW.rightLCABody.v_0[3] DUMMY_STATE */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6079]] /* chassis.detailedChassis.frameFR.R.T[1,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5274]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2570]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5275]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2569]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6082]] /* chassis.detailedChassis.frameFR.R.T[2,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5275]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2568]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5273]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2570]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6085]] /* chassis.detailedChassis.frameFR.R.T[3,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5273]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2569]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5274]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2568]] /* chassis.detailedChassis.frAxleDW.toRightWheelCenter.r[1] PARAM */))));
  threadData->lastEquationSolved = 5355;
}

/*
equation index: 5356
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightUnsprungBody.frame_a.r_0[3] = chassis.detailedChassis.frAxleDW.rightUnsprungBody.v_0[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5356(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5356};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1251]] /* der(chassis.detailedChassis.frAxleDW.rightUnsprungBody.frame_a.r_0[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5272]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.v_0[3] DUMMY_STATE */);
  threadData->lastEquationSolved = 5356;
}

/*
equation index: 5357
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.v_cp[3] = chassis.detailedChassis.frAxleDW.rightUnsprungBody.v_0[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5357(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5357};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4920]] /* chassis.detailedChassis.frAxleDW.rightTire.v_cp[3] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5272]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.v_0[3] DUMMY_STATE */);
  threadData->lastEquationSolved = 5357;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32124(DATA *data, threadData_t *threadData);


/*
equation index: 5359
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frameFR.r_0[3] = chassis.detailedChassis.frAxleDW.rightTire.v_cp[3] + chassis.detailedChassis.frameFR.R.T[1,3] * (-chassis.detailedChassis.frameFR.R.w[2]) * chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.s + chassis.detailedChassis.frameFR.R.T[2,3] * chassis.detailedChassis.frameFR.R.w[1] * chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.s
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5359(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5359};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1431]] /* der(chassis.detailedChassis.frameFR.r_0[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4920]] /* chassis.detailedChassis.frAxleDW.rightTire.v_cp[3] variable */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6079]] /* chassis.detailedChassis.frameFR.R.T[1,3] DUMMY_STATE */)) * (((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6087]] /* chassis.detailedChassis.frameFR.R.w[2] variable */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4982]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.s DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6082]] /* chassis.detailedChassis.frameFR.R.T[2,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6086]] /* chassis.detailedChassis.frameFR.R.w[1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4982]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.s DUMMY_STATE */)));
  threadData->lastEquationSolved = 5359;
}

/*
equation index: 5360
type: SIMPLE_ASSIGN
$DER.chassis.ground_2.r_rel_z = $DER.chassis.detailedChassis.frameFR.r_0[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5360(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5360};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2016]] /* der(chassis.ground_2.r_rel_z) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1431]] /* der(chassis.detailedChassis.frameFR.r_0[3]) DUMMY_DER */);
  threadData->lastEquationSolved = 5360;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32139(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32140(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32141(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32142(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32143(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33196(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32144(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32145(DATA *data, threadData_t *threadData);


/*
equation index: 5369
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.f = chassis.detailedChassis.frAxleDW.rightTire.constantZero.k + chassis.ground_2.f_z
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5369(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5369};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4979]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.f variable */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1713]] /* chassis.detailedChassis.frAxleDW.rightTire.constantZero.k PARAM */) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10079]] /* chassis.ground_2.f_z variable */);
  threadData->lastEquationSolved = 5369;
}

/*
equation index: 5370
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.f[3] = chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.f - chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.frame_a.f[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5370(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5370};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4991]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.f[3] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4979]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.f variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4949]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.frame_a.f[3] variable */);
  threadData->lastEquationSolved = 5370;
}

/*
equation index: 5371
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.chassisFrame.f[3] = -chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.f[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5371(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5371};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4836]] /* chassis.detailedChassis.frAxleDW.rightTire.chassisFrame.f[3] variable */) = (-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4991]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.f[3] variable */));
  threadData->lastEquationSolved = 5371;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32118(DATA *data, threadData_t *threadData);


/*
equation index: 5373
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.w[3] = chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,1] * chassis.detailedChassis.frameFR.R.w[1] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,2] * chassis.detailedChassis.frameFR.R.w[2] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,3] * chassis.detailedChassis.frameFR.R.w[3] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.w[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5373(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5373};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5033]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.w[3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4931]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6086]] /* chassis.detailedChassis.frameFR.R.w[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4932]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6087]] /* chassis.detailedChassis.frameFR.R.w[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4933]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6088]] /* chassis.detailedChassis.frameFR.R.w[3] variable */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4936]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.w[3] variable */);
  threadData->lastEquationSolved = 5373;
}

/*
equation index: 5374
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.w[2] = chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,1] * chassis.detailedChassis.frameFR.R.w[1] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,2] * chassis.detailedChassis.frameFR.R.w[2] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,3] * chassis.detailedChassis.frameFR.R.w[3] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.w[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5374(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5374};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5032]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.w[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4928]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6086]] /* chassis.detailedChassis.frameFR.R.w[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4929]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6087]] /* chassis.detailedChassis.frameFR.R.w[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4930]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6088]] /* chassis.detailedChassis.frameFR.R.w[3] variable */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4935]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.w[2] variable */);
  threadData->lastEquationSolved = 5374;
}

/*
equation index: 5375
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.w[1] = chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,1] * chassis.detailedChassis.frameFR.R.w[1] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,2] * chassis.detailedChassis.frameFR.R.w[2] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,3] * chassis.detailedChassis.frameFR.R.w[3] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.w[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5375(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5375};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5031]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.voluminousWheel.torus.R.w[1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4925]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6086]] /* chassis.detailedChassis.frameFR.R.w[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4926]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6087]] /* chassis.detailedChassis.frameFR.R.w[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4927]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6088]] /* chassis.detailedChassis.frameFR.R.w[3] variable */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4934]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.w[1] variable */);
  threadData->lastEquationSolved = 5375;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31807(DATA *data, threadData_t *threadData);


/*
equation index: 5377
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,3] = (1.0 - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] ^ 2.0) * (-sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5377(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5377};
  modelica_real tmp753;
  tmp753 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1313]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,3]) DUMMY_DER */) = (1.0 - ((tmp753 * tmp753))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1317]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)));
  threadData->lastEquationSolved = 5377;
}

/*
equation index: 5378
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,2] = (-chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3]) * (-sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5378(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5378};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1312]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,2]) DUMMY_DER */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1317]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1317]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */))));
  threadData->lastEquationSolved = 5378;
}

/*
equation index: 5379
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * (-sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5379(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5379};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1311]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,1]) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1317]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1317]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)))));
  threadData->lastEquationSolved = 5379;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31818(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31817(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31816(DATA *data, threadData_t *threadData);


/*
equation index: 5383
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * (-sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5383(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5383};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1310]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,3]) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1317]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1317]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)))));
  threadData->lastEquationSolved = 5383;
}

/*
equation index: 5384
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,2] = (1.0 - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] ^ 2.0) * (-sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5384(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5384};
  modelica_real tmp754;
  tmp754 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1309]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,2]) DUMMY_DER */) = (1.0 - ((tmp754 * tmp754))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1317]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)));
  threadData->lastEquationSolved = 5384;
}

/*
equation index: 5385
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,1] = (-chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2]) * (-sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5385(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5385};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1308]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,1]) DUMMY_DER */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1317]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1317]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */))));
  threadData->lastEquationSolved = 5385;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31824(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31823(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31822(DATA *data, threadData_t *threadData);


/*
equation index: 5389
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,3] = (-chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1]) * (-sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5389(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5389};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1307]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,3]) DUMMY_DER */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1317]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1317]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */))));
  threadData->lastEquationSolved = 5389;
}

/*
equation index: 5390
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * cos(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * (-sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5390(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5390};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1306]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,2]) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2225]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1317]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1317]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2224]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)))));
  threadData->lastEquationSolved = 5390;
}

/*
equation index: 5391
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,1] = (1.0 - chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] ^ 2.0) * (-sin(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5391(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5391};
  modelica_real tmp755;
  tmp755 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2223]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1305]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,1]) DUMMY_DER */) = (1.0 - ((tmp755 * tmp755))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5605]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1317]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)));
  threadData->lastEquationSolved = 5391;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31830(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31829(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31828(DATA *data, threadData_t *threadData);


/*
equation index: 5395
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodLength = 0.155908214617319
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5395(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5395};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1164]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodLength PARAM */) = 0.155908214617319;
  threadData->lastEquationSolved = 5395;
}

/*
equation index: 5396
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1Length = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5396(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5396};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1168]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1Length PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1164]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodLength PARAM */);
  threadData->lastEquationSolved = 5396;
}

/*
equation index: 5397
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.lengthConstraint = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1Length
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5397(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5397};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1137]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.lengthConstraint PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1168]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1Length PARAM */);
  threadData->lastEquationSolved = 5397;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32196(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32199(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32200(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32201(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32743(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32744(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32745(DATA *data, threadData_t *threadData);


/*
equation index: 5405
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.positiveBranch = BobLib.Experiments.Standards.VehicleSim.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.selectBranch(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.lengthConstraint, chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e, 0.017453292519943295 * (chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.phi_offset + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.phi_guess), chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_a, chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5405(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5405};
  real_array tmp756;
  real_array tmp757;
  real_array tmp758;
  real_array_create(&tmp756, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1134]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp757, ((modelica_real*)&((&data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3880]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_a[1] DUMMY_STATE */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp758, ((modelica_real*)&((&data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3883]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] variable */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  (data->simulationInfo->booleanParameter[data->simulationInfo->booleanParamsIndex[128]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.positiveBranch PARAM */) = omc_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_frAxleDW_leftWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1137]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.lengthConstraint PARAM */), tmp756, (0.017453292519943295) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1142]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.phi_offset PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1141]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.phi_guess PARAM */)), tmp757, tmp758);
  threadData->lastEquationSolved = 5405;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32203(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32202(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32204(DATA *data, threadData_t *threadData);


/*
equation index: 5409
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,1] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] ^ 2.0 + (1.0 - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] ^ 2.0) * cos(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5409(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5409};
  modelica_real tmp759;
  modelica_real tmp760;
  tmp759 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1134]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */);
  tmp760 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1134]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3841]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,1] DUMMY_STATE */) = (tmp759 * tmp759) + (1.0 - ((tmp760 * tmp760))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 5409;
}

/*
equation index: 5410
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,2] = (chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * cos(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * sin(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5410(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5410};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3842]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,2] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1134]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1134]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1135]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1136]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 5410;
}

/*
equation index: 5411
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,3] = (chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * cos(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * sin(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5411(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5411};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3843]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,3] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1134]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1134]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1136]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1135]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))));
  threadData->lastEquationSolved = 5411;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32212(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32213(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32214(DATA *data, threadData_t *threadData);


/*
equation index: 5415
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,1] = (chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * cos(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * sin(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5415(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5415};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3844]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,1] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1135]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1135]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1134]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1136]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))));
  threadData->lastEquationSolved = 5415;
}

/*
equation index: 5416
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,2] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] ^ 2.0 + (1.0 - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] ^ 2.0) * cos(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5416(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5416};
  modelica_real tmp761;
  modelica_real tmp762;
  tmp761 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1135]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */);
  tmp762 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1135]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3845]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,2] DUMMY_STATE */) = (tmp761 * tmp761) + (1.0 - ((tmp762 * tmp762))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 5416;
}

/*
equation index: 5417
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,3] = (chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * cos(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * sin(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5417(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5417};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3846]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,3] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1135]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1135]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1136]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1134]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 5417;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32217(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32218(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32219(DATA *data, threadData_t *threadData);


/*
equation index: 5421
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,1] = (chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * cos(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * sin(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5421(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5421};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3847]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,1] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1136]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1136]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1134]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1135]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 5421;
}

/*
equation index: 5422
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,2] = (chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * cos(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * sin(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5422(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5422};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3848]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,2] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1136]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1136]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1135]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1134]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))));
  threadData->lastEquationSolved = 5422;
}

/*
equation index: 5423
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,3] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] ^ 2.0 + (1.0 - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] ^ 2.0) * cos(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5423(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5423};
  modelica_real tmp763;
  modelica_real tmp764;
  tmp763 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1136]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */);
  tmp764 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1136]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3849]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,3] DUMMY_STATE */) = (tmp763 * tmp763) + (1.0 - ((tmp764 * tmp764))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)));
  threadData->lastEquationSolved = 5423;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32222(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32223(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32224(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32225(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32226(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32227(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32228(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32229(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32241(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32244(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32245(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32575(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32576(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32242(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32243(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32577(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32578(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32581(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32585(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32579(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32580(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32596(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32593(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32590(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32586(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32589(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32588(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32587(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32584(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32598(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32597(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32601(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32583(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32595(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32594(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32600(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32582(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32592(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32591(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32599(DATA *data, threadData_t *threadData);


void BobLib_Experiments_Standards_VehicleSim_eqFunction_5464(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5465(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5466(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5467(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5468(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5469(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5470(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5471(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5472(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5473(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5474(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5475(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5476(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5477(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5478(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5479(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5480(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5481(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5482(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5483(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5484(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5485(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5486(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5487(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5488(DATA*, threadData_t*);
/*
equation index: 5516
indexNonlinear: 13
type: NONLINEAR

vars: {chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.steeringAxis.phi}
eqns: {5464, 5465, 5466, 5467, 5468, 5469, 5470, 5471, 5472, 5473, 5474, 5475, 5476, 5477, 5478, 5479, 5480, 5481, 5482, 5483, 5484, 5485, 5486, 5487, 5488}
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5516(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5516};
  int retValue;
  infoStreamPrint(OMC_LOG_DT, 0, "Solving nonlinear system 5516 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
  /* get old value */
  data->simulationInfo->nonlinearSystemData[13].nlsxOld[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3689]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.steeringAxis.phi DUMMY_STATE */);
  retValue = solve_nonlinear_system(data, threadData, 13);
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,5516};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving non-linear system 5516 failed at time=%.15g.\nFor more information please use -lv LOG_NLS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3689]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.steeringAxis.phi DUMMY_STATE */) = data->simulationInfo->nonlinearSystemData[13].nlsx[0];
  threadData->lastEquationSolved = 5516;
}

/*
equation index: 5517
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.e_xw[1] = chassis.detailedChassis.frameFL.R.T[1,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5517(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5517};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3086]] /* chassis.detailedChassis.frAxleDW.leftTire.e_xw[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6059]] /* chassis.detailedChassis.frameFL.R.T[1,1] DUMMY_STATE */);
  threadData->lastEquationSolved = 5517;
}

/*
equation index: 5518
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.e_xw[2] = chassis.detailedChassis.frameFL.R.T[1,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5518(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5518};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3087]] /* chassis.detailedChassis.frAxleDW.leftTire.e_xw[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6060]] /* chassis.detailedChassis.frameFL.R.T[1,2] DUMMY_STATE */);
  threadData->lastEquationSolved = 5518;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32660(DATA *data, threadData_t *threadData);


/*
equation index: 5520
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.e_xw[3] = chassis.detailedChassis.frameFL.R.T[1,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5520(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5520};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3088]] /* chassis.detailedChassis.frAxleDW.leftTire.e_xw[3] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6061]] /* chassis.detailedChassis.frameFL.R.T[1,3] DUMMY_STATE */);
  threadData->lastEquationSolved = 5520;
}

/*
equation index: 5521
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.e_yw[1] = chassis.detailedChassis.frameFL.R.T[2,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5521(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5521};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3092]] /* chassis.detailedChassis.frAxleDW.leftTire.e_yw[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6062]] /* chassis.detailedChassis.frameFL.R.T[2,1] DUMMY_STATE */);
  threadData->lastEquationSolved = 5521;
}

/*
equation index: 5522
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.e_yw[2] = chassis.detailedChassis.frameFL.R.T[2,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5522(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5522};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3093]] /* chassis.detailedChassis.frAxleDW.leftTire.e_yw[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6063]] /* chassis.detailedChassis.frameFL.R.T[2,2] DUMMY_STATE */);
  threadData->lastEquationSolved = 5522;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32665(DATA *data, threadData_t *threadData);


/*
equation index: 5524
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.e_yw[3] = chassis.detailedChassis.frameFL.R.T[2,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5524(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5524};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3094]] /* chassis.detailedChassis.frAxleDW.leftTire.e_yw[3] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6064]] /* chassis.detailedChassis.frameFL.R.T[2,3] DUMMY_STATE */);
  threadData->lastEquationSolved = 5524;
}

/*
equation index: 5525
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUnsprungBody.frame_a.r_0[1] = chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[1] + (-0.0029972) * chassis.detailedChassis.frameFL.R.T[1,1] + 0.04311976745599999 * chassis.detailedChassis.frameFL.R.T[2,1] + 0.08590279999999999 * chassis.detailedChassis.frameFL.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5525(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5525};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3484]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.frame_a.r_0[1] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2647]] /* chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[1] DUMMY_STATE */) + (-0.0029972) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6059]] /* chassis.detailedChassis.frameFL.R.T[1,1] DUMMY_STATE */)) + (0.04311976745599999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6062]] /* chassis.detailedChassis.frameFL.R.T[2,1] DUMMY_STATE */)) + (0.08590279999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6065]] /* chassis.detailedChassis.frameFL.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 5525;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32668(DATA *data, threadData_t *threadData);


/*
equation index: 5527
type: SIMPLE_ASSIGN
chassis.leftWheelVector[3] = chassis.chassisFrame.R.T[1,3] * chassis.detailedChassis.frameFL.R.T[1,1] + chassis.chassisFrame.R.T[2,3] * chassis.detailedChassis.frameFL.R.T[2,1] + chassis.chassisFrame.R.T[3,3] * chassis.detailedChassis.frameFL.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5527(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5527};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10122]] /* chassis.leftWheelVector[3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6059]] /* chassis.detailedChassis.frameFL.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6062]] /* chassis.detailedChassis.frameFL.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6065]] /* chassis.detailedChassis.frameFL.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 5527;
}

/*
equation index: 5528
type: SIMPLE_ASSIGN
chassis.leftWheelVector[2] = chassis.chassisFrame.R.T[1,2] * chassis.detailedChassis.frameFL.R.T[1,1] + chassis.chassisFrame.R.T[2,2] * chassis.detailedChassis.frameFL.R.T[2,1] + chassis.chassisFrame.R.T[3,2] * chassis.detailedChassis.frameFL.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5528(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5528};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10121]] /* chassis.leftWheelVector[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6059]] /* chassis.detailedChassis.frameFL.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6062]] /* chassis.detailedChassis.frameFL.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6065]] /* chassis.detailedChassis.frameFL.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 5528;
}

/*
equation index: 5529
type: SIMPLE_ASSIGN
chassis.leftWheelVector[1] = chassis.chassisFrame.R.T[1,1] * chassis.detailedChassis.frameFL.R.T[1,1] + chassis.chassisFrame.R.T[2,1] * chassis.detailedChassis.frameFL.R.T[2,1] + chassis.chassisFrame.R.T[3,1] * chassis.detailedChassis.frameFL.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5529(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5529};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10120]] /* chassis.leftWheelVector[1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6059]] /* chassis.detailedChassis.frameFL.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6062]] /* chassis.detailedChassis.frameFL.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6065]] /* chassis.detailedChassis.frameFL.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 5529;
}
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_functionInitialEquations_7(DATA *data, threadData_t *threadData)
{
  static void (*const eqFunctions[494])(DATA*, threadData_t*) = {
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32518,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32516,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32519,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32515,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32517,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32520,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4720,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4721,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32509,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4723,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32507,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32510,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32522,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32526,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32531,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32528,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32530,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32529,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32527,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32532,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32410,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32411,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32533,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32537,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32535,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4800,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4801,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33025,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4803,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33022,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4805,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33019,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33026,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33027,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33028,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33029,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33030,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4812,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4813,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4814,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33036,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4816,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33034,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33037,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4819,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33043,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33044,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4822,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33041,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33045,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33038,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33039,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33042,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33046,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33093,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4830,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4831,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4832,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33095,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4901,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33162,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32540,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4904,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32545,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33165,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4907,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33163,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32541,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32543,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32544,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32546,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32548,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32547,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32549,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32550,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32553,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32552,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32554,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32551,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32571,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32567,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32563,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33168,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32559,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32562,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32561,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32560,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32555,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4930,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4931,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4932,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4962,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33078,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33077,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33076,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33082,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33080,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33083,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33079,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33081,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33084,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4972,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4973,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33089,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4975,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33087,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33090,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32558,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4979,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4980,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4981,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32557,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4983,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4984,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4985,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32556,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4987,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4988,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4989,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33167,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33166,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33173,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33174,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33171,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33172,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33169,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33170,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4998,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_4999,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5000,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5001,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5002,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5003,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31422,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31423,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31424,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31793,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31794,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31795,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5010,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31426,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31425,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31427,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5014,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5015,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5016,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31435,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31436,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31437,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5020,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5021,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5022,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31440,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31441,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31442,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5026,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5027,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5028,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31445,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31446,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31447,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31448,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31449,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31450,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31451,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31452,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31464,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31467,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31468,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31465,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31466,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31637,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31638,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31639,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31640,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31641,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31642,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31643,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31644,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31647,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31646,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31645,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31648,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31651,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31650,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31649,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31658,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31660,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31659,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31663,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31655,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31657,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31656,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31662,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31652,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31654,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31653,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31661,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5121,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5122,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5123,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31722,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5125,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5126,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31730,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5128,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5129,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5130,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5131,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5132,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5133,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5134,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5135,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5136,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5137,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5138,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5139,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31738,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5141,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5142,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31726,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5144,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5145,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5146,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5147,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31740,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31741,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31742,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31743,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31744,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31745,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31747,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31746,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31748,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5157,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31749,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31750,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31767,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31763,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31759,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31755,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5164,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31758,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31757,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31756,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31751,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5169,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31754,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31770,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31769,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31768,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31753,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31766,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31765,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31764,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31752,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31762,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31761,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31760,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5182,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31772,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5184,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31774,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31775,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5187,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5188,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5189,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33195,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5191,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5192,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31457,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31453,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31456,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31455,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31454,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31462,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31458,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31461,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31460,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31459,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31776,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31463,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31797,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31796,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31798,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31803,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5209,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31801,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5211,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31799,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5213,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31811,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31831,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31812,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31808,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31809,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31810,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31805,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31806,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31855,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31856,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31848,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31849,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31833,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31834,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31850,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31851,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31853,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31864,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31852,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31860,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5234,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5235,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5236,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31854,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5238,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5239,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5240,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5241,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31883,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31887,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32057,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5245,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31882,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31886,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32056,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5249,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31881,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31885,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32055,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31840,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31837,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31832,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31839,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31841,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31838,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31844,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31847,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31843,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31846,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31842,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31845,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5326,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32154,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32119,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32120,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5330,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5331,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32160,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32158,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5334,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32159,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32165,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5337,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32163,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5339,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32161,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5341,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5342,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5343,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5344,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32137,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5346,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5347,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5348,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32134,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32130,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32133,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32132,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5353,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32128,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5355,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5356,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5357,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32124,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5359,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5360,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32139,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32140,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32141,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32142,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32143,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33196,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32144,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32145,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5369,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5370,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5371,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32118,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5373,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5374,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5375,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31807,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5377,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5378,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5379,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31818,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31817,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31816,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5383,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5384,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5385,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31824,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31823,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31822,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5389,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5390,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5391,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31830,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31829,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31828,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5395,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5396,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5397,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32196,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32199,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32200,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32201,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32743,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32744,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32745,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5405,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32203,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32202,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32204,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5409,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5410,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5411,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32212,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32213,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32214,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5415,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5416,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5417,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32217,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32218,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32219,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5421,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5422,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5423,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32222,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32223,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32224,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32225,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32226,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32227,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32228,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32229,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32241,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32244,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32245,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32575,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32576,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32242,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32243,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32577,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32578,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32581,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32585,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32579,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32580,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32596,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32593,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32590,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32586,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32589,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32588,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32587,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32584,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32598,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32597,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32601,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32583,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32595,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32594,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32600,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32582,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32592,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32591,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32599,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5516,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5517,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5518,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32660,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5520,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5521,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5522,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32665,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5524,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5525,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32668,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5527,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5528,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5529
  };
  
  for (int id = 0; id < 494; id++) {
    eqFunctions[id](data, threadData);
  }
}
#if defined(__cplusplus)
}
#endif