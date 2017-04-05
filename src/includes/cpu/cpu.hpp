#pragma once
#include <stddef.h>
#include <string>
#include <spdlog/spdlog.h>
class CSystem;


/// Negative Flag
#define CPU_FLAG_N 0x1
/// Zero Flag
#define CPU_FLAG_Z 0x2
/// Carry Flag
#define CPU_FLAG_C 0x4
/// Overflow Flag
#define CPU_FLAG_V 0x8

class CCpu {
public:
    std::shared_ptr<spdlog::logger> _log;

    bool isActive = true;
    uint64_t instructions_total = 0;
    uint64_t instructions_last = 0;
    uint64_t ips = 0;
    uint64_t cycles = 0;
    CCpu();
    ~CCpu();

    CSystem * sys;

    typedef struct {
        struct {
            union {
                struct {
                    uint8_t low;
                    uint8_t hi;
                };
                uint16_t val;
            };
        };
    } reg_t;

    reg_t regs[16];

    //bool cpuActive();
    void Init();
    void Start();
    void Stop();
    void Tick();
    void RunNext();
    void Reset();
    void InterpretCycle();
    void StatusReport();
};
