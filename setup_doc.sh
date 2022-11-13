#!/bin/bash
cd docs
rm -rf docs/*
doxygen doxyfile
xdg-open docs/html/index.html