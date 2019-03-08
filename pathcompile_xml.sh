#!/bin/bash
echo "now start!!!!!!!!!"
gcc  -v -Wall -g -o pathparse pathxmlparse.c `pkg-config --cflags --libs libxml-2.0` -lrgb_api
echo "end!!!!!!!!!"
