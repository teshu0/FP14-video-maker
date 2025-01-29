#!/bin/bash

ffmpeg -framerate 24 -i ./output/frame_%05d.ppm \
    output.gif
