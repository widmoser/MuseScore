//
// Created by Hannes Widmoser on 11/09/15.
//

#ifndef ORCHESTRALINTERFACECMAKE_MEMORYBLOCK_H
#define ORCHESTRALINTERFACECMAKE_MEMORYBLOCK_H


#include <stddef.h>
#include <string>
#include <sstream>

class Data {
public:
    Data(const size_t size = 0);

    void setSize(const size_t size);
    size_t getSize() const;

    const void* getData() const;
    void copyTo(void* destData, size_t numBytes) const noexcept;
    void copyFrom(const void* srcData, size_t numBytes) noexcept;
    void copyFromBase64(const std::string& data) noexcept;
private:
    size_t size;
    char* data;
};


#endif //ORCHESTRALINTERFACECMAKE_MEMORYBLOCK_H
