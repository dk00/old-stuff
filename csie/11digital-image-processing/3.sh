#!/bin/sh
./fs < bear.raw > h1.raw
./rev < bear.raw | ./fs > h2.raw
./or h1.raw h2.raw > h3.raw
