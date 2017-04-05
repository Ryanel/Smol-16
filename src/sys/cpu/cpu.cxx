#include <cpu/cpu.hpp>

CCpu::CCpu() {
    _log = spdlog::stdout_color_mt("cpu");
    _log->info("Initialised");
    this->Reset();
}

CCpu::~CCpu() {
    this->Reset();
}

void CCpu::Init() {

}
void CCpu::Start() {
    _log->debug("Started");
    isActive = true;

}
void CCpu::Stop() {
    _log->debug("Stopped");
    isActive = false;

}
void CCpu::Tick() {
    InterpretCycle();
}
void CCpu::Reset() {
    _log->debug("Reset");
    this->Stop();
    for(int i = 0; i < 16; i++) {
        regs[i].val = 0;
    }
}

void CCpu::StatusReport() {
    _log->info("CPU Status:");
    _log->info("Registers:");
        _log->info("=> R0 : {0:04x}, R1 : {1:04x}, R2 : {2:04x}, R3 : {3:04x}",
            regs[0].val, regs[1].val, regs[2].val, regs[3].val);
        _log->info("=> R4 : {0:04x}, R5 : {1:04x}, R6 : {2:04x}, R7 : {3:04x}",
            regs[4].val, regs[5].val, regs[6].val, regs[7].val);
        _log->info("=> R8 : {0:04x}, R9 : {1:04x}, R10: {2:04x}, R11: {3:04x}",
            regs[8].val, regs[9].val, regs[10].val, regs[11].val);
        _log->info("=> R12: {0:04x}, R13: {1:04x}, R14: {2:04x}, R15: {3:04x}",
            regs[12].val, regs[13].val, regs[14].val, regs[15].val);

    _log->info("Run instructions: {}, {} cycles", instructions_total, cycles);
}
