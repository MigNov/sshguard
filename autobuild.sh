#!/bin/bash

rm -rf sshguard-1.5
rm -f sshguard-1.5.tar.bz2

mkdir -p sshguard-1.5
cp -af * sshguard-1.5 2> /dev/null
tar -cjf ../sshguard-1.5.tar.bz2 *
mv ../sshguard-1.5.tar.bz2 .
rm -rf sshguard-1.5

autoreconf -f -i

./configure --prefix=$AUTOBUILD_INSTALL_ROOT --with-firewall=custom --with-custom=/bin/sshguard-custom-script

EXTRA_RELEASE=`whoami`

rpmbuild --nodeps \
	--define "extra_release $EXTRA_RELEASE" \
	--define "_sourcedir `pwd`" \
	-ba --clean sshguard.spec

rm -rf sshguard-1.5
rm -f sshguard-1.5.tar.bz2

echo "Done"
exit 0
