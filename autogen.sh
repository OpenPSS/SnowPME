find . \( -iname '*.cpp' -o -iname '*.c' \) -exec gcc -I External/Linux/include -I LibImGui -MM -MQ '{}.o' '{}' \; | sed -e ':a; /\\$/ { N; s/ *\\\n//; ta }' >Makefile-autogen.mk
