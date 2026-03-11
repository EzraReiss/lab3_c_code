// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmulti_column_drum.h for the primary calling header

#include "Vmulti_column_drum__pch.h"
#include "Vmulti_column_drum__Syms.h"
#include "Vmulti_column_drum___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmulti_column_drum___024root___dump_triggers__stl(Vmulti_column_drum___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vmulti_column_drum___024root___eval_triggers__stl(Vmulti_column_drum___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmulti_column_drum__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmulti_column_drum___024root___eval_triggers__stl\n"); );
    // Body
    vlSelf->__VstlTriggered.set(0U, (IData)(vlSelf->__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vmulti_column_drum___024root___dump_triggers__stl(vlSelf);
    }
#endif
}
