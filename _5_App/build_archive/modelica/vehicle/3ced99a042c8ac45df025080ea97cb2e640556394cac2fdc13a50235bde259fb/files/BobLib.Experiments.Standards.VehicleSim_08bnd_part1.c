#include "BobLib.Experiments.Standards.VehicleSim_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/*
equation index: 37571
type: SIMPLE_ASSIGN
inverter.P_max_reg = pVehicle.pInverter.P_max_reg
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37571(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37571};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5920]] /* inverter.P_max_reg PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6492]] /* pVehicle.pInverter.P_max_reg PARAM */);
  threadData->lastEquationSolved = 37571;
}

/*
equation index: 37572
type: SIMPLE_ASSIGN
inverter.inverter.P_max_reg = inverter.P_max_reg
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37572(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37572};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5947]] /* inverter.inverter.P_max_reg PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5920]] /* inverter.P_max_reg PARAM */);
  threadData->lastEquationSolved = 37572;
}

/*
equation index: 37573
type: SIMPLE_ASSIGN
inverter.P_max_mot = pVehicle.pInverter.P_max_mot
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37573(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37573};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5919]] /* inverter.P_max_mot PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6491]] /* pVehicle.pInverter.P_max_mot PARAM */);
  threadData->lastEquationSolved = 37573;
}

/*
equation index: 37574
type: SIMPLE_ASSIGN
inverter.inverter.P_max_mot = inverter.P_max_mot
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37574(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37574};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5946]] /* inverter.inverter.P_max_mot PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5919]] /* inverter.P_max_mot PARAM */);
  threadData->lastEquationSolved = 37574;
}

/*
equation index: 37575
type: SIMPLE_ASSIGN
inverter.inverter.enabled = inverter.enabled
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37575(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37575};
  (data->simulationInfo->booleanParameter[data->simulationInfo->booleanParamsIndex[575]] /* inverter.inverter.enabled PARAM */) = (data->simulationInfo->booleanParameter[data->simulationInfo->booleanParamsIndex[574]] /* inverter.enabled PARAM */);
  threadData->lastEquationSolved = 37575;
}

/*
equation index: 37576
type: SIMPLE_ASSIGN
inverter.inverter.V_eps = inverter.V_eps
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37576(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37576};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5952]] /* inverter.inverter.V_eps PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5925]] /* inverter.V_eps PARAM */);
  threadData->lastEquationSolved = 37576;
}

/*
equation index: 37577
type: SIMPLE_ASSIGN
inverter.inverter.eta_reg = inverter.eta_reg
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37577(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37577};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5962]] /* inverter.inverter.eta_reg PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5935]] /* inverter.eta_reg PARAM */);
  threadData->lastEquationSolved = 37577;
}

/*
equation index: 37578
type: SIMPLE_ASSIGN
inverter.inverter.eta_mot = inverter.eta_mot
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37578(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37578};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5955]] /* inverter.inverter.eta_mot PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5928]] /* inverter.eta_mot PARAM */);
  threadData->lastEquationSolved = 37578;
}

/*
equation index: 37579
type: SIMPLE_ASSIGN
vcu.stepDuration = vcu.frRampSteerDuration
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37579(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37579};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6876]] /* vcu.stepDuration PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6825]] /* vcu.frRampSteerDuration PARAM */);
  threadData->lastEquationSolved = 37579;
}

/*
equation index: 37580
type: SIMPLE_ASSIGN
vcu.openLoopAy = vcu.useMode == 0
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37580(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37580};
  (data->simulationInfo->booleanParameter[data->simulationInfo->booleanParamsIndex[612]] /* vcu.openLoopAy PARAM */) = ((data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[287]] /* vcu.useMode PARAM */) == ((modelica_integer) 0));
  threadData->lastEquationSolved = 37580;
}

/*
equation index: 37581
type: SIMPLE_ASSIGN
vcu.steadyStateAy = vcu.useMode == 3
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37581(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37581};
  (data->simulationInfo->booleanParameter[data->simulationInfo->booleanParamsIndex[620]] /* vcu.steadyStateAy PARAM */) = ((data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[287]] /* vcu.useMode PARAM */) == ((modelica_integer) 3));
  threadData->lastEquationSolved = 37581;
}

/*
equation index: 37582
type: SIMPLE_ASSIGN
vcu.ayManeuver = vcu.openLoopAy or vcu.steadyStateAy
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37582(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37582};
  (data->simulationInfo->booleanParameter[data->simulationInfo->booleanParamsIndex[607]] /* vcu.ayManeuver PARAM */) = ((data->simulationInfo->booleanParameter[data->simulationInfo->booleanParamsIndex[612]] /* vcu.openLoopAy PARAM */) || (data->simulationInfo->booleanParameter[data->simulationInfo->booleanParamsIndex[620]] /* vcu.steadyStateAy PARAM */));
  threadData->lastEquationSolved = 37582;
}

/*
equation index: 37583
type: SIMPLE_ASSIGN
vcu.motorSpeedSign = pVehicle.pVCU.motorSpeedSign
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37583(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37583};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6831]] /* vcu.motorSpeedSign PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6793]] /* pVehicle.pVCU.motorSpeedSign PARAM */);
  threadData->lastEquationSolved = 37583;
}

/*
equation index: 37584
type: SIMPLE_ASSIGN
vcu.vcu.motorSpeedSign = vcu.motorSpeedSign
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37584(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37584};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6881]] /* vcu.vcu.motorSpeedSign PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6831]] /* vcu.motorSpeedSign PARAM */);
  threadData->lastEquationSolved = 37584;
}

/*
equation index: 37585
type: SIMPLE_ASSIGN
vcu.w_eps = pVehicle.pVCU.w_eps
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37585(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37585};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6886]] /* vcu.w_eps PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6797]] /* pVehicle.pVCU.w_eps PARAM */);
  threadData->lastEquationSolved = 37585;
}

/*
equation index: 37586
type: SIMPLE_ASSIGN
vcu.vcu.w_eps = vcu.w_eps
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37586(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37586};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6883]] /* vcu.vcu.w_eps PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6886]] /* vcu.w_eps PARAM */);
  threadData->lastEquationSolved = 37586;
}

/*
equation index: 37587
type: SIMPLE_ASSIGN
vcu.tau_max = pVehicle.pVCU.tau_max
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37587(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37587};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6879]] /* vcu.tau_max PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6796]] /* pVehicle.pVCU.tau_max PARAM */);
  threadData->lastEquationSolved = 37587;
}

/*
equation index: 37588
type: SIMPLE_ASSIGN
vcu.vcu.tau_max = vcu.tau_max
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37588(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37588};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6882]] /* vcu.vcu.tau_max PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6879]] /* vcu.tau_max PARAM */);
  threadData->lastEquationSolved = 37588;
}

/*
equation index: 37590
type: SIMPLE_ASSIGN
vcu.speedPI.addFF.k2 = vcu.speedPI.kFF
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37590(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37590};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6844]] /* vcu.speedPI.addFF.k2 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6858]] /* vcu.speedPI.kFF PARAM */);
  threadData->lastEquationSolved = 37590;
}

/*
equation index: 37600
type: SIMPLE_ASSIGN
vcu.speedPI.k = vcu.velGain
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37600(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37600};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6857]] /* vcu.speedPI.k PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6884]] /* vcu.velGain PARAM */);
  threadData->lastEquationSolved = 37600;
}

/*
equation index: 37602
type: SIMPLE_ASSIGN
vcu.speedPI.gainTrack.k = 1.0 / (vcu.speedPI.Ni * vcu.speedPI.k)
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37602(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37602};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6856]] /* vcu.speedPI.gainTrack.k PARAM */) = DIVISION_SIM(1.0,((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6839]] /* vcu.speedPI.Ni PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6857]] /* vcu.speedPI.k PARAM */)),"vcu.speedPI.Ni * vcu.speedPI.k",equationIndexes);
  threadData->lastEquationSolved = 37602;
}

/*
equation index: 37611
type: SIMPLE_ASSIGN
vcu.speedPI.gainPID.k = vcu.speedPI.k
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37611(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37611};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6855]] /* vcu.speedPI.gainPID.k PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6857]] /* vcu.speedPI.k PARAM */);
  threadData->lastEquationSolved = 37611;
}

/*
equation index: 37613
type: SIMPLE_ASSIGN
vcu.speedPI.I.y_start = vcu.speedPI.xi_start
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37613(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37613};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6837]] /* vcu.speedPI.I.y_start PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6864]] /* vcu.speedPI.xi_start PARAM */);
  threadData->lastEquationSolved = 37613;
}

/*
equation index: 37617
type: SIMPLE_ASSIGN
vcu.speedPI.Ti = vcu.velTi
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37617(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37617};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6842]] /* vcu.speedPI.Ti PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6885]] /* vcu.velTi PARAM */);
  threadData->lastEquationSolved = 37617;
}

/*
equation index: 37618
type: SIMPLE_ASSIGN
vcu.speedPI.I.k = 1.0 / vcu.speedPI.Ti
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37618(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37618};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6836]] /* vcu.speedPI.I.k PARAM */) = DIVISION_SIM(1.0,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6842]] /* vcu.speedPI.Ti PARAM */),"vcu.speedPI.Ti",equationIndexes);
  threadData->lastEquationSolved = 37618;
}

/*
equation index: 37622
type: SIMPLE_ASSIGN
vcu.speedPI.addP.k1 = vcu.speedPI.wp
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37622(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37622};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6848]] /* vcu.speedPI.addP.k1 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6862]] /* vcu.speedPI.wp PARAM */);
  threadData->lastEquationSolved = 37622;
}

/*
equation index: 37635
type: SIMPLE_ASSIGN
vcu.regenBrakeBlend = pVehicle.pVCU.regenBrakeBlend
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37635(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37635};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6832]] /* vcu.regenBrakeBlend PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6794]] /* pVehicle.pVCU.regenBrakeBlend PARAM */);
  threadData->lastEquationSolved = 37635;
}

/*
equation index: 37636
type: SIMPLE_ASSIGN
vcu.mechanicalBrakeTorqueLimit = pVehicle.pVCU.mechanicalBrakeTorqueLimit
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37636(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37636};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6830]] /* vcu.mechanicalBrakeTorqueLimit PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6792]] /* pVehicle.pVCU.mechanicalBrakeTorqueLimit PARAM */);
  threadData->lastEquationSolved = 37636;
}

/*
equation index: 37637
type: SIMPLE_ASSIGN
vcu.regenTorqueLimit = pVehicle.pVCU.regenTorqueLimit
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37637(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37637};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6833]] /* vcu.regenTorqueLimit PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6795]] /* pVehicle.pVCU.regenTorqueLimit PARAM */);
  threadData->lastEquationSolved = 37637;
}

/*
equation index: 37638
type: SIMPLE_ASSIGN
vcu.targetVel = initialVel
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37638(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37638};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6878]] /* vcu.targetVel PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5914]] /* initialVel PARAM */);
  threadData->lastEquationSolved = 37638;
}

/*
equation index: 37641
type: SIMPLE_ASSIGN
battery.Np = pVehicle.pBattery.Np
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37641(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37641};
  (data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[5]] /* battery.Np PARAM */) = (data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[267]] /* pVehicle.pBattery.Np PARAM */);
  threadData->lastEquationSolved = 37641;
}

/*
equation index: 37642
type: SIMPLE_ASSIGN
battery.battery.Np = battery.Np
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37642(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37642};
  (data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[7]] /* battery.battery.Np PARAM */) = (data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[5]] /* battery.Np PARAM */);
  threadData->lastEquationSolved = 37642;
}

/*
equation index: 37643
type: SIMPLE_ASSIGN
battery.battery.Q_cell = battery.battery.E_cell / battery.battery.V_cell_nominal
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37643(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37643};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[195]] /* battery.battery.Q_cell PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[179]] /* battery.battery.E_cell PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[245]] /* battery.battery.V_cell_nominal PARAM */),"battery.battery.V_cell_nominal",equationIndexes);
  threadData->lastEquationSolved = 37643;
}

/*
equation index: 37644
type: SIMPLE_ASSIGN
battery.battery.Q_pack = (*Real*)(battery.battery.Np) * battery.battery.Q_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37644(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37644};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[196]] /* battery.battery.Q_pack PARAM */) = (((modelica_real)(data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[7]] /* battery.battery.Np PARAM */))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[195]] /* battery.battery.Q_cell PARAM */));
  threadData->lastEquationSolved = 37644;
}

/*
equation index: 37645
type: SIMPLE_ASSIGN
battery.Ns = pVehicle.pBattery.Ns
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37645(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37645};
  (data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[6]] /* battery.Ns PARAM */) = (data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[268]] /* pVehicle.pBattery.Ns PARAM */);
  threadData->lastEquationSolved = 37645;
}

/*
equation index: 37646
type: SIMPLE_ASSIGN
battery.battery.Ns = battery.Ns
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37646(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37646};
  (data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[8]] /* battery.battery.Ns PARAM */) = (data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[6]] /* battery.Ns PARAM */);
  threadData->lastEquationSolved = 37646;
}

/*
equation index: 37647
type: SIMPLE_ASSIGN
battery.battery.E_pack = (*Real*)(battery.battery.Ns * battery.battery.Np) * battery.battery.E_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37647(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37647};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[180]] /* battery.battery.E_pack PARAM */) = (((modelica_real)((data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[8]] /* battery.battery.Ns PARAM */)) * ((data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[7]] /* battery.battery.Np PARAM */)))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[179]] /* battery.battery.E_cell PARAM */));
  threadData->lastEquationSolved = 37647;
}

/*
equation index: 37648
type: SIMPLE_ASSIGN
battery.battery.R_pack = (*Real*)(battery.battery.Ns) * battery.battery.R_cell / (*Real*)(battery.battery.Np)
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37648(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37648};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[227]] /* battery.battery.R_pack PARAM */) = (((modelica_real)(data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[8]] /* battery.battery.Ns PARAM */))) * (DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */),((modelica_real)(data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[7]] /* battery.battery.Np PARAM */)),"/*Real*/(battery.battery.Np)",equationIndexes));
  threadData->lastEquationSolved = 37648;
}

/*
equation index: 37649
type: SIMPLE_ASSIGN
battery.battery.R1_chg_cell_table[7] = 0.9 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37649(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37649};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[217]] /* battery.battery.R1_chg_cell_table[7] PARAM */) = (0.9) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37649;
}

/*
equation index: 37650
type: SIMPLE_ASSIGN
battery.battery.R1_chg_cell_table[6] = 0.68 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37650(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37650};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[216]] /* battery.battery.R1_chg_cell_table[6] PARAM */) = (0.68) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37650;
}

/*
equation index: 37651
type: SIMPLE_ASSIGN
battery.battery.R1_chg_cell_table[5] = 0.52 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37651(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37651};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[215]] /* battery.battery.R1_chg_cell_table[5] PARAM */) = (0.52) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37651;
}

/*
equation index: 37652
type: SIMPLE_ASSIGN
battery.battery.R1_chg_cell_table[4] = 0.5 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37652(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37652};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[214]] /* battery.battery.R1_chg_cell_table[4] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37652;
}

/*
equation index: 37653
type: SIMPLE_ASSIGN
battery.battery.R1_chg_cell_table[3] = 0.6 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37653(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37653};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[213]] /* battery.battery.R1_chg_cell_table[3] PARAM */) = (0.6) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37653;
}

/*
equation index: 37654
type: SIMPLE_ASSIGN
battery.battery.R1_chg_cell_table[2] = 0.8 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37654(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37654};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[212]] /* battery.battery.R1_chg_cell_table[2] PARAM */) = (0.8) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37654;
}

/*
equation index: 37655
type: SIMPLE_ASSIGN
battery.battery.R1_chg_cell_table[1] = battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37655(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37655};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[211]] /* battery.battery.R1_chg_cell_table[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */);
  threadData->lastEquationSolved = 37655;
}

/*
equation index: 37656
type: SIMPLE_ASSIGN
battery.battery.R1_dis_cell_table[7] = 0.75 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37656(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37656};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[224]] /* battery.battery.R1_dis_cell_table[7] PARAM */) = (0.75) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37656;
}

/*
equation index: 37657
type: SIMPLE_ASSIGN
battery.battery.R1_dis_cell_table[6] = 0.55 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37657(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37657};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[223]] /* battery.battery.R1_dis_cell_table[6] PARAM */) = (0.55) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37657;
}

/*
equation index: 37658
type: SIMPLE_ASSIGN
battery.battery.R1_dis_cell_table[5] = 0.45 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37658(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37658};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[222]] /* battery.battery.R1_dis_cell_table[5] PARAM */) = (0.45) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37658;
}

/*
equation index: 37659
type: SIMPLE_ASSIGN
battery.battery.R1_dis_cell_table[4] = 0.45 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37659(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37659};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[221]] /* battery.battery.R1_dis_cell_table[4] PARAM */) = (0.45) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37659;
}

/*
equation index: 37660
type: SIMPLE_ASSIGN
battery.battery.R1_dis_cell_table[3] = 0.55 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37660(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37660};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[220]] /* battery.battery.R1_dis_cell_table[3] PARAM */) = (0.55) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37660;
}

/*
equation index: 37661
type: SIMPLE_ASSIGN
battery.battery.R1_dis_cell_table[2] = 0.7 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37661(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37661};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[219]] /* battery.battery.R1_dis_cell_table[2] PARAM */) = (0.7) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37661;
}

/*
equation index: 37662
type: SIMPLE_ASSIGN
battery.battery.R1_dis_cell_table[1] = 0.9 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37662(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37662};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[218]] /* battery.battery.R1_dis_cell_table[1] PARAM */) = (0.9) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37662;
}

/*
equation index: 37663
type: SIMPLE_ASSIGN
battery.battery.R0_chg_cell_table[7] = 1.45 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37663(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37663};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[203]] /* battery.battery.R0_chg_cell_table[7] PARAM */) = (1.45) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37663;
}

/*
equation index: 37664
type: SIMPLE_ASSIGN
battery.battery.R0_chg_cell_table[6] = 1.18 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37664(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37664};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[202]] /* battery.battery.R0_chg_cell_table[6] PARAM */) = (1.18) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37664;
}

/*
equation index: 37665
type: SIMPLE_ASSIGN
battery.battery.R0_chg_cell_table[5] = 1.05 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37665(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37665};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[201]] /* battery.battery.R0_chg_cell_table[5] PARAM */) = (1.05) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37665;
}

/*
equation index: 37666
type: SIMPLE_ASSIGN
battery.battery.R0_chg_cell_table[4] = 1.03 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37666(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37666};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[200]] /* battery.battery.R0_chg_cell_table[4] PARAM */) = (1.03) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37666;
}

/*
equation index: 37667
type: SIMPLE_ASSIGN
battery.battery.R0_chg_cell_table[3] = 1.1 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37667(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37667};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[199]] /* battery.battery.R0_chg_cell_table[3] PARAM */) = (1.1) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37667;
}

/*
equation index: 37668
type: SIMPLE_ASSIGN
battery.battery.R0_chg_cell_table[2] = 1.35 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37668(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37668};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[198]] /* battery.battery.R0_chg_cell_table[2] PARAM */) = (1.35) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37668;
}

/*
equation index: 37669
type: SIMPLE_ASSIGN
battery.battery.R0_chg_cell_table[1] = 1.8 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37669(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37669};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[197]] /* battery.battery.R0_chg_cell_table[1] PARAM */) = (1.8) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37669;
}

/*
equation index: 37670
type: SIMPLE_ASSIGN
battery.battery.R0_dis_cell_table[7] = 1.25 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37670(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37670};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[210]] /* battery.battery.R0_dis_cell_table[7] PARAM */) = (1.25) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37670;
}

/*
equation index: 37671
type: SIMPLE_ASSIGN
battery.battery.R0_dis_cell_table[6] = 1.08 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37671(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37671};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[209]] /* battery.battery.R0_dis_cell_table[6] PARAM */) = (1.08) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37671;
}

/*
equation index: 37672
type: SIMPLE_ASSIGN
battery.battery.R0_dis_cell_table[5] = battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37672(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37672};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[208]] /* battery.battery.R0_dis_cell_table[5] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */);
  threadData->lastEquationSolved = 37672;
}

/*
equation index: 37673
type: SIMPLE_ASSIGN
battery.battery.R0_dis_cell_table[4] = battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37673(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37673};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[207]] /* battery.battery.R0_dis_cell_table[4] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */);
  threadData->lastEquationSolved = 37673;
}

/*
equation index: 37674
type: SIMPLE_ASSIGN
battery.battery.R0_dis_cell_table[3] = 1.05 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37674(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37674};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[206]] /* battery.battery.R0_dis_cell_table[3] PARAM */) = (1.05) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37674;
}

/*
equation index: 37675
type: SIMPLE_ASSIGN
battery.battery.R0_dis_cell_table[2] = 1.25 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37675(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37675};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[205]] /* battery.battery.R0_dis_cell_table[2] PARAM */) = (1.25) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37675;
}

/*
equation index: 37676
type: SIMPLE_ASSIGN
battery.battery.R0_dis_cell_table[1] = 1.6 * battery.battery.R_cell
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37676(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37676};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[204]] /* battery.battery.R0_dis_cell_table[1] PARAM */) = (1.6) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[225]] /* battery.battery.R_cell PARAM */));
  threadData->lastEquationSolved = 37676;
}

/*
equation index: 37677
type: SIMPLE_ASSIGN
battery.SOC_start = pVehicle.pBattery.SOC_start
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37677(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37677};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[178]] /* battery.SOC_start PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6193]] /* pVehicle.pBattery.SOC_start PARAM */);
  threadData->lastEquationSolved = 37677;
}

/*
equation index: 37678
type: SIMPLE_ASSIGN
battery.battery.SOC_start = battery.SOC_start
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37678(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37678};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[228]] /* battery.battery.SOC_start PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[178]] /* battery.SOC_start PARAM */);
  threadData->lastEquationSolved = 37678;
}

/*
equation index: 37705
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_4.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37705(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37705};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[346]] /* chassis.fixedContactPatch_4.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 37705;
}

/*
equation index: 37709
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_3.r[1] = chassis.contactPatchPosition_3[1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37709(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37709};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5029]] /* chassis.fixedContactPatch_3.r[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[345]] /* chassis.contactPatchPosition_3[1] PARAM */);
  threadData->lastEquationSolved = 37709;
}

/*
equation index: 37710
type: SIMPLE_ASSIGN
chassis.pVehicle.pRrPartialWheel.R0 = pVehicle.pRrPartialWheel.R0
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37710(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37710};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5681]] /* chassis.pVehicle.pRrPartialWheel.R0 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6619]] /* pVehicle.pRrPartialWheel.R0 PARAM */);
  threadData->lastEquationSolved = 37710;
}

/*
equation index: 37711
type: SIMPLE_ASSIGN
chassis.pVehicle.pRrPartialWheel.staticGamma = pVehicle.pRrPartialWheel.staticGamma
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37711(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37711};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5685]] /* chassis.pVehicle.pRrPartialWheel.staticGamma PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6623]] /* pVehicle.pRrPartialWheel.staticGamma PARAM */);
  threadData->lastEquationSolved = 37711;
}

/*
equation index: 37712
type: SIMPLE_ASSIGN
chassis.contactPatchPosition_3[2] = 0.60611077 + sin(0.017453292519943295 * chassis.pVehicle.pRrPartialWheel.staticGamma) * chassis.pVehicle.pRrPartialWheel.R0
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37712(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37712};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[346]] /* chassis.contactPatchPosition_3[2] PARAM */) = 0.60611077 + (sin((0.017453292519943295) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5685]] /* chassis.pVehicle.pRrPartialWheel.staticGamma PARAM */)))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5681]] /* chassis.pVehicle.pRrPartialWheel.R0 PARAM */));
  threadData->lastEquationSolved = 37712;
}

/*
equation index: 37713
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_3.r[2] = chassis.contactPatchPosition_3[2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37713(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37713};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5030]] /* chassis.fixedContactPatch_3.r[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[346]] /* chassis.contactPatchPosition_3[2] PARAM */);
  threadData->lastEquationSolved = 37713;
}

/*
equation index: 37714
type: SIMPLE_ASSIGN
chassis.contactPatchPosition_3[3] = 0.199898 - cos(0.017453292519943295 * chassis.pVehicle.pRrPartialWheel.staticGamma) * chassis.pVehicle.pRrPartialWheel.R0
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37714(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37714};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[347]] /* chassis.contactPatchPosition_3[3] PARAM */) = 0.199898 - ((cos((0.017453292519943295) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5685]] /* chassis.pVehicle.pRrPartialWheel.staticGamma PARAM */)))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5681]] /* chassis.pVehicle.pRrPartialWheel.R0 PARAM */)));
  threadData->lastEquationSolved = 37714;
}

/*
equation index: 37715
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_3.r[3] = chassis.contactPatchPosition_3[3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37715(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37715};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5031]] /* chassis.fixedContactPatch_3.r[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[347]] /* chassis.contactPatchPosition_3[3] PARAM */);
  threadData->lastEquationSolved = 37715;
}

/*
equation index: 37719
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_3.length = sqrt((chassis.fixedContactPatch_3.r[1] - chassis.fixedContactPatch_3.r_shape[1]) ^ 2.0 + (chassis.fixedContactPatch_3.r[2] - chassis.fixedContactPatch_3.r_shape[2]) ^ 2.0 + (chassis.fixedContactPatch_3.r[3] - chassis.fixedContactPatch_3.r_shape[3]) ^ 2.0)
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37719(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37719};
  modelica_real tmp16;
  modelica_real tmp17;
  modelica_real tmp18;
  modelica_real tmp19;
  tmp16 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5029]] /* chassis.fixedContactPatch_3.r[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5032]] /* chassis.fixedContactPatch_3.r_shape[1] PARAM */);
  tmp17 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5030]] /* chassis.fixedContactPatch_3.r[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5033]] /* chassis.fixedContactPatch_3.r_shape[2] PARAM */);
  tmp18 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5031]] /* chassis.fixedContactPatch_3.r[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5034]] /* chassis.fixedContactPatch_3.r_shape[3] PARAM */);
  tmp19 = (tmp16 * tmp16) + (tmp17 * tmp17) + (tmp18 * tmp18);
  if(!(tmp19 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.fixedContactPatch_3.r[1] - chassis.fixedContactPatch_3.r_shape[1]) ^ 2.0 + (chassis.fixedContactPatch_3.r[2] - chassis.fixedContactPatch_3.r_shape[2]) ^ 2.0 + (chassis.fixedContactPatch_3.r[3] - chassis.fixedContactPatch_3.r_shape[3]) ^ 2.0) was %g should be >= 0", tmp19);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5025]] /* chassis.fixedContactPatch_3.length PARAM */) = sqrt(tmp19);
  threadData->lastEquationSolved = 37719;
}

/*
equation index: 37720
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_3.width = chassis.fixedContactPatch_3.length / world.defaultWidthFraction
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37720(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37720};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5035]] /* chassis.fixedContactPatch_3.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5025]] /* chassis.fixedContactPatch_3.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 37720;
}

/*
equation index: 37721
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_3.height = chassis.fixedContactPatch_3.width
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37721(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37721};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5024]] /* chassis.fixedContactPatch_3.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5035]] /* chassis.fixedContactPatch_3.width PARAM */);
  threadData->lastEquationSolved = 37721;
}

/*
equation index: 37725
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_3.lengthDirection[3] = chassis.fixedContactPatch_3.r[3] - chassis.fixedContactPatch_3.r_shape[3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37725(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37725};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5028]] /* chassis.fixedContactPatch_3.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5031]] /* chassis.fixedContactPatch_3.r[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5034]] /* chassis.fixedContactPatch_3.r_shape[3] PARAM */);
  threadData->lastEquationSolved = 37725;
}

/*
equation index: 37726
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_3.lengthDirection[2] = chassis.fixedContactPatch_3.r[2] - chassis.fixedContactPatch_3.r_shape[2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37726(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37726};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5027]] /* chassis.fixedContactPatch_3.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5030]] /* chassis.fixedContactPatch_3.r[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5033]] /* chassis.fixedContactPatch_3.r_shape[2] PARAM */);
  threadData->lastEquationSolved = 37726;
}

/*
equation index: 37727
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_3.lengthDirection[1] = chassis.fixedContactPatch_3.r[1] - chassis.fixedContactPatch_3.r_shape[1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37727(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37727};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5026]] /* chassis.fixedContactPatch_3.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5029]] /* chassis.fixedContactPatch_3.r[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5032]] /* chassis.fixedContactPatch_3.r_shape[1] PARAM */);
  threadData->lastEquationSolved = 37727;
}

/*
equation index: 37728
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_3.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37728(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37728};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[345]] /* chassis.fixedContactPatch_3.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 37728;
}

/*
equation index: 37737
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_2.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37737(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37737};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[344]] /* chassis.fixedContactPatch_2.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 37737;
}

/*
equation index: 37741
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_1.r[1] = chassis.contactPatchPosition_1[1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37741(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37741};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4997]] /* chassis.fixedContactPatch_1.r[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[339]] /* chassis.contactPatchPosition_1[1] PARAM */);
  threadData->lastEquationSolved = 37741;
}

/*
equation index: 37742
type: SIMPLE_ASSIGN
chassis.pVehicle.pFrPartialWheel.R0 = pVehicle.pFrPartialWheel.R0
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37742(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37742};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5394]] /* chassis.pVehicle.pFrPartialWheel.R0 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6332]] /* pVehicle.pFrPartialWheel.R0 PARAM */);
  threadData->lastEquationSolved = 37742;
}

/*
equation index: 37743
type: SIMPLE_ASSIGN
chassis.pVehicle.pFrPartialWheel.staticGamma = pVehicle.pFrPartialWheel.staticGamma
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37743(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37743};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5398]] /* chassis.pVehicle.pFrPartialWheel.staticGamma PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6336]] /* pVehicle.pFrPartialWheel.staticGamma PARAM */);
  threadData->lastEquationSolved = 37743;
}

/*
equation index: 37744
type: SIMPLE_ASSIGN
chassis.contactPatchPosition_1[2] = 0.606110767456 + sin(0.017453292519943295 * chassis.pVehicle.pFrPartialWheel.staticGamma) * chassis.pVehicle.pFrPartialWheel.R0
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37744(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37744};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[340]] /* chassis.contactPatchPosition_1[2] PARAM */) = 0.606110767456 + (sin((0.017453292519943295) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5398]] /* chassis.pVehicle.pFrPartialWheel.staticGamma PARAM */)))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5394]] /* chassis.pVehicle.pFrPartialWheel.R0 PARAM */));
  threadData->lastEquationSolved = 37744;
}

/*
equation index: 37745
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_1.r[2] = chassis.contactPatchPosition_1[2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37745(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37745};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4998]] /* chassis.fixedContactPatch_1.r[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[340]] /* chassis.contactPatchPosition_1[2] PARAM */);
  threadData->lastEquationSolved = 37745;
}

/*
equation index: 37746
type: SIMPLE_ASSIGN
chassis.contactPatchPosition_1[3] = 0.199898 - cos(0.017453292519943295 * chassis.pVehicle.pFrPartialWheel.staticGamma) * chassis.pVehicle.pFrPartialWheel.R0
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37746(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37746};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[341]] /* chassis.contactPatchPosition_1[3] PARAM */) = 0.199898 - ((cos((0.017453292519943295) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5398]] /* chassis.pVehicle.pFrPartialWheel.staticGamma PARAM */)))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5394]] /* chassis.pVehicle.pFrPartialWheel.R0 PARAM */)));
  threadData->lastEquationSolved = 37746;
}

/*
equation index: 37747
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_1.r[3] = chassis.contactPatchPosition_1[3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37747(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37747};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4999]] /* chassis.fixedContactPatch_1.r[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[341]] /* chassis.contactPatchPosition_1[3] PARAM */);
  threadData->lastEquationSolved = 37747;
}

/*
equation index: 37751
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_1.length = sqrt((chassis.fixedContactPatch_1.r[1] - chassis.fixedContactPatch_1.r_shape[1]) ^ 2.0 + (chassis.fixedContactPatch_1.r[2] - chassis.fixedContactPatch_1.r_shape[2]) ^ 2.0 + (chassis.fixedContactPatch_1.r[3] - chassis.fixedContactPatch_1.r_shape[3]) ^ 2.0)
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37751(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37751};
  modelica_real tmp20;
  modelica_real tmp21;
  modelica_real tmp22;
  modelica_real tmp23;
  tmp20 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4997]] /* chassis.fixedContactPatch_1.r[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5000]] /* chassis.fixedContactPatch_1.r_shape[1] PARAM */);
  tmp21 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4998]] /* chassis.fixedContactPatch_1.r[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5001]] /* chassis.fixedContactPatch_1.r_shape[2] PARAM */);
  tmp22 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4999]] /* chassis.fixedContactPatch_1.r[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5002]] /* chassis.fixedContactPatch_1.r_shape[3] PARAM */);
  tmp23 = (tmp20 * tmp20) + (tmp21 * tmp21) + (tmp22 * tmp22);
  if(!(tmp23 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.fixedContactPatch_1.r[1] - chassis.fixedContactPatch_1.r_shape[1]) ^ 2.0 + (chassis.fixedContactPatch_1.r[2] - chassis.fixedContactPatch_1.r_shape[2]) ^ 2.0 + (chassis.fixedContactPatch_1.r[3] - chassis.fixedContactPatch_1.r_shape[3]) ^ 2.0) was %g should be >= 0", tmp23);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4993]] /* chassis.fixedContactPatch_1.length PARAM */) = sqrt(tmp23);
  threadData->lastEquationSolved = 37751;
}

/*
equation index: 37752
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_1.width = chassis.fixedContactPatch_1.length / world.defaultWidthFraction
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37752(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37752};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5003]] /* chassis.fixedContactPatch_1.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4993]] /* chassis.fixedContactPatch_1.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 37752;
}

/*
equation index: 37753
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_1.height = chassis.fixedContactPatch_1.width
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37753(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37753};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4992]] /* chassis.fixedContactPatch_1.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5003]] /* chassis.fixedContactPatch_1.width PARAM */);
  threadData->lastEquationSolved = 37753;
}

/*
equation index: 37757
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_1.lengthDirection[3] = chassis.fixedContactPatch_1.r[3] - chassis.fixedContactPatch_1.r_shape[3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37757(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37757};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4996]] /* chassis.fixedContactPatch_1.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4999]] /* chassis.fixedContactPatch_1.r[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5002]] /* chassis.fixedContactPatch_1.r_shape[3] PARAM */);
  threadData->lastEquationSolved = 37757;
}

/*
equation index: 37758
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_1.lengthDirection[2] = chassis.fixedContactPatch_1.r[2] - chassis.fixedContactPatch_1.r_shape[2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37758(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37758};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4995]] /* chassis.fixedContactPatch_1.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4998]] /* chassis.fixedContactPatch_1.r[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5001]] /* chassis.fixedContactPatch_1.r_shape[2] PARAM */);
  threadData->lastEquationSolved = 37758;
}

/*
equation index: 37759
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_1.lengthDirection[1] = chassis.fixedContactPatch_1.r[1] - chassis.fixedContactPatch_1.r_shape[1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37759(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37759};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4994]] /* chassis.fixedContactPatch_1.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4997]] /* chassis.fixedContactPatch_1.r[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5000]] /* chassis.fixedContactPatch_1.r_shape[1] PARAM */);
  threadData->lastEquationSolved = 37759;
}

/*
equation index: 37760
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_1.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37760(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37760};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[343]] /* chassis.fixedContactPatch_1.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 37760;
}

/*
equation index: 37763
type: SIMPLE_ASSIGN
chassis.cgFreeMotion.phi_start[3] = chassis.cgFreeMotion.angles_start[3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37763(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37763};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[313]] /* chassis.cgFreeMotion.phi_start[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[310]] /* chassis.cgFreeMotion.angles_start[3] PARAM */);
  threadData->lastEquationSolved = 37763;
}

/*
equation index: 37765
type: SIMPLE_ASSIGN
chassis.cgFreeMotion.phi_start[2] = chassis.cgFreeMotion.angles_start[2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37765(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37765};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[312]] /* chassis.cgFreeMotion.phi_start[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[309]] /* chassis.cgFreeMotion.angles_start[2] PARAM */);
  threadData->lastEquationSolved = 37765;
}

/*
equation index: 37767
type: SIMPLE_ASSIGN
chassis.cgFreeMotion.phi_start[1] = chassis.cgFreeMotion.angles_start[1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37767(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37767};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[311]] /* chassis.cgFreeMotion.phi_start[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[308]] /* chassis.cgFreeMotion.angles_start[1] PARAM */);
  threadData->lastEquationSolved = 37767;
}

/*
equation index: 37768
type: ARRAY_CALL_ASSIGN

chassis.cgFreeMotion.Q_start = {0.0, 0.0, 0.0, 1.0}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37768(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37768};
  real_array tmp24;
  real_array_create(&tmp24, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[292]] /* chassis.cgFreeMotion.Q_start[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)4);
  real_array_copy_data(_OMC_LIT46, tmp24);
  threadData->lastEquationSolved = 37768;
}

/*
equation index: 37803
type: SIMPLE_ASSIGN
chassis.cgFixed.length = sqrt((-0.8048573854162592 - chassis.cgFixed.r_shape[1]) ^ 2.0 + (0.04115040316450602 - chassis.cgFixed.r_shape[2]) ^ 2.0 + (0.28552952360282374 - chassis.cgFixed.r_shape[3]) ^ 2.0)
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37803(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37803};
  modelica_real tmp25;
  modelica_real tmp26;
  modelica_real tmp27;
  modelica_real tmp28;
  tmp25 = -0.8048573854162592 - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[285]] /* chassis.cgFixed.r_shape[1] PARAM */);
  tmp26 = 0.04115040316450602 - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[286]] /* chassis.cgFixed.r_shape[2] PARAM */);
  tmp27 = 0.28552952360282374 - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[287]] /* chassis.cgFixed.r_shape[3] PARAM */);
  tmp28 = (tmp25 * tmp25) + (tmp26 * tmp26) + (tmp27 * tmp27);
  if(!(tmp28 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((-0.8048573854162592 - chassis.cgFixed.r_shape[1]) ^ 2.0 + (0.04115040316450602 - chassis.cgFixed.r_shape[2]) ^ 2.0 + (0.28552952360282374 - chassis.cgFixed.r_shape[3]) ^ 2.0) was %g should be >= 0", tmp28);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[278]] /* chassis.cgFixed.length PARAM */) = sqrt(tmp28);
  threadData->lastEquationSolved = 37803;
}

/*
equation index: 37804
type: SIMPLE_ASSIGN
chassis.cgFixed.width = chassis.cgFixed.length / world.defaultWidthFraction
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37804(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37804};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[288]] /* chassis.cgFixed.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[278]] /* chassis.cgFixed.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 37804;
}

/*
equation index: 37805
type: SIMPLE_ASSIGN
chassis.cgFixed.height = chassis.cgFixed.width
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37805(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37805};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[277]] /* chassis.cgFixed.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[288]] /* chassis.cgFixed.width PARAM */);
  threadData->lastEquationSolved = 37805;
}

/*
equation index: 37809
type: SIMPLE_ASSIGN
chassis.cgFixed.lengthDirection[3] = 0.28552952360282374 - chassis.cgFixed.r_shape[3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37809(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37809};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[281]] /* chassis.cgFixed.lengthDirection[3] PARAM */) = 0.28552952360282374 - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[287]] /* chassis.cgFixed.r_shape[3] PARAM */);
  threadData->lastEquationSolved = 37809;
}

/*
equation index: 37810
type: SIMPLE_ASSIGN
chassis.cgFixed.lengthDirection[2] = 0.04115040316450602 - chassis.cgFixed.r_shape[2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37810(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37810};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[280]] /* chassis.cgFixed.lengthDirection[2] PARAM */) = 0.04115040316450602 - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[286]] /* chassis.cgFixed.r_shape[2] PARAM */);
  threadData->lastEquationSolved = 37810;
}

/*
equation index: 37811
type: SIMPLE_ASSIGN
chassis.cgFixed.lengthDirection[1] = -0.8048573854162592 - chassis.cgFixed.r_shape[1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37811(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37811};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[279]] /* chassis.cgFixed.lengthDirection[1] PARAM */) = -0.8048573854162592 - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[285]] /* chassis.cgFixed.r_shape[1] PARAM */);
  threadData->lastEquationSolved = 37811;
}

/*
equation index: 37812
type: SIMPLE_ASSIGN
chassis.cgFixed.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37812(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37812};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[1]] /* chassis.cgFixed.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 37812;
}

/*
equation index: 37819
type: SIMPLE_ASSIGN
chassis.chassisFrameToCG.width = chassis.chassisFrameToCG.length / world.defaultWidthFraction
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37819(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37819};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[332]] /* chassis.chassisFrameToCG.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[322]] /* chassis.chassisFrameToCG.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 37819;
}

/*
equation index: 37820
type: SIMPLE_ASSIGN
chassis.chassisFrameToCG.height = chassis.chassisFrameToCG.width
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37820(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37820};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[321]] /* chassis.chassisFrameToCG.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[332]] /* chassis.chassisFrameToCG.width PARAM */);
  threadData->lastEquationSolved = 37820;
}

/*
equation index: 37830
type: SIMPLE_ASSIGN
chassis.chassisFrameToCG.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37830(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37830};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[2]] /* chassis.chassisFrameToCG.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 37830;
}

/*
equation index: 37840
type: SIMPLE_ASSIGN
chassis.pVehicle.pTorsionalStiff = pVehicle.pTorsionalStiff
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37840(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37840};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5853]] /* chassis.pVehicle.pTorsionalStiff PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6791]] /* pVehicle.pTorsionalStiff PARAM */);
  threadData->lastEquationSolved = 37840;
}

/*
equation index: 37841
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.torsionalStiff = chassis.pVehicle.pTorsionalStiff
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37841(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37841};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4986]] /* chassis.detailedChassis.spaceFrame.torsionalStiff PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5853]] /* chassis.pVehicle.pTorsionalStiff PARAM */);
  threadData->lastEquationSolved = 37841;
}

/*
equation index: 37842
type: SIMPLE_ASSIGN
chassis.pVehicle.pSprungMass.inertia[1,1] = pVehicle.pSprungMass.inertia[1,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37842(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37842};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5840]] /* chassis.pVehicle.pSprungMass.inertia[1,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6778]] /* pVehicle.pSprungMass.inertia[1,1] PARAM */);
  threadData->lastEquationSolved = 37842;
}

/*
equation index: 37843
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.pSprungMass.inertia[1,1] = chassis.pVehicle.pSprungMass.inertia[1,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37843(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37843};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4909]] /* chassis.detailedChassis.spaceFrame.pSprungMass.inertia[1,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5840]] /* chassis.pVehicle.pSprungMass.inertia[1,1] PARAM */);
  threadData->lastEquationSolved = 37843;
}

/*
equation index: 37844
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.torsionalDamp = 2.0 * sqrt(chassis.detailedChassis.spaceFrame.torsionalStiff * chassis.detailedChassis.spaceFrame.pSprungMass.inertia[1,1])
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37844(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37844};
  modelica_real tmp29;
  tmp29 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4986]] /* chassis.detailedChassis.spaceFrame.torsionalStiff PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4909]] /* chassis.detailedChassis.spaceFrame.pSprungMass.inertia[1,1] PARAM */));
  if(!(tmp29 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.spaceFrame.torsionalStiff * chassis.detailedChassis.spaceFrame.pSprungMass.inertia[1,1]) was %g should be >= 0", tmp29);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4976]] /* chassis.detailedChassis.spaceFrame.torsionalDamp PARAM */) = (2.0) * (sqrt(tmp29));
  threadData->lastEquationSolved = 37844;
}

/*
equation index: 37845
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.damper.d = chassis.detailedChassis.spaceFrame.torsionalDamp
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37845(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37845};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4843]] /* chassis.detailedChassis.spaceFrame.damper.d PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4976]] /* chassis.detailedChassis.spaceFrame.torsionalDamp PARAM */);
  threadData->lastEquationSolved = 37845;
}

/*
equation index: 37849
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.spring.c = chassis.detailedChassis.spaceFrame.torsionalStiff
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37849(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37849};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4925]] /* chassis.detailedChassis.spaceFrame.spring.c PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4986]] /* chassis.detailedChassis.spaceFrame.torsionalStiff PARAM */);
  threadData->lastEquationSolved = 37849;
}

/*
equation index: 37851
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.torsionalRevolute.cylinder.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37851(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37851};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[342]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.cylinder.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 37851;
}

/*
equation index: 37856
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.torsionalRevolute.cylinderDiameter = world.defaultJointWidth
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37856(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37856};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4977]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.cylinderDiameter PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6897]] /* world.defaultJointWidth PARAM */);
  threadData->lastEquationSolved = 37856;
}

/*
equation index: 37857
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.torsionalRevolute.cylinderLength = world.defaultJointLength
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37857(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37857};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4978]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.cylinderLength PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6896]] /* world.defaultJointLength PARAM */);
  threadData->lastEquationSolved = 37857;
}

/*
equation index: 37863
type: SIMPLE_ASSIGN
chassis.pVehicle.pSprungMass.inertia[3,3] = pVehicle.pSprungMass.inertia[3,3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37863(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37863};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5848]] /* chassis.pVehicle.pSprungMass.inertia[3,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6786]] /* pVehicle.pSprungMass.inertia[3,3] PARAM */);
  threadData->lastEquationSolved = 37863;
}

/*
equation index: 37864
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.pSprungMass.inertia[3,3] = chassis.pVehicle.pSprungMass.inertia[3,3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37864(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37864};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4917]] /* chassis.detailedChassis.spaceFrame.pSprungMass.inertia[3,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5848]] /* chassis.pVehicle.pSprungMass.inertia[3,3] PARAM */);
  threadData->lastEquationSolved = 37864;
}

/*
equation index: 37865
type: SIMPLE_ASSIGN
chassis.pVehicle.pSprungMass.inertia[3,2] = pVehicle.pSprungMass.inertia[3,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37865(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37865};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5847]] /* chassis.pVehicle.pSprungMass.inertia[3,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6785]] /* pVehicle.pSprungMass.inertia[3,2] PARAM */);
  threadData->lastEquationSolved = 37865;
}

/*
equation index: 37866
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.pSprungMass.inertia[3,2] = chassis.pVehicle.pSprungMass.inertia[3,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37866(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37866};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4916]] /* chassis.detailedChassis.spaceFrame.pSprungMass.inertia[3,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5847]] /* chassis.pVehicle.pSprungMass.inertia[3,2] PARAM */);
  threadData->lastEquationSolved = 37866;
}

/*
equation index: 37867
type: SIMPLE_ASSIGN
chassis.pVehicle.pSprungMass.inertia[3,1] = pVehicle.pSprungMass.inertia[3,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37867(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37867};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5846]] /* chassis.pVehicle.pSprungMass.inertia[3,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6784]] /* pVehicle.pSprungMass.inertia[3,1] PARAM */);
  threadData->lastEquationSolved = 37867;
}

/*
equation index: 37868
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.pSprungMass.inertia[3,1] = chassis.pVehicle.pSprungMass.inertia[3,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37868(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37868};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4915]] /* chassis.detailedChassis.spaceFrame.pSprungMass.inertia[3,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5846]] /* chassis.pVehicle.pSprungMass.inertia[3,1] PARAM */);
  threadData->lastEquationSolved = 37868;
}

/*
equation index: 37869
type: SIMPLE_ASSIGN
chassis.pVehicle.pSprungMass.inertia[2,3] = pVehicle.pSprungMass.inertia[2,3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37869(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37869};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5845]] /* chassis.pVehicle.pSprungMass.inertia[2,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6783]] /* pVehicle.pSprungMass.inertia[2,3] PARAM */);
  threadData->lastEquationSolved = 37869;
}

/*
equation index: 37870
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.pSprungMass.inertia[2,3] = chassis.pVehicle.pSprungMass.inertia[2,3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37870(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37870};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4914]] /* chassis.detailedChassis.spaceFrame.pSprungMass.inertia[2,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5845]] /* chassis.pVehicle.pSprungMass.inertia[2,3] PARAM */);
  threadData->lastEquationSolved = 37870;
}

/*
equation index: 37871
type: SIMPLE_ASSIGN
chassis.pVehicle.pSprungMass.inertia[2,2] = pVehicle.pSprungMass.inertia[2,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37871(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37871};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5844]] /* chassis.pVehicle.pSprungMass.inertia[2,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6782]] /* pVehicle.pSprungMass.inertia[2,2] PARAM */);
  threadData->lastEquationSolved = 37871;
}

/*
equation index: 37872
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.pSprungMass.inertia[2,2] = chassis.pVehicle.pSprungMass.inertia[2,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37872(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37872};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4913]] /* chassis.detailedChassis.spaceFrame.pSprungMass.inertia[2,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5844]] /* chassis.pVehicle.pSprungMass.inertia[2,2] PARAM */);
  threadData->lastEquationSolved = 37872;
}

/*
equation index: 37873
type: SIMPLE_ASSIGN
chassis.pVehicle.pSprungMass.inertia[2,1] = pVehicle.pSprungMass.inertia[2,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37873(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37873};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5843]] /* chassis.pVehicle.pSprungMass.inertia[2,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6781]] /* pVehicle.pSprungMass.inertia[2,1] PARAM */);
  threadData->lastEquationSolved = 37873;
}

/*
equation index: 37874
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.pSprungMass.inertia[2,1] = chassis.pVehicle.pSprungMass.inertia[2,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37874(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37874};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4912]] /* chassis.detailedChassis.spaceFrame.pSprungMass.inertia[2,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5843]] /* chassis.pVehicle.pSprungMass.inertia[2,1] PARAM */);
  threadData->lastEquationSolved = 37874;
}

/*
equation index: 37875
type: SIMPLE_ASSIGN
chassis.pVehicle.pSprungMass.inertia[1,3] = pVehicle.pSprungMass.inertia[1,3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37875(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37875};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5842]] /* chassis.pVehicle.pSprungMass.inertia[1,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6780]] /* pVehicle.pSprungMass.inertia[1,3] PARAM */);
  threadData->lastEquationSolved = 37875;
}

/*
equation index: 37876
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.pSprungMass.inertia[1,3] = chassis.pVehicle.pSprungMass.inertia[1,3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37876(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37876};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4911]] /* chassis.detailedChassis.spaceFrame.pSprungMass.inertia[1,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5842]] /* chassis.pVehicle.pSprungMass.inertia[1,3] PARAM */);
  threadData->lastEquationSolved = 37876;
}

/*
equation index: 37877
type: SIMPLE_ASSIGN
chassis.pVehicle.pSprungMass.inertia[1,2] = pVehicle.pSprungMass.inertia[1,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37877(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37877};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5841]] /* chassis.pVehicle.pSprungMass.inertia[1,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6779]] /* pVehicle.pSprungMass.inertia[1,2] PARAM */);
  threadData->lastEquationSolved = 37877;
}

/*
equation index: 37878
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.pSprungMass.inertia[1,2] = chassis.pVehicle.pSprungMass.inertia[1,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37878(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37878};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4910]] /* chassis.detailedChassis.spaceFrame.pSprungMass.inertia[1,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5841]] /* chassis.pVehicle.pSprungMass.inertia[1,2] PARAM */);
  threadData->lastEquationSolved = 37878;
}

/*
equation index: 37884
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.midToCG.width = 0.09901294229785942 / world.defaultWidthFraction
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37884(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37884};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4876]] /* chassis.detailedChassis.spaceFrame.midToCG.width PARAM */) = DIVISION_SIM(0.09901294229785942,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 37884;
}

/*
equation index: 37885
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.midToCG.height = chassis.detailedChassis.spaceFrame.midToCG.width
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37885(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37885};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4865]] /* chassis.detailedChassis.spaceFrame.midToCG.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4876]] /* chassis.detailedChassis.spaceFrame.midToCG.width PARAM */);
  threadData->lastEquationSolved = 37885;
}

/*
equation index: 37896
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.midToCG.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37896(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37896};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[337]] /* chassis.detailedChassis.spaceFrame.midToCG.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 37896;
}

/*
equation index: 37901
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.midToAft.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37901(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37901};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[336]] /* chassis.detailedChassis.spaceFrame.midToAft.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 37901;
}

/*
equation index: 37902
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.midToAft.shape.shapeType = chassis.detailedChassis.spaceFrame.midToAft.shapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37902(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37902};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[335]] /* chassis.detailedChassis.spaceFrame.midToAft.shape.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[336]] /* chassis.detailedChassis.spaceFrame.midToAft.shapeType PARAM */);
  threadData->lastEquationSolved = 37902;
}

/*
equation index: 37904
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.midToAft.width = 0.7747 / world.defaultWidthFraction
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37904(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37904};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4860]] /* chassis.detailedChassis.spaceFrame.midToAft.width PARAM */) = DIVISION_SIM(0.7747,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 37904;
}

/*
equation index: 37905
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.midToAft.height = chassis.detailedChassis.spaceFrame.midToAft.width
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37905(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37905};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4849]] /* chassis.detailedChassis.spaceFrame.midToAft.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4860]] /* chassis.detailedChassis.spaceFrame.midToAft.width PARAM */);
  threadData->lastEquationSolved = 37905;
}

/*
equation index: 37920
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.midToFore.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37920(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37920};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[339]] /* chassis.detailedChassis.spaceFrame.midToFore.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 37920;
}

/*
equation index: 37921
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.midToFore.shape.shapeType = chassis.detailedChassis.spaceFrame.midToFore.shapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37921(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37921};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[338]] /* chassis.detailedChassis.spaceFrame.midToFore.shape.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[339]] /* chassis.detailedChassis.spaceFrame.midToFore.shapeType PARAM */);
  threadData->lastEquationSolved = 37921;
}

/*
equation index: 37923
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.midToFore.width = 0.7747 / world.defaultWidthFraction
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37923(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37923};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4892]] /* chassis.detailedChassis.spaceFrame.midToFore.width PARAM */) = DIVISION_SIM(0.7747,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 37923;
}

/*
equation index: 37924
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.midToFore.height = chassis.detailedChassis.spaceFrame.midToFore.width
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37924(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37924};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4881]] /* chassis.detailedChassis.spaceFrame.midToFore.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4892]] /* chassis.detailedChassis.spaceFrame.midToFore.width PARAM */);
  threadData->lastEquationSolved = 37924;
}

/*
equation index: 37939
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.sphere.shapeType = "sphere"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37939(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37939};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[341]] /* chassis.detailedChassis.spaceFrame.sprungBody.sphere.shapeType PARAM */) = _OMC_LIT47;
  threadData->lastEquationSolved = 37939;
}

/*
equation index: 37940
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.cylinder.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37940(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37940};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[340]] /* chassis.detailedChassis.spaceFrame.sprungBody.cylinder.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 37940;
}

/*
equation index: 37942
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.phi_start[3] = chassis.detailedChassis.spaceFrame.sprungBody.angles_start[3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37942(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37942};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4965]] /* chassis.detailedChassis.spaceFrame.sprungBody.phi_start[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4960]] /* chassis.detailedChassis.spaceFrame.sprungBody.angles_start[3] PARAM */);
  threadData->lastEquationSolved = 37942;
}

/*
equation index: 37944
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.phi_start[2] = chassis.detailedChassis.spaceFrame.sprungBody.angles_start[2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37944(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37944};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4964]] /* chassis.detailedChassis.spaceFrame.sprungBody.phi_start[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4959]] /* chassis.detailedChassis.spaceFrame.sprungBody.angles_start[2] PARAM */);
  threadData->lastEquationSolved = 37944;
}

/*
equation index: 37946
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.phi_start[1] = chassis.detailedChassis.spaceFrame.sprungBody.angles_start[1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37946(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37946};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4963]] /* chassis.detailedChassis.spaceFrame.sprungBody.phi_start[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4958]] /* chassis.detailedChassis.spaceFrame.sprungBody.angles_start[1] PARAM */);
  threadData->lastEquationSolved = 37946;
}

/*
equation index: 37947
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.spaceFrame.sprungBody.Q_start = {0.0, 0.0, 0.0, 1.0}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37947(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37947};
  real_array tmp30;
  real_array_create(&tmp30, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4942]] /* chassis.detailedChassis.spaceFrame.sprungBody.Q_start[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)4);
  real_array_copy_data(_OMC_LIT46, tmp30);
  threadData->lastEquationSolved = 37947;
}

/*
equation index: 37960
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.pSprung.inertia[3,3] = chassis.pVehicle.pSprungMass.inertia[3,3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37960(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37960};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4904]] /* chassis.detailedChassis.spaceFrame.pSprung.inertia[3,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5848]] /* chassis.pVehicle.pSprungMass.inertia[3,3] PARAM */);
  threadData->lastEquationSolved = 37960;
}

/*
equation index: 37961
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.I_33 = chassis.detailedChassis.spaceFrame.pSprung.inertia[3,3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37961(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37961};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4941]] /* chassis.detailedChassis.spaceFrame.sprungBody.I_33 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4904]] /* chassis.detailedChassis.spaceFrame.pSprung.inertia[3,3] PARAM */);
  threadData->lastEquationSolved = 37961;
}

/*
equation index: 37962
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.I[3,3] = chassis.detailedChassis.spaceFrame.sprungBody.I_33
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37962(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37962};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4935]] /* chassis.detailedChassis.spaceFrame.sprungBody.I[3,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4941]] /* chassis.detailedChassis.spaceFrame.sprungBody.I_33 PARAM */);
  threadData->lastEquationSolved = 37962;
}

/*
equation index: 37963
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.pSprung.inertia[3,2] = chassis.pVehicle.pSprungMass.inertia[3,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37963(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37963};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4903]] /* chassis.detailedChassis.spaceFrame.pSprung.inertia[3,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5847]] /* chassis.pVehicle.pSprungMass.inertia[3,2] PARAM */);
  threadData->lastEquationSolved = 37963;
}

/*
equation index: 37964
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.I_32 = chassis.detailedChassis.spaceFrame.pSprung.inertia[3,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37964(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37964};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4940]] /* chassis.detailedChassis.spaceFrame.sprungBody.I_32 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4903]] /* chassis.detailedChassis.spaceFrame.pSprung.inertia[3,2] PARAM */);
  threadData->lastEquationSolved = 37964;
}

/*
equation index: 37965
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.I[3,2] = chassis.detailedChassis.spaceFrame.sprungBody.I_32
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37965(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37965};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4934]] /* chassis.detailedChassis.spaceFrame.sprungBody.I[3,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4940]] /* chassis.detailedChassis.spaceFrame.sprungBody.I_32 PARAM */);
  threadData->lastEquationSolved = 37965;
}

/*
equation index: 37966
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.pSprung.inertia[3,1] = chassis.pVehicle.pSprungMass.inertia[3,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37966(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37966};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4902]] /* chassis.detailedChassis.spaceFrame.pSprung.inertia[3,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5846]] /* chassis.pVehicle.pSprungMass.inertia[3,1] PARAM */);
  threadData->lastEquationSolved = 37966;
}

/*
equation index: 37967
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.I_31 = chassis.detailedChassis.spaceFrame.pSprung.inertia[3,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37967(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37967};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4939]] /* chassis.detailedChassis.spaceFrame.sprungBody.I_31 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4902]] /* chassis.detailedChassis.spaceFrame.pSprung.inertia[3,1] PARAM */);
  threadData->lastEquationSolved = 37967;
}

/*
equation index: 37968
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.I[3,1] = chassis.detailedChassis.spaceFrame.sprungBody.I_31
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37968(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37968};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4933]] /* chassis.detailedChassis.spaceFrame.sprungBody.I[3,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4939]] /* chassis.detailedChassis.spaceFrame.sprungBody.I_31 PARAM */);
  threadData->lastEquationSolved = 37968;
}

/*
equation index: 37969
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.I[2,3] = chassis.detailedChassis.spaceFrame.sprungBody.I_32
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37969(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37969};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4932]] /* chassis.detailedChassis.spaceFrame.sprungBody.I[2,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4940]] /* chassis.detailedChassis.spaceFrame.sprungBody.I_32 PARAM */);
  threadData->lastEquationSolved = 37969;
}

/*
equation index: 37970
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.pSprung.inertia[2,2] = chassis.pVehicle.pSprungMass.inertia[2,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37970(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37970};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4900]] /* chassis.detailedChassis.spaceFrame.pSprung.inertia[2,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5844]] /* chassis.pVehicle.pSprungMass.inertia[2,2] PARAM */);
  threadData->lastEquationSolved = 37970;
}

/*
equation index: 37971
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.I_22 = chassis.detailedChassis.spaceFrame.pSprung.inertia[2,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37971(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37971};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4938]] /* chassis.detailedChassis.spaceFrame.sprungBody.I_22 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4900]] /* chassis.detailedChassis.spaceFrame.pSprung.inertia[2,2] PARAM */);
  threadData->lastEquationSolved = 37971;
}

/*
equation index: 37972
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.I[2,2] = chassis.detailedChassis.spaceFrame.sprungBody.I_22
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37972(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37972};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4931]] /* chassis.detailedChassis.spaceFrame.sprungBody.I[2,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4938]] /* chassis.detailedChassis.spaceFrame.sprungBody.I_22 PARAM */);
  threadData->lastEquationSolved = 37972;
}

/*
equation index: 37973
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.pSprung.inertia[2,1] = chassis.pVehicle.pSprungMass.inertia[2,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37973(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37973};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4899]] /* chassis.detailedChassis.spaceFrame.pSprung.inertia[2,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5843]] /* chassis.pVehicle.pSprungMass.inertia[2,1] PARAM */);
  threadData->lastEquationSolved = 37973;
}

/*
equation index: 37974
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.I_21 = chassis.detailedChassis.spaceFrame.pSprung.inertia[2,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37974(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37974};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4937]] /* chassis.detailedChassis.spaceFrame.sprungBody.I_21 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4899]] /* chassis.detailedChassis.spaceFrame.pSprung.inertia[2,1] PARAM */);
  threadData->lastEquationSolved = 37974;
}

/*
equation index: 37975
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.I[2,1] = chassis.detailedChassis.spaceFrame.sprungBody.I_21
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37975(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37975};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4930]] /* chassis.detailedChassis.spaceFrame.sprungBody.I[2,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4937]] /* chassis.detailedChassis.spaceFrame.sprungBody.I_21 PARAM */);
  threadData->lastEquationSolved = 37975;
}

/*
equation index: 37976
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.I[1,3] = chassis.detailedChassis.spaceFrame.sprungBody.I_31
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37976(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37976};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4929]] /* chassis.detailedChassis.spaceFrame.sprungBody.I[1,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4939]] /* chassis.detailedChassis.spaceFrame.sprungBody.I_31 PARAM */);
  threadData->lastEquationSolved = 37976;
}

/*
equation index: 37977
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.I[1,2] = chassis.detailedChassis.spaceFrame.sprungBody.I_21
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37977(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37977};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4928]] /* chassis.detailedChassis.spaceFrame.sprungBody.I[1,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4937]] /* chassis.detailedChassis.spaceFrame.sprungBody.I_21 PARAM */);
  threadData->lastEquationSolved = 37977;
}

/*
equation index: 37978
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.pSprung.inertia[1,1] = chassis.pVehicle.pSprungMass.inertia[1,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37978(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37978};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4896]] /* chassis.detailedChassis.spaceFrame.pSprung.inertia[1,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5840]] /* chassis.pVehicle.pSprungMass.inertia[1,1] PARAM */);
  threadData->lastEquationSolved = 37978;
}

/*
equation index: 37979
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.I_11 = chassis.detailedChassis.spaceFrame.pSprung.inertia[1,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37979(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37979};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4936]] /* chassis.detailedChassis.spaceFrame.sprungBody.I_11 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4896]] /* chassis.detailedChassis.spaceFrame.pSprung.inertia[1,1] PARAM */);
  threadData->lastEquationSolved = 37979;
}

/*
equation index: 37980
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.I[1,1] = chassis.detailedChassis.spaceFrame.sprungBody.I_11
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_37980(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,37980};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4927]] /* chassis.detailedChassis.spaceFrame.sprungBody.I[1,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4936]] /* chassis.detailedChassis.spaceFrame.sprungBody.I_11 PARAM */);
  threadData->lastEquationSolved = 37980;
}

/*
equation index: 38005
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.pSprung.inertia[2,3] = chassis.pVehicle.pSprungMass.inertia[2,3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38005(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38005};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4901]] /* chassis.detailedChassis.spaceFrame.pSprung.inertia[2,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5845]] /* chassis.pVehicle.pSprungMass.inertia[2,3] PARAM */);
  threadData->lastEquationSolved = 38005;
}

/*
equation index: 38006
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.pSprung.inertia[1,3] = chassis.pVehicle.pSprungMass.inertia[1,3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38006(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38006};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4898]] /* chassis.detailedChassis.spaceFrame.pSprung.inertia[1,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5842]] /* chassis.pVehicle.pSprungMass.inertia[1,3] PARAM */);
  threadData->lastEquationSolved = 38006;
}

/*
equation index: 38007
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.pSprung.inertia[1,2] = chassis.pVehicle.pSprungMass.inertia[1,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38007(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38007};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4897]] /* chassis.detailedChassis.spaceFrame.pSprung.inertia[1,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5841]] /* chassis.pVehicle.pSprungMass.inertia[1,2] PARAM */);
  threadData->lastEquationSolved = 38007;
}

/*
equation index: 38018
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38018(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38018};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[266]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38018;
}

/*
equation index: 38019
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38019(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38019};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[265]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38019;
}

/*
equation index: 38020
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.sphericalShape_b.shapeType = "sphere"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38020(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38020};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[264]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.sphericalShape_b.shapeType PARAM */) = _OMC_LIT47;
  threadData->lastEquationSolved = 38020;
}

/*
equation index: 38021
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodShapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38021(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38021};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[263]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodShapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38021;
}

/*
equation index: 38022
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodShape.shapeType = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodShapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38022(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38022};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[262]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodShape.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[263]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodShapeType PARAM */);
  threadData->lastEquationSolved = 38022;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_2399(DATA *data, threadData_t *threadData);


/*
equation index: 38026
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.kinematicConstraint = chassis.detailedChassis.rrAxleDW.rightPushrod.kinematicConstraint
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38026(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38026};
  (data->simulationInfo->booleanParameter[data->simulationInfo->booleanParamsIndex[398]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.kinematicConstraint PARAM */) = (data->simulationInfo->booleanParameter[data->simulationInfo->booleanParamsIndex[394]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.kinematicConstraint PARAM */);
  threadData->lastEquationSolved = 38026;
}

/*
equation index: 38039
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightPushrod.n1_a = if noEvent(sqrt(BobLib.Utilities.Math.Vector.mirrorXZ({0.887962410598, 0.302708516859, 0.346251803151}) * BobLib.Utilities.Math.Vector.mirrorXZ({0.887962410598, 0.302708516859, 0.346251803151})) >= 2.220446049250313e-14) then BobLib.Utilities.Math.Vector.mirrorXZ({0.887962410598, 0.302708516859, 0.346251803151}) / sqrt(BobLib.Utilities.Math.Vector.mirrorXZ({0.887962410598, 0.302708516859, 0.346251803151}) * BobLib.Utilities.Math.Vector.mirrorXZ({0.887962410598, 0.302708516859, 0.346251803151})) else BobLib.Utilities.Math.Vector.mirrorXZ({0.887962410598, 0.302708516859, 0.346251803151}) / 2.220446049250313e-14
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38039(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38039};
  modelica_real tmp31;
  modelica_boolean tmp32;
  modelica_real tmp33;
  modelica_boolean tmp34;
  real_array tmp35;
  real_array tmp36;
  tmp31 = mul_real_scalar_product(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT48), omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT48));
  if(!(tmp31 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(BobLib.Utilities.Math.Vector.mirrorXZ({0.887962410598, 0.302708516859, 0.346251803151}) * BobLib.Utilities.Math.Vector.mirrorXZ({0.887962410598, 0.302708516859, 0.346251803151})) was %g should be >= 0", tmp31);
    }
  }tmp32 = GreaterEq(sqrt(tmp31),2.220446049250313e-14);
  tmp34 = (modelica_boolean)tmp32;
  if(tmp34)
  {
    tmp33 = mul_real_scalar_product(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT48), omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT48));
    if(!(tmp33 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(BobLib.Utilities.Math.Vector.mirrorXZ({0.887962410598, 0.302708516859, 0.346251803151}) * BobLib.Utilities.Math.Vector.mirrorXZ({0.887962410598, 0.302708516859, 0.346251803151})) was %g should be >= 0", tmp33);
      }
    }
    tmp35 = division_alloc_real_array_scalar(threadData,omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT48),sqrt(tmp33),"sqrt(BobLib.Utilities.Math.Vector.mirrorXZ({0.887962410598, 0.302708516859, 0.346251803151}) * BobLib.Utilities.Math.Vector.mirrorXZ({0.887962410598, 0.302708516859, 0.346251803151}))");
  }
  else
  {
    tmp35 = division_alloc_real_array_scalar(threadData,omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT48),2.220446049250313e-14,"2.220446049250313e-14");
  }
  real_array_create(&tmp36, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3826]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.n1_a[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(tmp35, tmp36);
  threadData->lastEquationSolved = 38039;
}

/*
equation index: 38040
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightPushrod.r_b = {-1.53509479, -0.50330883, 0.26648017}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38040(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38040};
  real_array tmp37;
  real_array_create(&tmp37, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3832]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.r_b[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(_OMC_LIT49, tmp37);
  threadData->lastEquationSolved = 38040;
}

/*
equation index: 38041
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightPushrod.r_a = {-1.41267566, -0.35197317, 0.08484064}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38041(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38041};
  real_array tmp38;
  real_array_create(&tmp38, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3829]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.r_a[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(_OMC_LIT50, tmp38);
  threadData->lastEquationSolved = 38041;
}

/*
equation index: 38042
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38042(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38042};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[190]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38042;
}

/*
equation index: 38043
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38043(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38043};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[189]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38043;
}

/*
equation index: 38044
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.sphericalShape_b.shapeType = "sphere"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38044(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38044};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[188]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.sphericalShape_b.shapeType PARAM */) = _OMC_LIT47;
  threadData->lastEquationSolved = 38044;
}

/*
equation index: 38045
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.rodShapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38045(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38045};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[187]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.rodShapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38045;
}

/*
equation index: 38046
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.rodShape.shapeType = chassis.detailedChassis.rrAxleDW.leftPushrod.rod.rodShapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38046(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38046};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[186]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.rodShape.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[187]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.rodShapeType PARAM */);
  threadData->lastEquationSolved = 38046;
}

/*
equation index: 38047
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia = {-0.4598135704301268, 0.5684257857248273, 0.6822489329939707}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38047(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38047};
  real_array tmp39;
  real_array_create(&tmp39, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2751]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(_OMC_LIT51, tmp39);
  threadData->lastEquationSolved = 38047;
}

/*
equation index: 38050
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.kinematicConstraint = chassis.detailedChassis.rrAxleDW.leftPushrod.kinematicConstraint
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38050(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38050};
  (data->simulationInfo->booleanParameter[data->simulationInfo->booleanParamsIndex[291]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.kinematicConstraint PARAM */) = (data->simulationInfo->booleanParameter[data->simulationInfo->booleanParamsIndex[287]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.kinematicConstraint PARAM */);
  threadData->lastEquationSolved = 38050;
}

/*
equation index: 38066
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.leftPushrod.n1_a = {0.8879624105983084, 0.30270851685910516, 0.34625180315112025}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38066(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38066};
  real_array tmp40;
  real_array_create(&tmp40, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2734]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.n1_a[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(_OMC_LIT52, tmp40);
  threadData->lastEquationSolved = 38066;
}

/*
equation index: 38074
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toStabar.width = 0.26401103223799494 / world.defaultWidthFraction
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38074(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38074};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4839]] /* chassis.detailedChassis.rrAxleDW.toStabar.width PARAM */) = DIVISION_SIM(0.26401103223799494,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 38074;
}

/*
equation index: 38075
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toStabar.height = chassis.detailedChassis.rrAxleDW.toStabar.width
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38075(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38075};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4828]] /* chassis.detailedChassis.rrAxleDW.toStabar.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4839]] /* chassis.detailedChassis.rrAxleDW.toStabar.width PARAM */);
  threadData->lastEquationSolved = 38075;
}

/*
equation index: 38086
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toStabar.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38086(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38086};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[334]] /* chassis.detailedChassis.rrAxleDW.toStabar.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38086;
}

/*
equation index: 38098
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightApex.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38098(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38098};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[328]] /* chassis.detailedChassis.rrAxleDW.toRightApex.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38098;
}

/*
equation index: 38099
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.toRightApex.r = {0.0189788099999999, 0.023461769999999937, -0.028159829999999997}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38099(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38099};
  real_array tmp41;
  real_array_create(&tmp41, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4737]] /* chassis.detailedChassis.rrAxleDW.toRightApex.r[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(_OMC_LIT53, tmp41);
  threadData->lastEquationSolved = 38099;
}

/*
equation index: 38102
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toLeftApex.width = 0.041275003406152415 / world.defaultWidthFraction
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38102(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38102};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4631]] /* chassis.detailedChassis.rrAxleDW.toLeftApex.width PARAM */) = DIVISION_SIM(0.041275003406152415,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 38102;
}

/*
equation index: 38103
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toLeftApex.height = chassis.detailedChassis.rrAxleDW.toLeftApex.width
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38103(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38103};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4620]] /* chassis.detailedChassis.rrAxleDW.toLeftApex.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4631]] /* chassis.detailedChassis.rrAxleDW.toLeftApex.width PARAM */);
  threadData->lastEquationSolved = 38103;
}

/*
equation index: 38114
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toLeftApex.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38114(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38114};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[321]] /* chassis.detailedChassis.rrAxleDW.toLeftApex.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38114;
}

/*
equation index: 38120
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightShock.width = 0.33800610323891134 / world.defaultWidthFraction
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38120(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38120};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4791]] /* chassis.detailedChassis.rrAxleDW.toRightShock.width PARAM */) = DIVISION_SIM(0.33800610323891134,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 38120;
}

/*
equation index: 38121
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightShock.height = chassis.detailedChassis.rrAxleDW.toRightShock.width
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38121(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38121};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4780]] /* chassis.detailedChassis.rrAxleDW.toRightShock.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4791]] /* chassis.detailedChassis.rrAxleDW.toRightShock.width PARAM */);
  threadData->lastEquationSolved = 38121;
}

/*
equation index: 38132
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightShock.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38132(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38132};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[331]] /* chassis.detailedChassis.rrAxleDW.toRightShock.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38132;
}

/*
equation index: 38133
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightShock.r[3] = -0.199898 + BobLib.Utilities.Math.Vector.mirrorXZ({-1.50192144, 0.28884688, 0.36889916})[3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38133(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38133};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4787]] /* chassis.detailedChassis.rrAxleDW.toRightShock.r[3] PARAM */) = -0.199898 + real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT27), 2);
  threadData->lastEquationSolved = 38133;
}

/*
equation index: 38135
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightShock.r[1] = 1.5494 + BobLib.Utilities.Math.Vector.mirrorXZ({-1.50192144, 0.28884688, 0.36889916})[1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38135(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38135};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4785]] /* chassis.detailedChassis.rrAxleDW.toRightShock.r[1] PARAM */) = 1.5494 + real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT27), 0);
  threadData->lastEquationSolved = 38135;
}

/*
equation index: 38138
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightBellcrank.width = 0.3431650519548978 / world.defaultWidthFraction
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38138(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38138};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4759]] /* chassis.detailedChassis.rrAxleDW.toRightBellcrank.width PARAM */) = DIVISION_SIM(0.3431650519548978,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 38138;
}

/*
equation index: 38139
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightBellcrank.height = chassis.detailedChassis.rrAxleDW.toRightBellcrank.width
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38139(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38139};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4748]] /* chassis.detailedChassis.rrAxleDW.toRightBellcrank.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4759]] /* chassis.detailedChassis.rrAxleDW.toRightBellcrank.width PARAM */);
  threadData->lastEquationSolved = 38139;
}

/*
equation index: 38150
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightBellcrank.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38150(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38150};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[329]] /* chassis.detailedChassis.rrAxleDW.toRightBellcrank.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38150;
}

/*
equation index: 38151
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightBellcrank.r[3] = -0.199898 + BobLib.Utilities.Math.Vector.mirrorXZ({-1.39886851, 0.29230126, 0.1016})[3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38151(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38151};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4755]] /* chassis.detailedChassis.rrAxleDW.toRightBellcrank.r[3] PARAM */) = -0.199898 + real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT26), 2);
  threadData->lastEquationSolved = 38151;
}

/*
equation index: 38153
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightBellcrank.r[1] = 1.5494 + BobLib.Utilities.Math.Vector.mirrorXZ({-1.39886851, 0.29230126, 0.1016})[1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38153(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38153};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4753]] /* chassis.detailedChassis.rrAxleDW.toRightBellcrank.r[1] PARAM */) = 1.5494 + real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT26), 0);
  threadData->lastEquationSolved = 38153;
}

/*
equation index: 38156
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toLeftShock.width = 0.33800610323891134 / world.defaultWidthFraction
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38156(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38156};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4679]] /* chassis.detailedChassis.rrAxleDW.toLeftShock.width PARAM */) = DIVISION_SIM(0.33800610323891134,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 38156;
}

/*
equation index: 38157
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toLeftShock.height = chassis.detailedChassis.rrAxleDW.toLeftShock.width
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38157(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38157};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4668]] /* chassis.detailedChassis.rrAxleDW.toLeftShock.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4679]] /* chassis.detailedChassis.rrAxleDW.toLeftShock.width PARAM */);
  threadData->lastEquationSolved = 38157;
}

/*
equation index: 38168
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toLeftShock.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38168(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38168};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[324]] /* chassis.detailedChassis.rrAxleDW.toLeftShock.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38168;
}

/*
equation index: 38174
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toLeftBellcrank.width = 0.3431650519548978 / world.defaultWidthFraction
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38174(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38174};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4647]] /* chassis.detailedChassis.rrAxleDW.toLeftBellcrank.width PARAM */) = DIVISION_SIM(0.3431650519548978,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 38174;
}

/*
equation index: 38175
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toLeftBellcrank.height = chassis.detailedChassis.rrAxleDW.toLeftBellcrank.width
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38175(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38175};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4636]] /* chassis.detailedChassis.rrAxleDW.toLeftBellcrank.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4647]] /* chassis.detailedChassis.rrAxleDW.toLeftBellcrank.width PARAM */);
  threadData->lastEquationSolved = 38175;
}

/*
equation index: 38186
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toLeftBellcrank.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38186(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38186};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[322]] /* chassis.detailedChassis.rrAxleDW.toLeftBellcrank.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38186;
}

/*
equation index: 38194
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.shapeType = "sphere"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38194(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38194};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[182]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.shapeType PARAM */) = _OMC_LIT47;
  threadData->lastEquationSolved = 38194;
}

/*
equation index: 38195
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftDroplink.shape_a.shapeType = "sphere"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38195(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38195};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[181]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_a.shapeType PARAM */) = _OMC_LIT47;
  threadData->lastEquationSolved = 38195;
}

/*
equation index: 38196
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftDroplink.shape_rod.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38196(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38196};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[183]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_rod.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38196;
}

/*
equation index: 38207
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.shapeType = "sphere"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38207(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38207};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[258]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.shapeType PARAM */) = _OMC_LIT47;
  threadData->lastEquationSolved = 38207;
}

/*
equation index: 38208
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightDroplink.shape_a.shapeType = "sphere"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38208(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38208};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[257]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_a.shapeType PARAM */) = _OMC_LIT47;
  threadData->lastEquationSolved = 38208;
}

/*
equation index: 38209
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightDroplink.shape_rod.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38209(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38209};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[259]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_rod.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38209;
}

/*
equation index: 38220
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.toRightBarEnd.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38220(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38220};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[320]] /* chassis.detailedChassis.rrAxleDW.stabar.toRightBarEnd.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38220;
}

/*
equation index: 38221
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.toRightBarEnd.shape.shapeType = chassis.detailedChassis.rrAxleDW.stabar.toRightBarEnd.shapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38221(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38221};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[319]] /* chassis.detailedChassis.rrAxleDW.stabar.toRightBarEnd.shape.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[320]] /* chassis.detailedChassis.rrAxleDW.stabar.toRightBarEnd.shapeType PARAM */);
  threadData->lastEquationSolved = 38221;
}

/*
equation index: 38235
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.toRightBarEnd.r[3] = -0.41224196 + BobLib.Utilities.Math.Vector.mirrorXZ({-1.3925183, 0.3032125, 0.41224196})[3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38235(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38235};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4611]] /* chassis.detailedChassis.rrAxleDW.stabar.toRightBarEnd.r[3] PARAM */) = -0.41224196 + real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT54), 2);
  threadData->lastEquationSolved = 38235;
}

/*
equation index: 38237
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.toRightBarEnd.r[1] = 1.3925183 + BobLib.Utilities.Math.Vector.mirrorXZ({-1.3925183, 0.3032125, 0.41224196})[1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38237(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38237};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4609]] /* chassis.detailedChassis.rrAxleDW.stabar.toRightBarEnd.r[1] PARAM */) = 1.3925183 + real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT54), 0);
  threadData->lastEquationSolved = 38237;
}

/*
equation index: 38239
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.toLeftBarEnd.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38239(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38239};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[316]] /* chassis.detailedChassis.rrAxleDW.stabar.toLeftBarEnd.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38239;
}

/*
equation index: 38240
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.toLeftBarEnd.shape.shapeType = chassis.detailedChassis.rrAxleDW.stabar.toLeftBarEnd.shapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38240(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38240};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[315]] /* chassis.detailedChassis.rrAxleDW.stabar.toLeftBarEnd.shape.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[316]] /* chassis.detailedChassis.rrAxleDW.stabar.toLeftBarEnd.shapeType PARAM */);
  threadData->lastEquationSolved = 38240;
}

/*
equation index: 38259
type: SIMPLE_ASSIGN
chassis.pRrStabar.barRate = pVehicle.pRrStabar.barRate
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38259(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38259};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5088]] /* chassis.pRrStabar.barRate PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6628]] /* pVehicle.pRrStabar.barRate PARAM */);
  threadData->lastEquationSolved = 38259;
}

/*
equation index: 38260
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.pStabar.barRate = chassis.pRrStabar.barRate
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38260(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38260};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3634]] /* chassis.detailedChassis.rrAxleDW.pStabar.barRate PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5088]] /* chassis.pRrStabar.barRate PARAM */);
  threadData->lastEquationSolved = 38260;
}

/*
equation index: 38261
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.pStabar.barRate = chassis.detailedChassis.rrAxleDW.pStabar.barRate
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38261(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38261};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4537]] /* chassis.detailedChassis.rrAxleDW.stabar.pStabar.barRate PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3634]] /* chassis.detailedChassis.rrAxleDW.pStabar.barRate PARAM */);
  threadData->lastEquationSolved = 38261;
}

/*
equation index: 38262
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.spring.c = chassis.detailedChassis.rrAxleDW.stabar.pStabar.barRate
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38262(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38262};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4544]] /* chassis.detailedChassis.rrAxleDW.stabar.spring.c PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4537]] /* chassis.detailedChassis.rrAxleDW.stabar.pStabar.barRate PARAM */);
  threadData->lastEquationSolved = 38262;
}

/*
equation index: 38270
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.mountAxis.cylinderDiameter = world.defaultJointWidth
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38270(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38270};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4528]] /* chassis.detailedChassis.rrAxleDW.stabar.mountAxis.cylinderDiameter PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6897]] /* world.defaultJointWidth PARAM */);
  threadData->lastEquationSolved = 38270;
}

/*
equation index: 38271
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.mountAxis.cylinderLength = world.defaultJointLength
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38271(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38271};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4529]] /* chassis.detailedChassis.rrAxleDW.stabar.mountAxis.cylinderLength PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6896]] /* world.defaultJointLength PARAM */);
  threadData->lastEquationSolved = 38271;
}

/*
equation index: 38278
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.stabarAxis.cylinder.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38278(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38278};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[312]] /* chassis.detailedChassis.rrAxleDW.stabar.stabarAxis.cylinder.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38278;
}

/*
equation index: 38290
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.toRightArmEnd.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38290(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38290};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[318]] /* chassis.detailedChassis.rrAxleDW.stabar.toRightArmEnd.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38290;
}

/*
equation index: 38291
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.toRightArmEnd.shape.shapeType = chassis.detailedChassis.rrAxleDW.stabar.toRightArmEnd.shapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38291(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38291};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[317]] /* chassis.detailedChassis.rrAxleDW.stabar.toRightArmEnd.shape.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[318]] /* chassis.detailedChassis.rrAxleDW.stabar.toRightArmEnd.shapeType PARAM */);
  threadData->lastEquationSolved = 38291;
}

/*
equation index: 38301
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.stabar.toRightArmEnd.r = {-0.037494529999999804, -0.0, -0.006765359999999998}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38301(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38301};
  real_array tmp42;
  real_array_create(&tmp42, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4593]] /* chassis.detailedChassis.rrAxleDW.stabar.toRightArmEnd.r[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(_OMC_LIT55, tmp42);
  threadData->lastEquationSolved = 38301;
}

/*
equation index: 38303
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.toLeftArmEnd.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38303(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38303};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[314]] /* chassis.detailedChassis.rrAxleDW.stabar.toLeftArmEnd.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38303;
}

/*
equation index: 38304
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.toLeftArmEnd.shape.shapeType = chassis.detailedChassis.rrAxleDW.stabar.toLeftArmEnd.shapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38304(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38304};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[313]] /* chassis.detailedChassis.rrAxleDW.stabar.toLeftArmEnd.shape.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[314]] /* chassis.detailedChassis.rrAxleDW.stabar.toLeftArmEnd.shapeType PARAM */);
  threadData->lastEquationSolved = 38304;
}

/*
equation index: 38330
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38330(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38330};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[274]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38330;
}

/*
equation index: 38331
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.shapeType = chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38331(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38331};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[273]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[274]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShapeType PARAM */);
  threadData->lastEquationSolved = 38331;
}

/*
equation index: 38341
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularDamper.combiTable1D.u_max = Modelica.Blocks.Tables.Internal.getTable1DAbscissaUmax(chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularDamper.combiTable1D.tableID)
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38341(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38341};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3863]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularDamper.combiTable1D.u_max PARAM */) = omc_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmax(threadData, (data->simulationInfo->extObjs[6]));
  threadData->lastEquationSolved = 38341;
}

/*
equation index: 38342
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularDamper.combiTable1D.u_min = Modelica.Blocks.Tables.Internal.getTable1DAbscissaUmin(chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularDamper.combiTable1D.tableID)
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38342(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38342};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3864]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularDamper.combiTable1D.u_min PARAM */) = omc_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmin(threadData, (data->simulationInfo->extObjs[6]));
  threadData->lastEquationSolved = 38342;
}

/*
equation index: 38347
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularDamper.combiTable1D.fileName = "NoName"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38347(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38347};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[268]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularDamper.combiTable1D.fileName PARAM */) = _OMC_LIT43;
  threadData->lastEquationSolved = 38347;
}

/*
equation index: 38348
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularDamper.combiTable1D.tableName = "NoName"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38348(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38348};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[269]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularDamper.combiTable1D.tableName PARAM */) = _OMC_LIT43;
  threadData->lastEquationSolved = 38348;
}

/*
equation index: 38353
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularSpring.combiTable1D.u_max = Modelica.Blocks.Tables.Internal.getTable1DAbscissaUmax(chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularSpring.combiTable1D.tableID)
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38353(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38353};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3876]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularSpring.combiTable1D.u_max PARAM */) = omc_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmax(threadData, (data->simulationInfo->extObjs[7]));
  threadData->lastEquationSolved = 38353;
}

/*
equation index: 38354
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularSpring.combiTable1D.u_min = Modelica.Blocks.Tables.Internal.getTable1DAbscissaUmin(chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularSpring.combiTable1D.tableID)
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38354(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38354};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3877]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularSpring.combiTable1D.u_min PARAM */) = omc_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmin(threadData, (data->simulationInfo->extObjs[7]));
  threadData->lastEquationSolved = 38354;
}

/*
equation index: 38359
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularSpring.combiTable1D.fileName = "NoName"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38359(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38359};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[271]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularSpring.combiTable1D.fileName PARAM */) = _OMC_LIT43;
  threadData->lastEquationSolved = 38359;
}

/*
equation index: 38360
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularSpring.combiTable1D.tableName = "NoName"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38360(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38360};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[272]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularSpring.combiTable1D.tableName PARAM */) = _OMC_LIT43;
  threadData->lastEquationSolved = 38360;
}

/*
equation index: 38363
type: SIMPLE_ASSIGN
chassis.pVehicle.pRrAxleDW.springFreeLength = pVehicle.pRrAxleDW.springFreeLength
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38363(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38363};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5600]] /* chassis.pVehicle.pRrAxleDW.springFreeLength PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6538]] /* pVehicle.pRrAxleDW.springFreeLength PARAM */);
  threadData->lastEquationSolved = 38363;
}

/*
equation index: 38364
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.pAxle.springFreeLength = chassis.pVehicle.pRrAxleDW.springFreeLength
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38364(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38364};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3463]] /* chassis.detailedChassis.rrAxleDW.pAxle.springFreeLength PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5600]] /* chassis.pVehicle.pRrAxleDW.springFreeLength PARAM */);
  threadData->lastEquationSolved = 38364;
}

/*
equation index: 38365
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightShockLinkage.s_0 = chassis.detailedChassis.rrAxleDW.pAxle.springFreeLength
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38365(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38365};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3908]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.s_0 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3463]] /* chassis.detailedChassis.rrAxleDW.pAxle.springFreeLength PARAM */);
  threadData->lastEquationSolved = 38365;
}

/*
equation index: 38366
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularSpring.s_0 = chassis.detailedChassis.rrAxleDW.rightShockLinkage.s_0
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38366(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38366};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3879]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularSpring.s_0 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3908]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.s_0 PARAM */);
  threadData->lastEquationSolved = 38366;
}

/*
equation index: 38372
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightShockLinkage.n_b = if noEvent(sqrt(BobLib.Utilities.Math.Vector.mirrorXZ({0.03914444000000006, -0.06907159000000002, -0.040000480000000005}) * BobLib.Utilities.Math.Vector.mirrorXZ({0.03914444000000006, -0.06907159000000002, -0.040000480000000005})) >= 2.220446049250313e-14) then BobLib.Utilities.Math.Vector.mirrorXZ({0.03914444000000006, -0.06907159000000002, -0.040000480000000005}) / sqrt(BobLib.Utilities.Math.Vector.mirrorXZ({0.03914444000000006, -0.06907159000000002, -0.040000480000000005}) * BobLib.Utilities.Math.Vector.mirrorXZ({0.03914444000000006, -0.06907159000000002, -0.040000480000000005})) else BobLib.Utilities.Math.Vector.mirrorXZ({0.03914444000000006, -0.06907159000000002, -0.040000480000000005}) / 2.220446049250313e-14
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38372(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38372};
  modelica_real tmp43;
  modelica_boolean tmp44;
  modelica_real tmp45;
  modelica_boolean tmp46;
  real_array tmp47;
  real_array tmp48;
  tmp43 = mul_real_scalar_product(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT56), omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT56));
  if(!(tmp43 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(BobLib.Utilities.Math.Vector.mirrorXZ({0.03914444000000006, -0.06907159000000002, -0.040000480000000005}) * BobLib.Utilities.Math.Vector.mirrorXZ({0.03914444000000006, -0.06907159000000002, -0.040000480000000005})) was %g should be >= 0", tmp43);
    }
  }tmp44 = GreaterEq(sqrt(tmp43),2.220446049250313e-14);
  tmp46 = (modelica_boolean)tmp44;
  if(tmp46)
  {
    tmp45 = mul_real_scalar_product(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT56), omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT56));
    if(!(tmp45 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(BobLib.Utilities.Math.Vector.mirrorXZ({0.03914444000000006, -0.06907159000000002, -0.040000480000000005}) * BobLib.Utilities.Math.Vector.mirrorXZ({0.03914444000000006, -0.06907159000000002, -0.040000480000000005})) was %g should be >= 0", tmp45);
      }
    }
    tmp47 = division_alloc_real_array_scalar(threadData,omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT56),sqrt(tmp45),"sqrt(BobLib.Utilities.Math.Vector.mirrorXZ({0.03914444000000006, -0.06907159000000002, -0.040000480000000005}) * BobLib.Utilities.Math.Vector.mirrorXZ({0.03914444000000006, -0.06907159000000002, -0.040000480000000005}))");
  }
  else
  {
    tmp47 = division_alloc_real_array_scalar(threadData,omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT56),2.220446049250313e-14,"2.220446049250313e-14");
  }
  real_array_create(&tmp48, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3899]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.n_b[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(tmp47, tmp48);
  threadData->lastEquationSolved = 38372;
}

/*
equation index: 38373
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightShockLinkage.n_a = {0.887962410598, -0.302708516859, 0.346251803151}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38373(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38373};
  real_array tmp49;
  real_array_create(&tmp49, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3896]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.n_a[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(_OMC_LIT57, tmp49);
  threadData->lastEquationSolved = 38373;
}

/*
equation index: 38374
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightShockLinkage.r_b = {-1.50192144, -0.28884688, 0.36889916}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38374(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38374};
  real_array tmp50;
  real_array_create(&tmp50, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3905]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.r_b[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(_OMC_LIT58, tmp50);
  threadData->lastEquationSolved = 38374;
}

/*
equation index: 38375
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightShockLinkage.r_a = {-1.43801295, -0.36137285, 0.14160048}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38375(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38375};
  real_array tmp51;
  real_array_create(&tmp51, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3902]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.r_a[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(_OMC_LIT59, tmp51);
  threadData->lastEquationSolved = 38375;
}

/*
equation index: 38383
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38383(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38383};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[256]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38383;
}

/*
equation index: 38392
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38392(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38392};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[255]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38392;
}

/*
equation index: 38401
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38401(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38401};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[254]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38401;
}

/*
equation index: 38403
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38403(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38403};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[252]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38403;
}

/*
equation index: 38404
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.vis.shapeType = chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.shapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38404(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38404};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[253]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.vis.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[252]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.shapeType PARAM */);
  threadData->lastEquationSolved = 38404;
}

/*
equation index: 38406
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_3.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38406(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38406};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[250]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_3.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38406;
}

/*
equation index: 38407
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_3.vis.shapeType = chassis.detailedChassis.rrAxleDW.rightBellcrank.side_3.shapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38407(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38407};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[251]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_3.vis.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[250]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_3.shapeType PARAM */);
  threadData->lastEquationSolved = 38407;
}

/*
equation index: 38409
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_2.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38409(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38409};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[248]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_2.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38409;
}

/*
equation index: 38410
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_2.vis.shapeType = chassis.detailedChassis.rrAxleDW.rightBellcrank.side_2.shapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38410(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38410};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[249]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_2.vis.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[248]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_2.shapeType PARAM */);
  threadData->lastEquationSolved = 38410;
}

/*
equation index: 38412
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_1.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38412(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38412};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[246]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_1.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38412;
}

/*
equation index: 38413
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_1.vis.shapeType = chassis.detailedChassis.rrAxleDW.rightBellcrank.side_1.shapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38413(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38413};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[247]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_1.vis.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[246]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_1.shapeType PARAM */);
  threadData->lastEquationSolved = 38413;
}

/*
equation index: 38418
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.revolute.cylinder.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38418(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38418};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[245]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.revolute.cylinder.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38418;
}

/*
equation index: 38419
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightBellcrank.revolute.e = {0.8879624105983084, -0.30270851685910516, 0.34625180315112025}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38419(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38419};
  real_array tmp52;
  real_array_create(&tmp52, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3715]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.revolute.e[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(_OMC_LIT60, tmp52);
  threadData->lastEquationSolved = 38419;
}

/*
equation index: 38423
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightBellcrank.revolute.n = {0.8879624105983084, -0.30270851685910516, 0.34625180315112025}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38423(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38423};
  real_array tmp53;
  real_array_create(&tmp53, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3719]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.revolute.n[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(_OMC_LIT60, tmp53);
  threadData->lastEquationSolved = 38423;
}

/*
equation index: 38428
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_3 = {-1.41346984, -0.31057564, 0.12306883}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38428(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38428};
  real_array tmp54;
  real_array_create(&tmp54, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3703]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_3[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(_OMC_LIT61, tmp54);
  threadData->lastEquationSolved = 38428;
}

/*
equation index: 38429
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2 = {-1.43801295, -0.36137285, 0.14160048}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38429(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38429};
  real_array tmp55;
  real_array_create(&tmp55, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3700]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(_OMC_LIT59, tmp55);
  threadData->lastEquationSolved = 38429;
}

/*
equation index: 38430
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1 = {-1.41267566, -0.35197317, 0.08484064}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38430(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38430};
  real_array tmp56;
  real_array_create(&tmp56, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3697]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(_OMC_LIT50, tmp56);
  threadData->lastEquationSolved = 38430;
}

/*
equation index: 38431
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightBellcrank.pivotAxis = {0.887962410598, -0.302708516859, 0.346251803151}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38431(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38431};
  real_array tmp57;
  real_array_create(&tmp57, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3709]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pivotAxis[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(_OMC_LIT57, tmp57);
  threadData->lastEquationSolved = 38431;
}

/*
equation index: 38432
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightBellcrank.pivot = {-1.39886851, -0.29230126, 0.1016}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38432(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38432};
  real_array tmp58;
  real_array_create(&tmp58, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3706]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pivot[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(_OMC_LIT62, tmp58);
  threadData->lastEquationSolved = 38432;
}

/*
equation index: 38433
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38433(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38433};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[198]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38433;
}

/*
equation index: 38434
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.shapeType = chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38434(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38434};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[197]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[198]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShapeType PARAM */);
  threadData->lastEquationSolved = 38434;
}

/*
equation index: 38444
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularDamper.combiTable1D.u_max = Modelica.Blocks.Tables.Internal.getTable1DAbscissaUmax(chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularDamper.combiTable1D.tableID)
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38444(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38444};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2774]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularDamper.combiTable1D.u_max PARAM */) = omc_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmax(threadData, (data->simulationInfo->extObjs[4]));
  threadData->lastEquationSolved = 38444;
}

/*
equation index: 38445
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularDamper.combiTable1D.u_min = Modelica.Blocks.Tables.Internal.getTable1DAbscissaUmin(chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularDamper.combiTable1D.tableID)
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38445(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38445};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2775]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularDamper.combiTable1D.u_min PARAM */) = omc_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmin(threadData, (data->simulationInfo->extObjs[4]));
  threadData->lastEquationSolved = 38445;
}

/*
equation index: 38450
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularDamper.combiTable1D.fileName = "NoName"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38450(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38450};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[192]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularDamper.combiTable1D.fileName PARAM */) = _OMC_LIT43;
  threadData->lastEquationSolved = 38450;
}

/*
equation index: 38451
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularDamper.combiTable1D.tableName = "NoName"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38451(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38451};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[193]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularDamper.combiTable1D.tableName PARAM */) = _OMC_LIT43;
  threadData->lastEquationSolved = 38451;
}

/*
equation index: 38456
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularSpring.combiTable1D.u_max = Modelica.Blocks.Tables.Internal.getTable1DAbscissaUmax(chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularSpring.combiTable1D.tableID)
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38456(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38456};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2787]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularSpring.combiTable1D.u_max PARAM */) = omc_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmax(threadData, (data->simulationInfo->extObjs[5]));
  threadData->lastEquationSolved = 38456;
}

/*
equation index: 38457
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularSpring.combiTable1D.u_min = Modelica.Blocks.Tables.Internal.getTable1DAbscissaUmin(chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularSpring.combiTable1D.tableID)
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38457(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38457};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2788]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularSpring.combiTable1D.u_min PARAM */) = omc_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmin(threadData, (data->simulationInfo->extObjs[5]));
  threadData->lastEquationSolved = 38457;
}

/*
equation index: 38462
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularSpring.combiTable1D.fileName = "NoName"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38462(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38462};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[195]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularSpring.combiTable1D.fileName PARAM */) = _OMC_LIT43;
  threadData->lastEquationSolved = 38462;
}

/*
equation index: 38463
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularSpring.combiTable1D.tableName = "NoName"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38463(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38463};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[196]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularSpring.combiTable1D.tableName PARAM */) = _OMC_LIT43;
  threadData->lastEquationSolved = 38463;
}

/*
equation index: 38466
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftShockLinkage.s_0 = chassis.detailedChassis.rrAxleDW.pAxle.springFreeLength
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38466(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38466};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2819]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.s_0 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3463]] /* chassis.detailedChassis.rrAxleDW.pAxle.springFreeLength PARAM */);
  threadData->lastEquationSolved = 38466;
}

/*
equation index: 38467
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularSpring.s_0 = chassis.detailedChassis.rrAxleDW.leftShockLinkage.s_0
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38467(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38467};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2790]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularSpring.s_0 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2819]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.s_0 PARAM */);
  threadData->lastEquationSolved = 38467;
}

/*
equation index: 38473
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.leftShockLinkage.n_b = {0.4403199064379694, -0.7769582614113715, -0.44994915270403263}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38473(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38473};
  real_array tmp59;
  real_array_create(&tmp59, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2810]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.n_b[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(_OMC_LIT63, tmp59);
  threadData->lastEquationSolved = 38473;
}

/*
equation index: 38484
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.toThirdPickup.width = 0.059381334137746544 / world.defaultWidthFraction
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38484(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38484};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2674]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.toThirdPickup.width PARAM */) = DIVISION_SIM(0.059381334137746544,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 38484;
}

/*
equation index: 38485
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.toThirdPickup.height = chassis.detailedChassis.rrAxleDW.leftBellcrank.toThirdPickup.width
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38485(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38485};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2663]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.toThirdPickup.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2674]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.toThirdPickup.width PARAM */);
  threadData->lastEquationSolved = 38485;
}

/*
equation index: 38496
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.toThirdPickup.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38496(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38496};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[180]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.toThirdPickup.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38496;
}

/*
equation index: 38502
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.toSecondPickup.width = 0.0628650275230362 / world.defaultWidthFraction
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38502(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38502};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2658]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.toSecondPickup.width PARAM */) = DIVISION_SIM(0.0628650275230362,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 38502;
}

/*
equation index: 38503
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.toSecondPickup.height = chassis.detailedChassis.rrAxleDW.leftBellcrank.toSecondPickup.width
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38503(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38503};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2647]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.toSecondPickup.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2658]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.toSecondPickup.width PARAM */);
  threadData->lastEquationSolved = 38503;
}

/*
equation index: 38514
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.toSecondPickup.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38514(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38514};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[179]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.toSecondPickup.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38514;
}

/*
equation index: 38520
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.toFirstPickup.width = 0.06350000300614325 / world.defaultWidthFraction
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38520(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38520};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2642]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.toFirstPickup.width PARAM */) = DIVISION_SIM(0.06350000300614325,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 38520;
}

/*
equation index: 38521
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.toFirstPickup.height = chassis.detailedChassis.rrAxleDW.leftBellcrank.toFirstPickup.width
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38521(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38521};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2631]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.toFirstPickup.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2642]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.toFirstPickup.width PARAM */);
  threadData->lastEquationSolved = 38521;
}

/*
equation index: 38532
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.toFirstPickup.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38532(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38532};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[178]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.toFirstPickup.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38532;
}

/*
equation index: 38537
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38537(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38537};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[176]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38537;
}

/*
equation index: 38538
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.vis.shapeType = chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.shapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38538(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38538};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[177]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.vis.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[176]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.shapeType PARAM */);
  threadData->lastEquationSolved = 38538;
}

/*
equation index: 38540
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_3.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38540(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38540};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[174]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_3.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38540;
}

/*
equation index: 38541
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_3.vis.shapeType = chassis.detailedChassis.rrAxleDW.leftBellcrank.side_3.shapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38541(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38541};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[175]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_3.vis.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[174]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_3.shapeType PARAM */);
  threadData->lastEquationSolved = 38541;
}

/*
equation index: 38543
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_2.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38543(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38543};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[172]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_2.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38543;
}

/*
equation index: 38544
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_2.vis.shapeType = chassis.detailedChassis.rrAxleDW.leftBellcrank.side_2.shapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38544(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38544};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[173]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_2.vis.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[172]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_2.shapeType PARAM */);
  threadData->lastEquationSolved = 38544;
}

/*
equation index: 38546
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_1.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38546(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38546};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[170]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_1.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38546;
}

/*
equation index: 38547
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_1.vis.shapeType = chassis.detailedChassis.rrAxleDW.leftBellcrank.side_1.shapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38547(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38547};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[171]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_1.vis.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[170]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_1.shapeType PARAM */);
  threadData->lastEquationSolved = 38547;
}

/*
equation index: 38552
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.revolute.cylinder.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38552(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38552};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[169]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.revolute.cylinder.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38552;
}

/*
equation index: 38553
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.leftBellcrank.revolute.e = {0.8879624105983084, 0.30270851685910516, 0.34625180315112025}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38553(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38553};
  real_array tmp60;
  real_array_create(&tmp60, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2623]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.revolute.e[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(_OMC_LIT52, tmp60);
  threadData->lastEquationSolved = 38553;
}

/*
equation index: 38557
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.leftBellcrank.revolute.n = {0.8879624105983084, 0.30270851685910516, 0.34625180315112025}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38557(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38557};
  real_array tmp61;
  real_array_create(&tmp61, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2627]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.revolute.n[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(_OMC_LIT52, tmp61);
  threadData->lastEquationSolved = 38557;
}

/*
equation index: 38577
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.sphere.shapeType = "sphere"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38577(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38577};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[288]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.sphere.shapeType PARAM */) = _OMC_LIT47;
  threadData->lastEquationSolved = 38577;
}

/*
equation index: 38578
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.cylinder.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38578(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38578};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[287]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.cylinder.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38578;
}

/*
equation index: 38580
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.phi_start[3] = chassis.detailedChassis.rrAxleDW.rightUnsprungBody.angles_start[3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38580(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38580};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4308]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.phi_start[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4303]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.angles_start[3] PARAM */);
  threadData->lastEquationSolved = 38580;
}

/*
equation index: 38582
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.phi_start[2] = chassis.detailedChassis.rrAxleDW.rightUnsprungBody.angles_start[2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38582(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38582};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4307]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.phi_start[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4302]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.angles_start[2] PARAM */);
  threadData->lastEquationSolved = 38582;
}

/*
equation index: 38584
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.phi_start[1] = chassis.detailedChassis.rrAxleDW.rightUnsprungBody.angles_start[1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38584(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38584};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4306]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.phi_start[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4301]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.angles_start[1] PARAM */);
  threadData->lastEquationSolved = 38584;
}

/*
equation index: 38585
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightUnsprungBody.Q_start = {0.0, 0.0, 0.0, 1.0}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38585(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38585};
  real_array tmp62;
  real_array_create(&tmp62, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4285]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.Q_start[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)4);
  real_array_copy_data(_OMC_LIT46, tmp62);
  threadData->lastEquationSolved = 38585;
}

/*
equation index: 38619
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.sphere.shapeType = "sphere"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38619(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38619};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[261]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.sphere.shapeType PARAM */) = _OMC_LIT47;
  threadData->lastEquationSolved = 38619;
}

/*
equation index: 38620
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.cylinder.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38620(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38620};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[260]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.cylinder.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38620;
}

/*
equation index: 38622
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.phi_start[3] = chassis.detailedChassis.rrAxleDW.rightLCABody.angles_start[3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38622(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38622};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3813]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.phi_start[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3808]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.angles_start[3] PARAM */);
  threadData->lastEquationSolved = 38622;
}

/*
equation index: 38624
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.phi_start[2] = chassis.detailedChassis.rrAxleDW.rightLCABody.angles_start[2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38624(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38624};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3812]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.phi_start[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3807]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.angles_start[2] PARAM */);
  threadData->lastEquationSolved = 38624;
}

/*
equation index: 38626
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.phi_start[1] = chassis.detailedChassis.rrAxleDW.rightLCABody.angles_start[1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38626(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38626};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3811]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.phi_start[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3806]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.angles_start[1] PARAM */);
  threadData->lastEquationSolved = 38626;
}

/*
equation index: 38627
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightLCABody.Q_start = {0.0, 0.0, 0.0, 1.0}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38627(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38627};
  real_array tmp63;
  real_array_create(&tmp63, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3790]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.Q_start[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)4);
  real_array_copy_data(_OMC_LIT46, tmp63);
  threadData->lastEquationSolved = 38627;
}

/*
equation index: 38661
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.shapeType = "sphere"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38661(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38661};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[286]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.shapeType PARAM */) = _OMC_LIT47;
  threadData->lastEquationSolved = 38661;
}

/*
equation index: 38662
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.cylinder.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38662(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38662};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[285]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.cylinder.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38662;
}

/*
equation index: 38664
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.phi_start[3] = chassis.detailedChassis.rrAxleDW.rightUCABody.angles_start[3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38664(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38664};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4259]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.phi_start[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4254]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.angles_start[3] PARAM */);
  threadData->lastEquationSolved = 38664;
}

/*
equation index: 38666
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.phi_start[2] = chassis.detailedChassis.rrAxleDW.rightUCABody.angles_start[2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38666(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38666};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4258]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.phi_start[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4253]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.angles_start[2] PARAM */);
  threadData->lastEquationSolved = 38666;
}

/*
equation index: 38668
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.phi_start[1] = chassis.detailedChassis.rrAxleDW.rightUCABody.angles_start[1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38668(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38668};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4257]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.phi_start[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4252]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.angles_start[1] PARAM */);
  threadData->lastEquationSolved = 38668;
}

/*
equation index: 38669
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightUCABody.Q_start = {0.0, 0.0, 0.0, 1.0}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38669(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38669};
  real_array tmp64;
  real_array_create(&tmp64, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4236]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.Q_start[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)4);
  real_array_copy_data(_OMC_LIT46, tmp64);
  threadData->lastEquationSolved = 38669;
}

/*
equation index: 38703
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.sphere.shapeType = "sphere"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38703(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38703};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[212]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.sphere.shapeType PARAM */) = _OMC_LIT47;
  threadData->lastEquationSolved = 38703;
}

/*
equation index: 38704
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.cylinder.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38704(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38704};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[211]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.cylinder.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38704;
}

/*
equation index: 38706
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.phi_start[3] = chassis.detailedChassis.rrAxleDW.leftUnsprungBody.angles_start[3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38706(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38706};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3219]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.phi_start[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3214]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.angles_start[3] PARAM */);
  threadData->lastEquationSolved = 38706;
}

/*
equation index: 38708
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.phi_start[2] = chassis.detailedChassis.rrAxleDW.leftUnsprungBody.angles_start[2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38708(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38708};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3218]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.phi_start[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3213]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.angles_start[2] PARAM */);
  threadData->lastEquationSolved = 38708;
}

/*
equation index: 38710
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.phi_start[1] = chassis.detailedChassis.rrAxleDW.leftUnsprungBody.angles_start[1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38710(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38710};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3217]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.phi_start[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3212]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.angles_start[1] PARAM */);
  threadData->lastEquationSolved = 38710;
}

/*
equation index: 38711
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.leftUnsprungBody.Q_start = {0.0, 0.0, 0.0, 1.0}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38711(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38711};
  real_array tmp65;
  real_array_create(&tmp65, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3196]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.Q_start[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)4);
  real_array_copy_data(_OMC_LIT46, tmp65);
  threadData->lastEquationSolved = 38711;
}

/*
equation index: 38724
type: SIMPLE_ASSIGN
chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[3,3] = pVehicle.pRrAxleMass.unsprungMass.inertia[3,3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38724(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38724};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5652]] /* chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[3,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6590]] /* pVehicle.pRrAxleMass.unsprungMass.inertia[3,3] PARAM */);
  threadData->lastEquationSolved = 38724;
}

/*
equation index: 38725
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[3,3] = chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[3,3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38725(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38725};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3515]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[3,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5652]] /* chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[3,3] PARAM */);
  threadData->lastEquationSolved = 38725;
}

/*
equation index: 38726
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_33 = chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[3,3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38726(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38726};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3195]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_33 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3515]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[3,3] PARAM */);
  threadData->lastEquationSolved = 38726;
}

/*
equation index: 38727
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I[3,3] = chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_33
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38727(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38727};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3189]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I[3,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3195]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_33 PARAM */);
  threadData->lastEquationSolved = 38727;
}

/*
equation index: 38728
type: SIMPLE_ASSIGN
chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[3,2] = pVehicle.pRrAxleMass.unsprungMass.inertia[3,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38728(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38728};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5651]] /* chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[3,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6589]] /* pVehicle.pRrAxleMass.unsprungMass.inertia[3,2] PARAM */);
  threadData->lastEquationSolved = 38728;
}

/*
equation index: 38729
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[3,2] = chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[3,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38729(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38729};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3514]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[3,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5651]] /* chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[3,2] PARAM */);
  threadData->lastEquationSolved = 38729;
}

/*
equation index: 38730
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_32 = chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[3,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38730(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38730};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3194]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_32 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3514]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[3,2] PARAM */);
  threadData->lastEquationSolved = 38730;
}

/*
equation index: 38731
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I[3,2] = chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_32
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38731(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38731};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3188]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I[3,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3194]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_32 PARAM */);
  threadData->lastEquationSolved = 38731;
}

/*
equation index: 38732
type: SIMPLE_ASSIGN
chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[3,1] = pVehicle.pRrAxleMass.unsprungMass.inertia[3,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38732(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38732};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5650]] /* chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[3,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6588]] /* pVehicle.pRrAxleMass.unsprungMass.inertia[3,1] PARAM */);
  threadData->lastEquationSolved = 38732;
}

/*
equation index: 38733
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[3,1] = chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[3,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38733(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38733};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3513]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[3,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5650]] /* chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[3,1] PARAM */);
  threadData->lastEquationSolved = 38733;
}

/*
equation index: 38734
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_31 = chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[3,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38734(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38734};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3193]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_31 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3513]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[3,1] PARAM */);
  threadData->lastEquationSolved = 38734;
}

/*
equation index: 38735
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I[3,1] = chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_31
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38735(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38735};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3187]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I[3,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3193]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_31 PARAM */);
  threadData->lastEquationSolved = 38735;
}

/*
equation index: 38736
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I[2,3] = chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_32
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38736(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38736};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3186]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I[2,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3194]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_32 PARAM */);
  threadData->lastEquationSolved = 38736;
}

/*
equation index: 38737
type: SIMPLE_ASSIGN
chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[2,2] = pVehicle.pRrAxleMass.unsprungMass.inertia[2,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38737(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38737};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5648]] /* chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[2,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6586]] /* pVehicle.pRrAxleMass.unsprungMass.inertia[2,2] PARAM */);
  threadData->lastEquationSolved = 38737;
}

/*
equation index: 38738
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[2,2] = chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[2,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38738(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38738};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3511]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[2,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5648]] /* chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[2,2] PARAM */);
  threadData->lastEquationSolved = 38738;
}

/*
equation index: 38739
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_22 = chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[2,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38739(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38739};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3192]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_22 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3511]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[2,2] PARAM */);
  threadData->lastEquationSolved = 38739;
}

/*
equation index: 38740
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I[2,2] = chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_22
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38740(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38740};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3185]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I[2,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3192]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_22 PARAM */);
  threadData->lastEquationSolved = 38740;
}

/*
equation index: 38741
type: SIMPLE_ASSIGN
chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[2,1] = pVehicle.pRrAxleMass.unsprungMass.inertia[2,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38741(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38741};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5647]] /* chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[2,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6585]] /* pVehicle.pRrAxleMass.unsprungMass.inertia[2,1] PARAM */);
  threadData->lastEquationSolved = 38741;
}

/*
equation index: 38742
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[2,1] = chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[2,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38742(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38742};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3510]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[2,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5647]] /* chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[2,1] PARAM */);
  threadData->lastEquationSolved = 38742;
}

/*
equation index: 38743
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_21 = chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[2,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38743(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38743};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3191]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_21 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3510]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[2,1] PARAM */);
  threadData->lastEquationSolved = 38743;
}

/*
equation index: 38744
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I[2,1] = chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_21
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38744(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38744};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3184]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I[2,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3191]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_21 PARAM */);
  threadData->lastEquationSolved = 38744;
}

/*
equation index: 38745
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I[1,3] = chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_31
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38745(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38745};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3183]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I[1,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3193]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_31 PARAM */);
  threadData->lastEquationSolved = 38745;
}

/*
equation index: 38746
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I[1,2] = chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_21
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38746(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38746};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3182]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I[1,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3191]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_21 PARAM */);
  threadData->lastEquationSolved = 38746;
}

/*
equation index: 38747
type: SIMPLE_ASSIGN
chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[1,1] = pVehicle.pRrAxleMass.unsprungMass.inertia[1,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38747(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38747};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5644]] /* chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[1,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6582]] /* pVehicle.pRrAxleMass.unsprungMass.inertia[1,1] PARAM */);
  threadData->lastEquationSolved = 38747;
}

/*
equation index: 38748
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[1,1] = chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[1,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38748(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38748};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3507]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[1,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5644]] /* chassis.pVehicle.pRrAxleMass.unsprungMass.inertia[1,1] PARAM */);
  threadData->lastEquationSolved = 38748;
}

/*
equation index: 38749
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_11 = chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[1,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38749(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38749};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3190]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_11 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3507]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.unsprungMass.inertia[1,1] PARAM */);
  threadData->lastEquationSolved = 38749;
}

/*
equation index: 38750
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I[1,1] = chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_11
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38750(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38750};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3181]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I[1,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3190]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.I_11 PARAM */);
  threadData->lastEquationSolved = 38750;
}

/*
equation index: 38775
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.sphere.shapeType = "sphere"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38775(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38775};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[185]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.sphere.shapeType PARAM */) = _OMC_LIT47;
  threadData->lastEquationSolved = 38775;
}

/*
equation index: 38776
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.cylinder.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38776(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38776};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[184]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.cylinder.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38776;
}

/*
equation index: 38778
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.phi_start[3] = chassis.detailedChassis.rrAxleDW.leftLCABody.angles_start[3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38778(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38778};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2721]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.phi_start[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2716]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.angles_start[3] PARAM */);
  threadData->lastEquationSolved = 38778;
}

/*
equation index: 38780
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.phi_start[2] = chassis.detailedChassis.rrAxleDW.leftLCABody.angles_start[2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38780(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38780};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2720]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.phi_start[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2715]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.angles_start[2] PARAM */);
  threadData->lastEquationSolved = 38780;
}

/*
equation index: 38782
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.phi_start[1] = chassis.detailedChassis.rrAxleDW.leftLCABody.angles_start[1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38782(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38782};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2719]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.phi_start[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2714]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.angles_start[1] PARAM */);
  threadData->lastEquationSolved = 38782;
}

/*
equation index: 38783
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.leftLCABody.Q_start = {0.0, 0.0, 0.0, 1.0}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38783(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38783};
  real_array tmp66;
  real_array_create(&tmp66, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2698]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.Q_start[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)4);
  real_array_copy_data(_OMC_LIT46, tmp66);
  threadData->lastEquationSolved = 38783;
}

/*
equation index: 38796
type: SIMPLE_ASSIGN
chassis.pVehicle.pRrAxleMass.lcaMass.inertia[3,3] = pVehicle.pRrAxleMass.lcaMass.inertia[3,3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38796(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38796};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5613]] /* chassis.pVehicle.pRrAxleMass.lcaMass.inertia[3,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6551]] /* pVehicle.pRrAxleMass.lcaMass.inertia[3,3] PARAM */);
  threadData->lastEquationSolved = 38796;
}

/*
equation index: 38797
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[3,3] = chassis.pVehicle.pRrAxleMass.lcaMass.inertia[3,3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38797(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38797};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3476]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[3,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5613]] /* chassis.pVehicle.pRrAxleMass.lcaMass.inertia[3,3] PARAM */);
  threadData->lastEquationSolved = 38797;
}

/*
equation index: 38798
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.I_33 = chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[3,3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38798(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38798};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2697]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I_33 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3476]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[3,3] PARAM */);
  threadData->lastEquationSolved = 38798;
}

/*
equation index: 38799
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.I[3,3] = chassis.detailedChassis.rrAxleDW.leftLCABody.I_33
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38799(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38799};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2691]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I[3,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2697]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I_33 PARAM */);
  threadData->lastEquationSolved = 38799;
}

/*
equation index: 38800
type: SIMPLE_ASSIGN
chassis.pVehicle.pRrAxleMass.lcaMass.inertia[3,2] = pVehicle.pRrAxleMass.lcaMass.inertia[3,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38800(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38800};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5612]] /* chassis.pVehicle.pRrAxleMass.lcaMass.inertia[3,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6550]] /* pVehicle.pRrAxleMass.lcaMass.inertia[3,2] PARAM */);
  threadData->lastEquationSolved = 38800;
}

/*
equation index: 38801
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[3,2] = chassis.pVehicle.pRrAxleMass.lcaMass.inertia[3,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38801(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38801};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3475]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[3,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5612]] /* chassis.pVehicle.pRrAxleMass.lcaMass.inertia[3,2] PARAM */);
  threadData->lastEquationSolved = 38801;
}

/*
equation index: 38802
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.I_32 = chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[3,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38802(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38802};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2696]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I_32 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3475]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[3,2] PARAM */);
  threadData->lastEquationSolved = 38802;
}

/*
equation index: 38803
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.I[3,2] = chassis.detailedChassis.rrAxleDW.leftLCABody.I_32
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38803(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38803};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2690]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I[3,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2696]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I_32 PARAM */);
  threadData->lastEquationSolved = 38803;
}

/*
equation index: 38804
type: SIMPLE_ASSIGN
chassis.pVehicle.pRrAxleMass.lcaMass.inertia[3,1] = pVehicle.pRrAxleMass.lcaMass.inertia[3,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38804(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38804};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5611]] /* chassis.pVehicle.pRrAxleMass.lcaMass.inertia[3,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6549]] /* pVehicle.pRrAxleMass.lcaMass.inertia[3,1] PARAM */);
  threadData->lastEquationSolved = 38804;
}

/*
equation index: 38805
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[3,1] = chassis.pVehicle.pRrAxleMass.lcaMass.inertia[3,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38805(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38805};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3474]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[3,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5611]] /* chassis.pVehicle.pRrAxleMass.lcaMass.inertia[3,1] PARAM */);
  threadData->lastEquationSolved = 38805;
}

/*
equation index: 38806
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.I_31 = chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[3,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38806(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38806};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2695]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I_31 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3474]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[3,1] PARAM */);
  threadData->lastEquationSolved = 38806;
}

/*
equation index: 38807
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.I[3,1] = chassis.detailedChassis.rrAxleDW.leftLCABody.I_31
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38807(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38807};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2689]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I[3,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2695]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I_31 PARAM */);
  threadData->lastEquationSolved = 38807;
}

/*
equation index: 38808
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.I[2,3] = chassis.detailedChassis.rrAxleDW.leftLCABody.I_32
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38808(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38808};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2688]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I[2,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2696]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I_32 PARAM */);
  threadData->lastEquationSolved = 38808;
}

/*
equation index: 38809
type: SIMPLE_ASSIGN
chassis.pVehicle.pRrAxleMass.lcaMass.inertia[2,2] = pVehicle.pRrAxleMass.lcaMass.inertia[2,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38809(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38809};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5609]] /* chassis.pVehicle.pRrAxleMass.lcaMass.inertia[2,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6547]] /* pVehicle.pRrAxleMass.lcaMass.inertia[2,2] PARAM */);
  threadData->lastEquationSolved = 38809;
}

/*
equation index: 38810
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[2,2] = chassis.pVehicle.pRrAxleMass.lcaMass.inertia[2,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38810(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38810};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3472]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[2,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5609]] /* chassis.pVehicle.pRrAxleMass.lcaMass.inertia[2,2] PARAM */);
  threadData->lastEquationSolved = 38810;
}

/*
equation index: 38811
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.I_22 = chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[2,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38811(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38811};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2694]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I_22 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3472]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[2,2] PARAM */);
  threadData->lastEquationSolved = 38811;
}

/*
equation index: 38812
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.I[2,2] = chassis.detailedChassis.rrAxleDW.leftLCABody.I_22
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38812(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38812};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2687]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I[2,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2694]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I_22 PARAM */);
  threadData->lastEquationSolved = 38812;
}

/*
equation index: 38813
type: SIMPLE_ASSIGN
chassis.pVehicle.pRrAxleMass.lcaMass.inertia[2,1] = pVehicle.pRrAxleMass.lcaMass.inertia[2,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38813(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38813};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5608]] /* chassis.pVehicle.pRrAxleMass.lcaMass.inertia[2,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6546]] /* pVehicle.pRrAxleMass.lcaMass.inertia[2,1] PARAM */);
  threadData->lastEquationSolved = 38813;
}

/*
equation index: 38814
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[2,1] = chassis.pVehicle.pRrAxleMass.lcaMass.inertia[2,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38814(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38814};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3471]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[2,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5608]] /* chassis.pVehicle.pRrAxleMass.lcaMass.inertia[2,1] PARAM */);
  threadData->lastEquationSolved = 38814;
}

/*
equation index: 38815
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.I_21 = chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[2,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38815(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38815};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2693]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I_21 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3471]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[2,1] PARAM */);
  threadData->lastEquationSolved = 38815;
}

/*
equation index: 38816
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.I[2,1] = chassis.detailedChassis.rrAxleDW.leftLCABody.I_21
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38816(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38816};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2686]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I[2,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2693]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I_21 PARAM */);
  threadData->lastEquationSolved = 38816;
}

/*
equation index: 38817
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.I[1,3] = chassis.detailedChassis.rrAxleDW.leftLCABody.I_31
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38817(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38817};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2685]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I[1,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2695]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I_31 PARAM */);
  threadData->lastEquationSolved = 38817;
}

/*
equation index: 38818
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.I[1,2] = chassis.detailedChassis.rrAxleDW.leftLCABody.I_21
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38818(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38818};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2684]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I[1,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2693]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I_21 PARAM */);
  threadData->lastEquationSolved = 38818;
}

/*
equation index: 38819
type: SIMPLE_ASSIGN
chassis.pVehicle.pRrAxleMass.lcaMass.inertia[1,1] = pVehicle.pRrAxleMass.lcaMass.inertia[1,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38819(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38819};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5605]] /* chassis.pVehicle.pRrAxleMass.lcaMass.inertia[1,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6543]] /* pVehicle.pRrAxleMass.lcaMass.inertia[1,1] PARAM */);
  threadData->lastEquationSolved = 38819;
}

/*
equation index: 38820
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[1,1] = chassis.pVehicle.pRrAxleMass.lcaMass.inertia[1,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38820(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38820};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3468]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[1,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5605]] /* chassis.pVehicle.pRrAxleMass.lcaMass.inertia[1,1] PARAM */);
  threadData->lastEquationSolved = 38820;
}

/*
equation index: 38821
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.I_11 = chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[1,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38821(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38821};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2692]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I_11 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3468]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.lcaMass.inertia[1,1] PARAM */);
  threadData->lastEquationSolved = 38821;
}

/*
equation index: 38822
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.I[1,1] = chassis.detailedChassis.rrAxleDW.leftLCABody.I_11
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38822(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38822};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2683]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I[1,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2692]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.I_11 PARAM */);
  threadData->lastEquationSolved = 38822;
}

/*
equation index: 38847
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.sphere.shapeType = "sphere"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38847(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38847};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[210]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.sphere.shapeType PARAM */) = _OMC_LIT47;
  threadData->lastEquationSolved = 38847;
}

/*
equation index: 38848
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.cylinder.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38848(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38848};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[209]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.cylinder.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38848;
}

/*
equation index: 38850
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.phi_start[3] = chassis.detailedChassis.rrAxleDW.leftUCABody.angles_start[3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38850(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38850};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3170]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.phi_start[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3165]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.angles_start[3] PARAM */);
  threadData->lastEquationSolved = 38850;
}

/*
equation index: 38852
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.phi_start[2] = chassis.detailedChassis.rrAxleDW.leftUCABody.angles_start[2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38852(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38852};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3169]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.phi_start[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3164]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.angles_start[2] PARAM */);
  threadData->lastEquationSolved = 38852;
}

/*
equation index: 38854
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.phi_start[1] = chassis.detailedChassis.rrAxleDW.leftUCABody.angles_start[1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38854(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38854};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3168]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.phi_start[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3163]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.angles_start[1] PARAM */);
  threadData->lastEquationSolved = 38854;
}

/*
equation index: 38855
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.leftUCABody.Q_start = {0.0, 0.0, 0.0, 1.0}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38855(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38855};
  real_array tmp67;
  real_array_create(&tmp67, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3147]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.Q_start[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)4);
  real_array_copy_data(_OMC_LIT46, tmp67);
  threadData->lastEquationSolved = 38855;
}

/*
equation index: 38868
type: SIMPLE_ASSIGN
chassis.pVehicle.pRrAxleMass.ucaMass.inertia[3,3] = pVehicle.pRrAxleMass.ucaMass.inertia[3,3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38868(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38868};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5639]] /* chassis.pVehicle.pRrAxleMass.ucaMass.inertia[3,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6577]] /* pVehicle.pRrAxleMass.ucaMass.inertia[3,3] PARAM */);
  threadData->lastEquationSolved = 38868;
}

/*
equation index: 38869
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[3,3] = chassis.pVehicle.pRrAxleMass.ucaMass.inertia[3,3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38869(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38869};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3502]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[3,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5639]] /* chassis.pVehicle.pRrAxleMass.ucaMass.inertia[3,3] PARAM */);
  threadData->lastEquationSolved = 38869;
}

/*
equation index: 38870
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.I_33 = chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[3,3]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38870(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38870};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3146]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I_33 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3502]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[3,3] PARAM */);
  threadData->lastEquationSolved = 38870;
}

/*
equation index: 38871
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.I[3,3] = chassis.detailedChassis.rrAxleDW.leftUCABody.I_33
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38871(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38871};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3140]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I[3,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3146]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I_33 PARAM */);
  threadData->lastEquationSolved = 38871;
}

/*
equation index: 38872
type: SIMPLE_ASSIGN
chassis.pVehicle.pRrAxleMass.ucaMass.inertia[3,2] = pVehicle.pRrAxleMass.ucaMass.inertia[3,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38872(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38872};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5638]] /* chassis.pVehicle.pRrAxleMass.ucaMass.inertia[3,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6576]] /* pVehicle.pRrAxleMass.ucaMass.inertia[3,2] PARAM */);
  threadData->lastEquationSolved = 38872;
}

/*
equation index: 38873
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[3,2] = chassis.pVehicle.pRrAxleMass.ucaMass.inertia[3,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38873(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38873};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3501]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[3,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5638]] /* chassis.pVehicle.pRrAxleMass.ucaMass.inertia[3,2] PARAM */);
  threadData->lastEquationSolved = 38873;
}

/*
equation index: 38874
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.I_32 = chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[3,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38874(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38874};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3145]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I_32 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3501]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[3,2] PARAM */);
  threadData->lastEquationSolved = 38874;
}

/*
equation index: 38875
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.I[3,2] = chassis.detailedChassis.rrAxleDW.leftUCABody.I_32
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38875(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38875};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3139]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I[3,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3145]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I_32 PARAM */);
  threadData->lastEquationSolved = 38875;
}

/*
equation index: 38876
type: SIMPLE_ASSIGN
chassis.pVehicle.pRrAxleMass.ucaMass.inertia[3,1] = pVehicle.pRrAxleMass.ucaMass.inertia[3,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38876(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38876};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5637]] /* chassis.pVehicle.pRrAxleMass.ucaMass.inertia[3,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6575]] /* pVehicle.pRrAxleMass.ucaMass.inertia[3,1] PARAM */);
  threadData->lastEquationSolved = 38876;
}

/*
equation index: 38877
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[3,1] = chassis.pVehicle.pRrAxleMass.ucaMass.inertia[3,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38877(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38877};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3500]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[3,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5637]] /* chassis.pVehicle.pRrAxleMass.ucaMass.inertia[3,1] PARAM */);
  threadData->lastEquationSolved = 38877;
}

/*
equation index: 38878
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.I_31 = chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[3,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38878(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38878};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3144]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I_31 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3500]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[3,1] PARAM */);
  threadData->lastEquationSolved = 38878;
}

/*
equation index: 38879
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.I[3,1] = chassis.detailedChassis.rrAxleDW.leftUCABody.I_31
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38879(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38879};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3138]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I[3,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3144]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I_31 PARAM */);
  threadData->lastEquationSolved = 38879;
}

/*
equation index: 38880
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.I[2,3] = chassis.detailedChassis.rrAxleDW.leftUCABody.I_32
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38880(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38880};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3137]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I[2,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3145]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I_32 PARAM */);
  threadData->lastEquationSolved = 38880;
}

/*
equation index: 38881
type: SIMPLE_ASSIGN
chassis.pVehicle.pRrAxleMass.ucaMass.inertia[2,2] = pVehicle.pRrAxleMass.ucaMass.inertia[2,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38881(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38881};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5635]] /* chassis.pVehicle.pRrAxleMass.ucaMass.inertia[2,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6573]] /* pVehicle.pRrAxleMass.ucaMass.inertia[2,2] PARAM */);
  threadData->lastEquationSolved = 38881;
}

/*
equation index: 38882
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[2,2] = chassis.pVehicle.pRrAxleMass.ucaMass.inertia[2,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38882(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38882};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3498]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[2,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5635]] /* chassis.pVehicle.pRrAxleMass.ucaMass.inertia[2,2] PARAM */);
  threadData->lastEquationSolved = 38882;
}

/*
equation index: 38883
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.I_22 = chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[2,2]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38883(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38883};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3143]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I_22 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3498]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[2,2] PARAM */);
  threadData->lastEquationSolved = 38883;
}

/*
equation index: 38884
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.I[2,2] = chassis.detailedChassis.rrAxleDW.leftUCABody.I_22
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38884(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38884};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3136]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I[2,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3143]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I_22 PARAM */);
  threadData->lastEquationSolved = 38884;
}

/*
equation index: 38885
type: SIMPLE_ASSIGN
chassis.pVehicle.pRrAxleMass.ucaMass.inertia[2,1] = pVehicle.pRrAxleMass.ucaMass.inertia[2,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38885(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38885};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5634]] /* chassis.pVehicle.pRrAxleMass.ucaMass.inertia[2,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6572]] /* pVehicle.pRrAxleMass.ucaMass.inertia[2,1] PARAM */);
  threadData->lastEquationSolved = 38885;
}

/*
equation index: 38886
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[2,1] = chassis.pVehicle.pRrAxleMass.ucaMass.inertia[2,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38886(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38886};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3497]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[2,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5634]] /* chassis.pVehicle.pRrAxleMass.ucaMass.inertia[2,1] PARAM */);
  threadData->lastEquationSolved = 38886;
}

/*
equation index: 38887
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.I_21 = chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[2,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38887(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38887};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3142]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I_21 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3497]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[2,1] PARAM */);
  threadData->lastEquationSolved = 38887;
}

/*
equation index: 38888
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.I[2,1] = chassis.detailedChassis.rrAxleDW.leftUCABody.I_21
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38888(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38888};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3135]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I[2,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3142]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I_21 PARAM */);
  threadData->lastEquationSolved = 38888;
}

/*
equation index: 38889
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.I[1,3] = chassis.detailedChassis.rrAxleDW.leftUCABody.I_31
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38889(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38889};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3134]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I[1,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3144]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I_31 PARAM */);
  threadData->lastEquationSolved = 38889;
}

/*
equation index: 38890
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.I[1,2] = chassis.detailedChassis.rrAxleDW.leftUCABody.I_21
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38890(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38890};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3133]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I[1,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3142]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I_21 PARAM */);
  threadData->lastEquationSolved = 38890;
}

/*
equation index: 38891
type: SIMPLE_ASSIGN
chassis.pVehicle.pRrAxleMass.ucaMass.inertia[1,1] = pVehicle.pRrAxleMass.ucaMass.inertia[1,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38891(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38891};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5631]] /* chassis.pVehicle.pRrAxleMass.ucaMass.inertia[1,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6569]] /* pVehicle.pRrAxleMass.ucaMass.inertia[1,1] PARAM */);
  threadData->lastEquationSolved = 38891;
}

/*
equation index: 38892
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[1,1] = chassis.pVehicle.pRrAxleMass.ucaMass.inertia[1,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38892(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38892};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3494]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[1,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5631]] /* chassis.pVehicle.pRrAxleMass.ucaMass.inertia[1,1] PARAM */);
  threadData->lastEquationSolved = 38892;
}

/*
equation index: 38893
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.I_11 = chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[1,1]
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38893(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38893};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3141]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I_11 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3494]] /* chassis.detailedChassis.rrAxleDW.pLeftAxleMass.ucaMass.inertia[1,1] PARAM */);
  threadData->lastEquationSolved = 38893;
}

/*
equation index: 38894
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.I[1,1] = chassis.detailedChassis.rrAxleDW.leftUCABody.I_11
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38894(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38894};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3132]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I[1,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3141]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.I_11 PARAM */);
  threadData->lastEquationSolved = 38894;
}

/*
equation index: 38926
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightLower_i.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38926(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38926};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[330]] /* chassis.detailedChassis.rrAxleDW.toRightLower_i.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38926;
}

/*
equation index: 38935
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightUpper_i.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38935(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38935};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[332]] /* chassis.detailedChassis.rrAxleDW.toRightUpper_i.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38935;
}

/*
equation index: 38938
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toLeftLower_i.width = 0.3367103175272329 / world.defaultWidthFraction
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38938(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38938};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4663]] /* chassis.detailedChassis.rrAxleDW.toLeftLower_i.width PARAM */) = DIVISION_SIM(0.3367103175272329,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 38938;
}

/*
equation index: 38939
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toLeftLower_i.height = chassis.detailedChassis.rrAxleDW.toLeftLower_i.width
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38939(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38939};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4652]] /* chassis.detailedChassis.rrAxleDW.toLeftLower_i.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4663]] /* chassis.detailedChassis.rrAxleDW.toLeftLower_i.width PARAM */);
  threadData->lastEquationSolved = 38939;
}

/*
equation index: 38950
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toLeftLower_i.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38950(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38950};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[323]] /* chassis.detailedChassis.rrAxleDW.toLeftLower_i.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38950;
}

/*
equation index: 38956
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toLeftUpper_i.width = 0.3349109915809124 / world.defaultWidthFraction
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38956(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38956};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4695]] /* chassis.detailedChassis.rrAxleDW.toLeftUpper_i.width PARAM */) = DIVISION_SIM(0.3349109915809124,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 38956;
}

/*
equation index: 38957
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toLeftUpper_i.height = chassis.detailedChassis.rrAxleDW.toLeftUpper_i.width
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38957(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38957};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4684]] /* chassis.detailedChassis.rrAxleDW.toLeftUpper_i.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4695]] /* chassis.detailedChassis.rrAxleDW.toLeftUpper_i.width PARAM */);
  threadData->lastEquationSolved = 38957;
}

/*
equation index: 38968
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toLeftUpper_i.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38968(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38968};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[325]] /* chassis.detailedChassis.rrAxleDW.toLeftUpper_i.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38968;
}

/*
equation index: 38980
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightWheelCenter.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38980(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38980};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[333]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38980;
}

/*
equation index: 38983
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toLeftWheelCenter.width = 0.08901497164406054 / world.defaultWidthFraction
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38983(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38983};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4711]] /* chassis.detailedChassis.rrAxleDW.toLeftWheelCenter.width PARAM */) = DIVISION_SIM(0.08901497164406054,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 38983;
}

/*
equation index: 38984
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toLeftWheelCenter.height = chassis.detailedChassis.rrAxleDW.toLeftWheelCenter.width
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38984(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38984};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4700]] /* chassis.detailedChassis.rrAxleDW.toLeftWheelCenter.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4711]] /* chassis.detailedChassis.rrAxleDW.toLeftWheelCenter.width PARAM */);
  threadData->lastEquationSolved = 38984;
}

/*
equation index: 38995
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toLeftWheelCenter.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_38995(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,38995};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[326]] /* chassis.detailedChassis.rrAxleDW.toLeftWheelCenter.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 38995;
}

/*
equation index: 39007
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieConnection.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39007(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39007};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[275]] /* chassis.detailedChassis.rrAxleDW.rightTieConnection.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 39007;
}

/*
equation index: 39010
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieConnection.width = 0.13786749851331906 / world.defaultWidthFraction
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39010(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39010};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2836]] /* chassis.detailedChassis.rrAxleDW.leftTieConnection.width PARAM */) = DIVISION_SIM(0.13786749851331906,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 39010;
}

/*
equation index: 39011
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieConnection.height = chassis.detailedChassis.rrAxleDW.leftTieConnection.width
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39011(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39011};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2825]] /* chassis.detailedChassis.rrAxleDW.leftTieConnection.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2836]] /* chassis.detailedChassis.rrAxleDW.leftTieConnection.width PARAM */);
  threadData->lastEquationSolved = 39011;
}

/*
equation index: 39022
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieConnection.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39022(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39022};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[199]] /* chassis.detailedChassis.rrAxleDW.leftTieConnection.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 39022;
}

/*
equation index: 39028
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRack.width = 0.1756135831240853 / world.defaultWidthFraction
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39028(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39028};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4727]] /* chassis.detailedChassis.rrAxleDW.toRack.width PARAM */) = DIVISION_SIM(0.1756135831240853,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 39028;
}

/*
equation index: 39029
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRack.height = chassis.detailedChassis.rrAxleDW.toRack.width
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39029(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39029};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4716]] /* chassis.detailedChassis.rrAxleDW.toRack.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4727]] /* chassis.detailedChassis.rrAxleDW.toRack.width PARAM */);
  threadData->lastEquationSolved = 39029;
}

/*
equation index: 39040
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRack.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39040(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39040};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[327]] /* chassis.detailedChassis.rrAxleDW.toRack.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 39040;
}

/*
equation index: 39045
type: SIMPLE_ASSIGN
chassis.pVehicle.pRrRack.cFactor = pVehicle.pRrRack.cFactor
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39045(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39045};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5686]] /* chassis.pVehicle.pRrRack.cFactor PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6624]] /* pVehicle.pRrRack.cFactor PARAM */);
  threadData->lastEquationSolved = 39045;
}

/*
equation index: 39046
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.pRack.cFactor = chassis.pVehicle.pRrRack.cFactor
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39046(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39046};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3549]] /* chassis.detailedChassis.rrAxleDW.pRack.cFactor PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5686]] /* chassis.pVehicle.pRrRack.cFactor PARAM */);
  threadData->lastEquationSolved = 39046;
}

/*
equation index: 39047
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.pRack.cFactor = chassis.detailedChassis.rrAxleDW.pRack.cFactor
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39047(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39047};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3663]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.pRack.cFactor PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3549]] /* chassis.detailedChassis.rrAxleDW.pRack.cFactor PARAM */);
  threadData->lastEquationSolved = 39047;
}

/*
equation index: 39048
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.idealGearR2T.ratio = 6.283185307179586 / chassis.detailedChassis.rrAxleDW.rackAndPinion.pRack.cFactor
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39048(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39048};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3657]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.idealGearR2T.ratio PARAM */) = DIVISION_SIM(6.283185307179586,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3663]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.pRack.cFactor PARAM */),"chassis.detailedChassis.rrAxleDW.rackAndPinion.pRack.cFactor",equationIndexes);
  threadData->lastEquationSolved = 39048;
}

/*
equation index: 39051
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.travelVisualizer.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39051(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39051};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[243]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.travelVisualizer.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 39051;
}

/*
equation index: 39052
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.travelVisualizer.vis.shapeType = chassis.detailedChassis.rrAxleDW.rackAndPinion.travelVisualizer.shapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39052(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39052};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[244]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.travelVisualizer.vis.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[243]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.travelVisualizer.shapeType PARAM */);
  threadData->lastEquationSolved = 39052;
}

/*
equation index: 39054
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.pinionVisualizer.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39054(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39054};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[238]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.pinionVisualizer.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 39054;
}

/*
equation index: 39055
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.pinionVisualizer.vis.shapeType = chassis.detailedChassis.rrAxleDW.rackAndPinion.pinionVisualizer.shapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39055(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39055};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[239]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.pinionVisualizer.vis.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[238]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.pinionVisualizer.shapeType PARAM */);
  threadData->lastEquationSolved = 39055;
}

/*
equation index: 39061
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.toRight.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39061(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39061};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[242]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.toRight.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 39061;
}

/*
equation index: 39062
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.toRight.shape.shapeType = chassis.detailedChassis.rrAxleDW.rackAndPinion.toRight.shapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39062(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39062};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[241]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.toRight.shape.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[242]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.toRight.shapeType PARAM */);
  threadData->lastEquationSolved = 39062;
}

/*
equation index: 39080
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.fromLeft.shapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39080(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39080};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[237]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.fromLeft.shapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 39080;
}

/*
equation index: 39081
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.fromLeft.shape.shapeType = chassis.detailedChassis.rrAxleDW.rackAndPinion.fromLeft.shapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39081(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39081};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[236]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.fromLeft.shape.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[237]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.fromLeft.shapeType PARAM */);
  threadData->lastEquationSolved = 39081;
}

/*
equation index: 39100
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.rackAxis.box.shapeType = "box"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39100(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39100};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[240]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.rackAxis.box.shapeType PARAM */) = _OMC_LIT64;
  threadData->lastEquationSolved = 39100;
}

/*
equation index: 39105
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.rackAxis.boxWidth = world.defaultJointWidth
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39105(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39105};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3668]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.rackAxis.boxWidth PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6897]] /* world.defaultJointWidth PARAM */);
  threadData->lastEquationSolved = 39105;
}

/*
equation index: 39106
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.rackAxis.boxHeight = chassis.detailedChassis.rrAxleDW.rackAndPinion.rackAxis.boxWidth
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39106(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39106};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3667]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.rackAxis.boxHeight PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3668]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.rackAxis.boxWidth PARAM */);
  threadData->lastEquationSolved = 39106;
}

/*
equation index: 39119
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.sphericalShape_a.shapeType = "sphere"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39119(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39119};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[278]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.sphericalShape_a.shapeType PARAM */) = _OMC_LIT47;
  threadData->lastEquationSolved = 39119;
}

/*
equation index: 39120
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.sphericalShape_b.shapeType = "sphere"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39120(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39120};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[279]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.sphericalShape_b.shapeType PARAM */) = _OMC_LIT47;
  threadData->lastEquationSolved = 39120;
}

/*
equation index: 39121
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodShapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39121(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39121};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[277]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodShapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 39121;
}

/*
equation index: 39122
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodShape.shapeType = chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodShapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39122(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39122};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[276]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodShape.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[277]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodShapeType PARAM */);
  threadData->lastEquationSolved = 39122;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_2401(DATA *data, threadData_t *threadData);


/*
equation index: 39126
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.kinematicConstraint = chassis.detailedChassis.rrAxleDW.rightTieRod.kinematicConstraint
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39126(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39126};
  (data->simulationInfo->booleanParameter[data->simulationInfo->booleanParamsIndex[420]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.kinematicConstraint PARAM */) = (data->simulationInfo->booleanParameter[data->simulationInfo->booleanParamsIndex[416]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.kinematicConstraint PARAM */);
  threadData->lastEquationSolved = 39126;
}

/*
equation index: 39145
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightTieRod.r_a = {-1.3763498, -0.2897124, 0.1700022}
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39145(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39145};
  real_array tmp68;
  real_array_create(&tmp68, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3934]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.r_a[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(_OMC_LIT65, tmp68);
  threadData->lastEquationSolved = 39145;
}

/*
equation index: 39146
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieRod.rod.sphericalShape_a.shapeType = "sphere"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39146(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39146};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[202]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.sphericalShape_a.shapeType PARAM */) = _OMC_LIT47;
  threadData->lastEquationSolved = 39146;
}

/*
equation index: 39147
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieRod.rod.sphericalShape_b.shapeType = "sphere"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39147(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39147};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[203]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.sphericalShape_b.shapeType PARAM */) = _OMC_LIT47;
  threadData->lastEquationSolved = 39147;
}

/*
equation index: 39148
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodShapeType = "cylinder"
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39148(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39148};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[201]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodShapeType PARAM */) = _OMC_LIT44;
  threadData->lastEquationSolved = 39148;
}

/*
equation index: 39149
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodShape.shapeType = chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodShapeType
*/
OMC_DISABLE_OPT
static void BobLib_Experiments_Standards_VehicleSim_eqFunction_39149(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,39149};
  (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[200]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodShape.shapeType PARAM */) = (data->simulationInfo->stringParameter[data->simulationInfo->stringParamsIndex[201]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodShapeType PARAM */);
  threadData->lastEquationSolved = 39149;
}
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_updateBoundParameters_1(DATA *data, threadData_t *threadData)
{
  static void (*const eqFunctions[477])(DATA*, threadData_t*) = {
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37571,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37572,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37573,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37574,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37575,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37576,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37577,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37578,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37579,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37580,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37581,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37582,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37583,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37584,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37585,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37586,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37587,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37588,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37590,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37600,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37602,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37611,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37613,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37617,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37618,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37622,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37635,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37636,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37637,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37638,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37641,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37642,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37643,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37644,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37645,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37646,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37647,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37648,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37649,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37650,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37651,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37652,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37653,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37654,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37655,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37656,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37657,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37658,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37659,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37660,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37661,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37662,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37663,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37664,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37665,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37666,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37667,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37668,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37669,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37670,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37671,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37672,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37673,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37674,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37675,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37676,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37677,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37678,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37705,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37709,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37710,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37711,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37712,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37713,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37714,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37715,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37719,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37720,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37721,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37725,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37726,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37727,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37728,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37737,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37741,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37742,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37743,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37744,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37745,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37746,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37747,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37751,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37752,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37753,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37757,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37758,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37759,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37760,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37763,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37765,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37767,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37768,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37803,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37804,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37805,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37809,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37810,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37811,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37812,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37819,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37820,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37830,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37840,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37841,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37842,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37843,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37844,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37845,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37849,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37851,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37856,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37857,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37863,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37864,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37865,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37866,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37867,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37868,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37869,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37870,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37871,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37872,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37873,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37874,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37875,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37876,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37877,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37878,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37884,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37885,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37896,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37901,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37902,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37904,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37905,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37920,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37921,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37923,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37924,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37939,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37940,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37942,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37944,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37946,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37947,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37960,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37961,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37962,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37963,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37964,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37965,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37966,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37967,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37968,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37969,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37970,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37971,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37972,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37973,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37974,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37975,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37976,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37977,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37978,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37979,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_37980,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38005,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38006,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38007,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38018,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38019,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38020,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38021,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38022,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2399,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38026,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38039,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38040,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38041,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38042,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38043,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38044,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38045,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38046,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38047,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38050,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38066,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38074,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38075,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38086,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38098,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38099,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38102,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38103,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38114,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38120,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38121,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38132,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38133,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38135,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38138,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38139,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38150,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38151,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38153,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38156,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38157,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38168,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38174,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38175,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38186,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38194,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38195,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38196,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38207,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38208,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38209,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38220,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38221,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38235,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38237,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38239,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38240,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38259,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38260,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38261,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38262,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38270,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38271,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38278,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38290,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38291,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38301,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38303,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38304,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38330,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38331,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38341,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38342,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38347,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38348,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38353,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38354,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38359,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38360,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38363,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38364,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38365,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38366,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38372,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38373,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38374,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38375,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38383,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38392,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38401,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38403,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38404,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38406,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38407,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38409,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38410,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38412,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38413,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38418,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38419,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38423,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38428,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38429,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38430,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38431,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38432,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38433,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38434,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38444,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38445,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38450,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38451,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38456,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38457,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38462,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38463,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38466,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38467,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38473,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38484,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38485,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38496,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38502,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38503,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38514,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38520,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38521,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38532,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38537,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38538,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38540,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38541,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38543,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38544,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38546,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38547,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38552,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38553,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38557,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38577,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38578,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38580,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38582,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38584,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38585,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38619,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38620,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38622,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38624,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38626,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38627,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38661,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38662,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38664,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38666,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38668,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38669,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38703,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38704,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38706,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38708,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38710,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38711,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38724,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38725,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38726,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38727,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38728,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38729,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38730,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38731,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38732,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38733,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38734,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38735,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38736,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38737,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38738,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38739,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38740,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38741,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38742,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38743,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38744,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38745,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38746,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38747,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38748,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38749,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38750,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38775,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38776,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38778,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38780,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38782,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38783,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38796,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38797,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38798,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38799,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38800,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38801,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38802,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38803,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38804,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38805,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38806,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38807,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38808,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38809,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38810,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38811,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38812,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38813,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38814,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38815,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38816,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38817,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38818,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38819,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38820,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38821,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38822,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38847,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38848,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38850,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38852,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38854,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38855,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38868,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38869,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38870,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38871,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38872,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38873,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38874,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38875,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38876,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38877,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38878,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38879,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38880,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38881,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38882,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38883,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38884,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38885,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38886,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38887,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38888,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38889,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38890,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38891,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38892,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38893,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38894,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38926,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38935,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38938,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38939,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38950,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38956,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38957,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38968,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38980,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38983,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38984,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_38995,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39007,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39010,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39011,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39022,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39028,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39029,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39040,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39045,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39046,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39047,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39048,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39051,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39052,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39054,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39055,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39061,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39062,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39080,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39081,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39100,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39105,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39106,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39119,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39120,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39121,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39122,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2401,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39126,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39145,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39146,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39147,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39148,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_39149
  };
  
  for (int id = 0; id < 477; id++) {
    eqFunctions[id](data, threadData);
  }
}
#if defined(__cplusplus)
}
#endif