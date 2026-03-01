#include "IXSelectInterruptFactory.h"
#include "IXSelectInterruptEvent.h"

namespace ix
{
    std::unique_ptr<SelectInterrupt> createSelectInterrupt()
    {
        /* * On ESP32, we use EventFD-based implementation because 
         * POSIX pipe() is not supported in the ESP-IDF networking stack.
         */
        return std::make_unique<SelectInterruptEvent>();
    }
} // namespace ix
