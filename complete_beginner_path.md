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
> [!NOTE]
> `_` for single (in-line) payload, `/` for staged payload

### Questions
- What is the name of the code taking advantage of a flaw on the target system?
  - **Exploit**
- What is the name of the code that runs on the target system to achieve the attacker's goal?
  - **Payload**
- What are self-contained payloads called?
  - **Singles**
- Is "windows/x64/pingback_reverse_tcp" among singles or staged payload?
  - **Singles**
