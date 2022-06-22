# Usage
# make		# compile
# clean		# remove all binaries

.PHONY = generate clean
.DEFAULT_GOAL := generate
generate:
	@gcc  converter.c -o convert.out

clean:
	rm *.out