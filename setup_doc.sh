#!/bin/bash
cd documentation
rm -rf docs/*
doxygen doxyfile
xdg-open docs/html/index.html