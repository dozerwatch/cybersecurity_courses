# Kenobi

## Scan the machine with nmap, how many ports are open?

`nmap -sC -sV -A -oN info.nmap <target-ip>`

Output: 
```

```

> 7

## Using the nmap command below, how many shares have been found?

`nmap -p 445 --script=smb-enum-shares.nse,smb-enum-users.nse <target-ip>`

> 3

