#!/bin/bash

read string
echo $string

touch inc/$string.hpp
touch lib/$string.cpp
