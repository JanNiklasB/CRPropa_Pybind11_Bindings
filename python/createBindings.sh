#!/bin/bash

working_dir=@CMAKE_CURRENT_BINARY_DIR@
headers_to_bind_file=@headers_to_bind_file@
root_module_name=@root_module_name@
compile_commands_file=@compile_commands_file@

# rm -rf $working_dir/bindings
if [ ! -d "$working_dir/bindings" ]; then
	mkdir -p $working_dir/bindings
fi
grep -rh "#include" $headers_to_bind_file \
	| sed -E "s/#include\s+\"/#include </g" \
	| sed -E s/\"/\>/g \
	| sed -E "s/\s+$//g" \
	> $working_dir/includes_for_bindings.h
binder \
	--root-module $root_module_name \
	--prefix $working_dir/bindings/ \
	--bind $root_module_name \
	--bind-class-template-specialization \
	--annotate-includes \
	--annotate-functions \
	--config $working_dir/binder.cfg \
	--include-pybind11-stl \
	$working_dir/includes_for_bindings.h \
	-p $compile_commands_file