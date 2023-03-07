//
// (c) 2023 Eduardo Doria.
//

#ifndef sokolsystem_h
#define sokolsystem_h

#include <stdint.h>

namespace Supernova{
    class SokolSystem{

    public:
        static void setup();
        static void executeQueue();
        static void commit();
        static void shutdown();

        static void scheduleCleanup(void (*cleanupFunc)(void* cleanupData), void* cleanupData, int32_t numFramesToDefer = 0);
    };
}

#endif //sokolsystem_h
