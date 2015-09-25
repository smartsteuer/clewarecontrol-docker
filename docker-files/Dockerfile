# Use phusion/baseimage as base image. To make your builds
# reproducible, make sure you lock down to a specific version, not
# to latest! See
# https://github.com/phusion/baseimage-docker/blob/master/Changelog.md
# for a list of version numbers.
FROM phusion/baseimage:0.9.17
MAINTAINER Eike <me@eike-hirsch.net>

# Use baseimage-docker's init system.
CMD ["/sbin/my_init"]

# ...put your own build instructions here...
ADD clewarecontrol-4.0 /usr/local/clewarecontrol

# we have to compile the clewarecontrol sources.
# Therefor we need a compiler and other dependencies
RUN apt-get update

RUN apt-get -y install \
	build-essential \
	libhidapi-dev

RUN apt-get -y install pkg-config

# comileing...
RUN cd /usr/local/clewarecontrol && \
	make install

# now that we have the executable we can delete everything else again.
RUN apt-get -y --purge remove \
	build-essential \
	pkg-config

RUN apt-get -y autoremove

RUN rm -r /usr/local/clewarecontrol

# ...put your own build instructions here... END

# Clean up APT when done.
RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*