.PHONY: all clean docs tarball

all: 
	python pct.py all

clean: 
	python pct.py clean

docs:
	doxygen Doxyfile

tarball:
	/bin/bash make_tarball.sh parser11

edit_vi:
	vi -p `find src -type f | sort`

edit_geany:
	geany `find src -type f | sort` &
