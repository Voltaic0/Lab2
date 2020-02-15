default:
	cd makeprocs; make
	cd h2oinject; make
	cd so4inject; make
	cd equation1; make
	cd equation2; make
	cd equation3; make

clean:
	cd makeprocs; make clean
	cd h2oinject; make clean
	cd so4inject; make clean
	cd equation1; make clean
	cd equation2; make clean
	cd equation3; make clean


run:
	cd ../../bin; dlxsim -x os.dlx.obj -a -u makeprocs.dlx.obj 3; ee469_fixterminal
