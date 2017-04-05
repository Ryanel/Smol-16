#pragma once
#include <spdlog/spdlog.h>
#include <memory.hpp>
#include <cpu/cpu.hpp>

class CSystem {
private:
    static CSystem *m_instance;
    std::shared_ptr<spdlog::logger> _log;
    CSystem();
public:
    static CSystem *instance();

public:
    bool isRunning = true;
    CCpu * cpu;
    CMemoryController * mem;

    void Init();
    void Tick();

};
