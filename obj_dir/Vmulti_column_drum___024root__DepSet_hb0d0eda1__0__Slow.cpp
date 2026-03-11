// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmulti_column_drum.h for the primary calling header

#include "Vmulti_column_drum__pch.h"
#include "Vmulti_column_drum___024root.h"

VL_ATTR_COLD void Vmulti_column_drum___024root___eval_static(Vmulti_column_drum___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmulti_column_drum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmulti_column_drum___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vmulti_column_drum___024root___eval_initial(Vmulti_column_drum___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmulti_column_drum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmulti_column_drum___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
}

VL_ATTR_COLD void Vmulti_column_drum___024root___eval_final(Vmulti_column_drum___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmulti_column_drum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmulti_column_drum___024root___eval_final\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmulti_column_drum___024root___dump_triggers__stl(Vmulti_column_drum___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vmulti_column_drum___024root___eval_phase__stl(Vmulti_column_drum___024root* vlSelf);

VL_ATTR_COLD void Vmulti_column_drum___024root___eval_settle(Vmulti_column_drum___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmulti_column_drum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmulti_column_drum___024root___eval_settle\n"); );
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelf->__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            Vmulti_column_drum___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("full_drum.sv", 1, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vmulti_column_drum___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelf->__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmulti_column_drum___024root___dump_triggers__stl(Vmulti_column_drum___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmulti_column_drum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmulti_column_drum___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vmulti_column_drum___024root___stl_sequent__TOP__0(Vmulti_column_drum___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmulti_column_drum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmulti_column_drum___024root___stl_sequent__TOP__0\n"); );
    // Init
    QData/*35:0*/ multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out;
    multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out = 0;
    IData/*17:0*/ multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__compute__DOT__product;
    multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__compute__DOT__product = 0;
    QData/*35:0*/ multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out;
    multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out = 0;
    IData/*17:0*/ multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__compute__DOT__product;
    multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__compute__DOT__product = 0;
    QData/*35:0*/ multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out;
    multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out = 0;
    IData/*17:0*/ multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__compute__DOT__product;
    multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__compute__DOT__product = 0;
    QData/*35:0*/ multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out;
    multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out = 0;
    IData/*17:0*/ multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__compute__DOT__product;
    multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__compute__DOT__product = 0;
    QData/*35:0*/ multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out;
    multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out = 0;
    IData/*17:0*/ multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__compute__DOT__product;
    multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__compute__DOT__product = 0;
    QData/*35:0*/ multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out;
    multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out = 0;
    IData/*17:0*/ multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__compute__DOT__product;
    multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__compute__DOT__product = 0;
    QData/*35:0*/ multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out;
    multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out = 0;
    IData/*17:0*/ multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__compute__DOT__product;
    multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__compute__DOT__product = 0;
    QData/*35:0*/ multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out;
    multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out = 0;
    IData/*17:0*/ multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__compute__DOT__product;
    multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__compute__DOT__product = 0;
    QData/*35:0*/ multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out;
    multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out = 0;
    IData/*17:0*/ multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__compute__DOT__product;
    multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__compute__DOT__product = 0;
    QData/*35:0*/ multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out;
    multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out = 0;
    IData/*17:0*/ multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__compute__DOT__product;
    multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__compute__DOT__product = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__0__Vfuncout;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__0__Vfuncout = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__0__a;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__0__a = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__0__b;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__0__b = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__1__Vfuncout;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__1__Vfuncout = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__1__a;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__1__a = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__1__b;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__1__b = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__2__Vfuncout;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__2__Vfuncout = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__2__a;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__2__a = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__2__b;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__2__b = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__3__Vfuncout;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__3__Vfuncout = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__3__a;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__3__a = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__3__b;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__3__b = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__4__Vfuncout;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__4__Vfuncout = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__4__a;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__4__a = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__4__b;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__4__b = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__5__Vfuncout;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__5__Vfuncout = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__5__a;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__5__a = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__5__b;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__5__b = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__6__Vfuncout;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__6__Vfuncout = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__6__a;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__6__a = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__6__b;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__6__b = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__7__Vfuncout;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__7__Vfuncout = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__7__a;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__7__a = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__7__b;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__7__b = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__8__Vfuncout;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__8__Vfuncout = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__8__a;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__8__a = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__8__b;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__8__b = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__9__Vfuncout;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__9__Vfuncout = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__9__a;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__9__a = 0;
    IData/*17:0*/ __Vfunc_multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__9__b;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__9__b = 0;
    // Body
    vlSelf->center_center_node = vlSelf->multi_column_drum__DOT____Vcellout__column_gen__BRA__4__KET____DOT__column_inst__u_middle_node;
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__triangle_value 
        = (0x3ffffU & (IData)((0xfffffffffULL & ((0xeU 
                                                  >= (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__init_addr))
                                                  ? 
                                                 VL_DIVS_QQQ(36, 
                                                             (0xfffffffffULL 
                                                              & VL_MULS_QQQ(36, 0x1000ULL, 
                                                                            (0xfffffffffULL 
                                                                             & VL_EXTENDS_QI(36,6, (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__init_addr))))), 0xeULL)
                                                  : 
                                                 VL_DIVS_QQQ(36, 
                                                             (0xfffffffffULL 
                                                              & VL_MULS_QQQ(36, 0x1000ULL, 
                                                                            (0xfffffffffULL 
                                                                             & VL_EXTENDS_QI(36,32, 
                                                                                ((IData)(0x1cU) 
                                                                                - (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__init_addr)))))), 0xeULL)))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__triangle_value 
        = (0x3ffffU & (IData)((0xfffffffffULL & ((0xeU 
                                                  >= (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__init_addr))
                                                  ? 
                                                 VL_DIVS_QQQ(36, 
                                                             (0xfffffffffULL 
                                                              & VL_MULS_QQQ(36, 0x2000ULL, 
                                                                            (0xfffffffffULL 
                                                                             & VL_EXTENDS_QI(36,6, (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__init_addr))))), 0xeULL)
                                                  : 
                                                 VL_DIVS_QQQ(36, 
                                                             (0xfffffffffULL 
                                                              & VL_MULS_QQQ(36, 0x2000ULL, 
                                                                            (0xfffffffffULL 
                                                                             & VL_EXTENDS_QI(36,32, 
                                                                                ((IData)(0x1cU) 
                                                                                - (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__init_addr)))))), 0xeULL)))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__triangle_value 
        = (0x3ffffU & (IData)((0xfffffffffULL & ((0xeU 
                                                  >= (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__init_addr))
                                                  ? 
                                                 VL_DIVS_QQQ(36, 
                                                             (0xfffffffffULL 
                                                              & VL_MULS_QQQ(36, 0x3000ULL, 
                                                                            (0xfffffffffULL 
                                                                             & VL_EXTENDS_QI(36,6, (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__init_addr))))), 0xeULL)
                                                  : 
                                                 VL_DIVS_QQQ(36, 
                                                             (0xfffffffffULL 
                                                              & VL_MULS_QQQ(36, 0x3000ULL, 
                                                                            (0xfffffffffULL 
                                                                             & VL_EXTENDS_QI(36,32, 
                                                                                ((IData)(0x1cU) 
                                                                                - (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__init_addr)))))), 0xeULL)))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__triangle_value 
        = (0x3ffffU & (IData)((0xfffffffffULL & ((0xeU 
                                                  >= (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__init_addr))
                                                  ? 
                                                 VL_DIVS_QQQ(36, 
                                                             (0xfffffffffULL 
                                                              & VL_MULS_QQQ(36, 0x4000ULL, 
                                                                            (0xfffffffffULL 
                                                                             & VL_EXTENDS_QI(36,6, (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__init_addr))))), 0xeULL)
                                                  : 
                                                 VL_DIVS_QQQ(36, 
                                                             (0xfffffffffULL 
                                                              & VL_MULS_QQQ(36, 0x4000ULL, 
                                                                            (0xfffffffffULL 
                                                                             & VL_EXTENDS_QI(36,32, 
                                                                                ((IData)(0x1cU) 
                                                                                - (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__init_addr)))))), 0xeULL)))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__triangle_value 
        = (0x3ffffU & (IData)((0xfffffffffULL & ((0xeU 
                                                  >= (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__init_addr))
                                                  ? 
                                                 VL_DIVS_QQQ(36, 
                                                             (0xfffffffffULL 
                                                              & VL_MULS_QQQ(36, 0x3000ULL, 
                                                                            (0xfffffffffULL 
                                                                             & VL_EXTENDS_QI(36,6, (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__init_addr))))), 0xeULL)
                                                  : 
                                                 VL_DIVS_QQQ(36, 
                                                             (0xfffffffffULL 
                                                              & VL_MULS_QQQ(36, 0x3000ULL, 
                                                                            (0xfffffffffULL 
                                                                             & VL_EXTENDS_QI(36,32, 
                                                                                ((IData)(0x1cU) 
                                                                                - (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__init_addr)))))), 0xeULL)))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__triangle_value 
        = (0x3ffffU & (IData)((0xfffffffffULL & ((0xeU 
                                                  >= (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__init_addr))
                                                  ? 
                                                 VL_DIVS_QQQ(36, 
                                                             (0xfffffffffULL 
                                                              & VL_MULS_QQQ(36, 0x2000ULL, 
                                                                            (0xfffffffffULL 
                                                                             & VL_EXTENDS_QI(36,6, (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__init_addr))))), 0xeULL)
                                                  : 
                                                 VL_DIVS_QQQ(36, 
                                                             (0xfffffffffULL 
                                                              & VL_MULS_QQQ(36, 0x2000ULL, 
                                                                            (0xfffffffffULL 
                                                                             & VL_EXTENDS_QI(36,32, 
                                                                                ((IData)(0x1cU) 
                                                                                - (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__init_addr)))))), 0xeULL)))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__triangle_value 
        = (0x3ffffU & (IData)((0xfffffffffULL & ((0xeU 
                                                  >= (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__init_addr))
                                                  ? 
                                                 VL_DIVS_QQQ(36, 
                                                             (0xfffffffffULL 
                                                              & VL_MULS_QQQ(36, 0x1000ULL, 
                                                                            (0xfffffffffULL 
                                                                             & VL_EXTENDS_QI(36,6, (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__init_addr))))), 0xeULL)
                                                  : 
                                                 VL_DIVS_QQQ(36, 
                                                             (0xfffffffffULL 
                                                              & VL_MULS_QQQ(36, 0x1000ULL, 
                                                                            (0xfffffffffULL 
                                                                             & VL_EXTENDS_QI(36,32, 
                                                                                ((IData)(0x1cU) 
                                                                                - (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__init_addr)))))), 0xeULL)))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__next_N_raddr 
        = ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__mem_N_raddr))
            ? 0U : (0x1fU & ((IData)(1U) + (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__mem_N_raddr))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__next_Nm1_raddr 
        = ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__mem_Nm1_raddr))
            ? 0U : (0x1fU & ((IData)(1U) + (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__mem_Nm1_raddr))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__next_N_raddr 
        = ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__mem_N_raddr))
            ? 0U : (0x1fU & ((IData)(1U) + (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__mem_N_raddr))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__next_Nm1_raddr 
        = ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__mem_Nm1_raddr))
            ? 0U : (0x1fU & ((IData)(1U) + (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__mem_Nm1_raddr))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__next_N_raddr 
        = ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__mem_N_raddr))
            ? 0U : (0x1fU & ((IData)(1U) + (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__mem_N_raddr))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__next_Nm1_raddr 
        = ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__mem_Nm1_raddr))
            ? 0U : (0x1fU & ((IData)(1U) + (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__mem_Nm1_raddr))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__next_N_raddr 
        = ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__mem_N_raddr))
            ? 0U : (0x1fU & ((IData)(1U) + (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__mem_N_raddr))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__next_Nm1_raddr 
        = ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__mem_Nm1_raddr))
            ? 0U : (0x1fU & ((IData)(1U) + (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__mem_Nm1_raddr))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__next_N_raddr 
        = ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__mem_N_raddr))
            ? 0U : (0x1fU & ((IData)(1U) + (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__mem_N_raddr))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__next_Nm1_raddr 
        = ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__mem_Nm1_raddr))
            ? 0U : (0x1fU & ((IData)(1U) + (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__mem_Nm1_raddr))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__next_N_raddr 
        = ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__mem_N_raddr))
            ? 0U : (0x1fU & ((IData)(1U) + (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__mem_N_raddr))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__next_Nm1_raddr 
        = ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__mem_Nm1_raddr))
            ? 0U : (0x1fU & ((IData)(1U) + (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__mem_Nm1_raddr))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__next_N_raddr 
        = ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__mem_N_raddr))
            ? 0U : (0x1fU & ((IData)(1U) + (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__mem_N_raddr))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__next_Nm1_raddr 
        = ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__mem_Nm1_raddr))
            ? 0U : (0x1fU & ((IData)(1U) + (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__mem_Nm1_raddr))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__next_N_raddr 
        = ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__mem_N_raddr))
            ? 0U : (0x1fU & ((IData)(1U) + (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__mem_N_raddr))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__next_Nm1_raddr 
        = ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__mem_Nm1_raddr))
            ? 0U : (0x1fU & ((IData)(1U) + (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__mem_Nm1_raddr))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__next_N_raddr 
        = ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__mem_N_raddr))
            ? 0U : (0x1fU & ((IData)(1U) + (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__mem_N_raddr))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__next_Nm1_raddr 
        = ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__mem_Nm1_raddr))
            ? 0U : (0x1fU & ((IData)(1U) + (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__mem_Nm1_raddr))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__next_N_raddr 
        = ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__mem_N_raddr))
            ? 0U : (0x1fU & ((IData)(1U) + (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__mem_N_raddr))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__next_Nm1_raddr 
        = ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__mem_Nm1_raddr))
            ? 0U : (0x1fU & ((IData)(1U) + (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__mem_Nm1_raddr))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__next_state 
        = ((4U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__state))
            ? ((2U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__state))
                ? ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__state))
                    ? ((IData)(vlSelf->next_sample)
                        ? 1U : 7U) : 7U) : ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__state))
                                             ? ((0x1cU 
                                                 == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__node_count))
                                                 ? 6U
                                                 : 5U)
                                             : 5U))
            : ((2U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__state))
                ? ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__state))
                    ? 4U : 3U) : ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__state))
                                   ? 2U : ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__init_addr))
                                            ? 1U : 0U))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__next_state 
        = ((4U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__state))
            ? ((2U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__state))
                ? ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__state))
                    ? ((IData)(vlSelf->next_sample)
                        ? 1U : 7U) : 7U) : ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__state))
                                             ? ((0x1cU 
                                                 == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__node_count))
                                                 ? 6U
                                                 : 5U)
                                             : 5U))
            : ((2U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__state))
                ? ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__state))
                    ? 4U : 3U) : ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__state))
                                   ? 2U : ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__init_addr))
                                            ? 1U : 0U))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__next_state 
        = ((4U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__state))
            ? ((2U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__state))
                ? ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__state))
                    ? ((IData)(vlSelf->next_sample)
                        ? 1U : 7U) : 7U) : ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__state))
                                             ? ((0x1cU 
                                                 == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__node_count))
                                                 ? 6U
                                                 : 5U)
                                             : 5U))
            : ((2U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__state))
                ? ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__state))
                    ? 4U : 3U) : ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__state))
                                   ? 2U : ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__init_addr))
                                            ? 1U : 0U))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__next_state 
        = ((4U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__state))
            ? ((2U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__state))
                ? ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__state))
                    ? ((IData)(vlSelf->next_sample)
                        ? 1U : 7U) : 7U) : ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__state))
                                             ? ((0x1cU 
                                                 == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__node_count))
                                                 ? 6U
                                                 : 5U)
                                             : 5U))
            : ((2U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__state))
                ? ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__state))
                    ? 4U : 3U) : ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__state))
                                   ? 2U : ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__init_addr))
                                            ? 1U : 0U))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__next_state 
        = ((4U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__state))
            ? ((2U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__state))
                ? ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__state))
                    ? ((IData)(vlSelf->next_sample)
                        ? 1U : 7U) : 7U) : ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__state))
                                             ? ((0x1cU 
                                                 == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__node_count))
                                                 ? 6U
                                                 : 5U)
                                             : 5U))
            : ((2U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__state))
                ? ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__state))
                    ? 4U : 3U) : ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__state))
                                   ? 2U : ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__init_addr))
                                            ? 1U : 0U))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__next_state 
        = ((4U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__state))
            ? ((2U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__state))
                ? ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__state))
                    ? ((IData)(vlSelf->next_sample)
                        ? 1U : 7U) : 7U) : ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__state))
                                             ? ((0x1cU 
                                                 == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__node_count))
                                                 ? 6U
                                                 : 5U)
                                             : 5U))
            : ((2U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__state))
                ? ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__state))
                    ? 4U : 3U) : ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__state))
                                   ? 2U : ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__init_addr))
                                            ? 1U : 0U))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__next_state 
        = ((4U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__state))
            ? ((2U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__state))
                ? ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__state))
                    ? ((IData)(vlSelf->next_sample)
                        ? 1U : 7U) : 7U) : ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__state))
                                             ? ((0x1cU 
                                                 == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__node_count))
                                                 ? 6U
                                                 : 5U)
                                             : 5U))
            : ((2U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__state))
                ? ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__state))
                    ? 4U : 3U) : ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__state))
                                   ? 2U : ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__init_addr))
                                            ? 1U : 0U))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__next_state 
        = ((4U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__state))
            ? ((2U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__state))
                ? ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__state))
                    ? ((IData)(vlSelf->next_sample)
                        ? 1U : 7U) : 7U) : ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__state))
                                             ? ((0x1cU 
                                                 == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__node_count))
                                                 ? 6U
                                                 : 5U)
                                             : 5U))
            : ((2U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__state))
                ? ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__state))
                    ? 4U : 3U) : ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__state))
                                   ? 2U : ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__init_addr))
                                            ? 1U : 0U))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__next_state 
        = ((4U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__state))
            ? ((2U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__state))
                ? ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__state))
                    ? ((IData)(vlSelf->next_sample)
                        ? 1U : 7U) : 7U) : ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__state))
                                             ? ((0x1cU 
                                                 == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__node_count))
                                                 ? 6U
                                                 : 5U)
                                             : 5U))
            : ((2U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__state))
                ? ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__state))
                    ? 4U : 3U) : ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__state))
                                   ? 2U : ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__init_addr))
                                            ? 1U : 0U))));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__next_state 
        = ((4U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__state))
            ? ((2U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__state))
                ? ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__state))
                    ? ((IData)(vlSelf->next_sample)
                        ? 1U : 7U) : 7U) : ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__state))
                                             ? ((0x1cU 
                                                 == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__node_count))
                                                 ? 6U
                                                 : 5U)
                                             : 5U))
            : ((2U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__state))
                ? ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__state))
                    ? 4U : 3U) : ((1U & (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__state))
                                   ? 2U : ((0x1cU == (IData)(vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__init_addr))
                                            ? 1U : 0U))));
    vlSelf->done = ((IData)(vlSelf->multi_column_drum__DOT____Vcellout__column_gen__BRA__9__KET____DOT__column_inst__done) 
                    & ((IData)(vlSelf->multi_column_drum__DOT____Vcellout__column_gen__BRA__8__KET____DOT__column_inst__done) 
                       & ((IData)(vlSelf->multi_column_drum__DOT____Vcellout__column_gen__BRA__7__KET____DOT__column_inst__done) 
                          & ((IData)(vlSelf->multi_column_drum__DOT____Vcellout__column_gen__BRA__6__KET____DOT__column_inst__done) 
                             & ((IData)(vlSelf->multi_column_drum__DOT____Vcellout__column_gen__BRA__5__KET____DOT__column_inst__done) 
                                & ((IData)(vlSelf->multi_column_drum__DOT____Vcellout__column_gen__BRA__4__KET____DOT__column_inst__done) 
                                   & ((IData)(vlSelf->multi_column_drum__DOT____Vcellout__column_gen__BRA__3__KET____DOT__column_inst__done) 
                                      & ((IData)(vlSelf->multi_column_drum__DOT____Vcellout__column_gen__BRA__2__KET____DOT__column_inst__done) 
                                         & ((IData)(vlSelf->multi_column_drum__DOT____Vcellout__column_gen__BRA__1__KET____DOT__column_inst__done) 
                                            & (IData)(vlSelf->multi_column_drum__DOT____Vcellout__column_gen__BRA__0__KET____DOT__column_inst__done))))))))));
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__0__b 
        = (0x3ffffU & (((vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__u_up 
                         + vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__u_down) 
                        + vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__u_center) 
                       - VL_SHIFTL_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__u_center, 1U)));
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__0__a 
        = vlSelf->rho_eff;
    multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
        = (0xfffffffffULL & VL_MULS_QQQ(36, (0xfffffffffULL 
                                             & VL_EXTENDS_QI(36,18, __Vfunc_multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__0__a)), 
                                        (0xfffffffffULL 
                                         & VL_EXTENDS_QI(36,18, __Vfunc_multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__0__b))));
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__0__Vfuncout 
        = ((0x20000U & ((IData)((multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
                                 >> 0x23U)) << 0x11U)) 
           | (0x1ffffU & (IData)((multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
                                  >> 0x11U))));
    multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__compute__DOT__product 
        = __Vfunc_multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__0__Vfuncout;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__9__b 
        = (0x3ffffU & (((vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__u_up 
                         + vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__u_down) 
                        + vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__u_center) 
                       - VL_SHIFTL_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__u_center, 1U)));
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__9__a 
        = vlSelf->rho_eff;
    multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
        = (0xfffffffffULL & VL_MULS_QQQ(36, (0xfffffffffULL 
                                             & VL_EXTENDS_QI(36,18, __Vfunc_multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__9__a)), 
                                        (0xfffffffffULL 
                                         & VL_EXTENDS_QI(36,18, __Vfunc_multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__9__b))));
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__9__Vfuncout 
        = ((0x20000U & ((IData)((multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
                                 >> 0x23U)) << 0x11U)) 
           | (0x1ffffU & (IData)((multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
                                  >> 0x11U))));
    multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__compute__DOT__product 
        = __Vfunc_multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__9__Vfuncout;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__1__b 
        = (0x3ffffU & ((((vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__u_up 
                          + vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__u_down) 
                         + vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__u_center) 
                        + vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__u_center) 
                       - VL_SHIFTL_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__u_center, 1U)));
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__1__a 
        = vlSelf->rho_eff;
    multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
        = (0xfffffffffULL & VL_MULS_QQQ(36, (0xfffffffffULL 
                                             & VL_EXTENDS_QI(36,18, __Vfunc_multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__1__a)), 
                                        (0xfffffffffULL 
                                         & VL_EXTENDS_QI(36,18, __Vfunc_multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__1__b))));
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__1__Vfuncout 
        = ((0x20000U & ((IData)((multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
                                 >> 0x23U)) << 0x11U)) 
           | (0x1ffffU & (IData)((multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
                                  >> 0x11U))));
    multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__compute__DOT__product 
        = __Vfunc_multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__1__Vfuncout;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__2__b 
        = (0x3ffffU & ((((vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__u_up 
                          + vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__u_down) 
                         + vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__u_center) 
                        + vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__u_center) 
                       - VL_SHIFTL_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__u_center, 1U)));
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__2__a 
        = vlSelf->rho_eff;
    multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
        = (0xfffffffffULL & VL_MULS_QQQ(36, (0xfffffffffULL 
                                             & VL_EXTENDS_QI(36,18, __Vfunc_multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__2__a)), 
                                        (0xfffffffffULL 
                                         & VL_EXTENDS_QI(36,18, __Vfunc_multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__2__b))));
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__2__Vfuncout 
        = ((0x20000U & ((IData)((multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
                                 >> 0x23U)) << 0x11U)) 
           | (0x1ffffU & (IData)((multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
                                  >> 0x11U))));
    multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__compute__DOT__product 
        = __Vfunc_multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__2__Vfuncout;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__3__b 
        = (0x3ffffU & ((((vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__u_up 
                          + vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__u_down) 
                         + vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__u_center) 
                        + vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__u_center) 
                       - VL_SHIFTL_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__u_center, 1U)));
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__3__a 
        = vlSelf->rho_eff;
    multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
        = (0xfffffffffULL & VL_MULS_QQQ(36, (0xfffffffffULL 
                                             & VL_EXTENDS_QI(36,18, __Vfunc_multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__3__a)), 
                                        (0xfffffffffULL 
                                         & VL_EXTENDS_QI(36,18, __Vfunc_multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__3__b))));
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__3__Vfuncout 
        = ((0x20000U & ((IData)((multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
                                 >> 0x23U)) << 0x11U)) 
           | (0x1ffffU & (IData)((multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
                                  >> 0x11U))));
    multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__compute__DOT__product 
        = __Vfunc_multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__3__Vfuncout;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__4__b 
        = (0x3ffffU & ((((vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__u_up 
                          + vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__u_down) 
                         + vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__u_center) 
                        + vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__u_center) 
                       - VL_SHIFTL_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__u_center, 1U)));
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__4__a 
        = vlSelf->rho_eff;
    multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
        = (0xfffffffffULL & VL_MULS_QQQ(36, (0xfffffffffULL 
                                             & VL_EXTENDS_QI(36,18, __Vfunc_multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__4__a)), 
                                        (0xfffffffffULL 
                                         & VL_EXTENDS_QI(36,18, __Vfunc_multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__4__b))));
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__4__Vfuncout 
        = ((0x20000U & ((IData)((multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
                                 >> 0x23U)) << 0x11U)) 
           | (0x1ffffU & (IData)((multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
                                  >> 0x11U))));
    multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__compute__DOT__product 
        = __Vfunc_multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__4__Vfuncout;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__5__b 
        = (0x3ffffU & ((((vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__u_up 
                          + vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__u_down) 
                         + vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__u_center) 
                        + vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__u_center) 
                       - VL_SHIFTL_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__u_center, 1U)));
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__5__a 
        = vlSelf->rho_eff;
    multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
        = (0xfffffffffULL & VL_MULS_QQQ(36, (0xfffffffffULL 
                                             & VL_EXTENDS_QI(36,18, __Vfunc_multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__5__a)), 
                                        (0xfffffffffULL 
                                         & VL_EXTENDS_QI(36,18, __Vfunc_multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__5__b))));
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__5__Vfuncout 
        = ((0x20000U & ((IData)((multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
                                 >> 0x23U)) << 0x11U)) 
           | (0x1ffffU & (IData)((multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
                                  >> 0x11U))));
    multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__compute__DOT__product 
        = __Vfunc_multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__5__Vfuncout;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__6__b 
        = (0x3ffffU & ((((vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__u_up 
                          + vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__u_down) 
                         + vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__u_center) 
                        + vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__u_center) 
                       - VL_SHIFTL_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__u_center, 1U)));
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__6__a 
        = vlSelf->rho_eff;
    multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
        = (0xfffffffffULL & VL_MULS_QQQ(36, (0xfffffffffULL 
                                             & VL_EXTENDS_QI(36,18, __Vfunc_multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__6__a)), 
                                        (0xfffffffffULL 
                                         & VL_EXTENDS_QI(36,18, __Vfunc_multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__6__b))));
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__6__Vfuncout 
        = ((0x20000U & ((IData)((multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
                                 >> 0x23U)) << 0x11U)) 
           | (0x1ffffU & (IData)((multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
                                  >> 0x11U))));
    multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__compute__DOT__product 
        = __Vfunc_multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__6__Vfuncout;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__7__b 
        = (0x3ffffU & ((((vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__u_up 
                          + vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__u_down) 
                         + vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__u_center) 
                        + vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__u_center) 
                       - VL_SHIFTL_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__u_center, 1U)));
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__7__a 
        = vlSelf->rho_eff;
    multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
        = (0xfffffffffULL & VL_MULS_QQQ(36, (0xfffffffffULL 
                                             & VL_EXTENDS_QI(36,18, __Vfunc_multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__7__a)), 
                                        (0xfffffffffULL 
                                         & VL_EXTENDS_QI(36,18, __Vfunc_multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__7__b))));
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__7__Vfuncout 
        = ((0x20000U & ((IData)((multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
                                 >> 0x23U)) << 0x11U)) 
           | (0x1ffffU & (IData)((multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
                                  >> 0x11U))));
    multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__compute__DOT__product 
        = __Vfunc_multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__7__Vfuncout;
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__8__b 
        = (0x3ffffU & ((((vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__u_up 
                          + vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__u_down) 
                         + vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__u_center) 
                        + vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__u_center) 
                       - VL_SHIFTL_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__u_center, 1U)));
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__8__a 
        = vlSelf->rho_eff;
    multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
        = (0xfffffffffULL & VL_MULS_QQQ(36, (0xfffffffffULL 
                                             & VL_EXTENDS_QI(36,18, __Vfunc_multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__8__a)), 
                                        (0xfffffffffULL 
                                         & VL_EXTENDS_QI(36,18, __Vfunc_multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__8__b))));
    __Vfunc_multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__8__Vfuncout 
        = ((0x20000U & ((IData)((multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
                                 >> 0x23U)) << 0x11U)) 
           | (0x1ffffU & (IData)((multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__Vstatic__mult_out 
                                  >> 0x11U))));
    multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__compute__DOT__product 
        = __Vfunc_multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__compute__DOT__mult_1p17__8__Vfuncout;
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__compute__DOT__sum 
        = (0x3ffffU & (((multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__compute__DOT__product 
                         + VL_SHIFTL_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__u_center, 1U)) 
                        - vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__u_center_prev) 
                       + VL_SHIFTRS_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__u_center_prev, 0xaU)));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__compute__DOT__sum 
        = (0x3ffffU & (((multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__compute__DOT__product 
                         + VL_SHIFTL_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__u_center, 1U)) 
                        - vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__u_center_prev) 
                       + VL_SHIFTRS_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__u_center_prev, 0xaU)));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__compute__DOT__sum 
        = (0x3ffffU & (((multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__compute__DOT__product 
                         + VL_SHIFTL_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__u_center, 1U)) 
                        - vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__u_center_prev) 
                       + VL_SHIFTRS_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__u_center_prev, 0xaU)));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__compute__DOT__sum 
        = (0x3ffffU & (((multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__compute__DOT__product 
                         + VL_SHIFTL_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__u_center, 1U)) 
                        - vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__u_center_prev) 
                       + VL_SHIFTRS_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__u_center_prev, 0xaU)));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__compute__DOT__sum 
        = (0x3ffffU & (((multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__compute__DOT__product 
                         + VL_SHIFTL_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__u_center, 1U)) 
                        - vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__u_center_prev) 
                       + VL_SHIFTRS_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__u_center_prev, 0xaU)));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__compute__DOT__sum 
        = (0x3ffffU & (((multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__compute__DOT__product 
                         + VL_SHIFTL_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__u_center, 1U)) 
                        - vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__u_center_prev) 
                       + VL_SHIFTRS_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__u_center_prev, 0xaU)));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__compute__DOT__sum 
        = (0x3ffffU & (((multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__compute__DOT__product 
                         + VL_SHIFTL_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__u_center, 1U)) 
                        - vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__u_center_prev) 
                       + VL_SHIFTRS_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__u_center_prev, 0xaU)));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__compute__DOT__sum 
        = (0x3ffffU & (((multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__compute__DOT__product 
                         + VL_SHIFTL_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__u_center, 1U)) 
                        - vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__u_center_prev) 
                       + VL_SHIFTRS_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__u_center_prev, 0xaU)));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__compute__DOT__sum 
        = (0x3ffffU & (((multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__compute__DOT__product 
                         + VL_SHIFTL_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__u_center, 1U)) 
                        - vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__u_center_prev) 
                       + VL_SHIFTRS_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__u_center_prev, 0xaU)));
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__compute__DOT__sum 
        = (0x3ffffU & (((multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__compute__DOT__product 
                         + VL_SHIFTL_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__u_center, 1U)) 
                        - vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__u_center_prev) 
                       + VL_SHIFTRS_III(18,18,32, vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__u_center_prev, 0xaU)));
}

VL_ATTR_COLD void Vmulti_column_drum___024root___eval_stl(Vmulti_column_drum___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmulti_column_drum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmulti_column_drum___024root___eval_stl\n"); );
    // Body
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        Vmulti_column_drum___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void Vmulti_column_drum___024root___eval_triggers__stl(Vmulti_column_drum___024root* vlSelf);

VL_ATTR_COLD bool Vmulti_column_drum___024root___eval_phase__stl(Vmulti_column_drum___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmulti_column_drum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmulti_column_drum___024root___eval_phase__stl\n"); );
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vmulti_column_drum___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelf->__VstlTriggered.any();
    if (__VstlExecute) {
        Vmulti_column_drum___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmulti_column_drum___024root___dump_triggers__ico(Vmulti_column_drum___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmulti_column_drum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmulti_column_drum___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VicoTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmulti_column_drum___024root___dump_triggers__act(Vmulti_column_drum___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmulti_column_drum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmulti_column_drum___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmulti_column_drum___024root___dump_triggers__nba(Vmulti_column_drum___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmulti_column_drum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmulti_column_drum___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vmulti_column_drum___024root___ctor_var_reset(Vmulti_column_drum___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmulti_column_drum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmulti_column_drum___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->rst = VL_RAND_RESET_I(1);
    vlSelf->next_sample = VL_RAND_RESET_I(1);
    vlSelf->rho_eff = VL_RAND_RESET_I(18);
    vlSelf->G_tension = VL_RAND_RESET_I(18);
    vlSelf->center_center_node = VL_RAND_RESET_I(18);
    vlSelf->done = VL_RAND_RESET_I(1);
    vlSelf->multi_column_drum__DOT____Vcellout__column_gen__BRA__0__KET____DOT__column_inst__done = VL_RAND_RESET_I(1);
    vlSelf->multi_column_drum__DOT____Vcellout__column_gen__BRA__1__KET____DOT__column_inst__done = VL_RAND_RESET_I(1);
    vlSelf->multi_column_drum__DOT____Vcellout__column_gen__BRA__2__KET____DOT__column_inst__done = VL_RAND_RESET_I(1);
    vlSelf->multi_column_drum__DOT____Vcellout__column_gen__BRA__3__KET____DOT__column_inst__done = VL_RAND_RESET_I(1);
    vlSelf->multi_column_drum__DOT____Vcellout__column_gen__BRA__4__KET____DOT__column_inst__done = VL_RAND_RESET_I(1);
    vlSelf->multi_column_drum__DOT____Vcellout__column_gen__BRA__4__KET____DOT__column_inst__u_middle_node = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT____Vcellout__column_gen__BRA__5__KET____DOT__column_inst__done = VL_RAND_RESET_I(1);
    vlSelf->multi_column_drum__DOT____Vcellout__column_gen__BRA__6__KET____DOT__column_inst__done = VL_RAND_RESET_I(1);
    vlSelf->multi_column_drum__DOT____Vcellout__column_gen__BRA__7__KET____DOT__column_inst__done = VL_RAND_RESET_I(1);
    vlSelf->multi_column_drum__DOT____Vcellout__column_gen__BRA__8__KET____DOT__column_inst__done = VL_RAND_RESET_I(1);
    vlSelf->multi_column_drum__DOT____Vcellout__column_gen__BRA__9__KET____DOT__column_inst__done = VL_RAND_RESET_I(1);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__u_up = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__u_down = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__u_center = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__u_center_prev = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__mem_N_rdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__mem_N_wdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__mem_N_waddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__mem_N_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__mem_Nm1_rdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__mem_Nm1_wdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__mem_Nm1_waddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__mem_Nm1_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__init_addr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__node_count = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__next_N_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__next_Nm1_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__state = VL_RAND_RESET_I(3);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__next_state = VL_RAND_RESET_I(3);
    for (int __Vi0 = 0; __Vi0 < 29; ++__Vi0) {
        vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__mem_N__DOT__mem[__Vi0] = VL_RAND_RESET_I(18);
    }
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__mem_N__DOT____Vlvbound_h61a5f7c7__0 = VL_RAND_RESET_I(18);
    for (int __Vi0 = 0; __Vi0 < 29; ++__Vi0) {
        vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__mem_Nm1__DOT__mem[__Vi0] = VL_RAND_RESET_I(18);
    }
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__mem_Nm1__DOT____Vlvbound_h61a5f7c7__0 = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__0__KET____DOT__column_inst__DOT__compute__DOT__sum = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__u_up = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__u_down = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__u_center = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__u_center_prev = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__mem_N_rdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__mem_N_wdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__mem_N_waddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__mem_N_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__mem_Nm1_rdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__mem_Nm1_wdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__mem_Nm1_waddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__mem_Nm1_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__mem_Nm1_we = VL_RAND_RESET_I(1);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__init_addr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__node_count = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__triangle_value = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__next_N_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__next_Nm1_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__state = VL_RAND_RESET_I(3);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__next_state = VL_RAND_RESET_I(3);
    for (int __Vi0 = 0; __Vi0 < 29; ++__Vi0) {
        vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__mem_N__DOT__mem[__Vi0] = VL_RAND_RESET_I(18);
    }
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__mem_N__DOT____Vlvbound_h61a5f7c7__0 = VL_RAND_RESET_I(18);
    for (int __Vi0 = 0; __Vi0 < 29; ++__Vi0) {
        vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__mem_Nm1__DOT__mem[__Vi0] = VL_RAND_RESET_I(18);
    }
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__mem_Nm1__DOT____Vlvbound_h61a5f7c7__0 = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__1__KET____DOT__column_inst__DOT__compute__DOT__sum = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__u_up = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__u_down = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__u_center = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__u_center_prev = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__mem_N_rdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__mem_N_wdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__mem_N_waddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__mem_N_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__mem_Nm1_rdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__mem_Nm1_wdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__mem_Nm1_waddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__mem_Nm1_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__init_addr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__node_count = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__triangle_value = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__next_N_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__next_Nm1_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__state = VL_RAND_RESET_I(3);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__next_state = VL_RAND_RESET_I(3);
    for (int __Vi0 = 0; __Vi0 < 29; ++__Vi0) {
        vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__mem_N__DOT__mem[__Vi0] = VL_RAND_RESET_I(18);
    }
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__mem_N__DOT____Vlvbound_h61a5f7c7__0 = VL_RAND_RESET_I(18);
    for (int __Vi0 = 0; __Vi0 < 29; ++__Vi0) {
        vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__mem_Nm1__DOT__mem[__Vi0] = VL_RAND_RESET_I(18);
    }
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__mem_Nm1__DOT____Vlvbound_h61a5f7c7__0 = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__2__KET____DOT__column_inst__DOT__compute__DOT__sum = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__u_up = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__u_down = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__u_center = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__u_center_prev = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__mem_N_rdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__mem_N_wdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__mem_N_waddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__mem_N_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__mem_Nm1_rdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__mem_Nm1_wdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__mem_Nm1_waddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__mem_Nm1_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__mem_Nm1_we = VL_RAND_RESET_I(1);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__init_addr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__node_count = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__triangle_value = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__next_N_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__next_Nm1_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__state = VL_RAND_RESET_I(3);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__next_state = VL_RAND_RESET_I(3);
    for (int __Vi0 = 0; __Vi0 < 29; ++__Vi0) {
        vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__mem_N__DOT__mem[__Vi0] = VL_RAND_RESET_I(18);
    }
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__mem_N__DOT____Vlvbound_h61a5f7c7__0 = VL_RAND_RESET_I(18);
    for (int __Vi0 = 0; __Vi0 < 29; ++__Vi0) {
        vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__mem_Nm1__DOT__mem[__Vi0] = VL_RAND_RESET_I(18);
    }
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__mem_Nm1__DOT____Vlvbound_h61a5f7c7__0 = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__3__KET____DOT__column_inst__DOT__compute__DOT__sum = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__u_up = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__u_down = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__u_center = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__u_center_prev = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__mem_N_rdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__mem_N_wdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__mem_N_waddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__mem_N_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__mem_N_we = VL_RAND_RESET_I(1);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__mem_Nm1_rdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__mem_Nm1_wdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__mem_Nm1_waddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__mem_Nm1_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__init_addr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__node_count = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__triangle_value = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__next_N_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__next_Nm1_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__state = VL_RAND_RESET_I(3);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__next_state = VL_RAND_RESET_I(3);
    for (int __Vi0 = 0; __Vi0 < 29; ++__Vi0) {
        vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__mem_N__DOT__mem[__Vi0] = VL_RAND_RESET_I(18);
    }
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__mem_N__DOT____Vlvbound_h61a5f7c7__0 = VL_RAND_RESET_I(18);
    for (int __Vi0 = 0; __Vi0 < 29; ++__Vi0) {
        vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__mem_Nm1__DOT__mem[__Vi0] = VL_RAND_RESET_I(18);
    }
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__mem_Nm1__DOT____Vlvbound_h61a5f7c7__0 = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__4__KET____DOT__column_inst__DOT__compute__DOT__sum = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__u_up = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__u_down = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__u_center = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__u_center_prev = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__mem_N_rdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__mem_N_wdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__mem_N_waddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__mem_N_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__mem_Nm1_rdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__mem_Nm1_wdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__mem_Nm1_waddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__mem_Nm1_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__mem_Nm1_we = VL_RAND_RESET_I(1);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__init_addr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__node_count = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__triangle_value = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__next_N_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__next_Nm1_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__state = VL_RAND_RESET_I(3);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__next_state = VL_RAND_RESET_I(3);
    for (int __Vi0 = 0; __Vi0 < 29; ++__Vi0) {
        vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__mem_N__DOT__mem[__Vi0] = VL_RAND_RESET_I(18);
    }
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__mem_N__DOT____Vlvbound_h61a5f7c7__0 = VL_RAND_RESET_I(18);
    for (int __Vi0 = 0; __Vi0 < 29; ++__Vi0) {
        vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__mem_Nm1__DOT__mem[__Vi0] = VL_RAND_RESET_I(18);
    }
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__mem_Nm1__DOT____Vlvbound_h61a5f7c7__0 = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__5__KET____DOT__column_inst__DOT__compute__DOT__sum = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__u_up = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__u_down = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__u_center = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__u_center_prev = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__mem_N_rdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__mem_N_wdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__mem_N_waddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__mem_N_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__mem_Nm1_rdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__mem_Nm1_wdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__mem_Nm1_waddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__mem_Nm1_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__mem_Nm1_we = VL_RAND_RESET_I(1);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__init_addr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__node_count = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__triangle_value = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__next_N_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__next_Nm1_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__state = VL_RAND_RESET_I(3);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__next_state = VL_RAND_RESET_I(3);
    for (int __Vi0 = 0; __Vi0 < 29; ++__Vi0) {
        vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__mem_N__DOT__mem[__Vi0] = VL_RAND_RESET_I(18);
    }
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__mem_N__DOT____Vlvbound_h61a5f7c7__0 = VL_RAND_RESET_I(18);
    for (int __Vi0 = 0; __Vi0 < 29; ++__Vi0) {
        vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__mem_Nm1__DOT__mem[__Vi0] = VL_RAND_RESET_I(18);
    }
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__mem_Nm1__DOT____Vlvbound_h61a5f7c7__0 = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__6__KET____DOT__column_inst__DOT__compute__DOT__sum = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__u_up = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__u_down = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__u_center = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__u_center_prev = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__mem_N_rdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__mem_N_wdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__mem_N_waddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__mem_N_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__mem_Nm1_rdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__mem_Nm1_wdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__mem_Nm1_waddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__mem_Nm1_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__init_addr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__node_count = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__triangle_value = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__next_N_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__next_Nm1_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__state = VL_RAND_RESET_I(3);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__next_state = VL_RAND_RESET_I(3);
    for (int __Vi0 = 0; __Vi0 < 29; ++__Vi0) {
        vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__mem_N__DOT__mem[__Vi0] = VL_RAND_RESET_I(18);
    }
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__mem_N__DOT____Vlvbound_h61a5f7c7__0 = VL_RAND_RESET_I(18);
    for (int __Vi0 = 0; __Vi0 < 29; ++__Vi0) {
        vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__mem_Nm1__DOT__mem[__Vi0] = VL_RAND_RESET_I(18);
    }
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__mem_Nm1__DOT____Vlvbound_h61a5f7c7__0 = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__7__KET____DOT__column_inst__DOT__compute__DOT__sum = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__u_up = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__u_down = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__u_center = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__u_center_prev = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__mem_N_rdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__mem_N_wdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__mem_N_waddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__mem_N_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__mem_Nm1_rdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__mem_Nm1_wdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__mem_Nm1_waddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__mem_Nm1_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__mem_Nm1_we = VL_RAND_RESET_I(1);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__init_addr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__node_count = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__next_N_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__next_Nm1_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__state = VL_RAND_RESET_I(3);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__next_state = VL_RAND_RESET_I(3);
    for (int __Vi0 = 0; __Vi0 < 29; ++__Vi0) {
        vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__mem_N__DOT__mem[__Vi0] = VL_RAND_RESET_I(18);
    }
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__mem_N__DOT____Vlvbound_h61a5f7c7__0 = VL_RAND_RESET_I(18);
    for (int __Vi0 = 0; __Vi0 < 29; ++__Vi0) {
        vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__mem_Nm1__DOT__mem[__Vi0] = VL_RAND_RESET_I(18);
    }
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__mem_Nm1__DOT____Vlvbound_h61a5f7c7__0 = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__8__KET____DOT__column_inst__DOT__compute__DOT__sum = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__u_up = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__u_down = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__u_center = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__u_center_prev = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__mem_N_rdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__mem_N_wdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__mem_N_waddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__mem_N_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__mem_Nm1_rdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__mem_Nm1_wdata = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__mem_Nm1_waddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__mem_Nm1_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__init_addr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__node_count = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__next_N_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__next_Nm1_raddr = VL_RAND_RESET_I(5);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__state = VL_RAND_RESET_I(3);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__next_state = VL_RAND_RESET_I(3);
    for (int __Vi0 = 0; __Vi0 < 29; ++__Vi0) {
        vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__mem_N__DOT__mem[__Vi0] = VL_RAND_RESET_I(18);
    }
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__mem_N__DOT____Vlvbound_h61a5f7c7__0 = VL_RAND_RESET_I(18);
    for (int __Vi0 = 0; __Vi0 < 29; ++__Vi0) {
        vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__mem_Nm1__DOT__mem[__Vi0] = VL_RAND_RESET_I(18);
    }
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__mem_Nm1__DOT____Vlvbound_h61a5f7c7__0 = VL_RAND_RESET_I(18);
    vlSelf->multi_column_drum__DOT__column_gen__BRA__9__KET____DOT__column_inst__DOT__compute__DOT__sum = VL_RAND_RESET_I(18);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_RAND_RESET_I(1);
}
