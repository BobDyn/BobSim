#ifndef BobLib_Experiments_Standards_VehicleSim__H
#define BobLib_Experiments_Standards_VehicleSim__H
#include "meta/meta_modelica.h"
#include "util/modelica.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "simulation/simulation_runtime.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  modelica_real _FNOMIN;
  modelica_real _FZMIN;
  modelica_real _FZMAX;
  modelica_real _UNLOADED_RADIUS;
} BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord;
extern struct record_description BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord__desc;

void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_construct_p(threadData_t *threadData, void* v_ths );
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_construct(td, ths ) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_construct_p(td, &ths )
void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_copy_p(void* v_src, void* v_dst);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_copy(src,dst) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_copy_p(&src, &dst)


void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_wrap_vars_p(threadData_t *threadData , void* v_dst , modelica_real in_FNOMIN, modelica_real in_FZMIN, modelica_real in_FZMAX, modelica_real in_UNLOADED_RADIUS);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_wrap_vars(td, dst , in_FNOMIN, in_FZMIN, in_FZMAX, in_UNLOADED_RADIUS) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_wrap_vars_p(td, &dst , in_FNOMIN, in_FZMIN, in_FZMAX, in_UNLOADED_RADIUS)

// This function is not needed anymore. If you want to know how a record
// is 'assigned to' in simulation context see assignRhsExpToRecordCrefSimContext and
// splitRecordAssignmentToMemberAssignments (simCode). Basically the record is
// split up assignments generated for each member individually.
// void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_copy_to_vars_p(void* v_src , modelica_real* in_FNOMIN, modelica_real* in_FZMIN, modelica_real* in_FZMAX, modelica_real* in_UNLOADED_RADIUS);
// #define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_copy_to_vars(src,...) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_copy_to_vars_p(&src, __VA_ARGS__)

typedef base_array_t BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_array;
#define alloc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_array(dst,ndims,...) generic_array_create(NULL, dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_construct_p, ndims, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord), __VA_ARGS__)
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_array_copy_data(src,dst)   generic_array_copy_data(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_array_alloc_copy(src,dst)  generic_array_alloc_copy(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_array_get(src,ndims,...)   (*(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord*)(generic_array_get(&src, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord), __VA_ARGS__)))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_set(dst,val,...)           generic_array_set(&dst, &val, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord), __VA_ARGS__)

typedef struct {
  modelica_real _FNOMIN;
  modelica_real _UNLOADED_RADIUS;
  modelica_real _LFZO;
  modelica_real _PTX1;
  modelica_real _PTX2;
  modelica_real _PTX3;
  modelica_real _PTY1;
  modelica_real _PTY2;
  modelica_real _PKY3;
  modelica_real _LSGKP;
  modelica_real _LSGAL;
} BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord;
extern struct record_description BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord__desc;

void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_construct_p(threadData_t *threadData, void* v_ths );
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_construct(td, ths ) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_construct_p(td, &ths )
void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_copy_p(void* v_src, void* v_dst);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_copy(src,dst) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_copy_p(&src, &dst)


void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_wrap_vars_p(threadData_t *threadData , void* v_dst , modelica_real in_FNOMIN, modelica_real in_UNLOADED_RADIUS, modelica_real in_LFZO, modelica_real in_PTX1, modelica_real in_PTX2, modelica_real in_PTX3, modelica_real in_PTY1, modelica_real in_PTY2, modelica_real in_PKY3, modelica_real in_LSGKP, modelica_real in_LSGAL);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_wrap_vars(td, dst , in_FNOMIN, in_UNLOADED_RADIUS, in_LFZO, in_PTX1, in_PTX2, in_PTX3, in_PTY1, in_PTY2, in_PKY3, in_LSGKP, in_LSGAL) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_wrap_vars_p(td, &dst , in_FNOMIN, in_UNLOADED_RADIUS, in_LFZO, in_PTX1, in_PTX2, in_PTX3, in_PTY1, in_PTY2, in_PKY3, in_LSGKP, in_LSGAL)

// This function is not needed anymore. If you want to know how a record
// is 'assigned to' in simulation context see assignRhsExpToRecordCrefSimContext and
// splitRecordAssignmentToMemberAssignments (simCode). Basically the record is
// split up assignments generated for each member individually.
// void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_copy_to_vars_p(void* v_src , modelica_real* in_FNOMIN, modelica_real* in_UNLOADED_RADIUS, modelica_real* in_LFZO, modelica_real* in_PTX1, modelica_real* in_PTX2, modelica_real* in_PTX3, modelica_real* in_PTY1, modelica_real* in_PTY2, modelica_real* in_PKY3, modelica_real* in_LSGKP, modelica_real* in_LSGAL);
// #define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_copy_to_vars(src,...) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_copy_to_vars_p(&src, __VA_ARGS__)

typedef base_array_t BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_array;
#define alloc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_array(dst,ndims,...) generic_array_create(NULL, dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_construct_p, ndims, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord), __VA_ARGS__)
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_array_copy_data(src,dst)   generic_array_copy_data(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_array_alloc_copy(src,dst)  generic_array_alloc_copy(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_array_get(src,ndims,...)   (*(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord*)(generic_array_get(&src, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord), __VA_ARGS__)))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_set(dst,val,...)           generic_array_set(&dst, &val, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord), __VA_ARGS__)

typedef struct {
  modelica_real _LGAX;
  modelica_real _LFZO;
  modelica_real _PCX1;
  modelica_real _PDX1;
  modelica_real _PDX2;
  modelica_real _PDX3;
  modelica_real _PKX1;
  modelica_real _PKX2;
  modelica_real _PKX3;
  modelica_real _PHX1;
  modelica_real _PHX2;
  modelica_real _PVX1;
  modelica_real _PVX2;
  modelica_real _PEX1;
  modelica_real _PEX2;
  modelica_real _PEX3;
  modelica_real _PEX4;
  modelica_real _LCX;
  modelica_real _LMUX;
  modelica_real _LKX;
  modelica_real _LHX;
  modelica_real _LVX;
  modelica_real _LEX;
  modelica_real _LXAL;
} BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord;
extern struct record_description BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord__desc;

void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_construct_p(threadData_t *threadData, void* v_ths );
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_construct(td, ths ) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_construct_p(td, &ths )
void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_copy_p(void* v_src, void* v_dst);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_copy(src,dst) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_copy_p(&src, &dst)


void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_wrap_vars_p(threadData_t *threadData , void* v_dst , modelica_real in_LGAX, modelica_real in_LFZO, modelica_real in_PCX1, modelica_real in_PDX1, modelica_real in_PDX2, modelica_real in_PDX3, modelica_real in_PKX1, modelica_real in_PKX2, modelica_real in_PKX3, modelica_real in_PHX1, modelica_real in_PHX2, modelica_real in_PVX1, modelica_real in_PVX2, modelica_real in_PEX1, modelica_real in_PEX2, modelica_real in_PEX3, modelica_real in_PEX4, modelica_real in_LCX, modelica_real in_LMUX, modelica_real in_LKX, modelica_real in_LHX, modelica_real in_LVX, modelica_real in_LEX, modelica_real in_LXAL);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_wrap_vars(td, dst , in_LGAX, in_LFZO, in_PCX1, in_PDX1, in_PDX2, in_PDX3, in_PKX1, in_PKX2, in_PKX3, in_PHX1, in_PHX2, in_PVX1, in_PVX2, in_PEX1, in_PEX2, in_PEX3, in_PEX4, in_LCX, in_LMUX, in_LKX, in_LHX, in_LVX, in_LEX, in_LXAL) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_wrap_vars_p(td, &dst , in_LGAX, in_LFZO, in_PCX1, in_PDX1, in_PDX2, in_PDX3, in_PKX1, in_PKX2, in_PKX3, in_PHX1, in_PHX2, in_PVX1, in_PVX2, in_PEX1, in_PEX2, in_PEX3, in_PEX4, in_LCX, in_LMUX, in_LKX, in_LHX, in_LVX, in_LEX, in_LXAL)

// This function is not needed anymore. If you want to know how a record
// is 'assigned to' in simulation context see assignRhsExpToRecordCrefSimContext and
// splitRecordAssignmentToMemberAssignments (simCode). Basically the record is
// split up assignments generated for each member individually.
// void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_copy_to_vars_p(void* v_src , modelica_real* in_LGAX, modelica_real* in_LFZO, modelica_real* in_PCX1, modelica_real* in_PDX1, modelica_real* in_PDX2, modelica_real* in_PDX3, modelica_real* in_PKX1, modelica_real* in_PKX2, modelica_real* in_PKX3, modelica_real* in_PHX1, modelica_real* in_PHX2, modelica_real* in_PVX1, modelica_real* in_PVX2, modelica_real* in_PEX1, modelica_real* in_PEX2, modelica_real* in_PEX3, modelica_real* in_PEX4, modelica_real* in_LCX, modelica_real* in_LMUX, modelica_real* in_LKX, modelica_real* in_LHX, modelica_real* in_LVX, modelica_real* in_LEX, modelica_real* in_LXAL);
// #define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_copy_to_vars(src,...) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_copy_to_vars_p(&src, __VA_ARGS__)

typedef base_array_t BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_array;
#define alloc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_array(dst,ndims,...) generic_array_create(NULL, dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_construct_p, ndims, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord), __VA_ARGS__)
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_array_copy_data(src,dst)   generic_array_copy_data(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_array_alloc_copy(src,dst)  generic_array_alloc_copy(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_array_get(src,ndims,...)   (*(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord*)(generic_array_get(&src, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord), __VA_ARGS__)))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_set(dst,val,...)           generic_array_set(&dst, &val, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord), __VA_ARGS__)

typedef struct {
  modelica_real _RBX1;
  modelica_real _RBX2;
  modelica_real _RCX1;
  modelica_real _REX1;
  modelica_real _REX2;
  modelica_real _RHX1;
} BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord;
extern struct record_description BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord__desc;

void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_construct_p(threadData_t *threadData, void* v_ths );
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_construct(td, ths ) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_construct_p(td, &ths )
void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_copy_p(void* v_src, void* v_dst);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_copy(src,dst) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_copy_p(&src, &dst)


void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_wrap_vars_p(threadData_t *threadData , void* v_dst , modelica_real in_RBX1, modelica_real in_RBX2, modelica_real in_RCX1, modelica_real in_REX1, modelica_real in_REX2, modelica_real in_RHX1);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_wrap_vars(td, dst , in_RBX1, in_RBX2, in_RCX1, in_REX1, in_REX2, in_RHX1) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_wrap_vars_p(td, &dst , in_RBX1, in_RBX2, in_RCX1, in_REX1, in_REX2, in_RHX1)

// This function is not needed anymore. If you want to know how a record
// is 'assigned to' in simulation context see assignRhsExpToRecordCrefSimContext and
// splitRecordAssignmentToMemberAssignments (simCode). Basically the record is
// split up assignments generated for each member individually.
// void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_copy_to_vars_p(void* v_src , modelica_real* in_RBX1, modelica_real* in_RBX2, modelica_real* in_RCX1, modelica_real* in_REX1, modelica_real* in_REX2, modelica_real* in_RHX1);
// #define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_copy_to_vars(src,...) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_copy_to_vars_p(&src, __VA_ARGS__)

typedef base_array_t BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_array;
#define alloc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_array(dst,ndims,...) generic_array_create(NULL, dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_construct_p, ndims, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord), __VA_ARGS__)
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_array_copy_data(src,dst)   generic_array_copy_data(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_array_alloc_copy(src,dst)  generic_array_alloc_copy(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_array_get(src,ndims,...)   (*(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord*)(generic_array_get(&src, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord), __VA_ARGS__)))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_set(dst,val,...)           generic_array_set(&dst, &val, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord), __VA_ARGS__)

typedef struct {
  modelica_real _LFZO;
  modelica_real _LGAY;
  modelica_real _PCY1;
  modelica_real _PDY1;
  modelica_real _PDY2;
  modelica_real _PDY3;
  modelica_real _PKY1;
  modelica_real _PKY2;
  modelica_real _PKY3;
  modelica_real _PHY1;
  modelica_real _PHY2;
  modelica_real _PHY3;
  modelica_real _PVY1;
  modelica_real _PVY2;
  modelica_real _PVY3;
  modelica_real _PVY4;
  modelica_real _PEY1;
  modelica_real _PEY2;
  modelica_real _PEY3;
  modelica_real _PEY4;
  modelica_real _LCY;
  modelica_real _LMUY;
  modelica_real _LEY;
  modelica_real _LKY;
  modelica_real _LHY;
  modelica_real _LVY;
  modelica_real _LYKA;
  modelica_real _LVYKA;
} BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord;
extern struct record_description BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord__desc;

void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_construct_p(threadData_t *threadData, void* v_ths );
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_construct(td, ths ) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_construct_p(td, &ths )
void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_copy_p(void* v_src, void* v_dst);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_copy(src,dst) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_copy_p(&src, &dst)


void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_wrap_vars_p(threadData_t *threadData , void* v_dst , modelica_real in_LFZO, modelica_real in_LGAY, modelica_real in_PCY1, modelica_real in_PDY1, modelica_real in_PDY2, modelica_real in_PDY3, modelica_real in_PKY1, modelica_real in_PKY2, modelica_real in_PKY3, modelica_real in_PHY1, modelica_real in_PHY2, modelica_real in_PHY3, modelica_real in_PVY1, modelica_real in_PVY2, modelica_real in_PVY3, modelica_real in_PVY4, modelica_real in_PEY1, modelica_real in_PEY2, modelica_real in_PEY3, modelica_real in_PEY4, modelica_real in_LCY, modelica_real in_LMUY, modelica_real in_LEY, modelica_real in_LKY, modelica_real in_LHY, modelica_real in_LVY, modelica_real in_LYKA, modelica_real in_LVYKA);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_wrap_vars(td, dst , in_LFZO, in_LGAY, in_PCY1, in_PDY1, in_PDY2, in_PDY3, in_PKY1, in_PKY2, in_PKY3, in_PHY1, in_PHY2, in_PHY3, in_PVY1, in_PVY2, in_PVY3, in_PVY4, in_PEY1, in_PEY2, in_PEY3, in_PEY4, in_LCY, in_LMUY, in_LEY, in_LKY, in_LHY, in_LVY, in_LYKA, in_LVYKA) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_wrap_vars_p(td, &dst , in_LFZO, in_LGAY, in_PCY1, in_PDY1, in_PDY2, in_PDY3, in_PKY1, in_PKY2, in_PKY3, in_PHY1, in_PHY2, in_PHY3, in_PVY1, in_PVY2, in_PVY3, in_PVY4, in_PEY1, in_PEY2, in_PEY3, in_PEY4, in_LCY, in_LMUY, in_LEY, in_LKY, in_LHY, in_LVY, in_LYKA, in_LVYKA)

// This function is not needed anymore. If you want to know how a record
// is 'assigned to' in simulation context see assignRhsExpToRecordCrefSimContext and
// splitRecordAssignmentToMemberAssignments (simCode). Basically the record is
// split up assignments generated for each member individually.
// void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_copy_to_vars_p(void* v_src , modelica_real* in_LFZO, modelica_real* in_LGAY, modelica_real* in_PCY1, modelica_real* in_PDY1, modelica_real* in_PDY2, modelica_real* in_PDY3, modelica_real* in_PKY1, modelica_real* in_PKY2, modelica_real* in_PKY3, modelica_real* in_PHY1, modelica_real* in_PHY2, modelica_real* in_PHY3, modelica_real* in_PVY1, modelica_real* in_PVY2, modelica_real* in_PVY3, modelica_real* in_PVY4, modelica_real* in_PEY1, modelica_real* in_PEY2, modelica_real* in_PEY3, modelica_real* in_PEY4, modelica_real* in_LCY, modelica_real* in_LMUY, modelica_real* in_LEY, modelica_real* in_LKY, modelica_real* in_LHY, modelica_real* in_LVY, modelica_real* in_LYKA, modelica_real* in_LVYKA);
// #define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_copy_to_vars(src,...) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_copy_to_vars_p(&src, __VA_ARGS__)

typedef base_array_t BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_array;
#define alloc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_array(dst,ndims,...) generic_array_create(NULL, dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_construct_p, ndims, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord), __VA_ARGS__)
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_array_copy_data(src,dst)   generic_array_copy_data(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_array_alloc_copy(src,dst)  generic_array_alloc_copy(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_array_get(src,ndims,...)   (*(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord*)(generic_array_get(&src, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord), __VA_ARGS__)))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_set(dst,val,...)           generic_array_set(&dst, &val, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord), __VA_ARGS__)

typedef struct {
  modelica_real _RBY1;
  modelica_real _RBY2;
  modelica_real _RBY3;
  modelica_real _RCY1;
  modelica_real _REY1;
  modelica_real _REY2;
  modelica_real _RHY1;
  modelica_real _RHY2;
  modelica_real _RVY1;
  modelica_real _RVY2;
  modelica_real _RVY3;
  modelica_real _RVY4;
  modelica_real _RVY5;
  modelica_real _RVY6;
} BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord;
extern struct record_description BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord__desc;

void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_construct_p(threadData_t *threadData, void* v_ths );
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_construct(td, ths ) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_construct_p(td, &ths )
void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_copy_p(void* v_src, void* v_dst);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_copy(src,dst) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_copy_p(&src, &dst)


void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_wrap_vars_p(threadData_t *threadData , void* v_dst , modelica_real in_RBY1, modelica_real in_RBY2, modelica_real in_RBY3, modelica_real in_RCY1, modelica_real in_REY1, modelica_real in_REY2, modelica_real in_RHY1, modelica_real in_RHY2, modelica_real in_RVY1, modelica_real in_RVY2, modelica_real in_RVY3, modelica_real in_RVY4, modelica_real in_RVY5, modelica_real in_RVY6);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_wrap_vars(td, dst , in_RBY1, in_RBY2, in_RBY3, in_RCY1, in_REY1, in_REY2, in_RHY1, in_RHY2, in_RVY1, in_RVY2, in_RVY3, in_RVY4, in_RVY5, in_RVY6) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_wrap_vars_p(td, &dst , in_RBY1, in_RBY2, in_RBY3, in_RCY1, in_REY1, in_REY2, in_RHY1, in_RHY2, in_RVY1, in_RVY2, in_RVY3, in_RVY4, in_RVY5, in_RVY6)

// This function is not needed anymore. If you want to know how a record
// is 'assigned to' in simulation context see assignRhsExpToRecordCrefSimContext and
// splitRecordAssignmentToMemberAssignments (simCode). Basically the record is
// split up assignments generated for each member individually.
// void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_copy_to_vars_p(void* v_src , modelica_real* in_RBY1, modelica_real* in_RBY2, modelica_real* in_RBY3, modelica_real* in_RCY1, modelica_real* in_REY1, modelica_real* in_REY2, modelica_real* in_RHY1, modelica_real* in_RHY2, modelica_real* in_RVY1, modelica_real* in_RVY2, modelica_real* in_RVY3, modelica_real* in_RVY4, modelica_real* in_RVY5, modelica_real* in_RVY6);
// #define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_copy_to_vars(src,...) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_copy_to_vars_p(&src, __VA_ARGS__)

typedef base_array_t BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_array;
#define alloc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_array(dst,ndims,...) generic_array_create(NULL, dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_construct_p, ndims, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord), __VA_ARGS__)
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_array_copy_data(src,dst)   generic_array_copy_data(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_array_alloc_copy(src,dst)  generic_array_alloc_copy(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_array_get(src,ndims,...)   (*(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord*)(generic_array_get(&src, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord), __VA_ARGS__)))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_set(dst,val,...)           generic_array_set(&dst, &val, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord), __VA_ARGS__)

typedef struct {
  modelica_real _QSX1;
  modelica_real _QSX2;
  modelica_real _QSX3;
  modelica_real _LMX;
  modelica_real _LVMX;
} BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord;
extern struct record_description BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord__desc;

void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_construct_p(threadData_t *threadData, void* v_ths );
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_construct(td, ths ) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_construct_p(td, &ths )
void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_copy_p(void* v_src, void* v_dst);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_copy(src,dst) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_copy_p(&src, &dst)


void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_wrap_vars_p(threadData_t *threadData , void* v_dst , modelica_real in_QSX1, modelica_real in_QSX2, modelica_real in_QSX3, modelica_real in_LMX, modelica_real in_LVMX);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_wrap_vars(td, dst , in_QSX1, in_QSX2, in_QSX3, in_LMX, in_LVMX) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_wrap_vars_p(td, &dst , in_QSX1, in_QSX2, in_QSX3, in_LMX, in_LVMX)

// This function is not needed anymore. If you want to know how a record
// is 'assigned to' in simulation context see assignRhsExpToRecordCrefSimContext and
// splitRecordAssignmentToMemberAssignments (simCode). Basically the record is
// split up assignments generated for each member individually.
// void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_copy_to_vars_p(void* v_src , modelica_real* in_QSX1, modelica_real* in_QSX2, modelica_real* in_QSX3, modelica_real* in_LMX, modelica_real* in_LVMX);
// #define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_copy_to_vars(src,...) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_copy_to_vars_p(&src, __VA_ARGS__)

typedef base_array_t BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_array;
#define alloc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_array(dst,ndims,...) generic_array_create(NULL, dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_construct_p, ndims, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord), __VA_ARGS__)
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_array_copy_data(src,dst)   generic_array_copy_data(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_array_alloc_copy(src,dst)  generic_array_alloc_copy(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_array_get(src,ndims,...)   (*(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord*)(generic_array_get(&src, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord), __VA_ARGS__)))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_set(dst,val,...)           generic_array_set(&dst, &val, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord), __VA_ARGS__)

typedef struct {
} BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord;
extern struct record_description BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord__desc;

void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_construct_p(threadData_t *threadData, void* v_ths );
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_construct(td, ths ) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_construct_p(td, &ths )
void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_copy_p(void* v_src, void* v_dst);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_copy(src,dst) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_copy_p(&src, &dst)


void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_wrap_vars_p(threadData_t *threadData , void* v_dst );
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_wrap_vars(td, dst ) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_wrap_vars_p(td, &dst )

// This function is not needed anymore. If you want to know how a record
// is 'assigned to' in simulation context see assignRhsExpToRecordCrefSimContext and
// splitRecordAssignmentToMemberAssignments (simCode). Basically the record is
// split up assignments generated for each member individually.
// void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_copy_to_vars_p(void* v_src );
// #define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_copy_to_vars(src,...) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_copy_to_vars_p(&src, __VA_ARGS__)

typedef base_array_t BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_array;
#define alloc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_array(dst,ndims,...) generic_array_create(NULL, dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_construct_p, ndims, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord), __VA_ARGS__)
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_array_copy_data(src,dst)   generic_array_copy_data(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_array_alloc_copy(src,dst)  generic_array_alloc_copy(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_array_get(src,ndims,...)   (*(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord*)(generic_array_get(&src, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord), __VA_ARGS__)))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_set(dst,val,...)           generic_array_set(&dst, &val, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord), __VA_ARGS__)

typedef struct {
  modelica_real _QSY1;
  modelica_real _QSY2;
  modelica_real _QSY3;
  modelica_real _QSY4;
  modelica_real _Vref;
  modelica_real _LMY;
} BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord;
extern struct record_description BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord__desc;

void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_construct_p(threadData_t *threadData, void* v_ths );
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_construct(td, ths ) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_construct_p(td, &ths )
void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_copy_p(void* v_src, void* v_dst);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_copy(src,dst) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_copy_p(&src, &dst)


void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_wrap_vars_p(threadData_t *threadData , void* v_dst , modelica_real in_QSY1, modelica_real in_QSY2, modelica_real in_QSY3, modelica_real in_QSY4, modelica_real in_Vref, modelica_real in_LMY);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_wrap_vars(td, dst , in_QSY1, in_QSY2, in_QSY3, in_QSY4, in_Vref, in_LMY) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_wrap_vars_p(td, &dst , in_QSY1, in_QSY2, in_QSY3, in_QSY4, in_Vref, in_LMY)

// This function is not needed anymore. If you want to know how a record
// is 'assigned to' in simulation context see assignRhsExpToRecordCrefSimContext and
// splitRecordAssignmentToMemberAssignments (simCode). Basically the record is
// split up assignments generated for each member individually.
// void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_copy_to_vars_p(void* v_src , modelica_real* in_QSY1, modelica_real* in_QSY2, modelica_real* in_QSY3, modelica_real* in_QSY4, modelica_real* in_Vref, modelica_real* in_LMY);
// #define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_copy_to_vars(src,...) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_copy_to_vars_p(&src, __VA_ARGS__)

typedef base_array_t BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_array;
#define alloc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_array(dst,ndims,...) generic_array_create(NULL, dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_construct_p, ndims, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord), __VA_ARGS__)
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_array_copy_data(src,dst)   generic_array_copy_data(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_array_alloc_copy(src,dst)  generic_array_alloc_copy(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_array_get(src,ndims,...)   (*(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord*)(generic_array_get(&src, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord), __VA_ARGS__)))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_set(dst,val,...)           generic_array_set(&dst, &val, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord), __VA_ARGS__)

typedef struct {
  modelica_real _QBZ1;
  modelica_real _QBZ2;
  modelica_real _QBZ3;
  modelica_real _QBZ4;
  modelica_real _QBZ5;
  modelica_real _QCZ1;
  modelica_real _QDZ1;
  modelica_real _QDZ2;
  modelica_real _QDZ3;
  modelica_real _QDZ4;
  modelica_real _QEZ1;
  modelica_real _QEZ2;
  modelica_real _QEZ3;
  modelica_real _QEZ4;
  modelica_real _QEZ5;
  modelica_real _QHZ1;
  modelica_real _QHZ2;
  modelica_real _QHZ3;
  modelica_real _QHZ4;
  modelica_real _QBZ9;
  modelica_real _QBZ10;
  modelica_real _QDZ6;
  modelica_real _QDZ7;
  modelica_real _QDZ8;
  modelica_real _QDZ9;
  modelica_real _LTR;
  modelica_real _LRES;
  modelica_real _LKY;
  modelica_real _LMUY;
  modelica_real _LGAZ;
} BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord;
extern struct record_description BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord__desc;

void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_construct_p(threadData_t *threadData, void* v_ths );
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_construct(td, ths ) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_construct_p(td, &ths )
void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_copy_p(void* v_src, void* v_dst);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_copy(src,dst) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_copy_p(&src, &dst)


void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_wrap_vars_p(threadData_t *threadData , void* v_dst , modelica_real in_QBZ1, modelica_real in_QBZ2, modelica_real in_QBZ3, modelica_real in_QBZ4, modelica_real in_QBZ5, modelica_real in_QCZ1, modelica_real in_QDZ1, modelica_real in_QDZ2, modelica_real in_QDZ3, modelica_real in_QDZ4, modelica_real in_QEZ1, modelica_real in_QEZ2, modelica_real in_QEZ3, modelica_real in_QEZ4, modelica_real in_QEZ5, modelica_real in_QHZ1, modelica_real in_QHZ2, modelica_real in_QHZ3, modelica_real in_QHZ4, modelica_real in_QBZ9, modelica_real in_QBZ10, modelica_real in_QDZ6, modelica_real in_QDZ7, modelica_real in_QDZ8, modelica_real in_QDZ9, modelica_real in_LTR, modelica_real in_LRES, modelica_real in_LKY, modelica_real in_LMUY, modelica_real in_LGAZ);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_wrap_vars(td, dst , in_QBZ1, in_QBZ2, in_QBZ3, in_QBZ4, in_QBZ5, in_QCZ1, in_QDZ1, in_QDZ2, in_QDZ3, in_QDZ4, in_QEZ1, in_QEZ2, in_QEZ3, in_QEZ4, in_QEZ5, in_QHZ1, in_QHZ2, in_QHZ3, in_QHZ4, in_QBZ9, in_QBZ10, in_QDZ6, in_QDZ7, in_QDZ8, in_QDZ9, in_LTR, in_LRES, in_LKY, in_LMUY, in_LGAZ) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_wrap_vars_p(td, &dst , in_QBZ1, in_QBZ2, in_QBZ3, in_QBZ4, in_QBZ5, in_QCZ1, in_QDZ1, in_QDZ2, in_QDZ3, in_QDZ4, in_QEZ1, in_QEZ2, in_QEZ3, in_QEZ4, in_QEZ5, in_QHZ1, in_QHZ2, in_QHZ3, in_QHZ4, in_QBZ9, in_QBZ10, in_QDZ6, in_QDZ7, in_QDZ8, in_QDZ9, in_LTR, in_LRES, in_LKY, in_LMUY, in_LGAZ)

// This function is not needed anymore. If you want to know how a record
// is 'assigned to' in simulation context see assignRhsExpToRecordCrefSimContext and
// splitRecordAssignmentToMemberAssignments (simCode). Basically the record is
// split up assignments generated for each member individually.
// void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_copy_to_vars_p(void* v_src , modelica_real* in_QBZ1, modelica_real* in_QBZ2, modelica_real* in_QBZ3, modelica_real* in_QBZ4, modelica_real* in_QBZ5, modelica_real* in_QCZ1, modelica_real* in_QDZ1, modelica_real* in_QDZ2, modelica_real* in_QDZ3, modelica_real* in_QDZ4, modelica_real* in_QEZ1, modelica_real* in_QEZ2, modelica_real* in_QEZ3, modelica_real* in_QEZ4, modelica_real* in_QEZ5, modelica_real* in_QHZ1, modelica_real* in_QHZ2, modelica_real* in_QHZ3, modelica_real* in_QHZ4, modelica_real* in_QBZ9, modelica_real* in_QBZ10, modelica_real* in_QDZ6, modelica_real* in_QDZ7, modelica_real* in_QDZ8, modelica_real* in_QDZ9, modelica_real* in_LTR, modelica_real* in_LRES, modelica_real* in_LKY, modelica_real* in_LMUY, modelica_real* in_LGAZ);
// #define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_copy_to_vars(src,...) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_copy_to_vars_p(&src, __VA_ARGS__)

typedef base_array_t BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_array;
#define alloc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_array(dst,ndims,...) generic_array_create(NULL, dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_construct_p, ndims, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord), __VA_ARGS__)
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_array_copy_data(src,dst)   generic_array_copy_data(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_array_alloc_copy(src,dst)  generic_array_alloc_copy(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_array_get(src,ndims,...)   (*(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord*)(generic_array_get(&src, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord), __VA_ARGS__)))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_set(dst,val,...)           generic_array_set(&dst, &val, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord), __VA_ARGS__)

typedef struct {
  modelica_real _SSZ1;
  modelica_real _SSZ2;
  modelica_real _SSZ3;
  modelica_real _SSZ4;
  modelica_real _RVY1;
  modelica_real _RVY2;
  modelica_real _RVY3;
  modelica_real _RVY4;
  modelica_real _RVY5;
  modelica_real _RVY6;
  modelica_real _LS;
  modelica_real _LVYKA;
} BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord;
extern struct record_description BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord__desc;

void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_construct_p(threadData_t *threadData, void* v_ths );
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_construct(td, ths ) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_construct_p(td, &ths )
void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_copy_p(void* v_src, void* v_dst);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_copy(src,dst) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_copy_p(&src, &dst)


void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_wrap_vars_p(threadData_t *threadData , void* v_dst , modelica_real in_SSZ1, modelica_real in_SSZ2, modelica_real in_SSZ3, modelica_real in_SSZ4, modelica_real in_RVY1, modelica_real in_RVY2, modelica_real in_RVY3, modelica_real in_RVY4, modelica_real in_RVY5, modelica_real in_RVY6, modelica_real in_LS, modelica_real in_LVYKA);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_wrap_vars(td, dst , in_SSZ1, in_SSZ2, in_SSZ3, in_SSZ4, in_RVY1, in_RVY2, in_RVY3, in_RVY4, in_RVY5, in_RVY6, in_LS, in_LVYKA) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_wrap_vars_p(td, &dst , in_SSZ1, in_SSZ2, in_SSZ3, in_SSZ4, in_RVY1, in_RVY2, in_RVY3, in_RVY4, in_RVY5, in_RVY6, in_LS, in_LVYKA)

// This function is not needed anymore. If you want to know how a record
// is 'assigned to' in simulation context see assignRhsExpToRecordCrefSimContext and
// splitRecordAssignmentToMemberAssignments (simCode). Basically the record is
// split up assignments generated for each member individually.
// void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_copy_to_vars_p(void* v_src , modelica_real* in_SSZ1, modelica_real* in_SSZ2, modelica_real* in_SSZ3, modelica_real* in_SSZ4, modelica_real* in_RVY1, modelica_real* in_RVY2, modelica_real* in_RVY3, modelica_real* in_RVY4, modelica_real* in_RVY5, modelica_real* in_RVY6, modelica_real* in_LS, modelica_real* in_LVYKA);
// #define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_copy_to_vars(src,...) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_copy_to_vars_p(&src, __VA_ARGS__)

typedef base_array_t BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_array;
#define alloc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_array(dst,ndims,...) generic_array_create(NULL, dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_construct_p, ndims, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord), __VA_ARGS__)
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_array_copy_data(src,dst)   generic_array_copy_data(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_array_alloc_copy(src,dst)  generic_array_alloc_copy(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_array_get(src,ndims,...)   (*(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord*)(generic_array_get(&src, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord), __VA_ARGS__)))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_set(dst,val,...)           generic_array_set(&dst, &val, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord), __VA_ARGS__)

typedef struct {
  real_array _T;
  real_array _w;
} Modelica_Mechanics_MultiBody_Frames_Orientation;
extern struct record_description Modelica_Mechanics_MultiBody_Frames_Orientation__desc;

void Modelica_Mechanics_MultiBody_Frames_Orientation_construct_p(threadData_t *threadData, void* v_ths );
#define Modelica_Mechanics_MultiBody_Frames_Orientation_construct(td, ths ) Modelica_Mechanics_MultiBody_Frames_Orientation_construct_p(td, &ths )
void Modelica_Mechanics_MultiBody_Frames_Orientation_copy_p(void* v_src, void* v_dst);
#define Modelica_Mechanics_MultiBody_Frames_Orientation_copy(src,dst) Modelica_Mechanics_MultiBody_Frames_Orientation_copy_p(&src, &dst)


void Modelica_Mechanics_MultiBody_Frames_Orientation_wrap_vars_p(threadData_t *threadData , void* v_dst , real_array in_T, real_array in_w);
#define Modelica_Mechanics_MultiBody_Frames_Orientation_wrap_vars(td, dst , in_T, in_w) Modelica_Mechanics_MultiBody_Frames_Orientation_wrap_vars_p(td, &dst , in_T, in_w)

// This function is not needed anymore. If you want to know how a record
// is 'assigned to' in simulation context see assignRhsExpToRecordCrefSimContext and
// splitRecordAssignmentToMemberAssignments (simCode). Basically the record is
// split up assignments generated for each member individually.
// void Modelica_Mechanics_MultiBody_Frames_Orientation_copy_to_vars_p(void* v_src , real_array* in_T, real_array* in_w);
// #define Modelica_Mechanics_MultiBody_Frames_Orientation_copy_to_vars(src,...) Modelica_Mechanics_MultiBody_Frames_Orientation_copy_to_vars_p(&src, __VA_ARGS__)

typedef base_array_t Modelica_Mechanics_MultiBody_Frames_Orientation_array;
#define alloc_Modelica_Mechanics_MultiBody_Frames_Orientation_array(dst,ndims,...) generic_array_create(NULL, dst, Modelica_Mechanics_MultiBody_Frames_Orientation_construct_p, ndims, sizeof(Modelica_Mechanics_MultiBody_Frames_Orientation), __VA_ARGS__)
#define Modelica_Mechanics_MultiBody_Frames_Orientation_array_copy_data(src,dst)   generic_array_copy_data(src, &dst, Modelica_Mechanics_MultiBody_Frames_Orientation_copy_p, sizeof(Modelica_Mechanics_MultiBody_Frames_Orientation))
#define Modelica_Mechanics_MultiBody_Frames_Orientation_array_alloc_copy(src,dst)  generic_array_alloc_copy(src, &dst, Modelica_Mechanics_MultiBody_Frames_Orientation_copy_p, sizeof(Modelica_Mechanics_MultiBody_Frames_Orientation))
#define Modelica_Mechanics_MultiBody_Frames_Orientation_array_get(src,ndims,...)   (*(Modelica_Mechanics_MultiBody_Frames_Orientation*)(generic_array_get(&src, sizeof(Modelica_Mechanics_MultiBody_Frames_Orientation), __VA_ARGS__)))
#define Modelica_Mechanics_MultiBody_Frames_Orientation_set(dst,val,...)           generic_array_set(&dst, &val, Modelica_Mechanics_MultiBody_Frames_Orientation_copy_p, sizeof(Modelica_Mechanics_MultiBody_Frames_Orientation), __VA_ARGS__)

typedef BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord;
extern struct record_description BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord__desc;

void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_construct_p(threadData_t *threadData, void* v_ths );
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_construct(td, ths ) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_construct_p(td, &ths )
void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_copy_p(void* v_src, void* v_dst);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_copy(src,dst) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_copy_p(&src, &dst)


void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_wrap_vars_p(threadData_t *threadData , void* v_dst );
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_wrap_vars(td, dst ) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_wrap_vars_p(td, &dst )

// This function is not needed anymore. If you want to know how a record
// is 'assigned to' in simulation context see assignRhsExpToRecordCrefSimContext and
// splitRecordAssignmentToMemberAssignments (simCode). Basically the record is
// split up assignments generated for each member individually.
// void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_copy_to_vars_p(void* v_src );
// #define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_copy_to_vars(src,...) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_copy_to_vars_p(&src, __VA_ARGS__)

typedef base_array_t BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_array;
#define alloc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_array(dst,ndims,...) generic_array_create(NULL, dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_construct_p, ndims, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord), __VA_ARGS__)
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_array_copy_data(src,dst)   generic_array_copy_data(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_array_alloc_copy(src,dst)  generic_array_alloc_copy(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_array_get(src,ndims,...)   (*(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord*)(generic_array_get(&src, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord), __VA_ARGS__)))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_set(dst,val,...)           generic_array_set(&dst, &val, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord), __VA_ARGS__)

typedef struct {
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord _setup;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord _relaxation;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord _fxPure;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord _fxCombined;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord _fyPure;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord _fyCombined;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord _mxPure;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord _mxCombined;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord _myPure;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord _myCombined;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord _mzPure;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord _mzCombined;
} BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record;
extern struct record_description BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record__desc;

void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_construct_p(threadData_t *threadData, void* v_ths );
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_construct(td, ths ) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_construct_p(td, &ths )
void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_copy_p(void* v_src, void* v_dst);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_copy(src,dst) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_copy_p(&src, &dst)


void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_wrap_vars_p(threadData_t *threadData , void* v_dst , BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord in_setup, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord in_relaxation, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord in_fxPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord in_fxCombined, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord in_fyPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord in_fyCombined, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord in_mxPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord in_mxCombined, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord in_myPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord in_myCombined, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord in_mzPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord in_mzCombined);
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_wrap_vars(td, dst , in_setup, in_relaxation, in_fxPure, in_fxCombined, in_fyPure, in_fyCombined, in_mxPure, in_mxCombined, in_myPure, in_myCombined, in_mzPure, in_mzCombined) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_wrap_vars_p(td, &dst , in_setup, in_relaxation, in_fxPure, in_fxCombined, in_fyPure, in_fyCombined, in_mxPure, in_mxCombined, in_myPure, in_myCombined, in_mzPure, in_mzCombined)

// This function is not needed anymore. If you want to know how a record
// is 'assigned to' in simulation context see assignRhsExpToRecordCrefSimContext and
// splitRecordAssignmentToMemberAssignments (simCode). Basically the record is
// split up assignments generated for each member individually.
// void BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_copy_to_vars_p(void* v_src , BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord* in_setup, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord* in_relaxation, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord* in_fxPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord* in_fxCombined, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord* in_fyPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord* in_fyCombined, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord* in_mxPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord* in_mxCombined, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord* in_myPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord* in_myCombined, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord* in_mzPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord* in_mzCombined);
// #define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_copy_to_vars(src,...) BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_copy_to_vars_p(&src, __VA_ARGS__)

typedef base_array_t BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_array;
#define alloc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_array(dst,ndims,...) generic_array_create(NULL, dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_construct_p, ndims, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record), __VA_ARGS__)
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_array_copy_data(src,dst)   generic_array_copy_data(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_array_alloc_copy(src,dst)  generic_array_alloc_copy(src, &dst, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_array_get(src,ndims,...)   (*(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record*)(generic_array_get(&src, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record), __VA_ARGS__)))
#define BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_set(dst,val,...)           generic_array_set(&dst, &val, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_copy_p, sizeof(BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record), __VA_ARGS__)

DLLDirection
real_array omc__omcQ_24DER_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData_t *threadData, real_array _r, real_array __omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr, real_array __omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr, real_array __omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr);
DLLDirection
modelica_metatype boxptr__omcQ_24DER_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData_t *threadData, modelica_metatype _r, modelica_metatype __omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr, modelica_metatype __omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr, modelica_metatype __omcQ_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr);
static const MMC_DEFSTRUCTLIT(boxvar_lit__omcQ_24DER_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ,2,0) {(void*) boxptr__omcQ_24DER_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ,0}};
#define boxvar__omcQ_24DER_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ MMC_REFSTRUCTLIT(boxvar_lit__omcQ_24DER_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ)


DLLDirection
real_array omc__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData_t *threadData, real_array _r, real_array __omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr);
DLLDirection
modelica_metatype boxptr__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData_t *threadData, modelica_metatype _r, modelica_metatype __omcQ_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ_24funDERr);
static const MMC_DEFSTRUCTLIT(boxvar_lit__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ,2,0) {(void*) boxptr__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ,0}};
#define boxvar__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ MMC_REFSTRUCTLIT(boxvar_lit__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ)


DLLDirection
modelica_real omc_BobLib_Aero_Internal_Bilinear2D(threadData_t *threadData, modelica_real _x, modelica_real _y, real_array _xGrid, real_array _yGrid, real_array _table);
DLLDirection
modelica_metatype boxptr_BobLib_Aero_Internal_Bilinear2D(threadData_t *threadData, modelica_metatype _x, modelica_metatype _y, modelica_metatype _xGrid, modelica_metatype _yGrid, modelica_metatype _table);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Aero_Internal_Bilinear2D,2,0) {(void*) boxptr_BobLib_Aero_Internal_Bilinear2D,0}};
#define boxvar_BobLib_Aero_Internal_Bilinear2D MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Aero_Internal_Bilinear2D)


DLLDirection
modelica_real omc_BobLib_Chassis_Suspension_Tires_MF52_Eval(threadData_t *threadData, modelica_real _Fz, modelica_real _alpha, modelica_real _kappa, modelica_real _gamma, modelica_real _Vx, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record _tire, modelica_real *out_Fy, modelica_real *out_Mx, modelica_real *out_My, modelica_real *out_Mz, modelica_real *out_t, modelica_real *out_s);
DLLDirection
modelica_metatype boxptr_BobLib_Chassis_Suspension_Tires_MF52_Eval(threadData_t *threadData, modelica_metatype _Fz, modelica_metatype _alpha, modelica_metatype _kappa, modelica_metatype _gamma, modelica_metatype _Vx, modelica_metatype _tire, modelica_metatype *out_Fy, modelica_metatype *out_Mx, modelica_metatype *out_My, modelica_metatype *out_Mz, modelica_metatype *out_t, modelica_metatype *out_s);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Chassis_Suspension_Tires_MF52_Eval,2,0) {(void*) boxptr_BobLib_Chassis_Suspension_Tires_MF52_Eval,0}};
#define boxvar_BobLib_Chassis_Suspension_Tires_MF52_Eval MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Chassis_Suspension_Tires_MF52_Eval)


DLLDirection
modelica_real omc_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_FxCombinedEval(threadData_t *threadData, modelica_real _Fz, modelica_real _kappa, modelica_real _alpha, modelica_real _gamma, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord _pPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord _pComb, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord _setup);
DLLDirection
modelica_metatype boxptr_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_FxCombinedEval(threadData_t *threadData, modelica_metatype _Fz, modelica_metatype _kappa, modelica_metatype _alpha, modelica_metatype _gamma, modelica_metatype _pPure, modelica_metatype _pComb, modelica_metatype _setup);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_FxCombinedEval,2,0) {(void*) boxptr_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_FxCombinedEval,0}};
#define boxvar_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_FxCombinedEval MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_FxCombinedEval)


DLLDirection
modelica_real omc_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_FyCombinedEval(threadData_t *threadData, modelica_real _Fz, modelica_real _alpha, modelica_real _kappa, modelica_real _gamma, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord _pPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord _pComb, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord _setup);
DLLDirection
modelica_metatype boxptr_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_FyCombinedEval(threadData_t *threadData, modelica_metatype _Fz, modelica_metatype _alpha, modelica_metatype _kappa, modelica_metatype _gamma, modelica_metatype _pPure, modelica_metatype _pComb, modelica_metatype _setup);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_FyCombinedEval,2,0) {(void*) boxptr_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_FyCombinedEval,0}};
#define boxvar_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_FyCombinedEval MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_FyCombinedEval)


DLLDirection
modelica_real omc_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MxCombinedEval(threadData_t *threadData, modelica_real _Fz, modelica_real _Fy, modelica_real _gamma, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord _pPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord _pComb, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord _setup);
DLLDirection
modelica_metatype boxptr_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MxCombinedEval(threadData_t *threadData, modelica_metatype _Fz, modelica_metatype _Fy, modelica_metatype _gamma, modelica_metatype _pPure, modelica_metatype _pComb, modelica_metatype _setup);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MxCombinedEval,2,0) {(void*) boxptr_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MxCombinedEval,0}};
#define boxvar_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MxCombinedEval MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MxCombinedEval)


DLLDirection
modelica_real omc_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MyCombinedEval(threadData_t *threadData, modelica_real _Fz, modelica_real _Fx, modelica_real _Vx, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord _pPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord _pFx, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord _pComb, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord _setup);
DLLDirection
modelica_metatype boxptr_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MyCombinedEval(threadData_t *threadData, modelica_metatype _Fz, modelica_metatype _Fx, modelica_metatype _Vx, modelica_metatype _pPure, modelica_metatype _pFx, modelica_metatype _pComb, modelica_metatype _setup);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MyCombinedEval,2,0) {(void*) boxptr_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MyCombinedEval,0}};
#define boxvar_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MyCombinedEval MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MyCombinedEval)


DLLDirection
modelica_real omc_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MzCombinedEval(threadData_t *threadData, modelica_real _Fz, modelica_real _Fx, modelica_real _Fy, modelica_real _alpha, modelica_real _kappa, modelica_real _gamma, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord _pFy, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord _pFx, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord _pPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord _pComb, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord _setup, modelica_real *out_t, modelica_real *out_s);
DLLDirection
modelica_metatype boxptr_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MzCombinedEval(threadData_t *threadData, modelica_metatype _Fz, modelica_metatype _Fx, modelica_metatype _Fy, modelica_metatype _alpha, modelica_metatype _kappa, modelica_metatype _gamma, modelica_metatype _pFy, modelica_metatype _pFx, modelica_metatype _pPure, modelica_metatype _pComb, modelica_metatype _setup, modelica_metatype *out_t, modelica_metatype *out_s);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MzCombinedEval,2,0) {(void*) boxptr_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MzCombinedEval,0}};
#define boxvar_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MzCombinedEval MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Chassis_Suspension_Tires_MF52_CombinedSlip_MzCombinedEval)


DLLDirection
modelica_real omc_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_FxPureEval(threadData_t *threadData, modelica_real _Fz, modelica_real _kappa, modelica_real _gamma, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord _p, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord _setup);
DLLDirection
modelica_metatype boxptr_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_FxPureEval(threadData_t *threadData, modelica_metatype _Fz, modelica_metatype _kappa, modelica_metatype _gamma, modelica_metatype _p, modelica_metatype _setup);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_FxPureEval,2,0) {(void*) boxptr_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_FxPureEval,0}};
#define boxvar_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_FxPureEval MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_FxPureEval)


DLLDirection
modelica_real omc_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_FyPureEval(threadData_t *threadData, modelica_real _Fz, modelica_real _alpha, modelica_real _gamma, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord _p, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord _setup);
DLLDirection
modelica_metatype boxptr_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_FyPureEval(threadData_t *threadData, modelica_metatype _Fz, modelica_metatype _alpha, modelica_metatype _gamma, modelica_metatype _p, modelica_metatype _setup);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_FyPureEval,2,0) {(void*) boxptr_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_FyPureEval,0}};
#define boxvar_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_FyPureEval MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_FyPureEval)


DLLDirection
modelica_real omc_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MxPureEval(threadData_t *threadData, modelica_real _Fz, modelica_real _Fy, modelica_real _gamma, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord _p, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord _setup);
DLLDirection
modelica_metatype boxptr_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MxPureEval(threadData_t *threadData, modelica_metatype _Fz, modelica_metatype _Fy, modelica_metatype _gamma, modelica_metatype _p, modelica_metatype _setup);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MxPureEval,2,0) {(void*) boxptr_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MxPureEval,0}};
#define boxvar_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MxPureEval MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MxPureEval)


DLLDirection
modelica_real omc_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MyPureEval(threadData_t *threadData, modelica_real _Fz, modelica_real _Fx, modelica_real _Vx, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord _p, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord _pFx, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord _setup);
DLLDirection
modelica_metatype boxptr_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MyPureEval(threadData_t *threadData, modelica_metatype _Fz, modelica_metatype _Fx, modelica_metatype _Vx, modelica_metatype _p, modelica_metatype _pFx, modelica_metatype _setup);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MyPureEval,2,0) {(void*) boxptr_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MyPureEval,0}};
#define boxvar_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MyPureEval MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MyPureEval)


DLLDirection
modelica_real omc_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MzPureEval(threadData_t *threadData, modelica_real _Fz, modelica_real _Fy, modelica_real _alpha, modelica_real _kappa, modelica_real _gamma, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord _pFy, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord _pFx, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord _p, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord _setup);
DLLDirection
modelica_metatype boxptr_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MzPureEval(threadData_t *threadData, modelica_metatype _Fz, modelica_metatype _Fy, modelica_metatype _alpha, modelica_metatype _kappa, modelica_metatype _gamma, modelica_metatype _pFy, modelica_metatype _pFx, modelica_metatype _p, modelica_metatype _setup);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MzPureEval,2,0) {(void*) boxptr_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MzPureEval,0}};
#define boxvar_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MzPureEval MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Chassis_Suspension_Tires_MF52_PureSlip_MzPureEval)


DLLDirection
modelica_boolean omc_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_frAxleDW_leftWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData_t *threadData, modelica_real _L, real_array _e, modelica_real _angle_guess, real_array _r_a, real_array _r_b);
DLLDirection
modelica_metatype boxptr_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_frAxleDW_leftWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData_t *threadData, modelica_metatype _L, modelica_metatype _e, modelica_metatype _angle_guess, modelica_metatype _r_a, modelica_metatype _r_b);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_frAxleDW_leftWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch,2,0) {(void*) boxptr_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_frAxleDW_leftWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch,0}};
#define boxvar_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_frAxleDW_leftWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_frAxleDW_leftWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch)


DLLDirection
modelica_boolean omc_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_frAxleDW_rightWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData_t *threadData, modelica_real _L, real_array _e, modelica_real _angle_guess, real_array _r_a, real_array _r_b);
DLLDirection
modelica_metatype boxptr_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_frAxleDW_rightWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData_t *threadData, modelica_metatype _L, modelica_metatype _e, modelica_metatype _angle_guess, modelica_metatype _r_a, modelica_metatype _r_b);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_frAxleDW_rightWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch,2,0) {(void*) boxptr_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_frAxleDW_rightWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch,0}};
#define boxvar_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_frAxleDW_rightWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_frAxleDW_rightWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch)


DLLDirection
modelica_boolean omc_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_rrAxleDW_leftWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData_t *threadData, modelica_real _L, real_array _e, modelica_real _angle_guess, real_array _r_a, real_array _r_b);
DLLDirection
modelica_metatype boxptr_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_rrAxleDW_leftWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData_t *threadData, modelica_metatype _L, modelica_metatype _e, modelica_metatype _angle_guess, modelica_metatype _r_a, modelica_metatype _r_b);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_rrAxleDW_leftWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch,2,0) {(void*) boxptr_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_rrAxleDW_leftWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch,0}};
#define boxvar_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_rrAxleDW_leftWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_rrAxleDW_leftWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch)


DLLDirection
modelica_boolean omc_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_rrAxleDW_rightWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData_t *threadData, modelica_real _L, real_array _e, modelica_real _angle_guess, real_array _r_a, real_array _r_b);
DLLDirection
modelica_metatype boxptr_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_rrAxleDW_rightWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch(threadData_t *threadData, modelica_metatype _L, modelica_metatype _e, modelica_metatype _angle_guess, modelica_metatype _r_a, modelica_metatype _r_b);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_rrAxleDW_rightWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch,2,0) {(void*) boxptr_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_rrAxleDW_rightWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch,0}};
#define boxvar_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_rrAxleDW_rightWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Experiments_Standards_VehicleSim_chassis_detailedChassis_rrAxleDW_rightWishboneUprightLoop_upperWishboneUpright_revolute_selectBranch)


DLLDirection
modelica_real omc_BobLib_Experiments_Standards_VehicleSim_motor_motor_interp1(threadData_t *threadData, real_array _tbl, modelica_real _xq);
DLLDirection
modelica_metatype boxptr_BobLib_Experiments_Standards_VehicleSim_motor_motor_interp1(threadData_t *threadData, modelica_metatype _tbl, modelica_metatype _xq);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Experiments_Standards_VehicleSim_motor_motor_interp1,2,0) {(void*) boxptr_BobLib_Experiments_Standards_VehicleSim_motor_motor_interp1,0}};
#define boxvar_BobLib_Experiments_Standards_VehicleSim_motor_motor_interp1 MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Experiments_Standards_VehicleSim_motor_motor_interp1)


DLLDirection
BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record (threadData_t *threadData, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord omc_setup, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord omc_relaxation, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord omc_fxPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord omc_fxCombined, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord omc_fyPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord omc_fyCombined, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord omc_mxPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord omc_mxCombined, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord omc_myPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord omc_myCombined, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord omc_mzPure, BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord omc_mzCombined);

DLLDirection
modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record(threadData_t *threadData, modelica_metatype _setup, modelica_metatype _relaxation, modelica_metatype _fxPure, modelica_metatype _fxCombined, modelica_metatype _fyPure, modelica_metatype _fyCombined, modelica_metatype _mxPure, modelica_metatype _mxCombined, modelica_metatype _myPure, modelica_metatype _myCombined, modelica_metatype _mzPure, modelica_metatype _mzCombined);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record,2,0) {(void*) boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record,0}};
#define boxvar_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record)


DLLDirection
BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord (threadData_t *threadData, modelica_real omc_FNOMIN, modelica_real omc_UNLOADED_RADIUS, modelica_real omc_LFZO, modelica_real omc_PTX1, modelica_real omc_PTX2, modelica_real omc_PTX3, modelica_real omc_PTY1, modelica_real omc_PTY2, modelica_real omc_PKY3, modelica_real omc_LSGKP, modelica_real omc_LSGAL);

DLLDirection
modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord(threadData_t *threadData, modelica_metatype _FNOMIN, modelica_metatype _UNLOADED_RADIUS, modelica_metatype _LFZO, modelica_metatype _PTX1, modelica_metatype _PTX2, modelica_metatype _PTX3, modelica_metatype _PTY1, modelica_metatype _PTY2, modelica_metatype _PKY3, modelica_metatype _LSGKP, modelica_metatype _LSGAL);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord,2,0) {(void*) boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord,0}};
#define boxvar_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord)


DLLDirection
BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord (threadData_t *threadData, modelica_real omc_FNOMIN, modelica_real omc_FZMIN, modelica_real omc_FZMAX, modelica_real omc_UNLOADED_RADIUS);

DLLDirection
modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord(threadData_t *threadData, modelica_metatype _FNOMIN, modelica_metatype _FZMIN, modelica_metatype _FZMAX, modelica_metatype _UNLOADED_RADIUS);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord,2,0) {(void*) boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord,0}};
#define boxvar_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord)


DLLDirection
BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord (threadData_t *threadData, modelica_real omc_RBX1, modelica_real omc_RBX2, modelica_real omc_RCX1, modelica_real omc_REX1, modelica_real omc_REX2, modelica_real omc_RHX1);

DLLDirection
modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord(threadData_t *threadData, modelica_metatype _RBX1, modelica_metatype _RBX2, modelica_metatype _RCX1, modelica_metatype _REX1, modelica_metatype _REX2, modelica_metatype _RHX1);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord,2,0) {(void*) boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord,0}};
#define boxvar_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord)


DLLDirection
BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord (threadData_t *threadData, modelica_real omc_RBY1, modelica_real omc_RBY2, modelica_real omc_RBY3, modelica_real omc_RCY1, modelica_real omc_REY1, modelica_real omc_REY2, modelica_real omc_RHY1, modelica_real omc_RHY2, modelica_real omc_RVY1, modelica_real omc_RVY2, modelica_real omc_RVY3, modelica_real omc_RVY4, modelica_real omc_RVY5, modelica_real omc_RVY6);

DLLDirection
modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord(threadData_t *threadData, modelica_metatype _RBY1, modelica_metatype _RBY2, modelica_metatype _RBY3, modelica_metatype _RCY1, modelica_metatype _REY1, modelica_metatype _REY2, modelica_metatype _RHY1, modelica_metatype _RHY2, modelica_metatype _RVY1, modelica_metatype _RVY2, modelica_metatype _RVY3, modelica_metatype _RVY4, modelica_metatype _RVY5, modelica_metatype _RVY6);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord,2,0) {(void*) boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord,0}};
#define boxvar_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord)


DLLDirection
BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord (threadData_t *threadData);

DLLDirection
modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord(threadData_t *threadData);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord,2,0) {(void*) boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord,0}};
#define boxvar_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord)


DLLDirection
BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord (threadData_t *threadData);

DLLDirection
modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord(threadData_t *threadData);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord,2,0) {(void*) boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord,0}};
#define boxvar_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord)


DLLDirection
BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord (threadData_t *threadData, modelica_real omc_SSZ1, modelica_real omc_SSZ2, modelica_real omc_SSZ3, modelica_real omc_SSZ4, modelica_real omc_RVY1, modelica_real omc_RVY2, modelica_real omc_RVY3, modelica_real omc_RVY4, modelica_real omc_RVY5, modelica_real omc_RVY6, modelica_real omc_LS, modelica_real omc_LVYKA);

DLLDirection
modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord(threadData_t *threadData, modelica_metatype _SSZ1, modelica_metatype _SSZ2, modelica_metatype _SSZ3, modelica_metatype _SSZ4, modelica_metatype _RVY1, modelica_metatype _RVY2, modelica_metatype _RVY3, modelica_metatype _RVY4, modelica_metatype _RVY5, modelica_metatype _RVY6, modelica_metatype _LS, modelica_metatype _LVYKA);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord,2,0) {(void*) boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord,0}};
#define boxvar_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord)


DLLDirection
BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord (threadData_t *threadData, modelica_real omc_LGAX, modelica_real omc_LFZO, modelica_real omc_PCX1, modelica_real omc_PDX1, modelica_real omc_PDX2, modelica_real omc_PDX3, modelica_real omc_PKX1, modelica_real omc_PKX2, modelica_real omc_PKX3, modelica_real omc_PHX1, modelica_real omc_PHX2, modelica_real omc_PVX1, modelica_real omc_PVX2, modelica_real omc_PEX1, modelica_real omc_PEX2, modelica_real omc_PEX3, modelica_real omc_PEX4, modelica_real omc_LCX, modelica_real omc_LMUX, modelica_real omc_LKX, modelica_real omc_LHX, modelica_real omc_LVX, modelica_real omc_LEX, modelica_real omc_LXAL);

DLLDirection
modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord(threadData_t *threadData, modelica_metatype _LGAX, modelica_metatype _LFZO, modelica_metatype _PCX1, modelica_metatype _PDX1, modelica_metatype _PDX2, modelica_metatype _PDX3, modelica_metatype _PKX1, modelica_metatype _PKX2, modelica_metatype _PKX3, modelica_metatype _PHX1, modelica_metatype _PHX2, modelica_metatype _PVX1, modelica_metatype _PVX2, modelica_metatype _PEX1, modelica_metatype _PEX2, modelica_metatype _PEX3, modelica_metatype _PEX4, modelica_metatype _LCX, modelica_metatype _LMUX, modelica_metatype _LKX, modelica_metatype _LHX, modelica_metatype _LVX, modelica_metatype _LEX, modelica_metatype _LXAL);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord,2,0) {(void*) boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord,0}};
#define boxvar_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord)


DLLDirection
BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord (threadData_t *threadData, modelica_real omc_LFZO, modelica_real omc_LGAY, modelica_real omc_PCY1, modelica_real omc_PDY1, modelica_real omc_PDY2, modelica_real omc_PDY3, modelica_real omc_PKY1, modelica_real omc_PKY2, modelica_real omc_PKY3, modelica_real omc_PHY1, modelica_real omc_PHY2, modelica_real omc_PHY3, modelica_real omc_PVY1, modelica_real omc_PVY2, modelica_real omc_PVY3, modelica_real omc_PVY4, modelica_real omc_PEY1, modelica_real omc_PEY2, modelica_real omc_PEY3, modelica_real omc_PEY4, modelica_real omc_LCY, modelica_real omc_LMUY, modelica_real omc_LEY, modelica_real omc_LKY, modelica_real omc_LHY, modelica_real omc_LVY, modelica_real omc_LYKA, modelica_real omc_LVYKA);

DLLDirection
modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord(threadData_t *threadData, modelica_metatype _LFZO, modelica_metatype _LGAY, modelica_metatype _PCY1, modelica_metatype _PDY1, modelica_metatype _PDY2, modelica_metatype _PDY3, modelica_metatype _PKY1, modelica_metatype _PKY2, modelica_metatype _PKY3, modelica_metatype _PHY1, modelica_metatype _PHY2, modelica_metatype _PHY3, modelica_metatype _PVY1, modelica_metatype _PVY2, modelica_metatype _PVY3, modelica_metatype _PVY4, modelica_metatype _PEY1, modelica_metatype _PEY2, modelica_metatype _PEY3, modelica_metatype _PEY4, modelica_metatype _LCY, modelica_metatype _LMUY, modelica_metatype _LEY, modelica_metatype _LKY, modelica_metatype _LHY, modelica_metatype _LVY, modelica_metatype _LYKA, modelica_metatype _LVYKA);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord,2,0) {(void*) boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord,0}};
#define boxvar_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord)


DLLDirection
BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord (threadData_t *threadData, modelica_real omc_QSX1, modelica_real omc_QSX2, modelica_real omc_QSX3, modelica_real omc_LMX, modelica_real omc_LVMX);

DLLDirection
modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord(threadData_t *threadData, modelica_metatype _QSX1, modelica_metatype _QSX2, modelica_metatype _QSX3, modelica_metatype _LMX, modelica_metatype _LVMX);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord,2,0) {(void*) boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord,0}};
#define boxvar_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord)


DLLDirection
BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord (threadData_t *threadData, modelica_real omc_QSY1, modelica_real omc_QSY2, modelica_real omc_QSY3, modelica_real omc_QSY4, modelica_real omc_Vref, modelica_real omc_LMY);

DLLDirection
modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord(threadData_t *threadData, modelica_metatype _QSY1, modelica_metatype _QSY2, modelica_metatype _QSY3, modelica_metatype _QSY4, modelica_metatype _Vref, modelica_metatype _LMY);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord,2,0) {(void*) boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord,0}};
#define boxvar_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord)


DLLDirection
BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord omc_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord (threadData_t *threadData, modelica_real omc_QBZ1, modelica_real omc_QBZ2, modelica_real omc_QBZ3, modelica_real omc_QBZ4, modelica_real omc_QBZ5, modelica_real omc_QCZ1, modelica_real omc_QDZ1, modelica_real omc_QDZ2, modelica_real omc_QDZ3, modelica_real omc_QDZ4, modelica_real omc_QEZ1, modelica_real omc_QEZ2, modelica_real omc_QEZ3, modelica_real omc_QEZ4, modelica_real omc_QEZ5, modelica_real omc_QHZ1, modelica_real omc_QHZ2, modelica_real omc_QHZ3, modelica_real omc_QHZ4, modelica_real omc_QBZ9, modelica_real omc_QBZ10, modelica_real omc_QDZ6, modelica_real omc_QDZ7, modelica_real omc_QDZ8, modelica_real omc_QDZ9, modelica_real omc_LTR, modelica_real omc_LRES, modelica_real omc_LKY, modelica_real omc_LMUY, modelica_real omc_LGAZ);

DLLDirection
modelica_metatype boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord(threadData_t *threadData, modelica_metatype _QBZ1, modelica_metatype _QBZ2, modelica_metatype _QBZ3, modelica_metatype _QBZ4, modelica_metatype _QBZ5, modelica_metatype _QCZ1, modelica_metatype _QDZ1, modelica_metatype _QDZ2, modelica_metatype _QDZ3, modelica_metatype _QDZ4, modelica_metatype _QEZ1, modelica_metatype _QEZ2, modelica_metatype _QEZ3, modelica_metatype _QEZ4, modelica_metatype _QEZ5, modelica_metatype _QHZ1, modelica_metatype _QHZ2, modelica_metatype _QHZ3, modelica_metatype _QHZ4, modelica_metatype _QBZ9, modelica_metatype _QBZ10, modelica_metatype _QDZ6, modelica_metatype _QDZ7, modelica_metatype _QDZ8, modelica_metatype _QDZ9, modelica_metatype _LTR, modelica_metatype _LRES, modelica_metatype _LKY, modelica_metatype _LMUY, modelica_metatype _LGAZ);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord,2,0) {(void*) boxptr_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord,0}};
#define boxvar_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord)


DLLDirection
real_array omc_BobLib_Utilities_Math_Tensor_mirrorXZ(threadData_t *threadData, real_array _T);
DLLDirection
modelica_metatype boxptr_BobLib_Utilities_Math_Tensor_mirrorXZ(threadData_t *threadData, modelica_metatype _T);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Utilities_Math_Tensor_mirrorXZ,2,0) {(void*) boxptr_BobLib_Utilities_Math_Tensor_mirrorXZ,0}};
#define boxvar_BobLib_Utilities_Math_Tensor_mirrorXZ MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Utilities_Math_Tensor_mirrorXZ)


DLLDirection
real_array omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData_t *threadData, real_array _r);
DLLDirection
modelica_metatype boxptr_BobLib_Utilities_Math_Vector_mirrorXZ(threadData_t *threadData, modelica_metatype _r);
static const MMC_DEFSTRUCTLIT(boxvar_lit_BobLib_Utilities_Math_Vector_mirrorXZ,2,0) {(void*) boxptr_BobLib_Utilities_Math_Vector_mirrorXZ,0}};
#define boxvar_BobLib_Utilities_Math_Vector_mirrorXZ MMC_REFSTRUCTLIT(boxvar_lit_BobLib_Utilities_Math_Vector_mirrorXZ)


DLLDirection
modelica_real omc_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmax(threadData_t *threadData, modelica_complex _tableID);
DLLDirection
modelica_metatype boxptr_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmax(threadData_t *threadData, modelica_metatype _tableID);
static const MMC_DEFSTRUCTLIT(boxvar_lit_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmax,2,0) {(void*) boxptr_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmax,0}};
#define boxvar_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmax MMC_REFSTRUCTLIT(boxvar_lit_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmax)

extern double ModelicaStandardTables_CombiTable1D_maximumAbscissa(void * /*_tableID*/);


DLLDirection
modelica_real omc_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmin(threadData_t *threadData, modelica_complex _tableID);
DLLDirection
modelica_metatype boxptr_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmin(threadData_t *threadData, modelica_metatype _tableID);
static const MMC_DEFSTRUCTLIT(boxvar_lit_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmin,2,0) {(void*) boxptr_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmin,0}};
#define boxvar_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmin MMC_REFSTRUCTLIT(boxvar_lit_Modelica_Blocks_Tables_Internal_getTable1DAbscissaUmin)

extern double ModelicaStandardTables_CombiTable1D_minimumAbscissa(void * /*_tableID*/);


DLLDirection
modelica_real omc_Modelica_Blocks_Tables_Internal_getTable1DValueNoDer2(threadData_t *threadData, modelica_complex _tableID, modelica_integer _icol, modelica_real _u);
DLLDirection
modelica_metatype boxptr_Modelica_Blocks_Tables_Internal_getTable1DValueNoDer2(threadData_t *threadData, modelica_metatype _tableID, modelica_metatype _icol, modelica_metatype _u);
static const MMC_DEFSTRUCTLIT(boxvar_lit_Modelica_Blocks_Tables_Internal_getTable1DValueNoDer2,2,0) {(void*) boxptr_Modelica_Blocks_Tables_Internal_getTable1DValueNoDer2,0}};
#define boxvar_Modelica_Blocks_Tables_Internal_getTable1DValueNoDer2 MMC_REFSTRUCTLIT(boxvar_lit_Modelica_Blocks_Tables_Internal_getTable1DValueNoDer2)

extern double ModelicaStandardTables_CombiTable1D_getValue(void * /*_tableID*/, int /*_icol*/, double /*_u*/);


DLLDirection
modelica_complex omc_Modelica_Blocks_Types_ExternalCombiTable1D_constructor(threadData_t *threadData, modelica_string _tableName, modelica_string _fileName, real_array _table, integer_array _columns, modelica_integer _smoothness, modelica_integer _extrapolation, modelica_boolean _verboseRead, modelica_string _delimiter, modelica_integer _nHeaderLines);
DLLDirection
modelica_metatype boxptr_Modelica_Blocks_Types_ExternalCombiTable1D_constructor(threadData_t *threadData, modelica_metatype _tableName, modelica_metatype _fileName, modelica_metatype _table, modelica_metatype _columns, modelica_metatype _smoothness, modelica_metatype _extrapolation, modelica_metatype _verboseRead, modelica_metatype _delimiter, modelica_metatype _nHeaderLines);
static const MMC_DEFSTRUCTLIT(boxvar_lit_Modelica_Blocks_Types_ExternalCombiTable1D_constructor,2,0) {(void*) boxptr_Modelica_Blocks_Types_ExternalCombiTable1D_constructor,0}};
#define boxvar_Modelica_Blocks_Types_ExternalCombiTable1D_constructor MMC_REFSTRUCTLIT(boxvar_lit_Modelica_Blocks_Types_ExternalCombiTable1D_constructor)

extern void * ModelicaStandardTables_CombiTable1D_init3(const char* /*_fileName*/, const char* /*_tableName*/, const double* /*_table*/, size_t, size_t, const int* /*_columns*/, size_t, int /*_smoothness*/, int /*_extrapolation*/, int /*_verboseRead*/, const char* /*_delimiter*/, int /*_nHeaderLines*/);


DLLDirection
void omc_Modelica_Blocks_Types_ExternalCombiTable1D_destructor(threadData_t *threadData, modelica_complex _externalCombiTable1D);
DLLDirection
void boxptr_Modelica_Blocks_Types_ExternalCombiTable1D_destructor(threadData_t *threadData, modelica_metatype _externalCombiTable1D);
static const MMC_DEFSTRUCTLIT(boxvar_lit_Modelica_Blocks_Types_ExternalCombiTable1D_destructor,2,0) {(void*) boxptr_Modelica_Blocks_Types_ExternalCombiTable1D_destructor,0}};
#define boxvar_Modelica_Blocks_Types_ExternalCombiTable1D_destructor MMC_REFSTRUCTLIT(boxvar_lit_Modelica_Blocks_Types_ExternalCombiTable1D_destructor)

extern void ModelicaStandardTables_CombiTable1D_close(void * /*_externalCombiTable1D*/);


DLLDirection
modelica_real omc_Modelica_Math_atan2(threadData_t *threadData, modelica_real _u1, modelica_real _u2);
DLLDirection
modelica_metatype boxptr_Modelica_Math_atan2(threadData_t *threadData, modelica_metatype _u1, modelica_metatype _u2);
static const MMC_DEFSTRUCTLIT(boxvar_lit_Modelica_Math_atan2,2,0) {(void*) boxptr_Modelica_Math_atan2,0}};
#define boxvar_Modelica_Math_atan2 MMC_REFSTRUCTLIT(boxvar_lit_Modelica_Math_atan2)


DLLDirection
modelica_real omc_Modelica_Math_Vectors_interpolate(threadData_t *threadData, real_array _x, real_array _y, modelica_real _xi, modelica_integer _iLast, modelica_integer *out_iNew);
DLLDirection
modelica_metatype boxptr_Modelica_Math_Vectors_interpolate(threadData_t *threadData, modelica_metatype _x, modelica_metatype _y, modelica_metatype _xi, modelica_metatype _iLast, modelica_metatype *out_iNew);
static const MMC_DEFSTRUCTLIT(boxvar_lit_Modelica_Math_Vectors_interpolate,2,0) {(void*) boxptr_Modelica_Math_Vectors_interpolate,0}};
#define boxvar_Modelica_Math_Vectors_interpolate MMC_REFSTRUCTLIT(boxvar_lit_Modelica_Math_Vectors_interpolate)


DLLDirection
modelica_real omc_Modelica_Math_Vectors_length(threadData_t *threadData, real_array _v);
DLLDirection
modelica_metatype boxptr_Modelica_Math_Vectors_length(threadData_t *threadData, modelica_metatype _v);
static const MMC_DEFSTRUCTLIT(boxvar_lit_Modelica_Math_Vectors_length,2,0) {(void*) boxptr_Modelica_Math_Vectors_length,0}};
#define boxvar_Modelica_Math_Vectors_length MMC_REFSTRUCTLIT(boxvar_lit_Modelica_Math_Vectors_length)


DLLDirection
modelica_real omc_Modelica_Math_Vectors_norm(threadData_t *threadData, real_array _v, modelica_real _p);
DLLDirection
modelica_metatype boxptr_Modelica_Math_Vectors_norm(threadData_t *threadData, modelica_metatype _v, modelica_metatype _p);
static const MMC_DEFSTRUCTLIT(boxvar_lit_Modelica_Math_Vectors_norm,2,0) {(void*) boxptr_Modelica_Math_Vectors_norm,0}};
#define boxvar_Modelica_Math_Vectors_norm MMC_REFSTRUCTLIT(boxvar_lit_Modelica_Math_Vectors_norm)


DLLDirection
real_array omc_Modelica_Math_Vectors_normalize(threadData_t *threadData, real_array _v, modelica_real _eps);
DLLDirection
modelica_metatype boxptr_Modelica_Math_Vectors_normalize(threadData_t *threadData, modelica_metatype _v, modelica_metatype _eps);
static const MMC_DEFSTRUCTLIT(boxvar_lit_Modelica_Math_Vectors_normalize,2,0) {(void*) boxptr_Modelica_Math_Vectors_normalize,0}};
#define boxvar_Modelica_Math_Vectors_normalize MMC_REFSTRUCTLIT(boxvar_lit_Modelica_Math_Vectors_normalize)


DLLDirection
Modelica_Mechanics_MultiBody_Frames_Orientation omc_Modelica_Mechanics_MultiBody_Frames_Orientation (threadData_t *threadData, real_array omc_T, real_array omc_w);

DLLDirection
modelica_metatype boxptr_Modelica_Mechanics_MultiBody_Frames_Orientation(threadData_t *threadData, modelica_metatype _T, modelica_metatype _w);
static const MMC_DEFSTRUCTLIT(boxvar_lit_Modelica_Mechanics_MultiBody_Frames_Orientation,2,0) {(void*) boxptr_Modelica_Mechanics_MultiBody_Frames_Orientation,0}};
#define boxvar_Modelica_Mechanics_MultiBody_Frames_Orientation MMC_REFSTRUCTLIT(boxvar_lit_Modelica_Mechanics_MultiBody_Frames_Orientation)


DLLDirection
real_array omc_Modelica_Mechanics_MultiBody_Frames_resolve2(threadData_t *threadData, Modelica_Mechanics_MultiBody_Frames_Orientation _R, real_array _v1);
DLLDirection
modelica_metatype boxptr_Modelica_Mechanics_MultiBody_Frames_resolve2(threadData_t *threadData, modelica_metatype _R, modelica_metatype _v1);
static const MMC_DEFSTRUCTLIT(boxvar_lit_Modelica_Mechanics_MultiBody_Frames_resolve2,2,0) {(void*) boxptr_Modelica_Mechanics_MultiBody_Frames_resolve2,0}};
#define boxvar_Modelica_Mechanics_MultiBody_Frames_resolve2 MMC_REFSTRUCTLIT(boxvar_lit_Modelica_Mechanics_MultiBody_Frames_resolve2)


DLLDirection
real_array omc_Modelica_Mechanics_MultiBody_Frames_TransformationMatrices_from__nxy(threadData_t *threadData, real_array _n_x, real_array _n_y);
DLLDirection
modelica_metatype boxptr_Modelica_Mechanics_MultiBody_Frames_TransformationMatrices_from__nxy(threadData_t *threadData, modelica_metatype _n_x, modelica_metatype _n_y);
static const MMC_DEFSTRUCTLIT(boxvar_lit_Modelica_Mechanics_MultiBody_Frames_TransformationMatrices_from__nxy,2,0) {(void*) boxptr_Modelica_Mechanics_MultiBody_Frames_TransformationMatrices_from__nxy,0}};
#define boxvar_Modelica_Mechanics_MultiBody_Frames_TransformationMatrices_from__nxy MMC_REFSTRUCTLIT(boxvar_lit_Modelica_Mechanics_MultiBody_Frames_TransformationMatrices_from__nxy)
#include "BobLib.Experiments.Standards.VehicleSim_model.h"


#ifdef __cplusplus
}
#endif
#endif
