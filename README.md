# clewarecontrol docker container

Very small collection of docker containers containing a compiled version of the [clewarecontrol program][1] by 
[Folkert van Heusden][2].

Clewarecontrol is used to control all kinds of usb-devices sold by [Cleware GmbH][3] at their store.

For details on the different container please view their READMEs:

* [clewarecontrol](docker-files/clewarecontrol/README.md)
* [clewarecontrol-jre](docker-files/clewarecontrol/README.md)

## Motivation

At smartsteuer we use the [cleware traffic lights][4] to show the status of our build pipelines. Setting up the binaries 
became a bit annoying so we automated it. 

[1]: https://github.com/flok99/clewarecontrol
[2]: https://github.com/flok99
[3]: http://www.cleware-shop.de
[4]: http://www.cleware-shop.de/epages/63698188.sf/de_DE/?ObjectPath=/Shops/63698188/Products/43/SubProducts/43-1