#!/bin/sh
./high < corridor_blur.raw > corridor_bc.raw
./high < corridor_noise.raw > corridor_nc.raw
./mid < corridor_noise.raw | ./high | ./grad | ./high1 | ./th0 > e1.raw
./mid < corridor_noise.raw | ./high | ./grad2 > e2.raw
