//
// Created by Hannes Widmoser on 11/09/15.
//

#include <stdlib.h>
#include <string>
#include <sstream>
#include <vst/third_party/libb64/include/b64/decode.h>
#include <cstring>

#include "Data.h"

Data::Data(const size_t size) : size(size) {
    if (size > 0) {
        data = (char*) malloc(size);
    } else {
        data = nullptr;
    }
}

void Data::setSize(const size_t size) {
    this->size = size;
    if (data != nullptr) {
        free(data);
    }
    data = (char*) malloc(size);
    memset(data, 0, size);
}

size_t Data::getSize() const {
    return size;
}

const void* Data::getData() const {
    return data;
}

void Data::copyTo(void* destData, size_t numBytes) const noexcept {
    memcpy(destData, getData(), numBytes);
}

void Data::copyFrom(const void* srcData, size_t numBytes) noexcept {
    setSize(numBytes);
    memcpy(data, srcData, numBytes);
    size = numBytes;
}

void Data::copyFromBase64(const std::string& encoded) noexcept {
    base64::decoder d;

    std::stringstream encodedStream(encoded);
    std::stringstream decodedStream;
    d.decode(encodedStream, decodedStream);

    std::string decoded = decodedStream.str();
    copyFrom(decoded.c_str(), decoded.size());
}