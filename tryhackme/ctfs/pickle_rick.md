# Pickle Rick
**What is the first ingredient that Rick needs?**

The first step is always enumeration.
Viewing the source page gives a username `R1ckRul3s`, so we can infer that there is a password lying around somewhere.

Running an `nmap` scan shows there's also `ssh` open, so we know we will be using `ssh` later on.

Running `gobuster` gives us a list of interesting pages.
```
gobuster dir -u http://<ip>/ -w /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt -x .php,.html,.txt,.js
```
- `/robots.txt` - Wubbalubbadubdub
    - This is the password to the username we got from source page.
- `/login.php` - this is a login page, we can use the credentials to log in
- `clue.txt` - Look around the file system for the other ingredient.
- `portal.php` - after logging in, this is a command interface

Execute `ls` and we see a `Sup3rS3cretPickl3Ingred.txt` file. We can read it with the `less` command.
> mr. meeseek hair

**What is the second ingredient in Rick’s potion?**

Gain a reverse shell with python. Then navigate to the home directory for rick and we see the second ingredient.
> 1 jerry tear

**What is the last and final ingredient?**

Privilege escalation with `sudo su` which is just permitted. We then see the final ingredient in the root folder.
> fleeb juice