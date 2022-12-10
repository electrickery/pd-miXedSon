This is a forked version of https://svn.code.sf.net/p/pure-data/svn/trunk/externals/miXed/cyclone. For active development see https://github.com/porres/pd-cyclone. The local repository is in 'maintainance' only mode.

<hr>

pd-cyclone is a 'fork' of https://svn.code.sf.net/p/pure-data/svn/trunk/externals/miXed/cyclone (via the https://git.puredata.info/cgit/svn2git/libraries/miXed.git/ migrated repository). It is cleaned to contain only the cyclone functionality. Other parts of the miXed library are either moved (pddp) or unmaintained (toxy, ViCious, riddle). Cyclone and miXed is written by Krzysztof Czaja. A copy of the original cyclone page is available here: http://electrickery.nl/digaud/puredata/cyclone/cyclone_site/cyclone.html

Within the cyclone file set, the transition to a new build system, started with 0.1-alpha57 is completed. The initial version at this github repository will be 0.2beta1.

The new build system is pd-lib-builder based and only builds each object in a separate file. The old build configuration also compiled to the hammer and sickle library objects and included a cyclone meta-library. The original location of this repository is https://github.com/electrickery/pd-cyclone.

<strong>Goals</strong>

The original goal of cyclone was to create a collection of Max/MSP objects for PureData. This was in the 2000s area, Max/MSP version 4.6. Since then MAX evolved its architecture and file format to something that is incompatible with PureData. Compatibility in patch file level is limited to this very old version of Max/MSP.

Since then an unknown number of patches is made for these objects in Pure Data. This leads to an additional goal of keeping the functionality backward compatible. Only bug fixes, new objects and if possible, different behaviour with extra arguments or messages will be added. Objects that are incompatible with current Cyclone should have another name or be placed in other libraries. 

<strong>Compiling with pdlibbuilder</strong>

PdLibBuilder tries to find the Pd source directory at several common locations, but when this fails, yo have to specify the path yourself using the pdincludepath variable. Example:

<pre>make pdincludepath=~/pd-0.46-6/src/  (for Windows/MinGW add 'pdbinpath=~/pd-0.46-6/bin/)</pre>

If the user installs pd-lib-builder separately, they can just point the buildsystem to their installation, e.g. to get the latest and greatest features of pd-lib-builder.

e.g. on Debian systems do:

<pre>sudo apt-get install pd-lib-builder
make PDLIBBUILDER_DIR=/usr/share/pd-lib-builder/</pre>

<strong>Installing with pdlibbuilder</strong>

The default path for installing might not be the best, surely for testing. Use the pkglibdir variable for this. Example:

<pre>make install pkglibdir=~/pd-externals/</pre>

