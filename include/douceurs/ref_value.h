#pragma once

namespace douceurs::value {

    template <class T>
    constexpr auto& keep(T &&x) noexcept {
        return x;
    }

}