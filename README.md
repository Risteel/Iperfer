# Iperfer
## Build
* Using `make` to build.

## Server
```bash
./Iperfer -s -p <port>
```
## Client
```bash
./Iperfer -c -h <hostname> -p <port> -t <time>
```
## Argument
* `hostname` can a hostname or an IP address
* `port` argument is greater than `1024` and less than `65535`
* `time` is the duration in seconds for which data should be generated
  * the unit of time is second
  
## What is Iperfer
* Iperfer is a common tool used to measure network bandwidth like Iperf.
* Run server mode to recieve packet and client mode to send packet, Iperfer will show the sending/receiving rate.
