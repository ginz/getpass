#!/bin/bash

echo 10 > ten
../gen_pass lotr_stat <ten 2>/dev/null
rm ten
