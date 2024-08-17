# Telnet - Blank Password

## Enumeration

The purpose of enumeration is to document the current state of the target and learn as much as possible about it.

Every server uses ports in order to serve data to clients.
We can port scan to determine the purpose of the server and see potential vulnerabilities from services running on it.

We see that Telnet is running on port 23 using `nmap -sV`. 

## Foothold

Sometimes important accounts might not have a password. Bruteforce usernames with blank password to see if there is such an account.