#!/bin/sh
./linear < sample.raw > o1.raw
./eq < sample.raw > o2.raw
./quan < o2.raw > o3.raw
./cat sample.raw o1.raw o2.raw o3.raw > sample_output.raw
