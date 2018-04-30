Build Status
VirusTotal C API library This libary is designed to work with both the:

The public API https://www.virustotal.com/en/documentation/public-api/
The private API https://www.virustotal.com/en/documentation/private-api/
Runtime Dependencies

curl or libcurl (curl-devel package on some distributions)
janson version 2.2 (min) (2.5 or newer recommeded. janson-devel on some distros)
Compiling Dependencies

automake, autoconf (might be autotools package on your platform)
gcc
libtool



Debian or Ubuntu Dependencies:

sudo apt-get install automake autoconf libtool libjansson-dev libcurl4-openssl-dev
Redhat, Fedora, Centos or RPM based distros:



yum install libtool jansson-devel



To compile on Linux, BSD, or Mac OS X:


autoreconf -fi
./configure
make
sudo make install



If you wish to build the examples in the 'examples' directory:

autoreconf -fi
./configure --enable-examples
make
sudo make install
