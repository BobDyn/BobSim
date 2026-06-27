#include "omc_simulation_settings.h"
#include "BobLib.Experiments.Standards.VehicleSim_functions.h"
#ifdef __cplusplus
extern "C" {
#endif

#include "BobLib.Experiments.Standards.VehicleSim_includes.h"


DLLDirection
real_array omc__omcQ_24DER_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData_t *threadData, real_array _r, real_array __omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr, real_array __omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr, real_array __omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr)
{
  real_array __omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm;
  real_array _r_m;
  real_array __omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm;
  real_array __omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm;
  _tailrecursive: OMC_LABEL_UNUSED
  alloc_real_array(&(__omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm), 1, (_index_t)3); // __omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm has no default value.
  alloc_real_array(&(_r_m), 1, (_index_t)3); // _r_m has no default value.
  alloc_real_array(&(__omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm), 1, (_index_t)3); // __omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm has no default value.
  alloc_real_array(&(__omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm), 1, (_index_t)3); // __omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm has no default value.
  real_array_get(_r_m, 1, ((modelica_integer) 1)) = real_array_get(_r, 1, ((modelica_integer) 1));

  real_array_get(__omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm, 1, ((modelica_integer) 1)) = real_array_get(__omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr, 1, ((modelica_integer) 1));

  real_array_get(__omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm, 1, ((modelica_integer) 1)) = real_array_get(__omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr, 1, ((modelica_integer) 1));

  real_array_get(__omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm, 1, ((modelica_integer) 1)) = real_array_get(__omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr, 1, ((modelica_integer) 1));

  real_array_get(_r_m, 1, ((modelica_integer) 2)) = (-real_array_get(_r, 1, ((modelica_integer) 2)));

  real_array_get(__omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm, 1, ((modelica_integer) 2)) = (-real_array_get(__omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr, 1, ((modelica_integer) 2)));

  real_array_get(__omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm, 1, ((modelica_integer) 2)) = (-real_array_get(__omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr, 1, ((modelica_integer) 2)));

  real_array_get(__omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm, 1, ((modelica_integer) 2)) = (-real_array_get(__omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr, 1, ((modelica_integer) 2)));

  real_array_get(_r_m, 1, ((modelica_integer) 3)) = real_array_get(_r, 1, ((modelica_integer) 3));

  real_array_get(__omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm, 1, ((modelica_integer) 3)) = real_array_get(__omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr, 1, ((modelica_integer) 3));

  real_array_get(__omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm, 1, ((modelica_integer) 3)) = real_array_get(__omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr, 1, ((modelica_integer) 3));

  real_array_get(__omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm, 1, ((modelica_integer) 3)) = real_array_get(__omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr, 1, ((modelica_integer) 3));
  _return: OMC_LABEL_UNUSED
  return __omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm;
}
modelica_metatype boxptr__omcQ_24DER_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData_t *threadData, modelica_metatype _r, modelica_metatype __omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr, modelica_metatype __omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr, modelica_metatype __omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr)
{
  real_array __omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm;
  modelica_metatype out__omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm;
  __omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm = omc__omcQ_24DER_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData, *((base_array_t*)_r), *((base_array_t*)__omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr), *((base_array_t*)__omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr), *((base_array_t*)__omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr));
  out__omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm = mmc_mk_modelica_array(__omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm);
  return out__omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm;
}

DLLDirection
real_array omc__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData_t *threadData, real_array _r, real_array __omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr)
{
  real_array __omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm;
  real_array _r_m;
  _tailrecursive: OMC_LABEL_UNUSED
  alloc_real_array(&(__omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm), 1, (_index_t)3); // __omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm has no default value.
  alloc_real_array(&(_r_m), 1, (_index_t)3); // _r_m has no default value.
  real_array_get(_r_m, 1, ((modelica_integer) 1)) = real_array_get(_r, 1, ((modelica_integer) 1));

  real_array_get(__omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm, 1, ((modelica_integer) 1)) = real_array_get(__omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr, 1, ((modelica_integer) 1));

  real_array_get(_r_m, 1, ((modelica_integer) 2)) = (-real_array_get(_r, 1, ((modelica_integer) 2)));

  real_array_get(__omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm, 1, ((modelica_integer) 2)) = (-real_array_get(__omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr, 1, ((modelica_integer) 2)));

  real_array_get(_r_m, 1, ((modelica_integer) 3)) = real_array_get(_r, 1, ((modelica_integer) 3));

  real_array_get(__omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm, 1, ((modelica_integer) 3)) = real_array_get(__omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr, 1, ((modelica_integer) 3));
  _return: OMC_LABEL_UNUSED
  return __omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm;
}
modelica_metatype boxptr__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData_t *threadData, modelica_metatype _r, modelica_metatype __omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr)
{
  real_array __omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm;
  modelica_metatype out__omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm;
  __omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm = omc__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData, *((base_array_t*)_r), *((base_array_t*)__omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr));
  out__omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm = mmc_mk_modelica_array(__omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm);
  return out__omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr_5Fm;
}

DLLDirection
modelica_real omc_BobLib_Aero_Internal_Bilinear2D(threadData_t *threadData, modelica_real _x, modelica_real _y, real_array _xGrid, real_array _yGrid, real_array _table)
{
  modelica_real _z;
  modelica_integer _ix;
  modelica_integer _iy;
  modelica_real _xLo;
  modelica_real _xHi;
  modelica_real _yLo;
  modelica_real _yHi;
  modelica_real _xFrac;
  modelica_real _yFrac;
  modelica_integer tmp1;
  modelica_integer tmp2;
  modelica_real tmp3;
  modelica_real tmp4;
  _tailrecursive: OMC_LABEL_UNUSED
  // _z has no default value.
  // _ix has no default value.
  // _iy has no default value.
  // _xLo has no default value.
  // _xHi has no default value.
  // _yLo has no default value.
  // _yHi has no default value.
  // _xFrac has no default value.
  // _yFrac has no default value.
  _ix = ((modelica_integer) 1);

  while(1)
  {
    tmp1 = size_of_dimension_base_array(_xGrid, ((modelica_integer) 1));
    if(!((_ix < tmp1 - ((modelica_integer) 1)) && (_x > real_array_get(_xGrid, 1, _ix + ((modelica_integer) 1))))) break;
    _ix = _ix + ((modelica_integer) 1);
  }

  _iy = ((modelica_integer) 1);

  while(1)
  {
    tmp2 = size_of_dimension_base_array(_yGrid, ((modelica_integer) 1));
    if(!((_iy < tmp2 - ((modelica_integer) 1)) && (_y > real_array_get(_yGrid, 1, _iy + ((modelica_integer) 1))))) break;
    _iy = _iy + ((modelica_integer) 1);
  }

  _xLo = real_array_get(_xGrid, 1, _ix);

  _xHi = real_array_get(_xGrid, 1, _ix + ((modelica_integer) 1));

  _yLo = real_array_get(_yGrid, 1, _iy);

  _yHi = real_array_get(_yGrid, 1, _iy + ((modelica_integer) 1));

  _xFrac = ((_xHi > _xLo)?fmin(fmax(_x,_xLo),_xHi) - _xLo:0.0);

  _yFrac = ((_yHi > _yLo)?fmin(fmax(_y,_yLo),_yHi) - _yLo:0.0);

  if((_xHi > _xLo))
  {
    tmp3 = _xHi - _xLo;
    if (tmp3 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "xFrac / (xHi - xLo)");}
    _xFrac = (_xFrac) / tmp3;
  }
  else
  {
    _xFrac = 0.0;
  }

  if((_yHi > _yLo))
  {
    tmp4 = _yHi - _yLo;
    if (tmp4 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "yFrac / (yHi - yLo)");}
    _yFrac = (_yFrac) / tmp4;
  }
  else
  {
    _yFrac = 0.0;
  }

  _z = ((1.0 - _xFrac) * (1.0 - _yFrac)) * (real_array_get(_table, 2, _ix, _iy)) + ((1.0 - _xFrac) * (_yFrac)) * (real_array_get(_table, 2, _ix, _iy + ((modelica_integer) 1))) + ((_xFrac) * (1.0 - _yFrac)) * (real_array_get(_table, 2, _ix + ((modelica_integer) 1), _iy)) + ((_xFrac) * (_yFrac)) * (real_array_get(_table, 2, _ix + ((modelica_integer) 1), _iy + ((modelica_integer) 1)));
  _return: OMC_LABEL_UNUSED
  return _z;
}
modelica_metatype boxptr_BobLib_Aero_Internal_Bilinear2D(threadData_t *threadData, modelica_metatype _x, modelica_metatype _y, modelica_metatype _xGrid, modelica_metatype _yGrid, modelica_metatype _table)
{
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_real _z;
  modelica_metatype out_z;
  tmp1 = mmc_unbox_real(_x);
  tmp2 = mmc_unbox_real(_y);
  _z = omc_BobLib_Aero_Internal_Bilinear2D(threadData, tmp1, tmp2, *((base_array_t*)_xGrid), *((base_array_t*)_yGrid), *((base_array_t*)_table));
  out_z = mmc_mk_rcon(_z);
  return out_z;
}

DLLDirection
modelica_real omc_BobLib_Chassis_Suspension_Tires_MF52_Eval(threadData_t *threadData, modelica_real _Fz, modelica_real _alpha, modelica_real _kappa, modelica_real _gamma, modelica_real _Vx, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record _tire, modelica_real *out_Fy, modelica_real *out_Mx, modelica_real *out_My, modelica_real *out_Mz, modelica_real *out_t, modelica_real *out_s)
{
  modelica_real _Fx;
  modelica_real _Fy;
  modelica_real _Mx;
  modelica_real _My;
  modelica_real _Mz;
  modelica_real _t;
  modelica_real _s;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord _pFxPure;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord _pFxComb;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord _pFyPure;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord _pFyComb;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord _pMxPure;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord _pMxComb;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord _pMyPure;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord _pMyComb;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord _pMzPure;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord _pMzComb;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord _setup;
  modelica_real _FzEval;
  modelica_real _loadScale;
  modelica_real tmp1;
  _tailrecursive: OMC_LABEL_UNUSED
  // _Fx has no default value.
  // _Fy has no default value.
  // _Mx has no default value.
  // _My has no default value.
  // _Mz has no default value.
  // _t has no default value.
  // _s has no default value.
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_construct(threadData, _pFxPure); // _pFxPure has no default value.
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_construct(threadData, _pFxComb); // _pFxComb has no default value.
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_construct(threadData, _pFyPure); // _pFyPure has no default value.
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_construct(threadData, _pFyComb); // _pFyComb has no default value.
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_construct(threadData, _pMxPure); // _pMxPure has no default value.
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_construct(threadData, _pMxComb); // _pMxComb has no default value.
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_construct(threadData, _pMyPure); // _pMyPure has no default value.
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_construct(threadData, _pMyComb); // _pMyComb has no default value.
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_construct(threadData, _pMzPure); // _pMzPure has no default value.
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_construct(threadData, _pMzComb); // _pMzComb has no default value.
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_construct(threadData, _setup); // _setup has no default value.
  // _FzEval has no default value.
  // _loadScale has no default value.
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_copy(_tire._fxPure, _pFxPure);;

  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_copy(_tire._fxCombined, _pFxComb);;

  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_copy(_tire._fyPure, _pFyPure);;

  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_copy(_tire._fyCombined, _pFyComb);;

  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_copy(_tire._mxPure, _pMxPure);;

  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_copy(_tire._mxCombined, _pMxComb);;

  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_copy(_tire._myPure, _pMyPure);;

  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_copy(_tire._myCombined, _pMyComb);;

  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_copy(_tire._mzPure, _pMzPure);;

  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_copy(_tire._mzCombined, _pMzComb);;

  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_copy(_tire._setup, _setup);;

  if((_Fz > 0.001))
  {
    if((_Fz > _setup._FZMIN))
    {
      _FzEval = _Fz;
    }
    else
    {
      _FzEval = _setup._FZMIN;
    }

    tmp1 = _FzEval;
    if (tmp1 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "Fz / FzEval");}
    _loadScale = (_Fz) / tmp1;
  }
  else
  {
    _FzEval = _setup._FZMIN;

    _loadScale = 0.0;
  }

  _Fx = omc_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_FxCombinedEval(threadData, _FzEval, _kappa, _alpha, _gamma, _pFxPure, _pFxComb, _setup);

  _Fy = omc_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_FyCombinedEval(threadData, _FzEval, _alpha, _kappa, _gamma, _pFyPure, _pFyComb, _setup);

  _Mx = omc_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MxCombinedEval(threadData, _FzEval, _Fy, _gamma, _pMxPure, _pMxComb, _setup);

  _My = omc_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MyCombinedEval(threadData, _FzEval, _Fx, _Vx, _pMyPure, _pFxPure, _pMyComb, _setup);

  _Mz = omc_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MzCombinedEval(threadData, _FzEval, _Fx, _Fy, _alpha, _kappa, _gamma, _pFyPure, _pFxPure, _pMzPure, _pMzComb, _setup ,&_t ,&_s);

  _Fx = (_loadScale) * (_Fx);

  _Fy = (_loadScale) * (_Fy);

  _Mx = (_loadScale) * (_Mx);

  _My = (_loadScale) * (_My);

  _Mz = (_loadScale) * (_Mz);

  _Fy = (-_Fy);

  _My = (-_My);

  _Mz = (-_Mz);
  _return: OMC_LABEL_UNUSED
  if (out_Fy) { *out_Fy = _Fy; }
  if (out_Mx) { *out_Mx = _Mx; }
  if (out_My) { *out_My = _My; }
  if (out_Mz) { *out_Mz = _Mz; }
  if (out_t) { *out_t = _t; }
  if (out_s) { *out_s = _s; }
  return _Fx;
}
modelica_metatype boxptr_BobLib_Chassis_Suspension_Tires_MF52_Eval(threadData_t *threadData, modelica_metatype _Fz, modelica_metatype _alpha, modelica_metatype _kappa, modelica_metatype _gamma, modelica_metatype _Vx, modelica_metatype _tire, modelica_metatype *out_Fy, modelica_metatype *out_Mx, modelica_metatype *out_My, modelica_metatype *out_Mz, modelica_metatype *out_t, modelica_metatype *out_s)
{
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  modelica_real tmp4;
  modelica_real tmp5;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record tmp6;
  modelica_metatype tmpMeta7;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord tmp8;
  modelica_metatype tmpMeta9;
  modelica_real tmp10;
  modelica_metatype tmpMeta11;
  modelica_real tmp12;
  modelica_metatype tmpMeta13;
  modelica_real tmp14;
  modelica_metatype tmpMeta15;
  modelica_real tmp16;
  modelica_metatype tmpMeta17;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord tmp18;
  modelica_metatype tmpMeta19;
  modelica_real tmp20;
  modelica_metatype tmpMeta21;
  modelica_real tmp22;
  modelica_metatype tmpMeta23;
  modelica_real tmp24;
  modelica_metatype tmpMeta25;
  modelica_real tmp26;
  modelica_metatype tmpMeta27;
  modelica_real tmp28;
  modelica_metatype tmpMeta29;
  modelica_real tmp30;
  modelica_metatype tmpMeta31;
  modelica_real tmp32;
  modelica_metatype tmpMeta33;
  modelica_real tmp34;
  modelica_metatype tmpMeta35;
  modelica_real tmp36;
  modelica_metatype tmpMeta37;
  modelica_real tmp38;
  modelica_metatype tmpMeta39;
  modelica_real tmp40;
  modelica_metatype tmpMeta41;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord tmp42;
  modelica_metatype tmpMeta43;
  modelica_real tmp44;
  modelica_metatype tmpMeta45;
  modelica_real tmp46;
  modelica_metatype tmpMeta47;
  modelica_real tmp48;
  modelica_metatype tmpMeta49;
  modelica_real tmp50;
  modelica_metatype tmpMeta51;
  modelica_real tmp52;
  modelica_metatype tmpMeta53;
  modelica_real tmp54;
  modelica_metatype tmpMeta55;
  modelica_real tmp56;
  modelica_metatype tmpMeta57;
  modelica_real tmp58;
  modelica_metatype tmpMeta59;
  modelica_real tmp60;
  modelica_metatype tmpMeta61;
  modelica_real tmp62;
  modelica_metatype tmpMeta63;
  modelica_real tmp64;
  modelica_metatype tmpMeta65;
  modelica_real tmp66;
  modelica_metatype tmpMeta67;
  modelica_real tmp68;
  modelica_metatype tmpMeta69;
  modelica_real tmp70;
  modelica_metatype tmpMeta71;
  modelica_real tmp72;
  modelica_metatype tmpMeta73;
  modelica_real tmp74;
  modelica_metatype tmpMeta75;
  modelica_real tmp76;
  modelica_metatype tmpMeta77;
  modelica_real tmp78;
  modelica_metatype tmpMeta79;
  modelica_real tmp80;
  modelica_metatype tmpMeta81;
  modelica_real tmp82;
  modelica_metatype tmpMeta83;
  modelica_real tmp84;
  modelica_metatype tmpMeta85;
  modelica_real tmp86;
  modelica_metatype tmpMeta87;
  modelica_real tmp88;
  modelica_metatype tmpMeta89;
  modelica_real tmp90;
  modelica_metatype tmpMeta91;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord tmp92;
  modelica_metatype tmpMeta93;
  modelica_real tmp94;
  modelica_metatype tmpMeta95;
  modelica_real tmp96;
  modelica_metatype tmpMeta97;
  modelica_real tmp98;
  modelica_metatype tmpMeta99;
  modelica_real tmp100;
  modelica_metatype tmpMeta101;
  modelica_real tmp102;
  modelica_metatype tmpMeta103;
  modelica_real tmp104;
  modelica_metatype tmpMeta105;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord tmp106;
  modelica_metatype tmpMeta107;
  modelica_real tmp108;
  modelica_metatype tmpMeta109;
  modelica_real tmp110;
  modelica_metatype tmpMeta111;
  modelica_real tmp112;
  modelica_metatype tmpMeta113;
  modelica_real tmp114;
  modelica_metatype tmpMeta115;
  modelica_real tmp116;
  modelica_metatype tmpMeta117;
  modelica_real tmp118;
  modelica_metatype tmpMeta119;
  modelica_real tmp120;
  modelica_metatype tmpMeta121;
  modelica_real tmp122;
  modelica_metatype tmpMeta123;
  modelica_real tmp124;
  modelica_metatype tmpMeta125;
  modelica_real tmp126;
  modelica_metatype tmpMeta127;
  modelica_real tmp128;
  modelica_metatype tmpMeta129;
  modelica_real tmp130;
  modelica_metatype tmpMeta131;
  modelica_real tmp132;
  modelica_metatype tmpMeta133;
  modelica_real tmp134;
  modelica_metatype tmpMeta135;
  modelica_real tmp136;
  modelica_metatype tmpMeta137;
  modelica_real tmp138;
  modelica_metatype tmpMeta139;
  modelica_real tmp140;
  modelica_metatype tmpMeta141;
  modelica_real tmp142;
  modelica_metatype tmpMeta143;
  modelica_real tmp144;
  modelica_metatype tmpMeta145;
  modelica_real tmp146;
  modelica_metatype tmpMeta147;
  modelica_real tmp148;
  modelica_metatype tmpMeta149;
  modelica_real tmp150;
  modelica_metatype tmpMeta151;
  modelica_real tmp152;
  modelica_metatype tmpMeta153;
  modelica_real tmp154;
  modelica_metatype tmpMeta155;
  modelica_real tmp156;
  modelica_metatype tmpMeta157;
  modelica_real tmp158;
  modelica_metatype tmpMeta159;
  modelica_real tmp160;
  modelica_metatype tmpMeta161;
  modelica_real tmp162;
  modelica_metatype tmpMeta163;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord tmp164;
  modelica_metatype tmpMeta165;
  modelica_real tmp166;
  modelica_metatype tmpMeta167;
  modelica_real tmp168;
  modelica_metatype tmpMeta169;
  modelica_real tmp170;
  modelica_metatype tmpMeta171;
  modelica_real tmp172;
  modelica_metatype tmpMeta173;
  modelica_real tmp174;
  modelica_metatype tmpMeta175;
  modelica_real tmp176;
  modelica_metatype tmpMeta177;
  modelica_real tmp178;
  modelica_metatype tmpMeta179;
  modelica_real tmp180;
  modelica_metatype tmpMeta181;
  modelica_real tmp182;
  modelica_metatype tmpMeta183;
  modelica_real tmp184;
  modelica_metatype tmpMeta185;
  modelica_real tmp186;
  modelica_metatype tmpMeta187;
  modelica_real tmp188;
  modelica_metatype tmpMeta189;
  modelica_real tmp190;
  modelica_metatype tmpMeta191;
  modelica_real tmp192;
  modelica_metatype tmpMeta193;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord tmp194;
  modelica_metatype tmpMeta195;
  modelica_real tmp196;
  modelica_metatype tmpMeta197;
  modelica_real tmp198;
  modelica_metatype tmpMeta199;
  modelica_real tmp200;
  modelica_metatype tmpMeta201;
  modelica_real tmp202;
  modelica_metatype tmpMeta203;
  modelica_real tmp204;
  modelica_metatype tmpMeta205;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord tmp206;
  modelica_metatype tmpMeta207;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord tmp208;
  modelica_metatype tmpMeta209;
  modelica_real tmp210;
  modelica_metatype tmpMeta211;
  modelica_real tmp212;
  modelica_metatype tmpMeta213;
  modelica_real tmp214;
  modelica_metatype tmpMeta215;
  modelica_real tmp216;
  modelica_metatype tmpMeta217;
  modelica_real tmp218;
  modelica_metatype tmpMeta219;
  modelica_real tmp220;
  modelica_metatype tmpMeta221;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord tmp222;
  modelica_metatype tmpMeta223;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord tmp224;
  modelica_metatype tmpMeta225;
  modelica_real tmp226;
  modelica_metatype tmpMeta227;
  modelica_real tmp228;
  modelica_metatype tmpMeta229;
  modelica_real tmp230;
  modelica_metatype tmpMeta231;
  modelica_real tmp232;
  modelica_metatype tmpMeta233;
  modelica_real tmp234;
  modelica_metatype tmpMeta235;
  modelica_real tmp236;
  modelica_metatype tmpMeta237;
  modelica_real tmp238;
  modelica_metatype tmpMeta239;
  modelica_real tmp240;
  modelica_metatype tmpMeta241;
  modelica_real tmp242;
  modelica_metatype tmpMeta243;
  modelica_real tmp244;
  modelica_metatype tmpMeta245;
  modelica_real tmp246;
  modelica_metatype tmpMeta247;
  modelica_real tmp248;
  modelica_metatype tmpMeta249;
  modelica_real tmp250;
  modelica_metatype tmpMeta251;
  modelica_real tmp252;
  modelica_metatype tmpMeta253;
  modelica_real tmp254;
  modelica_metatype tmpMeta255;
  modelica_real tmp256;
  modelica_metatype tmpMeta257;
  modelica_real tmp258;
  modelica_metatype tmpMeta259;
  modelica_real tmp260;
  modelica_metatype tmpMeta261;
  modelica_real tmp262;
  modelica_metatype tmpMeta263;
  modelica_real tmp264;
  modelica_metatype tmpMeta265;
  modelica_real tmp266;
  modelica_metatype tmpMeta267;
  modelica_real tmp268;
  modelica_metatype tmpMeta269;
  modelica_real tmp270;
  modelica_metatype tmpMeta271;
  modelica_real tmp272;
  modelica_metatype tmpMeta273;
  modelica_real tmp274;
  modelica_metatype tmpMeta275;
  modelica_real tmp276;
  modelica_metatype tmpMeta277;
  modelica_real tmp278;
  modelica_metatype tmpMeta279;
  modelica_real tmp280;
  modelica_metatype tmpMeta281;
  modelica_real tmp282;
  modelica_metatype tmpMeta283;
  modelica_real tmp284;
  modelica_metatype tmpMeta285;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord tmp286;
  modelica_metatype tmpMeta287;
  modelica_real tmp288;
  modelica_metatype tmpMeta289;
  modelica_real tmp290;
  modelica_metatype tmpMeta291;
  modelica_real tmp292;
  modelica_metatype tmpMeta293;
  modelica_real tmp294;
  modelica_metatype tmpMeta295;
  modelica_real tmp296;
  modelica_metatype tmpMeta297;
  modelica_real tmp298;
  modelica_metatype tmpMeta299;
  modelica_real tmp300;
  modelica_metatype tmpMeta301;
  modelica_real tmp302;
  modelica_metatype tmpMeta303;
  modelica_real tmp304;
  modelica_metatype tmpMeta305;
  modelica_real tmp306;
  modelica_metatype tmpMeta307;
  modelica_real tmp308;
  modelica_metatype tmpMeta309;
  modelica_real tmp310;
  modelica_real _Fy;
  modelica_real _Mx;
  modelica_real _My;
  modelica_real _Mz;
  modelica_real _t;
  modelica_real _s;
  modelica_real _Fx;
  modelica_metatype out_Fx;
  tmp1 = mmc_unbox_real(_Fz);
  tmp2 = mmc_unbox_real(_alpha);
  tmp3 = mmc_unbox_real(_kappa);
  tmp4 = mmc_unbox_real(_gamma);
  tmp5 = mmc_unbox_real(_Vx);
  tmpMeta7 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_tire), 2)));
  tmpMeta9 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta7), 2)));
  tmp10 = mmc_unbox_real(tmpMeta9);
  tmp8._FNOMIN = tmp10;
  tmpMeta11 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta7), 3)));
  tmp12 = mmc_unbox_real(tmpMeta11);
  tmp8._FZMIN = tmp12;
  tmpMeta13 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta7), 4)));
  tmp14 = mmc_unbox_real(tmpMeta13);
  tmp8._FZMAX = tmp14;
  tmpMeta15 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta7), 5)));
  tmp16 = mmc_unbox_real(tmpMeta15);
  tmp8._UNLOADED_RADIUS = tmp16;
  tmp6._setup = tmp8;
  tmpMeta17 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_tire), 3)));
  tmpMeta19 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta17), 2)));
  tmp20 = mmc_unbox_real(tmpMeta19);
  tmp18._FNOMIN = tmp20;
  tmpMeta21 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta17), 3)));
  tmp22 = mmc_unbox_real(tmpMeta21);
  tmp18._UNLOADED_RADIUS = tmp22;
  tmpMeta23 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta17), 4)));
  tmp24 = mmc_unbox_real(tmpMeta23);
  tmp18._LFZO = tmp24;
  tmpMeta25 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta17), 5)));
  tmp26 = mmc_unbox_real(tmpMeta25);
  tmp18._PTX1 = tmp26;
  tmpMeta27 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta17), 6)));
  tmp28 = mmc_unbox_real(tmpMeta27);
  tmp18._PTX2 = tmp28;
  tmpMeta29 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta17), 7)));
  tmp30 = mmc_unbox_real(tmpMeta29);
  tmp18._PTX3 = tmp30;
  tmpMeta31 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta17), 8)));
  tmp32 = mmc_unbox_real(tmpMeta31);
  tmp18._PTY1 = tmp32;
  tmpMeta33 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta17), 9)));
  tmp34 = mmc_unbox_real(tmpMeta33);
  tmp18._PTY2 = tmp34;
  tmpMeta35 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta17), 10)));
  tmp36 = mmc_unbox_real(tmpMeta35);
  tmp18._PKY3 = tmp36;
  tmpMeta37 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta17), 11)));
  tmp38 = mmc_unbox_real(tmpMeta37);
  tmp18._LSGKP = tmp38;
  tmpMeta39 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta17), 12)));
  tmp40 = mmc_unbox_real(tmpMeta39);
  tmp18._LSGAL = tmp40;
  tmp6._relaxation = tmp18;
  tmpMeta41 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_tire), 4)));
  tmpMeta43 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 2)));
  tmp44 = mmc_unbox_real(tmpMeta43);
  tmp42._LGAX = tmp44;
  tmpMeta45 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 3)));
  tmp46 = mmc_unbox_real(tmpMeta45);
  tmp42._LFZO = tmp46;
  tmpMeta47 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 4)));
  tmp48 = mmc_unbox_real(tmpMeta47);
  tmp42._PCX1 = tmp48;
  tmpMeta49 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 5)));
  tmp50 = mmc_unbox_real(tmpMeta49);
  tmp42._PDX1 = tmp50;
  tmpMeta51 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 6)));
  tmp52 = mmc_unbox_real(tmpMeta51);
  tmp42._PDX2 = tmp52;
  tmpMeta53 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 7)));
  tmp54 = mmc_unbox_real(tmpMeta53);
  tmp42._PDX3 = tmp54;
  tmpMeta55 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 8)));
  tmp56 = mmc_unbox_real(tmpMeta55);
  tmp42._PKX1 = tmp56;
  tmpMeta57 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 9)));
  tmp58 = mmc_unbox_real(tmpMeta57);
  tmp42._PKX2 = tmp58;
  tmpMeta59 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 10)));
  tmp60 = mmc_unbox_real(tmpMeta59);
  tmp42._PKX3 = tmp60;
  tmpMeta61 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 11)));
  tmp62 = mmc_unbox_real(tmpMeta61);
  tmp42._PHX1 = tmp62;
  tmpMeta63 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 12)));
  tmp64 = mmc_unbox_real(tmpMeta63);
  tmp42._PHX2 = tmp64;
  tmpMeta65 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 13)));
  tmp66 = mmc_unbox_real(tmpMeta65);
  tmp42._PVX1 = tmp66;
  tmpMeta67 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 14)));
  tmp68 = mmc_unbox_real(tmpMeta67);
  tmp42._PVX2 = tmp68;
  tmpMeta69 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 15)));
  tmp70 = mmc_unbox_real(tmpMeta69);
  tmp42._PEX1 = tmp70;
  tmpMeta71 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 16)));
  tmp72 = mmc_unbox_real(tmpMeta71);
  tmp42._PEX2 = tmp72;
  tmpMeta73 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 17)));
  tmp74 = mmc_unbox_real(tmpMeta73);
  tmp42._PEX3 = tmp74;
  tmpMeta75 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 18)));
  tmp76 = mmc_unbox_real(tmpMeta75);
  tmp42._PEX4 = tmp76;
  tmpMeta77 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 19)));
  tmp78 = mmc_unbox_real(tmpMeta77);
  tmp42._LCX = tmp78;
  tmpMeta79 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 20)));
  tmp80 = mmc_unbox_real(tmpMeta79);
  tmp42._LMUX = tmp80;
  tmpMeta81 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 21)));
  tmp82 = mmc_unbox_real(tmpMeta81);
  tmp42._LKX = tmp82;
  tmpMeta83 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 22)));
  tmp84 = mmc_unbox_real(tmpMeta83);
  tmp42._LHX = tmp84;
  tmpMeta85 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 23)));
  tmp86 = mmc_unbox_real(tmpMeta85);
  tmp42._LVX = tmp86;
  tmpMeta87 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 24)));
  tmp88 = mmc_unbox_real(tmpMeta87);
  tmp42._LEX = tmp88;
  tmpMeta89 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta41), 25)));
  tmp90 = mmc_unbox_real(tmpMeta89);
  tmp42._LXAL = tmp90;
  tmp6._fxPure = tmp42;
  tmpMeta91 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_tire), 5)));
  tmpMeta93 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta91), 2)));
  tmp94 = mmc_unbox_real(tmpMeta93);
  tmp92._RBX1 = tmp94;
  tmpMeta95 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta91), 3)));
  tmp96 = mmc_unbox_real(tmpMeta95);
  tmp92._RBX2 = tmp96;
  tmpMeta97 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta91), 4)));
  tmp98 = mmc_unbox_real(tmpMeta97);
  tmp92._RCX1 = tmp98;
  tmpMeta99 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta91), 5)));
  tmp100 = mmc_unbox_real(tmpMeta99);
  tmp92._REX1 = tmp100;
  tmpMeta101 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta91), 6)));
  tmp102 = mmc_unbox_real(tmpMeta101);
  tmp92._REX2 = tmp102;
  tmpMeta103 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta91), 7)));
  tmp104 = mmc_unbox_real(tmpMeta103);
  tmp92._RHX1 = tmp104;
  tmp6._fxCombined = tmp92;
  tmpMeta105 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_tire), 6)));
  tmpMeta107 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 2)));
  tmp108 = mmc_unbox_real(tmpMeta107);
  tmp106._LFZO = tmp108;
  tmpMeta109 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 3)));
  tmp110 = mmc_unbox_real(tmpMeta109);
  tmp106._LGAY = tmp110;
  tmpMeta111 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 4)));
  tmp112 = mmc_unbox_real(tmpMeta111);
  tmp106._PCY1 = tmp112;
  tmpMeta113 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 5)));
  tmp114 = mmc_unbox_real(tmpMeta113);
  tmp106._PDY1 = tmp114;
  tmpMeta115 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 6)));
  tmp116 = mmc_unbox_real(tmpMeta115);
  tmp106._PDY2 = tmp116;
  tmpMeta117 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 7)));
  tmp118 = mmc_unbox_real(tmpMeta117);
  tmp106._PDY3 = tmp118;
  tmpMeta119 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 8)));
  tmp120 = mmc_unbox_real(tmpMeta119);
  tmp106._PKY1 = tmp120;
  tmpMeta121 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 9)));
  tmp122 = mmc_unbox_real(tmpMeta121);
  tmp106._PKY2 = tmp122;
  tmpMeta123 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 10)));
  tmp124 = mmc_unbox_real(tmpMeta123);
  tmp106._PKY3 = tmp124;
  tmpMeta125 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 11)));
  tmp126 = mmc_unbox_real(tmpMeta125);
  tmp106._PHY1 = tmp126;
  tmpMeta127 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 12)));
  tmp128 = mmc_unbox_real(tmpMeta127);
  tmp106._PHY2 = tmp128;
  tmpMeta129 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 13)));
  tmp130 = mmc_unbox_real(tmpMeta129);
  tmp106._PHY3 = tmp130;
  tmpMeta131 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 14)));
  tmp132 = mmc_unbox_real(tmpMeta131);
  tmp106._PVY1 = tmp132;
  tmpMeta133 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 15)));
  tmp134 = mmc_unbox_real(tmpMeta133);
  tmp106._PVY2 = tmp134;
  tmpMeta135 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 16)));
  tmp136 = mmc_unbox_real(tmpMeta135);
  tmp106._PVY3 = tmp136;
  tmpMeta137 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 17)));
  tmp138 = mmc_unbox_real(tmpMeta137);
  tmp106._PVY4 = tmp138;
  tmpMeta139 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 18)));
  tmp140 = mmc_unbox_real(tmpMeta139);
  tmp106._PEY1 = tmp140;
  tmpMeta141 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 19)));
  tmp142 = mmc_unbox_real(tmpMeta141);
  tmp106._PEY2 = tmp142;
  tmpMeta143 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 20)));
  tmp144 = mmc_unbox_real(tmpMeta143);
  tmp106._PEY3 = tmp144;
  tmpMeta145 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 21)));
  tmp146 = mmc_unbox_real(tmpMeta145);
  tmp106._PEY4 = tmp146;
  tmpMeta147 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 22)));
  tmp148 = mmc_unbox_real(tmpMeta147);
  tmp106._LCY = tmp148;
  tmpMeta149 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 23)));
  tmp150 = mmc_unbox_real(tmpMeta149);
  tmp106._LMUY = tmp150;
  tmpMeta151 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 24)));
  tmp152 = mmc_unbox_real(tmpMeta151);
  tmp106._LEY = tmp152;
  tmpMeta153 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 25)));
  tmp154 = mmc_unbox_real(tmpMeta153);
  tmp106._LKY = tmp154;
  tmpMeta155 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 26)));
  tmp156 = mmc_unbox_real(tmpMeta155);
  tmp106._LHY = tmp156;
  tmpMeta157 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 27)));
  tmp158 = mmc_unbox_real(tmpMeta157);
  tmp106._LVY = tmp158;
  tmpMeta159 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 28)));
  tmp160 = mmc_unbox_real(tmpMeta159);
  tmp106._LYKA = tmp160;
  tmpMeta161 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta105), 29)));
  tmp162 = mmc_unbox_real(tmpMeta161);
  tmp106._LVYKA = tmp162;
  tmp6._fyPure = tmp106;
  tmpMeta163 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_tire), 7)));
  tmpMeta165 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta163), 2)));
  tmp166 = mmc_unbox_real(tmpMeta165);
  tmp164._RBY1 = tmp166;
  tmpMeta167 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta163), 3)));
  tmp168 = mmc_unbox_real(tmpMeta167);
  tmp164._RBY2 = tmp168;
  tmpMeta169 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta163), 4)));
  tmp170 = mmc_unbox_real(tmpMeta169);
  tmp164._RBY3 = tmp170;
  tmpMeta171 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta163), 5)));
  tmp172 = mmc_unbox_real(tmpMeta171);
  tmp164._RCY1 = tmp172;
  tmpMeta173 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta163), 6)));
  tmp174 = mmc_unbox_real(tmpMeta173);
  tmp164._REY1 = tmp174;
  tmpMeta175 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta163), 7)));
  tmp176 = mmc_unbox_real(tmpMeta175);
  tmp164._REY2 = tmp176;
  tmpMeta177 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta163), 8)));
  tmp178 = mmc_unbox_real(tmpMeta177);
  tmp164._RHY1 = tmp178;
  tmpMeta179 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta163), 9)));
  tmp180 = mmc_unbox_real(tmpMeta179);
  tmp164._RHY2 = tmp180;
  tmpMeta181 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta163), 10)));
  tmp182 = mmc_unbox_real(tmpMeta181);
  tmp164._RVY1 = tmp182;
  tmpMeta183 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta163), 11)));
  tmp184 = mmc_unbox_real(tmpMeta183);
  tmp164._RVY2 = tmp184;
  tmpMeta185 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta163), 12)));
  tmp186 = mmc_unbox_real(tmpMeta185);
  tmp164._RVY3 = tmp186;
  tmpMeta187 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta163), 13)));
  tmp188 = mmc_unbox_real(tmpMeta187);
  tmp164._RVY4 = tmp188;
  tmpMeta189 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta163), 14)));
  tmp190 = mmc_unbox_real(tmpMeta189);
  tmp164._RVY5 = tmp190;
  tmpMeta191 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta163), 15)));
  tmp192 = mmc_unbox_real(tmpMeta191);
  tmp164._RVY6 = tmp192;
  tmp6._fyCombined = tmp164;
  tmpMeta193 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_tire), 8)));
  tmpMeta195 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta193), 2)));
  tmp196 = mmc_unbox_real(tmpMeta195);
  tmp194._QSX1 = tmp196;
  tmpMeta197 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta193), 3)));
  tmp198 = mmc_unbox_real(tmpMeta197);
  tmp194._QSX2 = tmp198;
  tmpMeta199 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta193), 4)));
  tmp200 = mmc_unbox_real(tmpMeta199);
  tmp194._QSX3 = tmp200;
  tmpMeta201 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta193), 5)));
  tmp202 = mmc_unbox_real(tmpMeta201);
  tmp194._LMX = tmp202;
  tmpMeta203 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta193), 6)));
  tmp204 = mmc_unbox_real(tmpMeta203);
  tmp194._LVMX = tmp204;
  tmp6._mxPure = tmp194;
  tmpMeta205 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_tire), 9)));
  tmp6._mxCombined = tmp206;
  tmpMeta207 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_tire), 10)));
  tmpMeta209 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta207), 2)));
  tmp210 = mmc_unbox_real(tmpMeta209);
  tmp208._QSY1 = tmp210;
  tmpMeta211 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta207), 3)));
  tmp212 = mmc_unbox_real(tmpMeta211);
  tmp208._QSY2 = tmp212;
  tmpMeta213 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta207), 4)));
  tmp214 = mmc_unbox_real(tmpMeta213);
  tmp208._QSY3 = tmp214;
  tmpMeta215 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta207), 5)));
  tmp216 = mmc_unbox_real(tmpMeta215);
  tmp208._QSY4 = tmp216;
  tmpMeta217 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta207), 6)));
  tmp218 = mmc_unbox_real(tmpMeta217);
  tmp208._Vref = tmp218;
  tmpMeta219 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta207), 7)));
  tmp220 = mmc_unbox_real(tmpMeta219);
  tmp208._LMY = tmp220;
  tmp6._myPure = tmp208;
  tmpMeta221 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_tire), 11)));
  tmp6._myCombined = tmp222;
  tmpMeta223 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_tire), 12)));
  tmpMeta225 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 2)));
  tmp226 = mmc_unbox_real(tmpMeta225);
  tmp224._QBZ1 = tmp226;
  tmpMeta227 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 3)));
  tmp228 = mmc_unbox_real(tmpMeta227);
  tmp224._QBZ2 = tmp228;
  tmpMeta229 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 4)));
  tmp230 = mmc_unbox_real(tmpMeta229);
  tmp224._QBZ3 = tmp230;
  tmpMeta231 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 5)));
  tmp232 = mmc_unbox_real(tmpMeta231);
  tmp224._QBZ4 = tmp232;
  tmpMeta233 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 6)));
  tmp234 = mmc_unbox_real(tmpMeta233);
  tmp224._QBZ5 = tmp234;
  tmpMeta235 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 7)));
  tmp236 = mmc_unbox_real(tmpMeta235);
  tmp224._QCZ1 = tmp236;
  tmpMeta237 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 8)));
  tmp238 = mmc_unbox_real(tmpMeta237);
  tmp224._QDZ1 = tmp238;
  tmpMeta239 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 9)));
  tmp240 = mmc_unbox_real(tmpMeta239);
  tmp224._QDZ2 = tmp240;
  tmpMeta241 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 10)));
  tmp242 = mmc_unbox_real(tmpMeta241);
  tmp224._QDZ3 = tmp242;
  tmpMeta243 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 11)));
  tmp244 = mmc_unbox_real(tmpMeta243);
  tmp224._QDZ4 = tmp244;
  tmpMeta245 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 12)));
  tmp246 = mmc_unbox_real(tmpMeta245);
  tmp224._QEZ1 = tmp246;
  tmpMeta247 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 13)));
  tmp248 = mmc_unbox_real(tmpMeta247);
  tmp224._QEZ2 = tmp248;
  tmpMeta249 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 14)));
  tmp250 = mmc_unbox_real(tmpMeta249);
  tmp224._QEZ3 = tmp250;
  tmpMeta251 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 15)));
  tmp252 = mmc_unbox_real(tmpMeta251);
  tmp224._QEZ4 = tmp252;
  tmpMeta253 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 16)));
  tmp254 = mmc_unbox_real(tmpMeta253);
  tmp224._QEZ5 = tmp254;
  tmpMeta255 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 17)));
  tmp256 = mmc_unbox_real(tmpMeta255);
  tmp224._QHZ1 = tmp256;
  tmpMeta257 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 18)));
  tmp258 = mmc_unbox_real(tmpMeta257);
  tmp224._QHZ2 = tmp258;
  tmpMeta259 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 19)));
  tmp260 = mmc_unbox_real(tmpMeta259);
  tmp224._QHZ3 = tmp260;
  tmpMeta261 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 20)));
  tmp262 = mmc_unbox_real(tmpMeta261);
  tmp224._QHZ4 = tmp262;
  tmpMeta263 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 21)));
  tmp264 = mmc_unbox_real(tmpMeta263);
  tmp224._QBZ9 = tmp264;
  tmpMeta265 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 22)));
  tmp266 = mmc_unbox_real(tmpMeta265);
  tmp224._QBZ10 = tmp266;
  tmpMeta267 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 23)));
  tmp268 = mmc_unbox_real(tmpMeta267);
  tmp224._QDZ6 = tmp268;
  tmpMeta269 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 24)));
  tmp270 = mmc_unbox_real(tmpMeta269);
  tmp224._QDZ7 = tmp270;
  tmpMeta271 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 25)));
  tmp272 = mmc_unbox_real(tmpMeta271);
  tmp224._QDZ8 = tmp272;
  tmpMeta273 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 26)));
  tmp274 = mmc_unbox_real(tmpMeta273);
  tmp224._QDZ9 = tmp274;
  tmpMeta275 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 27)));
  tmp276 = mmc_unbox_real(tmpMeta275);
  tmp224._LTR = tmp276;
  tmpMeta277 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 28)));
  tmp278 = mmc_unbox_real(tmpMeta277);
  tmp224._LRES = tmp278;
  tmpMeta279 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 29)));
  tmp280 = mmc_unbox_real(tmpMeta279);
  tmp224._LKY = tmp280;
  tmpMeta281 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 30)));
  tmp282 = mmc_unbox_real(tmpMeta281);
  tmp224._LMUY = tmp282;
  tmpMeta283 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta223), 31)));
  tmp284 = mmc_unbox_real(tmpMeta283);
  tmp224._LGAZ = tmp284;
  tmp6._mzPure = tmp224;
  tmpMeta285 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_tire), 13)));
  tmpMeta287 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta285), 2)));
  tmp288 = mmc_unbox_real(tmpMeta287);
  tmp286._SSZ1 = tmp288;
  tmpMeta289 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta285), 3)));
  tmp290 = mmc_unbox_real(tmpMeta289);
  tmp286._SSZ2 = tmp290;
  tmpMeta291 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta285), 4)));
  tmp292 = mmc_unbox_real(tmpMeta291);
  tmp286._SSZ3 = tmp292;
  tmpMeta293 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta285), 5)));
  tmp294 = mmc_unbox_real(tmpMeta293);
  tmp286._SSZ4 = tmp294;
  tmpMeta295 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta285), 6)));
  tmp296 = mmc_unbox_real(tmpMeta295);
  tmp286._RVY1 = tmp296;
  tmpMeta297 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta285), 7)));
  tmp298 = mmc_unbox_real(tmpMeta297);
  tmp286._RVY2 = tmp298;
  tmpMeta299 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta285), 8)));
  tmp300 = mmc_unbox_real(tmpMeta299);
  tmp286._RVY3 = tmp300;
  tmpMeta301 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta285), 9)));
  tmp302 = mmc_unbox_real(tmpMeta301);
  tmp286._RVY4 = tmp302;
  tmpMeta303 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta285), 10)));
  tmp304 = mmc_unbox_real(tmpMeta303);
  tmp286._RVY5 = tmp304;
  tmpMeta305 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta285), 11)));
  tmp306 = mmc_unbox_real(tmpMeta305);
  tmp286._RVY6 = tmp306;
  tmpMeta307 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta285), 12)));
  tmp308 = mmc_unbox_real(tmpMeta307);
  tmp286._LS = tmp308;
  tmpMeta309 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(tmpMeta285), 13)));
  tmp310 = mmc_unbox_real(tmpMeta309);
  tmp286._LVYKA = tmp310;
  tmp6._mzCombined = tmp286;
  _Fx = omc_BobLib_Chassis_Suspension_Tires_MF52_Eval(threadData, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, &_Fy, &_Mx, &_My, &_Mz, &_t, &_s);
  out_Fx = mmc_mk_rcon(_Fx);
  if (out_Fy) { *out_Fy = mmc_mk_rcon(_Fy); }
  if (out_Mx) { *out_Mx = mmc_mk_rcon(_Mx); }
  if (out_My) { *out_My = mmc_mk_rcon(_My); }
  if (out_Mz) { *out_Mz = mmc_mk_rcon(_Mz); }
  if (out_t) { *out_t = mmc_mk_rcon(_t); }
  if (out_s) { *out_s = mmc_mk_rcon(_s); }
  return out_Fx;
}

DLLDirection
modelica_real omc_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_FxCombinedEval(threadData_t *threadData, modelica_real _Fz, modelica_real _kappa, modelica_real _alpha, modelica_real _gamma, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord _pPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord _pComb, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord _setup)
{
  modelica_real _Fx;
  modelica_real _Fx_pure;
  modelica_real _dfz;
  modelica_real _C_xSA;
  modelica_real _B_xSA;
  modelica_real _E_xSA;
  modelica_real _S_HxSA;
  modelica_real _SA_s;
  modelica_real _G_xSA;
  modelica_real tmp1;
  modelica_real tmp2;
  _tailrecursive: OMC_LABEL_UNUSED
  // _Fx has no default value.
  // _Fx_pure has no default value.
  // _dfz has no default value.
  // _C_xSA has no default value.
  // _B_xSA has no default value.
  // _E_xSA has no default value.
  // _S_HxSA has no default value.
  // _SA_s has no default value.
  // _G_xSA has no default value.
  if((_Fz > 0.001))
  {
    _Fx_pure = omc_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_FxPureEval(threadData, _Fz, _kappa, _gamma, _pPure, _setup);

    tmp1 = (_setup._FNOMIN) * (_pPure._LFZO);
    if (tmp1 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "(Fz - setup.FNOMIN * pPure.LFZO) / (setup.FNOMIN * pPure.LFZO)");}
    _dfz = (_Fz - ((_setup._FNOMIN) * (_pPure._LFZO))) / tmp1;

    _C_xSA = _pComb._RCX1;

    _B_xSA = ((_pComb._RBX1) * (cos(atan((_pComb._RBX2) * (_kappa))))) * (_pPure._LXAL);

    _E_xSA = _pComb._REX1 + (_pComb._REX2) * (_dfz);

    _S_HxSA = _pComb._RHX1;

    _SA_s = _alpha + _S_HxSA;

    tmp2 = cos((_C_xSA) * (atan((_B_xSA) * (_S_HxSA) - ((_E_xSA) * ((_B_xSA) * (_S_HxSA) - atan((_B_xSA) * (_S_HxSA)))))));
    if (tmp2 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "cos(C_xSA * atan(B_xSA * SA_s - E_xSA * (B_xSA * SA_s - atan(B_xSA * SA_s)))) / cos(C_xSA * atan(B_xSA * S_HxSA - E_xSA * (B_xSA * S_HxSA - atan(B_xSA * S_HxSA))))");}
    _G_xSA = (cos((_C_xSA) * (atan((_B_xSA) * (_SA_s) - ((_E_xSA) * ((_B_xSA) * (_SA_s) - atan((_B_xSA) * (_SA_s)))))))) / tmp2;

    _Fx = (_Fx_pure) * (_G_xSA);
  }
  else
  {
    _Fx = 0.0;
  }
  _return: OMC_LABEL_UNUSED
  return _Fx;
}
modelica_metatype boxptr_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_FxCombinedEval(threadData_t *threadData, modelica_metatype _Fz, modelica_metatype _kappa, modelica_metatype _alpha, modelica_metatype _gamma, modelica_metatype _pPure, modelica_metatype _pComb, modelica_metatype _setup)
{
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  modelica_real tmp4;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord tmp5;
  modelica_metatype tmpMeta6;
  modelica_real tmp7;
  modelica_metatype tmpMeta8;
  modelica_real tmp9;
  modelica_metatype tmpMeta10;
  modelica_real tmp11;
  modelica_metatype tmpMeta12;
  modelica_real tmp13;
  modelica_metatype tmpMeta14;
  modelica_real tmp15;
  modelica_metatype tmpMeta16;
  modelica_real tmp17;
  modelica_metatype tmpMeta18;
  modelica_real tmp19;
  modelica_metatype tmpMeta20;
  modelica_real tmp21;
  modelica_metatype tmpMeta22;
  modelica_real tmp23;
  modelica_metatype tmpMeta24;
  modelica_real tmp25;
  modelica_metatype tmpMeta26;
  modelica_real tmp27;
  modelica_metatype tmpMeta28;
  modelica_real tmp29;
  modelica_metatype tmpMeta30;
  modelica_real tmp31;
  modelica_metatype tmpMeta32;
  modelica_real tmp33;
  modelica_metatype tmpMeta34;
  modelica_real tmp35;
  modelica_metatype tmpMeta36;
  modelica_real tmp37;
  modelica_metatype tmpMeta38;
  modelica_real tmp39;
  modelica_metatype tmpMeta40;
  modelica_real tmp41;
  modelica_metatype tmpMeta42;
  modelica_real tmp43;
  modelica_metatype tmpMeta44;
  modelica_real tmp45;
  modelica_metatype tmpMeta46;
  modelica_real tmp47;
  modelica_metatype tmpMeta48;
  modelica_real tmp49;
  modelica_metatype tmpMeta50;
  modelica_real tmp51;
  modelica_metatype tmpMeta52;
  modelica_real tmp53;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord tmp54;
  modelica_metatype tmpMeta55;
  modelica_real tmp56;
  modelica_metatype tmpMeta57;
  modelica_real tmp58;
  modelica_metatype tmpMeta59;
  modelica_real tmp60;
  modelica_metatype tmpMeta61;
  modelica_real tmp62;
  modelica_metatype tmpMeta63;
  modelica_real tmp64;
  modelica_metatype tmpMeta65;
  modelica_real tmp66;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord tmp67;
  modelica_metatype tmpMeta68;
  modelica_real tmp69;
  modelica_metatype tmpMeta70;
  modelica_real tmp71;
  modelica_metatype tmpMeta72;
  modelica_real tmp73;
  modelica_metatype tmpMeta74;
  modelica_real tmp75;
  modelica_real _Fx;
  modelica_metatype out_Fx;
  tmp1 = mmc_unbox_real(_Fz);
  tmp2 = mmc_unbox_real(_kappa);
  tmp3 = mmc_unbox_real(_alpha);
  tmp4 = mmc_unbox_real(_gamma);
  tmpMeta6 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 2)));
  tmp7 = mmc_unbox_real(tmpMeta6);
  tmp5._LGAX = tmp7;
  tmpMeta8 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 3)));
  tmp9 = mmc_unbox_real(tmpMeta8);
  tmp5._LFZO = tmp9;
  tmpMeta10 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 4)));
  tmp11 = mmc_unbox_real(tmpMeta10);
  tmp5._PCX1 = tmp11;
  tmpMeta12 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 5)));
  tmp13 = mmc_unbox_real(tmpMeta12);
  tmp5._PDX1 = tmp13;
  tmpMeta14 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 6)));
  tmp15 = mmc_unbox_real(tmpMeta14);
  tmp5._PDX2 = tmp15;
  tmpMeta16 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 7)));
  tmp17 = mmc_unbox_real(tmpMeta16);
  tmp5._PDX3 = tmp17;
  tmpMeta18 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 8)));
  tmp19 = mmc_unbox_real(tmpMeta18);
  tmp5._PKX1 = tmp19;
  tmpMeta20 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 9)));
  tmp21 = mmc_unbox_real(tmpMeta20);
  tmp5._PKX2 = tmp21;
  tmpMeta22 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 10)));
  tmp23 = mmc_unbox_real(tmpMeta22);
  tmp5._PKX3 = tmp23;
  tmpMeta24 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 11)));
  tmp25 = mmc_unbox_real(tmpMeta24);
  tmp5._PHX1 = tmp25;
  tmpMeta26 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 12)));
  tmp27 = mmc_unbox_real(tmpMeta26);
  tmp5._PHX2 = tmp27;
  tmpMeta28 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 13)));
  tmp29 = mmc_unbox_real(tmpMeta28);
  tmp5._PVX1 = tmp29;
  tmpMeta30 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 14)));
  tmp31 = mmc_unbox_real(tmpMeta30);
  tmp5._PVX2 = tmp31;
  tmpMeta32 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 15)));
  tmp33 = mmc_unbox_real(tmpMeta32);
  tmp5._PEX1 = tmp33;
  tmpMeta34 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 16)));
  tmp35 = mmc_unbox_real(tmpMeta34);
  tmp5._PEX2 = tmp35;
  tmpMeta36 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 17)));
  tmp37 = mmc_unbox_real(tmpMeta36);
  tmp5._PEX3 = tmp37;
  tmpMeta38 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 18)));
  tmp39 = mmc_unbox_real(tmpMeta38);
  tmp5._PEX4 = tmp39;
  tmpMeta40 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 19)));
  tmp41 = mmc_unbox_real(tmpMeta40);
  tmp5._LCX = tmp41;
  tmpMeta42 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 20)));
  tmp43 = mmc_unbox_real(tmpMeta42);
  tmp5._LMUX = tmp43;
  tmpMeta44 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 21)));
  tmp45 = mmc_unbox_real(tmpMeta44);
  tmp5._LKX = tmp45;
  tmpMeta46 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 22)));
  tmp47 = mmc_unbox_real(tmpMeta46);
  tmp5._LHX = tmp47;
  tmpMeta48 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 23)));
  tmp49 = mmc_unbox_real(tmpMeta48);
  tmp5._LVX = tmp49;
  tmpMeta50 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 24)));
  tmp51 = mmc_unbox_real(tmpMeta50);
  tmp5._LEX = tmp51;
  tmpMeta52 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 25)));
  tmp53 = mmc_unbox_real(tmpMeta52);
  tmp5._LXAL = tmp53;tmpMeta55 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 2)));
  tmp56 = mmc_unbox_real(tmpMeta55);
  tmp54._RBX1 = tmp56;
  tmpMeta57 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 3)));
  tmp58 = mmc_unbox_real(tmpMeta57);
  tmp54._RBX2 = tmp58;
  tmpMeta59 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 4)));
  tmp60 = mmc_unbox_real(tmpMeta59);
  tmp54._RCX1 = tmp60;
  tmpMeta61 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 5)));
  tmp62 = mmc_unbox_real(tmpMeta61);
  tmp54._REX1 = tmp62;
  tmpMeta63 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 6)));
  tmp64 = mmc_unbox_real(tmpMeta63);
  tmp54._REX2 = tmp64;
  tmpMeta65 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 7)));
  tmp66 = mmc_unbox_real(tmpMeta65);
  tmp54._RHX1 = tmp66;tmpMeta68 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 2)));
  tmp69 = mmc_unbox_real(tmpMeta68);
  tmp67._FNOMIN = tmp69;
  tmpMeta70 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 3)));
  tmp71 = mmc_unbox_real(tmpMeta70);
  tmp67._FZMIN = tmp71;
  tmpMeta72 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 4)));
  tmp73 = mmc_unbox_real(tmpMeta72);
  tmp67._FZMAX = tmp73;
  tmpMeta74 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 5)));
  tmp75 = mmc_unbox_real(tmpMeta74);
  tmp67._UNLOADED_RADIUS = tmp75;
  _Fx = omc_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_FxCombinedEval(threadData, tmp1, tmp2, tmp3, tmp4, tmp5, tmp54, tmp67);
  out_Fx = mmc_mk_rcon(_Fx);
  return out_Fx;
}

DLLDirection
modelica_real omc_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_FyCombinedEval(threadData_t *threadData, modelica_real _Fz, modelica_real _alpha, modelica_real _kappa, modelica_real _gamma, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord _pPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord _pComb, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord _setup)
{
  modelica_real _Fy;
  modelica_real _Fy_pure;
  modelica_real _dfz;
  modelica_real _C_ySR;
  modelica_real _B_ySR;
  modelica_real _E_ySR;
  modelica_real _S_HySR;
  modelica_real _D_VySR;
  modelica_real _S_VySR;
  modelica_real _SR_s;
  modelica_real _G_ySR;
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  _tailrecursive: OMC_LABEL_UNUSED
  // _Fy has no default value.
  // _Fy_pure has no default value.
  // _dfz has no default value.
  // _C_ySR has no default value.
  // _B_ySR has no default value.
  // _E_ySR has no default value.
  // _S_HySR has no default value.
  // _D_VySR has no default value.
  // _S_VySR has no default value.
  // _SR_s has no default value.
  // _G_ySR has no default value.
  if((_Fz > 0.001))
  {
    _Fy_pure = omc_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_FyPureEval(threadData, _Fz, _alpha, _gamma, _pPure, _setup);

    tmp1 = (_setup._FNOMIN) * (_pPure._LFZO);
    if (tmp1 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "(Fz - setup.FNOMIN * pPure.LFZO) / (setup.FNOMIN * pPure.LFZO)");}
    _dfz = (_Fz - ((_setup._FNOMIN) * (_pPure._LFZO))) / tmp1;

    _C_ySR = _pComb._RCY1;

    _B_ySR = ((_pComb._RBY1) * (cos(atan((_pComb._RBY2) * (_alpha - _pComb._RBY3))))) * (_pPure._LYKA);

    _E_ySR = _pComb._REY1 + (_pComb._REY2) * (_dfz);

    _S_HySR = _pComb._RHY1 + (_pComb._RHY2) * (_dfz);

    tmp2 = (_gamma) * (_pPure._LGAY);
    _D_VySR = (((((_pPure._PDY1 + (_pPure._PDY2) * (_dfz)) * (1.0 - ((_pPure._PDY3) * ((tmp2 * tmp2))))) * (_pPure._LMUY)) * (_Fz)) * (_pComb._RVY1 + (_pComb._RVY2) * (_dfz) + (_pComb._RVY3) * (_gamma))) * (cos(atan((_pComb._RVY4) * (_alpha))));

    _S_VySR = ((_D_VySR) * (sin((_pComb._RVY5) * (atan((_pComb._RVY6) * (_kappa)))))) * (_pPure._LVYKA);

    _SR_s = _kappa + _S_HySR;

    tmp3 = cos((_C_ySR) * (atan((_B_ySR) * (_S_HySR) - ((_E_ySR) * ((_B_ySR) * (_S_HySR) - atan((_B_ySR) * (_S_HySR)))))));
    if (tmp3 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "cos(C_ySR * atan(B_ySR * SR_s - E_ySR * (B_ySR * SR_s - atan(B_ySR * SR_s)))) / cos(C_ySR * atan(B_ySR * S_HySR - E_ySR * (B_ySR * S_HySR - atan(B_ySR * S_HySR))))");}
    _G_ySR = (cos((_C_ySR) * (atan((_B_ySR) * (_SR_s) - ((_E_ySR) * ((_B_ySR) * (_SR_s) - atan((_B_ySR) * (_SR_s)))))))) / tmp3;

    _Fy = (_Fy_pure) * (_G_ySR) + _S_VySR;
  }
  else
  {
    _Fy = 0.0;
  }
  _return: OMC_LABEL_UNUSED
  return _Fy;
}
modelica_metatype boxptr_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_FyCombinedEval(threadData_t *threadData, modelica_metatype _Fz, modelica_metatype _alpha, modelica_metatype _kappa, modelica_metatype _gamma, modelica_metatype _pPure, modelica_metatype _pComb, modelica_metatype _setup)
{
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  modelica_real tmp4;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord tmp5;
  modelica_metatype tmpMeta6;
  modelica_real tmp7;
  modelica_metatype tmpMeta8;
  modelica_real tmp9;
  modelica_metatype tmpMeta10;
  modelica_real tmp11;
  modelica_metatype tmpMeta12;
  modelica_real tmp13;
  modelica_metatype tmpMeta14;
  modelica_real tmp15;
  modelica_metatype tmpMeta16;
  modelica_real tmp17;
  modelica_metatype tmpMeta18;
  modelica_real tmp19;
  modelica_metatype tmpMeta20;
  modelica_real tmp21;
  modelica_metatype tmpMeta22;
  modelica_real tmp23;
  modelica_metatype tmpMeta24;
  modelica_real tmp25;
  modelica_metatype tmpMeta26;
  modelica_real tmp27;
  modelica_metatype tmpMeta28;
  modelica_real tmp29;
  modelica_metatype tmpMeta30;
  modelica_real tmp31;
  modelica_metatype tmpMeta32;
  modelica_real tmp33;
  modelica_metatype tmpMeta34;
  modelica_real tmp35;
  modelica_metatype tmpMeta36;
  modelica_real tmp37;
  modelica_metatype tmpMeta38;
  modelica_real tmp39;
  modelica_metatype tmpMeta40;
  modelica_real tmp41;
  modelica_metatype tmpMeta42;
  modelica_real tmp43;
  modelica_metatype tmpMeta44;
  modelica_real tmp45;
  modelica_metatype tmpMeta46;
  modelica_real tmp47;
  modelica_metatype tmpMeta48;
  modelica_real tmp49;
  modelica_metatype tmpMeta50;
  modelica_real tmp51;
  modelica_metatype tmpMeta52;
  modelica_real tmp53;
  modelica_metatype tmpMeta54;
  modelica_real tmp55;
  modelica_metatype tmpMeta56;
  modelica_real tmp57;
  modelica_metatype tmpMeta58;
  modelica_real tmp59;
  modelica_metatype tmpMeta60;
  modelica_real tmp61;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord tmp62;
  modelica_metatype tmpMeta63;
  modelica_real tmp64;
  modelica_metatype tmpMeta65;
  modelica_real tmp66;
  modelica_metatype tmpMeta67;
  modelica_real tmp68;
  modelica_metatype tmpMeta69;
  modelica_real tmp70;
  modelica_metatype tmpMeta71;
  modelica_real tmp72;
  modelica_metatype tmpMeta73;
  modelica_real tmp74;
  modelica_metatype tmpMeta75;
  modelica_real tmp76;
  modelica_metatype tmpMeta77;
  modelica_real tmp78;
  modelica_metatype tmpMeta79;
  modelica_real tmp80;
  modelica_metatype tmpMeta81;
  modelica_real tmp82;
  modelica_metatype tmpMeta83;
  modelica_real tmp84;
  modelica_metatype tmpMeta85;
  modelica_real tmp86;
  modelica_metatype tmpMeta87;
  modelica_real tmp88;
  modelica_metatype tmpMeta89;
  modelica_real tmp90;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord tmp91;
  modelica_metatype tmpMeta92;
  modelica_real tmp93;
  modelica_metatype tmpMeta94;
  modelica_real tmp95;
  modelica_metatype tmpMeta96;
  modelica_real tmp97;
  modelica_metatype tmpMeta98;
  modelica_real tmp99;
  modelica_real _Fy;
  modelica_metatype out_Fy;
  tmp1 = mmc_unbox_real(_Fz);
  tmp2 = mmc_unbox_real(_alpha);
  tmp3 = mmc_unbox_real(_kappa);
  tmp4 = mmc_unbox_real(_gamma);
  tmpMeta6 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 2)));
  tmp7 = mmc_unbox_real(tmpMeta6);
  tmp5._LFZO = tmp7;
  tmpMeta8 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 3)));
  tmp9 = mmc_unbox_real(tmpMeta8);
  tmp5._LGAY = tmp9;
  tmpMeta10 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 4)));
  tmp11 = mmc_unbox_real(tmpMeta10);
  tmp5._PCY1 = tmp11;
  tmpMeta12 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 5)));
  tmp13 = mmc_unbox_real(tmpMeta12);
  tmp5._PDY1 = tmp13;
  tmpMeta14 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 6)));
  tmp15 = mmc_unbox_real(tmpMeta14);
  tmp5._PDY2 = tmp15;
  tmpMeta16 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 7)));
  tmp17 = mmc_unbox_real(tmpMeta16);
  tmp5._PDY3 = tmp17;
  tmpMeta18 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 8)));
  tmp19 = mmc_unbox_real(tmpMeta18);
  tmp5._PKY1 = tmp19;
  tmpMeta20 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 9)));
  tmp21 = mmc_unbox_real(tmpMeta20);
  tmp5._PKY2 = tmp21;
  tmpMeta22 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 10)));
  tmp23 = mmc_unbox_real(tmpMeta22);
  tmp5._PKY3 = tmp23;
  tmpMeta24 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 11)));
  tmp25 = mmc_unbox_real(tmpMeta24);
  tmp5._PHY1 = tmp25;
  tmpMeta26 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 12)));
  tmp27 = mmc_unbox_real(tmpMeta26);
  tmp5._PHY2 = tmp27;
  tmpMeta28 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 13)));
  tmp29 = mmc_unbox_real(tmpMeta28);
  tmp5._PHY3 = tmp29;
  tmpMeta30 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 14)));
  tmp31 = mmc_unbox_real(tmpMeta30);
  tmp5._PVY1 = tmp31;
  tmpMeta32 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 15)));
  tmp33 = mmc_unbox_real(tmpMeta32);
  tmp5._PVY2 = tmp33;
  tmpMeta34 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 16)));
  tmp35 = mmc_unbox_real(tmpMeta34);
  tmp5._PVY3 = tmp35;
  tmpMeta36 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 17)));
  tmp37 = mmc_unbox_real(tmpMeta36);
  tmp5._PVY4 = tmp37;
  tmpMeta38 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 18)));
  tmp39 = mmc_unbox_real(tmpMeta38);
  tmp5._PEY1 = tmp39;
  tmpMeta40 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 19)));
  tmp41 = mmc_unbox_real(tmpMeta40);
  tmp5._PEY2 = tmp41;
  tmpMeta42 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 20)));
  tmp43 = mmc_unbox_real(tmpMeta42);
  tmp5._PEY3 = tmp43;
  tmpMeta44 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 21)));
  tmp45 = mmc_unbox_real(tmpMeta44);
  tmp5._PEY4 = tmp45;
  tmpMeta46 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 22)));
  tmp47 = mmc_unbox_real(tmpMeta46);
  tmp5._LCY = tmp47;
  tmpMeta48 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 23)));
  tmp49 = mmc_unbox_real(tmpMeta48);
  tmp5._LMUY = tmp49;
  tmpMeta50 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 24)));
  tmp51 = mmc_unbox_real(tmpMeta50);
  tmp5._LEY = tmp51;
  tmpMeta52 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 25)));
  tmp53 = mmc_unbox_real(tmpMeta52);
  tmp5._LKY = tmp53;
  tmpMeta54 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 26)));
  tmp55 = mmc_unbox_real(tmpMeta54);
  tmp5._LHY = tmp55;
  tmpMeta56 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 27)));
  tmp57 = mmc_unbox_real(tmpMeta56);
  tmp5._LVY = tmp57;
  tmpMeta58 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 28)));
  tmp59 = mmc_unbox_real(tmpMeta58);
  tmp5._LYKA = tmp59;
  tmpMeta60 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 29)));
  tmp61 = mmc_unbox_real(tmpMeta60);
  tmp5._LVYKA = tmp61;tmpMeta63 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 2)));
  tmp64 = mmc_unbox_real(tmpMeta63);
  tmp62._RBY1 = tmp64;
  tmpMeta65 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 3)));
  tmp66 = mmc_unbox_real(tmpMeta65);
  tmp62._RBY2 = tmp66;
  tmpMeta67 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 4)));
  tmp68 = mmc_unbox_real(tmpMeta67);
  tmp62._RBY3 = tmp68;
  tmpMeta69 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 5)));
  tmp70 = mmc_unbox_real(tmpMeta69);
  tmp62._RCY1 = tmp70;
  tmpMeta71 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 6)));
  tmp72 = mmc_unbox_real(tmpMeta71);
  tmp62._REY1 = tmp72;
  tmpMeta73 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 7)));
  tmp74 = mmc_unbox_real(tmpMeta73);
  tmp62._REY2 = tmp74;
  tmpMeta75 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 8)));
  tmp76 = mmc_unbox_real(tmpMeta75);
  tmp62._RHY1 = tmp76;
  tmpMeta77 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 9)));
  tmp78 = mmc_unbox_real(tmpMeta77);
  tmp62._RHY2 = tmp78;
  tmpMeta79 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 10)));
  tmp80 = mmc_unbox_real(tmpMeta79);
  tmp62._RVY1 = tmp80;
  tmpMeta81 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 11)));
  tmp82 = mmc_unbox_real(tmpMeta81);
  tmp62._RVY2 = tmp82;
  tmpMeta83 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 12)));
  tmp84 = mmc_unbox_real(tmpMeta83);
  tmp62._RVY3 = tmp84;
  tmpMeta85 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 13)));
  tmp86 = mmc_unbox_real(tmpMeta85);
  tmp62._RVY4 = tmp86;
  tmpMeta87 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 14)));
  tmp88 = mmc_unbox_real(tmpMeta87);
  tmp62._RVY5 = tmp88;
  tmpMeta89 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 15)));
  tmp90 = mmc_unbox_real(tmpMeta89);
  tmp62._RVY6 = tmp90;tmpMeta92 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 2)));
  tmp93 = mmc_unbox_real(tmpMeta92);
  tmp91._FNOMIN = tmp93;
  tmpMeta94 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 3)));
  tmp95 = mmc_unbox_real(tmpMeta94);
  tmp91._FZMIN = tmp95;
  tmpMeta96 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 4)));
  tmp97 = mmc_unbox_real(tmpMeta96);
  tmp91._FZMAX = tmp97;
  tmpMeta98 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 5)));
  tmp99 = mmc_unbox_real(tmpMeta98);
  tmp91._UNLOADED_RADIUS = tmp99;
  _Fy = omc_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_FyCombinedEval(threadData, tmp1, tmp2, tmp3, tmp4, tmp5, tmp62, tmp91);
  out_Fy = mmc_mk_rcon(_Fy);
  return out_Fy;
}

DLLDirection
modelica_real omc_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MxCombinedEval(threadData_t *threadData, modelica_real _Fz, modelica_real _Fy, modelica_real _gamma, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord _pPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord _pComb, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord _setup)
{
  modelica_real _Mx;
  _tailrecursive: OMC_LABEL_UNUSED
  // _Mx has no default value.
  if((_Fz > 0.001))
  {
    _Mx = omc_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MxPureEval(threadData, _Fz, _Fy, _gamma, _pPure, _setup);
  }
  else
  {
    _Mx = 0.0;
  }
  _return: OMC_LABEL_UNUSED
  return _Mx;
}
modelica_metatype boxptr_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MxCombinedEval(threadData_t *threadData, modelica_metatype _Fz, modelica_metatype _Fy, modelica_metatype _gamma, modelica_metatype _pPure, modelica_metatype _pComb, modelica_metatype _setup)
{
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord tmp4;
  modelica_metatype tmpMeta5;
  modelica_real tmp6;
  modelica_metatype tmpMeta7;
  modelica_real tmp8;
  modelica_metatype tmpMeta9;
  modelica_real tmp10;
  modelica_metatype tmpMeta11;
  modelica_real tmp12;
  modelica_metatype tmpMeta13;
  modelica_real tmp14;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord tmp15;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord tmp16;
  modelica_metatype tmpMeta17;
  modelica_real tmp18;
  modelica_metatype tmpMeta19;
  modelica_real tmp20;
  modelica_metatype tmpMeta21;
  modelica_real tmp22;
  modelica_metatype tmpMeta23;
  modelica_real tmp24;
  modelica_real _Mx;
  modelica_metatype out_Mx;
  tmp1 = mmc_unbox_real(_Fz);
  tmp2 = mmc_unbox_real(_Fy);
  tmp3 = mmc_unbox_real(_gamma);
  tmpMeta5 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 2)));
  tmp6 = mmc_unbox_real(tmpMeta5);
  tmp4._QSX1 = tmp6;
  tmpMeta7 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 3)));
  tmp8 = mmc_unbox_real(tmpMeta7);
  tmp4._QSX2 = tmp8;
  tmpMeta9 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 4)));
  tmp10 = mmc_unbox_real(tmpMeta9);
  tmp4._QSX3 = tmp10;
  tmpMeta11 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 5)));
  tmp12 = mmc_unbox_real(tmpMeta11);
  tmp4._LMX = tmp12;
  tmpMeta13 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 6)));
  tmp14 = mmc_unbox_real(tmpMeta13);
  tmp4._LVMX = tmp14;tmpMeta17 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 2)));
  tmp18 = mmc_unbox_real(tmpMeta17);
  tmp16._FNOMIN = tmp18;
  tmpMeta19 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 3)));
  tmp20 = mmc_unbox_real(tmpMeta19);
  tmp16._FZMIN = tmp20;
  tmpMeta21 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 4)));
  tmp22 = mmc_unbox_real(tmpMeta21);
  tmp16._FZMAX = tmp22;
  tmpMeta23 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 5)));
  tmp24 = mmc_unbox_real(tmpMeta23);
  tmp16._UNLOADED_RADIUS = tmp24;
  _Mx = omc_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MxCombinedEval(threadData, tmp1, tmp2, tmp3, tmp4, tmp15, tmp16);
  out_Mx = mmc_mk_rcon(_Mx);
  return out_Mx;
}

DLLDirection
modelica_real omc_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MyCombinedEval(threadData_t *threadData, modelica_real _Fz, modelica_real _Fx, modelica_real _Vx, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord _pPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord _pFx, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord _pComb, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord _setup)
{
  modelica_real _My;
  _tailrecursive: OMC_LABEL_UNUSED
  // _My has no default value.
  if((_Fz > 0.001))
  {
    _My = omc_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MyPureEval(threadData, _Fz, _Fx, _Vx, _pPure, _pFx, _setup);
  }
  else
  {
    _My = 0.0;
  }
  _return: OMC_LABEL_UNUSED
  return _My;
}
modelica_metatype boxptr_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MyCombinedEval(threadData_t *threadData, modelica_metatype _Fz, modelica_metatype _Fx, modelica_metatype _Vx, modelica_metatype _pPure, modelica_metatype _pFx, modelica_metatype _pComb, modelica_metatype _setup)
{
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord tmp4;
  modelica_metatype tmpMeta5;
  modelica_real tmp6;
  modelica_metatype tmpMeta7;
  modelica_real tmp8;
  modelica_metatype tmpMeta9;
  modelica_real tmp10;
  modelica_metatype tmpMeta11;
  modelica_real tmp12;
  modelica_metatype tmpMeta13;
  modelica_real tmp14;
  modelica_metatype tmpMeta15;
  modelica_real tmp16;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord tmp17;
  modelica_metatype tmpMeta18;
  modelica_real tmp19;
  modelica_metatype tmpMeta20;
  modelica_real tmp21;
  modelica_metatype tmpMeta22;
  modelica_real tmp23;
  modelica_metatype tmpMeta24;
  modelica_real tmp25;
  modelica_metatype tmpMeta26;
  modelica_real tmp27;
  modelica_metatype tmpMeta28;
  modelica_real tmp29;
  modelica_metatype tmpMeta30;
  modelica_real tmp31;
  modelica_metatype tmpMeta32;
  modelica_real tmp33;
  modelica_metatype tmpMeta34;
  modelica_real tmp35;
  modelica_metatype tmpMeta36;
  modelica_real tmp37;
  modelica_metatype tmpMeta38;
  modelica_real tmp39;
  modelica_metatype tmpMeta40;
  modelica_real tmp41;
  modelica_metatype tmpMeta42;
  modelica_real tmp43;
  modelica_metatype tmpMeta44;
  modelica_real tmp45;
  modelica_metatype tmpMeta46;
  modelica_real tmp47;
  modelica_metatype tmpMeta48;
  modelica_real tmp49;
  modelica_metatype tmpMeta50;
  modelica_real tmp51;
  modelica_metatype tmpMeta52;
  modelica_real tmp53;
  modelica_metatype tmpMeta54;
  modelica_real tmp55;
  modelica_metatype tmpMeta56;
  modelica_real tmp57;
  modelica_metatype tmpMeta58;
  modelica_real tmp59;
  modelica_metatype tmpMeta60;
  modelica_real tmp61;
  modelica_metatype tmpMeta62;
  modelica_real tmp63;
  modelica_metatype tmpMeta64;
  modelica_real tmp65;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord tmp66;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord tmp67;
  modelica_metatype tmpMeta68;
  modelica_real tmp69;
  modelica_metatype tmpMeta70;
  modelica_real tmp71;
  modelica_metatype tmpMeta72;
  modelica_real tmp73;
  modelica_metatype tmpMeta74;
  modelica_real tmp75;
  modelica_real _My;
  modelica_metatype out_My;
  tmp1 = mmc_unbox_real(_Fz);
  tmp2 = mmc_unbox_real(_Fx);
  tmp3 = mmc_unbox_real(_Vx);
  tmpMeta5 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 2)));
  tmp6 = mmc_unbox_real(tmpMeta5);
  tmp4._QSY1 = tmp6;
  tmpMeta7 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 3)));
  tmp8 = mmc_unbox_real(tmpMeta7);
  tmp4._QSY2 = tmp8;
  tmpMeta9 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 4)));
  tmp10 = mmc_unbox_real(tmpMeta9);
  tmp4._QSY3 = tmp10;
  tmpMeta11 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 5)));
  tmp12 = mmc_unbox_real(tmpMeta11);
  tmp4._QSY4 = tmp12;
  tmpMeta13 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 6)));
  tmp14 = mmc_unbox_real(tmpMeta13);
  tmp4._Vref = tmp14;
  tmpMeta15 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 7)));
  tmp16 = mmc_unbox_real(tmpMeta15);
  tmp4._LMY = tmp16;tmpMeta18 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 2)));
  tmp19 = mmc_unbox_real(tmpMeta18);
  tmp17._LGAX = tmp19;
  tmpMeta20 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 3)));
  tmp21 = mmc_unbox_real(tmpMeta20);
  tmp17._LFZO = tmp21;
  tmpMeta22 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 4)));
  tmp23 = mmc_unbox_real(tmpMeta22);
  tmp17._PCX1 = tmp23;
  tmpMeta24 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 5)));
  tmp25 = mmc_unbox_real(tmpMeta24);
  tmp17._PDX1 = tmp25;
  tmpMeta26 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 6)));
  tmp27 = mmc_unbox_real(tmpMeta26);
  tmp17._PDX2 = tmp27;
  tmpMeta28 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 7)));
  tmp29 = mmc_unbox_real(tmpMeta28);
  tmp17._PDX3 = tmp29;
  tmpMeta30 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 8)));
  tmp31 = mmc_unbox_real(tmpMeta30);
  tmp17._PKX1 = tmp31;
  tmpMeta32 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 9)));
  tmp33 = mmc_unbox_real(tmpMeta32);
  tmp17._PKX2 = tmp33;
  tmpMeta34 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 10)));
  tmp35 = mmc_unbox_real(tmpMeta34);
  tmp17._PKX3 = tmp35;
  tmpMeta36 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 11)));
  tmp37 = mmc_unbox_real(tmpMeta36);
  tmp17._PHX1 = tmp37;
  tmpMeta38 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 12)));
  tmp39 = mmc_unbox_real(tmpMeta38);
  tmp17._PHX2 = tmp39;
  tmpMeta40 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 13)));
  tmp41 = mmc_unbox_real(tmpMeta40);
  tmp17._PVX1 = tmp41;
  tmpMeta42 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 14)));
  tmp43 = mmc_unbox_real(tmpMeta42);
  tmp17._PVX2 = tmp43;
  tmpMeta44 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 15)));
  tmp45 = mmc_unbox_real(tmpMeta44);
  tmp17._PEX1 = tmp45;
  tmpMeta46 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 16)));
  tmp47 = mmc_unbox_real(tmpMeta46);
  tmp17._PEX2 = tmp47;
  tmpMeta48 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 17)));
  tmp49 = mmc_unbox_real(tmpMeta48);
  tmp17._PEX3 = tmp49;
  tmpMeta50 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 18)));
  tmp51 = mmc_unbox_real(tmpMeta50);
  tmp17._PEX4 = tmp51;
  tmpMeta52 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 19)));
  tmp53 = mmc_unbox_real(tmpMeta52);
  tmp17._LCX = tmp53;
  tmpMeta54 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 20)));
  tmp55 = mmc_unbox_real(tmpMeta54);
  tmp17._LMUX = tmp55;
  tmpMeta56 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 21)));
  tmp57 = mmc_unbox_real(tmpMeta56);
  tmp17._LKX = tmp57;
  tmpMeta58 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 22)));
  tmp59 = mmc_unbox_real(tmpMeta58);
  tmp17._LHX = tmp59;
  tmpMeta60 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 23)));
  tmp61 = mmc_unbox_real(tmpMeta60);
  tmp17._LVX = tmp61;
  tmpMeta62 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 24)));
  tmp63 = mmc_unbox_real(tmpMeta62);
  tmp17._LEX = tmp63;
  tmpMeta64 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 25)));
  tmp65 = mmc_unbox_real(tmpMeta64);
  tmp17._LXAL = tmp65;tmpMeta68 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 2)));
  tmp69 = mmc_unbox_real(tmpMeta68);
  tmp67._FNOMIN = tmp69;
  tmpMeta70 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 3)));
  tmp71 = mmc_unbox_real(tmpMeta70);
  tmp67._FZMIN = tmp71;
  tmpMeta72 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 4)));
  tmp73 = mmc_unbox_real(tmpMeta72);
  tmp67._FZMAX = tmp73;
  tmpMeta74 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 5)));
  tmp75 = mmc_unbox_real(tmpMeta74);
  tmp67._UNLOADED_RADIUS = tmp75;
  _My = omc_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MyCombinedEval(threadData, tmp1, tmp2, tmp3, tmp4, tmp17, tmp66, tmp67);
  out_My = mmc_mk_rcon(_My);
  return out_My;
}

DLLDirection
modelica_real omc_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MzCombinedEval(threadData_t *threadData, modelica_real _Fz, modelica_real _Fx, modelica_real _Fy, modelica_real _alpha, modelica_real _kappa, modelica_real _gamma, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord _pFy, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord _pFx, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord _pPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord _pComb, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord _setup, modelica_real *out_t, modelica_real *out_s)
{
  modelica_real _Mz;
  modelica_real _t;
  modelica_real _s;
  modelica_real _dfz;
  modelica_real _mu_y;
  modelica_real _D_VySR;
  modelica_real _S_VySR;
  modelica_real _Fy_eff;
  modelica_real _Mz_pure;
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  modelica_real tmp4;
  _tailrecursive: OMC_LABEL_UNUSED
  // _Mz has no default value.
  // _t has no default value.
  // _s has no default value.
  // _dfz has no default value.
  // _mu_y has no default value.
  // _D_VySR has no default value.
  // _S_VySR has no default value.
  // _Fy_eff has no default value.
  // _Mz_pure has no default value.
  if((_Fz > 0.001))
  {
    tmp1 = (_setup._FNOMIN) * (_pFy._LFZO);
    if (tmp1 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "(Fz - setup.FNOMIN * pFy.LFZO) / (setup.FNOMIN * pFy.LFZO)");}
    _dfz = (_Fz - ((_setup._FNOMIN) * (_pFy._LFZO))) / tmp1;

    tmp2 = (_gamma) * (_pFy._LGAY);
    _mu_y = ((_pFy._PDY1 + (_pFy._PDY2) * (_dfz)) * (1.0 - ((_pFy._PDY3) * ((tmp2 * tmp2))))) * (_pFy._LMUY);

    _D_VySR = (((_mu_y) * (_Fz)) * (_pComb._RVY1 + (_pComb._RVY2) * (_dfz) + (_pComb._RVY3) * (_gamma))) * (cos(atan((_pComb._RVY4) * (_alpha))));

    _S_VySR = ((_D_VySR) * (sin((_pComb._RVY5) * (atan((_pComb._RVY6) * (_kappa)))))) * (_pFy._LVYKA);

    _Fy_eff = _Fy - _S_VySR;

    _Mz_pure = omc_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MzPureEval(threadData, _Fz, _Fy_eff, _alpha, _kappa, _gamma, _pFy, _pFx, _pPure, _setup);

    if((fabs(_Fy_eff) > 1e-6))
    {
      tmp3 = _Fy_eff;
      if (tmp3 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "Mz_pure / Fy_eff");}
      _t = (-((_Mz_pure) / tmp3));
    }
    else
    {
      _t = 0.0;
    }

    tmp4 = _setup._FNOMIN;
    if (tmp4 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "Fy / setup.FNOMIN");}
    _s = ((_pComb._SSZ1 + (_pComb._SSZ2) * ((_Fy) / tmp4) + (_pComb._SSZ3 + (_pComb._SSZ4) * (_dfz)) * (_gamma)) * (_setup._UNLOADED_RADIUS)) * (_pComb._LS);

    _Mz = _Mz_pure + (_s) * (_Fx);
  }
  else
  {
    _Mz = 0.0;

    _t = 0.0;

    _s = 0.0;
  }
  _return: OMC_LABEL_UNUSED
  if (out_t) { *out_t = _t; }
  if (out_s) { *out_s = _s; }
  return _Mz;
}
modelica_metatype boxptr_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MzCombinedEval(threadData_t *threadData, modelica_metatype _Fz, modelica_metatype _Fx, modelica_metatype _Fy, modelica_metatype _alpha, modelica_metatype _kappa, modelica_metatype _gamma, modelica_metatype _pFy, modelica_metatype _pFx, modelica_metatype _pPure, modelica_metatype _pComb, modelica_metatype _setup, modelica_metatype *out_t, modelica_metatype *out_s)
{
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  modelica_real tmp4;
  modelica_real tmp5;
  modelica_real tmp6;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord tmp7;
  modelica_metatype tmpMeta8;
  modelica_real tmp9;
  modelica_metatype tmpMeta10;
  modelica_real tmp11;
  modelica_metatype tmpMeta12;
  modelica_real tmp13;
  modelica_metatype tmpMeta14;
  modelica_real tmp15;
  modelica_metatype tmpMeta16;
  modelica_real tmp17;
  modelica_metatype tmpMeta18;
  modelica_real tmp19;
  modelica_metatype tmpMeta20;
  modelica_real tmp21;
  modelica_metatype tmpMeta22;
  modelica_real tmp23;
  modelica_metatype tmpMeta24;
  modelica_real tmp25;
  modelica_metatype tmpMeta26;
  modelica_real tmp27;
  modelica_metatype tmpMeta28;
  modelica_real tmp29;
  modelica_metatype tmpMeta30;
  modelica_real tmp31;
  modelica_metatype tmpMeta32;
  modelica_real tmp33;
  modelica_metatype tmpMeta34;
  modelica_real tmp35;
  modelica_metatype tmpMeta36;
  modelica_real tmp37;
  modelica_metatype tmpMeta38;
  modelica_real tmp39;
  modelica_metatype tmpMeta40;
  modelica_real tmp41;
  modelica_metatype tmpMeta42;
  modelica_real tmp43;
  modelica_metatype tmpMeta44;
  modelica_real tmp45;
  modelica_metatype tmpMeta46;
  modelica_real tmp47;
  modelica_metatype tmpMeta48;
  modelica_real tmp49;
  modelica_metatype tmpMeta50;
  modelica_real tmp51;
  modelica_metatype tmpMeta52;
  modelica_real tmp53;
  modelica_metatype tmpMeta54;
  modelica_real tmp55;
  modelica_metatype tmpMeta56;
  modelica_real tmp57;
  modelica_metatype tmpMeta58;
  modelica_real tmp59;
  modelica_metatype tmpMeta60;
  modelica_real tmp61;
  modelica_metatype tmpMeta62;
  modelica_real tmp63;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord tmp64;
  modelica_metatype tmpMeta65;
  modelica_real tmp66;
  modelica_metatype tmpMeta67;
  modelica_real tmp68;
  modelica_metatype tmpMeta69;
  modelica_real tmp70;
  modelica_metatype tmpMeta71;
  modelica_real tmp72;
  modelica_metatype tmpMeta73;
  modelica_real tmp74;
  modelica_metatype tmpMeta75;
  modelica_real tmp76;
  modelica_metatype tmpMeta77;
  modelica_real tmp78;
  modelica_metatype tmpMeta79;
  modelica_real tmp80;
  modelica_metatype tmpMeta81;
  modelica_real tmp82;
  modelica_metatype tmpMeta83;
  modelica_real tmp84;
  modelica_metatype tmpMeta85;
  modelica_real tmp86;
  modelica_metatype tmpMeta87;
  modelica_real tmp88;
  modelica_metatype tmpMeta89;
  modelica_real tmp90;
  modelica_metatype tmpMeta91;
  modelica_real tmp92;
  modelica_metatype tmpMeta93;
  modelica_real tmp94;
  modelica_metatype tmpMeta95;
  modelica_real tmp96;
  modelica_metatype tmpMeta97;
  modelica_real tmp98;
  modelica_metatype tmpMeta99;
  modelica_real tmp100;
  modelica_metatype tmpMeta101;
  modelica_real tmp102;
  modelica_metatype tmpMeta103;
  modelica_real tmp104;
  modelica_metatype tmpMeta105;
  modelica_real tmp106;
  modelica_metatype tmpMeta107;
  modelica_real tmp108;
  modelica_metatype tmpMeta109;
  modelica_real tmp110;
  modelica_metatype tmpMeta111;
  modelica_real tmp112;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord tmp113;
  modelica_metatype tmpMeta114;
  modelica_real tmp115;
  modelica_metatype tmpMeta116;
  modelica_real tmp117;
  modelica_metatype tmpMeta118;
  modelica_real tmp119;
  modelica_metatype tmpMeta120;
  modelica_real tmp121;
  modelica_metatype tmpMeta122;
  modelica_real tmp123;
  modelica_metatype tmpMeta124;
  modelica_real tmp125;
  modelica_metatype tmpMeta126;
  modelica_real tmp127;
  modelica_metatype tmpMeta128;
  modelica_real tmp129;
  modelica_metatype tmpMeta130;
  modelica_real tmp131;
  modelica_metatype tmpMeta132;
  modelica_real tmp133;
  modelica_metatype tmpMeta134;
  modelica_real tmp135;
  modelica_metatype tmpMeta136;
  modelica_real tmp137;
  modelica_metatype tmpMeta138;
  modelica_real tmp139;
  modelica_metatype tmpMeta140;
  modelica_real tmp141;
  modelica_metatype tmpMeta142;
  modelica_real tmp143;
  modelica_metatype tmpMeta144;
  modelica_real tmp145;
  modelica_metatype tmpMeta146;
  modelica_real tmp147;
  modelica_metatype tmpMeta148;
  modelica_real tmp149;
  modelica_metatype tmpMeta150;
  modelica_real tmp151;
  modelica_metatype tmpMeta152;
  modelica_real tmp153;
  modelica_metatype tmpMeta154;
  modelica_real tmp155;
  modelica_metatype tmpMeta156;
  modelica_real tmp157;
  modelica_metatype tmpMeta158;
  modelica_real tmp159;
  modelica_metatype tmpMeta160;
  modelica_real tmp161;
  modelica_metatype tmpMeta162;
  modelica_real tmp163;
  modelica_metatype tmpMeta164;
  modelica_real tmp165;
  modelica_metatype tmpMeta166;
  modelica_real tmp167;
  modelica_metatype tmpMeta168;
  modelica_real tmp169;
  modelica_metatype tmpMeta170;
  modelica_real tmp171;
  modelica_metatype tmpMeta172;
  modelica_real tmp173;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord tmp174;
  modelica_metatype tmpMeta175;
  modelica_real tmp176;
  modelica_metatype tmpMeta177;
  modelica_real tmp178;
  modelica_metatype tmpMeta179;
  modelica_real tmp180;
  modelica_metatype tmpMeta181;
  modelica_real tmp182;
  modelica_metatype tmpMeta183;
  modelica_real tmp184;
  modelica_metatype tmpMeta185;
  modelica_real tmp186;
  modelica_metatype tmpMeta187;
  modelica_real tmp188;
  modelica_metatype tmpMeta189;
  modelica_real tmp190;
  modelica_metatype tmpMeta191;
  modelica_real tmp192;
  modelica_metatype tmpMeta193;
  modelica_real tmp194;
  modelica_metatype tmpMeta195;
  modelica_real tmp196;
  modelica_metatype tmpMeta197;
  modelica_real tmp198;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord tmp199;
  modelica_metatype tmpMeta200;
  modelica_real tmp201;
  modelica_metatype tmpMeta202;
  modelica_real tmp203;
  modelica_metatype tmpMeta204;
  modelica_real tmp205;
  modelica_metatype tmpMeta206;
  modelica_real tmp207;
  modelica_real _t;
  modelica_real _s;
  modelica_real _Mz;
  modelica_metatype out_Mz;
  tmp1 = mmc_unbox_real(_Fz);
  tmp2 = mmc_unbox_real(_Fx);
  tmp3 = mmc_unbox_real(_Fy);
  tmp4 = mmc_unbox_real(_alpha);
  tmp5 = mmc_unbox_real(_kappa);
  tmp6 = mmc_unbox_real(_gamma);
  tmpMeta8 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 2)));
  tmp9 = mmc_unbox_real(tmpMeta8);
  tmp7._LFZO = tmp9;
  tmpMeta10 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 3)));
  tmp11 = mmc_unbox_real(tmpMeta10);
  tmp7._LGAY = tmp11;
  tmpMeta12 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 4)));
  tmp13 = mmc_unbox_real(tmpMeta12);
  tmp7._PCY1 = tmp13;
  tmpMeta14 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 5)));
  tmp15 = mmc_unbox_real(tmpMeta14);
  tmp7._PDY1 = tmp15;
  tmpMeta16 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 6)));
  tmp17 = mmc_unbox_real(tmpMeta16);
  tmp7._PDY2 = tmp17;
  tmpMeta18 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 7)));
  tmp19 = mmc_unbox_real(tmpMeta18);
  tmp7._PDY3 = tmp19;
  tmpMeta20 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 8)));
  tmp21 = mmc_unbox_real(tmpMeta20);
  tmp7._PKY1 = tmp21;
  tmpMeta22 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 9)));
  tmp23 = mmc_unbox_real(tmpMeta22);
  tmp7._PKY2 = tmp23;
  tmpMeta24 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 10)));
  tmp25 = mmc_unbox_real(tmpMeta24);
  tmp7._PKY3 = tmp25;
  tmpMeta26 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 11)));
  tmp27 = mmc_unbox_real(tmpMeta26);
  tmp7._PHY1 = tmp27;
  tmpMeta28 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 12)));
  tmp29 = mmc_unbox_real(tmpMeta28);
  tmp7._PHY2 = tmp29;
  tmpMeta30 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 13)));
  tmp31 = mmc_unbox_real(tmpMeta30);
  tmp7._PHY3 = tmp31;
  tmpMeta32 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 14)));
  tmp33 = mmc_unbox_real(tmpMeta32);
  tmp7._PVY1 = tmp33;
  tmpMeta34 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 15)));
  tmp35 = mmc_unbox_real(tmpMeta34);
  tmp7._PVY2 = tmp35;
  tmpMeta36 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 16)));
  tmp37 = mmc_unbox_real(tmpMeta36);
  tmp7._PVY3 = tmp37;
  tmpMeta38 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 17)));
  tmp39 = mmc_unbox_real(tmpMeta38);
  tmp7._PVY4 = tmp39;
  tmpMeta40 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 18)));
  tmp41 = mmc_unbox_real(tmpMeta40);
  tmp7._PEY1 = tmp41;
  tmpMeta42 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 19)));
  tmp43 = mmc_unbox_real(tmpMeta42);
  tmp7._PEY2 = tmp43;
  tmpMeta44 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 20)));
  tmp45 = mmc_unbox_real(tmpMeta44);
  tmp7._PEY3 = tmp45;
  tmpMeta46 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 21)));
  tmp47 = mmc_unbox_real(tmpMeta46);
  tmp7._PEY4 = tmp47;
  tmpMeta48 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 22)));
  tmp49 = mmc_unbox_real(tmpMeta48);
  tmp7._LCY = tmp49;
  tmpMeta50 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 23)));
  tmp51 = mmc_unbox_real(tmpMeta50);
  tmp7._LMUY = tmp51;
  tmpMeta52 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 24)));
  tmp53 = mmc_unbox_real(tmpMeta52);
  tmp7._LEY = tmp53;
  tmpMeta54 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 25)));
  tmp55 = mmc_unbox_real(tmpMeta54);
  tmp7._LKY = tmp55;
  tmpMeta56 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 26)));
  tmp57 = mmc_unbox_real(tmpMeta56);
  tmp7._LHY = tmp57;
  tmpMeta58 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 27)));
  tmp59 = mmc_unbox_real(tmpMeta58);
  tmp7._LVY = tmp59;
  tmpMeta60 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 28)));
  tmp61 = mmc_unbox_real(tmpMeta60);
  tmp7._LYKA = tmp61;
  tmpMeta62 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 29)));
  tmp63 = mmc_unbox_real(tmpMeta62);
  tmp7._LVYKA = tmp63;tmpMeta65 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 2)));
  tmp66 = mmc_unbox_real(tmpMeta65);
  tmp64._LGAX = tmp66;
  tmpMeta67 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 3)));
  tmp68 = mmc_unbox_real(tmpMeta67);
  tmp64._LFZO = tmp68;
  tmpMeta69 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 4)));
  tmp70 = mmc_unbox_real(tmpMeta69);
  tmp64._PCX1 = tmp70;
  tmpMeta71 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 5)));
  tmp72 = mmc_unbox_real(tmpMeta71);
  tmp64._PDX1 = tmp72;
  tmpMeta73 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 6)));
  tmp74 = mmc_unbox_real(tmpMeta73);
  tmp64._PDX2 = tmp74;
  tmpMeta75 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 7)));
  tmp76 = mmc_unbox_real(tmpMeta75);
  tmp64._PDX3 = tmp76;
  tmpMeta77 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 8)));
  tmp78 = mmc_unbox_real(tmpMeta77);
  tmp64._PKX1 = tmp78;
  tmpMeta79 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 9)));
  tmp80 = mmc_unbox_real(tmpMeta79);
  tmp64._PKX2 = tmp80;
  tmpMeta81 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 10)));
  tmp82 = mmc_unbox_real(tmpMeta81);
  tmp64._PKX3 = tmp82;
  tmpMeta83 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 11)));
  tmp84 = mmc_unbox_real(tmpMeta83);
  tmp64._PHX1 = tmp84;
  tmpMeta85 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 12)));
  tmp86 = mmc_unbox_real(tmpMeta85);
  tmp64._PHX2 = tmp86;
  tmpMeta87 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 13)));
  tmp88 = mmc_unbox_real(tmpMeta87);
  tmp64._PVX1 = tmp88;
  tmpMeta89 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 14)));
  tmp90 = mmc_unbox_real(tmpMeta89);
  tmp64._PVX2 = tmp90;
  tmpMeta91 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 15)));
  tmp92 = mmc_unbox_real(tmpMeta91);
  tmp64._PEX1 = tmp92;
  tmpMeta93 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 16)));
  tmp94 = mmc_unbox_real(tmpMeta93);
  tmp64._PEX2 = tmp94;
  tmpMeta95 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 17)));
  tmp96 = mmc_unbox_real(tmpMeta95);
  tmp64._PEX3 = tmp96;
  tmpMeta97 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 18)));
  tmp98 = mmc_unbox_real(tmpMeta97);
  tmp64._PEX4 = tmp98;
  tmpMeta99 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 19)));
  tmp100 = mmc_unbox_real(tmpMeta99);
  tmp64._LCX = tmp100;
  tmpMeta101 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 20)));
  tmp102 = mmc_unbox_real(tmpMeta101);
  tmp64._LMUX = tmp102;
  tmpMeta103 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 21)));
  tmp104 = mmc_unbox_real(tmpMeta103);
  tmp64._LKX = tmp104;
  tmpMeta105 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 22)));
  tmp106 = mmc_unbox_real(tmpMeta105);
  tmp64._LHX = tmp106;
  tmpMeta107 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 23)));
  tmp108 = mmc_unbox_real(tmpMeta107);
  tmp64._LVX = tmp108;
  tmpMeta109 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 24)));
  tmp110 = mmc_unbox_real(tmpMeta109);
  tmp64._LEX = tmp110;
  tmpMeta111 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 25)));
  tmp112 = mmc_unbox_real(tmpMeta111);
  tmp64._LXAL = tmp112;tmpMeta114 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 2)));
  tmp115 = mmc_unbox_real(tmpMeta114);
  tmp113._QBZ1 = tmp115;
  tmpMeta116 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 3)));
  tmp117 = mmc_unbox_real(tmpMeta116);
  tmp113._QBZ2 = tmp117;
  tmpMeta118 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 4)));
  tmp119 = mmc_unbox_real(tmpMeta118);
  tmp113._QBZ3 = tmp119;
  tmpMeta120 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 5)));
  tmp121 = mmc_unbox_real(tmpMeta120);
  tmp113._QBZ4 = tmp121;
  tmpMeta122 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 6)));
  tmp123 = mmc_unbox_real(tmpMeta122);
  tmp113._QBZ5 = tmp123;
  tmpMeta124 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 7)));
  tmp125 = mmc_unbox_real(tmpMeta124);
  tmp113._QCZ1 = tmp125;
  tmpMeta126 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 8)));
  tmp127 = mmc_unbox_real(tmpMeta126);
  tmp113._QDZ1 = tmp127;
  tmpMeta128 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 9)));
  tmp129 = mmc_unbox_real(tmpMeta128);
  tmp113._QDZ2 = tmp129;
  tmpMeta130 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 10)));
  tmp131 = mmc_unbox_real(tmpMeta130);
  tmp113._QDZ3 = tmp131;
  tmpMeta132 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 11)));
  tmp133 = mmc_unbox_real(tmpMeta132);
  tmp113._QDZ4 = tmp133;
  tmpMeta134 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 12)));
  tmp135 = mmc_unbox_real(tmpMeta134);
  tmp113._QEZ1 = tmp135;
  tmpMeta136 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 13)));
  tmp137 = mmc_unbox_real(tmpMeta136);
  tmp113._QEZ2 = tmp137;
  tmpMeta138 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 14)));
  tmp139 = mmc_unbox_real(tmpMeta138);
  tmp113._QEZ3 = tmp139;
  tmpMeta140 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 15)));
  tmp141 = mmc_unbox_real(tmpMeta140);
  tmp113._QEZ4 = tmp141;
  tmpMeta142 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 16)));
  tmp143 = mmc_unbox_real(tmpMeta142);
  tmp113._QEZ5 = tmp143;
  tmpMeta144 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 17)));
  tmp145 = mmc_unbox_real(tmpMeta144);
  tmp113._QHZ1 = tmp145;
  tmpMeta146 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 18)));
  tmp147 = mmc_unbox_real(tmpMeta146);
  tmp113._QHZ2 = tmp147;
  tmpMeta148 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 19)));
  tmp149 = mmc_unbox_real(tmpMeta148);
  tmp113._QHZ3 = tmp149;
  tmpMeta150 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 20)));
  tmp151 = mmc_unbox_real(tmpMeta150);
  tmp113._QHZ4 = tmp151;
  tmpMeta152 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 21)));
  tmp153 = mmc_unbox_real(tmpMeta152);
  tmp113._QBZ9 = tmp153;
  tmpMeta154 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 22)));
  tmp155 = mmc_unbox_real(tmpMeta154);
  tmp113._QBZ10 = tmp155;
  tmpMeta156 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 23)));
  tmp157 = mmc_unbox_real(tmpMeta156);
  tmp113._QDZ6 = tmp157;
  tmpMeta158 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 24)));
  tmp159 = mmc_unbox_real(tmpMeta158);
  tmp113._QDZ7 = tmp159;
  tmpMeta160 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 25)));
  tmp161 = mmc_unbox_real(tmpMeta160);
  tmp113._QDZ8 = tmp161;
  tmpMeta162 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 26)));
  tmp163 = mmc_unbox_real(tmpMeta162);
  tmp113._QDZ9 = tmp163;
  tmpMeta164 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 27)));
  tmp165 = mmc_unbox_real(tmpMeta164);
  tmp113._LTR = tmp165;
  tmpMeta166 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 28)));
  tmp167 = mmc_unbox_real(tmpMeta166);
  tmp113._LRES = tmp167;
  tmpMeta168 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 29)));
  tmp169 = mmc_unbox_real(tmpMeta168);
  tmp113._LKY = tmp169;
  tmpMeta170 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 30)));
  tmp171 = mmc_unbox_real(tmpMeta170);
  tmp113._LMUY = tmp171;
  tmpMeta172 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pPure), 31)));
  tmp173 = mmc_unbox_real(tmpMeta172);
  tmp113._LGAZ = tmp173;tmpMeta175 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 2)));
  tmp176 = mmc_unbox_real(tmpMeta175);
  tmp174._SSZ1 = tmp176;
  tmpMeta177 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 3)));
  tmp178 = mmc_unbox_real(tmpMeta177);
  tmp174._SSZ2 = tmp178;
  tmpMeta179 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 4)));
  tmp180 = mmc_unbox_real(tmpMeta179);
  tmp174._SSZ3 = tmp180;
  tmpMeta181 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 5)));
  tmp182 = mmc_unbox_real(tmpMeta181);
  tmp174._SSZ4 = tmp182;
  tmpMeta183 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 6)));
  tmp184 = mmc_unbox_real(tmpMeta183);
  tmp174._RVY1 = tmp184;
  tmpMeta185 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 7)));
  tmp186 = mmc_unbox_real(tmpMeta185);
  tmp174._RVY2 = tmp186;
  tmpMeta187 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 8)));
  tmp188 = mmc_unbox_real(tmpMeta187);
  tmp174._RVY3 = tmp188;
  tmpMeta189 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 9)));
  tmp190 = mmc_unbox_real(tmpMeta189);
  tmp174._RVY4 = tmp190;
  tmpMeta191 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 10)));
  tmp192 = mmc_unbox_real(tmpMeta191);
  tmp174._RVY5 = tmp192;
  tmpMeta193 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 11)));
  tmp194 = mmc_unbox_real(tmpMeta193);
  tmp174._RVY6 = tmp194;
  tmpMeta195 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 12)));
  tmp196 = mmc_unbox_real(tmpMeta195);
  tmp174._LS = tmp196;
  tmpMeta197 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pComb), 13)));
  tmp198 = mmc_unbox_real(tmpMeta197);
  tmp174._LVYKA = tmp198;tmpMeta200 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 2)));
  tmp201 = mmc_unbox_real(tmpMeta200);
  tmp199._FNOMIN = tmp201;
  tmpMeta202 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 3)));
  tmp203 = mmc_unbox_real(tmpMeta202);
  tmp199._FZMIN = tmp203;
  tmpMeta204 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 4)));
  tmp205 = mmc_unbox_real(tmpMeta204);
  tmp199._FZMAX = tmp205;
  tmpMeta206 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 5)));
  tmp207 = mmc_unbox_real(tmpMeta206);
  tmp199._UNLOADED_RADIUS = tmp207;
  _Mz = omc_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MzCombinedEval(threadData, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp64, tmp113, tmp174, tmp199, &_t, &_s);
  out_Mz = mmc_mk_rcon(_Mz);
  if (out_t) { *out_t = mmc_mk_rcon(_t); }
  if (out_s) { *out_s = mmc_mk_rcon(_s); }
  return out_Mz;
}

DLLDirection
modelica_real omc_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_FxPureEval(threadData_t *threadData, modelica_real _Fz, modelica_real _kappa, modelica_real _gamma, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord _p, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord _setup)
{
  modelica_real _Fx;
  modelica_real _IA_x;
  modelica_real _dfz;
  modelica_real _mu_x;
  modelica_real _C;
  modelica_real _D;
  modelica_real _K;
  modelica_real _B;
  modelica_real _Sh;
  modelica_real _Sv;
  modelica_real _SR_x;
  modelica_real _E;
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  modelica_real tmp4;
  _tailrecursive: OMC_LABEL_UNUSED
  // _Fx has no default value.
  // _IA_x has no default value.
  // _dfz has no default value.
  // _mu_x has no default value.
  // _C has no default value.
  // _D has no default value.
  // _K has no default value.
  // _B has no default value.
  // _Sh has no default value.
  // _Sv has no default value.
  // _SR_x has no default value.
  // _E has no default value.
  if((_Fz > 0.001))
  {
    _IA_x = (_gamma) * (_p._LGAX);

    tmp1 = (_setup._FNOMIN) * (_p._LFZO);
    if (tmp1 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "(Fz - setup.FNOMIN * p.LFZO) / (setup.FNOMIN * p.LFZO)");}
    _dfz = (_Fz - ((_setup._FNOMIN) * (_p._LFZO))) / tmp1;

    tmp2 = _IA_x;
    _mu_x = ((_p._PDX1 + (_p._PDX2) * (_dfz)) * (1.0 - ((_p._PDX3) * ((tmp2 * tmp2))))) * (_p._LMUX);

    _C = (_p._PCX1) * (_p._LCX);

    _D = (_mu_x) * (_Fz);

    _K = (((_Fz) * (_p._PKX1 + (_p._PKX2) * (_dfz))) * (exp((_p._PKX3) * (_dfz)))) * (_p._LKX);

    tmp3 = (_C) * (_D) + 1e-8;
    if (tmp3 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "K / (C * D + 1e-8)");}
    _B = (_K) / tmp3;

    _Sh = (_p._PHX1 + (_p._PHX2) * (_dfz)) * (_p._LHX);

    _Sv = (((_Fz) * (_p._PVX1 + (_p._PVX2) * (_dfz))) * (_p._LVX)) * (_p._LMUX);

    _SR_x = _kappa + _Sh;

    tmp4 = _dfz;
    _E = ((_p._PEX1 + (_p._PEX2) * (_dfz) + (_p._PEX3) * ((tmp4 * tmp4))) * (1.0 - ((_p._PEX4) * (((modelica_real)sign(_SR_x)))))) * (_p._LEX);

    _E = fmin(_E,1.0);

    _Fx = (_D) * (sin((_C) * (atan((_B) * (_SR_x) - ((_E) * ((_B) * (_SR_x) - atan((_B) * (_SR_x)))))))) + _Sv;
  }
  else
  {
    _Fx = 0.0;
  }
  _return: OMC_LABEL_UNUSED
  return _Fx;
}
modelica_metatype boxptr_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_FxPureEval(threadData_t *threadData, modelica_metatype _Fz, modelica_metatype _kappa, modelica_metatype _gamma, modelica_metatype _p, modelica_metatype _setup)
{
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord tmp4;
  modelica_metatype tmpMeta5;
  modelica_real tmp6;
  modelica_metatype tmpMeta7;
  modelica_real tmp8;
  modelica_metatype tmpMeta9;
  modelica_real tmp10;
  modelica_metatype tmpMeta11;
  modelica_real tmp12;
  modelica_metatype tmpMeta13;
  modelica_real tmp14;
  modelica_metatype tmpMeta15;
  modelica_real tmp16;
  modelica_metatype tmpMeta17;
  modelica_real tmp18;
  modelica_metatype tmpMeta19;
  modelica_real tmp20;
  modelica_metatype tmpMeta21;
  modelica_real tmp22;
  modelica_metatype tmpMeta23;
  modelica_real tmp24;
  modelica_metatype tmpMeta25;
  modelica_real tmp26;
  modelica_metatype tmpMeta27;
  modelica_real tmp28;
  modelica_metatype tmpMeta29;
  modelica_real tmp30;
  modelica_metatype tmpMeta31;
  modelica_real tmp32;
  modelica_metatype tmpMeta33;
  modelica_real tmp34;
  modelica_metatype tmpMeta35;
  modelica_real tmp36;
  modelica_metatype tmpMeta37;
  modelica_real tmp38;
  modelica_metatype tmpMeta39;
  modelica_real tmp40;
  modelica_metatype tmpMeta41;
  modelica_real tmp42;
  modelica_metatype tmpMeta43;
  modelica_real tmp44;
  modelica_metatype tmpMeta45;
  modelica_real tmp46;
  modelica_metatype tmpMeta47;
  modelica_real tmp48;
  modelica_metatype tmpMeta49;
  modelica_real tmp50;
  modelica_metatype tmpMeta51;
  modelica_real tmp52;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord tmp53;
  modelica_metatype tmpMeta54;
  modelica_real tmp55;
  modelica_metatype tmpMeta56;
  modelica_real tmp57;
  modelica_metatype tmpMeta58;
  modelica_real tmp59;
  modelica_metatype tmpMeta60;
  modelica_real tmp61;
  modelica_real _Fx;
  modelica_metatype out_Fx;
  tmp1 = mmc_unbox_real(_Fz);
  tmp2 = mmc_unbox_real(_kappa);
  tmp3 = mmc_unbox_real(_gamma);
  tmpMeta5 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 2)));
  tmp6 = mmc_unbox_real(tmpMeta5);
  tmp4._LGAX = tmp6;
  tmpMeta7 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 3)));
  tmp8 = mmc_unbox_real(tmpMeta7);
  tmp4._LFZO = tmp8;
  tmpMeta9 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 4)));
  tmp10 = mmc_unbox_real(tmpMeta9);
  tmp4._PCX1 = tmp10;
  tmpMeta11 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 5)));
  tmp12 = mmc_unbox_real(tmpMeta11);
  tmp4._PDX1 = tmp12;
  tmpMeta13 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 6)));
  tmp14 = mmc_unbox_real(tmpMeta13);
  tmp4._PDX2 = tmp14;
  tmpMeta15 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 7)));
  tmp16 = mmc_unbox_real(tmpMeta15);
  tmp4._PDX3 = tmp16;
  tmpMeta17 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 8)));
  tmp18 = mmc_unbox_real(tmpMeta17);
  tmp4._PKX1 = tmp18;
  tmpMeta19 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 9)));
  tmp20 = mmc_unbox_real(tmpMeta19);
  tmp4._PKX2 = tmp20;
  tmpMeta21 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 10)));
  tmp22 = mmc_unbox_real(tmpMeta21);
  tmp4._PKX3 = tmp22;
  tmpMeta23 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 11)));
  tmp24 = mmc_unbox_real(tmpMeta23);
  tmp4._PHX1 = tmp24;
  tmpMeta25 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 12)));
  tmp26 = mmc_unbox_real(tmpMeta25);
  tmp4._PHX2 = tmp26;
  tmpMeta27 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 13)));
  tmp28 = mmc_unbox_real(tmpMeta27);
  tmp4._PVX1 = tmp28;
  tmpMeta29 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 14)));
  tmp30 = mmc_unbox_real(tmpMeta29);
  tmp4._PVX2 = tmp30;
  tmpMeta31 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 15)));
  tmp32 = mmc_unbox_real(tmpMeta31);
  tmp4._PEX1 = tmp32;
  tmpMeta33 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 16)));
  tmp34 = mmc_unbox_real(tmpMeta33);
  tmp4._PEX2 = tmp34;
  tmpMeta35 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 17)));
  tmp36 = mmc_unbox_real(tmpMeta35);
  tmp4._PEX3 = tmp36;
  tmpMeta37 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 18)));
  tmp38 = mmc_unbox_real(tmpMeta37);
  tmp4._PEX4 = tmp38;
  tmpMeta39 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 19)));
  tmp40 = mmc_unbox_real(tmpMeta39);
  tmp4._LCX = tmp40;
  tmpMeta41 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 20)));
  tmp42 = mmc_unbox_real(tmpMeta41);
  tmp4._LMUX = tmp42;
  tmpMeta43 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 21)));
  tmp44 = mmc_unbox_real(tmpMeta43);
  tmp4._LKX = tmp44;
  tmpMeta45 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 22)));
  tmp46 = mmc_unbox_real(tmpMeta45);
  tmp4._LHX = tmp46;
  tmpMeta47 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 23)));
  tmp48 = mmc_unbox_real(tmpMeta47);
  tmp4._LVX = tmp48;
  tmpMeta49 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 24)));
  tmp50 = mmc_unbox_real(tmpMeta49);
  tmp4._LEX = tmp50;
  tmpMeta51 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 25)));
  tmp52 = mmc_unbox_real(tmpMeta51);
  tmp4._LXAL = tmp52;tmpMeta54 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 2)));
  tmp55 = mmc_unbox_real(tmpMeta54);
  tmp53._FNOMIN = tmp55;
  tmpMeta56 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 3)));
  tmp57 = mmc_unbox_real(tmpMeta56);
  tmp53._FZMIN = tmp57;
  tmpMeta58 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 4)));
  tmp59 = mmc_unbox_real(tmpMeta58);
  tmp53._FZMAX = tmp59;
  tmpMeta60 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 5)));
  tmp61 = mmc_unbox_real(tmpMeta60);
  tmp53._UNLOADED_RADIUS = tmp61;
  _Fx = omc_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_FxPureEval(threadData, tmp1, tmp2, tmp3, tmp4, tmp53);
  out_Fx = mmc_mk_rcon(_Fx);
  return out_Fx;
}

DLLDirection
modelica_real omc_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_FyPureEval(threadData_t *threadData, modelica_real _Fz, modelica_real _alpha, modelica_real _gamma, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord _p, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord _setup)
{
  modelica_real _Fy;
  modelica_real _IA_y;
  modelica_real _dfz;
  modelica_real _mu_y;
  modelica_real _C;
  modelica_real _D;
  modelica_real _K;
  modelica_real _B;
  modelica_real _Sh;
  modelica_real _Sv;
  modelica_real _SA;
  modelica_real _E;
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  modelica_real tmp4;
  _tailrecursive: OMC_LABEL_UNUSED
  // _Fy has no default value.
  // _IA_y has no default value.
  // _dfz has no default value.
  // _mu_y has no default value.
  // _C has no default value.
  // _D has no default value.
  // _K has no default value.
  // _B has no default value.
  // _Sh has no default value.
  // _Sv has no default value.
  // _SA has no default value.
  // _E has no default value.
  if((_Fz > 0.001))
  {
    _IA_y = (_gamma) * (_p._LGAY);

    tmp1 = (_setup._FNOMIN) * (_p._LFZO);
    if (tmp1 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "(Fz - setup.FNOMIN * p.LFZO) / (setup.FNOMIN * p.LFZO)");}
    _dfz = (_Fz - ((_setup._FNOMIN) * (_p._LFZO))) / tmp1;

    tmp2 = _IA_y;
    _mu_y = ((_p._PDY1 + (_p._PDY2) * (_dfz)) * (1.0 - ((_p._PDY3) * ((tmp2 * tmp2))))) * (_p._LMUY);

    _C = (_p._PCY1) * (_p._LCY);

    _D = (_mu_y) * (_Fz);

    tmp3 = ((_p._PKY2) * (_setup._FNOMIN)) * (_p._LFZO);
    if (tmp3 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "Fz / (p.PKY2 * setup.FNOMIN * p.LFZO)");}
    _K = (((((_p._PKY1) * (_setup._FNOMIN)) * (sin((2.0) * (atan((_Fz) / tmp3))))) * (1.0 - ((_p._PKY3) * (fabs(_IA_y))))) * (_p._LFZO)) * (_p._LKY);

    tmp4 = (_C) * (_D) + 1e-8;
    if (tmp4 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "K / (C * D + 1e-8)");}
    _B = (_K) / tmp4;

    _Sh = (_p._PHY1 + (_p._PHY2) * (_dfz)) * (_p._LHY) + (_p._PHY3) * (_IA_y);

    _Sv = ((_Fz) * ((_p._PVY1 + (_p._PVY2) * (_dfz)) * (_p._LVY) + (_p._PVY3 + (_p._PVY4) * (_dfz)) * (_IA_y))) * (_p._LMUY);

    _SA = _alpha + _Sh;

    _E = ((_p._PEY1 + (_p._PEY2) * (_dfz)) * (1.0 - ((_p._PEY3 + (_p._PEY4) * (_IA_y)) * (((modelica_real)sign(_SA)))))) * (_p._LEY);

    _E = fmin(_E,1.0);

    _Fy = (_D) * (sin((_C) * (atan((_B) * (_SA) - ((_E) * ((_B) * (_SA) - atan((_B) * (_SA)))))))) + _Sv;
  }
  else
  {
    _Fy = 0.0;
  }
  _return: OMC_LABEL_UNUSED
  return _Fy;
}
modelica_metatype boxptr_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_FyPureEval(threadData_t *threadData, modelica_metatype _Fz, modelica_metatype _alpha, modelica_metatype _gamma, modelica_metatype _p, modelica_metatype _setup)
{
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord tmp4;
  modelica_metatype tmpMeta5;
  modelica_real tmp6;
  modelica_metatype tmpMeta7;
  modelica_real tmp8;
  modelica_metatype tmpMeta9;
  modelica_real tmp10;
  modelica_metatype tmpMeta11;
  modelica_real tmp12;
  modelica_metatype tmpMeta13;
  modelica_real tmp14;
  modelica_metatype tmpMeta15;
  modelica_real tmp16;
  modelica_metatype tmpMeta17;
  modelica_real tmp18;
  modelica_metatype tmpMeta19;
  modelica_real tmp20;
  modelica_metatype tmpMeta21;
  modelica_real tmp22;
  modelica_metatype tmpMeta23;
  modelica_real tmp24;
  modelica_metatype tmpMeta25;
  modelica_real tmp26;
  modelica_metatype tmpMeta27;
  modelica_real tmp28;
  modelica_metatype tmpMeta29;
  modelica_real tmp30;
  modelica_metatype tmpMeta31;
  modelica_real tmp32;
  modelica_metatype tmpMeta33;
  modelica_real tmp34;
  modelica_metatype tmpMeta35;
  modelica_real tmp36;
  modelica_metatype tmpMeta37;
  modelica_real tmp38;
  modelica_metatype tmpMeta39;
  modelica_real tmp40;
  modelica_metatype tmpMeta41;
  modelica_real tmp42;
  modelica_metatype tmpMeta43;
  modelica_real tmp44;
  modelica_metatype tmpMeta45;
  modelica_real tmp46;
  modelica_metatype tmpMeta47;
  modelica_real tmp48;
  modelica_metatype tmpMeta49;
  modelica_real tmp50;
  modelica_metatype tmpMeta51;
  modelica_real tmp52;
  modelica_metatype tmpMeta53;
  modelica_real tmp54;
  modelica_metatype tmpMeta55;
  modelica_real tmp56;
  modelica_metatype tmpMeta57;
  modelica_real tmp58;
  modelica_metatype tmpMeta59;
  modelica_real tmp60;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord tmp61;
  modelica_metatype tmpMeta62;
  modelica_real tmp63;
  modelica_metatype tmpMeta64;
  modelica_real tmp65;
  modelica_metatype tmpMeta66;
  modelica_real tmp67;
  modelica_metatype tmpMeta68;
  modelica_real tmp69;
  modelica_real _Fy;
  modelica_metatype out_Fy;
  tmp1 = mmc_unbox_real(_Fz);
  tmp2 = mmc_unbox_real(_alpha);
  tmp3 = mmc_unbox_real(_gamma);
  tmpMeta5 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 2)));
  tmp6 = mmc_unbox_real(tmpMeta5);
  tmp4._LFZO = tmp6;
  tmpMeta7 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 3)));
  tmp8 = mmc_unbox_real(tmpMeta7);
  tmp4._LGAY = tmp8;
  tmpMeta9 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 4)));
  tmp10 = mmc_unbox_real(tmpMeta9);
  tmp4._PCY1 = tmp10;
  tmpMeta11 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 5)));
  tmp12 = mmc_unbox_real(tmpMeta11);
  tmp4._PDY1 = tmp12;
  tmpMeta13 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 6)));
  tmp14 = mmc_unbox_real(tmpMeta13);
  tmp4._PDY2 = tmp14;
  tmpMeta15 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 7)));
  tmp16 = mmc_unbox_real(tmpMeta15);
  tmp4._PDY3 = tmp16;
  tmpMeta17 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 8)));
  tmp18 = mmc_unbox_real(tmpMeta17);
  tmp4._PKY1 = tmp18;
  tmpMeta19 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 9)));
  tmp20 = mmc_unbox_real(tmpMeta19);
  tmp4._PKY2 = tmp20;
  tmpMeta21 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 10)));
  tmp22 = mmc_unbox_real(tmpMeta21);
  tmp4._PKY3 = tmp22;
  tmpMeta23 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 11)));
  tmp24 = mmc_unbox_real(tmpMeta23);
  tmp4._PHY1 = tmp24;
  tmpMeta25 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 12)));
  tmp26 = mmc_unbox_real(tmpMeta25);
  tmp4._PHY2 = tmp26;
  tmpMeta27 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 13)));
  tmp28 = mmc_unbox_real(tmpMeta27);
  tmp4._PHY3 = tmp28;
  tmpMeta29 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 14)));
  tmp30 = mmc_unbox_real(tmpMeta29);
  tmp4._PVY1 = tmp30;
  tmpMeta31 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 15)));
  tmp32 = mmc_unbox_real(tmpMeta31);
  tmp4._PVY2 = tmp32;
  tmpMeta33 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 16)));
  tmp34 = mmc_unbox_real(tmpMeta33);
  tmp4._PVY3 = tmp34;
  tmpMeta35 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 17)));
  tmp36 = mmc_unbox_real(tmpMeta35);
  tmp4._PVY4 = tmp36;
  tmpMeta37 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 18)));
  tmp38 = mmc_unbox_real(tmpMeta37);
  tmp4._PEY1 = tmp38;
  tmpMeta39 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 19)));
  tmp40 = mmc_unbox_real(tmpMeta39);
  tmp4._PEY2 = tmp40;
  tmpMeta41 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 20)));
  tmp42 = mmc_unbox_real(tmpMeta41);
  tmp4._PEY3 = tmp42;
  tmpMeta43 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 21)));
  tmp44 = mmc_unbox_real(tmpMeta43);
  tmp4._PEY4 = tmp44;
  tmpMeta45 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 22)));
  tmp46 = mmc_unbox_real(tmpMeta45);
  tmp4._LCY = tmp46;
  tmpMeta47 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 23)));
  tmp48 = mmc_unbox_real(tmpMeta47);
  tmp4._LMUY = tmp48;
  tmpMeta49 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 24)));
  tmp50 = mmc_unbox_real(tmpMeta49);
  tmp4._LEY = tmp50;
  tmpMeta51 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 25)));
  tmp52 = mmc_unbox_real(tmpMeta51);
  tmp4._LKY = tmp52;
  tmpMeta53 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 26)));
  tmp54 = mmc_unbox_real(tmpMeta53);
  tmp4._LHY = tmp54;
  tmpMeta55 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 27)));
  tmp56 = mmc_unbox_real(tmpMeta55);
  tmp4._LVY = tmp56;
  tmpMeta57 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 28)));
  tmp58 = mmc_unbox_real(tmpMeta57);
  tmp4._LYKA = tmp58;
  tmpMeta59 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 29)));
  tmp60 = mmc_unbox_real(tmpMeta59);
  tmp4._LVYKA = tmp60;tmpMeta62 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 2)));
  tmp63 = mmc_unbox_real(tmpMeta62);
  tmp61._FNOMIN = tmp63;
  tmpMeta64 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 3)));
  tmp65 = mmc_unbox_real(tmpMeta64);
  tmp61._FZMIN = tmp65;
  tmpMeta66 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 4)));
  tmp67 = mmc_unbox_real(tmpMeta66);
  tmp61._FZMAX = tmp67;
  tmpMeta68 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 5)));
  tmp69 = mmc_unbox_real(tmpMeta68);
  tmp61._UNLOADED_RADIUS = tmp69;
  _Fy = omc_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_FyPureEval(threadData, tmp1, tmp2, tmp3, tmp4, tmp61);
  out_Fy = mmc_mk_rcon(_Fy);
  return out_Fy;
}

DLLDirection
modelica_real omc_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MxPureEval(threadData_t *threadData, modelica_real _Fz, modelica_real _Fy, modelica_real _gamma, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord _p, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord _setup)
{
  modelica_real _Mx;
  modelica_real tmp1;
  _tailrecursive: OMC_LABEL_UNUSED
  // _Mx has no default value.
  if((_Fz > 0.001))
  {
    tmp1 = _setup._FNOMIN;
    if (tmp1 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "p.QSX3 * Fy / setup.FNOMIN");}
    _Mx = ((_setup._UNLOADED_RADIUS) * (_Fz)) * ((_p._QSX1) * (_p._LVMX) + (((_p._QSX3) * (_Fy)) / tmp1 - ((_p._QSX2) * (_gamma))) * (_p._LMX));
  }
  else
  {
    _Mx = 0.0;
  }
  _return: OMC_LABEL_UNUSED
  return _Mx;
}
modelica_metatype boxptr_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MxPureEval(threadData_t *threadData, modelica_metatype _Fz, modelica_metatype _Fy, modelica_metatype _gamma, modelica_metatype _p, modelica_metatype _setup)
{
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord tmp4;
  modelica_metatype tmpMeta5;
  modelica_real tmp6;
  modelica_metatype tmpMeta7;
  modelica_real tmp8;
  modelica_metatype tmpMeta9;
  modelica_real tmp10;
  modelica_metatype tmpMeta11;
  modelica_real tmp12;
  modelica_metatype tmpMeta13;
  modelica_real tmp14;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord tmp15;
  modelica_metatype tmpMeta16;
  modelica_real tmp17;
  modelica_metatype tmpMeta18;
  modelica_real tmp19;
  modelica_metatype tmpMeta20;
  modelica_real tmp21;
  modelica_metatype tmpMeta22;
  modelica_real tmp23;
  modelica_real _Mx;
  modelica_metatype out_Mx;
  tmp1 = mmc_unbox_real(_Fz);
  tmp2 = mmc_unbox_real(_Fy);
  tmp3 = mmc_unbox_real(_gamma);
  tmpMeta5 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 2)));
  tmp6 = mmc_unbox_real(tmpMeta5);
  tmp4._QSX1 = tmp6;
  tmpMeta7 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 3)));
  tmp8 = mmc_unbox_real(tmpMeta7);
  tmp4._QSX2 = tmp8;
  tmpMeta9 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 4)));
  tmp10 = mmc_unbox_real(tmpMeta9);
  tmp4._QSX3 = tmp10;
  tmpMeta11 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 5)));
  tmp12 = mmc_unbox_real(tmpMeta11);
  tmp4._LMX = tmp12;
  tmpMeta13 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 6)));
  tmp14 = mmc_unbox_real(tmpMeta13);
  tmp4._LVMX = tmp14;tmpMeta16 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 2)));
  tmp17 = mmc_unbox_real(tmpMeta16);
  tmp15._FNOMIN = tmp17;
  tmpMeta18 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 3)));
  tmp19 = mmc_unbox_real(tmpMeta18);
  tmp15._FZMIN = tmp19;
  tmpMeta20 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 4)));
  tmp21 = mmc_unbox_real(tmpMeta20);
  tmp15._FZMAX = tmp21;
  tmpMeta22 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 5)));
  tmp23 = mmc_unbox_real(tmpMeta22);
  tmp15._UNLOADED_RADIUS = tmp23;
  _Mx = omc_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MxPureEval(threadData, tmp1, tmp2, tmp3, tmp4, tmp15);
  out_Mx = mmc_mk_rcon(_Mx);
  return out_Mx;
}

DLLDirection
modelica_real omc_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MyPureEval(threadData_t *threadData, modelica_real _Fz, modelica_real _Fx, modelica_real _Vx, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord _p, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord _pFx, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord _setup)
{
  modelica_real _My;
  modelica_real _eps;
  modelica_real _Vx_n;
  modelica_real _dfz;
  modelica_real _K_x;
  modelica_real _S_Hx;
  modelica_real _S_Vx;
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  modelica_real tmp4;
  _tailrecursive: OMC_LABEL_UNUSED
  // _My has no default value.
  _eps = 1e-8;
  // _Vx_n has no default value.
  // _dfz has no default value.
  // _K_x has no default value.
  // _S_Hx has no default value.
  // _S_Vx has no default value.
  if((_Fz > 0.001))
  {
    if(((fabs(_p._QSY1) <= _eps) && (fabs(_p._QSY2) <= _eps)))
    {
      tmp1 = (_setup._FNOMIN) * (_pFx._LFZO);
      if (tmp1 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "(Fz - setup.FNOMIN * pFx.LFZO) / (setup.FNOMIN * pFx.LFZO)");}
      _dfz = (_Fz - ((_setup._FNOMIN) * (_pFx._LFZO))) / tmp1;

      _K_x = (((_Fz) * (_pFx._PKX1 + (_pFx._PKX2) * (_dfz))) * (exp((_pFx._PKX3) * (_dfz)))) * (_pFx._LKX);

      _S_Hx = (_pFx._PHX1 + (_pFx._PHX2) * (_dfz)) * (_pFx._LHX);

      _S_Vx = (((_Fz) * (_pFx._PVX1 + (_pFx._PVX2) * (_dfz))) * (_pFx._LVX)) * (_pFx._LMUX);

      _My = (_setup._UNLOADED_RADIUS) * (_S_Vx + (_K_x) * (_S_Hx));
    }
    else
    {
      tmp2 = fmax(fabs(_p._Vref),_eps);
      if (tmp2 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "Vx / max(abs(p.Vref), eps)");}
      _Vx_n = (_Vx) / tmp2;

      tmp3 = _setup._FNOMIN;
      if (tmp3 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "Fx / setup.FNOMIN");}
      tmp4 = _Vx_n;
      tmp4 *= tmp4;
      _My = (((_setup._UNLOADED_RADIUS) * (_Fz)) * (_p._QSY1 + (_p._QSY2) * ((_Fx) / tmp3) + (_p._QSY3) * (fabs(_Vx_n)) + (_p._QSY4) * ((tmp4 * tmp4)))) * (_p._LMY);
    }
  }
  else
  {
    _My = 0.0;
  }
  _return: OMC_LABEL_UNUSED
  return _My;
}
modelica_metatype boxptr_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MyPureEval(threadData_t *threadData, modelica_metatype _Fz, modelica_metatype _Fx, modelica_metatype _Vx, modelica_metatype _p, modelica_metatype _pFx, modelica_metatype _setup)
{
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord tmp4;
  modelica_metatype tmpMeta5;
  modelica_real tmp6;
  modelica_metatype tmpMeta7;
  modelica_real tmp8;
  modelica_metatype tmpMeta9;
  modelica_real tmp10;
  modelica_metatype tmpMeta11;
  modelica_real tmp12;
  modelica_metatype tmpMeta13;
  modelica_real tmp14;
  modelica_metatype tmpMeta15;
  modelica_real tmp16;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord tmp17;
  modelica_metatype tmpMeta18;
  modelica_real tmp19;
  modelica_metatype tmpMeta20;
  modelica_real tmp21;
  modelica_metatype tmpMeta22;
  modelica_real tmp23;
  modelica_metatype tmpMeta24;
  modelica_real tmp25;
  modelica_metatype tmpMeta26;
  modelica_real tmp27;
  modelica_metatype tmpMeta28;
  modelica_real tmp29;
  modelica_metatype tmpMeta30;
  modelica_real tmp31;
  modelica_metatype tmpMeta32;
  modelica_real tmp33;
  modelica_metatype tmpMeta34;
  modelica_real tmp35;
  modelica_metatype tmpMeta36;
  modelica_real tmp37;
  modelica_metatype tmpMeta38;
  modelica_real tmp39;
  modelica_metatype tmpMeta40;
  modelica_real tmp41;
  modelica_metatype tmpMeta42;
  modelica_real tmp43;
  modelica_metatype tmpMeta44;
  modelica_real tmp45;
  modelica_metatype tmpMeta46;
  modelica_real tmp47;
  modelica_metatype tmpMeta48;
  modelica_real tmp49;
  modelica_metatype tmpMeta50;
  modelica_real tmp51;
  modelica_metatype tmpMeta52;
  modelica_real tmp53;
  modelica_metatype tmpMeta54;
  modelica_real tmp55;
  modelica_metatype tmpMeta56;
  modelica_real tmp57;
  modelica_metatype tmpMeta58;
  modelica_real tmp59;
  modelica_metatype tmpMeta60;
  modelica_real tmp61;
  modelica_metatype tmpMeta62;
  modelica_real tmp63;
  modelica_metatype tmpMeta64;
  modelica_real tmp65;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord tmp66;
  modelica_metatype tmpMeta67;
  modelica_real tmp68;
  modelica_metatype tmpMeta69;
  modelica_real tmp70;
  modelica_metatype tmpMeta71;
  modelica_real tmp72;
  modelica_metatype tmpMeta73;
  modelica_real tmp74;
  modelica_real _My;
  modelica_metatype out_My;
  tmp1 = mmc_unbox_real(_Fz);
  tmp2 = mmc_unbox_real(_Fx);
  tmp3 = mmc_unbox_real(_Vx);
  tmpMeta5 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 2)));
  tmp6 = mmc_unbox_real(tmpMeta5);
  tmp4._QSY1 = tmp6;
  tmpMeta7 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 3)));
  tmp8 = mmc_unbox_real(tmpMeta7);
  tmp4._QSY2 = tmp8;
  tmpMeta9 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 4)));
  tmp10 = mmc_unbox_real(tmpMeta9);
  tmp4._QSY3 = tmp10;
  tmpMeta11 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 5)));
  tmp12 = mmc_unbox_real(tmpMeta11);
  tmp4._QSY4 = tmp12;
  tmpMeta13 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 6)));
  tmp14 = mmc_unbox_real(tmpMeta13);
  tmp4._Vref = tmp14;
  tmpMeta15 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 7)));
  tmp16 = mmc_unbox_real(tmpMeta15);
  tmp4._LMY = tmp16;tmpMeta18 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 2)));
  tmp19 = mmc_unbox_real(tmpMeta18);
  tmp17._LGAX = tmp19;
  tmpMeta20 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 3)));
  tmp21 = mmc_unbox_real(tmpMeta20);
  tmp17._LFZO = tmp21;
  tmpMeta22 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 4)));
  tmp23 = mmc_unbox_real(tmpMeta22);
  tmp17._PCX1 = tmp23;
  tmpMeta24 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 5)));
  tmp25 = mmc_unbox_real(tmpMeta24);
  tmp17._PDX1 = tmp25;
  tmpMeta26 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 6)));
  tmp27 = mmc_unbox_real(tmpMeta26);
  tmp17._PDX2 = tmp27;
  tmpMeta28 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 7)));
  tmp29 = mmc_unbox_real(tmpMeta28);
  tmp17._PDX3 = tmp29;
  tmpMeta30 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 8)));
  tmp31 = mmc_unbox_real(tmpMeta30);
  tmp17._PKX1 = tmp31;
  tmpMeta32 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 9)));
  tmp33 = mmc_unbox_real(tmpMeta32);
  tmp17._PKX2 = tmp33;
  tmpMeta34 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 10)));
  tmp35 = mmc_unbox_real(tmpMeta34);
  tmp17._PKX3 = tmp35;
  tmpMeta36 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 11)));
  tmp37 = mmc_unbox_real(tmpMeta36);
  tmp17._PHX1 = tmp37;
  tmpMeta38 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 12)));
  tmp39 = mmc_unbox_real(tmpMeta38);
  tmp17._PHX2 = tmp39;
  tmpMeta40 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 13)));
  tmp41 = mmc_unbox_real(tmpMeta40);
  tmp17._PVX1 = tmp41;
  tmpMeta42 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 14)));
  tmp43 = mmc_unbox_real(tmpMeta42);
  tmp17._PVX2 = tmp43;
  tmpMeta44 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 15)));
  tmp45 = mmc_unbox_real(tmpMeta44);
  tmp17._PEX1 = tmp45;
  tmpMeta46 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 16)));
  tmp47 = mmc_unbox_real(tmpMeta46);
  tmp17._PEX2 = tmp47;
  tmpMeta48 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 17)));
  tmp49 = mmc_unbox_real(tmpMeta48);
  tmp17._PEX3 = tmp49;
  tmpMeta50 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 18)));
  tmp51 = mmc_unbox_real(tmpMeta50);
  tmp17._PEX4 = tmp51;
  tmpMeta52 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 19)));
  tmp53 = mmc_unbox_real(tmpMeta52);
  tmp17._LCX = tmp53;
  tmpMeta54 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 20)));
  tmp55 = mmc_unbox_real(tmpMeta54);
  tmp17._LMUX = tmp55;
  tmpMeta56 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 21)));
  tmp57 = mmc_unbox_real(tmpMeta56);
  tmp17._LKX = tmp57;
  tmpMeta58 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 22)));
  tmp59 = mmc_unbox_real(tmpMeta58);
  tmp17._LHX = tmp59;
  tmpMeta60 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 23)));
  tmp61 = mmc_unbox_real(tmpMeta60);
  tmp17._LVX = tmp61;
  tmpMeta62 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 24)));
  tmp63 = mmc_unbox_real(tmpMeta62);
  tmp17._LEX = tmp63;
  tmpMeta64 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 25)));
  tmp65 = mmc_unbox_real(tmpMeta64);
  tmp17._LXAL = tmp65;tmpMeta67 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 2)));
  tmp68 = mmc_unbox_real(tmpMeta67);
  tmp66._FNOMIN = tmp68;
  tmpMeta69 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 3)));
  tmp70 = mmc_unbox_real(tmpMeta69);
  tmp66._FZMIN = tmp70;
  tmpMeta71 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 4)));
  tmp72 = mmc_unbox_real(tmpMeta71);
  tmp66._FZMAX = tmp72;
  tmpMeta73 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 5)));
  tmp74 = mmc_unbox_real(tmpMeta73);
  tmp66._UNLOADED_RADIUS = tmp74;
  _My = omc_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MyPureEval(threadData, tmp1, tmp2, tmp3, tmp4, tmp17, tmp66);
  out_My = mmc_mk_rcon(_My);
  return out_My;
}

DLLDirection
modelica_real omc_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MzPureEval(threadData_t *threadData, modelica_real _Fz, modelica_real _Fy, modelica_real _alpha, modelica_real _kappa, modelica_real _gamma, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord _pFy, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord _pFx, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord _p, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord _setup)
{
  modelica_real _Mz_pure;
  modelica_real _dfz;
  modelica_real _mu_y;
  modelica_real _C_y;
  modelica_real _K_y;
  modelica_real _B_y;
  modelica_real _K_x;
  modelica_real _IA_y;
  modelica_real _S_Hy;
  modelica_real _S_Vy;
  modelica_real _IA_z;
  modelica_real _eps;
  modelica_real _D_t;
  modelica_real _C_t;
  modelica_real _B_t;
  modelica_real _E_t;
  modelica_real _S_Ht;
  modelica_real _SA_t;
  modelica_real _SA_t_eq;
  modelica_real _SA_r;
  modelica_real _SA_r_eq;
  modelica_real _t;
  modelica_real _D_r;
  modelica_real _B_r;
  modelica_real _M_zr;
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  modelica_real tmp4;
  modelica_real tmp5;
  modelica_real tmp6;
  modelica_real tmp7;
  modelica_real tmp8;
  modelica_real tmp9;
  modelica_real tmp10;
  modelica_real tmp11;
  modelica_real tmp12;
  modelica_real tmp13;
  modelica_real tmp14;
  modelica_real tmp15;
  modelica_real tmp16;
  modelica_real tmp17;
  modelica_real tmp18;
  modelica_real tmp19;
  modelica_real tmp20;
  modelica_real tmp21;
  _tailrecursive: OMC_LABEL_UNUSED
  // _Mz_pure has no default value.
  // _dfz has no default value.
  // _mu_y has no default value.
  // _C_y has no default value.
  // _K_y has no default value.
  // _B_y has no default value.
  // _K_x has no default value.
  // _IA_y has no default value.
  // _S_Hy has no default value.
  // _S_Vy has no default value.
  // _IA_z has no default value.
  _eps = 1e-8;
  // _D_t has no default value.
  // _C_t has no default value.
  // _B_t has no default value.
  // _E_t has no default value.
  // _S_Ht has no default value.
  // _SA_t has no default value.
  // _SA_t_eq has no default value.
  // _SA_r has no default value.
  // _SA_r_eq has no default value.
  // _t has no default value.
  // _D_r has no default value.
  // _B_r has no default value.
  // _M_zr has no default value.
  if((_Fz > 0.001))
  {
    tmp1 = (_setup._FNOMIN) * (_pFy._LFZO);
    if (tmp1 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "(Fz - setup.FNOMIN * pFy.LFZO) / (setup.FNOMIN * pFy.LFZO)");}
    _dfz = (_Fz - ((_setup._FNOMIN) * (_pFy._LFZO))) / tmp1;

    _IA_y = (_gamma) * (_pFy._LGAY);

    _C_y = (_pFy._PCY1) * (_pFy._LCY);

    tmp2 = _IA_y;
    _mu_y = ((_pFy._PDY1 + (_pFy._PDY2) * (_dfz)) * (1.0 - ((_pFy._PDY3) * ((tmp2 * tmp2))))) * (_pFy._LMUY);

    tmp3 = ((_pFy._PKY2) * (_setup._FNOMIN)) * (_pFy._LFZO);
    if (tmp3 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "Fz / (pFy.PKY2 * setup.FNOMIN * pFy.LFZO)");}
    _K_y = (((((_pFy._PKY1) * (_setup._FNOMIN)) * (sin((2.0) * (atan((_Fz) / tmp3))))) * (1.0 - ((_pFy._PKY3) * (fabs(_IA_y))))) * (_pFy._LFZO)) * (_pFy._LKY);

    tmp4 = ((_C_y) * (_mu_y)) * (_Fz) + _eps;
    if (tmp4 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "K_y / (C_y * mu_y * Fz + eps)");}
    _B_y = (_K_y) / tmp4;

    _S_Hy = (_pFy._PHY1 + (_pFy._PHY2) * (_dfz)) * (_pFy._LHY) + (_pFy._PHY3) * (_IA_y);

    _S_Vy = ((_Fz) * ((_pFy._PVY1 + (_pFy._PVY2) * (_dfz)) * (_pFy._LVY) + (_pFy._PVY3 + (_pFy._PVY4) * (_dfz)) * (_IA_y))) * (_pFy._LMUY);

    _K_x = (((_Fz) * (_pFx._PKX1 + (_pFx._PKX2) * (_dfz))) * (exp((_pFx._PKX3) * (_dfz)))) * (_pFx._LKX);

    _IA_z = _gamma;

    tmp5 = (_IA_z) * (_p._LGAZ);
    tmp6 = _setup._FNOMIN;
    if (tmp6 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "setup.UNLOADED_RADIUS / setup.FNOMIN");}
    _D_t = ((((_Fz) * (_p._QDZ1 + (_p._QDZ2) * (_dfz))) * (1.0 + ((_p._QDZ3) * (_IA_z)) * (_p._LGAZ) + (_p._QDZ4) * ((tmp5 * tmp5)))) * ((_setup._UNLOADED_RADIUS) / tmp6)) * (_p._LTR);

    _C_t = _p._QCZ1;

    tmp7 = _dfz;
    tmp8 = _p._LMUY;
    if (tmp8 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "(p.QBZ1 + p.QBZ2 * dfz + p.QBZ3 * dfz ^ 2.0) * (1.0 + p.QBZ4 * IA_z * p.LGAZ + p.QBZ5 * abs(IA_z * p.LGAZ)) * p.LKY / p.LMUY");}
    _B_t = (((_p._QBZ1 + (_p._QBZ2) * (_dfz) + (_p._QBZ3) * ((tmp7 * tmp7))) * (1.0 + ((_p._QBZ4) * (_IA_z)) * (_p._LGAZ) + (_p._QBZ5) * (fabs((_IA_z) * (_p._LGAZ))))) * (_p._LKY)) / tmp8;

    _S_Ht = _p._QHZ1 + (_p._QHZ2) * (_dfz) + ((_p._QHZ3 + (_p._QHZ4) * (_dfz)) * (_IA_z)) * (_p._LGAZ);

    _SA_t = _alpha + _S_Ht;

    tmp9 = _dfz;
    _E_t = (_p._QEZ1 + (_p._QEZ2) * (_dfz) + (_p._QEZ3) * ((tmp9 * tmp9))) * (1.0 + ((_p._QEZ4 + ((_p._QEZ5) * (_IA_z)) * (_p._LGAZ)) * (0.6366197723675814)) * (atan(((_B_t) * (_C_t)) * (_SA_t))));

    _E_t = fmin(_E_t,1.0);

    tmp10 = tan(_SA_t);
    tmp11 = _K_y + _eps;
    if (tmp11 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "K_x / (K_y + eps)");}
    tmp12 = (_K_x) / tmp11;
    tmp13 = _kappa;
    tmp14 = (tmp10 * tmp10) + ((tmp12 * tmp12)) * ((tmp13 * tmp13));
    if(!(tmp14 >= 0.0))
    {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert(threadData, info, "Model error: Argument of sqrt(tan(SA_t) ^ 2.0 + (K_x / (K_y + eps)) ^ 2.0 * kappa ^ 2.0) was %g should be >= 0", tmp14);
    }
    _SA_t_eq = (atan(sqrt(tmp14))) * (((modelica_real)sign(_SA_t)));

    _t = ((_D_t) * (cos((_C_t) * (atan((_B_t) * (_SA_t_eq) - ((_E_t) * ((_B_t) * (_SA_t_eq) - atan((_B_t) * (_SA_t_eq))))))))) * (cos(_alpha));

    tmp15 = _K_y + _eps;
    if (tmp15 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "S_Vy / (K_y + eps)");}
    _SA_r = _alpha + _S_Hy + (_S_Vy) / tmp15;

    tmp16 = tan(_SA_r);
    tmp17 = _K_y + _eps;
    if (tmp17 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "K_x / (K_y + eps)");}
    tmp18 = (_K_x) / tmp17;
    tmp19 = _kappa;
    tmp20 = (tmp16 * tmp16) + ((tmp18 * tmp18)) * ((tmp19 * tmp19));
    if(!(tmp20 >= 0.0))
    {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert(threadData, info, "Model error: Argument of sqrt(tan(SA_r) ^ 2.0 + (K_x / (K_y + eps)) ^ 2.0 * kappa ^ 2.0) was %g should be >= 0", tmp20);
    }
    _SA_r_eq = (atan(sqrt(tmp20))) * (((modelica_real)sign(_SA_r)));

    _D_r = (((_Fz) * ((_p._QDZ6 + (_p._QDZ7) * (_dfz)) * (_p._LRES) + ((_p._QDZ8 + (_p._QDZ9) * (_dfz)) * (_IA_z)) * (_p._LGAZ))) * (_setup._UNLOADED_RADIUS)) * (_p._LMUY);

    tmp21 = _p._LMUY;
    if (tmp21 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "p.QBZ9 * p.LKY / p.LMUY");}
    _B_r = ((_p._QBZ9) * (_p._LKY)) / tmp21 + ((_p._QBZ10) * (_B_y)) * (_C_y);

    _M_zr = ((_D_r) * (cos(atan((_B_r) * (_SA_r_eq))))) * (cos(_alpha));

    _Mz_pure = _M_zr - ((_t) * (_Fy));
  }
  else
  {
    _Mz_pure = 0.0;
  }
  _return: OMC_LABEL_UNUSED
  return _Mz_pure;
}
modelica_metatype boxptr_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MzPureEval(threadData_t *threadData, modelica_metatype _Fz, modelica_metatype _Fy, modelica_metatype _alpha, modelica_metatype _kappa, modelica_metatype _gamma, modelica_metatype _pFy, modelica_metatype _pFx, modelica_metatype _p, modelica_metatype _setup)
{
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  modelica_real tmp4;
  modelica_real tmp5;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord tmp6;
  modelica_metatype tmpMeta7;
  modelica_real tmp8;
  modelica_metatype tmpMeta9;
  modelica_real tmp10;
  modelica_metatype tmpMeta11;
  modelica_real tmp12;
  modelica_metatype tmpMeta13;
  modelica_real tmp14;
  modelica_metatype tmpMeta15;
  modelica_real tmp16;
  modelica_metatype tmpMeta17;
  modelica_real tmp18;
  modelica_metatype tmpMeta19;
  modelica_real tmp20;
  modelica_metatype tmpMeta21;
  modelica_real tmp22;
  modelica_metatype tmpMeta23;
  modelica_real tmp24;
  modelica_metatype tmpMeta25;
  modelica_real tmp26;
  modelica_metatype tmpMeta27;
  modelica_real tmp28;
  modelica_metatype tmpMeta29;
  modelica_real tmp30;
  modelica_metatype tmpMeta31;
  modelica_real tmp32;
  modelica_metatype tmpMeta33;
  modelica_real tmp34;
  modelica_metatype tmpMeta35;
  modelica_real tmp36;
  modelica_metatype tmpMeta37;
  modelica_real tmp38;
  modelica_metatype tmpMeta39;
  modelica_real tmp40;
  modelica_metatype tmpMeta41;
  modelica_real tmp42;
  modelica_metatype tmpMeta43;
  modelica_real tmp44;
  modelica_metatype tmpMeta45;
  modelica_real tmp46;
  modelica_metatype tmpMeta47;
  modelica_real tmp48;
  modelica_metatype tmpMeta49;
  modelica_real tmp50;
  modelica_metatype tmpMeta51;
  modelica_real tmp52;
  modelica_metatype tmpMeta53;
  modelica_real tmp54;
  modelica_metatype tmpMeta55;
  modelica_real tmp56;
  modelica_metatype tmpMeta57;
  modelica_real tmp58;
  modelica_metatype tmpMeta59;
  modelica_real tmp60;
  modelica_metatype tmpMeta61;
  modelica_real tmp62;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord tmp63;
  modelica_metatype tmpMeta64;
  modelica_real tmp65;
  modelica_metatype tmpMeta66;
  modelica_real tmp67;
  modelica_metatype tmpMeta68;
  modelica_real tmp69;
  modelica_metatype tmpMeta70;
  modelica_real tmp71;
  modelica_metatype tmpMeta72;
  modelica_real tmp73;
  modelica_metatype tmpMeta74;
  modelica_real tmp75;
  modelica_metatype tmpMeta76;
  modelica_real tmp77;
  modelica_metatype tmpMeta78;
  modelica_real tmp79;
  modelica_metatype tmpMeta80;
  modelica_real tmp81;
  modelica_metatype tmpMeta82;
  modelica_real tmp83;
  modelica_metatype tmpMeta84;
  modelica_real tmp85;
  modelica_metatype tmpMeta86;
  modelica_real tmp87;
  modelica_metatype tmpMeta88;
  modelica_real tmp89;
  modelica_metatype tmpMeta90;
  modelica_real tmp91;
  modelica_metatype tmpMeta92;
  modelica_real tmp93;
  modelica_metatype tmpMeta94;
  modelica_real tmp95;
  modelica_metatype tmpMeta96;
  modelica_real tmp97;
  modelica_metatype tmpMeta98;
  modelica_real tmp99;
  modelica_metatype tmpMeta100;
  modelica_real tmp101;
  modelica_metatype tmpMeta102;
  modelica_real tmp103;
  modelica_metatype tmpMeta104;
  modelica_real tmp105;
  modelica_metatype tmpMeta106;
  modelica_real tmp107;
  modelica_metatype tmpMeta108;
  modelica_real tmp109;
  modelica_metatype tmpMeta110;
  modelica_real tmp111;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord tmp112;
  modelica_metatype tmpMeta113;
  modelica_real tmp114;
  modelica_metatype tmpMeta115;
  modelica_real tmp116;
  modelica_metatype tmpMeta117;
  modelica_real tmp118;
  modelica_metatype tmpMeta119;
  modelica_real tmp120;
  modelica_metatype tmpMeta121;
  modelica_real tmp122;
  modelica_metatype tmpMeta123;
  modelica_real tmp124;
  modelica_metatype tmpMeta125;
  modelica_real tmp126;
  modelica_metatype tmpMeta127;
  modelica_real tmp128;
  modelica_metatype tmpMeta129;
  modelica_real tmp130;
  modelica_metatype tmpMeta131;
  modelica_real tmp132;
  modelica_metatype tmpMeta133;
  modelica_real tmp134;
  modelica_metatype tmpMeta135;
  modelica_real tmp136;
  modelica_metatype tmpMeta137;
  modelica_real tmp138;
  modelica_metatype tmpMeta139;
  modelica_real tmp140;
  modelica_metatype tmpMeta141;
  modelica_real tmp142;
  modelica_metatype tmpMeta143;
  modelica_real tmp144;
  modelica_metatype tmpMeta145;
  modelica_real tmp146;
  modelica_metatype tmpMeta147;
  modelica_real tmp148;
  modelica_metatype tmpMeta149;
  modelica_real tmp150;
  modelica_metatype tmpMeta151;
  modelica_real tmp152;
  modelica_metatype tmpMeta153;
  modelica_real tmp154;
  modelica_metatype tmpMeta155;
  modelica_real tmp156;
  modelica_metatype tmpMeta157;
  modelica_real tmp158;
  modelica_metatype tmpMeta159;
  modelica_real tmp160;
  modelica_metatype tmpMeta161;
  modelica_real tmp162;
  modelica_metatype tmpMeta163;
  modelica_real tmp164;
  modelica_metatype tmpMeta165;
  modelica_real tmp166;
  modelica_metatype tmpMeta167;
  modelica_real tmp168;
  modelica_metatype tmpMeta169;
  modelica_real tmp170;
  modelica_metatype tmpMeta171;
  modelica_real tmp172;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord tmp173;
  modelica_metatype tmpMeta174;
  modelica_real tmp175;
  modelica_metatype tmpMeta176;
  modelica_real tmp177;
  modelica_metatype tmpMeta178;
  modelica_real tmp179;
  modelica_metatype tmpMeta180;
  modelica_real tmp181;
  modelica_real _Mz_pure;
  modelica_metatype out_Mz_pure;
  tmp1 = mmc_unbox_real(_Fz);
  tmp2 = mmc_unbox_real(_Fy);
  tmp3 = mmc_unbox_real(_alpha);
  tmp4 = mmc_unbox_real(_kappa);
  tmp5 = mmc_unbox_real(_gamma);
  tmpMeta7 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 2)));
  tmp8 = mmc_unbox_real(tmpMeta7);
  tmp6._LFZO = tmp8;
  tmpMeta9 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 3)));
  tmp10 = mmc_unbox_real(tmpMeta9);
  tmp6._LGAY = tmp10;
  tmpMeta11 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 4)));
  tmp12 = mmc_unbox_real(tmpMeta11);
  tmp6._PCY1 = tmp12;
  tmpMeta13 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 5)));
  tmp14 = mmc_unbox_real(tmpMeta13);
  tmp6._PDY1 = tmp14;
  tmpMeta15 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 6)));
  tmp16 = mmc_unbox_real(tmpMeta15);
  tmp6._PDY2 = tmp16;
  tmpMeta17 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 7)));
  tmp18 = mmc_unbox_real(tmpMeta17);
  tmp6._PDY3 = tmp18;
  tmpMeta19 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 8)));
  tmp20 = mmc_unbox_real(tmpMeta19);
  tmp6._PKY1 = tmp20;
  tmpMeta21 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 9)));
  tmp22 = mmc_unbox_real(tmpMeta21);
  tmp6._PKY2 = tmp22;
  tmpMeta23 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 10)));
  tmp24 = mmc_unbox_real(tmpMeta23);
  tmp6._PKY3 = tmp24;
  tmpMeta25 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 11)));
  tmp26 = mmc_unbox_real(tmpMeta25);
  tmp6._PHY1 = tmp26;
  tmpMeta27 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 12)));
  tmp28 = mmc_unbox_real(tmpMeta27);
  tmp6._PHY2 = tmp28;
  tmpMeta29 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 13)));
  tmp30 = mmc_unbox_real(tmpMeta29);
  tmp6._PHY3 = tmp30;
  tmpMeta31 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 14)));
  tmp32 = mmc_unbox_real(tmpMeta31);
  tmp6._PVY1 = tmp32;
  tmpMeta33 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 15)));
  tmp34 = mmc_unbox_real(tmpMeta33);
  tmp6._PVY2 = tmp34;
  tmpMeta35 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 16)));
  tmp36 = mmc_unbox_real(tmpMeta35);
  tmp6._PVY3 = tmp36;
  tmpMeta37 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 17)));
  tmp38 = mmc_unbox_real(tmpMeta37);
  tmp6._PVY4 = tmp38;
  tmpMeta39 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 18)));
  tmp40 = mmc_unbox_real(tmpMeta39);
  tmp6._PEY1 = tmp40;
  tmpMeta41 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 19)));
  tmp42 = mmc_unbox_real(tmpMeta41);
  tmp6._PEY2 = tmp42;
  tmpMeta43 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 20)));
  tmp44 = mmc_unbox_real(tmpMeta43);
  tmp6._PEY3 = tmp44;
  tmpMeta45 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 21)));
  tmp46 = mmc_unbox_real(tmpMeta45);
  tmp6._PEY4 = tmp46;
  tmpMeta47 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 22)));
  tmp48 = mmc_unbox_real(tmpMeta47);
  tmp6._LCY = tmp48;
  tmpMeta49 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 23)));
  tmp50 = mmc_unbox_real(tmpMeta49);
  tmp6._LMUY = tmp50;
  tmpMeta51 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 24)));
  tmp52 = mmc_unbox_real(tmpMeta51);
  tmp6._LEY = tmp52;
  tmpMeta53 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 25)));
  tmp54 = mmc_unbox_real(tmpMeta53);
  tmp6._LKY = tmp54;
  tmpMeta55 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 26)));
  tmp56 = mmc_unbox_real(tmpMeta55);
  tmp6._LHY = tmp56;
  tmpMeta57 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 27)));
  tmp58 = mmc_unbox_real(tmpMeta57);
  tmp6._LVY = tmp58;
  tmpMeta59 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 28)));
  tmp60 = mmc_unbox_real(tmpMeta59);
  tmp6._LYKA = tmp60;
  tmpMeta61 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFy), 29)));
  tmp62 = mmc_unbox_real(tmpMeta61);
  tmp6._LVYKA = tmp62;tmpMeta64 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 2)));
  tmp65 = mmc_unbox_real(tmpMeta64);
  tmp63._LGAX = tmp65;
  tmpMeta66 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 3)));
  tmp67 = mmc_unbox_real(tmpMeta66);
  tmp63._LFZO = tmp67;
  tmpMeta68 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 4)));
  tmp69 = mmc_unbox_real(tmpMeta68);
  tmp63._PCX1 = tmp69;
  tmpMeta70 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 5)));
  tmp71 = mmc_unbox_real(tmpMeta70);
  tmp63._PDX1 = tmp71;
  tmpMeta72 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 6)));
  tmp73 = mmc_unbox_real(tmpMeta72);
  tmp63._PDX2 = tmp73;
  tmpMeta74 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 7)));
  tmp75 = mmc_unbox_real(tmpMeta74);
  tmp63._PDX3 = tmp75;
  tmpMeta76 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 8)));
  tmp77 = mmc_unbox_real(tmpMeta76);
  tmp63._PKX1 = tmp77;
  tmpMeta78 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 9)));
  tmp79 = mmc_unbox_real(tmpMeta78);
  tmp63._PKX2 = tmp79;
  tmpMeta80 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 10)));
  tmp81 = mmc_unbox_real(tmpMeta80);
  tmp63._PKX3 = tmp81;
  tmpMeta82 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 11)));
  tmp83 = mmc_unbox_real(tmpMeta82);
  tmp63._PHX1 = tmp83;
  tmpMeta84 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 12)));
  tmp85 = mmc_unbox_real(tmpMeta84);
  tmp63._PHX2 = tmp85;
  tmpMeta86 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 13)));
  tmp87 = mmc_unbox_real(tmpMeta86);
  tmp63._PVX1 = tmp87;
  tmpMeta88 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 14)));
  tmp89 = mmc_unbox_real(tmpMeta88);
  tmp63._PVX2 = tmp89;
  tmpMeta90 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 15)));
  tmp91 = mmc_unbox_real(tmpMeta90);
  tmp63._PEX1 = tmp91;
  tmpMeta92 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 16)));
  tmp93 = mmc_unbox_real(tmpMeta92);
  tmp63._PEX2 = tmp93;
  tmpMeta94 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 17)));
  tmp95 = mmc_unbox_real(tmpMeta94);
  tmp63._PEX3 = tmp95;
  tmpMeta96 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 18)));
  tmp97 = mmc_unbox_real(tmpMeta96);
  tmp63._PEX4 = tmp97;
  tmpMeta98 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 19)));
  tmp99 = mmc_unbox_real(tmpMeta98);
  tmp63._LCX = tmp99;
  tmpMeta100 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 20)));
  tmp101 = mmc_unbox_real(tmpMeta100);
  tmp63._LMUX = tmp101;
  tmpMeta102 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 21)));
  tmp103 = mmc_unbox_real(tmpMeta102);
  tmp63._LKX = tmp103;
  tmpMeta104 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 22)));
  tmp105 = mmc_unbox_real(tmpMeta104);
  tmp63._LHX = tmp105;
  tmpMeta106 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 23)));
  tmp107 = mmc_unbox_real(tmpMeta106);
  tmp63._LVX = tmp107;
  tmpMeta108 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 24)));
  tmp109 = mmc_unbox_real(tmpMeta108);
  tmp63._LEX = tmp109;
  tmpMeta110 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_pFx), 25)));
  tmp111 = mmc_unbox_real(tmpMeta110);
  tmp63._LXAL = tmp111;tmpMeta113 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 2)));
  tmp114 = mmc_unbox_real(tmpMeta113);
  tmp112._QBZ1 = tmp114;
  tmpMeta115 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 3)));
  tmp116 = mmc_unbox_real(tmpMeta115);
  tmp112._QBZ2 = tmp116;
  tmpMeta117 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 4)));
  tmp118 = mmc_unbox_real(tmpMeta117);
  tmp112._QBZ3 = tmp118;
  tmpMeta119 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 5)));
  tmp120 = mmc_unbox_real(tmpMeta119);
  tmp112._QBZ4 = tmp120;
  tmpMeta121 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 6)));
  tmp122 = mmc_unbox_real(tmpMeta121);
  tmp112._QBZ5 = tmp122;
  tmpMeta123 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 7)));
  tmp124 = mmc_unbox_real(tmpMeta123);
  tmp112._QCZ1 = tmp124;
  tmpMeta125 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 8)));
  tmp126 = mmc_unbox_real(tmpMeta125);
  tmp112._QDZ1 = tmp126;
  tmpMeta127 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 9)));
  tmp128 = mmc_unbox_real(tmpMeta127);
  tmp112._QDZ2 = tmp128;
  tmpMeta129 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 10)));
  tmp130 = mmc_unbox_real(tmpMeta129);
  tmp112._QDZ3 = tmp130;
  tmpMeta131 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 11)));
  tmp132 = mmc_unbox_real(tmpMeta131);
  tmp112._QDZ4 = tmp132;
  tmpMeta133 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 12)));
  tmp134 = mmc_unbox_real(tmpMeta133);
  tmp112._QEZ1 = tmp134;
  tmpMeta135 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 13)));
  tmp136 = mmc_unbox_real(tmpMeta135);
  tmp112._QEZ2 = tmp136;
  tmpMeta137 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 14)));
  tmp138 = mmc_unbox_real(tmpMeta137);
  tmp112._QEZ3 = tmp138;
  tmpMeta139 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 15)));
  tmp140 = mmc_unbox_real(tmpMeta139);
  tmp112._QEZ4 = tmp140;
  tmpMeta141 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 16)));
  tmp142 = mmc_unbox_real(tmpMeta141);
  tmp112._QEZ5 = tmp142;
  tmpMeta143 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 17)));
  tmp144 = mmc_unbox_real(tmpMeta143);
  tmp112._QHZ1 = tmp144;
  tmpMeta145 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 18)));
  tmp146 = mmc_unbox_real(tmpMeta145);
  tmp112._QHZ2 = tmp146;
  tmpMeta147 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 19)));
  tmp148 = mmc_unbox_real(tmpMeta147);
  tmp112._QHZ3 = tmp148;
  tmpMeta149 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 20)));
  tmp150 = mmc_unbox_real(tmpMeta149);
  tmp112._QHZ4 = tmp150;
  tmpMeta151 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 21)));
  tmp152 = mmc_unbox_real(tmpMeta151);
  tmp112._QBZ9 = tmp152;
  tmpMeta153 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 22)));
  tmp154 = mmc_unbox_real(tmpMeta153);
  tmp112._QBZ10 = tmp154;
  tmpMeta155 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 23)));
  tmp156 = mmc_unbox_real(tmpMeta155);
  tmp112._QDZ6 = tmp156;
  tmpMeta157 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 24)));
  tmp158 = mmc_unbox_real(tmpMeta157);
  tmp112._QDZ7 = tmp158;
  tmpMeta159 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 25)));
  tmp160 = mmc_unbox_real(tmpMeta159);
  tmp112._QDZ8 = tmp160;
  tmpMeta161 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 26)));
  tmp162 = mmc_unbox_real(tmpMeta161);
  tmp112._QDZ9 = tmp162;
  tmpMeta163 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 27)));
  tmp164 = mmc_unbox_real(tmpMeta163);
  tmp112._LTR = tmp164;
  tmpMeta165 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 28)));
  tmp166 = mmc_unbox_real(tmpMeta165);
  tmp112._LRES = tmp166;
  tmpMeta167 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 29)));
  tmp168 = mmc_unbox_real(tmpMeta167);
  tmp112._LKY = tmp168;
  tmpMeta169 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 30)));
  tmp170 = mmc_unbox_real(tmpMeta169);
  tmp112._LMUY = tmp170;
  tmpMeta171 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_p), 31)));
  tmp172 = mmc_unbox_real(tmpMeta171);
  tmp112._LGAZ = tmp172;tmpMeta174 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 2)));
  tmp175 = mmc_unbox_real(tmpMeta174);
  tmp173._FNOMIN = tmp175;
  tmpMeta176 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 3)));
  tmp177 = mmc_unbox_real(tmpMeta176);
  tmp173._FZMIN = tmp177;
  tmpMeta178 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 4)));
  tmp179 = mmc_unbox_real(tmpMeta178);
  tmp173._FZMAX = tmp179;
  tmpMeta180 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_setup), 5)));
  tmp181 = mmc_unbox_real(tmpMeta180);
  tmp173._UNLOADED_RADIUS = tmp181;
  _Mz_pure = omc_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MzPureEval(threadData, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp63, tmp112, tmp173);
  out_Mz_pure = mmc_mk_rcon(_Mz_pure);
  return out_Mz_pure;
}

DLLDirection
modelica_boolean omc_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_frAxleDW_leftWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData_t *threadData, modelica_real _L, real_array _e, modelica_real _angle_guess, real_array _r_a, real_array _r_b)
{
  modelica_boolean _positiveBranch;
  modelica_real _e_r_a;
  modelica_real _e_r_b;
  modelica_real _A;
  modelica_real _B;
  modelica_real _C;
  modelica_real _k1;
  modelica_real _k2;
  modelica_real _k1a;
  modelica_real _k1b;
  modelica_real _kcos1;
  modelica_real _ksin1;
  modelica_real _kcos2;
  modelica_real _ksin2;
  modelica_real _angle1;
  modelica_real _angle2;
  static int tmp1 = 0;
  modelica_real tmp2;
  _tailrecursive: OMC_LABEL_UNUSED
  // _positiveBranch has no default value.
  // _e_r_a has no default value.
  // _e_r_b has no default value.
  // _A has no default value.
  // _B has no default value.
  // _C has no default value.
  // _k1 has no default value.
  // _k2 has no default value.
  // _k1a has no default value.
  // _k1b has no default value.
  // _kcos1 has no default value.
  // _ksin1 has no default value.
  // _kcos2 has no default value.
  // _ksin2 has no default value.
  // _angle1 has no default value.
  // _angle2 has no default value.
  _e_r_a = (real_array_get(_e, 1, ((modelica_integer) 1))) * (real_array_get(_r_a, 1, ((modelica_integer) 1))) + (real_array_get(_e, 1, ((modelica_integer) 2))) * (real_array_get(_r_a, 1, ((modelica_integer) 2))) + (real_array_get(_e, 1, ((modelica_integer) 3))) * (real_array_get(_r_a, 1, ((modelica_integer) 3)));

  _e_r_b = (real_array_get(_e, 1, ((modelica_integer) 1))) * (real_array_get(_r_b, 1, ((modelica_integer) 1))) + (real_array_get(_e, 1, ((modelica_integer) 2))) * (real_array_get(_r_b, 1, ((modelica_integer) 2))) + (real_array_get(_e, 1, ((modelica_integer) 3))) * (real_array_get(_r_b, 1, ((modelica_integer) 3)));

  _A = (-((2.0) * ((real_array_get(_r_b, 1, ((modelica_integer) 1))) * (real_array_get(_r_a, 1, ((modelica_integer) 1))) + (real_array_get(_r_b, 1, ((modelica_integer) 2))) * (real_array_get(_r_a, 1, ((modelica_integer) 2))) + (real_array_get(_r_b, 1, ((modelica_integer) 3))) * (real_array_get(_r_a, 1, ((modelica_integer) 3))) - ((_e_r_b) * (_e_r_a)))));

  _B = ((2.0) * (real_array_get(_r_b, 1, ((modelica_integer) 1)))) * ((real_array_get(_e, 1, ((modelica_integer) 2))) * (real_array_get(_r_a, 1, ((modelica_integer) 3))) - ((real_array_get(_e, 1, ((modelica_integer) 3))) * (real_array_get(_r_a, 1, ((modelica_integer) 2))))) + ((2.0) * (real_array_get(_r_b, 1, ((modelica_integer) 2)))) * ((real_array_get(_e, 1, ((modelica_integer) 3))) * (real_array_get(_r_a, 1, ((modelica_integer) 1))) - ((real_array_get(_e, 1, ((modelica_integer) 1))) * (real_array_get(_r_a, 1, ((modelica_integer) 3))))) + ((2.0) * (real_array_get(_r_b, 1, ((modelica_integer) 3)))) * ((real_array_get(_e, 1, ((modelica_integer) 1))) * (real_array_get(_r_a, 1, ((modelica_integer) 2))) - ((real_array_get(_e, 1, ((modelica_integer) 2))) * (real_array_get(_r_a, 1, ((modelica_integer) 1)))));

  _C = (real_array_get(_r_a, 1, ((modelica_integer) 1))) * (real_array_get(_r_a, 1, ((modelica_integer) 1))) + (real_array_get(_r_a, 1, ((modelica_integer) 2))) * (real_array_get(_r_a, 1, ((modelica_integer) 2))) + (real_array_get(_r_a, 1, ((modelica_integer) 3))) * (real_array_get(_r_a, 1, ((modelica_integer) 3))) + (real_array_get(_r_b, 1, ((modelica_integer) 1))) * (real_array_get(_r_b, 1, ((modelica_integer) 1))) + (real_array_get(_r_b, 1, ((modelica_integer) 2))) * (real_array_get(_r_b, 1, ((modelica_integer) 2))) + (real_array_get(_r_b, 1, ((modelica_integer) 3))) * (real_array_get(_r_b, 1, ((modelica_integer) 3))) - ((_L) * (_L)) - (((2.0) * (_e_r_b)) * (_e_r_a));

  _k1 = (_A) * (_A) + (_B) * (_B);

  _k1a = _k1 - ((_C) * (_C));

  {
    if(!(_k1a > 1e-10))
    {
      {
        FILE_INFO info = {"/home/rhorvath/.openmodelica/libraries/Modelica 4.1.0+maint.om/Mechanics/MultiBody/Joints/Internal/RevoluteWithLengthConstraint.mo",160,5,172,3,0};
        omc_assert(threadData, info, MMC_STRINGDATA(_OMC_LIT14));
      }
    }
  }

  _k1b = fmax(_k1a,1e-12);

  tmp2 = _k1b;
  if(!(tmp2 >= 0.0))
  {
    FILE_INFO info = {"",0,0,0,0,0};
    omc_assert(threadData, info, "Model error: Argument of sqrt(k1b) was %g should be >= 0", tmp2);
  }
  _k2 = sqrt(tmp2);

  _kcos1 = (_B) * (_k2) - ((_A) * (_C));

  _ksin1 = (-((_B) * (_C) + (_A) * (_k2)));

  _angle1 = omc_Modelica_Math_atan2(threadData, _ksin1, _kcos1);

  _kcos2 = (-((_A) * (_C) + (_B) * (_k2)));

  _ksin2 = (_A) * (_k2) - ((_B) * (_C));

  _angle2 = omc_Modelica_Math_atan2(threadData, _ksin2, _kcos2);

  if((fabs(_angle1 - _angle_guess) <= fabs(_angle2 - _angle_guess)))
  {
    _positiveBranch = 1 /* true */;
  }
  else
  {
    _positiveBranch = 0 /* false */;
  }
  _return: OMC_LABEL_UNUSED
  return _positiveBranch;
}
modelica_metatype boxptr_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_frAxleDW_leftWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData_t *threadData, modelica_metatype _L, modelica_metatype _e, modelica_metatype _angle_guess, modelica_metatype _r_a, modelica_metatype _r_b)
{
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_boolean _positiveBranch;
  modelica_metatype out_positiveBranch;
  tmp1 = mmc_unbox_real(_L);
  tmp2 = mmc_unbox_real(_angle_guess);
  _positiveBranch = omc_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_frAxleDW_leftWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData, tmp1, *((base_array_t*)_e), tmp2, *((base_array_t*)_r_a), *((base_array_t*)_r_b));
  out_positiveBranch = mmc_mk_icon(_positiveBranch);
  return out_positiveBranch;
}

DLLDirection
modelica_boolean omc_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_frAxleDW_rightWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData_t *threadData, modelica_real _L, real_array _e, modelica_real _angle_guess, real_array _r_a, real_array _r_b)
{
  modelica_boolean _positiveBranch;
  modelica_real _e_r_a;
  modelica_real _e_r_b;
  modelica_real _A;
  modelica_real _B;
  modelica_real _C;
  modelica_real _k1;
  modelica_real _k2;
  modelica_real _k1a;
  modelica_real _k1b;
  modelica_real _kcos1;
  modelica_real _ksin1;
  modelica_real _kcos2;
  modelica_real _ksin2;
  modelica_real _angle1;
  modelica_real _angle2;
  static int tmp1 = 0;
  modelica_real tmp2;
  _tailrecursive: OMC_LABEL_UNUSED
  // _positiveBranch has no default value.
  // _e_r_a has no default value.
  // _e_r_b has no default value.
  // _A has no default value.
  // _B has no default value.
  // _C has no default value.
  // _k1 has no default value.
  // _k2 has no default value.
  // _k1a has no default value.
  // _k1b has no default value.
  // _kcos1 has no default value.
  // _ksin1 has no default value.
  // _kcos2 has no default value.
  // _ksin2 has no default value.
  // _angle1 has no default value.
  // _angle2 has no default value.
  _e_r_a = (real_array_get(_e, 1, ((modelica_integer) 1))) * (real_array_get(_r_a, 1, ((modelica_integer) 1))) + (real_array_get(_e, 1, ((modelica_integer) 2))) * (real_array_get(_r_a, 1, ((modelica_integer) 2))) + (real_array_get(_e, 1, ((modelica_integer) 3))) * (real_array_get(_r_a, 1, ((modelica_integer) 3)));

  _e_r_b = (real_array_get(_e, 1, ((modelica_integer) 1))) * (real_array_get(_r_b, 1, ((modelica_integer) 1))) + (real_array_get(_e, 1, ((modelica_integer) 2))) * (real_array_get(_r_b, 1, ((modelica_integer) 2))) + (real_array_get(_e, 1, ((modelica_integer) 3))) * (real_array_get(_r_b, 1, ((modelica_integer) 3)));

  _A = (-((2.0) * ((real_array_get(_r_b, 1, ((modelica_integer) 1))) * (real_array_get(_r_a, 1, ((modelica_integer) 1))) + (real_array_get(_r_b, 1, ((modelica_integer) 2))) * (real_array_get(_r_a, 1, ((modelica_integer) 2))) + (real_array_get(_r_b, 1, ((modelica_integer) 3))) * (real_array_get(_r_a, 1, ((modelica_integer) 3))) - ((_e_r_b) * (_e_r_a)))));

  _B = ((2.0) * (real_array_get(_r_b, 1, ((modelica_integer) 1)))) * ((real_array_get(_e, 1, ((modelica_integer) 2))) * (real_array_get(_r_a, 1, ((modelica_integer) 3))) - ((real_array_get(_e, 1, ((modelica_integer) 3))) * (real_array_get(_r_a, 1, ((modelica_integer) 2))))) + ((2.0) * (real_array_get(_r_b, 1, ((modelica_integer) 2)))) * ((real_array_get(_e, 1, ((modelica_integer) 3))) * (real_array_get(_r_a, 1, ((modelica_integer) 1))) - ((real_array_get(_e, 1, ((modelica_integer) 1))) * (real_array_get(_r_a, 1, ((modelica_integer) 3))))) + ((2.0) * (real_array_get(_r_b, 1, ((modelica_integer) 3)))) * ((real_array_get(_e, 1, ((modelica_integer) 1))) * (real_array_get(_r_a, 1, ((modelica_integer) 2))) - ((real_array_get(_e, 1, ((modelica_integer) 2))) * (real_array_get(_r_a, 1, ((modelica_integer) 1)))));

  _C = (real_array_get(_r_a, 1, ((modelica_integer) 1))) * (real_array_get(_r_a, 1, ((modelica_integer) 1))) + (real_array_get(_r_a, 1, ((modelica_integer) 2))) * (real_array_get(_r_a, 1, ((modelica_integer) 2))) + (real_array_get(_r_a, 1, ((modelica_integer) 3))) * (real_array_get(_r_a, 1, ((modelica_integer) 3))) + (real_array_get(_r_b, 1, ((modelica_integer) 1))) * (real_array_get(_r_b, 1, ((modelica_integer) 1))) + (real_array_get(_r_b, 1, ((modelica_integer) 2))) * (real_array_get(_r_b, 1, ((modelica_integer) 2))) + (real_array_get(_r_b, 1, ((modelica_integer) 3))) * (real_array_get(_r_b, 1, ((modelica_integer) 3))) - ((_L) * (_L)) - (((2.0) * (_e_r_b)) * (_e_r_a));

  _k1 = (_A) * (_A) + (_B) * (_B);

  _k1a = _k1 - ((_C) * (_C));

  {
    if(!(_k1a > 1e-10))
    {
      {
        FILE_INFO info = {"/home/rhorvath/.openmodelica/libraries/Modelica 4.1.0+maint.om/Mechanics/MultiBody/Joints/Internal/RevoluteWithLengthConstraint.mo",160,5,172,3,0};
        omc_assert(threadData, info, MMC_STRINGDATA(_OMC_LIT14));
      }
    }
  }

  _k1b = fmax(_k1a,1e-12);

  tmp2 = _k1b;
  if(!(tmp2 >= 0.0))
  {
    FILE_INFO info = {"",0,0,0,0,0};
    omc_assert(threadData, info, "Model error: Argument of sqrt(k1b) was %g should be >= 0", tmp2);
  }
  _k2 = sqrt(tmp2);

  _kcos1 = (_B) * (_k2) - ((_A) * (_C));

  _ksin1 = (-((_B) * (_C) + (_A) * (_k2)));

  _angle1 = omc_Modelica_Math_atan2(threadData, _ksin1, _kcos1);

  _kcos2 = (-((_A) * (_C) + (_B) * (_k2)));

  _ksin2 = (_A) * (_k2) - ((_B) * (_C));

  _angle2 = omc_Modelica_Math_atan2(threadData, _ksin2, _kcos2);

  if((fabs(_angle1 - _angle_guess) <= fabs(_angle2 - _angle_guess)))
  {
    _positiveBranch = 1 /* true */;
  }
  else
  {
    _positiveBranch = 0 /* false */;
  }
  _return: OMC_LABEL_UNUSED
  return _positiveBranch;
}
modelica_metatype boxptr_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_frAxleDW_rightWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData_t *threadData, modelica_metatype _L, modelica_metatype _e, modelica_metatype _angle_guess, modelica_metatype _r_a, modelica_metatype _r_b)
{
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_boolean _positiveBranch;
  modelica_metatype out_positiveBranch;
  tmp1 = mmc_unbox_real(_L);
  tmp2 = mmc_unbox_real(_angle_guess);
  _positiveBranch = omc_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_frAxleDW_rightWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData, tmp1, *((base_array_t*)_e), tmp2, *((base_array_t*)_r_a), *((base_array_t*)_r_b));
  out_positiveBranch = mmc_mk_icon(_positiveBranch);
  return out_positiveBranch;
}

DLLDirection
modelica_boolean omc_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_rrAxleDW_leftWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData_t *threadData, modelica_real _L, real_array _e, modelica_real _angle_guess, real_array _r_a, real_array _r_b)
{
  modelica_boolean _positiveBranch;
  modelica_real _e_r_a;
  modelica_real _e_r_b;
  modelica_real _A;
  modelica_real _B;
  modelica_real _C;
  modelica_real _k1;
  modelica_real _k2;
  modelica_real _k1a;
  modelica_real _k1b;
  modelica_real _kcos1;
  modelica_real _ksin1;
  modelica_real _kcos2;
  modelica_real _ksin2;
  modelica_real _angle1;
  modelica_real _angle2;
  static int tmp1 = 0;
  modelica_real tmp2;
  _tailrecursive: OMC_LABEL_UNUSED
  // _positiveBranch has no default value.
  // _e_r_a has no default value.
  // _e_r_b has no default value.
  // _A has no default value.
  // _B has no default value.
  // _C has no default value.
  // _k1 has no default value.
  // _k2 has no default value.
  // _k1a has no default value.
  // _k1b has no default value.
  // _kcos1 has no default value.
  // _ksin1 has no default value.
  // _kcos2 has no default value.
  // _ksin2 has no default value.
  // _angle1 has no default value.
  // _angle2 has no default value.
  _e_r_a = (real_array_get(_e, 1, ((modelica_integer) 1))) * (real_array_get(_r_a, 1, ((modelica_integer) 1))) + (real_array_get(_e, 1, ((modelica_integer) 2))) * (real_array_get(_r_a, 1, ((modelica_integer) 2))) + (real_array_get(_e, 1, ((modelica_integer) 3))) * (real_array_get(_r_a, 1, ((modelica_integer) 3)));

  _e_r_b = (real_array_get(_e, 1, ((modelica_integer) 1))) * (real_array_get(_r_b, 1, ((modelica_integer) 1))) + (real_array_get(_e, 1, ((modelica_integer) 2))) * (real_array_get(_r_b, 1, ((modelica_integer) 2))) + (real_array_get(_e, 1, ((modelica_integer) 3))) * (real_array_get(_r_b, 1, ((modelica_integer) 3)));

  _A = (-((2.0) * ((real_array_get(_r_b, 1, ((modelica_integer) 1))) * (real_array_get(_r_a, 1, ((modelica_integer) 1))) + (real_array_get(_r_b, 1, ((modelica_integer) 2))) * (real_array_get(_r_a, 1, ((modelica_integer) 2))) + (real_array_get(_r_b, 1, ((modelica_integer) 3))) * (real_array_get(_r_a, 1, ((modelica_integer) 3))) - ((_e_r_b) * (_e_r_a)))));

  _B = ((2.0) * (real_array_get(_r_b, 1, ((modelica_integer) 1)))) * ((real_array_get(_e, 1, ((modelica_integer) 2))) * (real_array_get(_r_a, 1, ((modelica_integer) 3))) - ((real_array_get(_e, 1, ((modelica_integer) 3))) * (real_array_get(_r_a, 1, ((modelica_integer) 2))))) + ((2.0) * (real_array_get(_r_b, 1, ((modelica_integer) 2)))) * ((real_array_get(_e, 1, ((modelica_integer) 3))) * (real_array_get(_r_a, 1, ((modelica_integer) 1))) - ((real_array_get(_e, 1, ((modelica_integer) 1))) * (real_array_get(_r_a, 1, ((modelica_integer) 3))))) + ((2.0) * (real_array_get(_r_b, 1, ((modelica_integer) 3)))) * ((real_array_get(_e, 1, ((modelica_integer) 1))) * (real_array_get(_r_a, 1, ((modelica_integer) 2))) - ((real_array_get(_e, 1, ((modelica_integer) 2))) * (real_array_get(_r_a, 1, ((modelica_integer) 1)))));

  _C = (real_array_get(_r_a, 1, ((modelica_integer) 1))) * (real_array_get(_r_a, 1, ((modelica_integer) 1))) + (real_array_get(_r_a, 1, ((modelica_integer) 2))) * (real_array_get(_r_a, 1, ((modelica_integer) 2))) + (real_array_get(_r_a, 1, ((modelica_integer) 3))) * (real_array_get(_r_a, 1, ((modelica_integer) 3))) + (real_array_get(_r_b, 1, ((modelica_integer) 1))) * (real_array_get(_r_b, 1, ((modelica_integer) 1))) + (real_array_get(_r_b, 1, ((modelica_integer) 2))) * (real_array_get(_r_b, 1, ((modelica_integer) 2))) + (real_array_get(_r_b, 1, ((modelica_integer) 3))) * (real_array_get(_r_b, 1, ((modelica_integer) 3))) - ((_L) * (_L)) - (((2.0) * (_e_r_b)) * (_e_r_a));

  _k1 = (_A) * (_A) + (_B) * (_B);

  _k1a = _k1 - ((_C) * (_C));

  {
    if(!(_k1a > 1e-10))
    {
      {
        FILE_INFO info = {"/home/rhorvath/.openmodelica/libraries/Modelica 4.1.0+maint.om/Mechanics/MultiBody/Joints/Internal/RevoluteWithLengthConstraint.mo",160,5,172,3,0};
        omc_assert(threadData, info, MMC_STRINGDATA(_OMC_LIT14));
      }
    }
  }

  _k1b = fmax(_k1a,1e-12);

  tmp2 = _k1b;
  if(!(tmp2 >= 0.0))
  {
    FILE_INFO info = {"",0,0,0,0,0};
    omc_assert(threadData, info, "Model error: Argument of sqrt(k1b) was %g should be >= 0", tmp2);
  }
  _k2 = sqrt(tmp2);

  _kcos1 = (_B) * (_k2) - ((_A) * (_C));

  _ksin1 = (-((_B) * (_C) + (_A) * (_k2)));

  _angle1 = omc_Modelica_Math_atan2(threadData, _ksin1, _kcos1);

  _kcos2 = (-((_A) * (_C) + (_B) * (_k2)));

  _ksin2 = (_A) * (_k2) - ((_B) * (_C));

  _angle2 = omc_Modelica_Math_atan2(threadData, _ksin2, _kcos2);

  if((fabs(_angle1 - _angle_guess) <= fabs(_angle2 - _angle_guess)))
  {
    _positiveBranch = 1 /* true */;
  }
  else
  {
    _positiveBranch = 0 /* false */;
  }
  _return: OMC_LABEL_UNUSED
  return _positiveBranch;
}
modelica_metatype boxptr_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_rrAxleDW_leftWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData_t *threadData, modelica_metatype _L, modelica_metatype _e, modelica_metatype _angle_guess, modelica_metatype _r_a, modelica_metatype _r_b)
{
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_boolean _positiveBranch;
  modelica_metatype out_positiveBranch;
  tmp1 = mmc_unbox_real(_L);
  tmp2 = mmc_unbox_real(_angle_guess);
  _positiveBranch = omc_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_rrAxleDW_leftWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData, tmp1, *((base_array_t*)_e), tmp2, *((base_array_t*)_r_a), *((base_array_t*)_r_b));
  out_positiveBranch = mmc_mk_icon(_positiveBranch);
  return out_positiveBranch;
}

DLLDirection
modelica_boolean omc_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_rrAxleDW_rightWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData_t *threadData, modelica_real _L, real_array _e, modelica_real _angle_guess, real_array _r_a, real_array _r_b)
{
  modelica_boolean _positiveBranch;
  modelica_real _e_r_a;
  modelica_real _e_r_b;
  modelica_real _A;
  modelica_real _B;
  modelica_real _C;
  modelica_real _k1;
  modelica_real _k2;
  modelica_real _k1a;
  modelica_real _k1b;
  modelica_real _kcos1;
  modelica_real _ksin1;
  modelica_real _kcos2;
  modelica_real _ksin2;
  modelica_real _angle1;
  modelica_real _angle2;
  static int tmp1 = 0;
  modelica_real tmp2;
  _tailrecursive: OMC_LABEL_UNUSED
  // _positiveBranch has no default value.
  // _e_r_a has no default value.
  // _e_r_b has no default value.
  // _A has no default value.
  // _B has no default value.
  // _C has no default value.
  // _k1 has no default value.
  // _k2 has no default value.
  // _k1a has no default value.
  // _k1b has no default value.
  // _kcos1 has no default value.
  // _ksin1 has no default value.
  // _kcos2 has no default value.
  // _ksin2 has no default value.
  // _angle1 has no default value.
  // _angle2 has no default value.
  _e_r_a = (real_array_get(_e, 1, ((modelica_integer) 1))) * (real_array_get(_r_a, 1, ((modelica_integer) 1))) + (real_array_get(_e, 1, ((modelica_integer) 2))) * (real_array_get(_r_a, 1, ((modelica_integer) 2))) + (real_array_get(_e, 1, ((modelica_integer) 3))) * (real_array_get(_r_a, 1, ((modelica_integer) 3)));

  _e_r_b = (real_array_get(_e, 1, ((modelica_integer) 1))) * (real_array_get(_r_b, 1, ((modelica_integer) 1))) + (real_array_get(_e, 1, ((modelica_integer) 2))) * (real_array_get(_r_b, 1, ((modelica_integer) 2))) + (real_array_get(_e, 1, ((modelica_integer) 3))) * (real_array_get(_r_b, 1, ((modelica_integer) 3)));

  _A = (-((2.0) * ((real_array_get(_r_b, 1, ((modelica_integer) 1))) * (real_array_get(_r_a, 1, ((modelica_integer) 1))) + (real_array_get(_r_b, 1, ((modelica_integer) 2))) * (real_array_get(_r_a, 1, ((modelica_integer) 2))) + (real_array_get(_r_b, 1, ((modelica_integer) 3))) * (real_array_get(_r_a, 1, ((modelica_integer) 3))) - ((_e_r_b) * (_e_r_a)))));

  _B = ((2.0) * (real_array_get(_r_b, 1, ((modelica_integer) 1)))) * ((real_array_get(_e, 1, ((modelica_integer) 2))) * (real_array_get(_r_a, 1, ((modelica_integer) 3))) - ((real_array_get(_e, 1, ((modelica_integer) 3))) * (real_array_get(_r_a, 1, ((modelica_integer) 2))))) + ((2.0) * (real_array_get(_r_b, 1, ((modelica_integer) 2)))) * ((real_array_get(_e, 1, ((modelica_integer) 3))) * (real_array_get(_r_a, 1, ((modelica_integer) 1))) - ((real_array_get(_e, 1, ((modelica_integer) 1))) * (real_array_get(_r_a, 1, ((modelica_integer) 3))))) + ((2.0) * (real_array_get(_r_b, 1, ((modelica_integer) 3)))) * ((real_array_get(_e, 1, ((modelica_integer) 1))) * (real_array_get(_r_a, 1, ((modelica_integer) 2))) - ((real_array_get(_e, 1, ((modelica_integer) 2))) * (real_array_get(_r_a, 1, ((modelica_integer) 1)))));

  _C = (real_array_get(_r_a, 1, ((modelica_integer) 1))) * (real_array_get(_r_a, 1, ((modelica_integer) 1))) + (real_array_get(_r_a, 1, ((modelica_integer) 2))) * (real_array_get(_r_a, 1, ((modelica_integer) 2))) + (real_array_get(_r_a, 1, ((modelica_integer) 3))) * (real_array_get(_r_a, 1, ((modelica_integer) 3))) + (real_array_get(_r_b, 1, ((modelica_integer) 1))) * (real_array_get(_r_b, 1, ((modelica_integer) 1))) + (real_array_get(_r_b, 1, ((modelica_integer) 2))) * (real_array_get(_r_b, 1, ((modelica_integer) 2))) + (real_array_get(_r_b, 1, ((modelica_integer) 3))) * (real_array_get(_r_b, 1, ((modelica_integer) 3))) - ((_L) * (_L)) - (((2.0) * (_e_r_b)) * (_e_r_a));

  _k1 = (_A) * (_A) + (_B) * (_B);

  _k1a = _k1 - ((_C) * (_C));

  {
    if(!(_k1a > 1e-10))
    {
      {
        FILE_INFO info = {"/home/rhorvath/.openmodelica/libraries/Modelica 4.1.0+maint.om/Mechanics/MultiBody/Joints/Internal/RevoluteWithLengthConstraint.mo",160,5,172,3,0};
        omc_assert(threadData, info, MMC_STRINGDATA(_OMC_LIT14));
      }
    }
  }

  _k1b = fmax(_k1a,1e-12);

  tmp2 = _k1b;
  if(!(tmp2 >= 0.0))
  {
    FILE_INFO info = {"",0,0,0,0,0};
    omc_assert(threadData, info, "Model error: Argument of sqrt(k1b) was %g should be >= 0", tmp2);
  }
  _k2 = sqrt(tmp2);

  _kcos1 = (_B) * (_k2) - ((_A) * (_C));

  _ksin1 = (-((_B) * (_C) + (_A) * (_k2)));

  _angle1 = omc_Modelica_Math_atan2(threadData, _ksin1, _kcos1);

  _kcos2 = (-((_A) * (_C) + (_B) * (_k2)));

  _ksin2 = (_A) * (_k2) - ((_B) * (_C));

  _angle2 = omc_Modelica_Math_atan2(threadData, _ksin2, _kcos2);

  if((fabs(_angle1 - _angle_guess) <= fabs(_angle2 - _angle_guess)))
  {
    _positiveBranch = 1 /* true */;
  }
  else
  {
    _positiveBranch = 0 /* false */;
  }
  _return: OMC_LABEL_UNUSED
  return _positiveBranch;
}
modelica_metatype boxptr_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_rrAxleDW_rightWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData_t *threadData, modelica_metatype _L, modelica_metatype _e, modelica_metatype _angle_guess, modelica_metatype _r_a, modelica_metatype _r_b)
{
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_boolean _positiveBranch;
  modelica_metatype out_positiveBranch;
  tmp1 = mmc_unbox_real(_L);
  tmp2 = mmc_unbox_real(_angle_guess);
  _positiveBranch = omc_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_rrAxleDW_rightWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData, tmp1, *((base_array_t*)_e), tmp2, *((base_array_t*)_r_a), *((base_array_t*)_r_b));
  out_positiveBranch = mmc_mk_icon(_positiveBranch);
  return out_positiveBranch;
}

DLLDirection
modelica_real omc_BobLib_Experiments_Standards_VehicleSim_motor_motor_interp1(threadData_t *threadData, real_array _tbl, modelica_real _xq)
{
  modelica_real _yq;
  real_array tmp1;
  index_spec_t tmp2;
  real_array tmp3;
  index_spec_t tmp4;
  _tailrecursive: OMC_LABEL_UNUSED
  // _yq has no default value.
  create_index_spec(&tmp2, 2, (modelica_integer)(1), (int*)0, 'W', (modelica_integer)(0), make_index_array(1, (modelica_integer) ((modelica_integer) 1)), 'S');
  index_alloc_real_array(&_tbl, &tmp2, &tmp1);
  create_index_spec(&tmp4, 2, (modelica_integer)(1), (int*)0, 'W', (modelica_integer)(0), make_index_array(1, (modelica_integer) ((modelica_integer) 2)), 'S');
  index_alloc_real_array(&_tbl, &tmp4, &tmp3);
  _yq = omc_Modelica_Math_Vectors_interpolate(threadData, tmp1, tmp3, _xq, ((modelica_integer) 1), NULL);
  _return: OMC_LABEL_UNUSED
  return _yq;
}
modelica_metatype boxptr_BobLib_Experiments_Standards_VehicleSim_motor_motor_interp1(threadData_t *threadData, modelica_metatype _tbl, modelica_metatype _xq)
{
  modelica_real tmp1;
  modelica_real _yq;
  modelica_metatype out_yq;
  tmp1 = mmc_unbox_real(_xq);
  _yq = omc_BobLib_Experiments_Standards_VehicleSim_motor_motor_interp1(threadData, *((base_array_t*)_tbl), tmp1);
  out_yq = mmc_mk_rcon(_yq);
  return out_yq;
}

BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record(threadData_t *threadData, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord omc_setup, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord omc_relaxation, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord omc_fxPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord omc_fxCombined, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord omc_fyPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord omc_fyCombined, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord omc_mxPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord omc_mxCombined, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord omc_myPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord omc_myCombined, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord omc_mzPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord omc_mzCombined)
{
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record tmp1;
  tmp1._setup = omc_setup;
  tmp1._relaxation = omc_relaxation;
  tmp1._fxPure = omc_fxPure;
  tmp1._fxCombined = omc_fxCombined;
  tmp1._fyPure = omc_fyPure;
  tmp1._fyCombined = omc_fyCombined;
  tmp1._mxPure = omc_mxPure;
  tmp1._mxCombined = omc_mxCombined;
  tmp1._myPure = omc_myPure;
  tmp1._myCombined = omc_myCombined;
  tmp1._mzPure = omc_mzPure;
  tmp1._mzCombined = omc_mzCombined;
  return tmp1;
}

modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record(threadData_t *threadData, modelica_metatype _setup, modelica_metatype _relaxation, modelica_metatype _fxPure, modelica_metatype _fxCombined, modelica_metatype _fyPure, modelica_metatype _fyCombined, modelica_metatype _mxPure, modelica_metatype _mxCombined, modelica_metatype _myPure, modelica_metatype _myCombined, modelica_metatype _mzPure, modelica_metatype _mzCombined)
{
  return mmc_mk_box13(3, &BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record__desc, _setup, _relaxation, _fxPure, _fxCombined, _fyPure, _fyCombined, _mxPure, _mxCombined, _myPure, _myCombined, _mzPure, _mzCombined);
}

BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord(threadData_t *threadData, modelica_real omc_FNOMIN, modelica_real omc_UNLOADED_RADIUS, modelica_real omc_LFZO, modelica_real omc_PTX1, modelica_real omc_PTX2, modelica_real omc_PTX3, modelica_real omc_PTY1, modelica_real omc_PTY2, modelica_real omc_PKY3, modelica_real omc_LSGKP, modelica_real omc_LSGAL)
{
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord tmp1;
  tmp1._FNOMIN = omc_FNOMIN;
  tmp1._UNLOADED_RADIUS = omc_UNLOADED_RADIUS;
  tmp1._LFZO = omc_LFZO;
  tmp1._PTX1 = omc_PTX1;
  tmp1._PTX2 = omc_PTX2;
  tmp1._PTX3 = omc_PTX3;
  tmp1._PTY1 = omc_PTY1;
  tmp1._PTY2 = omc_PTY2;
  tmp1._PKY3 = omc_PKY3;
  tmp1._LSGKP = omc_LSGKP;
  tmp1._LSGAL = omc_LSGAL;
  return tmp1;
}

modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord(threadData_t *threadData, modelica_metatype _FNOMIN, modelica_metatype _UNLOADED_RADIUS, modelica_metatype _LFZO, modelica_metatype _PTX1, modelica_metatype _PTX2, modelica_metatype _PTX3, modelica_metatype _PTY1, modelica_metatype _PTY2, modelica_metatype _PKY3, modelica_metatype _LSGKP, modelica_metatype _LSGAL)
{
  return mmc_mk_box12(3, &BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord__desc, _FNOMIN, _UNLOADED_RADIUS, _LFZO, _PTX1, _PTX2, _PTX3, _PTY1, _PTY2, _PKY3, _LSGKP, _LSGAL);
}

BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord(threadData_t *threadData, modelica_real omc_FNOMIN, modelica_real omc_FZMIN, modelica_real omc_FZMAX, modelica_real omc_UNLOADED_RADIUS)
{
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord tmp1;
  tmp1._FNOMIN = omc_FNOMIN;
  tmp1._FZMIN = omc_FZMIN;
  tmp1._FZMAX = omc_FZMAX;
  tmp1._UNLOADED_RADIUS = omc_UNLOADED_RADIUS;
  return tmp1;
}

modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord(threadData_t *threadData, modelica_metatype _FNOMIN, modelica_metatype _FZMIN, modelica_metatype _FZMAX, modelica_metatype _UNLOADED_RADIUS)
{
  return mmc_mk_box5(3, &BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord__desc, _FNOMIN, _FZMIN, _FZMAX, _UNLOADED_RADIUS);
}

BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord(threadData_t *threadData, modelica_real omc_RBX1, modelica_real omc_RBX2, modelica_real omc_RCX1, modelica_real omc_REX1, modelica_real omc_REX2, modelica_real omc_RHX1)
{
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord tmp1;
  tmp1._RBX1 = omc_RBX1;
  tmp1._RBX2 = omc_RBX2;
  tmp1._RCX1 = omc_RCX1;
  tmp1._REX1 = omc_REX1;
  tmp1._REX2 = omc_REX2;
  tmp1._RHX1 = omc_RHX1;
  return tmp1;
}

modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord(threadData_t *threadData, modelica_metatype _RBX1, modelica_metatype _RBX2, modelica_metatype _RCX1, modelica_metatype _REX1, modelica_metatype _REX2, modelica_metatype _RHX1)
{
  return mmc_mk_box7(3, &BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord__desc, _RBX1, _RBX2, _RCX1, _REX1, _REX2, _RHX1);
}

BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord(threadData_t *threadData, modelica_real omc_RBY1, modelica_real omc_RBY2, modelica_real omc_RBY3, modelica_real omc_RCY1, modelica_real omc_REY1, modelica_real omc_REY2, modelica_real omc_RHY1, modelica_real omc_RHY2, modelica_real omc_RVY1, modelica_real omc_RVY2, modelica_real omc_RVY3, modelica_real omc_RVY4, modelica_real omc_RVY5, modelica_real omc_RVY6)
{
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord tmp1;
  tmp1._RBY1 = omc_RBY1;
  tmp1._RBY2 = omc_RBY2;
  tmp1._RBY3 = omc_RBY3;
  tmp1._RCY1 = omc_RCY1;
  tmp1._REY1 = omc_REY1;
  tmp1._REY2 = omc_REY2;
  tmp1._RHY1 = omc_RHY1;
  tmp1._RHY2 = omc_RHY2;
  tmp1._RVY1 = omc_RVY1;
  tmp1._RVY2 = omc_RVY2;
  tmp1._RVY3 = omc_RVY3;
  tmp1._RVY4 = omc_RVY4;
  tmp1._RVY5 = omc_RVY5;
  tmp1._RVY6 = omc_RVY6;
  return tmp1;
}

modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord(threadData_t *threadData, modelica_metatype _RBY1, modelica_metatype _RBY2, modelica_metatype _RBY3, modelica_metatype _RCY1, modelica_metatype _REY1, modelica_metatype _REY2, modelica_metatype _RHY1, modelica_metatype _RHY2, modelica_metatype _RVY1, modelica_metatype _RVY2, modelica_metatype _RVY3, modelica_metatype _RVY4, modelica_metatype _RVY5, modelica_metatype _RVY6)
{
  return mmc_mk_box15(3, &BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord__desc, _RBY1, _RBY2, _RBY3, _RCY1, _REY1, _REY2, _RHY1, _RHY2, _RVY1, _RVY2, _RVY3, _RVY4, _RVY5, _RVY6);
}

BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord(threadData_t *threadData)
{
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord tmp1;
  return tmp1;
}

modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord(threadData_t *threadData)
{
  return mmc_mk_box1(3, &BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord__desc);
}

BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord(threadData_t *threadData)
{
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord tmp1;
  return tmp1;
}

modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord(threadData_t *threadData)
{
  return mmc_mk_box1(3, &BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord__desc);
}

BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord(threadData_t *threadData, modelica_real omc_SSZ1, modelica_real omc_SSZ2, modelica_real omc_SSZ3, modelica_real omc_SSZ4, modelica_real omc_RVY1, modelica_real omc_RVY2, modelica_real omc_RVY3, modelica_real omc_RVY4, modelica_real omc_RVY5, modelica_real omc_RVY6, modelica_real omc_LS, modelica_real omc_LVYKA)
{
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord tmp1;
  tmp1._SSZ1 = omc_SSZ1;
  tmp1._SSZ2 = omc_SSZ2;
  tmp1._SSZ3 = omc_SSZ3;
  tmp1._SSZ4 = omc_SSZ4;
  tmp1._RVY1 = omc_RVY1;
  tmp1._RVY2 = omc_RVY2;
  tmp1._RVY3 = omc_RVY3;
  tmp1._RVY4 = omc_RVY4;
  tmp1._RVY5 = omc_RVY5;
  tmp1._RVY6 = omc_RVY6;
  tmp1._LS = omc_LS;
  tmp1._LVYKA = omc_LVYKA;
  return tmp1;
}

modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord(threadData_t *threadData, modelica_metatype _SSZ1, modelica_metatype _SSZ2, modelica_metatype _SSZ3, modelica_metatype _SSZ4, modelica_metatype _RVY1, modelica_metatype _RVY2, modelica_metatype _RVY3, modelica_metatype _RVY4, modelica_metatype _RVY5, modelica_metatype _RVY6, modelica_metatype _LS, modelica_metatype _LVYKA)
{
  return mmc_mk_box13(3, &BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord__desc, _SSZ1, _SSZ2, _SSZ3, _SSZ4, _RVY1, _RVY2, _RVY3, _RVY4, _RVY5, _RVY6, _LS, _LVYKA);
}

BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord(threadData_t *threadData, modelica_real omc_LGAX, modelica_real omc_LFZO, modelica_real omc_PCX1, modelica_real omc_PDX1, modelica_real omc_PDX2, modelica_real omc_PDX3, modelica_real omc_PKX1, modelica_real omc_PKX2, modelica_real omc_PKX3, modelica_real omc_PHX1, modelica_real omc_PHX2, modelica_real omc_PVX1, modelica_real omc_PVX2, modelica_real omc_PEX1, modelica_real omc_PEX2, modelica_real omc_PEX3, modelica_real omc_PEX4, modelica_real omc_LCX, modelica_real omc_LMUX, modelica_real omc_LKX, modelica_real omc_LHX, modelica_real omc_LVX, modelica_real omc_LEX, modelica_real omc_LXAL)
{
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord tmp1;
  tmp1._LGAX = omc_LGAX;
  tmp1._LFZO = omc_LFZO;
  tmp1._PCX1 = omc_PCX1;
  tmp1._PDX1 = omc_PDX1;
  tmp1._PDX2 = omc_PDX2;
  tmp1._PDX3 = omc_PDX3;
  tmp1._PKX1 = omc_PKX1;
  tmp1._PKX2 = omc_PKX2;
  tmp1._PKX3 = omc_PKX3;
  tmp1._PHX1 = omc_PHX1;
  tmp1._PHX2 = omc_PHX2;
  tmp1._PVX1 = omc_PVX1;
  tmp1._PVX2 = omc_PVX2;
  tmp1._PEX1 = omc_PEX1;
  tmp1._PEX2 = omc_PEX2;
  tmp1._PEX3 = omc_PEX3;
  tmp1._PEX4 = omc_PEX4;
  tmp1._LCX = omc_LCX;
  tmp1._LMUX = omc_LMUX;
  tmp1._LKX = omc_LKX;
  tmp1._LHX = omc_LHX;
  tmp1._LVX = omc_LVX;
  tmp1._LEX = omc_LEX;
  tmp1._LXAL = omc_LXAL;
  return tmp1;
}

modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord(threadData_t *threadData, modelica_metatype _LGAX, modelica_metatype _LFZO, modelica_metatype _PCX1, modelica_metatype _PDX1, modelica_metatype _PDX2, modelica_metatype _PDX3, modelica_metatype _PKX1, modelica_metatype _PKX2, modelica_metatype _PKX3, modelica_metatype _PHX1, modelica_metatype _PHX2, modelica_metatype _PVX1, modelica_metatype _PVX2, modelica_metatype _PEX1, modelica_metatype _PEX2, modelica_metatype _PEX3, modelica_metatype _PEX4, modelica_metatype _LCX, modelica_metatype _LMUX, modelica_metatype _LKX, modelica_metatype _LHX, modelica_metatype _LVX, modelica_metatype _LEX, modelica_metatype _LXAL)
{
  return mmc_mk_box(25, 3, &BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord__desc, _LGAX, _LFZO, _PCX1, _PDX1, _PDX2, _PDX3, _PKX1, _PKX2, _PKX3, _PHX1, _PHX2, _PVX1, _PVX2, _PEX1, _PEX2, _PEX3, _PEX4, _LCX, _LMUX, _LKX, _LHX, _LVX, _LEX, _LXAL);
}

BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord(threadData_t *threadData, modelica_real omc_LFZO, modelica_real omc_LGAY, modelica_real omc_PCY1, modelica_real omc_PDY1, modelica_real omc_PDY2, modelica_real omc_PDY3, modelica_real omc_PKY1, modelica_real omc_PKY2, modelica_real omc_PKY3, modelica_real omc_PHY1, modelica_real omc_PHY2, modelica_real omc_PHY3, modelica_real omc_PVY1, modelica_real omc_PVY2, modelica_real omc_PVY3, modelica_real omc_PVY4, modelica_real omc_PEY1, modelica_real omc_PEY2, modelica_real omc_PEY3, modelica_real omc_PEY4, modelica_real omc_LCY, modelica_real omc_LMUY, modelica_real omc_LEY, modelica_real omc_LKY, modelica_real omc_LHY, modelica_real omc_LVY, modelica_real omc_LYKA, modelica_real omc_LVYKA)
{
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord tmp1;
  tmp1._LFZO = omc_LFZO;
  tmp1._LGAY = omc_LGAY;
  tmp1._PCY1 = omc_PCY1;
  tmp1._PDY1 = omc_PDY1;
  tmp1._PDY2 = omc_PDY2;
  tmp1._PDY3 = omc_PDY3;
  tmp1._PKY1 = omc_PKY1;
  tmp1._PKY2 = omc_PKY2;
  tmp1._PKY3 = omc_PKY3;
  tmp1._PHY1 = omc_PHY1;
  tmp1._PHY2 = omc_PHY2;
  tmp1._PHY3 = omc_PHY3;
  tmp1._PVY1 = omc_PVY1;
  tmp1._PVY2 = omc_PVY2;
  tmp1._PVY3 = omc_PVY3;
  tmp1._PVY4 = omc_PVY4;
  tmp1._PEY1 = omc_PEY1;
  tmp1._PEY2 = omc_PEY2;
  tmp1._PEY3 = omc_PEY3;
  tmp1._PEY4 = omc_PEY4;
  tmp1._LCY = omc_LCY;
  tmp1._LMUY = omc_LMUY;
  tmp1._LEY = omc_LEY;
  tmp1._LKY = omc_LKY;
  tmp1._LHY = omc_LHY;
  tmp1._LVY = omc_LVY;
  tmp1._LYKA = omc_LYKA;
  tmp1._LVYKA = omc_LVYKA;
  return tmp1;
}

modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord(threadData_t *threadData, modelica_metatype _LFZO, modelica_metatype _LGAY, modelica_metatype _PCY1, modelica_metatype _PDY1, modelica_metatype _PDY2, modelica_metatype _PDY3, modelica_metatype _PKY1, modelica_metatype _PKY2, modelica_metatype _PKY3, modelica_metatype _PHY1, modelica_metatype _PHY2, modelica_metatype _PHY3, modelica_metatype _PVY1, modelica_metatype _PVY2, modelica_metatype _PVY3, modelica_metatype _PVY4, modelica_metatype _PEY1, modelica_metatype _PEY2, modelica_metatype _PEY3, modelica_metatype _PEY4, modelica_metatype _LCY, modelica_metatype _LMUY, modelica_metatype _LEY, modelica_metatype _LKY, modelica_metatype _LHY, modelica_metatype _LVY, modelica_metatype _LYKA, modelica_metatype _LVYKA)
{
  return mmc_mk_box(29, 3, &BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord__desc, _LFZO, _LGAY, _PCY1, _PDY1, _PDY2, _PDY3, _PKY1, _PKY2, _PKY3, _PHY1, _PHY2, _PHY3, _PVY1, _PVY2, _PVY3, _PVY4, _PEY1, _PEY2, _PEY3, _PEY4, _LCY, _LMUY, _LEY, _LKY, _LHY, _LVY, _LYKA, _LVYKA);
}

BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord(threadData_t *threadData, modelica_real omc_QSX1, modelica_real omc_QSX2, modelica_real omc_QSX3, modelica_real omc_LMX, modelica_real omc_LVMX)
{
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord tmp1;
  tmp1._QSX1 = omc_QSX1;
  tmp1._QSX2 = omc_QSX2;
  tmp1._QSX3 = omc_QSX3;
  tmp1._LMX = omc_LMX;
  tmp1._LVMX = omc_LVMX;
  return tmp1;
}

modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord(threadData_t *threadData, modelica_metatype _QSX1, modelica_metatype _QSX2, modelica_metatype _QSX3, modelica_metatype _LMX, modelica_metatype _LVMX)
{
  return mmc_mk_box6(3, &BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord__desc, _QSX1, _QSX2, _QSX3, _LMX, _LVMX);
}

BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord(threadData_t *threadData, modelica_real omc_QSY1, modelica_real omc_QSY2, modelica_real omc_QSY3, modelica_real omc_QSY4, modelica_real omc_Vref, modelica_real omc_LMY)
{
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord tmp1;
  tmp1._QSY1 = omc_QSY1;
  tmp1._QSY2 = omc_QSY2;
  tmp1._QSY3 = omc_QSY3;
  tmp1._QSY4 = omc_QSY4;
  tmp1._Vref = omc_Vref;
  tmp1._LMY = omc_LMY;
  return tmp1;
}

modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord(threadData_t *threadData, modelica_metatype _QSY1, modelica_metatype _QSY2, modelica_metatype _QSY3, modelica_metatype _QSY4, modelica_metatype _Vref, modelica_metatype _LMY)
{
  return mmc_mk_box7(3, &BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord__desc, _QSY1, _QSY2, _QSY3, _QSY4, _Vref, _LMY);
}

BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord(threadData_t *threadData, modelica_real omc_QBZ1, modelica_real omc_QBZ2, modelica_real omc_QBZ3, modelica_real omc_QBZ4, modelica_real omc_QBZ5, modelica_real omc_QCZ1, modelica_real omc_QDZ1, modelica_real omc_QDZ2, modelica_real omc_QDZ3, modelica_real omc_QDZ4, modelica_real omc_QEZ1, modelica_real omc_QEZ2, modelica_real omc_QEZ3, modelica_real omc_QEZ4, modelica_real omc_QEZ5, modelica_real omc_QHZ1, modelica_real omc_QHZ2, modelica_real omc_QHZ3, modelica_real omc_QHZ4, modelica_real omc_QBZ9, modelica_real omc_QBZ10, modelica_real omc_QDZ6, modelica_real omc_QDZ7, modelica_real omc_QDZ8, modelica_real omc_QDZ9, modelica_real omc_LTR, modelica_real omc_LRES, modelica_real omc_LKY, modelica_real omc_LMUY, modelica_real omc_LGAZ)
{
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord tmp1;
  tmp1._QBZ1 = omc_QBZ1;
  tmp1._QBZ2 = omc_QBZ2;
  tmp1._QBZ3 = omc_QBZ3;
  tmp1._QBZ4 = omc_QBZ4;
  tmp1._QBZ5 = omc_QBZ5;
  tmp1._QCZ1 = omc_QCZ1;
  tmp1._QDZ1 = omc_QDZ1;
  tmp1._QDZ2 = omc_QDZ2;
  tmp1._QDZ3 = omc_QDZ3;
  tmp1._QDZ4 = omc_QDZ4;
  tmp1._QEZ1 = omc_QEZ1;
  tmp1._QEZ2 = omc_QEZ2;
  tmp1._QEZ3 = omc_QEZ3;
  tmp1._QEZ4 = omc_QEZ4;
  tmp1._QEZ5 = omc_QEZ5;
  tmp1._QHZ1 = omc_QHZ1;
  tmp1._QHZ2 = omc_QHZ2;
  tmp1._QHZ3 = omc_QHZ3;
  tmp1._QHZ4 = omc_QHZ4;
  tmp1._QBZ9 = omc_QBZ9;
  tmp1._QBZ10 = omc_QBZ10;
  tmp1._QDZ6 = omc_QDZ6;
  tmp1._QDZ7 = omc_QDZ7;
  tmp1._QDZ8 = omc_QDZ8;
  tmp1._QDZ9 = omc_QDZ9;
  tmp1._LTR = omc_LTR;
  tmp1._LRES = omc_LRES;
  tmp1._LKY = omc_LKY;
  tmp1._LMUY = omc_LMUY;
  tmp1._LGAZ = omc_LGAZ;
  return tmp1;
}

modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord(threadData_t *threadData, modelica_metatype _QBZ1, modelica_metatype _QBZ2, modelica_metatype _QBZ3, modelica_metatype _QBZ4, modelica_metatype _QBZ5, modelica_metatype _QCZ1, modelica_metatype _QDZ1, modelica_metatype _QDZ2, modelica_metatype _QDZ3, modelica_metatype _QDZ4, modelica_metatype _QEZ1, modelica_metatype _QEZ2, modelica_metatype _QEZ3, modelica_metatype _QEZ4, modelica_metatype _QEZ5, modelica_metatype _QHZ1, modelica_metatype _QHZ2, modelica_metatype _QHZ3, modelica_metatype _QHZ4, modelica_metatype _QBZ9, modelica_metatype _QBZ10, modelica_metatype _QDZ6, modelica_metatype _QDZ7, modelica_metatype _QDZ8, modelica_metatype _QDZ9, modelica_metatype _LTR, modelica_metatype _LRES, modelica_metatype _LKY, modelica_metatype _LMUY, modelica_metatype _LGAZ)
{
  return mmc_mk_box(31, 3, &BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord__desc, _QBZ1, _QBZ2, _QBZ3, _QBZ4, _QBZ5, _QCZ1, _QDZ1, _QDZ2, _QDZ3, _QDZ4, _QEZ1, _QEZ2, _QEZ3, _QEZ4, _QEZ5, _QHZ1, _QHZ2, _QHZ3, _QHZ4, _QBZ9, _QBZ10, _QDZ6, _QDZ7, _QDZ8, _QDZ9, _LTR, _LRES, _LKY, _LMUY, _LGAZ);
}

DLLDirection
real_array omc_BobLib_Utilities_Math_Tensor_mirrorXZ(threadData_t *threadData, real_array _T)
{
  real_array _T_m;
  real_array _R;
  real_array tmp1;
  real_array tmp2;
  real_array tmp3;
  real_array tmp4;
  _tailrecursive: OMC_LABEL_UNUSED
  alloc_real_array(&(_T_m), 2, (_index_t)3, (_index_t)3); // _T_m has no default value.
  alloc_real_array(&(_R), 2, (_index_t)3, (_index_t)3);
  real_array_copy_data(_OMC_LIT15, _R);
  
  array_alloc_scalar_real_array(&tmp2, 3, (modelica_real)((real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 1))) + (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 1))) + (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 1)))) * (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 1))) + ((real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 2))) + (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 2))) + (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 2)))) * (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 2))) + ((real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 3))) + (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 3))) + (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 3)))) * (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 3))), (modelica_real)((real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 1))) + (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 1))) + (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 1)))) * (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 1))) + ((real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 2))) + (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 2))) + (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 2)))) * (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 2))) + ((real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 3))) + (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 3))) + (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 3)))) * (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 3))), (modelica_real)((real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 1))) + (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 1))) + (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 1)))) * (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 1))) + ((real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 2))) + (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 2))) + (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 2)))) * (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 2))) + ((real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 3))) + (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 3))) + (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 3)))) * (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 3))));
  array_alloc_scalar_real_array(&tmp3, 3, (modelica_real)((real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 1))) + (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 1))) + (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 1)))) * (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 1))) + ((real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 2))) + (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 2))) + (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 2)))) * (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 2))) + ((real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 3))) + (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 3))) + (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 3)))) * (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 3))), (modelica_real)((real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 1))) + (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 1))) + (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 1)))) * (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 1))) + ((real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 2))) + (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 2))) + (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 2)))) * (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 2))) + ((real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 3))) + (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 3))) + (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 3)))) * (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 3))), (modelica_real)((real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 1))) + (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 1))) + (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 1)))) * (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 1))) + ((real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 2))) + (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 2))) + (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 2)))) * (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 2))) + ((real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 3))) + (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 3))) + (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 3)))) * (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 3))));
  array_alloc_scalar_real_array(&tmp4, 3, (modelica_real)((real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 1))) + (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 1))) + (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 1)))) * (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 1))) + ((real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 2))) + (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 2))) + (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 2)))) * (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 2))) + ((real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 3))) + (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 3))) + (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 3)))) * (real_array_get(_R, 2, ((modelica_integer) 1), ((modelica_integer) 3))), (modelica_real)((real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 1))) + (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 1))) + (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 1)))) * (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 1))) + ((real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 2))) + (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 2))) + (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 2)))) * (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 2))) + ((real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 3))) + (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 3))) + (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 3)))) * (real_array_get(_R, 2, ((modelica_integer) 2), ((modelica_integer) 3))), (modelica_real)((real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 1))) + (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 1))) + (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 1)))) * (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 1))) + ((real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 2))) + (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 2))) + (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 2)))) * (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 2))) + ((real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 1))) * (real_array_get(_T, 2, ((modelica_integer) 1), ((modelica_integer) 3))) + (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 2))) * (real_array_get(_T, 2, ((modelica_integer) 2), ((modelica_integer) 3))) + (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 3))) * (real_array_get(_T, 2, ((modelica_integer) 3), ((modelica_integer) 3)))) * (real_array_get(_R, 2, ((modelica_integer) 3), ((modelica_integer) 3))));
  array_alloc_real_array(&tmp1, 3, tmp2, tmp3, tmp4);
  real_array_copy_data(tmp1, _T_m);
  _return: OMC_LABEL_UNUSED
  return _T_m;
}
modelica_metatype boxptr_BobLib_Utilities_Math_Tensor_mirrorXZ(threadData_t *threadData, modelica_metatype _T)
{
  real_array _T_m;
  modelica_metatype out_T_m;
  _T_m = omc_BobLib_Utilities_Math_Tensor_mirrorXZ(threadData, *((base_array_t*)_T));
  out_T_m = mmc_mk_modelica_array(_T_m);
  return out_T_m;
}

DLLDirection
real_array omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData_t *threadData, real_array _r)
{
  real_array _r_m;
  _tailrecursive: OMC_LABEL_UNUSED
  alloc_real_array(&(_r_m), 1, (_index_t)3); // _r_m has no default value.
  real_array_get(_r_m, 1, ((modelica_integer) 1)) = real_array_get(_r, 1, ((modelica_integer) 1));

  real_array_get(_r_m, 1, ((modelica_integer) 2)) = (-real_array_get(_r, 1, ((modelica_integer) 2)));

  real_array_get(_r_m, 1, ((modelica_integer) 3)) = real_array_get(_r, 1, ((modelica_integer) 3));
  _return: OMC_LABEL_UNUSED
  return _r_m;
}
modelica_metatype boxptr_BobLib_Utilities_Math_Vector_mirrorXZ(threadData_t *threadData, modelica_metatype _r)
{
  real_array _r_m;
  modelica_metatype out_r_m;
  _r_m = omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, *((base_array_t*)_r));
  out_r_m = mmc_mk_modelica_array(_r_m);
  return out_r_m;
}

modelica_real omc_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmax(threadData_t *threadData, modelica_complex _tableID)
{
  void * _tableID_ext;
  double _uMax_ext;
  modelica_real _uMax;
  // _uMax has no default value.
  _tableID_ext = (void *)_tableID;
  _uMax_ext = ModelicaStandardTables_CombiTable1D_maximumAbscissa(_tableID_ext);
  _uMax = (modelica_real)_uMax_ext;
  return _uMax;
}
modelica_metatype boxptr_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmax(threadData_t *threadData, modelica_metatype _tableID)
{
  modelica_real _uMax;
  modelica_metatype out_uMax;
  _uMax = omc_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmax(threadData, _tableID);
  out_uMax = mmc_mk_rcon(_uMax);
  return out_uMax;
}

modelica_real omc_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmin(threadData_t *threadData, modelica_complex _tableID)
{
  void * _tableID_ext;
  double _uMin_ext;
  modelica_real _uMin;
  // _uMin has no default value.
  _tableID_ext = (void *)_tableID;
  _uMin_ext = ModelicaStandardTables_CombiTable1D_minimumAbscissa(_tableID_ext);
  _uMin = (modelica_real)_uMin_ext;
  return _uMin;
}
modelica_metatype boxptr_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmin(threadData_t *threadData, modelica_metatype _tableID)
{
  modelica_real _uMin;
  modelica_metatype out_uMin;
  _uMin = omc_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmin(threadData, _tableID);
  out_uMin = mmc_mk_rcon(_uMin);
  return out_uMin;
}

modelica_real omc_Modelica_Blocks_Tables_Internal_getTable1DValueNoDer2(threadData_t *threadData, modelica_complex _tableID, modelica_integer _icol, modelica_real _u)
{
  void * _tableID_ext;
  int _icol_ext;
  double _u_ext;
  double _y_ext;
  modelica_real _y;
  // _y has no default value.
  _tableID_ext = (void *)_tableID;
  _icol_ext = (int)_icol;
  _u_ext = (double)_u;
  _y_ext = ModelicaStandardTables_CombiTable1D_getValue(_tableID_ext, _icol_ext, _u_ext);
  _y = (modelica_real)_y_ext;
  return _y;
}
modelica_metatype boxptr_Modelica_Blocks_Tables_Internal_getTable1DValueNoDer2(threadData_t *threadData, modelica_metatype _tableID, modelica_metatype _icol, modelica_metatype _u)
{
  modelica_integer tmp1;
  modelica_real tmp2;
  modelica_real _y;
  modelica_metatype out_y;
  tmp1 = mmc_unbox_integer(_icol);
  tmp2 = mmc_unbox_real(_u);
  _y = omc_Modelica_Blocks_Tables_Internal_getTable1DValueNoDer2(threadData, _tableID, tmp1, tmp2);
  out_y = mmc_mk_rcon(_y);
  return out_y;
}

modelica_complex omc_Modelica_Blocks_Types_ExternalCombiTable1D_constructor(threadData_t *threadData, modelica_string _tableName, modelica_string _fileName, real_array _table, integer_array _columns, modelica_integer _smoothness, modelica_integer _extrapolation, modelica_boolean _verboseRead, modelica_string _delimiter, modelica_integer _nHeaderLines)
{
  integer_array _columns_packed;
  int _smoothness_ext;
  int _extrapolation_ext;
  int _verboseRead_ext;
  int _nHeaderLines_ext;
  void *_table_c89;
  void *_columns_c89;
  void * _externalCombiTable1D_ext;
  modelica_complex _externalCombiTable1D;
  // _externalCombiTable1D has no default value.
  pack_alloc_integer_array(&_columns, &_columns_packed);

  _smoothness_ext = (int)_smoothness;
  _extrapolation_ext = (int)_extrapolation;
  _verboseRead_ext = (int)_verboseRead;
  _nHeaderLines_ext = (int)_nHeaderLines;_table_c89 = (void*) data_of_real_c89_array(_table);
  _columns_c89 = (void*) data_of_integer_c89_array(_columns_packed);
  _externalCombiTable1D_ext = ModelicaStandardTables_CombiTable1D_init3(MMC_STRINGDATA(_fileName), MMC_STRINGDATA(_tableName), (const double*) _table_c89, size_of_dimension_base_array(_table, ((modelica_integer) 1)), size_of_dimension_base_array(_table, ((modelica_integer) 2)), (const int*) _columns_c89, size_of_dimension_base_array(_columns, ((modelica_integer) 1)), _smoothness_ext, _extrapolation_ext, _verboseRead_ext, MMC_STRINGDATA(_delimiter), _nHeaderLines_ext);
  _externalCombiTable1D = (modelica_complex)_externalCombiTable1D_ext;
  return _externalCombiTable1D;
}
modelica_metatype boxptr_Modelica_Blocks_Types_ExternalCombiTable1D_constructor(threadData_t *threadData, modelica_metatype _tableName, modelica_metatype _fileName, modelica_metatype _table, modelica_metatype _columns, modelica_metatype _smoothness, modelica_metatype _extrapolation, modelica_metatype _verboseRead, modelica_metatype _delimiter, modelica_metatype _nHeaderLines)
{
  modelica_integer tmp1;
  modelica_integer tmp2;
  modelica_integer tmp3;
  modelica_integer tmp4;
  modelica_complex _externalCombiTable1D;
  tmp1 = mmc_unbox_integer(_smoothness);
  tmp2 = mmc_unbox_integer(_extrapolation);
  tmp3 = mmc_unbox_integer(_verboseRead);
  tmp4 = mmc_unbox_integer(_nHeaderLines);
  _externalCombiTable1D = omc_Modelica_Blocks_Types_ExternalCombiTable1D_constructor(threadData, _tableName, _fileName, *((base_array_t*)_table), *((base_array_t*)_columns), tmp1, tmp2, tmp3, _delimiter, tmp4);
  /* skip box _externalCombiTable1D; ExternalObject Modelica.Blocks.Types.ExternalCombiTable1D */
  return _externalCombiTable1D;
}

void omc_Modelica_Blocks_Types_ExternalCombiTable1D_destructor(threadData_t *threadData, modelica_complex _externalCombiTable1D)
{
  void * _externalCombiTable1D_ext;
  _externalCombiTable1D_ext = (void *)_externalCombiTable1D;
  ModelicaStandardTables_CombiTable1D_close(_externalCombiTable1D_ext);
  return;
}
void boxptr_Modelica_Blocks_Types_ExternalCombiTable1D_destructor(threadData_t *threadData, modelica_metatype _externalCombiTable1D)
{
  omc_Modelica_Blocks_Types_ExternalCombiTable1D_destructor(threadData, _externalCombiTable1D);
  return;
}

DLLDirection
modelica_real omc_Modelica_Math_atan2(threadData_t *threadData, modelica_real _u1, modelica_real _u2)
{
  modelica_real _y;
  _tailrecursive: OMC_LABEL_UNUSED
  // _y has no default value.
  _y = atan2(_u1, _u2);
  _return: OMC_LABEL_UNUSED
  return _y;
}
modelica_metatype boxptr_Modelica_Math_atan2(threadData_t *threadData, modelica_metatype _u1, modelica_metatype _u2)
{
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_real _y;
  modelica_metatype out_y;
  tmp1 = mmc_unbox_real(_u1);
  tmp2 = mmc_unbox_real(_u2);
  _y = omc_Modelica_Math_atan2(threadData, tmp1, tmp2);
  out_y = mmc_mk_rcon(_y);
  return out_y;
}

DLLDirection
modelica_real omc_Modelica_Math_Vectors_interpolate(threadData_t *threadData, real_array _x, real_array _y, modelica_real _xi, modelica_integer _iLast, modelica_integer *out_iNew)
{
  modelica_real _yi;
  modelica_integer _iNew;
  modelica_integer _i;
  modelica_integer _nx;
  modelica_integer tmp1;
  modelica_real _x1;
  modelica_real _x2;
  modelica_real _y1;
  modelica_real _y2;
  static int tmp2 = 0;
  static int tmp3 = 0;
  modelica_real tmp4;
  _tailrecursive: OMC_LABEL_UNUSED
  // _yi has no default value.
  _iNew = ((modelica_integer) 1);
  // _i has no default value.
  tmp1 = size_of_dimension_base_array(_x, ((modelica_integer) 1));
  _nx = tmp1;
  // _x1 has no default value.
  // _x2 has no default value.
  // _y1 has no default value.
  // _y2 has no default value.
  {
    if(!(_nx > ((modelica_integer) 0)))
    {
      {
        FILE_INFO info = {"/home/rhorvath/.openmodelica/libraries/Modelica 4.1.0+maint.om/Math/package.mo",514,5,514,68,0};
        omc_assert(threadData, info, MMC_STRINGDATA(_OMC_LIT17));
      }
    }
  }

  if((_nx == ((modelica_integer) 1)))
  {
    _yi = real_array_get(_y, 1, ((modelica_integer) 1));
  }
  else
  {
    _i = modelica_integer_min((modelica_integer)(modelica_integer_max((modelica_integer)(_iLast),(modelica_integer)(((modelica_integer) 1)))),(modelica_integer)(_nx - ((modelica_integer) 1)));

    if((_xi >= real_array_get(_x, 1, _i)))
    {
      while(1)
      {
        if(!((_i < _nx) && (_xi >= real_array_get(_x, 1, _i)))) break;
        _i = _i + ((modelica_integer) 1);
      }

      _i = _i - ((modelica_integer) 1);
    }
    else
    {
      while(1)
      {
        if(!((_i > ((modelica_integer) 1)) && (_xi < real_array_get(_x, 1, _i)))) break;
        _i = _i - ((modelica_integer) 1);
      }
    }

    _x1 = real_array_get(_x, 1, _i);

    _x2 = real_array_get(_x, 1, _i + ((modelica_integer) 1));

    _y1 = real_array_get(_y, 1, _i);

    _y2 = real_array_get(_y, 1, _i + ((modelica_integer) 1));

    {
      if(!(_x2 > _x1))
      {
        {
          FILE_INFO info = {"/home/rhorvath/.openmodelica/libraries/Modelica 4.1.0+maint.om/Math/package.mo",539,7,539,73,0};
          omc_assert(threadData, info, MMC_STRINGDATA(_OMC_LIT18));
        }
      }
    }

    tmp4 = _x2 - _x1;
    if (tmp4 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "(y2 - y1) * (xi - x1) / (x2 - x1)");}
    _yi = _y1 + ((_y2 - _y1) * (_xi - _x1)) / tmp4;

    _iNew = _i;
  }
  _return: OMC_LABEL_UNUSED
  if (out_iNew) { *out_iNew = _iNew; }
  return _yi;
}
modelica_metatype boxptr_Modelica_Math_Vectors_interpolate(threadData_t *threadData, modelica_metatype _x, modelica_metatype _y, modelica_metatype _xi, modelica_metatype _iLast, modelica_metatype *out_iNew)
{
  modelica_real tmp1;
  modelica_integer tmp2;
  modelica_integer _iNew;
  modelica_real _yi;
  modelica_metatype out_yi;
  tmp1 = mmc_unbox_real(_xi);
  tmp2 = mmc_unbox_integer(_iLast);
  _yi = omc_Modelica_Math_Vectors_interpolate(threadData, *((base_array_t*)_x), *((base_array_t*)_y), tmp1, tmp2, &_iNew);
  out_yi = mmc_mk_rcon(_yi);
  if (out_iNew) { *out_iNew = mmc_mk_icon(_iNew); }
  return out_yi;
}

DLLDirection
modelica_real omc_Modelica_Math_Vectors_length(threadData_t *threadData, real_array _v)
{
  modelica_real _result;
  modelica_real tmp1;
  _tailrecursive: OMC_LABEL_UNUSED
  // _result has no default value.
  tmp1 = mul_real_scalar_product(_v, _v);
  if(!(tmp1 >= 0.0))
  {
    FILE_INFO info = {"",0,0,0,0,0};
    omc_assert(threadData, info, "Model error: Argument of sqrt(v * v) was %g should be >= 0", tmp1);
  }
  _result = sqrt(tmp1);
  _return: OMC_LABEL_UNUSED
  return _result;
}
modelica_metatype boxptr_Modelica_Math_Vectors_length(threadData_t *threadData, modelica_metatype _v)
{
  modelica_real _result;
  modelica_metatype out_result;
  _result = omc_Modelica_Math_Vectors_length(threadData, *((base_array_t*)_v));
  out_result = mmc_mk_rcon(_result);
  return out_result;
}

DLLDirection
modelica_real omc_Modelica_Math_Vectors_norm(threadData_t *threadData, real_array _v, modelica_real _p)
{
  modelica_real _result;
  modelica_real _eps;
  modelica_integer tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  modelica_real tmp8;
  modelica_real tmp13;
  modelica_real tmp25;
  modelica_real tmp26;
  modelica_real tmp27;
  modelica_real tmp28;
  modelica_real tmp29;
  modelica_real tmp30;
  modelica_real tmp31;
  modelica_real tmp32;
  modelica_string tmp33;
  modelica_metatype tmpMeta34;
  modelica_metatype tmpMeta35;
  static int tmp36 = 0;
  _tailrecursive: OMC_LABEL_UNUSED
  _result = 0.0;
  _eps = 2.220446049250313e-15;
  tmp1 = size_of_dimension_base_array(_v, ((modelica_integer) 1));
  if((tmp1 > ((modelica_integer) 0)))
  {
    if(((_p >= 2.0 - _eps) && (_p <= 2.0 + _eps)))
    {
      tmp2 = mul_real_scalar_product(_v, _v);
      if(!(tmp2 >= 0.0))
      {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert(threadData, info, "Model error: Argument of sqrt(v * v) was %g should be >= 0", tmp2);
      }
      _result = sqrt(tmp2);
    }
    else
    {
      if((_p >= 1e60))
      {
        {
          modelica_real __omcQ_24tmpVar3;
          modelica_real __omcQ_24tmpVar2;
          modelica_integer tmp4;
          modelica_integer tmp5;
          modelica_integer tmp6;
          modelica_integer tmp7;
          modelica_integer __omcQ_24i4;
          tmp7 = size_of_dimension_base_array(_v, ((modelica_integer) 1));
          tmp5 = 1 /* Range step-value */;
          tmp6 = tmp7 /* Range stop-value */;
          __omcQ_24i4 = ((modelica_integer) 1) /* Range start-value */;
          __omcQ_24i4 = (((modelica_integer) 1) /* Range start-value */)-tmp5;
          __omcQ_24tmpVar3 = -8.777798510069901e304; /* defaultValue */
          while(1) {
            tmp4 = 1;
            if (tmp5 > 0 ? __omcQ_24i4+tmp5 <= tmp6 : __omcQ_24i4+tmp5 >= tmp6) {
              __omcQ_24i4 += tmp5;
              tmp4--;
            }
            if (tmp4 == 0) {
              __omcQ_24tmpVar2 = fabs(real_array_get(_v, 1, __omcQ_24i4));
              __omcQ_24tmpVar3 = fmax(__omcQ_24tmpVar2,__omcQ_24tmpVar3);
            } else if (tmp4 == 1) {
              break;
            } else {
              MMC_THROW_INTERNAL();
            }
          }
          tmp3 = __omcQ_24tmpVar3;
        }
        _result = tmp3;
      }
      else
      {
        if(((_p >= 1.0 - _eps) && (_p <= 1.0 + _eps)))
        {
          {
            modelica_real __omcQ_24tmpVar5;
            modelica_real __omcQ_24tmpVar4;
            modelica_integer tmp9;
            modelica_integer tmp10;
            modelica_integer tmp11;
            modelica_integer tmp12;
            modelica_integer __omcQ_24i5;
            tmp12 = size_of_dimension_base_array(_v, ((modelica_integer) 1));
            tmp10 = 1 /* Range step-value */;
            tmp11 = tmp12 /* Range stop-value */;
            __omcQ_24i5 = ((modelica_integer) 1) /* Range start-value */;
            __omcQ_24i5 = (((modelica_integer) 1) /* Range start-value */)-tmp10;
            __omcQ_24tmpVar5 = 0.0; /* defaultValue */
            while(1) {
              tmp9 = 1;
              if (tmp10 > 0 ? __omcQ_24i5+tmp10 <= tmp11 : __omcQ_24i5+tmp10 >= tmp11) {
                __omcQ_24i5 += tmp10;
                tmp9--;
              }
              if (tmp9 == 0) {
                __omcQ_24tmpVar4 = fabs(real_array_get(_v, 1, __omcQ_24i5));
                __omcQ_24tmpVar5 = __omcQ_24tmpVar5 + __omcQ_24tmpVar4;
              } else if (tmp9 == 1) {
                break;
              } else {
                MMC_THROW_INTERNAL();
              }
            }
            tmp8 = __omcQ_24tmpVar5;
          }
          _result = tmp8;
        }
        else
        {
          if((_p >= 1.0))
          {
            {
              modelica_real __omcQ_24tmpVar1;
              modelica_real tmp14;
              modelica_real tmp15;
              modelica_real tmp16;
              modelica_real tmp17;
              modelica_real tmp18;
              modelica_real tmp19;
              modelica_real tmp20;
              modelica_real __omcQ_24tmpVar0;
              modelica_integer tmp21;
              modelica_integer tmp22;
              modelica_integer tmp23;
              modelica_integer tmp24;
              modelica_integer _i;
              tmp24 = size_of_dimension_base_array(_v, ((modelica_integer) 1));
              tmp22 = 1 /* Range step-value */;
              tmp23 = tmp24 /* Range stop-value */;
              _i = ((modelica_integer) 1) /* Range start-value */;
              _i = (((modelica_integer) 1) /* Range start-value */)-tmp22;
              __omcQ_24tmpVar1 = 0.0; /* defaultValue */
              while(1) {
                tmp21 = 1;
                if (tmp22 > 0 ? _i+tmp22 <= tmp23 : _i+tmp22 >= tmp23) {
                  _i += tmp22;
                  tmp21--;
                }
                if (tmp21 == 0) {
                  tmp14 = fabs(real_array_get(_v, 1, _i));
                  tmp15 = _p;
                  if(tmp14 < 0.0 && tmp15 != 0.0)
                  {
                    tmp17 = modf(tmp15, &tmp18);
                    
                    if(tmp17 > 0.5)
                    {
                      tmp17 -= 1.0;
                      tmp18 += 1.0;
                    }
                    else if(tmp17 < -0.5)
                    {
                      tmp17 += 1.0;
                      tmp18 -= 1.0;
                    }
                    
                    if(fabs(tmp17) < 1e-10)
                      tmp16 = pow(tmp14, tmp18);
                    else
                    {
                      tmp20 = modf(1.0/tmp15, &tmp19);
                      if(tmp20 > 0.5)
                      {
                        tmp20 -= 1.0;
                        tmp19 += 1.0;
                      }
                      else if(tmp20 < -0.5)
                      {
                        tmp20 += 1.0;
                        tmp19 -= 1.0;
                      }
                      if(fabs(tmp20) < 1e-10 && ((unsigned long)tmp19 & 1))
                      {
                        tmp16 = -pow(-tmp14, tmp17)*pow(tmp14, tmp18);
                      }
                      else
                      {
                        throwStreamPrint(threadData, "%s:%d: Invalid root: (%g)^(%g)", __FILE__, __LINE__, tmp14, tmp15);
                      }
                    }
                  }
                  else
                  {
                    tmp16 = pow(tmp14, tmp15);
                  }
                  if(isnan(tmp16) || isinf(tmp16))
                  {
                    throwStreamPrint(threadData, "%s:%d: Invalid root: (%g)^(%g)", __FILE__, __LINE__, tmp14, tmp15);
                  }__omcQ_24tmpVar0 = tmp16;
                  __omcQ_24tmpVar1 = __omcQ_24tmpVar1 + __omcQ_24tmpVar0;
                } else if (tmp21 == 1) {
                  break;
                } else {
                  MMC_THROW_INTERNAL();
                }
              }
              tmp13 = __omcQ_24tmpVar1;
            }
            tmp25 = _p;
            if (tmp25 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "1.0 / p");}
            tmp26 = tmp13;
            tmp27 = (1.0) / tmp25;
            if(tmp26 < 0.0 && tmp27 != 0.0)
            {
              tmp29 = modf(tmp27, &tmp30);
              
              if(tmp29 > 0.5)
              {
                tmp29 -= 1.0;
                tmp30 += 1.0;
              }
              else if(tmp29 < -0.5)
              {
                tmp29 += 1.0;
                tmp30 -= 1.0;
              }
              
              if(fabs(tmp29) < 1e-10)
                tmp28 = pow(tmp26, tmp30);
              else
              {
                tmp32 = modf(1.0/tmp27, &tmp31);
                if(tmp32 > 0.5)
                {
                  tmp32 -= 1.0;
                  tmp31 += 1.0;
                }
                else if(tmp32 < -0.5)
                {
                  tmp32 += 1.0;
                  tmp31 -= 1.0;
                }
                if(fabs(tmp32) < 1e-10 && ((unsigned long)tmp31 & 1))
                {
                  tmp28 = -pow(-tmp26, tmp29)*pow(tmp26, tmp30);
                }
                else
                {
                  throwStreamPrint(threadData, "%s:%d: Invalid root: (%g)^(%g)", __FILE__, __LINE__, tmp26, tmp27);
                }
              }
            }
            else
            {
              tmp28 = pow(tmp26, tmp27);
            }
            if(isnan(tmp28) || isinf(tmp28))
            {
              throwStreamPrint(threadData, "%s:%d: Invalid root: (%g)^(%g)", __FILE__, __LINE__, tmp26, tmp27);
            }
            _result = tmp28;
          }
          else
          {
            {
              if(!0 /* false */)
              {
                tmp33 = modelica_real_to_modelica_string(_p, ((modelica_integer) 6), ((modelica_integer) 0), 1 /* true */);
                tmpMeta34 = stringAppend(_OMC_LIT19,tmp33);
                tmpMeta35 = stringAppend(tmpMeta34,_OMC_LIT20);
                {
                  FILE_INFO info = {"/home/rhorvath/.openmodelica/libraries/Modelica 4.1.0+maint.om/Math/package.mo",159,7,159,104,0};
                  omc_assert(threadData, info, MMC_STRINGDATA(tmpMeta35));
                }
              }
            }
          }
        }
      }
    }
  }
  _return: OMC_LABEL_UNUSED
  return _result;
}
modelica_metatype boxptr_Modelica_Math_Vectors_norm(threadData_t *threadData, modelica_metatype _v, modelica_metatype _p)
{
  modelica_real tmp1;
  modelica_real _result;
  modelica_metatype out_result;
  tmp1 = mmc_unbox_real(_p);
  _result = omc_Modelica_Math_Vectors_norm(threadData, *((base_array_t*)_v), tmp1);
  out_result = mmc_mk_rcon(_result);
  return out_result;
}

DLLDirection
real_array omc_Modelica_Math_Vectors_normalize(threadData_t *threadData, real_array _v, modelica_real _eps)
{
  real_array _result;
  modelica_integer tmp1;
  modelica_boolean tmp2;
  real_array tmp3;
  _tailrecursive: OMC_LABEL_UNUSED
  tmp1 = size_of_dimension_base_array(_v, ((modelica_integer) 1));
  alloc_real_array(&(_result), 1, (_index_t)tmp1); // _result has no default value.
  tmp2 = (modelica_boolean)(omc_Modelica_Math_Vectors_length(threadData, _v) >= _eps);
  if(tmp2)
  {
    tmp3 = div_alloc_real_array_scalar(_v, omc_Modelica_Math_Vectors_length(threadData, _v));
  }
  else
  {
    tmp3 = div_alloc_real_array_scalar(_v, _eps);
  }
  real_array_copy_data(tmp3, _result);
  _return: OMC_LABEL_UNUSED
  return _result;
}
modelica_metatype boxptr_Modelica_Math_Vectors_normalize(threadData_t *threadData, modelica_metatype _v, modelica_metatype _eps)
{
  modelica_real tmp1;
  real_array _result;
  modelica_integer tmp2;
  modelica_metatype out_result;
  tmp1 = mmc_unbox_real(_eps);
  _result = omc_Modelica_Math_Vectors_normalize(threadData, *((base_array_t*)_v), tmp1);
  out_result = mmc_mk_modelica_array(_result);
  return out_result;
}

Modelica_Mechanics_MultiBody_Frames_Orientation omc_Modelica_Mechanics_MultiBody_Frames_Orientation(threadData_t *threadData, real_array omc_T, real_array omc_w)
{
  Modelica_Mechanics_MultiBody_Frames_Orientation tmp1;
  tmp1._T = omc_T;
  tmp1._w = omc_w;
  return tmp1;
}

modelica_metatype boxptr_Modelica_Mechanics_MultiBody_Frames_Orientation(threadData_t *threadData, modelica_metatype _T, modelica_metatype _w)
{
  return mmc_mk_box3(3, &Modelica_Mechanics_MultiBody_Frames_Orientation__desc, _T, _w);
}

DLLDirection
real_array omc_Modelica_Mechanics_MultiBody_Frames_resolve2(threadData_t *threadData, Modelica_Mechanics_MultiBody_Frames_Orientation _R, real_array _v1)
{
  real_array _v2;
  real_array tmp1;
  _tailrecursive: OMC_LABEL_UNUSED
  alloc_real_array(&(_v2), 1, (_index_t)3); // _v2 has no default value.
  array_alloc_scalar_real_array(&tmp1, 3, (modelica_real)(real_array_get(_R._T, 2, ((modelica_integer) 1), ((modelica_integer) 1))) * (real_array_get(_v1, 1, ((modelica_integer) 1))) + (real_array_get(_R._T, 2, ((modelica_integer) 1), ((modelica_integer) 2))) * (real_array_get(_v1, 1, ((modelica_integer) 2))) + (real_array_get(_R._T, 2, ((modelica_integer) 1), ((modelica_integer) 3))) * (real_array_get(_v1, 1, ((modelica_integer) 3))), (modelica_real)(real_array_get(_R._T, 2, ((modelica_integer) 2), ((modelica_integer) 1))) * (real_array_get(_v1, 1, ((modelica_integer) 1))) + (real_array_get(_R._T, 2, ((modelica_integer) 2), ((modelica_integer) 2))) * (real_array_get(_v1, 1, ((modelica_integer) 2))) + (real_array_get(_R._T, 2, ((modelica_integer) 2), ((modelica_integer) 3))) * (real_array_get(_v1, 1, ((modelica_integer) 3))), (modelica_real)(real_array_get(_R._T, 2, ((modelica_integer) 3), ((modelica_integer) 1))) * (real_array_get(_v1, 1, ((modelica_integer) 1))) + (real_array_get(_R._T, 2, ((modelica_integer) 3), ((modelica_integer) 2))) * (real_array_get(_v1, 1, ((modelica_integer) 2))) + (real_array_get(_R._T, 2, ((modelica_integer) 3), ((modelica_integer) 3))) * (real_array_get(_v1, 1, ((modelica_integer) 3))));
  real_array_copy_data(tmp1, _v2);
  _return: OMC_LABEL_UNUSED
  return _v2;
}
modelica_metatype boxptr_Modelica_Mechanics_MultiBody_Frames_resolve2(threadData_t *threadData, modelica_metatype _R, modelica_metatype _v1)
{
  Modelica_Mechanics_MultiBody_Frames_Orientation tmp1;
  modelica_metatype tmpMeta2;
  modelica_metatype tmpMeta3;
  real_array _v2;
  modelica_metatype out_v2;
  tmpMeta2 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_R), 2)));
  tmp1._T = *((base_array_t*)tmpMeta2);
  tmpMeta3 = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_R), 3)));
  tmp1._w = *((base_array_t*)tmpMeta3);
  _v2 = omc_Modelica_Mechanics_MultiBody_Frames_resolve2(threadData, tmp1, *((base_array_t*)_v1));
  out_v2 = mmc_mk_modelica_array(_v2);
  return out_v2;
}

DLLDirection
real_array omc_Modelica_Mechanics_MultiBody_Frames_TransformationMatrices_from__nxy(threadData_t *threadData, real_array _n_x, real_array _n_y)
{
  real_array _T;
  real_array _e_x;
  modelica_boolean tmp1;
  real_array tmp2;
  real_array _e_y;
  modelica_boolean tmp3;
  real_array tmp4;
  real_array _n_z_aux;
  real_array tmp5;
  real_array _n_y_aux;
  modelica_boolean tmp6;
  real_array tmp7;
  modelica_boolean tmp8;
  real_array tmp9;
  real_array _e_z_aux;
  real_array tmp10;
  real_array _e_z;
  real_array tmp11;
  real_array tmp12;
  _tailrecursive: OMC_LABEL_UNUSED
  alloc_real_array(&(_T), 2, (_index_t)3, (_index_t)3); // _T has no default value.
  alloc_real_array(&(_e_x), 1, (_index_t)3);
  tmp1 = (modelica_boolean)(omc_Modelica_Math_Vectors_length(threadData, _n_x) < 1e-10);
  if(tmp1)
  {
    tmp2 = _OMC_LIT21;
  }
  else
  {
    tmp2 = omc_Modelica_Math_Vectors_normalize(threadData, _n_x, 2.220446049250313e-14);
  }
  real_array_copy_data(tmp2, _e_x);
  
  alloc_real_array(&(_e_y), 1, (_index_t)3);
  tmp3 = (modelica_boolean)(omc_Modelica_Math_Vectors_length(threadData, _n_y) < 1e-10);
  if(tmp3)
  {
    tmp4 = _OMC_LIT22;
  }
  else
  {
    tmp4 = omc_Modelica_Math_Vectors_normalize(threadData, _n_y, 2.220446049250313e-14);
  }
  real_array_copy_data(tmp4, _e_y);
  
  alloc_real_array(&(_n_z_aux), 1, (_index_t)3);
  array_alloc_scalar_real_array(&tmp5, 3, (modelica_real)(real_array_get(_e_x, 1, ((modelica_integer) 2))) * (real_array_get(_e_y, 1, ((modelica_integer) 3))) - ((real_array_get(_e_x, 1, ((modelica_integer) 3))) * (real_array_get(_e_y, 1, ((modelica_integer) 2)))), (modelica_real)(real_array_get(_e_x, 1, ((modelica_integer) 3))) * (real_array_get(_e_y, 1, ((modelica_integer) 1))) - ((real_array_get(_e_x, 1, ((modelica_integer) 1))) * (real_array_get(_e_y, 1, ((modelica_integer) 3)))), (modelica_real)(real_array_get(_e_x, 1, ((modelica_integer) 1))) * (real_array_get(_e_y, 1, ((modelica_integer) 2))) - ((real_array_get(_e_x, 1, ((modelica_integer) 2))) * (real_array_get(_e_y, 1, ((modelica_integer) 1)))));
  real_array_copy_data(tmp5, _n_z_aux);
  
  alloc_real_array(&(_n_y_aux), 1, (_index_t)3);
  tmp8 = (modelica_boolean)((real_array_get(_n_z_aux, 1, ((modelica_integer) 1))) * (real_array_get(_n_z_aux, 1, ((modelica_integer) 1))) + (real_array_get(_n_z_aux, 1, ((modelica_integer) 2))) * (real_array_get(_n_z_aux, 1, ((modelica_integer) 2))) + (real_array_get(_n_z_aux, 1, ((modelica_integer) 3))) * (real_array_get(_n_z_aux, 1, ((modelica_integer) 3))) > 1e-6);
  if(tmp8)
  {
    tmp9 = _e_y;
  }
  else
  {
    tmp6 = (modelica_boolean)(fabs(real_array_get(_e_x, 1, ((modelica_integer) 1))) > 1e-6);
    if(tmp6)
    {
      tmp7 = _OMC_LIT22;
    }
    else
    {
      tmp7 = _OMC_LIT21;
    }
    tmp9 = tmp7;
  }
  real_array_copy_data(tmp9, _n_y_aux);
  
  alloc_real_array(&(_e_z_aux), 1, (_index_t)3);
  array_alloc_scalar_real_array(&tmp10, 3, (modelica_real)(real_array_get(_e_x, 1, ((modelica_integer) 2))) * (real_array_get(_n_y_aux, 1, ((modelica_integer) 3))) - ((real_array_get(_e_x, 1, ((modelica_integer) 3))) * (real_array_get(_n_y_aux, 1, ((modelica_integer) 2)))), (modelica_real)(real_array_get(_e_x, 1, ((modelica_integer) 3))) * (real_array_get(_n_y_aux, 1, ((modelica_integer) 1))) - ((real_array_get(_e_x, 1, ((modelica_integer) 1))) * (real_array_get(_n_y_aux, 1, ((modelica_integer) 3)))), (modelica_real)(real_array_get(_e_x, 1, ((modelica_integer) 1))) * (real_array_get(_n_y_aux, 1, ((modelica_integer) 2))) - ((real_array_get(_e_x, 1, ((modelica_integer) 2))) * (real_array_get(_n_y_aux, 1, ((modelica_integer) 1)))));
  real_array_copy_data(tmp10, _e_z_aux);
  
  alloc_real_array(&(_e_z), 1, (_index_t)3);
  real_array_copy_data(omc_Modelica_Math_Vectors_normalize(threadData, _e_z_aux, 2.220446049250313e-14), _e_z);
  
  array_alloc_scalar_real_array(&tmp12, 3, (modelica_real)(real_array_get(_e_z, 1, ((modelica_integer) 2))) * (real_array_get(_e_x, 1, ((modelica_integer) 3))) - ((real_array_get(_e_z, 1, ((modelica_integer) 3))) * (real_array_get(_e_x, 1, ((modelica_integer) 2)))), (modelica_real)(real_array_get(_e_z, 1, ((modelica_integer) 3))) * (real_array_get(_e_x, 1, ((modelica_integer) 1))) - ((real_array_get(_e_z, 1, ((modelica_integer) 1))) * (real_array_get(_e_x, 1, ((modelica_integer) 3)))), (modelica_real)(real_array_get(_e_z, 1, ((modelica_integer) 1))) * (real_array_get(_e_x, 1, ((modelica_integer) 2))) - ((real_array_get(_e_z, 1, ((modelica_integer) 2))) * (real_array_get(_e_x, 1, ((modelica_integer) 1)))));
  array_alloc_real_array(&tmp11, 3, _e_x, tmp12, _e_z);
  real_array_copy_data(tmp11, _T);
  _return: OMC_LABEL_UNUSED
  return _T;
}
modelica_metatype boxptr_Modelica_Mechanics_MultiBody_Frames_TransformationMatrices_from__nxy(threadData_t *threadData, modelica_metatype _n_x, modelica_metatype _n_y)
{
  real_array _T;
  modelica_metatype out_T;
  _T = omc_Modelica_Mechanics_MultiBody_Frames_TransformationMatrices_from__nxy(threadData, *((base_array_t*)_n_x), *((base_array_t*)_n_y));
  out_T = mmc_mk_modelica_array(_T);
  return out_T;
}

#ifdef __cplusplus
}
#endif
