#ifdef __cplusplus
extern "C" {
#endif

#define _OMC_LIT0_data "Force"
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT0,5,_OMC_LIT0_data);
#define _OMC_LIT0 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT0)
#define _OMC_LIT1_data "N"
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT1,1,_OMC_LIT1_data);
#define _OMC_LIT1 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT1)
#define _OMC_LIT2_data "Angle"
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT2,5,_OMC_LIT2_data);
#define _OMC_LIT2 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT2)
#define _OMC_LIT3_data "rad"
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT3,3,_OMC_LIT3_data);
#define _OMC_LIT3 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT3)
#define _OMC_LIT4_data "deg"
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT4,3,_OMC_LIT4_data);
#define _OMC_LIT4 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT4)
#define _OMC_LIT5_data "1"
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT5,1,_OMC_LIT5_data);
#define _OMC_LIT5 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT5)
#define _OMC_LIT6_data "Velocity"
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT6,8,_OMC_LIT6_data);
#define _OMC_LIT6 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT6)
#define _OMC_LIT7_data "m/s"
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT7,3,_OMC_LIT7_data);
#define _OMC_LIT7 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT7)
#define _OMC_LIT8_data "Torque"
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT8,6,_OMC_LIT8_data);
#define _OMC_LIT8 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT8)
#define _OMC_LIT9_data "N.m"
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT9,3,_OMC_LIT9_data);
#define _OMC_LIT9 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT9)
#define _OMC_LIT10_data "Length"
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT10,6,_OMC_LIT10_data);
#define _OMC_LIT10 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT10)
#define _OMC_LIT11_data "m"
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT11,1,_OMC_LIT11_data);
#define _OMC_LIT11 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT11)
static _index_t _OMC_LIT12_dims[1] = {3};
static const modelica_string _OMC_LIT12_data[] = {_OMC_LIT10, _OMC_LIT10, _OMC_LIT10};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static string_array const _OMC_LIT12 = {
  1, _OMC_LIT12_dims, (void*) _OMC_LIT12_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT12 (base_array_t){1, _OMC_LIT12_dims, (void*) _OMC_LIT12_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT13_dims[1] = {3};
static const modelica_string _OMC_LIT13_data[] = {_OMC_LIT11, _OMC_LIT11, _OMC_LIT11};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static string_array const _OMC_LIT13 = {
  1, _OMC_LIT13_dims, (void*) _OMC_LIT13_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT13 (base_array_t){1, _OMC_LIT13_dims, (void*) _OMC_LIT13_data, (modelica_boolean) 0}
#endif
#define _OMC_LIT14_data "\nSingular position of loop (either no or two analytic solutions;\nthe mechanism has lost one-degree-of freedom in this position).\nTry first to use another Modelica.Mechanics.MultiBody.Joints.Assemblies.JointXXX component.\nIn most cases it is best that the joints outside of the JointXXX\ncomponent are revolute and NOT prismatic joints. If this also\nlead to singular positions, it could be that this kinematic loop\ncannot be solved analytically. In this case you have to build\nup the loop with basic joints (NO aggregation JointXXX components)\nand rely on dynamic state selection, i.e., during simulation\nthe states will be dynamically selected in such a way that in no\nposition a degree of freedom is lost.\n"
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT14,706,_OMC_LIT14_data);
#define _OMC_LIT14 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT14)
static _index_t _OMC_LIT15_dims[2] = {3, 3};
static const modelica_real _OMC_LIT15_data[] = {1.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 1.0};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT15 = {
  2, _OMC_LIT15_dims, (void*) _OMC_LIT15_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT15 (base_array_t){2, _OMC_LIT15_dims, (void*) _OMC_LIT15_data, (modelica_boolean) 0}
#endif
#define _OMC_LIT16_data ","
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT16,1,_OMC_LIT16_data);
#define _OMC_LIT16 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT16)
#define _OMC_LIT17_data "The table vectors must have at least 1 entry."
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT17,45,_OMC_LIT17_data);
#define _OMC_LIT17 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT17)
#define _OMC_LIT18_data "Abscissa table vector values must be increasing"
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT18,47,_OMC_LIT18_data);
#define _OMC_LIT18 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT18)
#define _OMC_LIT19_data "Optional argument \"p\" (= "
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT19,25,_OMC_LIT19_data);
#define _OMC_LIT19 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT19)
#define _OMC_LIT20_data ") of function \"norm\" >= 1 required"
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT20,34,_OMC_LIT20_data);
#define _OMC_LIT20 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT20)
static _index_t _OMC_LIT21_dims[1] = {3};
static const modelica_real _OMC_LIT21_data[] = {1.0, 0.0, 0.0};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT21 = {
  1, _OMC_LIT21_dims, (void*) _OMC_LIT21_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT21 (base_array_t){1, _OMC_LIT21_dims, (void*) _OMC_LIT21_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT22_dims[1] = {3};
static const modelica_real _OMC_LIT22_data[] = {0.0, 1.0, 0.0};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT22 = {
  1, _OMC_LIT22_dims, (void*) _OMC_LIT22_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT22 (base_array_t){1, _OMC_LIT22_dims, (void*) _OMC_LIT22_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT23_dims[1] = {3};
static const modelica_real _OMC_LIT23_data[] = {-0.042144464098, 0.250754351932, 0.370010000136};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT23 = {
  1, _OMC_LIT23_dims, (void*) _OMC_LIT23_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT23 (base_array_t){1, _OMC_LIT23_dims, (void*) _OMC_LIT23_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT24_dims[1] = {3};
static const modelica_real _OMC_LIT24_data[] = {-0.020673469702, 0.247847085458, 0.561456926868};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT24 = {
  1, _OMC_LIT24_dims, (void*) _OMC_LIT24_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT24 (base_array_t){1, _OMC_LIT24_dims, (void*) _OMC_LIT24_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT25_dims[1] = {3};
static const modelica_real _OMC_LIT25_data[] = {0.0, 0.0, 0.0};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT25 = {
  1, _OMC_LIT25_dims, (void*) _OMC_LIT25_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT25 (base_array_t){1, _OMC_LIT25_dims, (void*) _OMC_LIT25_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT26_dims[1] = {3};
static const modelica_real _OMC_LIT26_data[] = {-1.39886851, 0.29230126, 0.1016};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT26 = {
  1, _OMC_LIT26_dims, (void*) _OMC_LIT26_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT26 (base_array_t){1, _OMC_LIT26_dims, (void*) _OMC_LIT26_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT27_dims[1] = {3};
static const modelica_real _OMC_LIT27_data[] = {-1.50192144, 0.28884688, 0.36889916};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT27 = {
  1, _OMC_LIT27_dims, (void*) _OMC_LIT27_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT27 (base_array_t){1, _OMC_LIT27_dims, (void*) _OMC_LIT27_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT28_dims[1] = {3};
static const modelica_real _OMC_LIT28_data[] = {0.0, 0.0, 1.0};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT28 = {
  1, _OMC_LIT28_dims, (void*) _OMC_LIT28_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT28 (base_array_t){1, _OMC_LIT28_dims, (void*) _OMC_LIT28_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT29_dims[1] = {3};
static const modelica_real _OMC_LIT29_data[] = {-1.0, 0.0, 0.0};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT29 = {
  1, _OMC_LIT29_dims, (void*) _OMC_LIT29_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT29 (base_array_t){1, _OMC_LIT29_dims, (void*) _OMC_LIT29_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT30_dims[1] = {3};
static const modelica_real _OMC_LIT30_data[] = {0.1696974, 0.0021082000000000045, -8.128000000000024e-4};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT30 = {
  1, _OMC_LIT30_dims, (void*) _OMC_LIT30_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT30 (base_array_t){1, _OMC_LIT30_dims, (void*) _OMC_LIT30_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT31_dims[1] = {3};
static const modelica_real _OMC_LIT31_data[] = {0.22024339999999998, 0.013385800000000003, 0.004800599999999988};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT31 = {
  1, _OMC_LIT31_dims, (void*) _OMC_LIT31_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT31 (base_array_t){1, _OMC_LIT31_dims, (void*) _OMC_LIT31_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT32_dims[1] = {3};
static const modelica_real _OMC_LIT32_data[] = {0.1778, 0.0, 0.0};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT32 = {
  1, _OMC_LIT32_dims, (void*) _OMC_LIT32_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT32 (base_array_t){1, _OMC_LIT32_dims, (void*) _OMC_LIT32_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT33_dims[1] = {3};
static const modelica_real _OMC_LIT33_data[] = {0.1855977999999998, -5.08000000000175e-5, -3.555999999999976e-4};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT33 = {
  1, _OMC_LIT33_dims, (void*) _OMC_LIT33_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT33 (base_array_t){1, _OMC_LIT33_dims, (void*) _OMC_LIT33_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT34_dims[1] = {3};
static const modelica_real _OMC_LIT34_data[] = {0.027651137991999995, 0.09765641835200001, 0.004604186625999984};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT34 = {
  1, _OMC_LIT34_dims, (void*) _OMC_LIT34_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT34 (base_array_t){1, _OMC_LIT34_dims, (void*) _OMC_LIT34_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT35_dims[1] = {3};
static const modelica_real _OMC_LIT35_data[] = {0.003465897055999999, -0.002875737454000049, 0.036645724016000025};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT35 = {
  1, _OMC_LIT35_dims, (void*) _OMC_LIT35_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT35 (base_array_t){1, _OMC_LIT35_dims, (void*) _OMC_LIT35_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT36_dims[1] = {3};
static const modelica_real _OMC_LIT36_data[] = {-0.017982744577999997, -0.048393882129999954, -0.039062922128};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT36 = {
  1, _OMC_LIT36_dims, (void*) _OMC_LIT36_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT36 (base_array_t){1, _OMC_LIT36_dims, (void*) _OMC_LIT36_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT37_dims[1] = {3};
static const modelica_real _OMC_LIT37_data[] = {-0.013134290469999997, -0.046386798768000004, -0.00218698851400001};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT37 = {
  1, _OMC_LIT37_dims, (void*) _OMC_LIT37_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT37 (base_array_t){1, _OMC_LIT37_dims, (void*) _OMC_LIT37_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT38_dims[1] = {3};
static const modelica_real _OMC_LIT38_data[] = {-0.013807150000000101, 0.059671909999999995, -0.01675936};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT38 = {
  1, _OMC_LIT38_dims, (void*) _OMC_LIT38_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT38 (base_array_t){1, _OMC_LIT38_dims, (void*) _OMC_LIT38_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT39_dims[1] = {3};
static const modelica_real _OMC_LIT39_data[] = {-0.025337289999999957, 0.009399680000000021, 0.056759840000000006};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT39 = {
  1, _OMC_LIT39_dims, (void*) _OMC_LIT39_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT39 (base_array_t){1, _OMC_LIT39_dims, (void*) _OMC_LIT39_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT40_dims[1] = {3};
static const modelica_real _OMC_LIT40_data[] = {0.02454310999999998, -0.05079721000000004, -0.018531649999999997};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT40 = {
  1, _OMC_LIT40_dims, (void*) _OMC_LIT40_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT40 (base_array_t){1, _OMC_LIT40_dims, (void*) _OMC_LIT40_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT41_dims[1] = {3};
static const modelica_real _OMC_LIT41_data[] = {0.014601330000000079, -0.01827437999999998, -0.021468830000000008};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT41 = {
  1, _OMC_LIT41_dims, (void*) _OMC_LIT41_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT41 (base_array_t){1, _OMC_LIT41_dims, (void*) _OMC_LIT41_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT42_dims[2] = {3, 3};
static const modelica_real _OMC_LIT42_data[] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT42 = {
  2, _OMC_LIT42_dims, (void*) _OMC_LIT42_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT42 (base_array_t){2, _OMC_LIT42_dims, (void*) _OMC_LIT42_data, (modelica_boolean) 0}
#endif
#define _OMC_LIT43_data "NoName"
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT43,6,_OMC_LIT43_data);
#define _OMC_LIT43 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT43)
#define _OMC_LIT44_data "cylinder"
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT44,8,_OMC_LIT44_data);
#define _OMC_LIT44 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT44)
#define _OMC_LIT45_data "cone"
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT45,4,_OMC_LIT45_data);
#define _OMC_LIT45 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT45)
static _index_t _OMC_LIT46_dims[1] = {4};
static const modelica_real _OMC_LIT46_data[] = {0.0, 0.0, 0.0, 1.0};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT46 = {
  1, _OMC_LIT46_dims, (void*) _OMC_LIT46_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT46 (base_array_t){1, _OMC_LIT46_dims, (void*) _OMC_LIT46_data, (modelica_boolean) 0}
#endif
#define _OMC_LIT47_data "sphere"
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT47,6,_OMC_LIT47_data);
#define _OMC_LIT47 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT47)
static _index_t _OMC_LIT48_dims[1] = {3};
static const modelica_real _OMC_LIT48_data[] = {0.887962410598, 0.302708516859, 0.346251803151};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT48 = {
  1, _OMC_LIT48_dims, (void*) _OMC_LIT48_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT48 (base_array_t){1, _OMC_LIT48_dims, (void*) _OMC_LIT48_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT49_dims[1] = {3};
static const modelica_real _OMC_LIT49_data[] = {-1.53509479, -0.50330883, 0.26648017};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT49 = {
  1, _OMC_LIT49_dims, (void*) _OMC_LIT49_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT49 (base_array_t){1, _OMC_LIT49_dims, (void*) _OMC_LIT49_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT50_dims[1] = {3};
static const modelica_real _OMC_LIT50_data[] = {-1.41267566, -0.35197317, 0.08484064};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT50 = {
  1, _OMC_LIT50_dims, (void*) _OMC_LIT50_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT50 (base_array_t){1, _OMC_LIT50_dims, (void*) _OMC_LIT50_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT51_dims[1] = {3};
static const modelica_real _OMC_LIT51_data[] = {-0.4598135704301268, 0.5684257857248273, 0.6822489329939707};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT51 = {
  1, _OMC_LIT51_dims, (void*) _OMC_LIT51_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT51 (base_array_t){1, _OMC_LIT51_dims, (void*) _OMC_LIT51_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT52_dims[1] = {3};
static const modelica_real _OMC_LIT52_data[] = {0.8879624105983084, 0.30270851685910516, 0.34625180315112025};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT52 = {
  1, _OMC_LIT52_dims, (void*) _OMC_LIT52_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT52 (base_array_t){1, _OMC_LIT52_dims, (void*) _OMC_LIT52_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT53_dims[1] = {3};
static const modelica_real _OMC_LIT53_data[] = {0.0189788099999999, 0.023461769999999937, -0.028159829999999997};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT53 = {
  1, _OMC_LIT53_dims, (void*) _OMC_LIT53_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT53 (base_array_t){1, _OMC_LIT53_dims, (void*) _OMC_LIT53_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT54_dims[1] = {3};
static const modelica_real _OMC_LIT54_data[] = {-1.3925183, 0.3032125, 0.41224196};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT54 = {
  1, _OMC_LIT54_dims, (void*) _OMC_LIT54_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT54 (base_array_t){1, _OMC_LIT54_dims, (void*) _OMC_LIT54_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT55_dims[1] = {3};
static const modelica_real _OMC_LIT55_data[] = {-0.037494529999999804, -0.0, -0.006765359999999998};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT55 = {
  1, _OMC_LIT55_dims, (void*) _OMC_LIT55_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT55 (base_array_t){1, _OMC_LIT55_dims, (void*) _OMC_LIT55_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT56_dims[1] = {3};
static const modelica_real _OMC_LIT56_data[] = {0.03914444000000006, -0.06907159000000002, -0.040000480000000005};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT56 = {
  1, _OMC_LIT56_dims, (void*) _OMC_LIT56_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT56 (base_array_t){1, _OMC_LIT56_dims, (void*) _OMC_LIT56_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT57_dims[1] = {3};
static const modelica_real _OMC_LIT57_data[] = {0.887962410598, -0.302708516859, 0.346251803151};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT57 = {
  1, _OMC_LIT57_dims, (void*) _OMC_LIT57_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT57 (base_array_t){1, _OMC_LIT57_dims, (void*) _OMC_LIT57_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT58_dims[1] = {3};
static const modelica_real _OMC_LIT58_data[] = {-1.50192144, -0.28884688, 0.36889916};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT58 = {
  1, _OMC_LIT58_dims, (void*) _OMC_LIT58_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT58 (base_array_t){1, _OMC_LIT58_dims, (void*) _OMC_LIT58_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT59_dims[1] = {3};
static const modelica_real _OMC_LIT59_data[] = {-1.43801295, -0.36137285, 0.14160048};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT59 = {
  1, _OMC_LIT59_dims, (void*) _OMC_LIT59_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT59 (base_array_t){1, _OMC_LIT59_dims, (void*) _OMC_LIT59_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT60_dims[1] = {3};
static const modelica_real _OMC_LIT60_data[] = {0.8879624105983084, -0.30270851685910516, 0.34625180315112025};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT60 = {
  1, _OMC_LIT60_dims, (void*) _OMC_LIT60_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT60 (base_array_t){1, _OMC_LIT60_dims, (void*) _OMC_LIT60_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT61_dims[1] = {3};
static const modelica_real _OMC_LIT61_data[] = {-1.41346984, -0.31057564, 0.12306883};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT61 = {
  1, _OMC_LIT61_dims, (void*) _OMC_LIT61_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT61 (base_array_t){1, _OMC_LIT61_dims, (void*) _OMC_LIT61_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT62_dims[1] = {3};
static const modelica_real _OMC_LIT62_data[] = {-1.39886851, -0.29230126, 0.1016};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT62 = {
  1, _OMC_LIT62_dims, (void*) _OMC_LIT62_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT62 (base_array_t){1, _OMC_LIT62_dims, (void*) _OMC_LIT62_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT63_dims[1] = {3};
static const modelica_real _OMC_LIT63_data[] = {0.4403199064379694, -0.7769582614113715, -0.44994915270403263};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT63 = {
  1, _OMC_LIT63_dims, (void*) _OMC_LIT63_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT63 (base_array_t){1, _OMC_LIT63_dims, (void*) _OMC_LIT63_data, (modelica_boolean) 0}
#endif
#define _OMC_LIT64_data "box"
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT64,3,_OMC_LIT64_data);
#define _OMC_LIT64 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT64)
static _index_t _OMC_LIT65_dims[1] = {3};
static const modelica_real _OMC_LIT65_data[] = {-1.3763498, -0.2897124, 0.1700022};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT65 = {
  1, _OMC_LIT65_dims, (void*) _OMC_LIT65_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT65 (base_array_t){1, _OMC_LIT65_dims, (void*) _OMC_LIT65_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT66_dims[1] = {3};
static const modelica_real _OMC_LIT66_data[] = {-0.2657719940194223, 0.9531561428838498, 0.14442511719822979};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT66 = {
  1, _OMC_LIT66_dims, (void*) _OMC_LIT66_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT66 (base_array_t){1, _OMC_LIT66_dims, (void*) _OMC_LIT66_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT67_dims[1] = {3};
static const modelica_real _OMC_LIT67_data[] = {0.002192260608837567, -0.2686889408705617, 0.9632245050076741};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT67 = {
  1, _OMC_LIT67_dims, (void*) _OMC_LIT67_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT67 (base_array_t){1, _OMC_LIT67_dims, (void*) _OMC_LIT67_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT68_dims[1] = {3};
static const modelica_real _OMC_LIT68_data[] = {0.9999981270742302, -2.737096283220407e-4, -0.001915967398253612};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT68 = {
  1, _OMC_LIT68_dims, (void*) _OMC_LIT68_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT68 (base_array_t){1, _OMC_LIT68_dims, (void*) _OMC_LIT68_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT69_dims[1] = {3};
static const modelica_real _OMC_LIT69_data[] = {0.9999981270742301, -2.7370962832204063e-4, -0.0019159673982536117};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT69 = {
  1, _OMC_LIT69_dims, (void*) _OMC_LIT69_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT69 (base_array_t){1, _OMC_LIT69_dims, (void*) _OMC_LIT69_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT70_dims[1] = {3};
static const modelica_real _OMC_LIT70_data[] = {0.9979220046573015, 0.06065100870192574, 0.021751500274504617};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT70 = {
  1, _OMC_LIT70_dims, (void*) _OMC_LIT70_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT70 (base_array_t){1, _OMC_LIT70_dims, (void*) _OMC_LIT70_data, (modelica_boolean) 0}
#endif
#define _OMC_LIT71_data "pipe"
static const MMC_DEFSTRINGLIT(_OMC_LIT_STRUCT71,4,_OMC_LIT71_data);
#define _OMC_LIT71 MMC_REFSTRINGLIT(_OMC_LIT_STRUCT71)
static _index_t _OMC_LIT72_dims[1] = {3};
static const modelica_real _OMC_LIT72_data[] = {-1.40704567, -0.39979876, 0.18668273};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT72 = {
  1, _OMC_LIT72_dims, (void*) _OMC_LIT72_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT72 (base_array_t){1, _OMC_LIT72_dims, (void*) _OMC_LIT72_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT73_dims[1] = {3};
static const modelica_real _OMC_LIT73_data[] = {-1.47625848, -0.4301135, 0.10156115};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT73 = {
  1, _OMC_LIT73_dims, (void*) _OMC_LIT73_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT73 (base_array_t){1, _OMC_LIT73_dims, (void*) _OMC_LIT73_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT74_dims[1] = {3};
static const modelica_real _OMC_LIT74_data[] = {-1.47556121, -0.42263392, 0.27196898};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT74 = {
  1, _OMC_LIT74_dims, (void*) _OMC_LIT74_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT74 (base_array_t){1, _OMC_LIT74_dims, (void*) _OMC_LIT74_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT75_dims[1] = {3};
static const modelica_real _OMC_LIT75_data[] = {-1.54081056, -0.59989818, 0.20113454};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT75 = {
  1, _OMC_LIT75_dims, (void*) _OMC_LIT75_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT75 (base_array_t){1, _OMC_LIT75_dims, (void*) _OMC_LIT75_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT76_dims[1] = {3};
static const modelica_real _OMC_LIT76_data[] = {-1.5494, -0.60611077, 0.199898};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT76 = {
  1, _OMC_LIT76_dims, (void*) _OMC_LIT76_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT76 (base_array_t){1, _OMC_LIT76_dims, (void*) _OMC_LIT76_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT77_dims[1] = {3};
static const modelica_real _OMC_LIT77_data[] = {-1.45796, -0.5823966, 0.2143506};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT77 = {
  1, _OMC_LIT77_dims, (void*) _OMC_LIT77_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT77 (base_array_t){1, _OMC_LIT77_dims, (void*) _OMC_LIT77_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT78_dims[1] = {3};
static const modelica_real _OMC_LIT78_data[] = {-1.55448, -0.57658, 0.116078};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT78 = {
  1, _OMC_LIT78_dims, (void*) _OMC_LIT78_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT78 (base_array_t){1, _OMC_LIT78_dims, (void*) _OMC_LIT78_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT79_dims[1] = {3};
static const modelica_real _OMC_LIT79_data[] = {-1.5540736, -0.5267706, 0.29464};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT79 = {
  1, _OMC_LIT79_dims, (void*) _OMC_LIT79_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT79 (base_array_t){1, _OMC_LIT79_dims, (void*) _OMC_LIT79_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT80_dims[1] = {3};
static const modelica_real _OMC_LIT80_data[] = {-1.4998192, -0.2835148, 0.0872236};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT80 = {
  1, _OMC_LIT80_dims, (void*) _OMC_LIT80_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT80 (base_array_t){1, _OMC_LIT80_dims, (void*) _OMC_LIT80_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT81_dims[1] = {3};
static const modelica_real _OMC_LIT81_data[] = {-1.3142214, -0.283464, 0.086868};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT81 = {
  1, _OMC_LIT81_dims, (void*) _OMC_LIT81_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT81 (base_array_t){1, _OMC_LIT81_dims, (void*) _OMC_LIT81_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT82_dims[1] = {3};
static const modelica_real _OMC_LIT82_data[] = {-1.4993874, -0.283845, 0.2434336};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT82 = {
  1, _OMC_LIT82_dims, (void*) _OMC_LIT82_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT82 (base_array_t){1, _OMC_LIT82_dims, (void*) _OMC_LIT82_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT83_dims[1] = {3};
static const modelica_real _OMC_LIT83_data[] = {-1.279144, -0.2972308, 0.2482342};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT83 = {
  1, _OMC_LIT83_dims, (void*) _OMC_LIT83_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT83 (base_array_t){1, _OMC_LIT83_dims, (void*) _OMC_LIT83_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT84_dims[1] = {3};
static const modelica_real _OMC_LIT84_data[] = {0.95754655, -0.26587315, -0.11142744};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT84 = {
  1, _OMC_LIT84_dims, (void*) _OMC_LIT84_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT84 (base_array_t){1, _OMC_LIT84_dims, (void*) _OMC_LIT84_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT85_dims[1] = {3};
static const modelica_real _OMC_LIT85_data[] = {0.006762552642, -0.525610676234, 0.134465050856};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT85 = {
  1, _OMC_LIT85_dims, (void*) _OMC_LIT85_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT85 (base_array_t){1, _OMC_LIT85_dims, (void*) _OMC_LIT85_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT86_dims[1] = {3};
static const modelica_real _OMC_LIT86_data[] = {-0.014493326106, -0.348410770284, 0.374614186762};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT86 = {
  1, _OMC_LIT86_dims, (void*) _OMC_LIT86_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT86 (base_array_t){1, _OMC_LIT86_dims, (void*) _OMC_LIT86_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT87_dims[1] = {3};
static const modelica_real _OMC_LIT87_data[] = {0.0710413492006013, 0.5922371192530506, -0.8026258912361389};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT87 = {
  1, _OMC_LIT87_dims, (void*) _OMC_LIT87_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT87 (base_array_t){1, _OMC_LIT87_dims, (void*) _OMC_LIT87_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT88_dims[1] = {3};
static const modelica_real _OMC_LIT88_data[] = {0.957546549189543, -0.26587314977496784, -0.11142743990568903};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT88 = {
  1, _OMC_LIT88_dims, (void*) _OMC_LIT88_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT88 (base_array_t){1, _OMC_LIT88_dims, (void*) _OMC_LIT88_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT89_dims[1] = {3};
static const modelica_real _OMC_LIT89_data[] = {0.0037653526419999996, 0.03738032376599998, 0.02046985085599999};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT89 = {
  1, _OMC_LIT89_dims, (void*) _OMC_LIT89_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT89 (base_array_t){1, _OMC_LIT89_dims, (void*) _OMC_LIT89_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT90_dims[1] = {3};
static const modelica_real _OMC_LIT90_data[] = {-0.10664664, 0.2667, 0.11811};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT90 = {
  1, _OMC_LIT90_dims, (void*) _OMC_LIT90_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT90 (base_array_t){1, _OMC_LIT90_dims, (void*) _OMC_LIT90_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT91_dims[1] = {3};
static const modelica_real _OMC_LIT91_data[] = {0.0698175, -0.0, -0.002130610000000005};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT91 = {
  1, _OMC_LIT91_dims, (void*) _OMC_LIT91_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT91 (base_array_t){1, _OMC_LIT91_dims, (void*) _OMC_LIT91_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT92_dims[1] = {3};
static const modelica_real _OMC_LIT92_data[] = {-0.031117035047999994, -0.09478068089799996, -0.04124991064200001};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT92 = {
  1, _OMC_LIT92_dims, (void*) _OMC_LIT92_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT92 (base_array_t){1, _OMC_LIT92_dims, (void*) _OMC_LIT92_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT93_dims[1] = {3};
static const modelica_real _OMC_LIT93_data[] = {0.95754655, 0.26587315, -0.11142744};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT93 = {
  1, _OMC_LIT93_dims, (void*) _OMC_LIT93_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT93 (base_array_t){1, _OMC_LIT93_dims, (void*) _OMC_LIT93_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT94_dims[1] = {3};
static const modelica_real _OMC_LIT94_data[] = {-0.020673469702, -0.247847085458, 0.561456926868};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT94 = {
  1, _OMC_LIT94_dims, (void*) _OMC_LIT94_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT94 (base_array_t){1, _OMC_LIT94_dims, (void*) _OMC_LIT94_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT95_dims[1] = {3};
static const modelica_real _OMC_LIT95_data[] = {-0.01102742905, -0.34553503283, 0.411259910778};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT95 = {
  1, _OMC_LIT95_dims, (void*) _OMC_LIT95_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT95 (base_array_t){1, _OMC_LIT95_dims, (void*) _OMC_LIT95_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT96_dims[1] = {3};
static const modelica_real _OMC_LIT96_data[] = {0.957546549189543, 0.26587314977496784, -0.11142743990568903};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT96 = {
  1, _OMC_LIT96_dims, (void*) _OMC_LIT96_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT96 (base_array_t){1, _OMC_LIT96_dims, (void*) _OMC_LIT96_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT97_dims[1] = {3};
static const modelica_real _OMC_LIT97_data[] = {-0.029010173628, -0.2971411507, 0.37219698865};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT97 = {
  1, _OMC_LIT97_dims, (void*) _OMC_LIT97_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT97 (base_array_t){1, _OMC_LIT97_dims, (void*) _OMC_LIT97_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT98_dims[1] = {3};
static const modelica_real _OMC_LIT98_data[] = {-0.042144464098, -0.250754351932, 0.370010000136};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT98 = {
  1, _OMC_LIT98_dims, (void*) _OMC_LIT98_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT98 (base_array_t){1, _OMC_LIT98_dims, (void*) _OMC_LIT98_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT99_dims[1] = {3};
static const modelica_real _OMC_LIT99_data[] = {-0.2882541462578468, -0.8780053823202029, -0.3821205252036513};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT99 = {
  1, _OMC_LIT99_dims, (void*) _OMC_LIT99_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT99 (base_array_t){1, _OMC_LIT99_dims, (void*) _OMC_LIT99_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT100_dims[1] = {3};
static const modelica_real _OMC_LIT100_data[] = {0.05715, -0.2260092, 0.1137158};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT100 = {
  1, _OMC_LIT100_dims, (void*) _OMC_LIT100_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT100 (base_array_t){1, _OMC_LIT100_dims, (void*) _OMC_LIT100_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT101_dims[1] = {3};
static const modelica_real _OMC_LIT101_data[] = {-4.714160720812992e-4, 0.9928808171485825, 0.11911112754587729};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT101 = {
  1, _OMC_LIT101_dims, (void*) _OMC_LIT101_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT101 (base_array_t){1, _OMC_LIT101_dims, (void*) _OMC_LIT101_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT102_dims[1] = {3};
static const modelica_real _OMC_LIT102_data[] = {-0.07885152190457047, -0.13456891961399844, 0.9877619365855592};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT102 = {
  1, _OMC_LIT102_dims, (void*) _OMC_LIT102_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT102 (base_array_t){1, _OMC_LIT102_dims, (void*) _OMC_LIT102_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT103_dims[1] = {3};
static const modelica_real _OMC_LIT103_data[] = {-0.07885152190457045, -0.13456891961399842, 0.9877619365855591};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT103 = {
  1, _OMC_LIT103_dims, (void*) _OMC_LIT103_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT103 (base_array_t){1, _OMC_LIT103_dims, (void*) _OMC_LIT103_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT104_dims[1] = {3};
static const modelica_real _OMC_LIT104_data[] = {0.9999113720941534, 0.012422188876487788, -0.004789277639127825};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT104 = {
  1, _OMC_LIT104_dims, (void*) _OMC_LIT104_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT104 (base_array_t){1, _OMC_LIT104_dims, (void*) _OMC_LIT104_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT105_dims[1] = {3};
static const modelica_real _OMC_LIT105_data[] = {0.05709287, -0.34616483, 0.1281302};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT105 = {
  1, _OMC_LIT105_dims, (void*) _OMC_LIT105_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT105 (base_array_t){1, _OMC_LIT105_dims, (void*) _OMC_LIT105_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT106_dims[1] = {3};
static const modelica_real _OMC_LIT106_data[] = {0.00803455, -0.40581792, 0.09882118};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT106 = {
  1, _OMC_LIT106_dims, (void*) _OMC_LIT106_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT106 (base_array_t){1, _OMC_LIT106_dims, (void*) _OMC_LIT106_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT107_dims[1] = {3};
static const modelica_real _OMC_LIT107_data[] = {-0.00187916, -0.45854113, 0.25343195};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT107 = {
  1, _OMC_LIT107_dims, (void*) _OMC_LIT107_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT107 (base_array_t){1, _OMC_LIT107_dims, (void*) _OMC_LIT107_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT108_dims[1] = {3};
static const modelica_real _OMC_LIT108_data[] = {-0.00611067, -0.60164333, 0.1980248};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT108 = {
  1, _OMC_LIT108_dims, (void*) _OMC_LIT108_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT108 (base_array_t){1, _OMC_LIT108_dims, (void*) _OMC_LIT108_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT109_dims[1] = {3};
static const modelica_real _OMC_LIT109_data[] = {0.0, -0.606110767456, 0.199898};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT109 = {
  1, _OMC_LIT109_dims, (void*) _OMC_LIT109_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT109 (base_array_t){1, _OMC_LIT109_dims, (void*) _OMC_LIT109_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT110_dims[1] = {3};
static const modelica_real _OMC_LIT110_data[] = {0.0569976, -0.546989, 0.1522222};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT110 = {
  1, _OMC_LIT110_dims, (void*) _OMC_LIT110_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT110 (base_array_t){1, _OMC_LIT110_dims, (void*) _OMC_LIT110_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT111_dims[1] = {3};
static const modelica_real _OMC_LIT111_data[] = {0.0029972, -0.562991, 0.1139952};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT111 = {
  1, _OMC_LIT111_dims, (void*) _OMC_LIT111_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT111 (base_array_t){1, _OMC_LIT111_dims, (void*) _OMC_LIT111_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT112_dims[1] = {3};
static const modelica_real _OMC_LIT112_data[] = {-0.0092964, -0.5420106, 0.2679954};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT112 = {
  1, _OMC_LIT112_dims, (void*) _OMC_LIT112_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT112 (base_array_t){1, _OMC_LIT112_dims, (void*) _OMC_LIT112_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT113_dims[1] = {3};
static const modelica_real _OMC_LIT113_data[] = {-0.0762, -0.226314, 0.08001};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT113 = {
  1, _OMC_LIT113_dims, (void*) _OMC_LIT113_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT113 (base_array_t){1, _OMC_LIT113_dims, (void*) _OMC_LIT113_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT114_dims[1] = {3};
static const modelica_real _OMC_LIT114_data[] = {0.1016, -0.226314, 0.08001};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT114 = {
  1, _OMC_LIT114_dims, (void*) _OMC_LIT114_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT114 (base_array_t){1, _OMC_LIT114_dims, (void*) _OMC_LIT114_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT115_dims[1] = {3};
static const modelica_real _OMC_LIT115_data[] = {-0.0680974, -0.2356358, 0.215138};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT115 = {
  1, _OMC_LIT115_dims, (void*) _OMC_LIT115_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT115 (base_array_t){1, _OMC_LIT115_dims, (void*) _OMC_LIT115_data, (modelica_boolean) 0}
#endif
static _index_t _OMC_LIT116_dims[1] = {3};
static const modelica_real _OMC_LIT116_data[] = {0.1016, -0.237744, 0.2143252};
#if (defined(__clang__)  && __clang_major__ >= 17) || (defined(__GNUC__) && __GNUC__ >= 8)
static real_array const _OMC_LIT116 = {
  1, _OMC_LIT116_dims, (void*) _OMC_LIT116_data, (modelica_boolean) 0
};
#else
/* handle joke compilers */
#define _OMC_LIT116 (base_array_t){1, _OMC_LIT116_dims, (void*) _OMC_LIT116_data, (modelica_boolean) 0}
#endif

#ifdef __cplusplus
}
#endif
