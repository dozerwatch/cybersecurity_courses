# FTP - Anonymous Login

The File Transfer Protocol is a standard communication protocol used to transfer computer files from a server to a client on a network.

FTP does not encrypt data being transferred. 

For secure transmission that protects the username and password and encrypts the content, FTP is often secured with SSL/TLS (FTPS) or replaced with SSH File Transfer Protocol (SFTP).

There is a high chance that an FTP service might be misconfigured or unsecured.

## Enumeration

`ping` the target to confirm that target is reachable. This not might always work because the target might have firewalls set up to prevent pinging between hosts.

`nmap -sV` to scan for services running on target.

## Foothold

A typical misconfiguration for running FTP services allows an `anonymous` account to access the service like an authenticated user. The password is disregarded.