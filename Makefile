#	Make basic WWW distribution
#
#  See the README and the documentation on the web.
#  When you have done BUILD you will have www so you will be able to
#  read the documentation online.
#
.DEFAULT_GOAL := all

all :
	./BUILD.SH

clean:
	rm -f *[~#] */*[~#] */*/*[~#]
	rm -f *.o */*.o */*/*.o
	rm -f *.old */*.old */*/*.old

clobber: clean
	rm -f Library/[a-z0-9]*/libwww.a
	rm -f LineMode/[a-z0-9]*/www*
	rm -f Daemon/[a-z0-9]*/httpd*
	rm -f Daemon/[a-z0-9]*/htimage
	rm -f Daemon/[a-z0-9]*/htadm
	rm -f Daemon/[a-z0-9]*/cgiparse
	rm -f Daemon/[a-z0-9]*/cgiutils
	rm -rf Daemon/linux/
	rm -rf Library/linux/
	rm -rf httpd/usr
	rm -rf httpd/etc
	rm httpd.deb

package: all
	rm -rf httpd/usr
	rm -rf httpd/etc
	mkdir -p httpd/usr/bin
	cp Daemon/linux/htimage httpd/usr/bin/htimage
	cp Daemon/linux/httpd_3.0A httpd/usr/bin/httpd
	cp Daemon/linux/htadm httpd/usr/bin/htadm
	cp Daemon/linux/cgiutils httpd/usr/bin/cgiutils
	cp Daemon/linux/cgiparse httpd/usr/bin/cgiparse
	mkdir httpd/etc
	cp server_root/config/httpd.conf httpd/etc/httpd.conf
	chmod 755 httpd -R
	dpkg-deb --build httpd

install: package
	sudo apt purge httpd -y
	sudo apt install ./httpd.deb -y