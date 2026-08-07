#include <sstream>

#include "..\include\errorMsg.h"

std::string outOfRangeMsg(size_t index, size_t limit) {
    std::string errorMsg;
    std::ostringstream errorMsgStream;
    errorMsgStream << "Out of range error: either " << index << " >= " << limit << "\n";
    return errorMsg;
}
