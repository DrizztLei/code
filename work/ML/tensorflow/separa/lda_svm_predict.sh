#!/usr/bin/env bash

TEST_FILE=$*
MODEL_FILE="lda_svm_eval.model"
OUT_FILE="out"

svm-predict ${TEST_FILE} ${MODEL_FILE} ${OUT_FILE}