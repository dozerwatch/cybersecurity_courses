# Introduction to Cybersecurity
- [Intercepting Communication](#intercepting-communication)
    - [CIDR](#cidr-notation-classless-inter-domain-routing)

![dynamic network](/pwncollege/images/dynamic_network.png)

## Intercepting Communication
- There are three different ways to intercept communication:
    1. At the source
    2. Middle-man
    3. At the destination

- **Ethernet** 
    - physically connected
    - **(Host A --> Host B)**: A: eth0 --> vethA --> bridge0 --> vethB --> B: eth0
    - Ethernet Packet Structure:
        ```
        6 bytes - Destinaction MAC addres
        6 bytes - Source MAC address
        2 bytes - Type
        ```
- **Internet**
    - routing, hosts are not physically linked
    - Type: `0x08` `0x00` - Internet protocol
    - The Internet packet structure is more complex
        ```
        4 bits  - Version
        4 bits  - Internet Header Length
        1 byte  - Differentiated Services Field
        2 bytes - Total Length
        2 bytes - Identification
        3 bits  - Flags
        13 bits - Fragment Offset
        1 byte  - Time To Live
        1 byte  - Protocol
        2 bytes - Header Checksum
        4 bytes - Source IP Address
        4 bytes - Destination IP Address
        ? bytes - Options
        ```
- **Transmission Control Protocol**
    - Protocol: `0x06` - TCP
    - Enables a stateful interaction
    - Introduces order, reliability, and ports
    - Packet structure
        ```
        2 bytes - Source port
        2 bytes - Destination port
        4 bytes - Sequence number: Start with randomly initalized value, maps amount of data sent
        4 bytes - Acknowledgement number: Start with randomly initialized value, maps amount of data recieved
        1 octet - Data Offset: Determines number of bytes used for header and the rest is data
        3 bits  - Reserved
        9 bits - Flags
        2 bytes - Window Size: Data max size
        2 bytes - Checksum: of the header
        2 bytes - Urgent Pointer: Indicate how part of data is urgent
        ? bytes - Options
        ```
    - Sequence and Acknowledgement number relates to state
    - Flags:
        - URG: indicate Urgent Pointer field is significant
        - ACK: acknowledge other's seq number
        - PSH: push forward the data immediately
        - RST: reset the connection
        - SYN: synchronize sequence numbers, only sent in first packet for both ends
        - FIN: last packet from sender
- **Address Resolution Protocol**
    - Type: `0x08` `0x06` - ARP 
    - Packet Structure
        ```
        2 bytes - Hardware Type
        2 bytes - Protocol Type
        1 byte  - Hardware Address Length
        1 byte  - Protocol Address Length
        2 bytes - Operation
        6 bytes - Sender Hardware Address
        4 bytes - Sender Protocol Address
        6 bytes - Target Hardware Address
        4 bytes - Target Protocol Address
        ```
        - Convert from Protocol Type to Hardware Type
        - Operation: `who-has: 00 01` `is-at: 00 02`

### tcpdump
```
-A: Print each packet in ASCII
-i: listen on interface, `any` captures from all interfaces
-
``````

### CIDR Notation (Classless Inter-Domain Routing)
- An IP address allocation method that improves data routing efficiency on the Internet.
- Organizations use CIDR to allocate IP addresses flexibly and efficiently in their networks.
- An IP address has 2 parts:
    1. Network address --> networ's unique identifier
    2. Host address --> host identifier on the network
- Classful addresses:
    - has fixed length for addresses
    - the number of bits allocated to network and host portions are fixed
    - IPv4: 32 bits
    - Three classes of IPv4 addresses:
        1. Class A: 8 bit network
        2. Class B: 16 bit network
        3. Class C: 24 bit network 
- Classless addresses
    - Uses variable length subnet masking (VLSM) to alter the ratio between network and host adresses
        - A subsubet mask returns the network's address value from IP address by turning host address to zeros.

## Problems

### Level 5
```
tcpdump -A -i eth0
```

### Level 7
```
ifconfig eth0 10.0.0.2
nc -l 31337
```

### Level 8

In this challenge you will manually send an Ethernet packet. The packet should have `Ether type=0xFFFF`. The packet should be sent to the remote host at `10.0.0.3`.

``` 
scapy
>>> sendp(Ether(src=get_if_hwaddr("eth0"), type=0xffff), iface="eth0")
```

The difference between `sendp` and `send` is that the former sends packets at layer 2 while the latter sends packets are layer 3. What I don't understand is how this difference (or possibly something else) prevents me from getting the flag if I use `send` instead of `sendp`.