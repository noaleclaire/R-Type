#!/bin/bash
rm -rf docs/*
doxygen doxyfile
firefox docs/html/index.html