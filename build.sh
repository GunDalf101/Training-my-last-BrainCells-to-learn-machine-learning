#!/bin/bash
set -xe
cc -Wextra -Werror simpleSingleBrainCell.c -o simpleSingleBrainCell
cc -Wextra -Werror moreComplexSingleBrainCell.c -o moreComplexSingleBrainCell
cc -Wextra -Werror multipleRetardedBrainCells.c -o multipleRetardedBrainCells