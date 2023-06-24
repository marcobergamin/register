//
// Created by Marco Bergamin (marco.bergamin@outlook.com) on 24/06/2023.
//
#include <mabe/register.hpp>

namespace my_regs {
using reg32 = RegU32<0x1000>;
using reg8 = RegU8<0x1004>;
} // namespace my_regs

void example() {
  my_regs::reg32::set_all();
  my_regs::reg32::set_bits<2, 3, 31>();
  my_regs::reg8::set_bits<0, 7>();
  my_regs::reg8::clear_all();
  my_regs::reg8::set_bit<1>();
  my_regs::reg8::clear_bit<1>();
  my_regs::reg8::clear_bits<1,2>();
}