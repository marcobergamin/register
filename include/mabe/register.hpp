//
// Created by Marco Bergamin (marco.bergamin@outlook.com) on 24/06/2023.
//

#ifndef MABE_REGISTER_HPP
#define MABE_REGISTER_HPP

#include <cstdint>
#include <type_traits>

namespace reg_impl {
    template<typename T, int BIT>
    inline constexpr void make_mask(T &mask) {
        mask |= T{T(1) << BIT};
    }

    template<typename T, int BIT0, int BIT1, int... BITS>
    inline constexpr void make_mask(T &mask) {
        mask |= T{T(1) << BIT0};
        make_mask<T, BIT1, BITS...>(mask);
    }
} // namespace reg_impl

template<typename T, std::size_t ADDRESS>
class Register final {
public:
    static_assert(ADDRESS
                  % std::alignment_of<T>::value == 0,
                  "Wrong alignment");

    Register(const Register &) = delete;

    Register &operator=(const Register &) = delete;

    Register(Register &&) = delete;

    Register &operator=(Register &&) = delete;

    static void set(const T &value) noexcept { reg() = value; }

    static T get() noexcept { return reg(); }

    template<int BIT>
    static void set_bit() noexcept {
        static_assert(BIT < sizeof(T) * 8U, "Out of bound");
        reg() |= T{T(1) << BIT};
    }

    template<int... BITS>
    static constexpr T make_mask() {
        T mask{};
        reg_impl::make_mask<T, BITS...>(mask);
        return mask;
    }

    template<int... BITS>
    static void set_bits() noexcept {
        constexpr
        auto mask = make_mask<BITS...>();
        reg() |= mask;
    }

    template<int BIT>
    static void clear_bit() noexcept {
        static_assert(BIT < sizeof(T) * 8U, "Out of bound");
        reg() &= ~T{T(1) << BIT};
    }

    static void set_all() noexcept { reg() = T{~0U}; }

    static void clear_all() noexcept { reg() = T{0U}; }

private:
    static volatile T &reg() {
        return *reinterpret_cast<volatile T *>(ADDRESS);
    }
};

// Defines some useful specializations:

template<std::size_t ADDRESS>
using RegU64 = Register<std::uint64_t, ADDRESS>;

template<std::size_t ADDRESS>
using RegU32 = Register<std::uint32_t, ADDRESS>;

template<std::size_t ADDRESS>
using RegU16 = Register<std::uint16_t, ADDRESS>;

template<std::size_t ADDRESS>
using RegU8 = Register<std::uint8_t, ADDRESS>;

#endif //MABE_REGISTER_HPP
