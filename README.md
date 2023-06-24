# Register

A simple utility to safely manipulate registers with zero overhead.\

# Why
I wanted to make a super simple utility with these features:

* Just a single reinterpret_cast<> for N registers, useful in case of future safety certifications
* Operations don't touch the stack. Zero stack used!
* Any bitmask calculated at compile time
* Errors like setting the bit 17 of a 16 bit registers caught at compile time
* The address of a given register is part of its type, no extra memory required to store any pointer.
* Last but not least: no macros

# Example

```cpp
#include <mabe/register.hpp>

// Lets define a couple of registers
namespace my_regs {
using reg32 = RegU32<0x1000>;
using reg8 = RegU8<0x1004>;
}  // namespace my_regs

my_regs::reg8::set_bits<0, 7>();
my_regs::reg8::clear_all();
}
```

## Setting all bits (32 bit reg)

```cpp
my_regs::reg32::set_all();
```

ARM32 assembly:

```asm
mov r3, #4096 ; 0x1000
mvn r2, #0
str r2, [r3]
```

## Setting bits 2,3,31 (32 bit reg)

```cpp
my_regs::reg32::set_bits<2, 3, 31>();
```

ARM32 assembly:

```asm
mov r2, #4096            ; 0x1000
ldr r3, [r2]
orr r3, r3, # 2147483636 ; 0x8000000c
str r3, [r2]
```

## Clearing bit 1 (8 bit reg)

```cpp
my_regs::reg8::clear_bit<1>();
```

ARM32 assembly:

```asm
mov	r2, #4096	; 0x1000
ldrb	r3, [r2, #4]
and	r3, r3, #253	; 0xfd
strb	r3, [r2, #4]
```

# !!! Note !!!

This project is still work in progress. Any feedback is appreciated.