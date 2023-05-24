#pragma once

#include <cstddef>

namespace UDA {

    template<std::size_t NElements>
    class IAdaptiveFilter {
    public:
        virtual float do_sample(std::array<float, NElements> sample) = 0;
    private:
    };

}