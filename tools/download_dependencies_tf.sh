#!/bin/sh

wget https://github.com/second-state/ssvm-tensorflow-deps/releases/download/0.7.3/ssvm-tensorflow-deps-TF-0.7.3-manylinux2014_x86_64.tar.gz
tar -zxvf ssvm-tensorflow-deps-TF-0.7.3-manylinux2014_x86_64.tar.gz
rm -f ssvm-tensorflow-deps-TF-0.7.3-manylinux2014_x86_64.tar.gz
ln -sf libtensorflow.so.2.4.0 libtensorflow.so.2
ln -sf libtensorflow.so.2 libtensorflow.so
ln -sf libtensorflow_framework.so.2.4.0 libtensorflow_framework.so.2
ln -sf libtensorflow_framework.so.2 libtensorflow_framework.so
