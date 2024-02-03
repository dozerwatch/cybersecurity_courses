These are my notes, answers, and writeups for all the rooms in the Complete Beginner Pathway.

- [Metasploit Introduction](#Metasploit-Introduction)

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
  - NOP - does thing 
  - payload
    - singles - don't need to download additional components to run
    - **?** adapters - wrap single payloads
    - stagers - set up connection between Metasploit and target system
    - stages - downloaded by stagers, allow for larger payloads
  - post - post-exploitation
- `_` for single (in-line) payload, `/` for staged payload
- **msfconsole** is context-based, meaning all module options settings (unless global) will be lost if the module is changed.
- `setg` is `set` for global variables, likewise `unsetg` for `unset`
- The exploitation process is 3 steps:
  1. Find the exploit
  1. Customize the exploit
  1. Exploit the vulnerable service

### Questions
##### Task 2
- What is the name of the code taking advantage of a flaw on the target system?
  > Exploit
- What is the name of the code that runs on the target system to achieve the attacker's goal?
  > Payload
- What are self-contained payloads called?
  > Singles
- Is "windows/x64/pingback_reverse_tcp" among singles or staged payload?
  > Singles
##### Task 3
- How would you search for a module related to Apache?
  > search apache
- Who provided the auxiliary/scanner/ssh/ssh_login module?
  > todb
##### Task 4
- How would you set the LPORT value to 6666?
  > set LPORT 6666
- How would you set the global value for RHOSTS to 10.10.19.23 ?
  > setg RHOSTS 10.10.19.23
- What command would you use to clear a set payload?
  > unset payload
- What command do you use to proceed with the exploitation phase?
  > exploit

   
  
## Metasploit: 
