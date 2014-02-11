#!/bin/bash
tardate=$(date +%y%m%d)
tartime=$(date +%H%M)
tarfile=$1_$tardate\_$tartime.tgz
rm -f $tarfile
tar czf $tarfile src/ test_data/ Makefile make_tarball.sh pct.py pctrc 

