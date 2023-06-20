#pragma once

#include <LFramework/Containers/StaticVector.h>

template<typename MapDataContainerToFilter, std::size_t maxNumberElements>
using StaticVector= LFramework::StaticVector<MapDataContainerToFilter, maxNumberElements>;

class ITransmitter {
public:
    ITransmitter() {
    }
    virtual std::size_t append(uint8_t* data, std::size_t size) = 0;
    virtual ~ITransmitter() = default;
};

struct DataContainer {
    int16_t * data;
    std::size_t size;            
};

struct MapDataContainerToFilter {
    DataContainer container;
    uint8_t numberFilter;
};

#include <LC_NLMS.h>
