# storm

**Storm** computes the windfield for a cyclone based on the pressure
distribution and radius to maximum winds.

This is the original Fortran 77 version of **storm**
written by Rudy Slingerland.
For more information,
see its
[model page](http://csdms.colorado.edu/wiki/Model:STORM)
on the CSDMS wiki.

Compile and run this program with a sample input file:

	$ make
	$ cp testing/data/wind.in .
	$ ./storm
