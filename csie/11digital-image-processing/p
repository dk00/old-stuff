#!/bin/sh
./med < puppy_impulse_low.raw > puppy_li.raw
./med < puppy_impulse_high.raw > puppy_hi.raw
./mean < puppy_uniform_low.raw > puppy_lu.raw
./mean < puppy_uniform_high.raw > puppy_hu.raw
./cat puppy_li.raw puppy_lu.raw puppy_hi.raw puppy_hu.raw > puppy_output.raw
