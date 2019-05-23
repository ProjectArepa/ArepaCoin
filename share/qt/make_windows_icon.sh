#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/arepa.ico

convert ../../src/qt/res/icons/arepa-16.png ../../src/qt/res/icons/arepa-32.png ../../src/qt/res/icons/arepa-48.png ${ICON_DST}