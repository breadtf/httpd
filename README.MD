# HTTPD for Debian
This is a modified version of HTTPD, packaged for Debian.

## SECURITY WARNING
This version of HTTPD is from 1994, and will obviously not support any modern HTTP features (HTTP/1.1+, Content Negotation, etc.) and will have countless security issues and exploits.

I would recommened using NGINX as a reverse proxy in-front of this server, with Fail2Ban configured very strictly to prevent any chance of exploits reaching the server.

## Installation
Head to the releases page and download `httpd.deb`.

Once installed, run `systemctl enable --now httpd` to start httpd on boot,
Or run `httpd -v -p 8080` for testing.

## Configuration
The config file is located in `/etc/httpd.conf`.

A full list of all options can be found [here](https://github.com/breadtf/httpd/blob/main/server_root/config/all.conf) or [here](https://www.w3.org/Daemon/User/Config/Overview.html).

## Building
Building is as simple as running these two commands
```
make all
make install
```
Once finished, there will be a `httpd.deb` file you can install on any 64-bit Debian system.

## Contributions
We would love to have contributions to anything in this repo (Yes, even the source code!)

I will not be making any major changes myself (except for package updates and version bumps), but you're free to open PRs and Issues.

## Licence
W3C httpd is covered by the [MIT Copyright Statement](COPYRIGHT), and with acknowledgement to [CERN](CERN)
