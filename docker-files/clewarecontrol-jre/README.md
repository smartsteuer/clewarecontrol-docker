# clewarecontrol-jre
Simple container with the clewarecontrol binary and a current jre ready to run.

## how to run
When running the container be sure to provide the `--privileged` flag and to 
bind the usb bus to this container `-v /dev/bus/usb:/dev/bus/usb`.

```bash
docker run --privileged -v /dev/bus/usb:/dev/bus/usb smartsteuer/clewarecontrol:latest
```

## how to test
```bash
docker exec <containerId> clewarecontrol <opts> <args>
```

## docker-machine a.k.a. boot2Docker
 When using boot2Docker on OSX or Windows be sure to active 
 the USB-Controller and create a filter for your device on the boot2Docker-VM.