#!/bin/bash

BUILDDIR=build
VOCAB_FILE=vocab.txt
FILE_DIRECT=./sample_data/
FILE_LIST=filelist.txt
VERBOSE=2
MEMORY=32.0
MAX_ITER=100
VECTOR_SIZE=200
NUM_THREADS=8
VEC_DIRECT=./vectors/
BETA=0.01
BINARY=0
X_MAX=100
TEMP_SHUFFLE=./sample_data/temp_shuffle

$BUILDDIR/txttobin -file-direct $FILE_DIRECT -file-list $FILE_LIST
$BUILDDIR/shuffle -memory $MEMORY -verbose $VERBOSE -file-direct $FILE_DIRECT -file-list $FILE_LIST -temp-file $TEMP_SHUFFLE
$BUILDDIR/dynamic -threads $NUM_THREADS -file-direct $FILE_DIRECT -vec-direct $VEC_DIRECT -file-list $FILE_LIST -x-max $X_MAX -iter $MAX_ITER -vector-size $VECTOR_SIZE -binary $BINARY -vocab-file $VOCAB_FILE -verbose $VERBOSE -beta $BETA