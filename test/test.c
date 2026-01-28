#include "zxl.h"

int main() {
    ZXL_INIT(ZXLV_DEBUG);

    ZXL_TRACE("This is trace: %d", 1);
    ZXL_DEBUG("Debug message %s", "hello");
    ZXL_INFO("Info message");
    ZXL_WARN("Warning message");
    ZXL_ERROR("Error occurred: %s", "file missing");
    ZXL_FATAL("Fatal error!");

    return 0;
}
