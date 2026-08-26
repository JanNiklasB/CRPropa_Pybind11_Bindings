#!/bin/bash

cat @compile_commands_file@ \
	| grep -e command -m 1 \
	| sed -E "s/ /\n/g" \
	| grep -e "-D" \
	| sed -E "s/\"//g" \
	| sed -E 's/\\//g'