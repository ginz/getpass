#!/bin/bash

echo 10 > ten
./gen_pass stat <ten 2>/dev/null
rm ten
