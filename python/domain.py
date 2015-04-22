#!/usr/bin/env python
import socket

data = socket.gethostbyname(raw_input ("\nPlease enter a domain name that you wish to translate: "))
print "\n\nThe IP Address of the Domain Name is: ", data

