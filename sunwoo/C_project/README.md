VirusTotal API를 사용해 만든 VirusScanner입니다.

오픈소스를 이용해서 짰습니다. 그래서 그런지 라이브러리 의존성 문제가 생겨 라이브러리를 일일이 추가하는 방법으로는 

코드를 짜기 힘듭니다. 그래서 configure을 이용하여 자동으로 해결해주는 방법을 사용합니다.



필요한 package는 다음과 같습니다.
1.automake
2.autoconf 
3.gcc
4.libtool
5.libjansson-dev
6.libcurl4-openssl-dev

위의 package를 설치하는 방법은 다음과 같습니다.
 Ubuntu:
sudo apt-get install automake autoconf libtool libjansson-dev libcurl4-openssl-dev
Redhat, Fedora, Centos or RPM based distros:



 Ubuntu compile:
autoreconf -fi
./configure
make
sudo make install


 파일의 구성코드 중, examples 디렉토리만을 빌드하고 싶을 경우
autoreconf -fi
./configure --enable-examples
make
sudo make install
