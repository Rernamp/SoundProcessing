#pragma once

#include <Filters/IAdaptiveFilter.h>

#include <array>

namespace UDA {
    template<std::size_t NElements, std::size_t FilterOrder>
    class FrostAdaptiveFilter : public IAdaptiveFilter<NElements> {
    public:
        FrostAdaptiveFilter() {

        }

        float do_sample(std::array<float, NElements> sample) override {
            float result = -1.0f;

            return result;
        }
    private:
        std::array<float, NElements * FilterOrder> _impulseResponse {0};
    };
}