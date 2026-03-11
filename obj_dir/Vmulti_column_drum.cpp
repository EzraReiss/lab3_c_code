// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vmulti_column_drum__pch.h"

//============================================================
// Constructors

Vmulti_column_drum::Vmulti_column_drum(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vmulti_column_drum__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , next_sample{vlSymsp->TOP.next_sample}
    , done{vlSymsp->TOP.done}
    , rho_eff{vlSymsp->TOP.rho_eff}
    , G_tension{vlSymsp->TOP.G_tension}
    , center_center_node{vlSymsp->TOP.center_center_node}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vmulti_column_drum::Vmulti_column_drum(const char* _vcname__)
    : Vmulti_column_drum(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vmulti_column_drum::~Vmulti_column_drum() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vmulti_column_drum___024root___eval_debug_assertions(Vmulti_column_drum___024root* vlSelf);
#endif  // VL_DEBUG
void Vmulti_column_drum___024root___eval_static(Vmulti_column_drum___024root* vlSelf);
void Vmulti_column_drum___024root___eval_initial(Vmulti_column_drum___024root* vlSelf);
void Vmulti_column_drum___024root___eval_settle(Vmulti_column_drum___024root* vlSelf);
void Vmulti_column_drum___024root___eval(Vmulti_column_drum___024root* vlSelf);

void Vmulti_column_drum::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vmulti_column_drum::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vmulti_column_drum___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vmulti_column_drum___024root___eval_static(&(vlSymsp->TOP));
        Vmulti_column_drum___024root___eval_initial(&(vlSymsp->TOP));
        Vmulti_column_drum___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vmulti_column_drum___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vmulti_column_drum::eventsPending() { return false; }

uint64_t Vmulti_column_drum::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vmulti_column_drum::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vmulti_column_drum___024root___eval_final(Vmulti_column_drum___024root* vlSelf);

VL_ATTR_COLD void Vmulti_column_drum::final() {
    Vmulti_column_drum___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vmulti_column_drum::hierName() const { return vlSymsp->name(); }
const char* Vmulti_column_drum::modelName() const { return "Vmulti_column_drum"; }
unsigned Vmulti_column_drum::threads() const { return 1; }
void Vmulti_column_drum::prepareClone() const { contextp()->prepareClone(); }
void Vmulti_column_drum::atClone() const {
    contextp()->threadPoolpOnClone();
}

//============================================================
// Trace configuration

VL_ATTR_COLD void Vmulti_column_drum::trace(VerilatedVcdC* tfp, int levels, int options) {
    vl_fatal(__FILE__, __LINE__, __FILE__,"'Vmulti_column_drum::trace()' called on model that was Verilated without --trace option");
}
