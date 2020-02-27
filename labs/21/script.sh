#! /usr/bin/env bash

find $(pwd) -name "Makefile*" -exec 'bash tr \\ / <{}' \; 
